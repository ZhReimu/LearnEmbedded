#include <bmp.h>

//映射内存首地址
int *lcdmem = NULL;

//初始化函数
//lcd屏幕初始化
int lcd_init(struct lcd_info *lcdinfo)
{
    //1.打开lcd屏幕
    lcdinfo->fd = open(LCD_DEVICE, O_RDWR);
    if (lcdinfo->fd == -1)
    {
        debug("open lcd failed", ERROR);
        return -1;
    }
    debug("open lcd OK", DEBUG);

    //获取lcd屏幕信息
    struct fb_var_screeninfo lcdvar;

    ioctl(lcdinfo->fd, FBIOGET_VSCREENINFO, &lcdvar);

    debugD("lcd Width = %d", lcdvar.xres, DEBUG);
    debugD("lcd Height = %d", lcdvar.yres, DEBUG);
    debugD("lcd Bit = %d", lcdvar.bits_per_pixel, DEBUG);

    lcdinfo->width = lcdvar.xres;
    lcdinfo->high = lcdvar.yres;
    lcdinfo->bits_per = lcdvar.bits_per_pixel;

    //申请内存映射
    lcdmem = mmap(
        NULL,
        lcdinfo->width * lcdinfo->high * lcdinfo->bits_per / 8,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        lcdinfo->fd,
        0);
    if (lcdmem == MAP_FAILED)
    {
        debug("mmap lcd failed", ERROR);
        return -1;
    }
}

/**
 * @brief 在显示器上显示 bmp
 * 
 * @param pathname bmp 文件路径
 * @param x_begin 要显示图片的左上角
 * @param y_begin 亚农显示图片的右上角
 * @param lcdinfo lcd 信息
 * @param isTransport 是否透明
 */
void show_bmp(const char *pathname, int x_begin, int y_begin, struct lcd_info *lcdinfo, int isTransport)
{
    int bmp_width;
    int bmp_high;
    int bmp_bit;

    FILE *fp = fopen(pathname, "r");
    if (fp == NULL)
    {
        debug("fopen bmp failed", ERROR);
        return;
    }

    //读取头文件信息
    struct bmphead bmphead_buf;
    fread(&bmphead_buf, 54, 1, fp);

    debugD("Pic Width: %d\n", bmphead_buf.Width, DEBUG);
    debugD("Pic Height: %d\n", bmphead_buf.Height, DEBUG);
    debugD("Pic Bit: %d\n", bmphead_buf.biBitCount, DEBUG);

    bmp_width = bmphead_buf.Width;
    bmp_high = bmphead_buf.Height;
    bmp_bit = bmphead_buf.biBitCount;

    //设置bmp图片颜色的缓冲区
    char *bmpbuf = malloc(bmp_width * bmp_high * bmp_bit / 8);
    if (bmpbuf == NULL)
    {
        debug("malloc bmpbuf failed", ERROR);
        exit(-1);
    }
    debug("malloc bmpbuf OK", DEBUG);
    //先计算是否有4字节补齐，如果有，求出补齐了多少个字节
    int add_size = (4 - (bmp_width * bmp_bit / 8) % 4) % 4;

    //每次读取一行数据的时候就要偏移add_size个字节，循环次数，就是图片的高度
    int i;
    for (i = 0; i < bmp_high; i++)
    {
        //每次读取的时候，保存到bmpbuf缓冲区的位置应该进行偏移
        fread(bmpbuf + (bmp_width * bmp_bit / 8) * i, bmp_width * bmp_bit / 8, 1, fp);
        fseek(fp, add_size, SEEK_CUR);
    }

    //以字节对齐的方式，将RGB颜色换成ARGB的颜色数据
    int *bmpARGB = malloc(bmp_high * bmp_width * 4);
    if (bmpARGB == NULL)
    {
        debug("malloc bmpARGB failed", ERROR);
        exit(-1);
    }
    debug("malloc bmpARGB OK", DEBUG);
    for (i = 0; i < bmp_width * bmp_high; i++)
    {
        // 				R						G							B
        int rgb = bmpbuf[3 * i + 2] << 16 | bmpbuf[3 * i + 1] << 8 | bmpbuf[3 * i];
        bmpARGB[i] = rgb;
    }
    debug(" << OK", DEBUG);
    int x, y;
    for (x = 0; x + x_begin < lcdinfo->width && x < bmp_width; x++)
    {
        for (y = 0; y + y_begin < lcdinfo->high && y < bmp_high; y++)
        {
            //对于x=0和y=0的坐标而言，lcd屏幕已经偏移了
            int lcd_offset = x + x_begin + lcdinfo->width * (y + y_begin);
            int bmp_offset = x + bmp_width * (bmp_high - y - 1);
            if (bmpARGB[bmp_offset] == 0x00FFFFFF && isTransport)
            {
                continue;
            }
            *(lcdmem + lcd_offset) = bmpARGB[bmp_offset];
        }
    }

    free(bmpbuf);
    free(bmpARGB);

    fclose(fp);
}

//销毁函数
void lcd_exit(struct lcd_info *lcdinfo)
{
    //释放了映射内存
    munmap(lcdmem, lcdinfo->width * lcdinfo->high * lcdinfo->bits_per / 8);
    lcdmem = NULL;
    //关闭屏幕
    close(lcdinfo->fd);

    //释放lcd结构体的堆空间
    free(lcdinfo);
}
/**
 * @brief 在指定位置显示一个 bmp 图片
 * 
 * @param fileName 要显示的 bmp 文件路径
 * @param x 显示坐标 x
 * @param y 显示坐标 y
 * @param isTransport 是否透明
 */
void showBMP(const char *fileName, int x, int y, int isTransport)
{
    // 创建一个屏幕信息结构体指针
    struct lcd_info *lcdinfo = NULL;
    lcdinfo = malloc(sizeof(struct lcd_info));
    if (lcdinfo == NULL)
    {
        debug("malloc struct lcd_info failed", ERROR);
        return;
    }
    if (lcdmem == NULL)
    {
        lcd_init(lcdinfo);
    }
    show_bmp(fileName, x, y, lcdinfo, isTransport);
    debugS("Showing Pic -> %s", fileName, DEBUG);
    lcd_exit(lcdinfo);
}
/**
 * @brief 在 0,0 的位置 显示一个 非透明的图片
 * 
 * @param fileName 图片文件名
 */
void showBMPOO(const char *fileName)
{
    showBMP(fileName, 0, 0, 0);
}