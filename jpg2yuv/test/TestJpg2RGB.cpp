#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jpeglib.h"



int main(int argc, char **argv)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * infile = NULL;
    int  row_stride; 
    unsigned char *buffer = NULL;

    // 分配和初始化一个decompression结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 指定源文件
    if ((infile = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", argv[1]);
        return -1;
    }

    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE); // 用jpeg_read_header获得jpg信息

    // 源信息
    printf("image: width(%d), height(%d)\n", cinfo.image_width, cinfo.image_height);
    printf("num_components = %d\n", cinfo.num_components);

    // 设置解压参数,比如放大、缩小
    // printf("enter M/N: \n");
    // scanf("%d/%d", &cinfo.scale_num, &cinfo.scale_denom);
    // printf("scale to : %d/%d\n", cinfo.scale_num, cinfo.scale_denom);

    // 启动解压
    jpeg_start_decompress(&cinfo);

    /* 输出的图像信息 */
    printf("output: width(%d), height(%d)\n", cinfo.output_width, cinfo.output_height);
    printf("output_components = %d\n", cinfo.output_components);

    //一行的数据长度
    row_stride = cinfo.output_width * cinfo.output_components; 
    buffer = (unsigned char *)malloc(row_stride);
     
    // 循环调用jpeg_read_scanlines一行一行的获得解压数据
    while(cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, &buffer, 1);
        // show
    }
    
    free(buffer);
    buffer = NULL;

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
      
    return 0;
}

