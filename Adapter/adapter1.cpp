#include <vector>
#include <iostream>

// 鸭子接口类
class Duck {
public:
    virtual void duck_quack() = 0;
    virtual void duck_fly() = 0;
};

class MallarDuck : public Duck {
public:
    void duck_quack() override {
        std::cout << " Mallar Duck Quack !!" << std::endl;
    }

    void duck_fly() override {
        std::cout << " Mallar Duck Can Fly !!" << std::endl;
    }
};

// 火鸡接口类
class Turkey {
public:
    virtual void turkey_gobble() = 0;
    virtual void turkey_fly() = 0;
};

class WildTurkey : public Turkey {
public:
    void turkey_gobble() override {
        std::cout << " Wild Turkey Gobble !!" << std::endl;
    }
    void turkey_fly() override {
        std::cout << " Wild Turkey Can Fly Short Distance !!" << std::endl;
    }
};

// 火鸡适配器，实现鸭子的接口
class TurkeyAdapter : public Duck {
public:
    explicit TurkeyAdapter(Turkey* turkey):m_turkey(turkey) {}

    void duck_quack() override {
        m_turkey->turkey_gobble();
    }

    void duck_fly() override {
        m_turkey->turkey_fly();
    }

private:
    Turkey*     m_turkey;
};


void TestAdpater() {

    // 创建一个鸭子类
    Duck* pMD = new MallarDuck();

    // 创建一个火鸡类
    Turkey* pWT = new WildTurkey();

    Duck* pAdapter = new TurkeyAdapter(pWT);

    std::cout << " The Duck Says ..... " << std::endl;
    pMD->duck_quack();
    pMD->duck_fly();

    std::cout << "\n\n The Turkey Says ..... " << std::endl;
    pWT->turkey_gobble();
    pWT->turkey_fly();

    // 通过鸭子的接口使用火鸡的方法。
    std::cout << "\n\n The Turkey Adapter Says ..... " << std::endl;
    pAdapter->duck_quack();
    pAdapter->duck_fly();
}

int main() {

    TestAdpater();
    return 0;
}