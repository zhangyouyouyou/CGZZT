# -*- coding: utf-8 -*-
"""
Created on Wed Aug 24 10:53:05 2016

@author: tan
"""

import mxnet as mx;
import cv2
# %matplotlib inline

train_iter = mx.io.ImageRecordIter(
    path_imgrec = 'train.rec',
    data_shape  = (1, 28, 28),
    batch_size  = 10)

data = train_iter.getdata().asnumpy()


for i in range(len(data)):
    X = data[i].transpose((1, 2, 0))
    X = cv2.cvtColor(X, cv2.COLOR_GRAY2RGB)
    cv2.imwrite("result%d.png"%(i), X)