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

void RenderTarget::DrawSprite(Vector position, Texture texture)
{
    sf::Sprite sprite(*texture.GetTexture());
    sprite.setPosition(position.GetX(), position.GetY());

    data.draw(sprite);
}

void RenderTarget::SetPixel(Vector position, Color color)
{
    sf::RectangleShape shape(sf::Vector2f(1, 1));
    shape.setPosition(position.GetX(), position.GetY());
    shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    
    data.draw(shape);
}

void RenderTarget::DrawText(Vector position, Font font, const char* text, int character_size)
{
    sf::Text label;

    label.setFont(*font.GetFont());
    label.setCharacterSize(character_size);
    label.setPosition(position.GetX(), position.GetY());
    label.setString(text); 

    data.draw(label);
}

void RenderTarget::Clear()
{
    data.clear();
}
