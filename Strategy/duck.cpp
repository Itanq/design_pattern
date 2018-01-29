
#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

// 飞行相关的行为
class FlyBehavior {
public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
public:
    void fly() override {
        std::cout << " I Can Fly With Wings " << std::endl;
    }
};

class FlyWithRocket : public FlyBehavior {
public:
    void fly() override {
        std::cout <<" I Can Fly With Rocket " << std::endl;
    }
};

class FlyNoWings : public FlyBehavior {
public:
    void fly() override {
        std::cout << " I Can't Fly " << std::endl;
    }
};

// 叫相关的行为
class QuackBehavior {
public:
    virtual void quack() = 0;
};

class Quack : public QuackBehavior {
public:
    void quack() override {
        std::cout << " quack quack " << std::endl;
    }
};

class Squeak : public QuackBehavior {
public:
    void quack() override {
        std::cout << " squeak squeak " << std::endl;
    }
};

class MuteQuack : public QuackBehavior {
public:
    void quack() override {
        std::cout << " can't make noise " << std::endl;
    }
};


// 鸭子基类
class Duck {
public:
    Duck(std::string type):m_name(type){}

    void swim() {
        std::cout << " I Can Swim ... " << std::endl;
    }

    virtual void display() {
        std::cout << " \n------------------------- \n";
        std::cout << " I'm a " << m_name << " Duck:" << std::endl;
    }

    // 鸭子会飞，怎么飞由飞行行为接口决定
    void performFly() {
        m_pFlyBehavior->fly();
    }

    // 鸭子会叫，怎么叫由叫的行为接口决定
    void performQuack() {
        m_pQuackBehavior->quack();
    }

    // 动态设定飞行行为
    void setFlyBehavior(FlyBehavior* flyBehavior) {
        m_pFlyBehavior = flyBehavior;
    }

    // 动态设定呱呱叫行为
    void setQuackBehavior(QuackBehavior* quackBehavior) {
        m_pQuackBehavior = quackBehavior;
    }

protected:
    FlyBehavior*     m_pFlyBehavior;
    QuackBehavior*   m_pQuackBehavior;

    std::string      m_name;
};

// 美拉诺鸭
class MarlarDuck : public Duck {
public:
    MarlarDuck(std::string type):Duck(type) {
        // 美拉诺鸭会飞，会嘎嘎叫
        m_pFlyBehavior = new FlyWithWings();
        m_pQuackBehavior = new Quack();
    }

    void display() override {
        Duck::display();
    }
};

// 红头鸭
class RedHeadDuck : public Duck {
public:
    RedHeadDuck(std::string type):Duck(type) {
        // 红头鸭会飞，会吱吱叫
        m_pFlyBehavior = new FlyWithWings();
        m_pQuackBehavior = new Squeak();
    }

    void display() override {
        Duck::display();
    }
};

// 橡皮鸭
class RubberDuck : public Duck {
public:
    RubberDuck(std::string type):Duck(type) {
        // 橡皮鸭不会飞，不会叫
        m_pFlyBehavior = new FlyNoWings();
        m_pQuackBehavior = new MuteQuack();
    }

    void display() override {
        Duck::display();
    }
};

// 模型鸭
class ModelDuck : public Duck {
public:
    ModelDuck(std::string type):Duck(type) {
        // 初始时，模型鸭不会飞，也不会叫
        m_pFlyBehavior = new FlyNoWings();
        m_pQuackBehavior = new MuteQuack();
    }
};

void TestDuck() {

    Duck* pduck_1 = new MarlarDuck("Marlar");
    pduck_1->display();
    pduck_1->swim();
    pduck_1->performFly();
    pduck_1->performQuack();

    Duck* pduck_2 = new RedHeadDuck("Red Head");
    pduck_2->display();
    pduck_2->swim();
    pduck_2->performFly();
    pduck_2->performQuack();

    Duck* pduck_3 = new RubberDuck("Rubber");
    pduck_3->display();
    pduck_3->swim();
    pduck_3->performFly();
    pduck_3->performQuack();

    Duck* pduck_4 = new ModelDuck("Model");
    pduck_4->display();
    pduck_4->swim();
    pduck_4->performFly();
    pduck_4->performQuack();

    pduck_4->setFlyBehavior(new FlyWithRocket);
    pduck_4->setQuackBehavior(new Quack);

    std::cout << "\n After a period of improvement .... \n" << std::endl;

    pduck_4->performFly();
    pduck_4->performQuack();

}

int main() {

    TestDuck();

    return 0;
}