
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// 产品基类
class Pizza {
public:
    virtual void prepare() {
        std::cout << " Preparing " << m_name << std::endl;
        std::cout << " Tossing dough ..." << std::endl;
        std::cout << " Adding  sauce ..." << std::endl;
        std::cout << " Adding Toppings: " << std::endl;
        for(const auto& item : m_toppings) {
            std::cout << " " << item;
        }
        std::cout << std::endl;
    }

    virtual void bake() {
        std::cout << " Bake for 25 minutes at 350 " << std::endl;
    }

    virtual void cut() {
        std::cout << " Cutting the pizza into DIAGONAL slices " << std::endl;
    }

    virtual void box() {
        std::cout << " Place pizza in official PizzaStore box " << std::endl;
    }

protected:
    std::string         m_name="Unkown";
    std::string         m_dough="";
    std::string         m_sauce="";
    std::vector<std::string>    m_toppings;
};

// 具体产品子类
class NYStyleChessePizza : public Pizza {
public:
    NYStyleChessePizza() {
        m_name = "New York Style Sauce and Chesse Pizza";
        m_dough = "Thin Crust Dough";
        m_sauce = "Marinara Sauce";
        m_toppings.push_back("Grated Reggiano Chesse");
    }
};

// 产品基类
class NYStyleClamPizza : public Pizza {
public:
    NYStyleClamPizza() {
        m_name = "New York Style Sauce and Clam Pizza";
        m_dough = "Thin Crust Dough";
        m_sauce = "Marinara Sauce";
        m_toppings.push_back("Grated Reggiano Chesse");
    }
};

// 产品基类
class ChicagoStyleChessePizza : public Pizza {
public:
    ChicagoStyleChessePizza() {
        m_name = "Chicago Style Deep Dish Cheese Pizza";
        m_dough = "Extra Thick Crust Dough";
        m_sauce = "Plum Tomato Sauce";
        m_toppings.push_back("Shredded Mozzarella Chesse");
    }

    // 　重写Cut方法，Chicago风味切成方形。
    void cut() override {
        std::cout << " Cutting the pizza into SQUARE slices " << std::endl;
    }
};

// 产品基类
class ChicagoStyleVeggiePizza : public Pizza {
public:
    ChicagoStyleVeggiePizza() {
        m_name = "Chicago Style Deep Dish Veggie Pizza";
        m_dough = "Extra Thick Crust Dough";
        m_sauce = "Plum Tomato Sauce";
        m_toppings.push_back("Shredded Mozzarella Chesse");
    }

    // 　重写Cut方法，Chicago风味切成方形。
    void cut() override {
        std::cout << " Cutting the pizza into SQUARE slices " << std::endl;
    }
};

// 工厂基类
class PizzaStore {
public:
    void orderPizza(std::string type) {
        // 具体创建何种比萨，由子类决定。
        m_pizza = createPizza(type);

        //
        m_pizza->prepare();
        m_pizza->bake();
        m_pizza->cut();
        m_pizza->box();
    }

protected:
    virtual std::shared_ptr<Pizza> createPizza(std::string type) = 0;

private:
    std::shared_ptr<Pizza>      m_pizza;
};

// 具体工厂子类
class NYStylePizzaStore : public PizzaStore {
public:
    std::shared_ptr<Pizza> createPizza(std::string type) override {
        if(type == "chesse")
            return std::shared_ptr<Pizza>(new NYStyleChessePizza());
        else if (type == "clam")
            return std::shared_ptr<Pizza>(new NYStyleClamPizza());
    }
};

// 具体工厂子类
class ChicagoStylePizzaStore : public PizzaStore {
public:
    std::shared_ptr<Pizza> createPizza(std::string type) override {
        if(type == "chesse")
            return std::shared_ptr<Pizza>(new ChicagoStyleChessePizza());
        else if(type == "veggie")
            return std::shared_ptr<Pizza>(new ChicagoStyleVeggiePizza());
    }
};

void TestFactoryMethod() {

    PizzaStore* nyPizzaStore = new NYStylePizzaStore();
    PizzaStore* chicagoPizzaStore = new ChicagoStylePizzaStore();

    // 订一份纽约风味的chesse比萨
    nyPizzaStore->orderPizza("chesse");
    std::cout << "\n" << std::endl;
    // 订一份纽约风味的clam比萨
    nyPizzaStore->orderPizza("clam");

    std::cout << "\n <<==========================>>\n" << std::endl;

    // 订一份芝加哥风味的chesse比萨
    chicagoPizzaStore->orderPizza("chesse");
    std::cout << "\n" << std::endl;
    // 订一份芝加哥风味的clam比萨
    chicagoPizzaStore->orderPizza("veggie");
}


int main() {
    TestFactoryMethod();
    return 0;
}
