@echo off

:: ffmpeg -i 1.mp4 -vf select='eq(pict_type\,I)' -vsync vfr -f image2 keyframe-%02d.bmp

for %%i in (*.bmp) do ffmpeg -i %%i -vf "hflip, transpose=2" %%i1.bmp

:: move *bmp1.bmp 1