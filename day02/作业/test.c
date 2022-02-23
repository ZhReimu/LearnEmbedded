#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    //打开文件
    int fd = open("1.txt", O_RDWR | O_CREAT, 0777);
    int fd2 = open("2.txt", O_RDWR | O_CREAT, 0777);
    int fd3 = open("3.txt", O_RDWR | O_CREAT | O_APPEND, 0777);

    const char hello[] = "Hello";
    const char world[] = "World";

    if (fd == -1 || fd2 == -1 || fd3 == -1)
    {
        //如果打开是否，返回-1并告诉我们打开谁失败，程序异常结束
        printf("open txt failed\n");
        return -1;
    }
    printf("open txt OK\n");

    write(fd, hello, strlen(hello) + 1);
    write(fd2, world, strlen(world) + 1);

    //光标偏移操作
    lseek(fd, 0, SEEK_SET);
    lseek(fd2, 0, SEEK_SET);

    //读操作
    char temp[1024];

    read(fd, temp, sizeof(hello));

    write(fd3, temp, strlen(temp) + 1);

    read(fd2, temp, sizeof(world));
    write(fd3, temp, strlen(temp) + 1);
    //关闭
    close(fd);
    close(fd2);
    close(fd3);

    return 0;
}