#include <iostream>

class Beverage {
public:
    // 定义一个算法的框架。
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiment();
    }

    void boilWater() {
        std::cout << " Boiling Water ... " << std::endl;
    }

    void pourInCup() {
        std::cout << " Pouring Into Cup ... " << std::endl;
    }

    // 延迟到子类中实现
    // 使得在不改变算法结构的前提下，
    // 可以重新定义算法中的某些步骤。
    virtual void brew() = 0;
    virtual void addCondiment() = 0;
};

class Tea : public Beverage {
public:
    void brew() override {
        std::cout << " Steeping The Tea " << std::endl;
    }
    void addCondiment() {
        std::cout << " Adding Sugar And Milk ..." << std::endl;
    }
};

class Coffee : public Beverage {
public:
    void brew() override {
        std::cout << " Dripping Coffee Through Filter ..." << std::endl;
    }
    void addCondiment() {
        std::cout << " Adding Sugar And Milk ..." << std::endl;
    }
};


void TestTemplateMethod() {

    Tea* tea = new Tea();
    tea->prepareRecipe();

    Coffee* coffee = new Coffee();
    coffee->prepareRecipe();
};

int main() {

    TestTemplateMethod();
    return 0;
}