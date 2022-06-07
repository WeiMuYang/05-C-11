#include <iostream>
#include <string>
#include <memory>
using namespace std;
/* 1 weak_ptr 是一个弱引用的指针，不会累计计数
 * 2 weak_ptr 只能从shared_ptr或者是weak_ptr构造而来
 * 3 主要用途是为了解决shared_ptr 循环引用导致内存未被释放问题
 * 注意点：
 *    不可以使用* 或者 ->访问对象
 *    weak_ptr不会造成计数的改变
 *    解决shared_ptr中的循环引用计数增加的问题
 *
 *
 *
 *
 *
 */

class B;
class A
{
public:
    A(){
        cout << "A()" << endl;
    }
    ~A(){
        cout << "~A()" << endl;
    }

//    shared_ptr<B> b;
    weak_ptr<B> b;
};

class B
{
public:
    B() {
        cout << "B" << endl;
    }
    ~B(){
        cout << "~B" << endl;
    }

//    shared_ptr<A> a;
    weak_ptr<A> a;
};

int main()
{
    //    weak_ptr<int>  pInt(new int(100));  错误，不能直接构建对象
    {
        shared_ptr<int> pShare(new int(100));
        cout << "count:" << pShare.use_count() << endl;
        weak_ptr<int> pWeak(pShare);
        cout << "count:" << pShare.use_count() << endl;
        pWeak.reset();
        cout << "count:" << pShare.use_count() << endl;
        // 访问数据：weak_ptr访问shared_ptr再去访问数据
        //  lock()函数可以访问shared_ptr;
        shared_ptr<int> temp = pWeak.lock(); //
        //        cout << *temp.get() << endl;
    }
    cout << "loop re" << endl;
    {
        shared_ptr<A> aObj = make_shared<A>();
        shared_ptr<B> bObj = make_shared<B>();
        cout << aObj.use_count() << endl;
        cout << bObj.use_count() << endl;
//        aObj.get()->b = bObj;
//        bObj.get()->a = aObj;

    }

    return 0;
}
