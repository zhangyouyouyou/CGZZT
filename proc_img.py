# -*- coding: utf-8 -*-
import cv2
import numpy as np
from os import walk

def get_all_dir_files():
    f = []
    for (dirpath, dirnames, filenames) in walk('.'):
        f.extend(filenames)
        break
    return f

def guass(image_path):
    src = cv2.imread(image_path,cv2.IMREAD_GRAYSCALE)
    # Reverse black and write
    src = 255 - src
    # threshold
    retval, dst = cv2.threshold(src, 200, 255, cv2.THRESH_BINARY)
    return dst

def crop(img):
    a = img[10:45,33:54]
    b = img[10:45,54:78]
    c = img[10:45,78:102]
    d = img[10:45,102:122]
    a = norm(a)
    b = norm(b)
    c = norm(c)
    d = norm(d)
    return [a,b,c,d]

def norm(img):
    ylen = (35 - img.shape[1]) / 2
    res = np.zeros((35,35),dtype = np.uint8)
    res[:,ylen:ylen + img.shape[1]] = img
    res = cv2.resize(res,(28,28))
    return res

def depart_training_pic(name):
    if len(name.split('.')) == 1:
        name = name + '.png'
    res = guass(name)
    four_pic = crop(res)
    for i in range(4):
        cv2.imwrite('%c-' % name[i] + name + '-.jpg',four_pic[i])

if __name__ == '__main__':
    files = get_all_dir_files()
    for fname in files:
        if fname.split('.')[1] == 'png':
            depart_training_pic(fname)
