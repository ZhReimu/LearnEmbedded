#include <sys/types.h>
#include <sys/stat.h>       
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



int main()
{
	//打开文件
	int fd = open("io.txt",O_RDWR | O_CREAT,0777);
	if(fd == -1)
	{
		//如果打开是否，返回-1并告诉我们打开谁失败，程序异常结束
		printf("open io.txt failed\n");
		return -1;
	}
	printf("open io.txt OK\n");
	
	//写操作
	char write_data[1024];
	
	printf("请输入写入的数据\n");
	
	scanf("%s",write_data);
	
	int wr_ret = write(fd,write_data,strlen(write_data));
	
	printf("成功写入的字节数是:%d\n",wr_ret);
	
	//光标偏移操作
	lseek(fd,0,SEEK_SET);
	
	//读操作
	char read_data[1024];
	
	int re_ret = read(fd,read_data,wr_ret);
	
	printf("读取了%d个字节\n",re_ret);
	printf("读取的内容为:%s\n",read_data);
	
	//关闭
	close(fd);
	
	return 0;
}