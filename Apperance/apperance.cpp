
#include <memory>
#include <string>
#include <iostream>

typedef std::string MovieType;

class DVDPlayer {
public:
    void on() {
        std::cout << " Open The DVD Player " << std::endl;
    }

    void off() {
        std::cout << " Close The DVD Player " << std::endl;
    }

    void setSurroundAudio() {
        std::cout << " Set The DVD Surround Audio " << std::endl;
    }

    void stop() {
        std::cout << " Stop The DVD Player " << std::endl;
    }

    void play(MovieType movie) {
        std::cout << " Play The Movie: " << movie << " ~~~~~~~~ " << std::endl;
    }
};

class Screen {
public:
    void down() {
        std::cout << " Put The Screen Down " << std::endl;
    }

    void up() {
        std::cout << " Pull The Screen Up " << std::endl;
    }
};

class Projector {
public:
    void on() {
        std::cout << " Open The Projector " << std::endl;
    }

    void off() {
        std::cout << " Close The Projector " << std::endl;
    }

    void wideScreenMode() {
        std::cout << " Set Fulling Screen Mode " << std::endl;
    }

    void tvMode() {
        std::cout << " Set TV Mode " << std::endl;
    }
};

class Amplifier {
public:
    void on() {
        std::cout << " Open The Amplifier " << std::endl;
    }

    void off() {
        std::cout << " Close The Amplifier " << std::endl;
    }

    void setVolumn(int n) {
        std::cout << " Set The Volumn Is " << n << std::endl;
    }

    void setStereoSound() {
        std::cout << " Set The Amplifier Is Stereo Sound " << std::endl;
    }
};

class HomeTheaterFacade {
public:
    HomeTheaterFacade(DVDPlayer dvd, Screen screen, Projector projector, Amplifier amplifier):m_dvd(dvd),
                                                                                              m_screen(screen),
                                                                                              m_projector(projector),
                                                                                              m_amp(amplifier) {}

    void watchMovie(MovieType movie) {

        m_screen.down();

        m_projector.on();
        m_projector.wideScreenMode();

        m_amp.on();
        m_amp.setStereoSound();
        m_amp.setVolumn(10);

        m_dvd.on();
        m_dvd.play(movie);
    }

    void endMovide() {
        m_screen.up();

        m_projector.off();
        m_amp.off();

        m_dvd.stop();
        m_dvd.off();
    }


private:

    DVDPlayer   m_dvd;
    Screen      m_screen;
    Projector   m_projector;
    Amplifier   m_amp;
};


void TestApperanceMode() {

    DVDPlayer  dvd;
    Screen     screen;
    Projector  projector;
    Amplifier  amplifier;

    HomeTheaterFacade* homeTheaterFacade = new HomeTheaterFacade(dvd, screen, projector, amplifier);

    MovieType movie("The Wolf II");

    homeTheaterFacade->watchMovie(movie);
    homeTheaterFacade->endMovide();
}

int main() {

    TestApperanceMode();
    return 0;
}