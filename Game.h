#include <deque>
#include <vector>
#include <set>
#include <queue>

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Point {
    std::size_t x;
    std::size_t y;

    bool operator == (const Point&);
    bool operator != (const Point&);
};

struct Cmp
{
    bool operator () (const Point& lhs, const Point& rhs) const {
        return 1000*lhs.x+lhs.y < 1000*rhs.x+rhs.y;
    }
};

enum class Event {
    APPLE_WAS_EATEN
};

class Game
{
        const std::size_t fieldWidth = 20;
        const std::size_t fieldHeight = 15;

        std::vector<std::vector<char>> field {fieldWidth, std::vector<char>(fieldHeight, 0)};

        std::deque<Point> snake { {{fieldWidth / 2, fieldHeight / 2}} };
        std::set<Point, Cmp> snakePoints {{{fieldWidth / 2, fieldHeight / 2}}};

        Direction snakeDirection {Direction::RIGHT};

        Point applePoint;

        bool IS_GAME_OVER = false;

        std::queue<Event> events;
    private:

        void generateNewApple();
        Point getNextPoint();

    public:

        Game(std::size_t width, std::size_t height);

        void moveSnake();
        int getScore();
        bool isGameOver();
        void setDirection(Direction);
        const std::vector<std::vector<char>>& getField();
        Event getEvent();
        bool isHasEvent();
};

