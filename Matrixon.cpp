#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <fstream>


char randomCharFromString(std::string word) {
    static std::mt19937 engine;
    std::uniform_int_distribution<int> dist(0, (int)word.length());
    return word[dist(engine)];
}
int randomInt(int min, int max) {
    static std::mt19937 engine;
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

void changeConsole(bool f)
{
    if (!f) {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }
    else if (f) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    }

}


class Matrix {
private:
    sf::RenderWindow window;
    sf::Font mono_font;
    sf::Text character;
    std::string characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM<>?/[{}])(&*+=";
    std::vector<int> drops;
    sf::RectangleShape background;
    sf::RenderTexture brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla;
    float col_width;
    bool running;


    void events() {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                running = false;

            case sf::Event::KeyPressed:

            default:
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {

                case sf::Keyboard::Escape:
                    running = false;

                case sf::Keyboard::R:
                    if (IsWindowVisible(GetConsoleWindow())) {
                        window.requestFocus();
                    }
                    else {
                        changeConsole(true);
                    }
                    

                default:
                    break;
                }

            }
        }

    }

    void draw() {
        window.clear();

        brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.draw(background);
        for (int i = 0; i < drops.size(); i++)
        {
            character.setString(randomCharFromString(characters));
            character.setPosition(i*col_width+1, drops[i]);
            character.setFillColor(sf::Color(0, 255, 0, 255));
            brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.draw(character);
            
            drops[i]+=character.getCharacterSize();

            if (drops[i] > brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.getSize().y) {
                drops[i] = randomInt(0, 400)*-1;
            }
            printf("%d , %d \n", window.getSize().x, drops.size());
        }

        sf::Sprite bufor_tla_ale_sprite_bo_inaczej_nie_dziala(brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.getTexture());
        bufor_tla_ale_sprite_bo_inaczej_nie_dziala.rotate(180.f);
        bufor_tla_ale_sprite_bo_inaczej_nie_dziala.move(window.getSize().x, window.getSize().y);

        window.draw(bufor_tla_ale_sprite_bo_inaczej_nie_dziala);


        //***
        window.display();
    };
    void update() {
        
        draw();

        if (!running)
            window.close();
    };

public:
    Matrix(int width, int height) {
        window.create(sf::VideoMode(width, height, 32), "Matrixon", sf::Style::Close);
        window.setFramerateLimit(20);
        col_width = 20;
        if (mono_font.loadFromFile("Monocraft.ttf")) printf("mom spaghetti");
        drops = std::vector<int>(width/col_width, 0);
        character.setFont(mono_font);
        character.setFillColor(sf::Color::Green);
        character.setStyle(sf::Text::Bold);
        character.setCharacterSize(col_width);
        background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        background.setFillColor(sf::Color(0, 0, 0, 40));
        background.setPosition(0,0);
        brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.create(width, height);
        brak_pomyslu_na_nazwe_ale_to_jest_bufor_tla.setSmooth(true);
        running = true;

    };
    ~Matrix() {};

    void run() {
        while (window.isOpen() && running)
        {
            events();
            update();
        }
    };

};





int main()
{
    changeConsole(false);
    Matrix matrix(800, 900);
    matrix.run();

    return 0;
}