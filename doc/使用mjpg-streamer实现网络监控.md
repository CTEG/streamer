#启动`Camera`

```
$ sudo raspi-config
```
通过`raspi-config`工具更新了操作并使能摄像头之后，它会告诉树莓派摄像头已经连接成功，并增加了`raspistill`、`raspivid`两个命令行工具以供用户使用摄像头，这两个命令可分别让你拍摄静帧照片和`HD`视频。


#安装依赖库

```
$ sudo apt-get install libv4l-dev
$ sudo apt-get install libjpeg62-turbo-dev
$ sudo apt-get install libjpeg8-dev
```


#下载、编译、安装`mjpg-streamer`

```
$ wget https://codeload.github.com/jacksonliam/mjpg-streamer/zip/master -O mjpg-streamer.zip
```

或者直接到网站下载`zip`安装包`mjpg-streamer-master.zip`，使用`unzip mjpg-streamer-master.zip`解压。

安装`cmake`：
```
$ sudo apt-get install cmake
```

切换到`mjpg`的路径下：
```
$ cd  mjpg-streamer-master/mjpg-streamer-experimental
$ sudo make clean all
$ sudo make install
```

#开启`mjpg-streamer`

```
$ LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "input_uvc.so" -o "output_http.so -w /usr/local/share/mjpg-streamer/www"
```

或者

```
$ LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "./input_uvc.so -d /dev/video0 -r 320*240 -f 12" -o "./output_http.so –p 8090 –w  /usr/local/share/mjpg-streamer/www"
```

`-r`后是分辨率参数；`-f`后面是帧率；`-p`后面是端口号；`-w`后面是`web`服务目录。也可以将`export LD_LIBRARY_PATH=/opt/mjpg-streamer/`添加到`path`路径。在浏览器输入`http://127.0.0.1:8080`，就可以打开监控界面了。

如果是自带的摄像头，那么`-i`使用`input_raspicam.so`参数。