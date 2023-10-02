#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Widget.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 1000;
const int  kMaxTextLength  = 50;

int main()
{
	Widget w;

	w.AddObject(new Button(Vector(0, 0),     Vector(100, 100), Color(255, 0, 0)));
	w.AddObject(new Button(Vector(100, 100), Vector(100, 100), Color(255, 0, 0)));
	w.AddObject(new Button(Vector(200, 200), Vector(100, 100), Color(255, 0, 0)));

	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	RenderTarget rend_targ(Vector(kWindowSize, kWindowSize));

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
			}
		}

		w.Render(&rend_targ);

		rend_targ.Display(&window);

		window.display();
	}
}
