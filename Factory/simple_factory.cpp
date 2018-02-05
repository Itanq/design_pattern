#include <memory>
#include <iostream>

class Pizza {
public:
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
};

class ChessePizza : public Pizza {
public:
    void prepare() override {
        std::cout << " Chesse Pizza Prepare .." << std::endl;
    }

    void bake() override {
        std::cout << " Chesse Pizza Bake    .." << std::endl;
    }

    void cut() override {
        std::cout << " Chesse Pizza Cut     .." << std::endl;
    }

    void box() override {
        std::cout << " Chesse Pizza Box     .." << std::endl;
    }
};

class VeggiePizza : public Pizza {
public:
    void prepare() override {
        std::cout << " Veggie Pizza Prepare .." << std::endl;
    }

    void bake() override {
        std::cout << " Veggie Pizza Bake    .." << std::endl;
    }

    void cut() override {
        std::cout << " Veggie Pizza Cut     .." << std::endl;
    }

    void box() override {
        std::cout << " Veggie Pizza Box     .." << std::endl;
    }
};

class ClamPizza : public Pizza {
public:
    void prepare() override {
        std::cout << "  Clam Pizza Prepare .." << std::endl;
    }

    void bake() override {
        std::cout << "  Clam Pizza Bake    .." << std::endl;
    }

    void cut() override {
        std::cout << "  Clam Pizza Cut     .." << std::endl;
    }

    void box() override {
        std::cout << "  Clam Pizza Box     .." << std::endl;
    }
};

class PepperoniPizza : public Pizza {
public:
    void prepare() override {
        std::cout << "  Pepperoni Pizza Prepare .." << std::endl;
    }

    void bake() override {
        std::cout << "  Pepperoni Pizza Bake    .." << std::endl;
    }

    void cut() override {
        std::cout << "  Pepperoni Pizza Cut     .." << std::endl;
    }

    void box() override {
        std::cout << "  Pepperoni Pizza Box     .." << std::endl;
    }
};

class SimplePizzaFactory {
public:
    Pizza* createPizza(std::string type) {
        if(type == "chesse") {
            return new ChessePizza();
        }
        else if (type == "veggie") {
            return new VeggiePizza();
        }
        else if (type == "clam") {
            return new ClamPizza();
        }
        else if (type == "pepperoni") {
            return new PepperoniPizza();
        }
    }
};

class PizzaStore {
public:
    explicit PizzaStore(SimplePizzaFactory factory) {
        m_factory = factory;
    }

    void orderPizza(std::string type) {

        m_pizza.reset(m_factory.createPizza(type));

        m_pizza->prepare();
        m_pizza->bake();
        m_pizza->cut();
        m_pizza->box();
    }

private:
    std::shared_ptr<Pizza>          m_pizza;
    SimplePizzaFactory              m_factory;
};

void TestSimpleFactory() {

    SimplePizzaFactory factory;
    PizzaStore _store = PizzaStore(factory);

    std::cout << " \n\n Order a Chesse Pizza: " << std::endl;
    _store.orderPizza("chesse");

    std::cout <<" \n\n Order A Pepperoni Pizza: " << std::endl;
    _store.orderPizza("pepperoni");

    std::cout <<" \n\n Order A Clam Pizza: " << std::endl;
    _store.orderPizza("clam");
}

int main() {
    TestSimpleFactory();
    return 0;
}