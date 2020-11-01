# Java方法

## 什么是方法？

- `System.out.println()`，其中`System`为类，`out`为对象，`println()`为方法；
- `Java`方法是语句的集合，它们在一起执行一个功能；
  - 方法是解决一类问题的步骤的有序组合
  - 方法包含于类或对象中
  - 方法在程序中被创建，在其他地方被引用

- 设计方法的原则：方法的本意是功能块，就是实现某个功能的语句块的集合。我们设计方法的时候，最好保持方法的原子性，***就是一个方法只完成 1 个功能，这样有利于我们后期的发展***。

```java
public class Demo01 {
    //main方法
    public static void main(String[] args) {
        int sum = add(20, 30);
        System.out.println(sum);
    }

    //加法方法
    public static int add(int a, int b) {
        return a + b;
    }
}
```



## 方法的定义

- `Java`的方法类似于其他语言的函数，是一段**用来完成特定功能的代码片段**，一般情况下，定义一个方法包含以下语法：
- **方法包含一个方法头和一个方法体**。下面是一个方法的所有部分：
  - **修饰符**：这是可选的，告诉编译器如何调用该方法。定义了该方法的访问类型；
  - **返回值类型**：方法可能会返回值。`returnValueType`是方法返回值的数据类型。有些方法执行所需的操作，但没有返回值。在这种情况下，`returnValueType`是关键字`void`；
  - **方法名**：是方法的实际名称，方法名和参数表共同构成方法签名；
  - **参数类型**：参数像是一个占位符。当方法被调用时，传递值给参数。这个值被称为实参或变量。参数列表是指方法的参数类型、顺序和参数的个数。参数是可选的，方法可以不包含任何参数；
    - **形式参数**：在方法被调用时用于接受外界输入的数据；
    - **实际参数**：调用方法时实际传给方法的数据；
  - **方法体**：方法体包含具体的语句，定义该方法的功能。

```java
修饰符 返回值类型 方法名 (参数类型 参数名) {
	...
	方法体
	...
	return 返回值;
}
```



## 方法的调用

- **调用方法**：对象名.方法名（实参列表）
- `Java`支持两种调用方法的方式，根据方法是否返回值来选择。
- 当方法返回一个值得时候，方法调用通常被当做一个值。例如：`int larger = max(30, 40);`

- 如果方法返回值是`void`，方法调用一定是一条语句：`System.out.println("Hello");`
- ***了解值传递（`Java`是值传递）和引用传递！！！***



## 方法的重载

- 重载就是在一个类中，有相同的函数名称，但形参不同的函数；
- **方法的重载规则**：
  - 方法名称必须相同；
  - 参数列表必须不同（个数不同、或类型不同、参数排列顺序不同等）；
  - 方法的返回类型可以相同也可以不相同；
  - 仅仅返回类型不同不足以成为方法的重载。
  - 被重载的方法可以改变访问修饰符；
  - 被重载的方法可以声明新的或更广的检查异常；
  - 方法能够在同一个类中或者在一个子类中被重载。
  - 无法以返回值类型作为重载函数的区分标准。
- **实现理论**：
  - 方法名称相同时，编译器会根据调用方法的参数个数、参数类型等去逐个匹配，以选择对应的方法，如果匹配失败，则编译器报错。

```java
public class Demo02 {
    public static void main(String[] args) {
        double max = max(10.0, 20.0);
        System.out.println(max);
    }

    //比大小
    public static int max(int num1, int num2) {
        if (num1 == num2) {
            System.out.println("num1==num2");
            return 0; //终止方法
        }
        if (num1 > num2) {
            return num1;
        }
        return num2;
    }

    //比大小,方法的重载
    public static double max(double num1, double num2) {
        if (num1 == num2) {
            System.out.println("num1==num2");
            return 0; //终止方法
        }
        if (num1 > num2) {
            return num1;
        }
        return num2;
    }
}
```



## 命令行传参

- 有时候希望运行一个程序时再传递给它消息。这要靠传递命令行参数给`main()`函数实现

```java
/*
命令行使用方法:
需要到src路径下使用javac编译,使用java运行
命令行输入：java Demo03.class hello world
结果：
    3 hello world
    args[0]:hello
    args[1]:world

 */
public class Demo03 {
    public static void main(String[] args) {
        //args.Length数组长度
        for (int i = 0; i < args.length; i++) {
            System.out.println("args[" + i + "]:" + args[i]);
        }
    }
}

```



## 可变参数

- `JDK 1.5`开始，`Java`支持传递同类型的可变参数给一个方法；
- 在方法声明中，在指定参数类型后加一个省略号（...）；
- 一个方法中只能指定一个可变参数，它必须是方法的最后一个参数，任何普通的函数必须在它之前声明。

```java
public class Demo04 {
    public static void main(String[] args) {
        //调用可变参数的方法
        printMax(34, 3, 5, 21, 4.4);
        printMax(new double[]{1.2, 2.3, 0.4, 1.6});
    }

    public static void printMax(double... numbers) {
        if (numbers.length == 0) {
            System.out.println("No argument passwd");
            return;
        }

        double result = numbers[0];

        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] > result) {
                result = numbers[i];
            }
        }
        System.out.println("The max value is " + result);
    }
}
```



## 递归

- **递归就是A方法调用A方法，自己调用自己**
- 利用递归可以用简单的程序来解决一些复杂的问题。它通常把一个大型复杂的问题层层转化为一个与原问题相似的规模较小的问题来求解，递归策略只需少量的程序就可描述出解题过程所需要的多次重复计算，大大地减少了程序的代码量。递归的能力在于用有限的语句来定义对象的无限集合。
- **递归结构包括两个部分：**
  - **递归头**：什么时候不调用自身方法。如果没有头，将陷入死循环。
  - **递归体**：什么时候需要调用自身方法。

>栈溢出（StackOverflowError）：避免爆栈（内存不够用）
>
>```java
>public class StackOverflow {
>    public static void main(String[] args) {
>        StackOverflow stack = new StackOverflow();
>        stack.test();
>	}
>    
>    public void test() {
>        test(); //无休止的调用自己，直到内存栈不够用
>    }
>}
>
>```

```java
public class Demo05 {
    public static void main(String[] args) {
        System.out.println(f(6));
    }

    //递归调用
    //1! = 1
    //2! = 2*1
    //3! = 3*2*1
    //4! = 4*3*2*1
    public static int f(int n) {
        if (n == 1)//基线条件
            return 1;
        else//递归条件(n>1)
            return n * f(n - 1);
    }
}
```

