
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

// 命令的实际执行者，不需要知道具体的命令发起者是谁，
// 和命令的发起者解耦了。
class Barbecure {
public:
    void BakeMutton() {
        std::cout << " 烤羊肉 " << std::endl;
    }

    void BakeChickenWing() {
        std::cout << " 烤鸡翅 " << std::endl;
    }
};

// 命令对象
class Command {
public:
    explicit Command(Barbecure* barbecure):m_receiver(barbecure) {}
    virtual void execute() = 0;
    virtual std::string getName() = 0;

protected:
    // 抽象命令类，需要知道命令执行者是谁，不需要知道如何执行
    Barbecure*   m_receiver;
};

class BakeMuttonCommand : public Command {
public:
    explicit BakeMuttonCommand(Barbecure* barbecure):Command(barbecure) {}

    void execute() override {
        m_receiver->BakeMutton();
    }

    std::string getName() override {
        return "羊肉串";
    }
};

class BakeChickenWingCommand : public Command {
public:
    explicit BakeChickenWingCommand(Barbecure* barbecure):Command(barbecure) {}

    void execute() override {
        m_receiver->BakeChickenWing();
    }

    std::string getName() override {
        return "鸡翅";
    }
};


// 命令的发起者，和命令的执行者解耦了，
// 不需要知道具体由谁执行这些命令
class Waiter {
public:
    void setCommand(Command* cmd) {
        m_pCmd.emplace_back(cmd);
    }

    void cancelOrder(Command* cmd) {

        auto pos = std::find(m_pCmd.begin(), m_pCmd.end(), cmd);
        if(pos != m_pCmd.end()) {
            std::cout << "取消订单： " << cmd->getName() << std::endl;
            m_pCmd.erase(pos);
        }
        else
            std::cout << " 没有此订单信息" << std::endl;
    }

    void Notify() {
        for(const auto& item : m_pCmd)
            item->execute();
    }

private:
    std::vector<Command*>  m_pCmd;
};


void TestCommand() {

    // 具体执行者
    Barbecure* barbecure = new Barbecure();

    // 一系列需要执行的命令
    BakeChickenWingCommand* cmd1 = new BakeChickenWingCommand(barbecure); // 具体由barbecure执行
    BakeChickenWingCommand* cmd2 = new BakeChickenWingCommand(barbecure);
    BakeMuttonCommand* cmd3 = new BakeMuttonCommand(barbecure);
    BakeMuttonCommand* cmd4 = new BakeMuttonCommand(barbecure);

    // 命令发起者
    Waiter* girl = new Waiter();

    girl->setCommand(cmd1);
    girl->setCommand(cmd2);
    girl->setCommand(cmd3);
    girl->setCommand(cmd4);

    // 通知命令执行者执行命令
    girl->Notify();

    // 取消一串烤羊肉
    girl->cancelOrder(cmd4);

    girl->Notify();

    delete cmd1;
    delete cmd2;
    delete cmd3;
    delete cmd4;
    delete girl;
    delete barbecure;
}

int main() {

    TestCommand();
    return 0;
}
