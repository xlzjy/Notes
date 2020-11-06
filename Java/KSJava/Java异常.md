# 异常

## 什么是异常？

- 实际工作中，遇到的情况不可能是非常完美的。比如：你写的某个模块，用户输入不一定符合你的要求、你的程序要打开某个文件，这个文件可能不存在或者文件格式不对，你要读取数据库的数据，数据可能是空的等、程序跑着跑着，内存或硬盘就满了等。
- 软件程序在运行过程中，非常可能遇到刚刚提到的这些异常问题，称之为异常，英文：`Exception`；
- 我们需要让程序作出合理的处理，而不至于让程序崩溃；
- 异常指程序运行中出现的不期而至的各种情况，如：文件找不到、网络连接失败、非法参数等；
- 异常发生在程序运行期间，它影响了正常的程序执行流程；

## 简单分类

- **<u>要理解Java异常处理是如何工作的，需要掌握以下三种类型的异常：</u>**
  - **检查性异常：**最具代表的检查性异常是用户错误或问题引起的异常，这是程序员无法预见的。例如要打开一个不存在的文件时，一个异常就发生了，这些异常在编译时不能被简单的忽略；
  - **运行时异常：**运行时异常是可能被程序眼避免的异常。与检查性异常相反，运行时异常可以在编译时被忽略；
  - **错误ERROR：**错误不是异常，而是脱离程序员控制的问题。错误在代码中通常被忽略。例如，当栈溢出时，一个错误就发生了，它们在编译也检查不到的。



## 异常体系结构

- `Java`把异常当作对象来处理，并定义一个基类`java.lang.Throwable`作为所有异常的**超类**；
- 在`Java API`中已经定义了许多异常类，这些异常类分为两大类，错误`Error`和异常`Exception`；

![image-20201101160037719](Java异常.assets/image-20201101160037719.png)



## Error

- `Error`类对象由`Java`虚拟机生成并抛出，大多数错误与代码编写者所执行的操作无关；
- `Java`虚拟机运行错误（`Virtual Machine Error`），当`JVM`不再有继续执行操作所需的内存资源时，将出现`OutOfMemoryError`。这些异常法神时，`Java`虚拟机（`JVM`）一般会选择线程终止；
- 还有发生在虚拟机试图执行应用时，如类定义错误（`NoClassDefFoundError`）、链接错误（`LinkageError`）。这些错误是不可查的，因为它们 在应用程序的控制和处理能力之外，而且绝大多数是程序运行时不允许出现的状况。



## Exception

- 在`Exception`分支中有一个重要的子类`RuntimeException`（运行时异常）
  - `ArrayIndexOutOfBoundsException`（数组下标越界）；
  - `NullPointerException`（空指针异常）；
  - `ArithmeticException`（算术异常）；
  - `MissingResourceException`（丢失资源）；
  - `ClassNotFoundException`（找不到类）等异常，这些异常是不检查异常，程序中可以选择捕获处理，也可以不处理；

- 这些异常一般是由程序逻辑错误引起的，程序应该从逻辑角度尽可能避免这类异常的发生；

  

## Error & Exception区别

- `Error`通常是灾难性的致命的错误，是程序无法控制和处理的，当出现这些异常时，`Java`虚拟机（JVM）一般会选择终止线程；
- `Exception`通常情况下是可以被程序处理的，并且在程序中应该尽可能的去处理这些异常。



## 异常处理机制

- 抛出异常
- 捕获异常



- 异常处理的五个关键字
  - try、catch、finally、throw、throws

```java
public class Test {
    public static void main(String[] args) {
        int a = 1;
        int b = 0;

        //可以写多个catch
        //假设要捕获多个异常：必须从范围小到大！
        try { //try监控区域
            System.out.println(a / b);
            new Test().a();
        } catch (Error e) { //catch(想要捕捉的异常类型！)捕获异常
            System.out.println("Error");
        } catch (Exception e) {
            System.out.println("Exception");
        } catch (Throwable e) { //Throwable需要放在最下面，Throwable覆盖了所有错误
            System.out.println("Throwable");
        } finally { //善后工作
            System.out.println("finally");
        }
        //finally 可以不要
        //假设IO流出现异常,finally可以关闭资源
    }

    public void a() {
        b();
    }

    public void b() {
        a();
    }
}
```

```java
//快捷键的使用
public class Test2 {
    public static void main(String[] args) {
        int a = 1;
        int b = 0;

        //idea 选中代码然后ctrl+alt+t，可以选择包裹代码
        //但ctrl+alt+t是终端命令，因此将idea改成ctrl+alt+r
        try {
            System.out.println(a / b);
        } catch (Exception e) {
            System.out.println("除0错误");
            e.printStackTrace(); //打印错误的栈信息
        } finally {
            System.exit(0); //手动程序退出
        }
    }
}
```

```java
public class Test {
    public static void main(String[] args) {
        int a = 10;
        int b = 0;
        int c = 5;

        try {
            new Test().test(a, c); //成功
            new Test().test(a, b); //异常
        } catch (ArithmeticException e) {
            System.out.println("发生除0错误");
            e.printStackTrace();
        } finally {
            System.exit(0);
        }
    }

    //假设这个方法中，处理不了这个异常，可以在方法上抛出异常
    public void test(int a, int b) throws ArithmeticException {
        if (b == 0) {
            throw new ArithmeticException(); //主动抛出一个异常,一般在方法中使用
        }
        System.out.println(a / b);
    }
}
```



## 自定义异常

- 使用`Java`内置的异常类可以描述在编程时出现的大部分异常情况。除此之外，用户还可以自定义异常，用户自定义异常类，只需继承`Exception`类即可；
- 在程序中使用自定义异常类，大体可分为以下几个步骤：
  - 创建自定义异常类；
  - 在方法中通过`throw`关键字抛出异常对象；
  - 如果在当前抛出异常的方法中处理异常，可以使用`try-catch`语句捕获并处理；否则在方法的声明处通过`throws`关键字指明要抛出给方法调用者的异常，继续进行下一步操作；
  - 在出现异常方法的调用者中捕获并处理异常。

```java
//自定义的异常类
public class MyException extends Exception {
    //传递数字>10就抛出异常
    private int detail;

    public MyException(int a) {
        this.detail = a;
    }

    //toString 异常的打印信息
    @Override
    public String toString() {
        return "MyException{" +
                "detail=" + detail +
                '}';
    }
}

public class Test {
    //可能会存在异常的方法
    static void test(int a) throws MyException {

        System.out.println("传递的参数为: " + a);
        if (a > 10) {
            throw new MyException(a); //抛出
        }
        System.out.println("OK");
    }

    public static void main(String[] args) {
        try {
            test(11);
        } catch (MyException e) {
            System.out.println("MyException => " + e);
        } finally {
            System.exit(0);
        }
    }
}

// output:
//	 传递的参数为: 11
//	 MyException => MyException{detail=11}
```



## 实际应用中的经验总结

- 处理运行时异常时，采用逻辑去合理规避同时辅助 `try-catch` 处理
- 在多重`catch`块后面，可以加一个`catch``（Exception）`来处理可能会被遗漏的异常
- 对于确定的代码，也可以加上` try-catch` ，处理潜在的异常
- 尽量去处理异常，切记只是简单地调用`printStackTrace()`去打印输出
- 具体如何处理异常，要根据不同的业务需求和异常类型去决定
- 尽量添加`finally`语句块去释放占用的资源

