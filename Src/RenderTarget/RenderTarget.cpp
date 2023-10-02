#include "RenderTarget.h"

sf::Color ColorToColor(Color color)
{
    return sf::Color(color.r, color.g, color.b);
}

sf::Vector2f VecToVec(Vector vec)
{
    return sf::Vector2f(vec.GetX(), vec.GetY());
}

RenderTarget::RenderTarget(Vector size)
{
    data.create(size.GetX(), size.GetY()); 
}

void RenderTarget::DrawCircle(Vector position, double r, Color color)
{
    sf::CircleShape circle(r);
    circle.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
    circle.setFillColor(sf::Color(color.r, color.g, color.b));

    data.draw(circle);
}

void RenderTarget::DrawRect(Vector position, Vector size, Color fill_color)
{
    sf::RectangleShape rect(VecToVec(size));
    rect.setPosition(VecToVec(position));
    rect.setFillColor(ColorToColor(fill_color));

    data.draw(rect);
}

void RenderTarget::Display(sf::RenderWindow* window)
{
    data.display();

    sf::Sprite sprite(data.getTexture());
	sprite.setPosition(0, 0);

    window->draw(sprite);
}
