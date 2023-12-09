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
#include "Renderable/Widget/RectangleWidget/RectangleWidget.h"
#include "Gui/Gui.h"

void TestRegClip(RenderTarget& rend_targ);
void AddMenu(Widget* root, Window* window, Canvas* canvas, 
			 FilterManager* fm, ToolManager* tm, EventManager* em, 
			 DynArray<char*> plugin_names);
void AddFilters(Widget* root, Canvas* canvas, FilterManager* fm, Font font,
				ToolManager* tm, EventManager* em, VerticalMenu* filters, 
				DynArray<char*> plugin_names);
void AddTools(Window* main_window, Window* tools, ToolManager* tm, 
			  plugin::App* app, DynArray<char*> plugin_names);
void AddColors(Window* main_window, Window* colors, ToolManager* tm);

typedef plugin::Plugin* (*GetInstanceType)(plugin::App *app);

plugin::Plugin* LoadPlugin(const char* path, plugin::App* app);

DynArray<char*> GetPluginNames()
{
	FILE* file = fopen("Plugins/Plugins", "r");

	DynArray<char*> plugin_names;
	
	char* name = new char[100];
	strcpy(name, "Plugins/");

	while (NULL != fgets(name + 8, 100, file))
	{
		plugin_names.PushBack(name);
		if (name[strlen(name) - 1] == '\n') 
			name[strlen(name) - 1] = 0;

		fprintf(stderr, "name = %s\n", name);
		name = new char[100];
		strcpy(name, "Plugins/");
	}

	delete[] name;

	return plugin_names;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	size_t WindowWidth  = window.getSize().x;
	size_t WindowHeight = window.getSize().y;

	RenderTarget rend_targ(plugin::Vec2(WindowWidth, WindowHeight));

	RectangleWidget the_root(plugin::Vec2(0, 0), plugin::Vec2(WindowWidth, WindowHeight));
	the_root.GetRT()->clear(plugin::Color(255, 255, 255));
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

	EventManager event_manager;
	
	DynArray<char*> plugin_name = GetPluginNames();

	// Adding tools	
	Window tools(plugin::Vec2(1400, 450),
			  	  plugin::Vec2(500, 300), "Tools");

	plugin::App app;
	app.event_manager  = (plugin::EventManagerI*)&event_manager;
	app.tool_manager   = (plugin::ToolManagerI*)&tm;
	app.root 		   = new Gui(&the_root);
	app.filter_manager = &fm;

	AddTools(&main_window, &tools, &tm, &app, plugin_name);

	// Adding colors
	Window colors(plugin::Vec2(1400, 150), 
			  	  plugin::Vec2(500, 300), "Colors");
	AddColors(&main_window, &colors, &tm);	

	event_manager.registerObject(&main_window);

	AddMenu(&the_root, &main_window, &canvas, &fm, &tm, &event_manager, plugin_name);

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
					event_manager.onMousePress({position, (plugin::MouseButton)event.mouseButton.button});
					break;
				}

				case sf::Event::MouseMoved:
				{
					plugin::Vec2 position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.onMouseMove(plugin::MouseContext(position, (plugin::MouseButton)1));
					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					plugin::Vec2 position(sf::Mouse::getPosition().x,
									sf::Mouse::getPosition().y);
					event_manager.onMouseRelease({position, (plugin::MouseButton)event.mouseButton.button});
					break;
				}

				case sf::Event::KeyPressed:
				{
					plugin::KeyboardContext kb_context;
					kb_context.key = (plugin::Key)event.key.code;
					
					switch (kb_context.key)
					{
						case plugin::Key::LShift:
							kb_context.shift = true;
							break;
						case plugin::Key::LAlt:
							kb_context.alt = true;
							break;
						case plugin::Key::LControl:
							kb_context.ctrl = true;
							break;
				
					}

					event_manager.onKeyboardPress(kb_context);
					break;
				}

				case sf::Event::KeyReleased:
				{
					plugin::KeyboardContext kb_context;
					kb_context.key = (plugin::Key)event.key.code;

					switch (kb_context.key)
					{
						case plugin::Key::LShift:
							kb_context.shift = false;
							break;
						case plugin::Key::LAlt:
							kb_context.alt = false;
							break;
						case plugin::Key::LControl:
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
			 ToolManager* tm, EventManager* em, DynArray<char*> plugin_names)
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

	AddFilters(root, canvas, fm, font, tm, em, filters, plugin_names);

	main_menu->registerSubWidget(filters);

	window->registerSubWidget(main_menu);
}

void AddFilters(Widget* root, Canvas* canvas, FilterManager* fm, Font font,
				ToolManager* tm, EventManager* em, VerticalMenu* filters,
				DynArray<char*> plugin_names)
{
	SelectFilterArgs* brightness_func = new SelectFilterArgs(fm, new BrightnessFilter(), 
															 font, em, root);

	TextButton* brightness_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		   	   plugin::Color(199, 181, 173),
									  	   		   font, 20, "Bright",
									  	   		   plugin::Color(255, 255, 255),
									  	   		   brightness_func);
	filters->registerSubWidget(brightness_filter);

	plugin::App* app = new plugin::App();
	Gui* 		 gui = new Gui(root);

	app->event_manager  = (plugin::EventManagerI*)em;
	app->tool_manager	= (plugin::ToolManagerI*)tm;
	app->filter_manager = fm;
	app->root 			= gui;

	//==============================ADD PLUGIN FILTERS==========================
	
	for (int i = 0; i < plugin_names.GetLength(); i++)
	{
		plugin::Plugin* new_plugin = LoadPlugin(plugin_names[i], app);
		if (new_plugin == nullptr)
		{
			fprintf(stderr, "Error during loading plugin [%d] <%s> like filter \n", i, plugin_names[i]);
			continue;
		}

		if (new_plugin->type == plugin::InterfaceType::Filter)
		{
			SelectFilterArgs* plugin_filter_func = new SelectFilterArgs(fm, 
																		(plugin::FilterI*)new_plugin->getInterface(), 
																		font, em, root);
			if (new_plugin->name == nullptr)
				new_plugin->name = "(null)";
			TextButton* plugin_filter = new TextButton(plugin::Vec2(0, 0),  plugin::Vec2(200, 50),  
									  		   		   plugin::Color(199, 181, 173),
									  		   		   font, 20, new_plugin->name,
									  		   		   plugin::Color(255, 255, 255),
									  		   		   plugin_filter_func);
			filters->registerSubWidget(plugin_filter);
		}
	}

	//==========================================================================

	LastFilter* last_filter_func = new LastFilter(fm); 
	TextButton* last_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		 plugin::Color(199, 181, 173),
											 font, 20, "Last filter",
											 plugin::Color(255, 255, 255),
											 last_filter_func);
	filters->registerSubWidget(last_filter);
}

plugin::Plugin* LoadPlugin(const char* path, plugin::App* app)
{
	void* dll_hand = dlopen(path, RTLD_NOW | RTLD_LOCAL);

	if (dlerror() != nullptr)
	{
		fprintf(stderr, "dlerr    = <%s>\n", dlerror());
		fprintf(stderr, "dll_hand = %d\n",   dll_hand);
		return nullptr;
	}

	GetInstanceType get_plugin = (GetInstanceType)dlsym(dll_hand, "getInstance");
	
	if (dlerror() != nullptr)
	{
		fprintf(stderr, "dlerr 		 = <%s>\n", dlerror());
		fprintf(stderr, "GetInstance = %p\n",   get_plugin);
		return nullptr;
	}

	plugin::Plugin* my_plugin = get_plugin(app);

	return my_plugin;
}

void ClearCanvas(void* args)
{
	((Canvas*)args)->Clear();
}

void AddTools(Window* main_window, Window* tools, ToolManager* tm, plugin::App* app, 
			 DynArray<char*> plugin_names)
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

	Font font;
	font.LoadFont(kFontFile);

	//==============================ADD PLUGIN TOOLS==========================
	
	int tool_i = ToolsNumber;

	for (int i = 0; i < plugin_names.GetLength(); i++)
	{
		fprintf(stderr, "plugin [%d] = <%s>\n", i, plugin_names[i]);
		plugin::Plugin* new_plugin = LoadPlugin(plugin_names[i], app);
		if (new_plugin == nullptr)
		{
			fprintf(stderr, "Error during loading plugin[%d] <%s> like tools\n", i, plugin_names[i]);
			continue;
		}
		
		if (new_plugin->type == plugin::InterfaceType::Tool)
		{
			plugin::ToolI* new_tool = (plugin::ToolI*)new_plugin->getInterface();
			if (new_tool == nullptr)
			{
				fprintf(stderr, "Error during loading tool from plugin [%d] <%s>\n", i, plugin_names[i]);
				continue;
			}

			if (new_tool->getIcon() != nullptr)
			{
				common_texture  = Texture(*(new_tool->getIcon()));
				pressed_texture = common_texture;
			}
			else
			{
				common_texture = Texture();
				common_texture.Create(50, 50);

				Image img, img_pressed;
				plugin::Color img_color = plugin::Color(rand() % 255, rand() % 255, rand() % 255);
				img.Create(50, 50, img_color);
				img_pressed.Create(50, 50, img_color.Inverse());

				common_texture.LoadFromImage(img);
				pressed_texture.LoadFromImage(img_pressed);
			}

			plugin::Vec2 position = tools->getPosition() + 
									plugin::Vec2(10 + 50 * tool_i, 50);
			tools->registerSubWidget(new Button(position, 
								   				plugin::Vec2(50, 50), 
							   	   				common_texture, pressed_texture, 
							   	   				new SwitchTool(tm, new_tool)));
			tool_i++;
		}
	}

	//==========================================================================


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
