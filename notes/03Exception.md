# Exception

类图:

![avatar](/notes/image/UMLClassDiagram-Exception.png)

1.backtrace: 栈回溯，保存各个栈帧的地址

2.backtrace_symbols: 根据地址，转成相应的函数符号

3.demangle: 将C++源程序标识符(original C++ source identifier)转换成C++ ABI标识符(C++ ABI identifier)的过程称为mangle；相反的过程称为demangle。

4.noexcept: 告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。

5.__thread: 关键字， __thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。__thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。

__thread使用规则：只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制内容可以任意复制memset,memcpy,且内容可以复原)，不能修饰class类型，因为无法自动调用构造函数和析构函数，可以用于修饰全局变量，函数内的静态变量，不能修饰函数的局部变量或者class的普通成员变量，且__thread变量值只能初始化为编译器常量(值在编译器就可以确定const int i=5,运行期常量是运行初始化后不再改变const int i=rand()).

6.__builtin__expect(): 分支预判,向编译器提供分支预测信息，从而帮助编译器进行代码优化