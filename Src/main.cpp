#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Resources.h"
#include "EventManager/EventManager.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Canvas/Canvas.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Menu/Menu.h"
#include "Renderable/Widget/Window/Window.h"
#include "Renderable/Widget/Window/ModalWindow.h"
#include "RegionSet/RegionSet.h"
#include "ClipRegion/ClipRegion.h"
#include "Tool/Brush/Brush.h"
#include "Tool/ShapeTool/CircleTool/CircleTool.h"
#include "Tool/ShapeTool/RectTool/RectTool.h"
#include "Tool/ShapeTool/LineTool/LineTool.h"
#include "Tool/PolylineTool/PolylineTool.h"
#include "Tool/SplineTool/SplineTool.h"
#include "Tool/FillTool/FillTool.h"
#include "Renderable/Widget/Menu/HorizontalMenu/HorizontalMenu.h"
#include "Renderable/Widget/Menu/VerticalMenu/VerticalMenu.h"
#include "Filter/Filter.h"
#include "Filter/BrightnessFilter/BrightnessFilter.h"

const char   kWindowHeader[] = "Photoshop";
const int    kMaxTextLength  = 50;
size_t       WindowWidth     = 0;
size_t       WindowHeight    = 0;

struct ToolStruct
{
	ToolManager* tm;
	Tool*		 tool;
};

struct ColorStruct
{
	ToolManager* tm;
	Color		 color;
};

struct FilterStruct
{
	FilterManager* fm;
	Filter*        filter;
};

void TestRegClip(RenderTarget& rend_targ);
void AddMenu(Window* window, Canvas* canvas, FilterManager* fm);
void AddTools(Window* main_window, Window* tool,   ToolManager* tm);
void AddColors(Window* main_window, Window* colors, ToolManager* tm);

void Say(void* args);
void SwitchTool(void* args);
void SwitchColor(void* args);
void SelectFilter(void* args);
void ClearCanvas(void* args);

int main()
{
	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));

	Window main_window(Vector(0, 0), 
					   Vector(WindowWidth, WindowHeight), "Window1");

	FilterManager fm;
	ToolManager   tm;

	Window canvas_window1(Vector(100, 100), Vector(1200, 850), "Canvas1");
	Canvas canvas(Vector(110, 160), Vector(1180, 780), &tm, &fm);
	canvas_window1.AddObject(&canvas);
	main_window.AddObject(&canvas_window1);

	Window canvas_window2(Vector(900, 150), Vector(500, 550), "Canvas2");
	Canvas canvas2(Vector(910, 210), Vector(480, 480), &tm, &fm);
	canvas_window2.AddObject(&canvas2);
	main_window.AddObject(&canvas_window2);

	// Adding tools	
	Window tools(Vector(1400, 450), 
			  	  Vector(500, 300), "Tools");
	AddTools(&main_window, &tools, &tm);

	// Adding colors
	Window colors(Vector(1400, 150), 
			  	  Vector(500, 300), "Colors");
	AddColors(&main_window, &colors, &tm);	
	AddMenu(&main_window, &canvas, &fm);

	EventManager event_manager;
	event_manager.AddObject(&main_window);

	ModalWindow notification(Vector(100, 100), Vector(500, 300), "Notification", &event_manager);

	main_window.AddObject(&notification);

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
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.OnMousePress({position, (MouseKey)event.mouseButton.button});
					break;
				}
				
				case sf::Event::MouseMoved:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.OnMouseMove(MouseCondition(position, (MouseKey)1));
					break;
				}
				
				case sf::Event::MouseButtonReleased:
				{
					Vector position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.OnMouseRelease({position, (MouseKey)event.mouseButton.button});
					break;
				}
			}
		}
		main_window.Render(&rend_targ);

		#ifdef DEBUG
			TestRegClip(rend_targ);
		#endif

		rend_targ.Display(&window);
		window.display();
	}
}

void SwitchColor(void* args)
{
	ColorStruct* cs = (ColorStruct*)args;

	cs->tm->ChangeColor(cs->color);
}

void SwitchTool(void* args)
{
	ToolStruct* ts = (ToolStruct*)args;
	ts->tm->ChangeTool(ts->tool);
}

void ClearCanvas(void* args)
{
	((Canvas*)args)->Clear();
}

void AddTools(Window* main_window, Window* tools, ToolManager* tm)
{
	const int ToolsNumber = 7;
	ToolStruct* ts = new ToolStruct[ToolsNumber];
	ts[0] = {tm, (Tool*)(new Brush(10))};
	ts[1] = {tm, (Tool*)(new CircleTool(10))},
	ts[2] = {tm, (Tool*)(new RectTool(10))},
	ts[3] = {tm, (Tool*)(new LineTool)},
	ts[4] = {tm, (Tool*)(new PolylineTool)},
	ts[5] = {tm, (Tool*)(new FillTool)};
	ts[6] = {tm, (Tool*)(new SplineTool(10))};

	const char* textures[ToolsNumber] = 
	{
		kBrushImgFile,
		kCircleImgFile,
		kRectImgFile,
		kLineImgFile,
		kPolylineImgFile,
		kFillImgFile,
		kSplineImgFile,
	};

	const char* press_textures[ToolsNumber] = 
	{
		kBrushPressedImgFile,
		kCirclePressedImgFile,
		kRectPressedImgFile,
		kLinePressedImgFile,
		kPolylinePressedImgFile,
		kFillPressedImgFile,
		kSplinePressedImgFile,
	};

	Texture common_texture, pressed_texture;

	for (int i = 0; i < ToolsNumber; i++)
	{
		common_texture.LoadFromFile(textures[i]);
		pressed_texture.LoadFromFile(press_textures[i]);
		tools->AddObject(new Button(tools->GetPosition() + Vector(10 + 50 * i, 50), 
								   Vector(50, 50), 
							   	   common_texture, pressed_texture, 
							   	   SwitchTool, &ts[i]));
	}

	main_window->AddObject(tools);
}

void AddColors(Window* main_window, Window* colors, ToolManager* tm)
{
	const int colors_num   = 5;
	Color     all_colors[] = {Color(255, 255, 255),
						 	  Color(0,     0,   0),
						 	  Color(255,   0,   0),
						 	  Color(0,   255,   0),
						 	  Color(0,     0, 255),};

	ColorStruct* cs = new ColorStruct[colors_num];
	for (int i = 0; i < colors_num; i++)
	{
		cs[i].color       = all_colors[i];
		cs[i].tm          = tm;

		Vector position = colors->GetPosition() + Vector(10 + 50 * i, 50);
		colors->AddObject(new Button(position, Vector(50, 50), all_colors[i], 
								  	 SwitchColor, &cs[i]));
	}

	main_window->AddObject(colors);
}

void AddMenu(Window* window, Canvas* canvas, FilterManager* fm)
{
	Font font;
	font.LoadFont(kFontFile);
	Texture texture, press_texture;
	texture.LoadFromFile(kBackgroundImgFile);
	press_texture.LoadFromFile(kBackgroundPressedImgFile);

	Button* file_button = new Button(Vector(10, 50), Vector(100, 50), 
									 texture, press_texture, 
									 Say, nullptr);
	file_button->AddObject(new Label(Vector(25, 60), font, 20, 
									 "File", Color(199, 181, 173)));

	Button* clear_button = new Button(Vector(110, 50),  Vector(100, 50), 
									  texture, press_texture, 
									  ClearCanvas, canvas);
	clear_button->AddObject(new Label(Vector(135, 60), font, 20, 
									  "Clear", Color(199, 181, 173)));
	
	window->AddObject(file_button);
	window->AddObject(clear_button);
	
	Button* filter_button = new Button(Vector(210, 50),  Vector(100, 50), 
									  texture, press_texture, 
									  nullptr, nullptr);
	filter_button->AddObject(new Label(Vector(235, 60), font, 20, 
									  "Filter", Color(199, 181, 173)));

	VerticalMenu* filters = new VerticalMenu(filter_button, false);

	FilterStruct* fs = new FilterStruct();
	fs->fm     = fm;
	fs->filter = new BrightnessFilter();
	Button* select_filter_button = new Button(Vector(0, 0),  Vector(100, 50), 
									  texture, press_texture, 
									  SelectFilter, fs);
	select_filter_button->AddObject(new Label(Vector(25, 10), font, 20, 
									   "Brightness", Color(199, 181, 173)));

	filters->AddObject(select_filter_button);

	window->AddObject(filters);
}

void SelectFilter(void* _args)
{
	FilterStruct* args = (FilterStruct*)_args;
	args->fm->SetFilter(args->filter);
}

void Say(void* args)
{
	printf("Open file\n");
}
