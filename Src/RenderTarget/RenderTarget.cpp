#include <string.h>

#include "RenderTarget.h"
#include "../RegionSet/RegionSet.h"
#include "../ClipRegion/ClipRegion.h"
#include "../Constants.h"

//#define DEBUG_REGIONS
Font RenderTarget::standard_font;

sf::Color ConvertColor(plugin::Color color)
{
    return sf::Color(color.r, color.g, color.b, color.a);
}

sf::Vector2f ConvertVecF(plugin::Vec2 vec)
{
    return sf::Vector2f(vec.GetX(), vec.GetY());
}

sf::Vector2i ConvertVecI(plugin::Vec2 vec)
{
    return sf::Vector2i(vec.GetX(), vec.GetY());
}

RenderTarget::RenderTarget(plugin::Vec2 size)
{
    standard_font.LoadFont(kFontFile);
    data.create(size.GetX(), size.GetY()); 
}

void DrawWithRegionSet(const RegionSet& rend_set, sf::RenderTexture& data, 
                                                  sf::RenderTexture& tmp_target)
{
    for (int i = 0; i < rend_set.GetLength(); i++)
    {
        sf::Sprite tmp_sprite(tmp_target.getTexture(), 
                              sf::IntRect(ConvertVecI(rend_set[i].getPosition()), 
                                          ConvertVecI(rend_set[i].getSize())));
        tmp_sprite.setPosition(ConvertVecF(rend_set[i].getPosition()));

        data.draw(tmp_sprite);
    }
}

void RenderTarget::DrawCircle(plugin::Vec2 position, double r, plugin::Color color, const RegionSet& rend_set)
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

void RenderTarget::DrawRect(plugin::Vec2 position, plugin::Vec2 size, 
                            const RegionSet& rend_set, plugin::Color fill_color,
                            int border_size, plugin::Color border_color)
{
    RegionSet rect_set;
    rect_set.AddRegion(ClipRegion(plugin::Vec2(position.GetX(),
                                         position.GetY()),
                                  plugin::Vec2(size.GetX(),
                                         size.GetY())));
    rect_set &= rend_set;
    #ifdef DEBUG_REGIONS
        DrawRegionSet(rect_set, fill_color, (size_t)&rend_set >> 3);
    #else
        DrawRegionSet(rect_set, fill_color);
        RegionSet border_set;
        border_set.AddRegion(ClipRegion(position,
                                        plugin::Vec2(border_size, size.GetY())));      //left

        border_set.AddRegion(ClipRegion(position,
                                        plugin::Vec2(size.GetX(), border_size)));      //down

        border_set.AddRegion(ClipRegion(plugin::Vec2((position + size).GetX() - border_size,
                                        position.GetY()),
                                        plugin::Vec2(border_size, size.GetY())));      //right

        border_set.AddRegion(ClipRegion(plugin::Vec2(position.GetX(),
                                        (position + size).GetY() - border_size),
                                        plugin::Vec2(size.GetX(), border_size)));      //up

        border_set &= rend_set;
        DrawRegionSet(border_set, border_color);
    #endif
}

Texture RenderTarget::GetTexture()
{
    return Texture(data.getTexture());
}

plugin::Texture* RenderTarget::getTexture()
{
    sf::Image img = data.getTexture().copyToImage();

    plugin::Texture* texture = new plugin::Texture();
    texture->width  = img.getSize().x;
    texture->height = img.getSize().y;

    size_t number_pixels = img.getSize().x * img.getSize().y;
    texture->pixels = new plugin::Color[number_pixels];
    memcpy(texture->pixels, img.getPixelsPtr(), sizeof(plugin::Color) * number_pixels);

    return texture;
}

void RenderTarget::display(sf::RenderWindow* window)
{
    data.display();

    sf::Sprite sprite(data.getTexture());
	sprite.setPosition(0, 0);

    window->draw(sprite);
}

void RenderTarget::display()
{
    data.display();
}

void RenderTarget::DrawSprite(plugin::Vec2 position, Texture texture, const RegionSet& rend_set)
{
    #ifdef DEBUG_REGIONS
        RegionSet result;
        result.AddRegion(ClipRegion(position, texture.getSize()));

        result &= rend_set;

        DrawRegionSet(result, plugin::Color(0, 0, 0, 255), 1);
    #else
        sf::Sprite sprite(*texture.GetTexture());
        sprite.setPosition(position.GetX(), position.GetY());

        sf::RenderTexture tmp_target;
        tmp_target.create(data.getSize().x, data.getSize().y);
        tmp_target.clear(sf::Color::Transparent);
        tmp_target.draw(sprite);
        tmp_target.display();

        DrawWithRegionSet(rend_set, data, tmp_target);
    #endif
}

bool InsideP(plugin::Vec2 v, plugin::Vec2 position, plugin::Vec2 size)
{
    return v.GetX() - position.GetX() > 0           &&
           v.GetX() - position.GetX() < size.GetX() &&
           v.GetY() - position.GetY() > 0           && 
           v.GetY() - position.GetY() < size.GetY();
}

void RenderTarget::SetPixel(plugin::Vec2 position, plugin::Color color, const RegionSet& rend_set)
{
    sf::RectangleShape shape(sf::Vector2f(1, 1));
    shape.setPosition(position.GetX(), position.GetY());
    shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

    for (int i = 0; i < rend_set.GetLength(); i++)
    {
        if (InsideP(position, rend_set[i].getPosition(), rend_set[i].getSize()))
        {
            data.draw(shape);
            return;
        }
    }
}

void RenderTarget::DrawText(plugin::Vec2 position, Font font, const char* text, 
                            int character_size, plugin::Color color, 
                            const RegionSet& rend_set)
{
    #ifdef DEBUG_REGIONS
        RegionSet result;
        result.AddRegion(ClipRegion(position, plugin::Vec2(character_size * strlen(text), character_size + 10)));

        result &= rend_set;

        DrawRegionSet(result, plugin::Color(0, 0, 0, 255), 1);
    #else
        sf::Text label;

        label.setFillColor(ConvertColor(color));
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
    #endif
}

plugin::Color ChooseDebugColor(size_t color_type, int index)
{
    switch (color_type % 2)
    {
        case 0:
        {
            switch (index % 4)
            {
                case 0:
                    return plugin::Color(255, 0, 0, 128);
                case 1:
                    return plugin::Color(255, 0, 125, 128);
                case 2:
                    return plugin::Color(255,  0, 255, 128);
                case 3:
                    return plugin::Color(150, 0, 255, 128);

                default:
                    return plugin::Color(0, 0, 0);
            }
            break;
        }
        case 1:
        {
            switch (index % 4)
            {
                case 0:
                    return plugin::Color(0, 255, 0, 128);
                case 1:
                    return plugin::Color(125, 255, 0, 128);
                case 2:
                    return plugin::Color(255, 255, 0, 128);
                case 3:
                    return plugin::Color(255, 125, 0, 128);

                default:
                    return plugin::Color(0, 0, 0);
            }
            break;
        }

        default:
            switch (index % 4)
            {
                case 0:
                    return plugin::Color(255, 0, 0, 128);
                case 1:
                    return plugin::Color(0, 255, 0, 128);
                case 2:
                    return plugin::Color(0,  0, 255, 128);
                case 3:
                    return plugin::Color(255, 255, 255, 128);

                default:
                    return plugin::Color(0, 0, 0);
            }
    }
}

void RenderTarget::DrawRegionSet(const RegionSet& reg_set, plugin::Color color, size_t color_type)
{
    for (int i = 0; i < reg_set.GetLength(); i++)
    {
        sf::RectangleShape rect(ConvertVecF(reg_set[i].getSize()));
        rect.setPosition(ConvertVecF(reg_set[i].getPosition()));

        #ifdef DEBUG_REGIONS
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(2);
            
            rect.setFillColor(ConvertColor(ChooseDebugColor(color_type, i)));
        #else
            rect.setFillColor(ConvertColor(color));
        #endif        

        data.draw(rect);
    }

    data.display();
}

void RenderTarget::clear()
{
    data.clear();
}

void RenderTarget::clear(plugin::Color color)
{
    data.clear(ConvertColor(color));
}

void RenderTarget::SetPixel(plugin::Vec2 position, plugin::Color color)
{
    sf::RectangleShape shape(sf::Vector2f(1, 1));
    shape.setPosition(position.GetX(), position.GetY());
    shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

    data.draw(shape);
}

void RenderTarget::DrawCircle(plugin::Vec2 position, double r, plugin::Color color, plugin::Vec2 scale)
{
    sf::CircleShape circle(r);
    circle.setPosition(sf::Vector2f(position.GetX(), position.GetY()));
    circle.setFillColor(sf::Color(color.r, color.g, color.b));
    circle.setScale(ConvertVecF(scale));

    data.draw(circle);
}

void RenderTarget::DrawLine(plugin::Vec2 v0, plugin::Vec2 v1, plugin::Color color)
{
    sf::Vertex line[] =
    {
        sf::Vertex(ConvertVecF(v0)),
        sf::Vertex(ConvertVecF(v1))
    };
    line[0].color = ConvertColor(color);
    line[1].color = ConvertColor(color);

    data.draw(line, 2, sf::Lines);
}

void RenderTarget::DrawRect(plugin::Vec2 position, plugin::Vec2 size,
                            plugin::Color fill_color,
                            int border_size, plugin::Color border_color)
{
    sf::RectangleShape rect(ConvertVecF(size));
    rect.setPosition(ConvertVecF(position));
    rect.setFillColor(ConvertColor(fill_color));

    rect.setOutlineColor(ConvertColor(border_color));
    rect.setOutlineThickness(border_size);

    data.draw(rect);
}

void RenderTarget::DrawSprite(plugin::Vec2 position, Texture texture)
{
    sf::Sprite sprite(*texture.GetTexture());
    sprite.setPosition(position.GetX(), position.GetY());

    data.draw(sprite);
}

void RenderTarget::DrawText(plugin::Vec2 position, Font font, const char* text, 
                            int character_size, plugin::Color color)
{
    sf::Text label;

    label.setFillColor(ConvertColor(color));
    label.setFont(*font.GetFont());
    label.setCharacterSize(character_size);
    label.setPosition(position.GetX(), position.GetY());
    label.setString(text); 

    data.draw(label);
}

void RenderTarget::setPixel(plugin::Vec2 pos, plugin::Color color)
{ 
    SetPixel(pos, color); 
}

void RenderTarget::drawLine(plugin::Vec2 point1, plugin::Vec2 point2, plugin::Color color)
{ 
    DrawLine(point1, point2, color); 
}

void RenderTarget::drawRect(plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color)
{ 
    DrawRect(pos, size, color); 
}

void RenderTarget::drawEllipse(plugin::Vec2 pos, plugin::Vec2 size, plugin::Color color)
{ 
    DrawCircle(pos, size.x, color, plugin::Vec2(1, size.y / size.x));  
}

void RenderTarget::drawText(plugin::Vec2 pos, const char *content, 
                 uint16_t char_size, plugin::Color color)
{ 
    DrawText(pos, standard_font, content, char_size, color); 
}

void RenderTarget::drawTexture(plugin::Vec2 pos, plugin::Vec2 size, 
                               const plugin::Texture *texture)
{
    Image img;
    img.Create(size.x, size.y);
    memcpy(img.GetPixelArray(), 
           texture->pixels, 
           size.x * size.y * sizeof(plugin::Color));

    Texture my_texture;
    my_texture.LoadFromImage(img);

    DrawSprite(pos, my_texture);
}