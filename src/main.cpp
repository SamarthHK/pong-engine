#include "state_files/umbrella_header.h"
#include <SFML/Graphics.hpp>

using namespace pong::state_files;

int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned screenWidth = desktopMode.size.x;
    unsigned screenHeight = desktopMode.size.y;
    unsigned windowWidth = 640;
    unsigned windowHeight = 480;
    unsigned frameRate = 60;

    sf::Window window(sf::VideoMode({windowWidth, windowHeight}), "pong",sf::Style::Titlebar,sf::State::Windowed);
    window.setFramerateLimit(frameRate);
    window.setTitle("pong");
    window.setPosition(sf::Vector2i((screenWidth - windowWidth)/2, (screenHeight - windowHeight)/2));

    //While the window is open this will run:
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Scancode::Left:
                        window.setPosition(sf::Vector2i(window.getPosition().x -screenWidth/100, window.getPosition().y));
                        break;
                    case sf::Keyboard::Scancode::Right:
                        window.setPosition(sf::Vector2i(window.getPosition().x +screenWidth/100, window.getPosition().y));
                        break;
                    case sf::Keyboard::Scancode::Up:
                        window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y -screenHeight/100));
                        break;
                    case sf::Keyboard::Scancode::Down:
                        window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y +screenHeight/100));
                        break;
                    default:
                        break;
                }
            }

        }

    }

}
