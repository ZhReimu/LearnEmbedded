#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <utils.h>
#include <pngpriv.h>

#define PNG_BYTES_TO_CHECK 4

int main()
{
    FILE *fp_read = fopen("/mnt/udisk/1.png", "rb");

    png_structp png_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop infop_read = png_create_info_struct(png_read);
    png_init_io(png_read, fp_read);

    png_read_png(png_read, infop_read, PNG_TRANSFORM_EXPAND, 0);

    // PNG_COLOR_TYPE_RGB_ALPHA
    int color_type = png_get_color_type(png_read, infop_read);
    printf("color_type:%d\n", color_type);

    int w = png_get_image_width(png_read, infop_read);
    int h = png_get_image_height(png_read, infop_read);
    printf("w:%d, h:%d\n", w, h);

    png_bytep buff = (png_bytep)malloc(h * w * 3 * sizeof(png_byte));
    memset(buff, 0, (h * w * 3 * sizeof(png_byte)));

    png_bytep *row_pointers = png_get_rows(png_read, infop_read);

    switch (color_type)
    {
    case PNG_COLOR_TYPE_RGB_ALPHA:
    {
        int i, j;
        for (i = 0; i < h; i++)
        {
            for (j = 0; j < w; j++)
            {
                buff[i * w + 3 * j + 3] = row_pointers[i][3 * j + 3];
                buff[i * w + 3 * j + 2] = row_pointers[i][3 * j + 2];
                buff[i * w + 3 * j + 1] = row_pointers[i][3 * j + 1];
                buff[i * w + 3 * j + 0] = row_pointers[i][3 * j + 0];
            }
        }
        break;
    }
    default:
        break;
    }

    int lcdfd = -1;
    char *sc = NULL;

    if ((lcdfd = openLCD(&sc)) < 0)
    {
        return -1;
    }

    for (int x = 0; x < 800; x++)
    {
        for (int y = 0; y < 480; y++)
        {
            setBMPColor(sc, buff, x, y);
        }
    }

    //关闭驱动文件描述符
    munmap(sc, BUFF_SIZE);
    //关闭驱动文件描述符
    close(lcdfd);
    return 0;
}