#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 15 // 存储空间初始分配量

typedef int Status; // status是函数的类型,其值是函数结果状态码,如ok
typedef int ElemType; // ElemType类型根据实际情况而定,这里假设为int
typedef char String[MAXSIZE + 1]; // 0号单元存放串的长度
// 理解: String等同于char[MAXSIZE+1]类型
// String a,即a是char[MAXSIZE+1]类型的元素

// 生成一个其值等于chars的串T
Status StrAssign(String T, char *chars)
{
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);  // 因为chars是用第0个字符开始
        return OK;
    }
}

// 串S存在,由串S复制得串T
Status StrCopy(String T, const String S)
{
    int i;
    for (i = 0; i <= S[0]; i++)  // 一共进行了MAXSIZE+1次
        T[i] = S[i];
    return OK;
}

// 若串S为空,则返回TRUE,否则返回FALSE
Status StrEmpty(const String S)
{
    if (S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

// 初始条件:串S和T存在
// 操作结果:若S>T,则返回值>0;若S=T,则返回值=0,若S<T,则返回值<0
int StrCompare(String S, String T)
{
    int i;

    // 如果两个字符串长度相等,且只有最后一位不相等,返回最后一位的差,可能为正可能为负
    for (i = 1; i <= S[0] && i <= T[0]; i++)
        if (S[i] != T[i])
            return S[i] - T[i];

    // 扫描过了所有位置,如果两个字符串完全相等,那么返回0
    // 两个字符串长度不相等,那么返回正值或者负值
    return S[0] - T[0];
}

// 返回串的元素个数
int StrLength(String S)
{
    return S[0];
}

// 初始条件:串S存在
// 操作结果:将S清为空串
Status ClearString(String S)
{
    S[0] = 0; // 令串长为0
    return OK;
}

// 用T返回S1和S2链接而成的新串.若未截断,则返回TRUE,否则FALSE
Status Concat(String T, const String S1, const String S2)
{
    int i;
    // S1[0]是S1字符串的长度,不包含S1[0]
    if (S1[0] + S2[0] <= MAXSIZE)
    {// 未截断
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = 1; i <= S2[0]; i++)
            T[S1[0] + i] = S2[i];
        T[0] = S1[0] + S2[0];
        return TRUE;
    } else
    {
        // 截断S2,即第二个字符串没法全部复制
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = 1; i <= MAXSIZE - S1[0]; i++)
            T[S1[0] + i] = S2[i];
        T[0] = MAXSIZE;
        return FALSE;
    }
}

// 用Sub返回串S的第pos个字符起长度为len的子串
Status SubString(String Sub, const String S, int pos, int len)
{
    int i;
    // 字串范围越界
    // 1.位置不在1和字符串长度S[0]之间(包含边界)
    // 2.字串长度应该在0到S[0]-pos+1之间(包含边界) len=0即空串,空串也算字串
    // S[0]-pos即pos这个位置之后还有几个元素,并且需要算上pos,因此长度最大等于S[0]-pos+1个
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;

    // pos+i-1即从pos逐个往后
    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;

    return TRUE;
}

// 返回子串T在主串S中第pos个字符之后的位置.若不存在,则函数返回值为0
// 其中,T非空,1<=pos<=StrLength(S)
int Index1(const String S, String T, int pos)
{
    int i = pos;  // i用于主串S中当前位置下标值,若pos不为1,则从pos位置开始匹配
    int j = 1; // j用于子串T中当前位置下标值

    while (i <= S[0] && j <= T[0])
    {
        // 两字母相等则继续
        if (S[i] == T[j])
        {
            i++;
            j++;
        } else
        {
            // 如果此轮两字母不相等,则指针后退重新开始匹配
            /* 1.j是串T当前下标值;i是串S当前下标值
             * 2.指针退回应该退回到pos+1的位置
             * 3.i-j+1即pos的位置,i-j+2即pos+1的位置
             */
            i = i - j + 2; // i退回到上次匹配首位的下一位
            j = 1; // j退回到子串T的首位
        }
    }

    // 循环正确结束后,j应该大于T[0],如果i先遍历完S,那么结果j<=T[0],同样返回0
    if (j > T[0])
        // i当前指向匹配子串的最后一个字母的下一个位置,i-T[0]为匹配字串的第一个字母所在位置
        return i - T[0];
    else
        return 0;   // 循环没有正确结束,即没有匹配到子串
}

// 返回子串T在主串S中第pos个字符之后的位置.若不存在,则函数返回值为0
// 其中,T非空,1<=pos<=StrLength(S)
// Index1的另外一种写法,通过改变pos来定位
int Index2(const String S, const String T, int pos)
{
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        } else
        {
            pos++;
            i = pos;
            j = 1;
        }
    }

    if (j > T[0])
        return pos;
    else
        return 0;
}

// T为非空串.若主串S中第pos个字符之后存在与T相等的字串,
// 则返回第一个这样的子串在S中的位置,否则返回0
int Index3(String S, String T, int pos)
{
    /*
     * 变量n用于保存主串的长度
     * 变量m用与保存需要比较的字符串的长度
     * i用于标注找到的位置
     * sub用于临时存放主串中的子串
     */
    int n, m, i;
    String sub;

    if (pos > 0)
    {
        // 得到主串S的长度
        n = StrLength(S);
        // 得到子串T的长度
        m = StrLength(T);
        // i从第pos个位置开始找
        i = pos;

        // 在长度为n的主串中寻找长度为m的子串,那么从主串第1位开始找,最多需要寻找n-m+1次
        while (i <= n - m + 1)
        {  // 从主串第i个位置,即第pos个位置开始找,至多n-m+1次
            // 取主串中第i个位置长度与T相等的子串给sub
            SubString(sub, S, i, m);
            if (StrCompare(sub, T) != 0) // 如果两串不相等
                i++;
            else // 如果两串相等
                return i;  // 返回i值
        }
    }

    // 若无子串与T相等,返回0
    return 0;
}

// 初始条件:串S和T存在,1<=pos<=StrLength(S)+1
// 操作结果:在串S的第pos个字符之前插入串T.完全插入返回TRUE,部分插入返回FALSE
Status StrInsert(String S, int pos, const String T)
{
    int i;
    // 判断边界,S[S[0]]即串S的最后一个位置元素,S[0]+1即下一个位置,相当于在结尾插入
    if (pos < 1 || pos > S[0] + 1)
        return ERROR;

    // ("bcd",2,"abcfghijk")
    if (S[0] + T[0] <= MAXSIZE)
    {
        // 完全插入,从pos开始空开T[0]个字符,pos+T[0]后,继续将S的剩下字符填充
        // 因此直接从字符串末尾开始逐个往前赋值更合理,相当于S后半段右移T[0]个单位
        // 后半段一共S[0]-pos+1个字符
        for (i = S[0]; i >= pos; i--)
            S[i + T[0]] = S[i];
        for (i = pos; i < T[0] + pos; i++)
            S[i] = T[i - pos + 1];
        S[0] = S[0] + T[0];
        return TRUE;
    } else
    {
        // 部分插入,不影响原先字符串的内容,仅在指定位置插入足够的元素
        int leftSize = MAXSIZE - S[0]; // 剩余可插入的长度
        // 从最后一位开始倒着赋值,直到指定(插入位置+插入元素个数)的位置
        for (i = MAXSIZE; i >= pos + leftSize; i--)
            S[i] = S[i - leftSize];
        for (i = pos; i < pos + leftSize; i++)
            S[i] = T[i - pos + 1];
        S[0] = MAXSIZE;
        return FALSE;
    }
}

// 初始条件:串S存在,1<=pos<=StrLength(S)-len+1
// 操作结果:从串S中删除第pos个字符起长度为len的子串
Status StrDelete(String S, int pos, int len)
{
    // 最后一个条件len>S[0]-pos+1也是错误的,这个条件等价于前面的pos>S[0]-len+1
    if (pos < 1 || pos > S[0] - len + 1 || len < 0 || len > S[0] - len + 1)
        return ERROR;
    // abcdefghij 4 2
    /*
     * pos+len要删除的最后一个元素的下一个元素位序,
     * 从这个位置开始的所有后面元素都向前移动len个位置
     */
    int i;
    for (i = pos + len; i <= S[0]; i++)
        S[i - len] = S[i];

    // 字符串长度减去要删除字符串的长度
    S[0] = S[0] - len;

    return OK;
}

// 初始条件:串S,T和V都存在,T是非空串(此函数与串的存储结构无关)
// 操作结果:用V替换主串S中出现的所有与T相等的不重叠的子串
Status Replace(String S, String T, String V)
{
    // 从串S的第一个字符起查找串T
    int i = 1;
    // T是空串
    if (StrEmpty(T))
        return ERROR;

    do
    {
        // 结果i为从上一个i之后找到的子串T的位置
        i = Index1(S, T, i);
        if (i)
        { // 串S中存在串T
            StrDelete(S, i, StrLength(T)); // 删除该串T
            StrInsert(S, i, V); // 在原串T的位置插入串V
            i += StrLength(V); // 在插入的串V后面继续查找串T
        }
    } while (i);

    return OK;
}

// 输出字符串T
void StrPrint(String T)
{
    int i;
    for (i = 1; i <= T[0]; i++)
        printf("%c", T[i]);
    printf("\n");
}


int main(void)
{
    int i, j;
    Status k;
    char s;
    String t, s1, s2;
    printf("请输入串s1: ");

    k = StrAssign(s1, "abcd");
    if (!k)
    {
        printf("串长超过MAXSIZE(=%d)\n", MAXSIZE);
        exit(0);
    }

    printf("串长为%d 串空否?%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));

    StrCopy(s2, s1);
    printf("拷贝s1生成的串为: ");
    StrPrint(s2);

    printf("请输入串s2: ");
    k = StrAssign(s2, "efghijk");
    if (!k)
    {
        printf("串长超过MAXSIZE(%d)\n", MAXSIZE);
        exit(0);
    }

    i = StrCompare(s1, s2);
    if (i < 0)
        s = '<';
    else if (i == 0)
        s = '=';
    else
        s = '>';
    printf("串s1%c串s2\n", s);

    k = Concat(t, s1, s2);
    printf("串s1连接串s2得到的串t为:");
    StrPrint(t);
    if (k == FALSE)
        printf("串t有截断\n");

    ClearString(s1);
    printf("清空为空串后,串s1为: ");
    StrPrint(s1);
    printf("串长为%d 串空否?%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));

    printf("求串t的子串,请输入子串的起始位置,子串长度: ");
    i = 2;
    j = 3;
    printf("%d, %d\n", i, j);
    k = SubString(s2, t, i, j);
    if (k)
    {
        printf("子串s2为: ");
        StrPrint(s2);
    }

    printf("从串t的第pos个字符起,删除len个字符,请输入pos,len ");
    i = 4;
    j = 2;
    printf("%d, %d\n", i, j);
    StrDelete(t, i, j);
    printf("删除后的串t为: ");
    StrPrint(t);

    // 插入没有溢出的情况
    i = StrLength(s2) / 2 + 1; // 2
    StrInsert(s2, i, t); // ("bcd",2,"abcfghijk")
    printf("在串s2的第%d个字符之前插入串t后,串s2为:\n", i);
    StrPrint(s2);

    // 插入溢出的情况
    String s3;
    k = StrAssign(s3, "abcdefghijklmn");
    StrInsert(s3, 5, "xxx");
    printf("在串s3的第%d个字符之前插入串t后,串s2为:\n", i);
    StrPrint(s3);

    i = Index1(s2, t, 1);
    printf("s2的第%d个字母起和t第一次匹配\n", i);

    SubString(t, s2, 1, 1);
    printf("串t为: ");
    StrPrint(t);

    Concat(s1, t, t);
    printf("串s1为: ");
    StrPrint(s1);

    StrAssign(s2, "aabbcc");
    Replace(s2, t, s1);
    printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
    StrPrint(s2);


    return 0;
}
