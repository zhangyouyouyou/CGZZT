# -*- coding:utf-8 -*-

import urllib
url = r"http://www.ceair.com/addservice/image-create!handleRequest.shtml?21?37?67?94?35?66?61?76"
for i in range(100):
    path = "%d.jpg" % i  
    data = urllib.urlretrieve(url,path)
