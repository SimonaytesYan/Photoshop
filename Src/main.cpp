#include <SFML/Graphics.hpp>
#include <assert.h>
#include <dlfcn.h>

#include "Standart/PluginStandart.h"
#include "List.h"
#include "Stopwatch.h"
#include "Functors.h"
#include "Constants.h"
#include "EventManager/EventManager.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/ScrollBar/ScrollBar.h"
#include "Renderable/Widget/Canvas/Canvas.h"
#include "Renderable/Widget/EditBox/EditBox.h"
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
#include "Filter/BlackAndWhiteFilter/BlackAndWhiteFilter.h"
#include "Renderable/Widget/RectangleWidget/RectangleWidget.h"

void TestRegClip(RenderTarget& rend_targ);
void AddMenu(Widget* root, Window* window, Canvas* canvas, 
			FilterManager* fm, ToolManager* tm, EventManager* em);
void AddTools(Window* main_window, Window* tool,   ToolManager* tm);
void AddColors(Window* main_window, Window* colors, ToolManager* tm);

typedef plugin::Plugin* (*GetInstanceType)(plugin::App *app);

void LoadPlugins()
{
	void* dll_plugin = dlopen("Plugins/PluginLol.so", RTLD_NOW || RTLD_LOCAL || RTLD_NOLOAD);

	fprintf(stderr, "dll loaded\n");

	GetInstanceType function = (GetInstanceType)dlsym(dll_plugin, "getInstance");

	fprintf(stderr, "function got\n");
	plugin::Plugin* new_plugin = function(nullptr);

	fprintf(stderr, "function performed\n");

	dlclose(dll_plugin);
	fprintf(stderr, "dll closed\n");
}

int main()
{
	LoadPlugins();

	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	size_t WindowWidth  = window.getSize().x;
	size_t WindowHeight = window.getSize().y;

	RenderTarget rend_targ(plugin::Vec2(WindowWidth, WindowHeight));

	RectangleWidget the_root(plugin::Vec2(0, 0), plugin::Vec2(WindowWidth, WindowHeight));
	Window main_window(plugin::Vec2(0, 0), 
					   plugin::Vec2(WindowWidth, WindowHeight), "Window1");
	the_root.registerSubWidget(&main_window);

	FilterManager fm;
	ToolManager   tm;

	Window canvas_window1(plugin::Vec2(100, 100), plugin::Vec2(1200, 850), "Canvas1");
	Canvas canvas(plugin::Vec2(110, 160), plugin::Vec2(1500, 1200), &tm, &fm);
	canvas_window1.registerSubWidget(&canvas);

	ScrollBar vertical_scroll_bar(canvas.getPosition(), plugin::Vec2(20, canvas_window1.getSize().GetY() - 50),
						 		  plugin::Color(100, 100, 100), 
						 		  plugin::Color(200, 200, 200), plugin::Vec2(1, 0.5),
						 		  &canvas, plugin::Vec2(20, 20), canvas_window1.getSize());
	
	ScrollBar horizontal_scroll_bar(canvas.getPosition(), plugin::Vec2(canvas_window1.getSize().GetX(), 20),
						 		    plugin::Color(100, 100, 100), 
						 		    plugin::Color(200, 200, 200), plugin::Vec2(0.5, 1),
						 		    &canvas, plugin::Vec2(0, 20), canvas_window1.getSize());
	canvas_window1.registerSubWidget(&vertical_scroll_bar);
	canvas_window1.registerSubWidget(&horizontal_scroll_bar);

	main_window.registerSubWidget(&canvas_window1);

	Window canvas_window2(plugin::Vec2(900, 150), plugin::Vec2(500, 550), "Canvas2");
	Canvas canvas2(plugin::Vec2(910, 210), plugin::Vec2(480, 480), &tm, &fm);
	canvas_window2.registerSubWidget(&canvas2);
	main_window.registerSubWidget(&canvas_window2);

	// Adding tools	
	Window tools(plugin::Vec2(1400, 450),
			  	  plugin::Vec2(500, 300), "Tools");
	AddTools(&main_window, &tools, &tm);

	// Adding colors
	Window colors(plugin::Vec2(1400, 150), 
			  	  plugin::Vec2(500, 300), "Colors");
	AddColors(&main_window, &colors, &tm);	

	EventManager event_manager;
	event_manager.registerObject(&main_window);

	AddMenu(&the_root, &main_window, &canvas, &fm, &tm, &event_manager);

	INIT_TIMER();
	RESTART_TIMER();
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
					plugin::Vec2 position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.onMousePress({position, (MouseButton)event.mouseButton.button});
					break;
				}

				case sf::Event::MouseMoved:
				{
					plugin::Vec2 position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.onMouseMove(MouseContext(position, (MouseButton)1));
					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					plugin::Vec2 position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.onMouseRelease({position, (MouseButton)event.mouseButton.button});
					break;
				}

				case sf::Event::KeyPressed:
				{
					KeyboardContext kb_context;
					kb_context.key = (Key)event.key.code;
					
					switch (kb_context.key)
					{
						case Key::LShift:
							kb_context.shift = true;
							break;
						case Key::LAlt:
							kb_context.alt = true;
							break;
						case Key::LControl:
							kb_context.ctrl = true;
							break;
				
					}

					event_manager.onKeyboardPress(kb_context);
					break;
				}

				case sf::Event::KeyReleased:
				{
					KeyboardContext kb_context;
					kb_context.key = (Key)event.key.code;

					switch (kb_context.key)
					{
						case Key::LShift:
							kb_context.shift = false;
							break;
						case Key::LAlt:
							kb_context.alt = false;
							break;
						case Key::LControl:
							kb_context.ctrl = false;
							break;				
					}

					event_manager.onKeyboardRelease(kb_context);
					break;
				}
			}
		}

		STOP_TIMER();
		double delta_time = GET_TIMER_SECONDS();
		if (delta_time > kDeltaTime)
		{
			RESTART_TIMER();
			event_manager.onClock(delta_time);
		}

		the_root.render(&rend_targ);

		rend_targ.display(&window);
		window.display();
	}
}

void AddMenu(Widget* root, Window* window, Canvas* canvas, FilterManager* fm, 
			 ToolManager* tm, EventManager* em)
{
	// Get resources
	Font font;
	font.LoadFont(kFontFile);
	Texture texture, press_texture;
	texture.LoadFromFile(kBackgroundImgFile);
	press_texture.LoadFromFile(kBackgroundPressedImgFile);

	// Create file menu
	TextButton* file_button = new TextButton(plugin::Vec2(10, 50), plugin::Vec2(100, 50), 
									 		 plugin::Color(199, 181, 173),
									 		 font, 20, "File", 
									 		 plugin::Color(255, 255, 255));
	VerticalMenu* file_menu = new VerticalMenu(file_button, false);

	SavingParams* saving_func = new SavingParams(window, em, canvas, font);
	file_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(100, 50), 
									 	plugin::Color(199, 181, 173),
										font, 20, "Save", 
										plugin::Color(255, 255, 255),
										saving_func));

	OpeningParams* opening_func = new OpeningParams(window, em, font, tm, fm);
	file_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(100, 50), 
									 	plugin::Color(199, 181, 173),
										font, 20, "Open", 
										plugin::Color(255, 255, 255),
										opening_func));

	// Create main menu
	HorizontalMenu* main_menu = new HorizontalMenu(file_menu);

	// Create filter menu
	TextButton* filter_button = new TextButton(plugin::Vec2(210, 50),  plugin::Vec2(200, 50),
									  		   plugin::Color(199, 181, 173),
									  		   font, 20, "Filters",
									  		   plugin::Color(255, 255, 255));

	VerticalMenu* filters = new VerticalMenu(filter_button, false);

	SelectFilterArgs* brightness_func = new SelectFilterArgs(fm, new BrightnessFilter(), 
															 font, em, root);

	TextButton* brightness_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		   	   plugin::Color(199, 181, 173),
									  	   		   font, 20, "Bright",
									  	   		   plugin::Color(255, 255, 255),
									  	   		   brightness_func);
	filters->registerSubWidget(brightness_filter);

	SelectFilter* black_white_func = new SelectFilter(fm, new BlackAndWhiteFilter(), 
													  nullptr, nullptr);

	TextButton* black_white_filter = new TextButton(plugin::Vec2(0, 0),  plugin::Vec2(200, 50),  
									  		   	    plugin::Color(199, 181, 173),
									  			    font, 20, "Black-White",
									  			    plugin::Color(255, 255, 255),
									  			    black_white_func);
	filters->registerSubWidget(black_white_filter);

	LastFilter* last_filter_func = new LastFilter(fm); 
	TextButton* last_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		 plugin::Color(199, 181, 173),
											 font, 20, "Last filter",
											 plugin::Color(255, 255, 255),
											 last_filter_func);
	filters->registerSubWidget(last_filter);

	main_menu->registerSubWidget(filters);

	window->registerSubWidget(main_menu);
}

void ClearCanvas(void* args)
{
	((Canvas*)args)->Clear();
}

void AddTools(Window* main_window, Window* tools, ToolManager* tm)
{
	const int ToolsNumber = 7;
	SwitchTool** tools_func = new SwitchTool*[ToolsNumber];
	tools_func[0] = new SwitchTool(tm, new Brush(10));
	tools_func[1] = new SwitchTool(tm, new CircleTool(10));
	tools_func[2] = new SwitchTool(tm, new RectTool(10));
	tools_func[3] = new SwitchTool(tm, new LineTool);
	tools_func[4] = new SwitchTool(tm, new PolylineTool);
	tools_func[5] = new SwitchTool(tm, new FillTool);
	tools_func[6] = new SwitchTool(tm, new SplineTool(10));

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
		tools->registerSubWidget(new Button(tools->getPosition() + plugin::Vec2(10 + 50 * i, 50), 
								   plugin::Vec2(50, 50), 
							   	   common_texture, pressed_texture, 
							   	   tools_func[i]));
	}

	main_window->registerSubWidget(tools);
}

void AddColors(Window* main_window, Window* colors, ToolManager* tm)
{
	const int colors_num   = 8;
	plugin::Color     all_colors[] = {plugin::Color(255, 255, 255),
						 	  plugin::Color(0,     0,   0),
						 	  plugin::Color(255,   0,   0),
						 	  plugin::Color(0,   255,   0),
						 	  plugin::Color(0,     0, 255),
						 	  plugin::Color(255, 255,   0),
						 	  plugin::Color(255,   0, 255),
						 	  plugin::Color(0,   255, 255),};

	SwitchColor* colors_func = nullptr;
	for (int i = 0; i < colors_num; i++)
	{
		colors_func = new SwitchColor(tm, all_colors[i]);

		plugin::Vec2 position = colors->getPosition() + plugin::Vec2(10 + 50 * i, 50);
		colors->registerSubWidget(new Button(position, plugin::Vec2(50, 50), all_colors[i], 
								  	 colors_func));
	}

	main_window->registerSubWidget(colors);
}
