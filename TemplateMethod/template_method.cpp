#include <iostream>

class Beverage {
public:
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