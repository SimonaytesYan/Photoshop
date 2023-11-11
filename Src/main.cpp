#include <SFML/Graphics.hpp>
#include <assert.h>

#include "List.h"
#include "Stopwatch.h"
#include "Resources.h"
#include "Image/Image.h"
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

const double kDeltaTime      = 0.25;
const char   kWindowHeader[] = "Photoshop";
const int    kMaxTextLength  = 50;
const double kLetterWidth    = 0.57;
const double kLetterHeight   = 1.5;
size_t       WindowWidth     = 0;
size_t       WindowHeight    = 0;

struct ColorStruct
{
	ToolManager* tm;
	Color		 color;
};

struct FilterStruct
{
	FilterManager* filter_manager;
	Filter*        filter;
	Font           font;
	EventManager*  event_manager;
	Widget*		   root;
};

struct FilterArgsStruct
{
	FilterManager*      filter_manager;
	Filter* 	        filter;
	DynArray<EditBox*>* edit_boxes;
	ModalWindow*		dialog_box;				
};

struct GetFilename
{
	Window* 	  main_window;
	EventManager* event_manager;
	Canvas* 	  canvas;
	Font 		  font;
};

struct SaveCanvasStruct
{
	Canvas*	     canvas;
	EditBox*     file_name_edit;  
	ModalWindow* dialog_box;
};

void TestRegClip(RenderTarget& rend_targ);
void AddMenu(Widget* root, Window* window, Canvas* canvas, FilterManager* fm, EventManager* em);
void AddTools(Window* main_window, Window* tool,   ToolManager* tm);
void AddColors(Window* main_window, Window* colors, ToolManager* tm);

void Say(void* args);

struct SwitchTool : ButtonFunction
{
	ToolManager* tool_manager;
	Tool*		 tool;

	SwitchTool() :
	tool_manager (nullptr),
	tool 		 (nullptr)
	{}

	SwitchTool(ToolManager* _tool_manager, Tool* _tool) :
	tool 		 (_tool),
	tool_manager (_tool_manager)
	{}

	void operator()() override
	{
		tool_manager->ChangeTool(tool);
	}

	~SwitchTool() { delete tool; }
};

struct SwitchColor : ButtonFunction
{
	ToolManager* tool_manager;
	Color		 color;

	SwitchColor() :
	tool_manager (nullptr),
	color 		 (Color(0, 0, 0))
	{}

	SwitchColor(ToolManager* _tool_manager, Color _color) :
	color 		 (_color),
	tool_manager (_tool_manager)
	{}

	void operator()() override
	{
		tool_manager->ChangeColor(color);
	}
};

void SelectFilter(void* args);
void SelectFilterArgs(void* args);
void SaveCanvasInFile(void* args);
void UseLastFilter(void* args);
void ClearCanvas(void* args);
void SavingParams(void* args);

int main()
{
	sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);

	WindowWidth  = window.getSize().x;
	WindowHeight = window.getSize().y;

	RenderTarget rend_targ(Vector(WindowWidth, WindowHeight));

	RectangleWidget the_root(Vector(0, 0), Vector(WindowWidth, WindowHeight));
	Window main_window(Vector(0, 0), 
					   Vector(WindowWidth, WindowHeight), "Window1");
	the_root.AddObject(&main_window);

	FilterManager fm;
	ToolManager   tm;

	Window canvas_window1(Vector(100, 100), Vector(1200, 850), "Canvas1");
	Canvas canvas(Vector(110, 160), Vector(1500, 1200), &tm, &fm);
	canvas_window1.AddObject(&canvas);

	ScrollBar vertical_scroll_bar(canvas.GetPosition(), Vector(20, canvas_window1.GetSize().GetY() - 50),
						 		  Color(100, 100, 100), 
						 		  Color(200, 200, 200), Vector(1, 0.5),
						 		  &canvas, Vector(20, 20), canvas_window1.GetSize());
	
	ScrollBar horizontal_scroll_bar(canvas.GetPosition(), Vector(canvas_window1.GetSize().GetX(), 20),
						 		    Color(100, 100, 100), 
						 		    Color(200, 200, 200), Vector(0.5, 1),
						 		    &canvas, Vector(0, 20), canvas_window1.GetSize());
	canvas_window1.AddObject(&vertical_scroll_bar);
	canvas_window1.AddObject(&horizontal_scroll_bar);

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

	EventManager event_manager;
	event_manager.AddObject(&main_window);

	AddMenu(&the_root, &main_window, &canvas, &fm, &event_manager);

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

				case sf::Event::KeyPressed:
				{
					event_manager.OnKeyPress((Key)event.key.code);
					break;
				}

				case sf::Event::KeyReleased:
				{
					event_manager.OnKeyRelease((Key)event.key.code);
					break;
				}
			}
		}

		STOP_TIMER();
		double delta_time = GET_TIMER_SECONDS();
		if (delta_time > kDeltaTime)
		{
			RESTART_TIMER();
			event_manager.OnClock(delta_time);
		}

		the_root.Render(&rend_targ);
		
		rend_targ.Display(&window);
		window.display();
	}
}

void AddMenu(Widget* root, Window* window, Canvas* canvas, FilterManager* fm, EventManager* em)
{
	// Get resources
	Font font;
	font.LoadFont(kFontFile);
	Texture texture, press_texture;
	texture.LoadFromFile(kBackgroundImgFile);
	press_texture.LoadFromFile(kBackgroundPressedImgFile);

	// Create file menu
	TextButton* file_button = new TextButton(Vector(10, 50), Vector(100, 50), 
									 		 Color(199, 181, 173),
									 		 font, 20, "File", 
									 		 Color(255, 255, 255),
									 		 Say, nullptr);
	VerticalMenu* file_menu = new VerticalMenu(file_button, false);

	GetFilename* get_fn   = new GetFilename();
	get_fn->canvas        = canvas;
	get_fn->font          = font;
	get_fn->event_manager = em;
	get_fn->main_window   = window;

	file_menu->AddObject(new TextButton(Vector(0, 0), Vector(100, 50), 
									 	Color(199, 181, 173),
										font, 20, "Save", 
										Color(255, 255, 255),
										SavingParams, get_fn));
	
	// Create main menu
	HorizontalMenu* main_menu = new HorizontalMenu(file_menu);

	// Create clear button 
	TextButton* clear_button = new TextButton(Vector(110, 50), Vector(100, 50), 
									 		  Color(199, 181, 173),
									  		  font, 20, "Clear",
									  		  Color(255, 255, 255),
									  		  ClearCanvas, canvas);
	main_menu->AddObject(clear_button);
	
	// Create filter menu
	TextButton* filter_button = new TextButton(Vector(210, 50),  Vector(200, 50),
									  		   Color(199, 181, 173),
									  		   font, 20, "Filters",
									  		   Color(255, 255, 255),
											   nullptr, nullptr);

	VerticalMenu* filters = new VerticalMenu(filter_button, false);

	FilterStruct* brightness_fs   = new FilterStruct();
	brightness_fs->filter_manager = fm;
	brightness_fs->filter 	      = new BrightnessFilter();
	brightness_fs->event_manager  = em;
	brightness_fs->root	          = root;
	brightness_fs->font			  = font;

	TextButton* brightness_filter = new TextButton(Vector(0, 0), Vector(200, 50), 
									  		   	   Color(199, 181, 173),
									  	   		   font, 20, "Bright",
									  	   		   Color(255, 255, 255),
									  	   		   SelectFilterArgs, brightness_fs);
	filters->AddObject(brightness_filter);
	
	FilterArgsStruct* black_white_fs = new FilterArgsStruct();
	black_white_fs->filter_manager = fm;
	black_white_fs->filter 	  	   = new BlackAndWhiteFilter();
	black_white_fs->dialog_box	   = nullptr;

	TextButton* black_white_filter = new TextButton(Vector(0, 0),  Vector(200, 50),  
									  		   	    Color(199, 181, 173),
									  			    font, 20, "Black-White",
									  			    Color(255, 255, 255),
									  			    SelectFilter, black_white_fs);
	filters->AddObject(black_white_filter);

	TextButton* last_filter = new TextButton(Vector(0, 0), Vector(200, 50), 
									  		 Color(199, 181, 173),
											 font, 20, "Last filter",
											 Color(255, 255, 255),
											 UseLastFilter, fm);
	filters->AddObject(last_filter);

	main_menu->AddObject(filters);
	
	window->AddObject(main_menu);
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
	tools_func[0] = new SwitchTool(tm, new CircleTool(10));
	tools_func[1] = new SwitchTool(tm, new RectTool(10));
	tools_func[2] = new SwitchTool(tm, new LineTool);
	tools_func[3] = new SwitchTool(tm, new PolylineTool);
	tools_func[4] = new SwitchTool(tm, new FillTool);
	tools_func[5] = new SwitchTool(tm, new CircleTool(10));
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
		tools->AddObject(new Button(tools->GetPosition() + Vector(10 + 50 * i, 50), 
								   Vector(50, 50), 
							   	   common_texture, pressed_texture, 
							   	   tools_func[i]));
	}

	main_window->AddObject(tools);
}

void AddColors(Window* main_window, Window* colors, ToolManager* tm)
{
	const int colors_num   = 8;
	Color     all_colors[] = {Color(255, 255, 255),
						 	  Color(0,     0,   0),
						 	  Color(255,   0,   0),
						 	  Color(0,   255,   0),
						 	  Color(0,     0, 255),
						 	  Color(255, 255,   0),
						 	  Color(255,   0, 255),
						 	  Color(0,   255, 255),};

	SwitchColor* colors_func = nullptr;
	for (int i = 0; i < colors_num; i++)
	{
		colors_func = new SwitchColor(tm, all_colors[i]);

		Vector position = colors->GetPosition() + Vector(10 + 50 * i, 50);
		colors->AddObject(new Button(position, Vector(50, 50), all_colors[i], 
								  	 colors_func));
	}

	main_window->AddObject(colors);
}

void SelectFilterArgs(void* _args)
{
	FilterStruct* fs = (FilterStruct*)_args;

	DynArray<const char*> filter_args = fs->filter->GetParamNames();
	
	int filter_args_n = filter_args.GetLength();
	if (filter_args_n > 0)
	{
		Vector position = fs->root->GetPosition() + fs->root->GetSize() / 2;
		Vector size(400, 2 * 50 + (filter_args_n + 1) * 100);
		ModalWindow* dialog_box = new ModalWindow(position, size, 
												  "Enter filter params", fs->event_manager);

		position = position + Vector(0, 100);
		DynArray<EditBox*>* edit_boxes = new DynArray<EditBox*>(0);

		for (int i = 0; i < filter_args_n; i++)
		{
			EditBox* edit_box = new EditBox(position + Vector(200, i * 100), Vector(100, 50), 
											fs->font, kLetterWidth, kLetterHeight, 20);
			edit_boxes->PushBack(edit_box);

			dialog_box->AddObject(edit_box);
			dialog_box->AddObject(new Label(position + Vector(25, i * 100), 
											fs->font, 20, filter_args[i]));
		}
	
		FilterArgsStruct* fas = new FilterArgsStruct(); 
		fas->edit_boxes     = edit_boxes;
		fas->filter		    = fs->filter;
		fas->filter_manager = fs->filter_manager;
		fas->dialog_box		= dialog_box;

		TextButton* ok_button = new TextButton(position + Vector(200, filter_args_n * 100), 
									   		   Vector(50, 50), Color(255, 255, 255), 
											   fs->font, 20, "Ok", Color(0, 0, 0),
									   		   SelectFilter, fas);
		dialog_box->AddObject(ok_button);		
		
		fs->root->AddObject(dialog_box);
	}
}

void SavingParams(void* _args)
{
	GetFilename* args = (GetFilename*)_args;

	Vector position = args->main_window->GetPosition() + args->main_window->GetSize() / 2;
	Vector size(400, 300);
	ModalWindow* dialog_box = new ModalWindow(position, size, 
											  "Enter file name params", 
											  args->event_manager);

	position = position + Vector(50, 100);
	dialog_box->AddObject(new Label(position, 
									args->font, 20, "Filename"));
	EditBox* edit_box = new EditBox(position + Vector(200, 0), Vector(100, 50), 
									args->font, kLetterWidth, kLetterHeight, 20);
	dialog_box->AddObject(edit_box);
	
	SaveCanvasStruct* save_canvas_struct = new SaveCanvasStruct();
	save_canvas_struct->canvas		   = args->canvas;
	save_canvas_struct->file_name_edit = edit_box;
	save_canvas_struct->dialog_box	   = dialog_box;

	TextButton* ok_button = new TextButton(position + Vector(200, 100), 
								   		   Vector(50, 50), Color(255, 255, 255), 
										   args->font, 20, "Ok", Color(0, 0, 0),
								   		   SaveCanvasInFile, save_canvas_struct);
	dialog_box->AddObject(ok_button);		
		
	args->main_window->AddObject(dialog_box);
}

void SaveCanvasInFile(void* _args)
{
	SaveCanvasStruct* args = (SaveCanvasStruct*)_args;

	Image img(args->canvas->GetData()->GetTexture());
	sf::Image image = img.GetImage();
	const char* file_name = args->file_name_edit->GetText();
	
	image.saveToFile(file_name);
	args->dialog_box->Close();
}

void SelectFilter(void* _args)
{
	FilterArgsStruct* fas = (FilterArgsStruct*)_args;
	if (fas->edit_boxes != nullptr)
	{
		DynArray<double> filter_params(fas->edit_boxes->GetLength());

		for (int i = 0; i < fas->edit_boxes->GetLength(); i++)
		{
			filter_params[i] = atof((*fas->edit_boxes)[i]->GetText());
		}

		fas->filter->SetParams(filter_params);
		fas->dialog_box->Close();
	}
	fas->filter_manager->SetFilter(fas->filter);
}

void UseLastFilter(void* _args)
{
	FilterManager* args = (FilterManager*)_args;
	args->SetFilter(args->GetFilter());
}

void Say(void* args)
{
	fprintf(stderr, "Open file\n");
}
