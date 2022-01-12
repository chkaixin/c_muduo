# Thread

1.explicit关键字: 

原文：https://www.cnblogs.com/gklovexixi/p/5622681.html

在C++中，我们有时可以将构造函数用作自动类型转换函数。但这种自动特性并非总是合乎要求的，有时会导致意外的类型转换，因此，C++新增了关键字explicit，用于关闭这种自动特性。即被explicit关键字修饰的类构造函数，不能进行自动地隐式类型转换，只能显式地进行类型转换。类构造函数默认情况下即声明为implicit(隐式)。

注意：只有一个参数的构造函数，或者构造函数有n个参数，但有n-1个参数提供了默认值，这样的情况才能进行类型转换。

下面通过一段代码演示具体应用（无explicit情形）:

```c++
/* 示例代码1 */
class Demo
{
   public:
    Demo();    　　　　　　　　　　　　　　   /* 构造函数1 */
    Demo(double a);　　　　　　　　　　　　  /* 示例代码2 */
    Demo(int a,double b);　　　　　　　　   /* 示例代码3 */
    Demo(int a,int b=10,double c=1.6);　　/* 示例代码4 */
    ~Demo();
    void Func(void);

    private:
    int value1;
    int value2;
};
```

上述四种构造函数：

构造函数1没有参数，无法进行类型转换！

构造函数2有一个参数，可以进行类型转换，如：Demo test; test = 12.2;这样的调用就相当于把12.2隐式转换为Demo类型。

构造函数3有两个参数，且无默认值，故无法使用类型转换！

构造函数4有3个参数，其中两个参数有默认值，故可以进行隐式转换，如：Demo test;test = 10;

下面讲述使用了关键字explicit的情况:
```c++
1 /* 示例代码2 */
class Demo
{
    public:
    Demo();    　　　　　　　　　　　　　　   /* 构造函数1 */
    explicit Demo(double a);　　　　　　　 /* 示例代码2 */
    Demo(int a,double b);　　　　　　　　   /* 示例代码3 */

    ~Demo();
    void Func(void);

    private:
    int value1;
    int value2;
};
```
在上述构造函数2中，由于使用了explicit关键字，则无法进行隐式转换。即：Demo test;test = 12.2;是无效的！但是我们可以进行显示类型转换，如：

Demo test;

test = Demo(12.2); 或者

test = (Demo)12.2;

2.__thread，gcc内置的线程局部存储设施

__thread只能修饰POD类型

POD类型（plain old data），与C兼容的原始数据，例如，结构和整型等C语言中的类型是 POD 类型，但带有用户定义的构造函数或虚函数的类则不是

__thread string t_obj1(“cppcourse”);	// 错误，不能调用对象的构造函数

__thread string* t_obj2 = new string;	// 错误，初始化只能是编译期常量

__thread string* t_obj3 = NULL;	// 正确

3.线程标识符: pthread_self/gettid

Linux中，每个进程有一个pid，类型pid_t，由getpid()取得。Linux下的POSIX线程也有一个id，类型 pthread_t，由pthread_self()取得，该id由线程库维护，其id空间是各个进程独立的（即不同进程中的线程可能有相同的id）。Linux中的POSIX线程库实现的线程其实也是一个进程（LWP），只是该进程与主进程（启动线程的进程）共享一些资源而已，比如代码段，数据段等。
有时候我们可能需要知道线程的真实pid。比如进程P1要向另外一个进程P2中的某个线程发送信号时，既不能使用P2的pid，更不能使用线程的pthread id，而只能使用该线程的真实pid，称为tid。

有一个函数gettid()可以得到tid，但glibc并没有实现该函数，只能通过Linux的系统调用syscall来获取。
return syscall(SYS_gettid)

4.pthread_atfork()

```c++
#include <pthread.h>
int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
```

调用fork时，内部创建子进程前在父进程中会调用prepare，内部创建子进程成功后，父进程会调用parent ，子进程会调用child

5.std::is_same: 判断类型是否一致

bool isInt = std::is_same<int, int>::value; //为true

编译器判断:

static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");

6.pthread_detach()

linux线程执行和windows不同，pthread有两种状态joinable状态和unjoinable状态

一个线程默认的状态是joinable，如果线程是joinable状态，当线程函数自己返回退出时或pthread_exit时都不会释放线程所占用堆栈和线程描述符（总计8K多）。只有当你调用了pthread_join之后这些资源才会被释放。
若是unjoinable状态的线程，这些资源在线程函数退出时或pthread_exit时自动会被释放。

unjoinable属性可以在pthread_create时指定，或在线程创建后在线程中pthread_detach自己, 如：pthread_detach(pthread_self())，将状态改为unjoinable状态，确保资源的释放。如果线程状态为 joinable,需要在之后适时调用pthread_join

7.prctl(): 设置进程名字

::prctl(PR_SET_NAME, muduo::CurrentThread::t_threadName);

