#include <lodepng.h>
#include <stdio.h>
#include <stdlib.h>

#include <utils.h>

void decodePNG(const char *filename, char *out)
{
    unsigned error;
    unsigned char *image = NULL;
    unsigned width, height;
    unsigned char *png = NULL;
    size_t pngsize;

    error = lodepng_load_file(&png, &pngsize, filename);
    if (!error)
        error = lodepng_decode32(&image, &width, &height, png, pngsize);
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    printf("width: %d, height: %d\n", width, height);

    free(png);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int start = x * width + y * height;
            *(out + start + 0) = *(image + start + 0);
            *(out + start + 1) = *(image + start + 1);
            *(out + start + 2) = *(image + start + 2);
            *(out + start + 3) = *(image + start + 3);
        }
    }

    free(image);
}

int main()
{
    char buff[804 * 1024 * 4];
    decodePNG("/mnt/udisk/1.png", buff);

    int lcdfd = -1;
    char *sc = NULL;
    if ((lcdfd = openLCD(&sc)) < 0)
    {
        return -1;
    }
    printf("%x\n", buff);
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
}