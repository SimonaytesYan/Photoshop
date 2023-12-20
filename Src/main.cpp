#include <SFML/Graphics.hpp>
#include <assert.h>

#include "ClipRegion/ClipRegion.h"
#include "Constants.h"
#include "EventManager/EventManager.h"
#include "Filter/Filter.h"
#include "Filter/BrightnessFilter/BrightnessFilter.h"
#include "Functors.h"
#include "Gui/Gui.h"
#include "GetPlugins/GetPlugins.h"
#include "List.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Canvas/Canvas.h"
#include "Renderable/Widget/EditBox/EditBox.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Menu/HorizontalMenu/HorizontalMenu.h"
#include "Renderable/Widget/Menu/Menu.h"
#include "Renderable/Widget/Menu/VerticalMenu/VerticalMenu.h"
#include "Renderable/Widget/RectangleWidget/RectangleWidget.h"
#include "Renderable/Widget/ScrollBar/ScrollBar.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Window/Window.h"
#include "Renderable/Widget/Window/ModalWindow.h"
#include "RegionSet/RegionSet.h"
#include "Standart/Standart.h"
#include "Stopwatch.h"
#include "Tool/Brush/Brush.h"
#include "Tool/ShapeTool/CircleTool/CircleTool.h"
#include "Tool/ShapeTool/RectTool/RectTool.h"
#include "Tool/ShapeTool/LineTool/LineTool.h"
#include "Tool/PolylineTool/PolylineTool.h"
#include "Tool/SplineTool/SplineTool.h"
#include "Tool/FillTool/FillTool.h"

int NewCanvas::counter = 0;

void TestRegClip(RenderTarget& rend_targ);
void AddMenu(Widget* root, Window* window, CanvasManager* canvas, 
			 FilterManager* fm, ToolManager* tm, EventManager* em, 
			 plugin::App* app);
void AddFilters(Widget* root, CanvasManager* canvas_manager, FilterManager* fm, Font font,
				ToolManager* tm, EventManager* em, VerticalMenu* filters,
				plugin::App* app);
void AddTools(Window* main_window, Window* tools, ToolManager* tm, 
			  plugin::App* app);
void AddColors(Window* main_window, Window* colors, ToolManager* tm);


int main()
{
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	size_t WindowWidth  = window.getSize().x;
	size_t WindowHeight = window.getSize().y;

	RenderTarget rend_targ(plugin::Vec2(WindowWidth, WindowHeight));

	RectangleWidget* the_root = new RectangleWidget(plugin::Vec2(0, 0), plugin::Vec2(WindowWidth, WindowHeight));
	the_root->GetRT()->clear(plugin::Color(255, 255, 255));
	Window* main_window = new Window(plugin::Vec2(0, 0), 
									 plugin::Vec2(WindowWidth, WindowHeight), 
									 "Window1");
	the_root->registerSubWidget(main_window);

	FilterManager fm;
	ToolManager   tm;
	EventManager  event_manager;
	CanvasManager canvas_manager(nullptr, &event_manager);

	// Adding tools
	Window* tools = new Window(plugin::Vec2(1400, 450),
			  	  			   plugin::Vec2(500, 300), "Tools");

	fprintf(stderr, "the root = %p\n", the_root);
	Gui* gui = new Gui(the_root, &event_manager);
	plugin::App app;
	app.root 		   = gui;
	app.event_manager  = (plugin::EventManagerI*)&event_manager;

	LoadPlugins(&app, gui);

	AddTools(main_window, tools, &tm, &app);

	// Adding colors
	Window* colors = new Window(plugin::Vec2(1400, 150), 
			  	  				plugin::Vec2(500, 300), "Colors");
	AddColors(main_window, colors, &tm);	

	event_manager.registerObject(main_window);

	AddMenu(the_root, main_window, &canvas_manager, &fm, &tm, &event_manager, &app);

	// Add some canvases

	Window* canvas_window1 = new Window(plugin::Vec2(100, 100), plugin::Vec2(1200, 850), "Canvas1");
	Canvas* canvas 		   = new Canvas(plugin::Vec2(110, 150), plugin::Vec2(1500, 1200), 
										&tm, &fm, "Canvas1", &canvas_manager);
	canvas_window1->registerSubWidget(canvas);

	ScrollBar* vertical_scroll_bar = new ScrollBar(canvas->getPos(), plugin::Vec2(20, canvas_window1->getSize().y - 50),
						 		  				   plugin::Color(100, 100, 100), 
						 		  				   plugin::Color(200, 200, 200), plugin::Vec2(1, 0.5),
						 		  				   canvas, plugin::Vec2(20, 20), canvas_window1->getSize());
	
	ScrollBar* horizontal_scroll_bar = new ScrollBar(canvas->getPos(), plugin::Vec2(canvas_window1->getSize().x, 20),
						 		    			     plugin::Color(100, 100, 100), 
						 		    			     plugin::Color(200, 200, 200), plugin::Vec2(0.5, 1),
						 		    			     canvas, plugin::Vec2(0, 20), canvas_window1->getSize());
	canvas_window1->registerSubWidget(vertical_scroll_bar);
	canvas_window1->registerSubWidget(horizontal_scroll_bar);

	main_window->registerSubWidget(canvas_window1);

	Window* canvas_window2 = new Window(plugin::Vec2(900, 150), plugin::Vec2(520, 560), "Canvas2");
	Canvas* canvas2 	   = new Canvas(plugin::Vec2(910, 200), plugin::Vec2(500, 500), 
										&tm, &fm, "Canvas2", &canvas_manager);
	canvas_window2->registerSubWidget(canvas2);
	main_window->registerSubWidget   (canvas_window2);

	//=============================================

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

		the_root->render(&rend_targ);

		rend_targ.display(&window);
		window.display();
	}
}

void AddMenu(Widget* root, Window* window, CanvasManager* canvas_manager, FilterManager* fm, 
			 ToolManager* tm, EventManager* em, plugin::App* app)
{
	// Get resources
	Font font;
	font.LoadFont(kFontFile);
	Texture texture, press_texture;
	texture.LoadFromFile(kBackgroundImgFile);
	press_texture.LoadFromFile(kBackgroundPressedImgFile);

	// Create file menu
	TextButton* file_button = new TextButton(plugin::Vec2(10, 50), plugin::Vec2(100, 50), 
									 		 kButtonColor,
									 		 font, 20, "File", 
									 		 plugin::Color(255, 255, 255));
	VerticalMenu* file_menu = new VerticalMenu(file_button, false);

	SavingParams* saving_func = new SavingParams(window, em, canvas_manager, font);
	file_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(100, 50), 
									 			kButtonColor,
												font, 20, "Save", 
												plugin::Color(255, 255, 255),
												saving_func));

	OpeningParams* opening_func = new OpeningParams(window, em, font, tm, fm, canvas_manager);
	file_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(100, 50), 
									 			kButtonColor,
												font, 20, "Open", 
												plugin::Color(255, 255, 255),
												opening_func));

	NewCanvas* new_canvas_functor = new NewCanvas(window, tm, fm, canvas_manager);
	file_menu->registerSubWidget(new TextButton(plugin::Vec2(0, 0), plugin::Vec2(100, 50), 
									 			kButtonColor,
												font, 20, "New", 
												plugin::Color(255, 255, 255),
												new_canvas_functor));

	// Create main menu
	HorizontalMenu* main_menu = new HorizontalMenu(file_menu);

	// Create filter menu
	TextButton* filter_button = new TextButton(plugin::Vec2(210, 50),  plugin::Vec2(200, 50),
									  		   kButtonColor,
									  		   font, 20, "Filters",
									  		   plugin::Color(255, 255, 255));

	VerticalMenu* filters = new VerticalMenu(filter_button, false);

	AddFilters(root, canvas_manager, fm, font, tm, em, filters, app);

	main_menu->registerSubWidget(filters);

	// Create windows menu

	TextButton* windows_button = new TextButton(plugin::Vec2(310, 50),  plugin::Vec2(200, 50),
									  		    kButtonColor,
									  		    font, 20, "Windows",
									  		    plugin::Color(255, 255, 255));
	VerticalMenu* windows = new VerticalMenu(windows_button, false);
	window->registerSubWidget(windows);

	canvas_manager->SetWindowMenu(windows);

	window->registerSubWidget(main_menu);
}

void AddFilters(Widget* root, CanvasManager* canvas_manager, FilterManager* fm, Font font,
				ToolManager* tm, EventManager* em, VerticalMenu* filters,
				plugin::App* app)
{
	SelectFilterArgs* brightness_func = new SelectFilterArgs(fm, new BrightnessFilter(), 
															 font, em, root);

	TextButton* brightness_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		   	   kButtonColor,
									  	   		   font, 20, "Bright",
									  	   		   plugin::Color(255, 255, 255),
									  	   		   brightness_func);
	filters->registerSubWidget(brightness_filter);

	//==============================ADD PLUGIN FILTERS==========================
	
	DynArray<plugin::Plugin*> plugins = ((Gui*)app->root)->GetPlugins();

	for (int i = 0; i < plugins.GetLength(); i++)
	{
		plugin::Plugin* new_plugin = plugins[i];

		if (new_plugin->type == plugin::InterfaceType::Filter)
		{
			SelectFilterArgs* plugin_filter_func = new SelectFilterArgs(fm, 
																		(plugin::FilterI*)new_plugin->getInterface(), 
																		font, em, root);
			
			TextButton* plugin_filter = new TextButton(plugin::Vec2(0, 0),  plugin::Vec2(200, 50),  
									  		   		   kButtonColor,
									  		   		   font, 20, new_plugin->name,
									  		   		   plugin::Color(255, 255, 255),
									  		   		   plugin_filter_func);
			filters->registerSubWidget(plugin_filter);
		}
	}

	//==========================================================================

	LastFilter* last_filter_func = new LastFilter(fm); 
	TextButton* last_filter = new TextButton(plugin::Vec2(0, 0), plugin::Vec2(200, 50), 
									  		 kButtonColor,
											 font, 20, "Last filter",
											 plugin::Color(255, 255, 255),
											 last_filter_func);
	filters->registerSubWidget(last_filter);
}

void ClearCanvas(void* args)
{
	((Canvas*)args)->Clear();
}

void AddTools(Window* main_window, Window* tools, ToolManager* tm, plugin::App* app)
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
		tools->registerSubWidget(new Button(tools->getPos() + plugin::Vec2(10 + 50 * i, 50), 
								            plugin::Vec2(50, 50), 
							   	            common_texture, pressed_texture, 
							   	            tools_func[i]));
	}

	Font font;
	font.LoadFont(kFontFile);

	//==============================ADD PLUGIN TOOLS==========================
	
	int tool_i = ToolsNumber;

	DynArray<plugin::Plugin*> plugins = ((Gui*)app->root)->GetPlugins();

	for (int i = 0; i < plugins.GetLength(); i++)
	{
		plugin::Plugin* new_plugin = plugins[i];
		
		if (new_plugin->type == plugin::InterfaceType::Tool)
		{
			plugin::ToolI* new_tool = (plugin::ToolI*)new_plugin->getInterface();

			if (new_tool == nullptr)
			{
				fprintf(stderr, "Error during loading tool from plugin [%d] <%s>\n", i, new_plugin->name);
				continue;
			}

			if (new_tool->getIcon() != nullptr)
			{
				fprintf(stderr, "icon[%d] (%d, %d) = %p", i, new_tool->getIcon()->width, new_tool->getIcon()->height, new_tool->getIcon()->pixels);
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

			plugin::Vec2 position = tools->getPos() + 
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

		plugin::Vec2 position = colors->getPos() + plugin::Vec2(10 + 50 * i, 50);
		colors->registerSubWidget(new Button(position, plugin::Vec2(50, 50), all_colors[i], 
								  	 colors_func));
	}

	main_window->registerSubWidget(colors);
}
