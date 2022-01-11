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