
#include <string>
#include <vector>
#include <iostream>

// 外国籍球员
class Player {
public:
    explicit Player(std::string name):m_name(name){}

    virtual void Attack() = 0;
    virtual void Defense() = 0;

protected:
    std::string     m_name;
};

class Forwards : public Player {
public:
    explicit Forwards(std::string  name):Player(name) {}

    void Attack() override {
        std::cout << " Forward " << m_name << " Attack !!" << std::endl;
    }

    void Defense() override {
        std::cout << " Forward " << m_name << " Defense !!" << std::endl;
    }
};

class Center : public Player {
public:
    explicit Center(std::string name):Player(name) {}

    void Attack() override {
        std::cout << " Center " << m_name << " Attack !!" << std::endl;
    }

    void Defense() override {
        std::cout << " Center " << m_name << " Defense !!" << std::endl;
    }
};

class Guards : public Player {
public:
    explicit Guards(std::string name):Player(name) {}

    void Attack() override {
        std::cout << " Guards " << m_name << " Attack !!" << std::endl;
    }

    void Defense() override {
        std::cout << " Guards " << m_name << " Defense !!" << std::endl;
    }
};


// 中国籍球员
class Chinese_Player {
public:
    explicit Chinese_Player(std::string name):m_name(name) {}

    virtual void Chinese_Attack() = 0;
    virtual void Chinese_Defense() = 0;

protected:
    std::string        m_name;
};

class Chinese_Forwards : public Chinese_Player {
public:
    explicit Chinese_Forwards(std::string name):Chinese_Player(name) {}

    void Chinese_Attack() override {
        std::cout << " Chinese Forward " << m_name << " Attack !!" << std::endl;
    }

    void Chinese_Defense() override {
        std::cout << " Chinese Forward " << m_name << " Defense !!" << std::endl;
    }
};

class Chinese_Center : public Chinese_Player {
public:
    explicit Chinese_Center(std::string name):Chinese_Player(name) {}

    void Chinese_Attack() override {
        std::cout << " Chinese Center " << m_name << " Attack !!" << std::endl;
    }

    void Chinese_Defense() override {
        std::cout << " Chinese Center " << m_name << " Defense !!" << std::endl;
    }
};

class Chinese_Guards : public Chinese_Player {
public:
    explicit Chinese_Guards(std::string name):Chinese_Player(name) {}

    void Chinese_Attack() override {
        std::cout << " Chinese Guards " << m_name << " Attack !!" << std::endl;
    }

    void Chinese_Defense() override {
        std::cout << " Chinese Guards " << m_name << " Defense !!" << std::endl;
    }
};

// 翻译者，即适配器；
class Translator : public Player {
public:
    explicit Translator(Chinese_Player* player):Player(""), m_pCP(player) {}

    void Attack() override {
        m_pCP->Chinese_Attack();
    }

    void Defense() override {
        m_pCP->Chinese_Defense();
    }

private:
    // 被适配者
    Chinese_Player*     m_pCP;
};

void TestAdapter() {

    Player* p1 = new Forwards("巴沙尔");
    p1->Attack();

    Player* p2 = new Guards("乔丹");
    p2->Defense();

    Chinese_Player* pchinese = new Chinese_Center("姚明");
    //pchinese->Chinese_Defense();
    //pchinese->Chinese_Attack();
    Player* yaoming = new Translator(pchinese);

    yaoming->Attack();
    yaoming->Defense();

}
int main() {

    TestAdapter();
    return 0;
}
