#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void cat(char*dst, int arg_cnt,...);

int main(void)
{
    char res[1024] = {0};
    cat(res,4, "123","456","789","666");
    puts("��� :");
    puts(res);
}


//��һ����������ɱ�����ĸ���
void cat(char*dst,int arg_cnt, ...)
{
    va_list p_args;
    va_start(p_args, arg_cnt);
    int idx;
    char* val;
    for(idx = 1; idx <= arg_cnt; ++idx){
        val = va_arg(p_args, char*);
        printf("�� %d ������: %s\n", idx, val);
        strcat(dst, val);
    }
    printf("---------------\n");
    va_end(p_args);
}
