# Java网络编程

## 网络通信的要素

### 如何实现网络的通信？

#### **通信双方地址：**

- `ip`
- 端口号

#### 规则：网络通信的协议

`TCP/IP`模型

#### 小结

- 网络编程中有两个主要的问题
  - 如何准确的定位到网络上的一台或者多台主机；
  - 找到主机之后如何进行通信；

- 网络编程中的要素
  - `IP`和端口号
  - 网络通信协议`UDP`、`TCP`
- `Java`中万物皆对象



## IP

- `IP`地址：`InetAddress`
  - 唯一定位一台网络上计算机
  - `127.0.0.1` 本机 `localhost`

- `IP`地址的分类
  - `ipv4` / `ipv6`
  - 公网 / 私网

- 域名

```java
import java.net.InetAddress;
import java.net.UnknownHostException;

//测试IP
public class TestInetAddress {
    public static void main(String[] args) {
        try {
            //查询本机地址
            InetAddress inetAddress1 = InetAddress.getByName("127.0.0.1");
            System.out.println(inetAddress1);
            InetAddress inetAddress2 = InetAddress.getByName("localhost");
            System.out.println(inetAddress2);
            InetAddress inetAddress3 = InetAddress.getLocalHost();
            System.out.println(inetAddress3);

            //查询网站ip地址
            InetAddress inetAddress4 = InetAddress.getByName("www.baidu.com");
            System.out.println(inetAddress4);

            //常用方法
            System.out.println(inetAddress4.getAddress());
            System.out.println(inetAddress4.getCanonicalHostName());
            System.out.println(inetAddress4.getHostAddress());
            System.out.println(inetAddress4.getHostName());
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
```



## 端口

- 端口表示计算机上的一个程序的进程；

- 不同的进程有不同的端口号；
- 端口号被规定`0 ~ 65535`
- 端口号不能重复；
- 端口用来区分软件
- 端口分类：
  - 公有端口 `0 ~ 1023`
  - `HTTP 80`
  - `HTTPS 443`
  - `FTP 21`
  - `Telnet 23`

- 程序注册端口：`1024 ~ 49151`，分配用户或者程序
  - `Tomcat 8080`
  - `MySQL  3306`
  - `Oracle 152`
- 动态、私有：`49152 ~ 65535`

```bash
netstat -ano #查看所有的端口
netstat -ano | findstr "5900" #查看指定的端口
tasklist | findstr "8696" #查看指定端口的进程
```

```java
public class TestInetSockertAddress {
    public static void main(String[] args) {
        InetSocketAddress socketAddress = new InetSocketAddress("127.0.0.1", 8080);
        InetSocketAddress socketAddress2 = new InetSocketAddress("localhost", 8080);
        System.out.println(socketAddress);
        System.out.println(socketAddress2);

        System.out.println(socketAddress.getAddress());
        System.out.println(socketAddress.getHostName());//地址
        System.out.println(socketAddress.getPort());//端口
    }
}
```



## 通信协议

- TCP
- UDP



## TCP