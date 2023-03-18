#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

std::mt19937 engine;

char randomCharFromString(std::string word) {
    std::uniform_int_distribution<int> dist(0, (int)word.length());
    return word[dist(engine)];
}
static char randomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}


class Matrix {
private:
    sf::RenderWindow window;
    sf::Font mono_font;
    sf::Text character;
    std::string characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM<>?/;:[{}])(&*+=";
    std::vector<int> drops;
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
        //***
        for (int i = 0; i < drops.size(); i++)
        {
            int x = randomInt(0, window.getSize().x);
            int y = randomInt(0, window.getSize().y);
            printf("%d,%d \n", x, y);
            character.setString(randomCharFromString(characters));
            character.setCharacterSize(randomInt(10, row_width));
            character.setPosition(x, y);
            window.draw(character);
        }

        //window.draw(sf::CircleShape(100.f));

        //***
        window.display();
    };
    void update() {

        if (!running)
            window.close();
    };

public:
    Matrix(int width, int height) {
        window.create(sf::VideoMode(width, height, 32), "Matrix", sf::Style::Close);
        window.setFramerateLimit(1);
        row_width = (float)window.getSize().x / 30.f;
        mono_font.loadFromFile("Monocraft.ttf");
        for (size_t i = 0; i < 30; i++) { drops.push_back(0); }
        character.setFont(mono_font);
        character.setFillColor(sf::Color::Green);
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
    Matrix matrix(600, 600);
    matrix.run();

    return 0;
}