
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

class Execute {
public:
    virtual void on() = 0;
    virtual void off() = 0;
};

// 命令的实际执行者
class Light : public Execute {
public:
    explicit Light(std::string pos): m_name(pos){}
    void on() override {
        std::cout << m_name << " Light ON " << std::endl;
    }
    void off() override {
        std::cout << m_name << " Light OFF" << std::endl;
    }

private:
    std::string     m_name;
};

class GarageDoor : public Execute {
public:
    void on() override {
        std::cout << " Garage Door ON " << std::endl;
    }
    void off() override {
        std::cout << " Garage Door OFF" << std::endl;
    }
};

// 命令对象
class Command {
public:
    explicit Command(Execute* execute):m_pExe(execute) {}

    virtual void execute() = 0;
    virtual void undo() = 0;

protected:
    Execute*  m_pExe;
};

class NoCommand : public Command {
public:
    explicit NoCommand(Execute* execute1= nullptr):Command(execute1) {}
    void execute() override {
    }
    void undo() override {
    }
};

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(Execute* execute):Command(execute) {}

    void execute() override {
        m_pExe->on();
    }

    void undo() override {
        m_pExe->off();
    }
};


class LightOffCommand : public Command {
public:
    explicit LightOffCommand(Execute* execute):Command(execute) {}

    void execute() override {
        m_pExe->off();
    }

    void undo() override {
        m_pExe->on();
    }
};

class GarageDoorOnCommand : public Command {
public:
    explicit GarageDoorOnCommand(Execute* execute1):Command(execute1) {}

    void execute() override {
        m_pExe->on();
    }

    void undo() override {
        m_pExe->off();
    }
};

class GarageDoorOffCommand : public Command {
public:
    explicit GarageDoorOffCommand(Execute* execute1):Command(execute1) {}

    void execute() override {
        m_pExe->off();
    }

    void undo() override {
        m_pExe->off();
    }
};

// 命令的发起者
class RemoteControl {
public:
    explicit RemoteControl(int slots=7) {
        m_pOnCmd.resize(slots);
        m_pOffCmd.resize(slots);
        NoCommand* cmd = new NoCommand();
        for(int i=0; i<7; ++i) {
            m_pOnCmd[i] = cmd;
            m_pOffCmd[i] = cmd;
        }
    }
    void setCommand(int slot, Command* onCmd, Command* offCmd) {
        m_pOnCmd[slot] = onCmd;
        m_pOffCmd[slot] = offCmd;
    }

    void onButtonWasPushed(int slot) {
        m_pOnCmd[slot]->execute();
        m_preCmd = m_pOffCmd[slot];
    }

    void offButtonWasPushed(int slot) {
        m_pOffCmd[slot]->execute();
        m_preCmd = m_pOffCmd[slot];
    }

    void undoButtonWasPushed() {
        m_preCmd->undo();
    }

    void onAll() {
        for(const auto& item : m_pOnCmd)
            item->execute();
    }

    void offAll() {
        for(const auto& item : m_pOffCmd)
            item->execute();
    }

private:
    Command*    m_preCmd;
    std::vector<Command*>   m_pOnCmd;
    std::vector<Command*>   m_pOffCmd;
};

void TestCommand() {

    // 控制灯开光的命令实际执行者
    Light* living_room_light = new Light("Living Room");
    Light* kitchen = new Light("Kitchen");
    // 控制大门开光的命令实际执行者
    GarageDoor* garageDoor = new GarageDoor();

    // 创建开光卧室灯的命令
    LightOnCommand* p_on_livingroom_light = new LightOnCommand(living_room_light);
    LightOffCommand* p_off_livingroom_light = new LightOffCommand(living_room_light);

    // 创建开光厨房灯的命令
    LightOnCommand* p_on_kitchen_light = new LightOnCommand(kitchen);
    LightOffCommand* p_off_kitchen_light = new LightOffCommand(kitchen);

    // 创建开关大门的命令
    GarageDoorOnCommand* p_on_garagedoor = new GarageDoorOnCommand(garageDoor);
    GarageDoorOffCommand* p_off_garagedoor = new GarageDoorOffCommand(garageDoor);

    // 创建一个遥控器对象，即命令的发起者。
    RemoteControl* pRc1 = new RemoteControl();

    pRc1->setCommand(0, p_on_livingroom_light, p_off_livingroom_light);
    pRc1->setCommand(1, p_on_kitchen_light, p_off_kitchen_light);
    pRc1->setCommand(2, p_on_garagedoor, p_off_garagedoor);

    pRc1->onButtonWasPushed(0); //　开卧室灯
    pRc1->offButtonWasPushed(0);//　关卧室灯

    pRc1->offButtonWasPushed(1); // 关厨房灯
    pRc1->undoButtonWasPushed(); // 撤销上一次执行的命令　

    pRc1->onButtonWasPushed(2); //开大门
    pRc1->offButtonWasPushed(2); //关大门

    std::cout<<"\nxxxxxxxxxxxxxxxx\n"<<std::endl;

    // 一键打开所有开关
    pRc1->onAll();
    std::cout<<"\nxxxxxxxxxxxxxxxx\n"<<std::endl;

    // 一键关闭所有开关
    pRc1->offAll();

}

int main() {
    TestCommand();
    return 0;
}