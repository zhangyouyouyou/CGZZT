# -*- coding: utf-8 -*-
# pylint: skip-file
import sys
import mxnet as mx
import numpy as np
import numba
import os, pickle, gzip
import logging

import importlib

# symbol net

def get_simple(output_num = 36):
    data = mx.symbol.Variable('data')
    conv1= mx.symbol.Convolution(data = data, name='conv1', num_filter=32, kernel=(3,3), stride=(2,2))
    bn1 = mx.symbol.BatchNorm(data = conv1, name="bn1")
    act1 = mx.symbol.Activation(data = bn1, name='relu1', act_type="relu")
    mp1 = mx.symbol.Pooling(data = act1, name = 'mp1', kernel=(2,2), stride=(2,2), pool_type='max')

    conv2= mx.symbol.Convolution(data = mp1, name='conv2', num_filter=32, kernel=(3,3), stride=(2,2))
    bn2 = mx.symbol.BatchNorm(data = conv2, name="bn2")
    act2 = mx.symbol.Activation(data = bn2, name='relu2', act_type="relu")
    mp2 = mx.symbol.Pooling(data = act2, name = 'mp2', kernel=(2,2), stride=(2,2), pool_type='max')


    fl = mx.symbol.Flatten(data = mp2, name="flatten")
    fc2 = mx.symbol.FullyConnected(data = fl, name='fc2', num_hidden=output_num)
    softmax = mx.symbol.SoftmaxOutput(data = fc2, name = 'sm')
    return softmax

# data

train_dataiter = mx.io.ImageRecordIter(
    #rec文件的路径
    path_imgrec="train.rec",
    #iterator生成的每一个实例的shape
    data_shape=(1,28, 28),
    #batch的大小
    batch_size=20,
    #
    label_name='sm_label')

val_dataiter = mx.io.ImageRecordIter(
    #rec文件的路径
    path_imgrec="val.rec",
    #iterator生成的每一个实例的shape
    data_shape=(1,28, 28),
    #batch的大小
    batch_size=20,
    #
    label_name='sm_label')



num_epoch = 100
network_name = 'inception-bn-28'
softmax = importlib.import_module(network_name).get_symbol(36)
# softmax = get_simple()
model = mx.model.FeedForward(softmax,mx.cpu(),
                             num_epoch=num_epoch,
                             learning_rate=0.001, wd=0.0001,
                             momentum=0.9)

def train():
    # print logging by default
    logging.basicConfig(level=logging.DEBUG)
    console = logging.StreamHandler()
    console.setLevel(logging.WARNING)
    logging.getLogger('').addHandler(console)
    # batch_callback = [mx.callback.Speedometer(train_dataiter.batch_size, frequent=50),mx.callback.log_train_metric(50)]
    batch_callback = mx.callback.log_train_metric(10)
    epoch_callback = mx.callback.do_checkpoint(network_name)
    #
    eval_metrics = ['accuracy']
    # TopKAccuracy only allows top_k > 1
    for top_k in [2, 3]:
        eval_metrics.append(mx.metric.create('top_k_accuracy', top_k = top_k))

    model.fit(X=train_dataiter,
              eval_data=val_dataiter,
              batch_end_callback=batch_callback,
              epoch_end_callback=epoch_callback,
              eval_metric = eval_metrics)
    logging.info('Finish fit...')
    prob = model.predict(val_dataiter)
    logging.info('Finish predict...')
    val_dataiter.reset()
    y = np.concatenate([batch.label[0].asnumpy() for batch in val_dataiter]).astype('int')
    py = np.argmax(prob, axis=1)
    acc1 = float(np.sum(py == y)) / len(y)
    logging.info('final accuracy = %f', acc1)
    assert(acc1 > 0.94)


if __name__ == "__main__":
    train()
