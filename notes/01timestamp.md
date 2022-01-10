# Timestamp

类图：

![avatar](/notes/image/UMLClassDiagram-Timestamp.png)

1.<base/Types.h>: Google封装类型转换的文件

2.less_than_comparable: 实现<,可自动实现>,<=,>=

3.BOOST_STATIC_ASSERT: 静态编译时断言

4.使用PRId64: #include <inttypes.h>,这是一种跨平台的书写方式，主要是为了同时支持32位和64位操作系统。PRId64表示64位整数，在32位系统中表示long long int，在64位系统中表示long int.
```
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
printf("%" PRId64 "\n", value);
```