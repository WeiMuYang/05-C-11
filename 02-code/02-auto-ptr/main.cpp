#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include <iostream>
#include <string>

using namespace std;


class Test
{
public:
    Test(string s)  {
        str = s;
        cout << "Test create\n";
    }
    ~Test()
    {
        cout << "Test delete:" << str << endl;
    }
    string& getStr() {
        return str;
    }
    void setStr(string s)  {
        str = s;
    }
    void print()  {
        cout << str << endl;
    }
private:
    string str;
};

int main()
{
    auto_ptr<Test> ptest(new Test("123"));
    ptest->setStr("hello ");
    ptest->print();
    ptest.get()->print();
    ptest->getStr() += "world !";
    (*ptest).print();
    // 重新绑定指向的对象，而原来的对象则会被释放
    ptest.reset(new Test("123"));  // 此时会释放ptest之前指向的hello world
    ptest->print();
    return 0;
}
