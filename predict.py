# -*- coding: utf-8 -*-
import mxnet as mx
import numpy as np
import cv2
import logging

color_modes = {-1: cv2.IMREAD_UNCHANGED,
    0: cv2.IMREAD_GRAYSCALE,
    1: cv2.IMREAD_COLOR}

model_name = 'inception-bn-28'
def load_model():
    return mx.model.FeedForward.load(model_name,22)

def load_val_dataiter():
    val_dataiter = mx.io.ImageRecordIter(
        #rec文件的路径
        path_imgrec="val.rec",
        #iterator生成的每一个实例的shape
        data_shape=(1,28, 28),
        #batch的大小
        batch_size=100,
        #是否随机从原图中切取出一个data_shape大小
        rand_crop=True,
        #是否随机水平反射
        rand_mirror=True,
        #
        label_name='sm_label')

    return val_dataiter

def predict_val_by_model(mod,val_dataiter):
    prob = mod.predict(val_dataiter)
    val_dataiter.reset()
    y = np.concatenate([batch.label[0].asnumpy() for batch in val_dataiter]).astype('int')
    py = np.argmax(prob, axis=1)
    acc = float(np.sum(py == y)) / len(y)
    print 'final accuracy = %f' % acc

def predict_pic_by_model(mod,path):
    im = cv2.imread(path,color_modes[0])
    assert(im.shape == (28,28))
    im.shape = (1,1,28,28)
    dataiter = mx.io.NDArrayIter(
        im)
    prob = mod.predict(dataiter)
    # print prob
    py = np.argmax(prob,axis = 1)
    # print 'predict ans = ', py[0]
    return py[0]

if __name__ == "__main__":
    mod = load_model()
    # ans = predict_pic_by_model(mod,'code.jpg')
    predict_val_by_model(mod,load_val_dataiter())
    # print 'predict = ',ans
