#include <SFML/Graphics.hpp>

struct Board : sf::Drawable
{
    int posx;
    int posy;
    int width;
    int height;

    public:
        Board(int posx, int posy, int w, int h, const std::vector<std::vector<char>>& field) 
        : posx(posx), posy(posy), width(w), height(h), field(field)
        {
            int width_in_squares = field.size(); 
            int height_in_squares = field[0].size();

            float rectWidth = (float)width / width_in_squares;
            float rectHeight = (float)height / height_in_squares;

            rects = std::vector<std::vector<sf::RectangleShape>>
            {width_in_squares, std::vector<sf::RectangleShape>(height_in_squares)};

            for (int i = 0; i < width_in_squares; ++i)
            for (int j = 0; j < height_in_squares; ++j)
            {
                sf::RectangleShape r(sf::Vector2f(rectWidth, rectHeight));
                r.setFillColor(sf::Color::White);

                float x = posx + i * rectWidth;
                float y = posy + j * rectHeight;

                r.setPosition(x,y);
                rects[i][j] = std::move(r);
            }
        }

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for (int i = 0; i < field.size(); ++i)
            for (int j = 0; j < field[0].size(); ++j)
            {
                sf::Color color;

                if (field[i][j] == 0) color = sf::Color::Blue;
                if (field[i][j] == 1) color = sf::Color::Green;
                if (field[i][j] == 2) color = sf::Color::Red;

                rects[i][j].setFillColor(color);

                target.draw(rects[i][j], states);
            }
        }
    
    const std::vector<std::vector<char>>& field;
    mutable std::vector<std::vector<sf::RectangleShape>> rects;
};