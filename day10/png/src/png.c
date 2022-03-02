#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <utils.h>
#include <pngpriv.h>

#define PNG_BYTES_TO_CHECK 4

/*
fun:    读取文件名为filepath的png文件
return: png_bytep类型的buff,即数据域
arg[0]: filepath,文件名
arg[1]: width,图像宽度
arg[2]: height,图像高度
*/
png_bytep load_png_image(const char *filepath, char *dst, int *width, int *height)
{
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep *row_pointers;
    char buf[PNG_BYTES_TO_CHECK];
    int w, h, x, y, temp, color_type;

    fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        printf("load_png_image err:fp == NULL");
        return 0;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    info_ptr = png_create_info_struct(png_ptr);

    setjmp(png_jmpbuf(png_ptr));
    /* 读取PNG_BYTES_TO_CHECK个字节的数据 */
    temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
    /* 若读到的数据并没有PNG_BYTES_TO_CHECK个字节 */
    if (temp < PNG_BYTES_TO_CHECK)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        printf("load_png_image err:读到的数据并没有PNG_BYTES_TO_CHECK个字节");
        return 0;
    }
    /* 检测数据是否为PNG的签名 */
    temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
    /* 如果不是PNG的签名，则说明该文件不是PNG文件 */
    if (temp != 0)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        printf("load_png_image err:不是PNG的签名");
        return 0;
    }

    /* 复位文件指针 */
    rewind(fp);
    /* 开始读文件 */
    png_init_io(png_ptr, fp);
    /* 读取PNG图片信息和像素数据 */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    /* 获取图像的色彩类型 */
    color_type = png_get_color_type(png_ptr, info_ptr);

    /* 获取图像的宽高 */
    w = png_get_image_width(png_ptr, info_ptr);
    h = png_get_image_height(png_ptr, info_ptr);
    *width = w;
    *height = h;

    /* 分配空间buff,保存像素数据 */
    png_bytep buff = (png_bytep)malloc(h * w * 3 * sizeof(png_byte));
    memset(buff, 0, (h * w * 3 * sizeof(png_byte)));

    /* 获取图像的所有行像素数据，row_pointers里边就是rgba数据 */
    row_pointers = png_get_rows(png_ptr, info_ptr);
    /* 根据不同的色彩类型进行相应处理 */
    switch (color_type)
    {
    case PNG_COLOR_TYPE_RGB_ALPHA:
        puts("RGBA");
        for (y = 0; y < h; ++y)
        {
            for (x = 0; x < w * 4;)
            {
                ///* TODO 以下是RGBA数据，需要自己补充代码，保存RGBA数据 */
                dst[y * x] = row_pointers[y][x++]; // red
                dst[y * x] = row_pointers[y][x++]; // green
                dst[y * x] = row_pointers[y][x++]; // blue
                dst[y * x] = row_pointers[y][x++]; // alpha
            }
        }
        puts("RGBA END");
        break;
    case PNG_COLOR_TYPE_RGB:
        for (y = 0; y < h; y++)
        {
            for (x = 0; x < w; x++)
            {
                buff[y * w + 3 * x + 0] = row_pointers[y][3 * x + 0];
                buff[y * w + 3 * x + 1] = row_pointers[y][3 * x + 1];
                buff[y * w + 3 * x + 2] = row_pointers[y][3 * x + 2];
            }
        }
        break;
        /* 其它色彩类型的图像就不读了 */
    default:
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        printf("default color_type:close\n");
        return 0;
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    return buff;
}

int main()
{
    char *path = "/mnt/udisk/1.png";
    int width = 0;
    int height = 0;
    char dst[804 * 1024 * 4] = {0};
    png_bytep buff = load_png_image(path, dst, &width, &height);
    if (!buff)
    {
        printf("load_png_image(filepath) erro");
    }
    printf("width:%d, height:%d\n", width, height);

    int lcdfd = -1;
    char *buffer = NULL;

    if ((lcdfd = openLCD(&buffer)) < 0)
    {
        return -1;
    }
    int x, y;
    // 特效 1
    for (y = 0; y < 480; y++)
    {
        for (x = 0; x < 800; x++)
        {
            setBMPColor(buffer, dst, x, y);
        }
        usleep(10);
    }
    //关闭驱动文件描述符
    munmap(buff, BUFF_SIZE);
    //关闭驱动文件描述符
    close(lcdfd);

    return 0;
}