# [智能指针-shared_ptr](./)  [img](./img)     

> ######  _标签:_   ![](https://img.shields.io/badge/技术类-yellowgreen.svg)   ![](https://img.shields.io/badge/C++11/14-用户手册-blue.svg)   [![](https://img.shields.io/badge/链接-手动实现shared_ptr-brightgreen.svg)](https://www.cnblogs.com/tianshihao/p/14378918.html)   [![](https://img.shields.io/badge/链接-shared_ptr与线程安全-brightgreen.svg)](https://www.cnblogs.com/tianshihao/p/14378918.html)    [![](https://img.shields.io/badge/链接-代码文件-orange.svg)](../02-code/)        
>

## 1 基本用法 

智能指针本质上是一个模板类，通过类的声明周期自动结束效果，实现的自动释放。虽然叫指针，但是本质上是一个对象。一般不会去new一个智能指针，如果自己new创建的需要自己手动释放。      

## 1 share_ptr  [官方文档](http://www.cplusplus.com/reference/memory/shared_ptr/?kw=shared_ptr)    

共享指针
管理指针的存储，提供有限的垃圾收集设施，可能与其他对象共享该管理。

shared_ptr 类型的对象能够获得指针的所有权并共享该所有权：一旦他们获得所有权，指针的所有者组就会在最后一个释放该所有权时负责删除该指针。

shared_ptr 对象一旦它们自己被销毁，或者它们的值因赋值操作或显式调用 shared_ptr::reset 而改变时，就会释放它们共同拥有的对象的所有权。一旦通过指针共享所有权的所有 shared_ptr 对象都释放了该所有权，则删除托管对象（通常通过调用 ::delete，但可以在构造时指定不同的删除器）。

shared_ptr 对象只能通过复制它们的值来共享所有权：如果两个 shared_ptr 是从同一个（非shared_ptr）指针构造（或制作）的，它们都将拥有该指针而不共享它，当其中一个释放时会导致潜在的访问问题它（删除其托管对象）并将另一个指向无效位置。

此外，shared_ptr 对象可以共享一个指针的所有权，同时指向另一个对象。这种能力称为别名（参见构造函数），通常用于在拥有成员对象时指向成员对象。因此，一个 shared_ptr 可能与两个指针相关：

一个存储的指针，即它所指向的指针，以及它用 operator* 取消引用的指针。
一个拥有的指针（可能是共享的），它是所有权组负责在某个时间点删除的指针，并计为使用。

通常，存储指针和拥有指针指向同一个对象，但别名 shared_ptr 对象（使用别名构造函数及其副本构造的对象）可能指向不同的对象。

不拥有任何指针的 shared_ptr 称为空 shared_ptr。不指向任何对象的 shared_ptr 称为空 shared_ptr 并且不应取消引用。请注意，空的 shared_ptr 不一定是空的 shared_ptr，空的 shared_ptr 也不一定是空的 shared_ptr。

shared_ptr 对象通过提供对它们通过运算符 * 和 -> 指向的对象的访问来复制有限的指针功能。出于安全原因，它们不支持指针算术。

一个相关的类，weak_ptr，能够与 shared_ptr 对象共享指针，而无需拥有它们。

## 2 share_ptr的简单实现  

### 2.1 引用计数   

面试时，我想是不是用 `static` 实现的引用计数？其实不能这样做，静态变量是同属一个类所有对象，这样的话这个类的所有对象，不管指向的是不是相同的内存，它们共享的都是同一个计数器。

引用计数，就是在内存中开辟一块内存专门用于存储资源被引用的次数，自己保留一个指向计数器的指针，计数器初始化为 1。每次用已有的 `shared_ptr` 构造新的 `shared_ptr` 或者给已有的 `shared_ptr` 赋值时，通过指针将计数器加 1，所有指向同一个资源的 `shared_ptr` 也指向同一个计数器。

### 2.2 释放所有权  

当 `shared_ptr` 析构或主动释放所有权时，应将引用计数减 1，然后判断引用计数是否归零，如果归零，那么就释放指针指向的内存，此后将计数器指针置为空。需要注意的是，如果将计数器指针置为空，为了防止指针主动释放所有权之后计数器指针为空，导致判断计数是否归零，需要在判断计数归零前先判断计数指针是否为空。
