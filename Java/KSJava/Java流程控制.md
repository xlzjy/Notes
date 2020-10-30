# Java流程控制

## Scanner对象

`java.util.Scanner`是`Java5`的新特征，我们可以通过`Scanner`类来获取用户的输入。

### 基础语法

```java
Scanner s = new Scanner(System.in);
```

通过`Scanner`类的`next()`与`nextLine()`方法获取输入的字符串，在读取前我们一般需要使用`hasNext()`与`hasNextLine()`判断是否还有输入的数据。

##### `next():`

1. 一定要读取到有效字符后才可以结束输入；
2. 对输入有效字符之前遇到的空白，`next()`方法会自动将其去掉；
3. 只要输入有效字符后才将其后面输入的空白作为分隔符或者结束符；
4. `next()`**不能得到带有空格的字符串。**

##### `nextLine():`

1. 以Enter为结束符，即`nextLine()`方法返回的是输入回车之前的所有字符；
2. 可以获得空白。

```java
import java.util.Scanner;

public class Demo01 {
    public static void main(String[] args) {
        //创建一个扫描器对象，用于接收键盘数据
        Scanner scanner = new Scanner(System.in);
        System.out.println("使用next方式接受: ");

        //判断用户有没有有没有输入字符串
        if (scanner.hasNext()) {
            //使用next方式接受
            String str = scanner.next(); //程序会等待用户输入
            System.out.println("输出的内容为: " + str);
        }

        // !!! 凡是属于IO流的类如果不关闭会一直占用资源，要养成好习惯用完就关掉
        scanner.close();
    }
}
// input:  hello world
// output: hello
```

```java
import java.util.Scanner;

public class Demo02 {
    public static void main(String[] args) {
        // 从键盘接受数据
        Scanner scanner = new Scanner(System.in);
        System.out.println("使用nextLine方式接收:");

        // 判断是否还有输入
        if (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            System.out.println("输出的内容为: " + str);
        }

        scanner.close();
    }
}
// input:  hello world
// output: hello world
```



## 顺序结构

程序一句一句执行，**他是任何一个算法都离不开的基本算法结构**。

```java
public class Sequence {
    public static void main(String[] args) {
        System.out.println("1");
        System.out.println("2");
        System.out.println("3");
        System.out.println("4");
        System.out.println("5");
    }
}
```



## 选择结构

- if单选择结构
- if双选择结构
- if多选择结构
- 嵌套的if结构
- switch多选择结构

**if选择结构**

`if`语句至多有1个`else`语句，`else`语句在所有的`else if`语句之后，`if`语句可以有若干个`else if`语句，他们必须在`else`语句之前。一旦其中一个`else if`语句检测为`true`，其他的`else if`以及`else`语句都将跳过执行。

**switch多选择结构**

- `switch case`语句判断一个变量与一系列值中某个值是否相等，每个值称为一个分支。
- `switch`语句中的变量类型可以是：
  - `byte`、`short`、`int`或`char`;
  - 从`Java SE 7`开始，`switch`支持字符串`String`类型
  - 同时`case`标签必须为字符串常量或字面量

```java
switch(expression){
    case value1:
    	//语句
    	break;//可选
    case value2:
    	break;
    default://可选
    	//语句
}
```

```java
public class SwitchDemo01 {
    public static void main(String[] args) {
        char grade = 'C';

        // 不写break会有case穿透
        switch (grade) {
            case 'A':
                System.out.println("优秀");
                break;
            case 'B':
                System.out.println("良好");
            case 'C':
                System.out.println("及格");
            case 'D':
                System.out.println("再接再厉");
                break;
            case 'E':
                System.out.println("挂科");
                break;
            default:
                System.out.println("没有此等级");
        }
    }
}
```

```java
public class SwitchDemo02 {
    public static void main(String[] args) {
        String name = "oddlife";

        //JDK7的新特性，表达式结果可以使字符串!!
        //字符的本质还是数字
        // 反编译 java---class (字节码文件) --- 反编译(IDEA)

        switch (name) {
            case "helloworld":
                System.out.println("helloworld");
                break;
            case "oddlife":
                System.out.println("oddlife");
                break;
            default:
                System.out.println("没有");
        }
    }
}
```



## 循环结构

### while循环

- `while`是最基本的循环，它的结构为：

```java
while(布尔表达式){
    //循环内容
}
```

- 只要布尔表达式为`true`，循环就会一直执行下去；
- <u>**我们大多数情况是会让循环停止下来的，我们需要一个表达式失效的方式来结束循环**</u>；
- 少部分情况需要循环一直执行，比如服务器的请求响应监听等；
- 循环条件一直为`true`就会造成无限循环（死循环），我们正常的业务编程中应该尽量避免死循环。会影响程序性能或者造成程序卡死崩溃！

### do...while循环

- 对于`while`语句而言，如果不满足条件，则不能进入循环，但有时候我们需要即使不满足条件，也至少执行一次；
- `do...while`循环和`while`循环相似，不同的是，`do...while`循环至少会执行一次；

```java
do {
    //代码语句
} while(布尔表达式);
```

- `while`和`do-while`的区别:
  - `while`先判断后执行。`do...while`是先执行后判断！
  - `do...while`总是保证循环体会被至少执行一次！这是他们的主要差别。

### for循环

- 虽然所有循环结构都可以用`while`或者`do...while`表示，但`Java`提供了另一种语句——`for`循环，使一些循环结构变得更加简单；
- `for`循环语句是支持迭代的一种通用结构，是最有效、最灵活的循环结构；
- `for`循环执行的次数是在执行前就确定的。语法格式如下：

```java
for (初始化;布尔表达式;更新){
    //代码语句
}
```

- `for`循环最先执行初始化步骤。可以声明一种类型，但可初始化一个或多个循环控制变量，也可以是空语句。然后，检查布尔表达式的值。如果为`true`，循环体被执行。如果为`false`，循环终止，开始执行循环体后面的语句。执行一次循环后，更新循环控制变量（迭代因子控制循环变量的增减）。再次检测布尔表达式，循环执行上面的过程。

```java
for (;;) {
    // for版死循环
}
```

```java
//练习1：计算0到100之间的奇数和偶数的和
public class ForDemo01 {
    public static void main(String[] args){
        int oddSum = 0;
        int evenSum = 0;
        
        for (int i = 0; i <= 100; i++){
            if (i%2 == 0){
                evenSum += i;
            } else {
                oddSum += i;
            }
        }
        System.out.println("偶数的和：" + evenSum);
        System.out.println("奇数的和：" + oddSum);
    }
}
```

```java
//练习2：用while或for循环输出1-1000之间能被5整除的数，并且每行输出3个
public class ForDemo02 {
    public static void main(String[] args) {
        for (int i = 0; i <= 1000; i++) {
            if (i % 5 == 0) {
                System.out.print(i + "\t");
            }
            if (i % (5*3) == 0) {
                System.out.println();
            }
        }
    }
}
```

```java
//练习3：打印九九乘法表
public class ForDemo03 {
    public static void main(String[] args) {
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print(i + " * " + j + " = " + i * j + '\t');
            }
            System.out.println();
        }
    }
}
```

### 增强for循环

- `Java5`引入了一种主要用于数组或集合的增强型for循环；
- 语法格式如下

```java
for (声明语句 : 表达式)
{
	//代码
}
```

- 声明语句：声明新的局部变量，该变量的类型必须和数组元素的类型匹配。其作用域限定在循环语句块，其值与此事数组元素的值相等；
- 表达式：表达式是要访问的数组名，或者是返回值为数组的方法。

```java
public class ForDemo03 {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50}; //定义了一个数组

        //遍历数组的元素
        for (int x : numbers) {
            System.out.println(x);
        }

        System.out.println("============");
        
        //等价于
        for (int i = 0; i < 5; i++) {
            System.out.println(numbers[i]);
        }
    }
}
```



### break和continue以及goto

- `break`在任何循环语句的主体部分，均可用`break`控制循环的流程。`break`**用于强行退出循环**，不执行循环中剩余的语句。（`break`语句也在`switch`语句中使用）
- `continue`语句用在循环语句体中，**用于终止某次循环过程**，即跳过循环体中尚未执行的语句，接着进行下一次是否执行循环的判定。
- 关于`goto`关键字
  - ​	`goto`关键字很早就在程序设计语言中出现。尽管`goto`仍是`Java`的一个保留字，但并未在语言中得到正式使用；`Java`没有`goto`。然而，在`break`和`continue`这两个关键字的身上，我们仍然看出一些`goto`的影子---带标签的`break`和`continue`。
  - "标签"是指后面跟一个冒号的标识符，例如：`label:`
  - 对`Java`来说唯一用到标签的地方是在循环语句之前。而在循环之前设置标签的唯一理由是：我们希望在其中嵌套另一个循环，由于`break`和`continue`关键字通常只中断当前循环，但若随同标签使用，它们就会终端到存在标签的地方。

```java
// Label的使用，尽量不要用
public class LabelDemo {
    public static void main(String[] args) {
        //打印101-150之间所有的质数

        int count = 0;

        outer:
        for (int i = 101; i < 150; i++) {
            for (int j = 2; j < i / 2; j++) {
                if (i % j == 0) {
                    System.out.println(i + "不是质数");
                    continue outer;
                }
            }
            System.out.println(i + " ");
        }
    }
}
```

```java
/*
打印三角形 10行
                 *|
                **|*
               ***|**
              ****|***
             *****|****
            ******|*****
           *******|******
          ********|*******
         *********|********
        **********|*********
思路:将三角形分成左右两部分打印, |将三角形分为两部分
 */
public class TestDemo {
    public static void main(String[] args) {
        int i, j;
        for (i = 1; i <= 10; i++) { //i用来打印行
            //打印左倒三角空白符
            for (j = 10; j > i; j--) {
                System.out.print(" ");
            }
            //打印左半三角
            for (j = 1; j <= i; j++)
                System.out.print("#");

            //打印右半三角
            for (j = 1; j < i; j++)
                System.out.print("#");
            System.out.println();
        }
    }
}
```

