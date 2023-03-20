﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>


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


class Matrix {
private:
    sf::RenderWindow window;
    sf::Font mono_font;
    sf::Text character;
    std::string characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM<>?/[{}])(&*+=";
    std::vector<int> drops;
    sf::RectangleShape background;
    float row_width;
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

                default:
                    break;
                }

            }
        }

    }

    void draw() {
        //window.clear();
        window.draw(background);
        //***
        for (int i = 0; i < drops.size(); i++)
        {
            character.setString(randomCharFromString(characters));
            character.setCharacterSize(randomInt(10, row_width));
            character.setPosition(i*row_width+4, drops[i]);
            window.draw(character);
            
            drops[i]+=8;
            if (drops[i] > window.getSize().y) {
                drops[i] = randomInt(0, 400)*-1;
            }
            printf("%d , %d \n", window.getSize().y, drops[i]);
        }


        //***
        window.display();
    };
    void update() {

        if (!running)
            window.close();
    };

public:
    Matrix(int width, int height, float colnum) {
        window.create(sf::VideoMode(width, height, 32), "Matrix", sf::Style::Close);
        window.setFramerateLimit(60);
        row_width = (float)window.getSize().x / colnum;
        if (mono_font.loadFromFile("Monocraft.ttf")) printf("udalo si");
        drops = std::vector<int>(int(colnum), 600);
        character.setFont(mono_font);
        character.setFillColor(sf::Color::Green);
        background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        background.setFillColor(sf::Color(0, 0, 0, 40));
        background.setPosition(0,0);
        running = true;

    };
    ~Matrix() {};

    void run() {
        while (window.isOpen() && running)
        {
            events();
            update();
            draw();
        }
    };

};





int main()
{
    Matrix matrix(600, 600, 40.f);
    matrix.run();

    return 0;
}