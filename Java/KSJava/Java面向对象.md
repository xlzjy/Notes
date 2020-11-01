# Java面向对象

## 面向对象 & 面向对象

### 面向对象思想

- 步骤清晰简单，第一步做什么，第二步做什么....；
- 面对过程适合处理一些较为简单的问题；

### 面向对象思想

- 物以类聚，**分类**的思维模式，思考问题首先会解决问题需要哪些分类，然后对这些分类进行单独思考。最后，对这些问题进行单独思考。最后，才对某个分类下的细节进行面向过程的思索；
- 面向对象适合处理复杂的问题，适合处理需要多人协作的问题！

>**对于描述复杂的事务，为了从宏观上把握、从整体合理分析，我们需要使用面向对象的思路来分析整个系统。但是，具体到微观操作，仍然需要面向过程的思路去处理。**



## 什么是面向对象

- 面向对象编程(Object-Oriented Programming, OOP)；
- 面向对象编程的本质就是：**<u>*以类的方式组织代码，以对象的组织（封装）数据。*</u>**

- **抽象**
- **三大特性：**
  - **封装**
  - **继承**
  - **多态**

- 从认识论角度考虑是先有对象后有类。对象，是具体的事务。类，是抽象的，是对对象的抽象；
- 从代码运行角度考虑是先有类后有对象。类是对象的模板；



## 方法回顾

### 方法的定义

- 修饰符
- 返回类型
- `break`和`return`的区别
  - `break `跳出循环，结束循环
  - `return `返回值，结束函数
- 方法名
  - 注意规范，见名知意
- 参数列表
- 异常抛出

```java
//抛出异常：如文件异常
public void readFile(String file) throws IOException {}
```

### 方法的调用

- #### **静态方法、非静态方法**

1. **静态方法的调用**

```java
//学生类
public class Student {
    //静态方法
    public static void say() {
        System.out.println("静态学生说话了");
    }
}

public static void main(String[] args) {
    //静态方法调用
    Student.say();
}
```

2. **非静态方法调用**

```java
//学生类
public class Student {
    //静态方法
    public static void say() {
        System.out.println("静态学生说话了");
    }
}

public static void main(String[] args) {
   //非静态方法调用先实例化
    Student stu = new Student();
    stu.say1();
}
```

3. **静态方法和非静态方法**

```java
//static关键字表示a()方法是类创建的时候就创建的，创建的时间较早
public static void a() {
    b();//不能调用，非静态方法
    c();//能调用
}

//没有static关键字表示这个方法是创建对象的时候才创建的
public void b() {}

//static方法c()
public static void c() {}
```

- #### **形参和实参**

1. **非静态方法传参**

```java
//非静态方法传参
public static void main(String[] args) {
    System.out.println(new Demo03().add(1, 2));
}
//非静态方法
public int add(int a, int b) {
    return a + b;
}
```

2. **静态方法传参**

```java
//静态方法传参
public static void main(String[] args) {
    System.out.println(add(1,2));
}
//静态方法
public static int add(int a, int b) {
    return a + b;
}
```

- #### 值传递和引用传递

1. **值传递**

```java
//值传递
public class Demo04 {
    public static void main(String[] args) {
        int a = 1;
        System.out.println(a); //1

        Demo04.change(a);
        System.out.println(a); //1
    }

    //返回值为空
    public static void change(int a) {
        a = 10;
    }
}
```

2. **引用传递**

```java
//引用传递：对象，本质还是值传递
public class Demo05 {
    public static void main(String[] args) {
        Person person = new Person();
        System.out.println(person); //@74a14482
        System.out.println(person.name); //null
        
        change(person); //引用传递
        System.out.println(person); //@74a14482，同一个对象
        System.out.println(person.name); //hello
    }

    public static void change(Person person) {
        person.name = "hello";
    }
}

//定义了一个Person类，有一个属性：name
class Person {
    String name; //默认值为null
}
```

- #### `this`关键字



## 类和对象的关系

- **类是一种抽象的数据类型，它是对某一类事物整体描述/定义，但是并不能代表某一个具体的事务。**
  - `Person`类、`Pet`类、`Car`类等，这些类都是用来描述/定义某一类具体的事务应该具备的特点和行为；

- **对象是抽象概念的具体实例**
  - 张三就是人的一个具体实例，张三家里的旺财就是狗的一个具体实例；
  - 能够体现出特点，展现出功能的是具体的实例，而不是一个抽象的概念。



## 类的创建与初始化对象

- 使用`new`关键字创建对象
- 使用`new`关键字创建的时候，除了分配内存空间之外，还会给创建好的对象进行默认的初始化以及对类中构造器的调用。

- 类中的构造器也成为构造方法，是在进行创建对象的时候必须要调用的，并且构造器有一下两个特点：
  1. 必须和类的名字相同
  2. 必须没有返回类型，也不能写`void`

```java
//学生类
public class Student {
    //属性：字段
    String name;
    int age;

    //方法
    public void study() {
        System.out.println(this.name + "在学习");
    }
}

//一个项目应该只有一个main方法
public class Application {
    public static void main(String[] args) {
        //类是抽象的，需要实例化
        //类实例化后会返回一个自己的对象
        //xm、xh对象就是一个Student类的具体实例
        Student xm = new Student();
        Student xh = new Student();

        System.out.println(xm.name); //null
        System.out.println(xh.age); //0

        xm.name = "小明"; //第一个对象
        xm.age = 1;
        System.out.print(xm.name); //小明
        System.out.println(xm.age); //1

        xh.name = "小红"; //第二个对象，是不同的对象
        xh.age = 2;
        System.out.print(xh.name); //小红
        System.out.println(xh.age); //2
    }
}
```

```java
public class Person {
    //查看Person类的class文件可知:
    //public class Person {
    //    public Person() {
    //    }
    //}
    //一个类即使什么都不写，它也会存在一个方法
    //显示的定义构造器
    String name;

    //构造器可以实例化初始值
    //1.使用new关键字，本质是在调用构造器
    //2.构造器一般用来初始化值
    //3.快捷键alt+insert constructor生成构造方法
    //4.this. 代表这个 类.
    public Person() {
        this.name = "helloworld";
    }
    
    //有参构造：一旦定义了有参构造，无参构造就必须显示定义
    public Person(String name){
        this.name = name;
    }
}

//一个项目应该只有一个main方法
/* 注意：一个对象使用了无参构造那么就不能再使用有参构造了，两者选其一，什么都不写默认为无参构造 */
public class Application {
    public static void main(String[] args) {
        //无参构造
        Person person = new Person(); //new实例化了一个对象
        System.out.println(person.name); //由于构造器初始化了name为helloworld
        
        //有参构造
        Person person1 = new Person("123");
        System.out.println(person1.name); //123
    }
}
```



## 面向对象三大特性

### 1.封装

- **该露的露，该藏的藏**
  - 我们程序设计要追求"**<u>高内聚，低耦合</u>**"。
    - **高内聚**：就是类的内部数据操作细节自己完成，不允许外部干涉；
    - **低耦合**：仅暴露少量的方法给外部使用；

- **封装（数据的隐藏）**
  - 通常，应禁止直接访问一个对象中数据的实际表示，而应通过操作接口来访问，这称为信息隐藏；

- **<u>属性私有，`get/set`方法</u>**

- ##### 封装的意义
  1. 提高程序的安全性，保护数据
  2. 隐藏代码的实现细节
  3. 统一接口
  4. 系统可维护性增加

```java
public class Student {
    //属性私有
    private String name; //名字
    private int id; //学号
    private char sex; //性别
    private int age; //年龄

    public int getAge() {
        return age;
    }

    //通过封装可以保证数据安全性,避免你取破坏这个系统
    public void setAge(int age) {
        if (age >= 0 && age <= 120) {
            this.age = age;
        } else {
            this.age = 0;
        }
    }

    //提供一些可以操作这些属性的方法
    //提供一些public的get、set方法
    //get获得这个属性值
    public String getName() {
        return this.name;
    }

    //set给这个属性设置值
    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public char getSex() {
        return sex;
    }

    public void setSex(char sex) {
        this.sex = sex;
    }
}

public class Application {
    public static void main(String[] args) {
        Student s1 = new Student();

        s1.setName("suoluobo");
        System.out.println(s1.getName());

        //通过封装,很容易直到set方法是否存在不合理性
        s1.setAge(999); //不合法
        System.out.println(s1.getAge()); //0
    }
}
```



### 2.继承

- 继承的本质是对某一批类的抽象，从而实现对现实世界更好的建模；
- `extends`的意思是"扩展"。子类是父类的扩展；
- `Java`中类只有单继承，没有多继承！即一个儿子只能有一个爸爸，但是一个爸爸可以有多个儿子；
- 继承是类和类之间的一种关系，除此之外，类和类之间的关系还有依赖、组合、聚合等；
- 继承关系的两个类，一个为子类（派生类），一个为父类（基类）。子类继承父类，使用关键字`extends`来表示；
- 子类和父类之间，从意义上讲应该具有"`is a`"的关系；

```java
/* 父类 */
/* 通过CTRL+H能够查看继承树 */
/* 在Java中，所有的类，都默认直接或间接继承Object类 */
public class Person /*extends Object*/ {
    //四个修饰符 public、protected、default、private
    private int money = 10_0000_0000;

    public void say() {
        System.out.println("说了一句话");
    }

    public int getMoney() {
        return money;
    }

    public void setMoney(int money) {
        this.money = money;
    }
}

/* Student is Person: 派生类，子类 */
/* 子类继承了父类，就会拥有父类的全部方法 */
public class Student extends Person {
}

/* Teacher is Person: 派生类，子类 */
public class Teacher extends Person {
}

public class Application {
    public static void main(String[] args) {
        Student student = new Student();
        student.say(); //说了一句话
        student.setMoney(100); 
        System.out.println(student.getMoney()); //100
    }
}
```



- `object`类，在`Java`中，所有的类，都默认直接或间接继承Object类；

- `super`的使用，`super`注意点：
  1. `super`调用父类的构造方法，必须在构造方法的第一个；
  2. `super`必须只能出现在子类的方法或者构造方法中；
  3. `super`和`this`不能同时调用构造方法；

- `super `vs `this`：
  - **代表的对象不同**：
    - `this`：本身调用者这个对象；
    - `super`：代表父类对象的应用；
  - **前提**
    - `this`：没有继承也可以使用；
    - `super`：只能在继承条件下才可以使用；
  - **构造方法**
    - `this(); `本类的构造；
    - `super();`父类的构造。

```java
/* 父类 */
public class Person {
    protected String name = "father";

    public void print() {
        System.out.println("Person");
    }

    /* private是父类私有的，无法被继承 */
    private void printPrivate() {
        System.out.println("Person Private");
    }
}

/* Student is Person: 派生类，子类 */
public class Student extends Person {
    private String name = "son";

    public void test(String name) {
        System.out.println(name); //luobo
        System.out.println(this.name); //son
        System.out.println(super.name); //father
    }

    public void print() {
        System.out.println("Student");
    }

    public void test1() {
        print(); //Student
        this.print(); //Student
        super.print(); //Person
//        super.printPrivate(); //调用失败，printPrivate是父类私有的
    }
}

public class Application {
    public static void main(String[] args) {
        Student student = new Student();
        student.test("luobo");
        student.test1();
    }
}
```

```java
/* 父类 */
public class Person {
    public Person() {
        System.out.println("Person无参执行了");
    }
}

/* Student is Person: 派生类，子类 */
public class Student extends Person {
    public Student() {
        //隐藏代码：调用了父类的无参构造，即super()
        super(); // 显示调用父类的构造器，同时必须要在子类构造器的第一行
//        this(); // 调用失败,this和super都需要放在第一行，只能取其1
        System.out.println("Student无参执行了");
//        super(); //调用失败
    }
}

public class Application {
    public static void main(String[] args) {
        Student student = new Student();
    }
}
```



- **方法重写**
  - **重写：**需要有继承关系，子类重写父类的方法！
    1. 方法名必须相同
    2. 参数列表必须相同
    3. 修饰符：范围可以扩大但不能缩小：`public > protected > default > private`
    4. 抛出的异常：范围，可以被缩小，但不能扩大：`Exception`(大) -> `ClassNotFoundException`(小) 
  - **重写**：子类的方法和父类必须一致，只是方法体不同！
  - **为什么需要重写**：
    - 父类的功能，子类不一定需要，或者不一定满足！
  - **`IDEA`快捷键** `Alt+Insert -> Override`

```java
// 有static情况下，以下不是重写
// 重写都是方法的重写，和属性无关
public class Father {
    //有static表示私有
    public static void test() {
        System.out.println("Father => test");
    }
}

public class Son extends Father {
    //有static表示私有，没有进行方法重写
    public static void test() {
        System.out.println("Son => test");
    }
}

// 父类子类都是静态方法：方法调用只看左边定义的数据类型有关
public class Application {
    public static void main(String[] args) {
        //方法的调用只和左边定义的数据类型有关
        Son son = new Son();
        son.test(); // Son => test

        //父类的引用指向了子类
        Father father = new Son();
        father.test(); // Father => test
    }
}

output:
	Son => test
    Father => test
```

```java
// 非静态方法下，重写
// 注意：静态的方法和非静态的方法区别很大！
// 重写都是方法的重写，和属性无关
// 重写只有用修饰符public
public class Father {
    public void test() {
        System.out.println("Father => test");
    }
}

public class Son extends Father {
    // Override 重写
    @Override // 注解：有功能的注释！
    public void test() {
        System.out.println("Son => test");
    }
}

public class Application {
    public static void main(String[] args) {
        //方法的调用只和左边定义的数据类型有关
        Son son = new Son();
        son.test(); // Son => test

        //父类的引用指向了子类
        Father father = new Son(); // 子类重写了父类的方法
        father.test(); // Son => test
    }
}

output:
	Son => test
    Son => test
```



### 3.多态

- **动态编译：增加类型可扩展性**
- 即同一个方法可以根据发送对象的不同而采用多种不同的行为方式；
- 一个对象的实际类型是确定的，但可以指向对象的引用的类型有很多；

- **多态存在的条件：**
  - 有继承关系
  - 子类重写父类方法
  - 父类引用指向子类对象

- **多态的注意事项：**
  - 多态是方法的多态，属性没有多态
  - 父类和子类之间要有关系，否则会类型转换异常，`ClassCastException`!
  - 存在条件：继承关系，方法需要重写，父类引用指向子类对象！ `Father f = new Son();`

```java
public class Person {
    public void run() {
        System.out.println("run");
    }
}

public class Student extends Person {
    @Override
    public void run() {
        System.out.println("student run");
    }

    public void eat() {
        System.out.println("student eat");
    }
}

public class Application {
    public static void main(String[] args) {
        //一个对象的实际类型是确定的
        new Student();
        new Person();

        //可以指向的引用类型就不确定了：父类的引用指向子类
        //Student子类，能调用的方法都是自己的或者继承父类的！
        Student s1 = new Student();
        //Person父类，可以指向子类，但是不能调用子类独有的方法！
        Person s2 = new Student();
        Object s3 = new Student();

        s2.run(); //子类重写了父类的方法，执行子类的方法
        s1.run();

        //对象能执行哪些方法，主要看对象左边的类型，和右边关系不大！
        s1.eat();
//        s2.eat(); //无法直接调用，s2的类型是Person，没有eat方法
        ((Student) s2).eat(); //强制类型转换
    }
}
```

- **如果采用了如下修饰符，则方法不存在多态性：**
  - `static`方法，属于类，它不属于实例，所以不存在实例；
  - `final`常量；
  - `private`方法；

- <u>**注意：多态是方法的多态，属性没有多态性**</u>
- `instanceof` 
  - 引用类型的类型转换
  - 判断一个对象是什么类型

```java
public class Person /*extends Object*/{
}

public class Student extends Person {
}

public class Teacher extends Person {
}

public class Application {
    public static void main(String[] args) {
        //Object > String
        //Object > Person > Teacher 第一条关系线
        //Object > Person > Student 第二条关系线
        //所以Teacher和Student之间没关系
        Object object = new Student();
        System.out.println(object instanceof Student); //true
        System.out.println(object instanceof Person); //true
        System.out.println(object instanceof Object); //true
        System.out.println(object instanceof Teacher); //false
        System.out.println(object instanceof String); //false
        System.out.println("===========================");

        //Person > Teacher
        //Person > Student
        Person person = new Student();
        System.out.println(person instanceof Student); //true
        System.out.println(person instanceof Person); //true
        System.out.println(person instanceof Object); //true
        System.out.println(person instanceof Teacher); //false
//        System.out.println(person instanceof String); //编译报错
        System.out.println("===========================");

        Student student = new Student();
        System.out.println(student instanceof Student); //true
        System.out.println(student instanceof Person); //true
        System.out.println(student instanceof Object); //true
//        System.out.println(student instanceof Teacher); //编译报错
//        System.out.println(student instanceof String); //编译报错
        System.out.println("===========================");
    }
}
```

```java
public class Person {
    public void run() {
        System.out.println("run");
    }
}

public class Student extends Person {
    public void go() {
        System.out.println("go");
    }
}

public class Application {
    public static void main(String[] args) {
        //类型之间的转化：父类（高） 子类（低）
        //低转高不需要强制转换
        //高转低需要强制转换
        //      高              低
        Person obj = new Student();

        //将obj这个对象转换为Student类型，我们就可以使用Student类型的方法了！
        ((Student) obj).go();
    }
}
```

```java
public class Application {
    public static void main(String[] args) {
        Student student = new Student();
        student.go();

        //子类转换为父类，可能丢失自己的本来的一些方法
        Person person = student;
        person.run();
        ((Student) person).go();
    }
}
```

- **多态总结**：

  - 父类引用指向子类对象；

  - 把子类转换为父类，向上转型；

  - 把父类转换为子类，向下转型，需要强制转换；

  - 优点：方便方法的调用，减少重复的代码，使代码简洁！

    

## static详解

### **static关键字的使用**

```java
public class Student {
    private static int age; //static,静态变量
    private double score; //非静态的变量

    public static void main(String[] args) {
        Student s1 = new Student();

        //staic静态变量，和类一起加载，所以能够共享
        System.out.println(age);
        System.out.println(s1.age);
        System.out.println(Student.age);

//        System.out.println(score); //不能调用
        System.out.println(s1.score); //必须实例化后才能调用
//        System.out.println(Student.score); //不能调用
    }
}
```

```java
public class Student {
    //非静态方法
    public void run() {
        System.out.println("run");
    }

    //静态方法
    public static void go() {
        System.out.println("go");
    }

    public static void main(String[] args) {
//        run(); //没法直接run,必须要new一个对象
        Student student = new Student();
        student.run();

        go(); //静态方法，它在当前这个类里面，直接调用
        student.go();
        Student.go();
    }
}
```

```java
public class Person {
    //最早执行
    static {
        //静态代码块
        //类加载的时候就执行，只执行一次
        //所以静态代码块可以用来赋初始值
        System.out.println("静态代码块");
    }

    //其次执行
    {
        //代码块（匿名代码块）
        //程序在运行的时候，并不能主动去加载这个块，只有创建对象时才会执行
        System.out.println("匿名代码块");
    }

    //最后执行
    public Person() {
        System.out.println("构造方法");
    }

    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("===============");
        Person person2 = new Person();
        /*
            output:
                静态代码块
                匿名代码块
                构造方法
                ===============
                匿名代码块
                构造方法
        */
    }
}
```

```java
//静态导入包
import static java.lang.Math.random;
import static java.lang.Math.PI;

public class Test {
    public static void main(String[] args) {
        System.out.println(Math.random());
        System.out.println(random()); //使用静态导入包之后，使用时就可以省去类名
    }
}
```



## 抽象类

- `abstract`修饰符可以用来修饰方法也可以修饰类，如果修饰方法，那么该方法就是抽象方法；如果修饰类，那么该类就是抽象类；
- 抽象类中可以没有抽象方法，但是有抽象方法的类一定要声明为抽象类；
- 抽象类，不能使用new关键字来创建对象，它是用来让子类继承的；
- 抽象方法，只有方法的声明，没有方法的实现，它是用来让子类实现的；
- 子类继承抽象类，那么就必须要实现抽象类没有实现的抽象方法，否则该子类也要声明为抽象类。

```java
// abstact 抽象类
// 但本质还是一个类，只能extends或者被extends，而Java只有单继承
// 为了能够支持多继承，引出了接口的概念
public abstract class Action {
    // 没有实现，希望有人帮我们实现
    // abstact，抽象方法，只有方法名字，没有方法的实现！
    public abstract void doSomething();

    //特点：
    //1.不能new这个抽象类，只能靠子类去实现它，这是一种约束！
    //2.抽象类中可以写普通的方法
    //3.抽象方法必须在抽象类中
    //4.抽象类也有构造
    //抽象类的意义：节省代码，提高开发效率

    //普通方法
    public void eat() {
    }

    //构造方法
    public Action() {
        super();
        System.out.println("抽象类构造");
    }
}

//抽象类的所有方法，继承了它的子类，都必须要实现它的方法，除非这个子类也是抽象类
public class A extends Action {
    @Override
    public void doSomething() {
        System.out.println("doSomething");
    }

    //构造方法
    public A() {
        super();
    }
}

public class Application {
    public static void main(String[] args) {
        A a = new A();
    }
}
```



## 接口

- **普通类**：只有具体实现；
- **抽象类**：具体实现和规范（抽象方法）都有；
- **接口**：只有规范！自己无法写方法，以此实现约束和实现分离，即面向接口编程；
- **接口就是规范，定义的是一组规则，体现了现实世界中"如果你是...则必须能..."的思想；**
- **接口的本质是契约，就像法律一样，制定好之后大家都要遵守；**
- `OO`的精髓，是对对象的抽象，最能体现这一点的就是接口。为什么我们讨论设计模式都只针对具备了抽象能力的语言（比如`C++`、`Java`、`C#`等），就是因为设计模式所研究的，实际上就是如何合理的去抽象；
- **声明接口的关键字是**`interface`

```java
//接口都需要有实现类
public interface UserInterface {
    //接口中的所有定义其实都是抽象的 public
    //public abstract void run();
    //其中public abstact是灰色的，说明本来就已经默认是public abstact
    void add(String name); //默认包含public abstarct

    void delete(String name);

    void update(String name);

    void query(String name);
}

public interface TimeService {
    void timer();

    //在接口中定义变量，实际是常量
    //默认用public static final修饰，是不能改变的
    public static final int AGE = 99;
}

//类可以实现接口，通过implements接口
//实现了接口的类，就需要重写接口中的方法
//UserServiceImpl类实现了UserInterface、TimeService两个接口
//因此通过接口实现了多继承
//类命名时使用Impl结尾
public class UserServiceImpl implements UserInterface, TimeService {
    @Override
    public void timer() {}

    @Override
    public void add(String name) {}

    @Override
    public void delete(String name) {}

    @Override
    public void update(String name) {}

    @Override
    public void query(String name) {}
}
```

- **接口作用**
  1. 约束；
  2. 定义一些方法，让不同的人实现；
  3. 接口中的方法都是`public abstract`，且没有方法体；
  4. 接口中的常量是`public static final`；
  5. 接口不能被实例化，因为接口中没有构造方法；
  6. `implements`可以实现多个接口；
  7. 实现接口必须要重写接口中的所有方法；



## 内部类

内部类就是在一个类的内部再定义一个类，比如，`A`类中定义一个`B`类，那么`B`类相对于`A`类来说就称为内部类，而`A`类相对`B`类来说就是外部类。

### 成员内部类

```java
public class Outer {
    private int id = 10;

    public void out() {
        System.out.println("这是外部类的方法");
    }

    public class Inner {
        public void in() {
            System.out.println("这是内部类的方法");
        }

        //内部类可以直接访问外部类私有属性
        public void getID() {
            System.out.println(id);
        }

        //内部类可以获得外部类的方法
        public void getOut() {
            out();
        }
    }
}

public class Application {
    public static void main(String[] args) {
        Outer outer = new Outer();

        //通过这个外部类来实例化
        Outer.Inner inner = outer.new Inner();
        inner.in();
        inner.getID();
        inner.getOut();
    }
}
```

### 静态内部类

```java
public class Outer {
    private int id = 10;

    public void out() {
        System.out.println("这是外部类的方法");
    }

    public static class Inner {
        public void in() {
            System.out.println("这是内部类的方法");
        }

        // 因为内部类在id还没创建时就已经加载，所以是访问不到id的
        // 静态内部类访问不到非静态属性、方法
        public void getID() {
//            System.out.println(id);
        }
    }
}
```

### 局部内部类

```java
// 以下不是内部类，只是说明了一个class文件里可以定义多个class
public class Outer {

}

// 一个java类中可以有多个class类，但是只要有一个public class
class A {}
```

```java
// 局部内部类
public class Outer {
    //局部内部类
    class Inner {
        public void in() {
        }
    }
}
```

### 匿名内部类

```java
public class Test {
    public static void main(String[] args) {
        //正常方法
        Apple apple = new Apple();
        //匿名对象的使用
        //没有名字初始化类，不用将实例保存到变量中
        new Apple().eat();

        //匿名接口的使用
        new UserService() {
            //必须要实现
            @Override
            public void hello() {

            }
        };
    }
}

class Apple {
    public void eat() {
        System.out.println("eat apple");
    }
}

interface UserService {
    void hello();
}
```

