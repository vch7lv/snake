#include "Game.h"
#include <cstdlib> 
#include <ctime> 
#include <SFML/Window.hpp>

Direction getOppositeDirection(Direction d) {
    Direction result;
    switch (d) {
        case Direction::DOWN:
            result = Direction::UP;
            break;
        case Direction::UP:
            result = Direction::DOWN;
            break;
        case Direction::LEFT:
            result = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            result = Direction::LEFT;
            break;
    }
    return result;
}

bool Point::operator == (const Point& other) {
    return x == other.x && y == other.y;
}

bool Point::operator != (const Point& other) {
    return !(*this == other);
}

Game::Game(std::size_t width, std::size_t height) : fieldWidth(width), fieldHeight(height) {
    generateNewApple();
    field[snake.back().x][snake.back().y] = 1;
}

int Game::getScore() {
    return snake.size();
}

bool Game::isGameOver() {
    return IS_GAME_OVER;
}

void Game::generateNewApple() {
    srand(time(0));

    Point randomPoint;
    do {
        randomPoint  = Point{rand() % fieldWidth, rand() % fieldHeight};
    } while (snakePoints.count(randomPoint));

    applePoint = randomPoint;
    field[applePoint.x][applePoint.y] = 2;
}

const std::vector<std::vector<char>>& Game::getField() {
    return field;
}

void Game::setDirection(Direction newDirection) {
    if (DirectionChanged) return;
    if (snake.size() > 1 && snakeDirection == getOppositeDirection(newDirection)) return;
    snakeDirection = newDirection;
    DirectionChanged = true;
}

Point Game::getNextPoint() {
    Point nextPoint = snake.front();

    switch (snakeDirection) {
        case Direction::UP :
            --nextPoint.y;
            break;
        case Direction::DOWN :
            ++nextPoint.y;
            break;
        case Direction::LEFT :
            --nextPoint.x;
            break;
        case Direction::RIGHT :
            ++nextPoint.x;
            break;
    }

    if (nextPoint.x == -1) nextPoint.x = fieldWidth-1;
    if (nextPoint.y == -1) nextPoint.y = fieldHeight-1;
    if (nextPoint.x == fieldWidth) nextPoint.x = 0;
    if (nextPoint.y == fieldHeight) nextPoint.y = 0;

    return nextPoint;
}

void Game::moveSnake() {
    auto nextPoint = getNextPoint();

    if (snakePoints.count(nextPoint)) {
        IS_GAME_OVER = true;
        return;
    }

    field[nextPoint.x][nextPoint.y] = 1;
    snakePoints.insert(nextPoint);
    snake.push_front(nextPoint);

    if (nextPoint != applePoint) {
        snakePoints.extract(snake.back());
        field[snake.back().x][snake.back().y] = 0;
        snake.pop_back();
    } else {
        generateNewApple();
        events.push(Event::APPLE_WAS_EATEN);
    }

    DirectionChanged = false;
}

bool Game::isHasEvent() {
    return !events.empty();
}
Event Game::getEvent() {
    auto event = events.front();
    events.pop();
    return event;
};

