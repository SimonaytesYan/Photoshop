#include "RenderTarget.h"
#include "../RegionSet/RegionSet.h"
#include "../ClipRegion/ClipRegion.h"

sf::Color ConvertColor(Color color)
{
    return sf::Color(color.r, color.g, color.b, color.a);
}

sf::Vector2f ConvertVec(Vector vec)
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

void RenderTarget::DrawRect(Vector position, Vector size, Color fill_color,
                            int border_size, Color border_color)
{
    sf::RectangleShape rect(ConvertVec(size));
    rect.setPosition(ConvertVec(position));
    rect.setFillColor(ConvertColor(fill_color));

    rect.setOutlineColor(ConvertColor(border_color));
    rect.setOutlineThickness(border_size);

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

void RenderTarget::DrawRegionSet(const RegionSet& reg_set, int color_type)
{
    Color* colors = (Color*)calloc(sizeof(Color), reg_set.GetLength());
    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        switch (color_type)
        {
        case 0:
            colors[i] = Color(0,
                              255/(reg_set.GetLength() + 1) * (i + 1),
                              0, 
                              128);
            break;
        
        case 1:
            colors[i] = Color(0,
                              0,
                              255/(reg_set.GetLength() + 1) * (i + 1), 
                              128);
            break;

        case 2:
            colors[i] = Color(255/(reg_set.GetLength() + 1) * (i + 1),
                              0,
                              0, 
                              128);
            break;
        }
    }

    for (int i = 0; i < reg_set.GetLength(); i++)
    {        
        DrawRect(reg_set[i].GetPosition() * 100, 
                 reg_set[i].GetSize() * 100, colors[i], 2);
    }

    free(colors);
}

void RenderTarget::Clear()
{
    data.clear();
}
