#include "state_files/umbrella_header.h"
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace pong::state_files;

int main()
{


    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned screenWidth = desktopMode.size.x;
    unsigned screenHeight = desktopMode.size.y;
    unsigned windowWidth = 640;
    unsigned windowHeight = 480;
    unsigned frameRate = 60;

    pong::Game game = pong::Game(10,10,100,windowWidth,windowHeight,80,1.5f,10.0f,1.0f,0.1f);

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "pong",sf::Style::Titlebar,sf::State::Windowed);
    window.setFramerateLimit(frameRate);
    window.setTitle("pong");
    window.setPosition(sf::Vector2i((screenWidth - windowWidth)/2, (screenHeight - windowHeight)/2));

    //While the window is open this will run:
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        pong::StepResult step_result = game.step(pong::Move::DOWN, pong::Move::DOWN);

        sf::CircleShape ball(game.ball.radius);
        ball.setFillColor(sf::Color::Yellow);
        ball.setPosition(sf::Vector2f(step_result.ball_x, step_result.ball_y));
        window.draw(ball);

        sf::RectangleShape paddleOne(sf::Vector2f(game.player_one.width, game.player_one.height));
        paddleOne.setFillColor(sf::Color::Blue);
        paddleOne.setPosition(sf::Vector2f(step_result.player_one_x, step_result.player_one_y-game.player_one.height/2));
        window.draw(paddleOne);

        sf::RectangleShape paddleTwo(sf::Vector2f(game.player_two.width, game.player_two.height));
        paddleTwo.setFillColor(sf::Color::Red);
        paddleTwo.setPosition(sf::Vector2f(step_result.player_two_x, step_result.player_two_y-game.player_two.height/2));
        window.draw(paddleTwo);

        window.display();
        }

}


