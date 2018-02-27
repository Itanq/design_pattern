
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

// 单例模式的最简单也最具性能的实现
class Single {
public:
    static Single* getInstance() {
        // c++11保证static静态变量的初始化是线程安全的。
        static Single instance;
        return &instance;
    }

    void printSingleAddress() {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << " This Thread ID Is    : " << std::this_thread::get_id() << std::endl;
        std::cout << " Address Of The Single: " << this << std::endl;
        std::cout << std::endl;
    }

private:
    std::mutex m_mutex;

private:
    Single() {}
    Single(const Single& single) = delete;
    const Single& operator = (const Single& single) = delete;
};

void TestSingle() {

    std::vector<std::thread> vecs(10);
    for(int i=0; i<10; ++i) {
        vecs.emplace_back([](){
            Single *pInstance = Single::getInstance();
            pInstance->printSingleAddress();
        });

    }

    Single* pInstance = Single::getInstance();
    pInstance->printSingleAddress();

    for(auto& item : vecs) if(item.joinable())
            item.join();
}


// 单例的使用双重检查机制实现。
class Single2 {
public:
    static Single2* getInstance() {
        // 双重锁定确保线程安全和性能
        if(m_pInstance == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            // 再次判断是否为空，因为此处有两个线程到达。
            if(m_pInstance == nullptr) {
                m_pInstance = new Single2();
            }
        }
        return m_pInstance;
    }

    void printSingleAddress() {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << " This Thread ID Is    : " << std::this_thread::get_id() << std::endl;
        std::cout << " Address Of The Single: " << this << std::endl;
        std::cout << std::endl;
    }

private:
    static std::mutex    m_mutex;
    static Single2*      m_pInstance;

private:
    Single2(){}
    Single2(const Single2& single2) = delete;
    Single2&operator = (const Single2& single2) = delete;

private:
    // 实现单例的内存自动释放的机制。
    // 也可再定义个静态的释放内存的函数。
    class AutoGC {
    public:
        ~AutoGC() {
            if(m_pInstance) {
                std::cout << " delete m_pinstance.." << std::endl;
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
        static AutoGC GC;
    };
};

std::mutex Single2::m_mutex;
Single2* Single2::m_pInstance = nullptr;

// 在全局位置初始化一个静态变量事项内存自动清理。
Single2::AutoGC Single2::AutoGC::GC;

void TestSingle2() {

    std::vector<std::thread> vecs(10);
    for(int i=0; i<10; ++i) {
        vecs.emplace_back([](){
            Single2 *pInstance = Single2::getInstance();
            pInstance->printSingleAddress();
        });

    }

    Single2* pInstance = Single2::getInstance();
    pInstance->printSingleAddress();

    for(auto& item : vecs) if(item.joinable())
            item.join();
}

int main() {
    //TestSingle();
    TestSingle2();
    return 0;
}
