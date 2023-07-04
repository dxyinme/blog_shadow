---
title: LIBPNG学习笔记
date: 2021-10-23 15:20:39
tags: 技术相关
---

## 写在前面

一些libpng相关的内容

## 一些用到的库

### 安装PIL
```bash
sudo apt-get install python3-pip
pip3 install pillow -i https://mirrors.aliyun.com/pypi/simple/
```
### libpng安装和使用
下载地址 https://sourceforge.net/projects/libpng/files/
解压之后
```bash
./configure
make check
sudo make install
```
libpng好像还需要依赖zlib

zlib 走这个下载 https://zlib.net/
然后基本也是跟libpng一样的安装方式。

就装好了，要用的话就在cmake链接里面加一下就行
```cmake
cmake_minimum_required(VERSION 3.1)
project(uxpng)
set(CMAKE_CXX_STANDARD 14)
add_executable(uxpng main.cpp)
target_link_libraries(uxpng png)
```

## jpg2png

```python
# coding: utf-8
# python3
from PIL import Image
import sys

if __name__ == '__main__' :
	pg = '{}.jpg'.format(sys.argv[1])
	img = Image.open(pg)
	img.save('{}.png'.format(sys.argv[1]))

```
这是一个把jpg文件转换成png文件的脚本，为啥要这样呢，主要是因为这里主要是在用libpng玩东西，所以有了这么个脚本

## PNG基础

https://gitee.com/dxyinme/uxpng 这里是我学习libpng相关的一些操作和实践

### 图像类型
```cpp
//摘抄自libpng的定义
#define PNG_COLOR_MASK_PALETTE    1
#define PNG_COLOR_MASK_COLOR      2
#define PNG_COLOR_MASK_ALPHA      4

#define PNG_COLOR_TYPE_GRAY 0   // 灰度图
#define PNG_COLOR_TYPE_PALETTE  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE) // 调色板（我也不知道啥玩意儿）
#define PNG_COLOR_TYPE_RGB        (PNG_COLOR_MASK_COLOR) // RGB图
#define PNG_COLOR_TYPE_RGB_ALPHA  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA) // RGB+透明度图
#define PNG_COLOR_TYPE_GRAY_ALPHA (PNG_COLOR_MASK_ALPHA) // 灰度+透明度图
```
先不考虑调色板的话，PNG一共有4种格式。抛开固定格式，整个图的存储方式大致是一个二维的矩阵，矩阵的每个元素可以被看成是一个像素, 每个像素按照自己的图像类型，以某些特定的方式排列。例如RGB类型的图像，他的排列方式就是
```cpp
|B|G|R| // 通道数为3
```
如果是RGB-alpha(有透明通道)的图像，他的排序方式就是
```cpp
B|G|R|A| // 通道数为4
```
灰度图和灰度透明图只有一个（两个）通道，用来表示每个像素的灰度和透明度。

## 图像的读写

### 读取png图像
```cpp
fp = fopen(img_path, "rb"); // 打开文件
png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr); // 初始化png读指针
info_ptr = png_create_info_struct(png_ptr); // 初始化内容指针
png_init_io(png_ptr, fp); // 初始化io指针
png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, nullptr); // 读取png
```
首先，先获取图像的基本信息
```cpp
int channels, color_type, bit_depth, width, height;
channels = png_get_channels(png_ptr, info_ptr);
color_type = png_get_color_type(png_ptr, info_ptr);
bit_depth = png_get_bit_depth(png_ptr, info_ptr);
width = png_get_image_width(png_ptr, info_ptr);
height  = png_get_image_height(png_ptr, info_ptr);
```
其次再获取整个图像矩阵
```cpp
auto row_pointers = png_get_rows(png_ptr, info_ptr);
```
这里的图像矩阵的高是height，宽是 channels * width 读取像素的时候需要获取连续channels个元素。

### 输出png图像
```cpp
png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr); // 这里要设置成write_struct
png_init_io(png_ptr, fp);
png_set_IHDR(png_ptr, info_ptr,
	png_data->Width(), png_data->Height(), png_data->BitDepth(), 
	png_data->ColorType(),
	PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
png_write_info(png_ptr, info_ptr);
// 先写入图像基本信息
```
按行写入图像的某个图像行,这个是按顺序的，调用一次，下一次写的行数+1。
```
png_write_row(png_ptr, row_ptr);
```