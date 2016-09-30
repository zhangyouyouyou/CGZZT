# CGZZT
A dirty deal between three beautiful sister and an uncle

## 工具准备

- [Mxnet](https://github.com/dmlc/mxnet/releases)
- Anaconda2
- cv2 (conda install -c https://conda.binstar.org/menpo opencv)

## 代码说明

### inception-bn-28.py

我们采用一个小型的28*28的inception-bn网络

### conv.py

进行训练的代码，参数在文件里面调（改成参数怕更不直观...）

### predict.py

用模型文件进行预测（内含切图部分）

### im2rec.py

进过简单修改的mxnet提供的将图片制作成二进制格式训练集的工具，原版有些问题

### showRec.py

提取二进制格式训练集中的图片的工具，查看训练集是否制作正确

### cal.py

统计当前目录下的中文文件信息

### pull.py

在指定网址循环下载图片

### *.rec

二进制格式训练集

### *-symbol.json

网络的json格式

### *.params

网络的参数权重
