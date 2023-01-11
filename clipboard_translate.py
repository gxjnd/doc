from __future__ import division, print_function, absolute_import

import  os 
import time
import argparse
import re
from pypdf import PdfReader



import sys

try:
  from sh import termux_clipboard_get
  from sh import termux_clipboard_set
except ImportError:
  print('Unable to find termux_clipboard')
  print('Please install or update termux-api')
  print(' $ pkg install termux-api')
  sys.exit(2)


class Clipboard:
  
  """
  (Get or Set) the system clipboard text.
  """
  def __init__(self):
    self.memory = termux_clipboard_get() or ''

  def get(self):
    '''
    Get the system clipboard text.
    '''
    self.memory = termux_clipboard_get() or ''
    return self.memory

  def set(self, text):
    '''
    Set the system clipboard text.
    '''
    self.memory = str(text)
    termux_clipboard_set(str(text))

  def __str__(self):
    self.memory = termux_clipboard_get() or ''
    return self.memory


reader = PdfReader("1.pdf")
t1 = Clipboard();
translate_f="1.txt"

def get_pdf_txt(i):
  
  page = reader.pages[i-1]
  str_t = page.extract_text()
  return str_t

def get_pdf_n(i,i_page_sign):
  str_t = get_pdf_txt(i).lstrip()
  str_t = get_pdf_txt(i).rstrip()
  if (i_page_sign != 0):
    str_t = str_t[i_page_sign:].lstrip()
  len_str = len(str_t)
 # print(f"len {len_str}")
  if (i>10):
    find_num = len(str(i-10))
  else:
    find_num = len(str(i))
  
  #print(str_t)
  #print(find_num)
  end_num = str_t[-find_num:]
  
  if (end_num==''):
    
    return 0,0
  second_page_sign = 0
 # if(i == int(end_num)):
  if(True):
    
    is_num = bool(re.search("^[0-9]*$",end_num))
    #print(f"the page i :{i} " )
    if (is_num):
    #str_n = str_t[:-find_num].rstrip()
      str_n = str_t[:-find_num].rstrip()
      print(f"the page:{end_num} " )
    else:
      str_n = str_t
      print(f"the page:  " )
    
    len_str_n = len(str_n)
    if(len_str_n==0):
      return   0,0  
    str_n_end = str_n[len_str_n-1]
    if (str_n_end != '.'):
     # print(str_n_end)
      str_n2 = get_pdf_txt(i+1)
      str_n2_first = str_n2.find('.')+1
      second_page_sign = str_n2_first
     # print(str_n2_first)
      str_n2_first_sentence = str_n2[:str_n2_first].lstrip()
      str_n_all = str_n + ' ' + str_n2_first_sentence
      #print(str_n_all)
      #print("\n\n\n")
      #print(str_n2[str_n2_first:])
    else:
      str_n_all = str_n
  else:
    return   0,0  

  return   str_n_all,  second_page_sign  



def is_chinese(chr):
  return len(chr.encode('utf8')) > len(chr)

def check_same(str_n_all):
 # print("here")
  let_stop = 1
  while (let_stop):
    from_clipboard =  t1.get()
    
    if (from_clipboard==str_n_all or from_clipboard==''):
        
        os.popen('su -c "am start -n com.android.chrome/com.google.android.apps.chrome.Main"')
        time.sleep(1)
        os.system('su -c "input tap 540 1014"')
        time.sleep(3)
        os.popen('su -c "am start -n com.termux/.app.TermuxActivity"')
        
       # return True
    else:
    #  print("here")
      #print(from_clipboard)
    #  print("$here")
      is_cn = is_chinese(from_clipboard)
      if(is_cn):
        #print(from_clipboard)
        let_stop =0
  return from_clipboard
        


def auto_mode(p_range):
  i_page_sign = 0
  if (p_range=='f'):
    stat_p  = 1
    end_p = 245
  else:
    pages_r = input("please input page range : ")
    
    pages_r = pages_r.split(',')
    #print(pages_r[0])
   # print(pages_r[1])
    stat_p  = int(pages_r[0])
    end_p = int(pages_r[1])+1
    
  for page in range(stat_p,end_p):
    str_n_all ,second_page_sign =  get_pdf_n(page,i_page_sign)
    #print(str_n_all)
    if(str_n_all==0 and second_page_sign== 0):
      pass
    i_page_sign = second_page_sign
    if(len(str(str_n_all)) <4):
      continue
    t1.set(str_n_all)
    


    translate_s = str(check_same(str_n_all))
   # print(translate_s)
    with open(translate_f,"a+",encoding="utf-8") as q:
      q.write(translate_s)
      q.write("\n\n")
      q.write("\t\t-----"+str(page)+ "-----\t")
      q.write("\n\n")


def input_mode():
  i_page_sign = 0
  page = 1;
  while(page!=9999):
    pages = input("please input page : ")
    
    if( pages == 'n'):
      page = page+ 1
    else:
      page = int(pages)
    
    
    str_n_all ,second_page_sign =  get_pdf_n(page,i_page_sign)
    #print(str_n_all)
    if(str_n_all==0 and second_page_sign== 0):
      pass
    i_page_sign = second_page_sign
    
    t1.set(str_n_all)
    #check_same(str_n_all)
   # os.system('su -c "setprop service.adb.tcp.port 5555"')
   # os.system(' su -c "stop adbd"')
  #  os.system(' su -c "start adbd"')
  #  os.system('su -c "am start -n com.android.chrome/com.google.android.apps.chrome.Main"')


def main():
  
  parser = argparse.ArgumentParser(description="translate pdf")
  parser.add_argument("-m","--mode" ,help = "mode",default="i")
  parser.add_argument("-r","--range" ,help = "range",default="f")

  modes = parser.parse_args()
  
  
  mode = modes.mode
  p_range = modes.range
  if (mode == 'i'):
    input_mode()
  if (mode == 'a'):
    auto_mode(p_range)


if __name__=="__main__":
  
  
  main()

