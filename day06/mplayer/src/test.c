#include <myHeader.h>

int main()
{
    char test[1024] = {0};
    stringCat(test, 2, "99999999", "666666666");
    puts(test);
    return 0;
}