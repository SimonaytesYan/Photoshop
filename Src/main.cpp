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
	printf("Button say %s", (char*)args);
}

void Close(void* args)
{
	printf("Close window\n");
	((Window*)(args))->Close();
}

int main()
{
	Font font;
	font.LoadFont("Resources/Font.ttf");
	Texture texture, close;
	close.loadFromFile("Resources/Close.png");
	texture.loadFromFile("Resources/img.png");


	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));

	Window w(Vector(0, 0), Vector(WindowWidth, WindowHeight));
	w.AddObject(new Button(Vector(WindowWidth - 50, 0), Vector(50,  50), close, Close, &w));
	w.AddObject(new Button(Vector(100, 100), Vector(100, 100), texture, Say, (void*)"2\n"));
	w.AddObject(new Button(Vector(200, 200), Vector(100, 100), texture, Say, (void*)"3\n"));
	w.AddObject(new Label(Vector(100, 0),  font, 30));

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
