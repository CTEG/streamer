 `libjpeg`是一个完全用`C`语言编写的库，包含了被广泛使用的`JPEG`解码、`JPEG`编码和其他的`JPEG`功能的实现。`libjpeg-turbo`是一个专门为`x86`和`x86-64`处理器优化的高速`libjpeg`的改进版本。


#编译安装

可以到[libjpeg-turbo-1.5.1](https://nchc.dl.sourceforge.net/project/libjpeg-turbo/1.5.1/libjpeg-turbo-1.5.1.tar.gz)下载源代码。

```
$ tar -xzvf libjpeg-turbo-1.5.1.tar.gz
$ cd libjpeg-turbo-1.5.1
$ ./configure --prefix=your-path
$ make
$ make install
```


#JPEG解码

##分配和初始化一个`JPEG decompression`结构体
```
struct jpeg_decompress_struct cinfo;
jpeg_create_decompress(&cinfo);
```

##指定待解压的源文件
```
infile = fopen(argv[1], "rb");
jpeg_stdio_src(&cinfo, infile);
```

##使用`jpeg_read_header`获得`jpg`信息
```
jpeg_read_header(&cinfo, TRUE);
cinfo.image_width  // jpg图片的宽度
cinfo.image_height   // jpg图片的高度
cinfo.num_components  // 每个图片的像素值由几部分组成，如rgb就是3部分
```

##设置解压参数
```
// scale_num/scale_denom为图像相对于原图的缩放比例
cinfo.scale_num
cinfo.scale_denom
```

##启动解压
```
jpeg_start_decompress(&cinfo);  // 启动jpg解压
```

##循环调用`jpeg_read_scanlines`
```
row_stride = cinfo.output_width * cinfo.output_components;  // 解压后图像的一行的字节长度
buffer = malloc(row_stride);
jpeg_read_scanlines(&cinfo, &buffer, 1);  // 读取图片的一行到buffer中去
```

##释放获取的资源
```
jpeg_finish_decompress(&cinfo);
jpeg_destroy_decompress(&cinfo);
```


#参考链接

[libjpeg使用](http://www.cnblogs.com/CZM-/p/5382865.html)   
[JPEG图像的解压缩操作](http://www.cnblogs.com/hzhida/archive/2012/05/30/2524989.html)
