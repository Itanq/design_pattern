
#include <string>
#include <memory>
#include <iostream>

// 装饰者和被装饰者的公共基类。
class Beverage {
public:
    explicit Beverage():m_name("unkonw") {}

    virtual std::string getDescription() { return m_name; }

    virtual float cost() = 0;

protected:
    std::string     m_name;
};

// 下面四个是被装饰者。
class HouseBlend : public Beverage {
public:
    explicit HouseBlend() {
        m_name = " House Blend";
    }

    float cost() override { return 7.85; }
};

class DarkRoast : public Beverage {
public:
    explicit DarkRoast() {
        m_name = " DarkRoast";
    }

    float cost() override { return 4.67; }
};

class Espresso : public Beverage {
public:
    explicit Espresso() {
        m_name = " Espresso";
    }

    float cost() override { return 5.85; }
};

class Decaf : public Beverage {
public:
    explicit Decaf() {
        m_name = " Decaf";
    }

    float cost() override { return 5.67; }
};


// 装饰者抽象类
class CondimentDecorator : public Beverage {
public:
    explicit CondimentDecorator(Beverage* beverage):m_pBeverage(beverage) {}

    // 所有的调料装饰者类都必须重新实现此方法
    virtual std::string getDescription() override = 0;

protected:
    // 装饰者抽象类需要一个示例变量保存被装饰者。
    std::shared_ptr<Beverage>   m_pBeverage;
};

// 装饰者具体类
class Milk : public CondimentDecorator {
public:
    explicit Milk(Beverage* beverage):CondimentDecorator(beverage) {}

    std::string getDescription() override {
        return m_pBeverage->getDescription() + " + Milk";
    }

    float cost() override {
        return m_pBeverage->cost() + 1.24;
    }
};


class Mocha : public CondimentDecorator {
public:
    explicit Mocha(Beverage* beverage):CondimentDecorator(beverage) {}

    std::string getDescription() override {
        return m_pBeverage->getDescription() + " + Mocha";
    }

    float cost() override {
        return m_pBeverage->cost() + 2.24;
    }
};


class Soy : public CondimentDecorator {
public:
    explicit Soy(Beverage* beverage):CondimentDecorator(beverage) {}

    std::string getDescription() override {
        return m_pBeverage->getDescription() + " + Soy";
    }

    float cost() override {
        return m_pBeverage->cost() + 0.24;
    }
};


class Whip : public CondimentDecorator {
public:
    explicit Whip(Beverage* beverage):CondimentDecorator(beverage) {}

    std::string getDescription() override {
        return m_pBeverage->getDescription() + " + Whip";
    }

    float cost() override {
        return m_pBeverage->cost() + 1.44;
    }
};


void TestDecorator() {

    auto DisplayBeverage = [](Beverage* p) {
        std::cout << " \n ------------------------------- \n" << std::endl;
        std::cout << p->getDescription();
        std::cout << " It Cost: " << p->cost() << std::endl;
    };

    std::cout << " \n---------------------------\n" << std::endl;
    std::cout << "  HouseBlen Cost  : " << 7.85 << std::endl;
    std::cout << "  DarkRoast Cost  : " << 4.67 << std::endl;
    std::cout << "  Espresso Cost   : " << 5.85 << std::endl;
    std::cout << "  Decaf Cost      : " << 5.67 << std::endl;
    std::cout << " \n---------------------------\n" << std::endl;
    std::cout << "  Milk Cost       : " << 1.24 << std::endl;
    std::cout << "  Mocha Cost      : " << 2.24 << std::endl;
    std::cout << "  Soy  Cost       : " << 0.24 << std::endl;
    std::cout << "  Whip Cost       : " << 1.44 << std::endl;
    std::cout << " \n---------------------------\n" << std::endl;

    Beverage* p1 = new Espresso(); // 顶一杯Espresso，不需要任何调料
    DisplayBeverage(p1);

    p1 = new Mocha(p1);   // 同样订一杯Espresso,加两倍Mocha,再放点Soy和Whip。
    p1 = new Mocha(p1);
    p1 = new Soy(p1);
    p1 = new Whip(p1);
    DisplayBeverage(p1);

    Beverage* p2 = new DarkRoast(); // 订一杯加Mocha,Whip的DarRoast饮料
    p2 = new Mocha(p2);
    p2 = new Whip(p2);
    DisplayBeverage(p2);
}


int main() {
    TestDecorator();
    return 0;
}