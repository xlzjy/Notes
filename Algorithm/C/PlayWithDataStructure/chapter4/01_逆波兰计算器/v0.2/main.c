#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXINPUT 50

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

int multiple(int n)
{
    int temp = 1;
    while (n)
    {
        temp *= 10;
        n--;
    }

    return temp;
}

void JoinInputs(char *src, char *dst)
{
    // 获取到字符串,注意所有的数字与符号都是ASCII
    s_gets(src, MAXINPUT);

    // 标记数字串的开始和结尾
    char *begin = src;
    char *end = src;

    int i;
    int j = 0;
    int count = 0;
    // 获取字符串的长度
    int len = (int) strlen(src);

    for (i = 0; i < len; i++)
    {
        if (src[i] >= '0' && src[i] <= '9')
        {
            if (count == 0) // 如果当前碰到是ASCII数字,且是第一个数字
            {
                *begin = src[i];
                *end = src[i];
            } else // 如果当前碰到的不是第一个数字
            {
                end++;
                *end = src[i];
            }
            count++; // 计数器,是数字就加1
        } else
        {
            // 如果当前碰到是符号,且count不为0
            if (count != 0)
            {
                int temp = 0;
                // 将前面的数字拼起来
                while (count)
                {
                    if (end >= begin)
                    {
                        *begin = *begin - '0';
                        temp += *begin * multiple(count - 1);
                        begin++;
                    } else
                        break;
                    count--;
                }

                // 赋值给dst
                dst[j++] = (char) temp;
            } else // 如果count为0
            {
                dst[j++] = src[i];
            }
        }
    }

}

// 逆波兰
int main(void)
{
    char inputs[MAXINPUT];
    char gets[MAXINPUT];
    JoinInputs(inputs, gets);
    printf("%s", gets);
}

