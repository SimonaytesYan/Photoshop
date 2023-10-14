#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Resources.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Canvas/Canvas.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Menu/Menu.h"
#include "Renderable/Widget/Window/Window.h"
#include "RegionSet/RegionSet.h"
#include "ClipRegion/ClipRegion.h"
#include "Tool/Brush/Brush.h"

const char   kWindowHeader[] = "Photoshop";
const int    kMaxTextLength  = 50;
size_t       WindowWidth     = 0;
size_t       WindowHeight    = 0;

struct ToolStruct
{
	ToolManager* tm;
	Tool*		 tool;
};

void TestRegClip(RenderTarget& rend_targ);
void Say(void* args);
void SwitchTool(void* args);
void AddMenu(Window* window);

int main()
{
	Texture brush_text, brush_pressed;
	brush_text.LoadFromFile(kBrushImgFile);
	brush_pressed.LoadFromFile(kBrushPressedImgFile);

	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));

	Window main_window(Vector(0, 0), 
					   Vector(WindowWidth, WindowHeight), "Window1");
	
	Window colors(Vector(1400, 150), 
			  	  Vector(500, 300), "Colors");
	Window tools(Vector(1400, 450), 
			  	  Vector(500, 300), "Tools");

	ToolManager tm;
	Brush brush(10);
	ToolStruct ts = {&tm, (Tool*)&brush};
	tools.AddObject(new Button(tools.GetPosition() + Vector(10, 50), Vector(50, 50), 
							   brush_text, brush_pressed, 
							   SwitchTool, &ts));

	Canvas canvas(Vector(100, 150), Vector(1200, 800), &tm);

	main_window.AddObject(&canvas);
	main_window.AddObject(&colors);
	main_window.AddObject(&tools);
	AddMenu(&main_window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}

				case sf::Event::MouseButtonPressed:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					main_window.OnMousePress({position, (MouseKey)event.mouseButton.button});
					break;
				}
				
				case sf::Event::MouseMoved:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					main_window.OnMouseMove(MouseCondition(position, (MouseKey)1));
					break;
				}
				
				case sf::Event::MouseButtonReleased:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					main_window.OnMouseRelease({position, (MouseKey)event.mouseButton.button});
					break;
				}
			}
		}

		rend_targ.Clear();
		window.clear();
		main_window.Render(&rend_targ);

		#ifdef DEBUG
			TestRegClip(rend_targ);
		#endif

		rend_targ.Display(&window);

		window.display();
	}
}

void TestRegClip(RenderTarget& rend_targ)
{
}

void SwitchTool(void* args)
{
	printf("Switch tool\n");
	ToolStruct* ts = (ToolStruct*)args;
	ts->tm->ChangeTool(ts->tool);
}

void AddMenu(Window* window)
{
	Font font;
	font.LoadFont(kFontFile);
	Texture texture, press_texture;
	texture.LoadFromFile(kBackgroundImgFile);
	press_texture.LoadFromFile(kBackgroundPressedImgFile);

	Button* file_button = new Button(Vector(10, 50), Vector(100, 50), texture, press_texture, Say, nullptr);
	file_button->AddObject(new Label(Vector(25, 60), font, 20, "File"));

	window->AddObject(file_button);
}

void Say(void* args)
{
	printf("Open file\n");
}
