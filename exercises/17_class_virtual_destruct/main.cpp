#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};
int A::num_a = 0;
struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
int B::num_b = 0;
int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");//num_a是静态成员每调用一次A/A的派生类都会使num_a＋1
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针,创建一个B类型的指针并声明为A类型
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    //static_cast 基本类型转换
    //reinterpret_cast 指针转换
    //const_cast
    //dynamic_cast 多态的转换（父子类转换，兄弟转换）
    B &bb = dynamic_cast<B &>(*ab);//动态转换后调用析构函数是调用A的析构函数
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");
    return 0;
}
