#include "gif_lib.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

GifRecordType gRecordType = UNDEFINED_RECORD_TYPE;
void GifFreeFile(GifFileType *gpGifFile, GifRowType *gpScreenBuffer);
void GifScreenBufferToRgb888(ColorMapObject *ColorMap, uint8_t *inRgb,
                             GifRowType *ScreenBuffer, int32_t ScreenWidth, int32_t ScreenHeight);
void FrameBufferDraw(uint8_t buff[]);
/**
 * @brief 加载 gif 文件
 * 
 * @param gEffectGifFile gif 文件路径
 * @param gpGifFile 
 * @param gpScreenBuffer 
 * @return int32_t 
 */
int32_t loadGifFile(const char *gEffectGifFile, GifFileType *gpGifFile, GifRowType *gpScreenBuffer)
{
    int32_t error = 0;
    int32_t size = 0;
    int32_t idx = 0;
    int32_t ret = 0;
    if (NULL == gEffectGifFile)
    {
        return -1;
    }
    gpGifFile = DGifOpenFileName(gEffectGifFile, &error);
    if (NULL == gpGifFile)
    {
        return -2;
    }
    if ((gpGifFile->SHeight == 0) || (gpGifFile->SWidth == 0))
    {
        return -3;
    }
    gpScreenBuffer = (GifRowType *)malloc(gpGifFile->SHeight * sizeof(GifRowType));
    if (NULL == gpScreenBuffer)
    {
        return -4;
    }
    /* Size in bytes one row */
    size = gpGifFile->SWidth * sizeof(GifPixelType);
    gpScreenBuffer[0] = (GifRowType)malloc(size);
    if (NULL == gpScreenBuffer[0])
    {
        return -5;
    }
    /* Set its color to BackGround */
    for (idx = 0; idx < gpGifFile->SWidth; idx++)
    {
        gpScreenBuffer[0][idx] = gpGifFile->SBackGroundColor;
    }
    /* Allocate the other rows, and set their color to background too */
    for (idx = 1; idx < gpGifFile->SHeight; idx++)
    {
        gpScreenBuffer[idx] = (GifRowType)malloc(size);
        if (NULL == gpScreenBuffer[idx])
        {
            return -6;
        }
        memcpy(gpScreenBuffer[idx], gpScreenBuffer[0], size);
    }
    if (0 > ret)
    {
        GifFreeFile(gpGifFile, gpScreenBuffer);
    }
    return ret;
}

int32_t GifFrameShow(GifFileType *gpGifFile, GifRowType *gpScreenBuffer)
{
    ColorMapObject *colorMap = NULL;
    GifByteType *extension = NULL;

    int32_t InterlacedOffset[] = {0, 4, 2, 1}; // The way Interlaced image should
    int32_t InterlacedJumps[] = {8, 8, 4, 2};  // be read - offsets and jumps...
    uint8_t rgbBuf[240 * 320] = {0};

    int32_t extCode = 0;
    int32_t row = 0;
    int32_t col = 0;
    int32_t width = 0;
    int32_t height = 0;
    int32_t iW = 0;
    int32_t iH = 0;
    int32_t ret = 0;
    puts("Test");
    do
    {
        if (DGifGetRecordType(gpGifFile, &gRecordType) == GIF_ERROR)
        {
            ret = -1;
            break;
        }
        puts("Test");
        switch (gRecordType)
        {
        case IMAGE_DESC_RECORD_TYPE:
            if (DGifGetImageDesc(gpGifFile) == GIF_ERROR)
            {
                ret = -2;
                break;
            }

            row = gpGifFile->Image.Top;
            col = gpGifFile->Image.Left;
            width = gpGifFile->Image.Width;
            height = gpGifFile->Image.Height;

            if (gpGifFile->Image.Interlace)
            {
                for (iH = 0; iH < 4; iH++)
                {
                    for (iW = row + InterlacedOffset[iH]; iW < row + height; iW += InterlacedJumps[iH])
                    {
                        DGifGetLine(gpGifFile, &gpScreenBuffer[iW][col], width);
                    }
                }
            }
            else
            {
                for (iH = 0; iH < height; iH++)
                {
                    DGifGetLine(gpGifFile, &gpScreenBuffer[row++][col], width);
                }
            }
            puts("Test2");
            colorMap = (gpGifFile->Image.ColorMap ? gpGifFile->Image.ColorMap : gpGifFile->SColorMap);
            if (colorMap == NULL)
            {
                ret = -3;
                break;
            }

            GifScreenBufferToRgb888(colorMap, rgbBuf, gpScreenBuffer,
                                    gpGifFile->SWidth, gpGifFile->SHeight);
            FrameBufferDraw(rgbBuf);
            break;

        case EXTENSION_RECORD_TYPE:
            /* Skip any extension blocks in file: */
            if (DGifGetExtension(gpGifFile, &extCode, &extension) == GIF_ERROR)
            {
                ret = -4;
                break;
            }
            puts("Test2");
            while (extension != NULL)
            {
                if (DGifGetExtensionNext(gpGifFile, &extension) == GIF_ERROR)
                {
                    ret = -5;
                    break;
                }
            }
            break;

        case TERMINATE_RECORD_TYPE:
            break;

        default:
            break;
        }

        if (0 < ret)
        {
            break;
        }
        puts("Test3");
    } while (gRecordType != TERMINATE_RECORD_TYPE);

    return ret;
}

void GifScreenBufferToRgb888(ColorMapObject *ColorMap, uint8_t *inRgb,
                             GifRowType *ScreenBuffer, int32_t ScreenWidth, int32_t ScreenHeight)
{
    GifColorType *ColorMapEntry = NULL;
    GifRowType GifRow = NULL;
    uint8_t *rgbBuf = inRgb;
    int32_t idxH = 0;
    int32_t idxW = 0;

    for (idxH = 0; idxH < ScreenHeight; idxH++)
    {
        GifRow = ScreenBuffer[idxH];
        rgbBuf = inRgb + idxH * ScreenWidth * 3;

        for (idxW = 0; idxW < ScreenWidth; idxW++)
        {
            ColorMapEntry = &ColorMap->Colors[GifRow[idxW]];
            *rgbBuf++ = ColorMapEntry->Red;
            *rgbBuf++ = ColorMapEntry->Green;
            *rgbBuf++ = ColorMapEntry->Blue;
        }
    }
}

void GifFreeFile(GifFileType *gpGifFile, GifRowType *gpScreenBuffer)
{
    int32_t idx = 0;
    int32_t error = 0;

    for (idx = 0; idx < gpGifFile->SHeight; idx++)
    {
        if (NULL != gpScreenBuffer[idx])
        {
            free(gpScreenBuffer[idx]);
            gpScreenBuffer[idx] = NULL;
        }
    }

    if (NULL != gpScreenBuffer)
    {
        free(gpScreenBuffer);
        gpScreenBuffer = NULL;
    }

    if (NULL != gpGifFile)
    {
        DGifCloseFile(gpGifFile, &error);
        gpGifFile = NULL;
    }
}

void FrameBufferDraw(uint8_t buff[])
{
    puts("Test");
    printf("%x\n", buff);
}

int main()
{
    const char *gifFile = "./1.gif";
    GifFileType *gpGifFile = NULL;
    GifRowType *gpScreenBuffer = NULL;
    int32_t res = loadGifFile(gifFile, gpGifFile, gpScreenBuffer);
    printf("Load Res -> %d\n", res);
    GifFrameShow(gpGifFile, gpScreenBuffer);
    GifFreeFile(gpGifFile, gpScreenBuffer);
    return 0;
}