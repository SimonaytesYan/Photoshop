#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Widget.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 1000;
const int  kMaxTextLength  = 50;

void Say(void* args)
{
	printf("Button say %s", (char*)args);
}

int main()
{
	Widget w;

	w.AddObject(new Button(Vector(0, 0),     Vector(100, 100), Color(255, 0, 0), Say, (void*)"1\n"));
	w.AddObject(new Button(Vector(100, 100), Vector(100, 100), Color(255, 0, 0), Say, (void*)"2\n"));
	w.AddObject(new Button(Vector(200, 200), Vector(100, 100), Color(255, 0, 0), Say, (void*)"3\n"));

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

				case sf::Event::MouseButtonPressed:
				{
					Vector position(event.mouseButton.x,
									event.mouseButton.y);
					w.OnMousePress({position, (MouseKey)event.mouseButton.button});
				}
			}
		}

		w.Render(&rend_targ);

		rend_targ.Display(&window);

		window.display();
	}
}
