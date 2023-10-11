#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Resources.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Window/Window.h"
#include "Renderable/Widget/Menu/Menu.h"
#include "RegionSet/RegionSet.h"
#include "ClipRegion/ClipRegion.h"

const char   kWindowHeader[] = "Photoshop";
const int    kMaxTextLength  = 50;
size_t       WindowWidth     = 0;
size_t       WindowHeight    = 0;

void TestRegClip(RenderTarget& rend_targ);
void Say(void* args);
void AddMenu(Window* window);

int main()
{
	Texture texture, close;
	close.LoadFromFile("Resources/Close.png");
	texture.LoadFromFile("Resources/img.png");

	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));
	
	TestRegClip(rend_targ);

	Window main_window(Vector(WindowWidth/2, WindowHeight/2), 
					   Vector(WindowWidth/3, WindowHeight/3), "Window1");
	
	Window sub_window(Vector(WindowWidth/2 + 50, WindowHeight/2 + 50), 
			  		  Vector(WindowWidth/6, WindowHeight/6), "Window2");

	main_window.AddObject(&sub_window);
	// AddMenu(&main_window);

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
					main_window.OnMouseMove(MouseCondition(position, (MouseKey)event.mouseButton.button));
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
	RegionSet r1, r2, r3;

	r1.AddRegion(ClipRegion(Vector(0, 0), Vector(300, 300)));

	r2.AddRegion(ClipRegion(Vector(0, 0), Vector(50, 300)));

	r2 &= r1;
	//r3 -= r2;

	//rend_targ.DrawRegionSet(r1, 1);
	rend_targ.DrawRegionSet(r2, Color(255, 0, 0));
	
	#ifdef DEBUG
		rend_targ.DrawRegionSet(r2, 2);

		r1 -= r2;
	
		printf("------------------\n");
		r1.Dump();

	rend_targ.DrawRegionSet(r1, 0);
	#endif
}

void Say(void* args)
{
	fprintf(stderr, "Button say %s", (char*)args);
}

void AddMenu(Window* window)
{
	Menu* menu = new Menu();

	Font font;
	font.LoadFont(kFontFile);
	Texture texture;
	texture.LoadFromFile(kBackgroundImgFile);

	Button* file_button = new Button(Vector(0, 50), Vector(100, 50), texture);
	file_button->AddObject(new Label(Vector(25, 60), font, 20, "File"));
	menu->AddObject(file_button);

	window->AddObject(menu);
}
