#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Board.h"
#include <cmath>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(820, 620), "Snake");

    Game game{16, 12};
    Board board(10,10,800,600, game.getField());
    sf::Clock clock;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("eat.wav")) {
        std::cout << "srgwreg";
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    while (!game.isGameOver())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::W) game.setDirection(Direction::UP);
                    if (event.key.code == sf::Keyboard::S) game.setDirection(Direction::DOWN);
                    if (event.key.code == sf::Keyboard::A) game.setDirection(Direction::LEFT);
                    if (event.key.code == sf::Keyboard::D) game.setDirection(Direction::RIGHT);
                    break;
            }
        }

        auto time = clock.getElapsedTime();
        if (time.asSeconds() >= 0.2f) {
            game.moveSnake();
            clock.restart();
        }

        while (game.isHasEvent())
        {
            switch(game.getEvent()) {
                case Event::APPLE_WAS_EATEN :
                    sound.play();
                    break;
            }
        }

        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}