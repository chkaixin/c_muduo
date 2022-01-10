# AtomicIntegerT

类图:

![avatar](/notes/image/UMLClassDiagram-AtomicIntegerT.png)

1.gcc原子性操作
```
// 原子自增操作
type __sync_fetch_and_add (type *ptr, type value)

// 原子比较和交换（设置）操作
type __sync_val_compare_and_swap (type *ptr, type oldval type newval)
bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval)

// 原子赋值操作
type __sync_lock_test_and_set (type *ptr, type value)
使用这些原子性操作，编译的时候需要加-march=cpu-type
-march=native		// 指定cpu体系结构为本地平台
```

2.volatile

volatile的作用： 作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值。简单地说就是防止编译器对代码进行优化

当要求使用volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，而不是使用保存在寄存器中的备份。即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存
