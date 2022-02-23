#include <stdio.h>

/*���� open ������ͷ�ļ� */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*���� write close ������ͷ�ļ� */
#include <unistd.h>

#define LCD_DEVICE	"/dev/fb0"	//---��������ʦȷ��	Ӧ�ÿ�������ʦ������Щ��

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF

int main()
{
	//��lcd��Ļ�����ļ�
	int lcdfd = open(LCD_DEVICE,O_RDWR);
	if(lcdfd < 0)
	{
		printf("open lcdfd failed\n");
		return 0;
	}
	printf("open lcdfd OK\n");
	
	//��lcd��Ļ��ʾ��ɫ----��lcd��Ļ��д����ɫ
	
	int i;
	int color1 = GREEN;
	int color2 = RED;
	int color3 = BLUE;
	
	for(i=0;i<800*480;i++)
	{
		
		write(lcdfd,&color1,4);
	}
	
	
	
	
	//�ر������ļ�������
	close(lcdfd);
	
	return 0;
}