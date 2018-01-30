#include <vector>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <algorithm>


class SubJect;

// 观察者抽象接口类
class Observer {
public:
    explicit Observer(std::shared_ptr<SubJect> subject):m_subject(subject){}

    virtual void update(int temprature, int humidity, int pressure) = 0;

protected:
    std::shared_ptr<SubJect>    m_subject;
};

// 主题抽象接口类，即被观察者
class SubJect {
public:
    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObserver() = 0;

protected:
    std::vector<std::shared_ptr<Observer>>      m_observerVec;
};

// 其中一个具体的主题类
class WeatherData : public SubJect {
public:
    // 观察者注册主题，以便可以获得数据变化
    void registerObserver(std::shared_ptr<Observer> observer)  override {
        m_observerVec.push_back(observer);
    }

    // 观察者取消注册
    void removeObserver(std::shared_ptr<Observer> observer) override {
        auto pos = std::find(m_observerVec.cbegin(), m_observerVec.cend(), observer);
        if(pos != m_observerVec.end())
            m_observerVec.erase(pos);
        else
            std::cout << " No The Observer " << std::endl;
    }

    // 通知所有观察者，状态改变
    void notifyObserver() override {
        m_temperature = getTemperature();
        m_humidity = getHumidity();
        m_pressure = getPressure();
        std::cout << " set: " << m_temperature << " " << m_humidity << " " << m_pressure << std::endl;
        for(auto& item : m_observerVec)
            item->update(m_temperature, m_humidity, m_pressure);
    }

    // 此函数在数据更新时会自动调用
    void measurementsChanged() {
        notifyObserver();
    }

    // 此函数模拟气象站数据采集的过程
    void setMeasurements() {

        m_temperature = rand() % 45;
        m_humidity = rand() % 35;
        m_pressure = rand() % 100;

        std::cout << " set: " << m_temperature << " " << m_humidity << " " << m_pressure << std::endl;
        measurementsChanged();
    }

    int getTemperature() {
        return m_temperature;
    }

    int getHumidity() {
        return m_humidity;
    }

    int getPressure() {
        return m_pressure;
    }

private:
    int     m_temperature;
    int     m_humidity;
    int     m_pressure;
};

// 显示板抽象接口类
class DisplayElement {
public:
    virtual void display() = 0;
};

// 当前状况显示板
class CurrentConditionsDisplay : public Observer, public DisplayElement {
public:
    explicit CurrentConditionsDisplay(std::shared_ptr<SubJect> subject):Observer(subject) {
        m_subject->registerObserver(std::shared_ptr<Observer>(this));
    }

    void update(int temprature, int humidity, int pressure) override {
        m_temperature = temprature;
        m_humidity = humidity;
        m_pressure = pressure;
        display();
    }

    void display() override {
        std::cout << "\n ------------------------- \n" << std::endl;
        std::cout << " THE CURRENT CONDITIONS DISPLY: " << std::endl;
        std::cout << " TEMPERATURE  : " << m_temperature << std::endl;
        std::cout << " HUMIDITY     : " << m_humidity << std::endl;
        std::cout << " PRESSURE     : " << m_pressure << std::endl;
    }

private:
    int         m_temperature;
    int         m_humidity;
    int         m_pressure;
};

// 统计屏显示板
class StatisticsDisplay : public Observer, public DisplayElement {
public:
    explicit StatisticsDisplay(std::shared_ptr<SubJect> subject):Observer(subject) {
        m_subject->registerObserver(std::shared_ptr<Observer>(this));
    }
    void update(int temprature, int humidity, int pressure) override {
        m_temperature = temprature;
        m_humidity = humidity;
        m_pressure = pressure;
        display();
    }

    void display() override {
        std::cout << "\n ------------------------- \n" << std::endl;
        std::cout << " THE STATISTICS DISPLY: " << std::endl;
        std::cout << " TEMPERATURE  : " << m_temperature << std::endl;
        std::cout << " HUMIDITY     : " << m_humidity << std::endl;
        std::cout << " PRESSURE     : " << m_pressure << std::endl;
    }



private:
    int         m_temperature;
    int         m_humidity;
    int         m_pressure;
};

// 天气预测显示板
class ForecastDisplay : public Observer, public DisplayElement {
public:
    explicit ForecastDisplay(std::shared_ptr<SubJect> subject):Observer(subject) {
        m_subject->registerObserver(std::shared_ptr<Observer>(this));
    }

    void update(int temprature, int humidity, int pressure) override {
        m_temperature = temprature;
        m_humidity = humidity;
        m_pressure = pressure;
        display();
    }

    void display() override {
        std::cout << "\n ------------------------- \n" << std::endl;
        std::cout << " THE FORECAST Display DISPLY: " << std::endl;
        std::cout << " TEMPERATURE  : " << m_temperature << std::endl;
        std::cout << " HUMIDITY     : " << m_humidity << std::endl;
        std::cout << " PRESSURE     : " << m_pressure << std::endl;
    }

private:
    int         m_temperature;
    int         m_humidity;
    int         m_pressure;
};

void TestSubJectObserver() {

    std::shared_ptr<WeatherData> pWD1(new WeatherData);

    // 如下三个观察者构造的时候即注册了主题　WeatherData
    // 主题WeatherData数据更新的时候会自动通知观察者
    CurrentConditionsDisplay* pCCD1 = new CurrentConditionsDisplay(pWD1);
    StatisticsDisplay* pSD1 = new StatisticsDisplay(pWD1);
    ForecastDisplay* pFD1 = new ForecastDisplay(pWD1);

    for(int i=0; i<5; ++i) {
        pWD1->setMeasurements();
    }
}

int main() {

    TestSubJectObserver();

    return 0;
}