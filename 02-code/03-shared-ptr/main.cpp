#include <iostream>
#include <string>
#include <memory>

using namespace std;
class MM
{
public:
    MM(string m,int a):name(m),age(a) {}
    ~MM() {
        cout << "~MM" << endl;
    }
    void print() {
        cout << "name: " << name << endl;
    }
public:
    string name;
    int age;
};


class TestData {
public:
    TestData() {
        cout << "TestData()" << endl;
    }
    ~TestData() {
        cout << "~TestData()" << endl;
    }
};




void printMM(shared_ptr<MM> pMM) {
    pMM->print();
}




//5 智能指针使用的几种形态
void testShared_ptr() {
    shared_ptr<MM> pmm(new MM("亲爱的" , 39));
    printMM(pmm);

    // 注意：智能指针管理能够直接delete内存变量，如果经过特殊
    // 特殊方式释放的内存，那么需要自己手动写删除器
    // 1 对象数组:申请一段内存的需要自己写删除器
    {
        shared_ptr<TestData> p(new TestData[10],[](TestData *p) {delete []p;});

    }

    // 2 函数指针
    {
//        shared_ptr<FILE> pf(fopen("1.txt","w+"));
    }

}

auto returnShare_ptr() {
    shared_ptr<MM> pmm(new MM("小仙女", 1000));
    return pmm;
}

int main()
{
    // 1 一个空的智能指针对象
    shared_ptr<int> pInt;
    if(!pInt) {
        cout << "空的指针对象" << endl;
    }
    // 2 构造函数传参的方式，绑定一个堆区变量
    shared_ptr<int> pNum(new int(100));
    // 3 make_shared来构建
    shared_ptr<int> pMake = make_shared<int>(1);
    // shared_ptr<MM> pMM = make_shared<MM>("MM", 18);

    /* 4 share_ptr 主要成员函数
     * get() 函数：返回管理数据的内存指针，指向管理对象
     * user_count()函数：计数，统计引用管理对象的智能指针对象数
     * swap()：交换
     * reset()：重新设置管理对象
     */

    {
        shared_ptr<MM> pmm(new MM("MM", 18));
        pmm.get()->print();
        shared_ptr<MM> pmm2(pmm);
        cout << "count :" <<  pmm.use_count() << endl;
        cout << "count :" <<  pmm2.use_count() << endl;
        shared_ptr<MM> pmm3 = pmm;
        cout << "count :" <<  pmm2.use_count() << endl;
        shared_ptr<MM> pmm4 = pmm;
        cout << "count :" <<  pmm2.use_count() << endl;
        // 断开与管理对象的联系
        pmm4.reset();
        cout << "count :" <<  pmm2.use_count() << endl;
        // 注意问题
        MM* p = pmm.get();  // 通过get获得智能指针管理对象
//        delete p;           // 导致内存多次释放，
    }
    testShared_ptr();

    return 0;
}
