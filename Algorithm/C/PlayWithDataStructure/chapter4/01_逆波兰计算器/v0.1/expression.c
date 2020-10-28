#include "stack.h"

/*
 * 用栈实现中缀表达式转后缀表达式:
 * 初始化一个栈,用于保存暂时还不能确定运算符顺序的运算符
 * 从左到右处理各个元素,直到末尾.可能遇到三种情况
 * 1.遇到操作数:直接加入后缀表达式
 * 2.遇到界限符:遇到"("直接入栈;遇到")"则依次弹出栈内运算符并加入后缀表达式,直到弹出"("位置
 * 注意:"("不加入后缀表达式
 * 3.遇到运算符:依次弹出栈中优先级高于或等于当前运算符的所有运算符,并加入后缀表达式,若碰到
 * "("或栈空时则停止.之后再把当前运算符入栈
 *
 * 不改变原先字符串,这里都是值拷贝操作
 */
char expression[15];

char *generate_expression(const char *array, int length)
{
    int j = 0;
    // 初始化一个栈
    SqStack s;
    if (InitStack(&s))
    {
        printf("初始化成功\n");
    } else
    {
        printf("初始化失败\n");
        exit(0);
    }

    for (int i = 0; i < length; i++)
    {
        if (array[i] >= '1' && array[i] <= '9')
            expression[j++] = array[i];
        else
        {
            /*
             * 判断符号,若符号为(,则入栈, 否则为) + - * / ,
             * 分为两种情况,若为空栈,只能是压栈,可能符号为 + - * /, 不可能是)
             * 若不是空栈,分为两种情况,第一种为): 那么弹出元素,直到(
             * 第二种情况是+ - * / 任意一种,需要判断优先级,如果当前符号优先级小于栈顶,
             * 那么栈顶出栈,当前入栈
             */
            if (array[i] == '(')
                Push(&s, array[i]);
            else
            {
                if (StackEmpty(s))
                {
                    if (array[i] == '+' || array[i] == '-' || array[i] == '*'
                        || array[i] == '/')
                        Push(&s, array[i]);
                    else
                    {
                        printf("error: 括号不匹配");
                        exit(0);
                    }
                } else
                {
                    if (array[i] == ')')
                    {
                        char topElem;
                        // 弹出元素
                        while (1)
                        {
                            Pop(&s, &topElem);
                            if (topElem == '(')
                                break;
                            expression[j++] = topElem;
                        }
                    } else
                    {
                        char topElem;
                        GetTop(s, &topElem);
                        if (array[i] == '+' || array[i] == '-')
                        {
                            if (topElem == '*' || topElem == '/')
                            {
                                Pop(&s, &topElem);
                                expression[j++] = topElem;
                                Push(&s, array[i]);
                            } else
                            {
                                Push(&s, array[i]);
                            }
                        } else
                        {
                            Push(&s, array[i]);
                        }
                    }
                }
            }
        }
    }

    while (1)
    {
        char temp;
        // 如果栈空则返回FALSE
        if (!GetTop(s, &temp))
            break;
        else
        {
            // 把剩下的符号都从栈中弹出
            Pop(&s, &temp);
            expression[j++] = temp;
        }
    }
    return expression;
}