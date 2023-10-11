#include "RenderTarget.h"
#include "../RegionSet/RegionSet.h"
#include "../ClipRegion/ClipRegion.h"

sf::Color ConvertColor(Color color)
{
    return sf::Color(color.r, color.g, color.b, color.a);
}

sf::Vector2f ConvertVecF(Vector vec)
{
    return sf::Vector2f(vec.GetX(), vec.GetY());
}

sf::Vector2i ConvertVecI(Vector vec)
{
    return sf::Vector2i(vec.GetX(), vec.GetY());
}

RenderTarget::RenderTarget(Vector size)
{
    data.create(size.GetX(), size.GetY()); 
}

void DrawWithRegionSet(const RegionSet& rend_set, sf::RenderTexture& data, 
                                                  sf::RenderTexture& tmp_target)
{
    for (int i = 0; i < rend_set.GetLength(); i++)
    {
        sf::Sprite tmp_sprite(tmp_target.getTexture(), 
                              sf::IntRect(ConvertVecI(rend_set[i].GetPosition()), 
                                          ConvertVecI(rend_set[i].GetSize())));
        tmp_sprite.setPosition(ConvertVecF(rend_set[i].GetPosition()));

        data.draw(tmp_sprite);
    }
}

void RenderTarget::DrawCircle(Vector position, double r, Color color, const RegionSet& rend_set)
{
    sf::CircleShape circle(r);
    circle.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
    circle.setFillColor(sf::Color(color.r, color.g, color.b));

    sf::RenderTexture tmp_target;
    tmp_target.create(data.getSize().x, data.getSize().y);
    tmp_target.clear(sf::Color::Transparent);
    tmp_target.draw(circle);
    tmp_target.display();

    DrawWithRegionSet(rend_set, data, tmp_target);
}

void RenderTarget::DrawRect(Vector position, Vector size, 
                            const RegionSet& rend_set, Color fill_color,
                            int border_size, Color border_color)
{
    RegionSet rect_set;
    rect_set.AddRegion(ClipRegion(Vector(position.GetX(),
                                         position.GetY()),
                                  Vector(size.GetX(),
                                         size.GetY())));
    rect_set &= rend_set;
    DrawRegionSet(rect_set, fill_color);

    RegionSet border_set;
    border_set.AddRegion(ClipRegion(Vector(position.GetX(),
                                           position.GetY()),
                                    Vector(border_size, size.GetY())));      //left

    border_set.AddRegion(ClipRegion(Vector(position.GetX(),
                                           position.GetY()),
                                    Vector(size.GetX(), border_size)));      //down

    border_set.AddRegion(ClipRegion(Vector((position + size).GetX() - border_size,
                                            position.GetY()),
                                    Vector(border_size, size.GetY())));      //right

    border_set.AddRegion(ClipRegion(Vector(position.GetX(),
                                           (position + size).GetY() - border_size),
                                    Vector(size.GetX(), border_size)));      //up

    DrawRegionSet(border_set, border_color);
}

void RenderTarget::Display(sf::RenderWindow* window)
{
    data.display();

    sf::Sprite sprite(data.getTexture());
	sprite.setPosition(0, 0);

    window->draw(sprite);
}

void RenderTarget::DrawSprite(Vector position, Texture texture, const RegionSet& rend_set)
{
    sf::Sprite sprite(*texture.GetTexture());
    sprite.setPosition(position.GetX(), position.GetY());

    sf::RenderTexture tmp_target;
    tmp_target.create(data.getSize().x, data.getSize().y);
    tmp_target.clear(sf::Color::Transparent);
    tmp_target.draw(sprite);
    tmp_target.display();

    DrawWithRegionSet(rend_set, data, tmp_target);
}

bool InsideP(Vector v, Vector position, Vector size)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}

void RenderTarget::SetPixel(Vector position, Color color, const RegionSet& rend_set)
{
    sf::RectangleShape shape(sf::Vector2f(1, 1));
    shape.setPosition(position.GetX(), position.GetY());
    shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

    for (int i = 0; i < rend_set.GetLength(); i++)
    {
        if (InsideP(position, rend_set[i].GetPosition(), rend_set[i].GetSize()))
        {
            data.draw(shape);
            return;
        }
    }

}

void RenderTarget::DrawText(Vector position, Font font, const char* text, 
                            int character_size, const RegionSet& rend_set)
{
    sf::Text label;

    label.setFont(*font.GetFont());
    label.setCharacterSize(character_size);
    label.setPosition(position.GetX(), position.GetY());
    label.setString(text); 

    sf::RenderTexture tmp_target;
    tmp_target.create(data.getSize().x, data.getSize().y);
    tmp_target.clear(sf::Color::Transparent);
    tmp_target.draw(label);
    tmp_target.display();

    DrawWithRegionSet(rend_set, data, tmp_target);
}

void RenderTarget::DrawRegionSet(const RegionSet& reg_set, Color color)
{
    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        sf::RectangleShape rect(ConvertVecF(reg_set[i].GetSize()));
        rect.setFillColor(ConvertColor(color));
        rect.setPosition(ConvertVecF(reg_set[i].GetPosition()));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);

        data.draw(rect);
    }

    data.display();
}

void RenderTarget::Clear()
{
    data.clear();
}
