#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Window/Window.h"

const char kWindowHeader[] = "Sphere";
const int  kMaxTextLength  = 50;
int WindowWidth  = 0;
int WindowHeight = 0;

void Say(void* args)
{
	fprintf(stderr, "Button say %s", (char*)args);
}

int main()
{
	Texture texture, close;
	close.LoadFromFile("Resources/Close.png");
	texture.LoadFromFile("Resources/img.png");


	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));

	Window w(Vector(0, 0), Vector(WindowWidth, WindowHeight), "Window1");
	Window w2(Vector(WindowWidth/2, WindowHeight/2), 
			  Vector(WindowWidth/3, WindowHeight/3), "Window2");

	w.AddObject(&w2);
	//w.AddObject(new Button(Vector(100, 100), Vector(100, 100), texture, Say, (void*)"2\n"));
	//w.AddObject(new Button(Vector(200, 200), Vector(100, 100), texture, Say, (void*)"3\n"));

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
					Vector position(event.mouseButton.x,
									event.mouseButton.y);
					w.OnMousePress({position, (MouseKey)event.mouseButton.button});
				}
			}
		}

		rend_targ.Clear();
		window.clear();
		w.Render(&rend_targ);

		rend_targ.Display(&window);

		window.display();
	}
}
