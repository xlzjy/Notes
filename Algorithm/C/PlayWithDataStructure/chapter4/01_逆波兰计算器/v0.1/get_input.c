#include "stack.h"

char *s_gets(char *st, int n)
{
    char *ret_val;
    ret_val = fgets(st, n, stdin);
    int i = 0;

    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }

    return ret_val;
}

int get_length(char *st)
{
    return (int) strlen(st);
}

// 获取到中缀表达式,但是还有问题,是字符串的形式
int Input_Array(char *ar, int n)
{
    return get_length(s_gets(ar, n));

}

