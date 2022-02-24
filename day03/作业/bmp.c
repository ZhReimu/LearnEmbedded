#include <stdio.h>

/*���� open ������ͷ�ļ� */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*���� write close ������ͷ�ļ� */
#include <unistd.h>

#include <sys/mman.h>

#define LCD_DEVICE	"/dev/fb0"	//---��������ʦȷ��	Ӧ�ÿ�������ʦ������Щ��

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF

/*
1.��LCD����
2.��ͼƬ����ȡ��ɫ����
3.�������⹲���ڴ�
4.24λbmpͼƬת����32λ��LCD����
5.ת��������ݷŵ������ڴ�
6.�ر�������ͼƬ���ͷ��ڴ�
*/

int main()
{
	//��lcd��Ļ�����ļ�
	int LCD_fd = open(LCD_DEVICE,O_RDWR);
	if(LCD_fd < 0)
	{
		printf("open lcdfd failed\n");
		return 0;
	}
	printf("open lcdfd OK\n");
	
	//��ͼƬ
	int BMP_fd = open("1.bmp",O_RDWR);
	if(BMP_fd < 0)
	{
		printf("open bmp failed\n");
		return -1;
	}
	printf("open bmp OK\n");
	
	//�������⹲���ڴ�
	char *share_addr = NULL;
	
	share_addr = mmap(NULL,//��ϵͳ����
					  800*480*4,//,����Ŀռ��С
					  PROT_READ | PROT_WRITE,//�ڴ�ռ��ʹ��Ȩ��
					  MAP_SHARED,//�ڴ��ʹ������
					  LCD_fd,
					  0
						);

	//��bmpͼƬ24λ��ɫ���ݶ�ȡ����
	char BMP_24bit[800*480*3] = {};

	//ƫ��54���ֽ�ͷ��Ϣ
	lseek(BMP_fd,54,SEEK_SET);
	
	int read_ret = read(BMP_fd,BMP_24bit,800*480*3);
	if(read_ret < 0)
	{
		printf("read bmp failed\n");
		return -1;
	}
	printf("read bmp OK\n");
	
	int x,y;
	for(x = 0; x < 480; x++)
	{
		for(y = 0; y < 800; y++)
		{
			share_addr[0+4*x+4*800*y] = BMP_24bit[0+3*x+800*3*y];
			share_addr[1+4*x+4*800*y] = BMP_24bit[1+3*x+800*3*y];
			share_addr[2+4*x+4*800*y] = BMP_24bit[2+3*x+800*3*y];
			share_addr[3+4*x+4*800*y] =0;
		}		
	}

	//�ر������ļ�������
	munmap(share_addr,800*480*4);
	close(BMP_fd);
	close(LCD_fd);
	
	return 0;
}