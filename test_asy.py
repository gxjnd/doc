









import aiohttp
import asyncio
import time
from bs4 import BeautifulSoup
from urllib.request import urljoin
import re

import os
import concurrent


base_url = "https://t.me/"
# base_url = "http://127.0.0.1:4000/"

# DON'T OVER CRAWL THE WEBSITE OR YOU MAY NEVER VISIT AGAIN
if base_url != "http://127.0.0.1:4000/":
  restricted_crawl = True
else:
  restricted_crawl = False

seen = set()
unseen = set([base_url])

#print(unseen)
def parse(html):
  soup = BeautifulSoup(html, 'lxml')
  #print(html)
  urls = soup.find_all('a', {"href": re.compile('^/.+?/$')})
  print(urls)
  title = soup.find('h1').get_text().strip()
  page_urls = set([urljoin(base_url, url['href']) for url in urls])
  url = soup.find('meta', {'property': "og:url"})['content']
  return title, page_urls, url
  
def parse_1(html):
  pre = ''
  usr_t = pre+"user.txt"
  view_tg_t =   pre+"view_tg.txt"
  
  usr_t_2 = pre+ "user_2.txt"
  view_tg_t_2 =  pre+ "view_tg_2.txt"
  
  soup = BeautifulSoup(html, 'lxml')
  #print(html)
  contact = soup.find_all('title')
  if (len(contact)==0):
    contact=''
  elif(len(contact)!=0):
    
    contact = contact[0].get_text().split('@')
    if(len(contact)<2):
      contact=''
    else:
      contact=contact[1]                    
#  time.sleep(6)

  

  
  urls_img = soup.find_all('img')
  if (len(urls_img)==0):
    urls_img=''
  elif(len(urls_img)!=0):
    urls_img = urls_img[0]['src']                     
#  time.sleep(6)


  title_b = soup.find_all("div", {"class": "tgme_page_title"})
  if (len(title_b)==0):
    title_b=''
   # print(html)
  elif(len(title_b)!=0):
    title_b = title_b[0]('span')[0].get_text()                

  
  
  extra = soup.find_all("div", {"class": "tgme_page_extra"})
  if (len(extra)==0):
    extra=''
   # print(html)
  elif(len(extra)!=0):
    extra = extra[0].get_text().strip()

                             
 
 
  description = soup.find_all("div", {"class": "tgme_page_description"})
  if (len(description)==0):
    description=''
  elif(len(description)!=0):
    description = description[0].get_text().strip()                           
  
  
  
  send_message = soup.find_all("a", {"class": "tgme_action_button_new"})
  if (len(send_message)==0):
    send_message=''
   # print(html)
  elif(len(send_message)!=0):
    send_message = send_message[0].get_text().strip()


  send_message_2 = soup.find_all("a", {"class": "tgme_action_button"})
  if (len(send_message_2)==0):
    send_message_2=''
   # print(html)
  elif(len(send_message_2)!=0):
    send_message_2 = send_message_2[0].get_text().strip()


  
  button_label = soup.find_all("span", {"class": "tgme_action_button_label"})
  if (len(button_label)==0):
    button_label=''
  elif(len(button_label)!=0):
    button_label = button_label[0].get_text().strip()                           
  
  if(send_message=="Send Message"):
    txt = f"@{contact} {send_message} {title_b} {extra} {description} {urls_img}  "           

    with open(usr_t, 'a') as f:
      f.write(f"{txt}\n")
    
  elif(send_message=="View in Telegram"):
    txt = f"@{contact} {send_message} {title_b} {extra} {description} {urls_img}  "           
    print(txt)
    with open(view_tg_t, 'a') as f:
      f.write(f"{txt}\n")
    
  else:
    #print(html)
    if(send_message_2=="View in Telegram"):
      txt = f"@{contact} {send_message} {title_b} {extra} {description} {urls_img}  "           
      print(txt)
      with open(view_tg_t_2, 'a') as f:
        f.write(f"{txt}\n")
      
    elif(send_message_2=="Send Message"):
      txt = f"@{contact} {send_message} {title_b} {extra} {description} {urls_img}  "           
  
      with open(usr_t_2, 'a') as f:
        f.write(f"{txt}\n")
      
    else:
      pass
      #print(html)
      print(f"@{contact} {urls_img} {title_b} {extra} {description} {send_message}  ")
  '''
  print(urls_img)
  print(title_b)
  print(extra)
  print(description)
  print(send_message)
  '''
 # return send_message,extra,title_b
  
  #for image in urls_img:
   # print(image['src'])
  #print(urls_img)
  #print(len(urls_img))
  '''
  title = soup.find('h1').get_text().strip()
  page_urls = set([urljoin(base_url, url['href']) for url in urls])
  url = soup.find('meta', {'property': "og:url"})['content']
  return title, page_urls, url
  '''


def read_l(begin,line):
  pre=''
  data_t =  pre+"data.txt"
  t = []
  with open(data_t, "rb") as file:
    if(begin==1):
      file.seek(0, os.SEEK_SET)
      for k in range(line):
        read_result = file.read(5)
        file.seek(1, os.SEEK_CUR)
        t.append(read_result.decode())
       
    else:
      start = (begin -1)*6
      file.seek(start, os.SEEK_SET)
      for k in range(line):
        read_result = file.read(5)
        file.seek(1, os.SEEK_CUR)
        t.append(read_result.decode())
  return t

  
  
  
async def crawl(url, session):
  r = await session.get(url)
  html = await r.text()
  await asyncio.sleep(0.1)        # slightly delay for downloading
  
  return html
  

async def main(loop):
  pre=''
  url_id_t =  pre+"url_id.txt"
  while 1:
      
    with open(url_id_t, "rb") as file:
      file.seek(-2, os.SEEK_END)
      while file.read(1) != b'\n':
        if (file.seek(-2, os.SEEK_CUR) == 0):
          break
      tail_c = file.readline().decode().strip()
    print(tail_c)
    
    
    start=int(tail_c)+ 1
    number_of_lines = 10
    #  pool = mp.Pool(2)               # slightly affected
    async with aiohttp.ClientSession() as session:
      count = 1
      d_t=[]
      
      d_t = read_l(start,number_of_lines)
      #print(d_t) 
      
  
      len_d_t = len(d_t)
      tasks = []
      for i in range(0,len_d_t):
        end_url =d_t[i]
        url = f"{base_url}{end_url}"
        task = loop.create_task(crawl(url, session))
        print("finish")
        tasks.append(task)
      finished = await asyncio.gather(*tasks)
      with open(url_id_t, 'a') as f:
        f.write(f"{int(tail_c)+number_of_lines}\n")
  
    #  for i in range(len(finished)):
       # url_list = finished[i]
       # print(url_list)
      with concurrent.futures.ProcessPoolExecutor() as executor:
        ##print(len(finished))
        results = executor.map(parse_1, finished)
       # for result in results:
        #  print()
      #print(len(finished))
      #print()
      
      #with open('wb.txt', 'w') as f:
       # f.write(f"{finished[2]}")
      '''
      for i in range(len(finished)):
        parse_jobs = pool.apply_async(func=parse_1, args=(finished[i],))
      results = [j.get() for j in parse_jobs]
      print(results)
      '''
      #parse_1(finished[1])
      #htmls = [f.result() for f in finished]
      #parse_jobs = [pool.apply_async(parse_1, args=(html,)) for html in htmls]
     
        
        
  
  '''
    htmls = [f.result() for f in finished]
    
    results = [j.get() for j in parse_jobs]
    
    seen.update(unseen)
    unseen.clear()
    for title, page_urls, url in results:
        print(count, title, url)
        unseen.update(page_urls - seen)
        count += 1
  
  '''


            
if __name__ == "__main__":
  t1 = time.time()
  loop = asyncio.get_event_loop()
  loop.run_until_complete(main(loop))
  loop.close()
  print("Async total time: ", time.time() - t1)
