#ifndef SYM_FUNCTORS
#define SYM_FUNCTORS

#include "Constants.h"
#include "EventManager/EventManager.h"
#include "Renderable/Widget/Widget.h"
#include "Renderable/Widget/Button/Button.h"
#include "Renderable/Widget/Canvas/Canvas.h"
#include "Renderable/Widget/EditBox/EditBox.h"
#include "Renderable/Widget/Label/Label.h"
#include "Renderable/Widget/Window/Window.h"
#include "Renderable/Widget/Window/ModalWindow.h"
#include "RegionSet/RegionSet.h"
#include "ClipRegion/ClipRegion.h"
#include "Filter/Filter.h"
#include "Texture/Texture.h"

struct SwitchTool : ButtonFunction
{
	ToolManager*   tool_manager;
	plugin::ToolI* tool;

	SwitchTool() :
	tool_manager (nullptr),
	tool 		 (nullptr)
	{}

	SwitchTool(ToolManager* _tool_manager, plugin::ToolI* _tool) :
	tool 		 (_tool),
	tool_manager (_tool_manager)
	{}

	void operator()() override;

	~SwitchTool() { delete tool; }
};

struct SwitchColor : ButtonFunction
{
	ToolManager* tool_manager;
	plugin::Color		 color;

	SwitchColor() :
	tool_manager (nullptr),
	color 		 (plugin::Color(0, 0, 0))
	{}

	SwitchColor(ToolManager* _tool_manager, plugin::Color _color) :
	color 		 (_color),
	tool_manager (_tool_manager)
	{}

	void operator()() override;
};

struct SelectFilter : ButtonFunction
{
	FilterManager*      filter_manager;
	plugin::FilterI* 	        filter;
	DynArray<EditBox*>* edit_boxes;
	ModalWindow*		dialog_box;	
	
	SelectFilter()
	{}

	SelectFilter(FilterManager* filter_manager, plugin::FilterI* filter, 
			     DynArray<EditBox*>* edit_boxes, ModalWindow* dialog_box) :
	filter_manager (filter_manager),
	filter         (filter),
	edit_boxes     (edit_boxes),
	dialog_box     (dialog_box)
	{}

	void operator()() override;
};

struct SelectFilterArgs : ButtonFunction
{
	FilterManager*   filter_manager;
	plugin::FilterI* filter;
	Font           	 font;
	EventManager*  	 event_manager;
	Widget*		   	 root;
	
	SelectFilterArgs()
	{}

	SelectFilterArgs(FilterManager* filter_manager, plugin::FilterI* filter, 
				     Font font, EventManager* event_manager, 
				     Widget* root) :
	filter_manager (filter_manager),
	filter         (filter),
	font           (font),
	event_manager  (event_manager),
	root		   (root)
	{}

	void operator()() override;
};

struct LastFilter : ButtonFunction
{
	FilterManager* filter_manager;

	LastFilter() :
	filter_manager (nullptr)
	{}

	LastFilter(FilterManager* _filter_manager) :
	filter_manager (_filter_manager)
	{}

	void operator()() override;
};

struct SavingParams : ButtonFunction
{
	Window* 	   main_window;
	EventManager*  event_manager;
	CanvasManager* canvas_manager;
	Font 		   font;

	SavingParams() :
	main_window    (nullptr),
	event_manager  (nullptr),
	canvas_manager (nullptr)
	{}

	SavingParams(Window* 	    main_window,
				 EventManager*  event_manager,
				 CanvasManager* canvas_manager,
				 Font 		    font) :
	main_window    (main_window),
	event_manager  (event_manager),
	canvas_manager (canvas_manager),
	font 		   (font)
	{}

	void operator()() override;
};

struct SaveInFile : ButtonFunction
{
	CanvasManager* canvas_manager;
	EditBox*       file_name_edit;  
	ModalWindow*   dialog_box;

	SaveInFile() :
	canvas_manager (nullptr),
	file_name_edit (nullptr),
	dialog_box     (nullptr)
	{}

	SaveInFile(CanvasManager*     canvas, 
			  EditBox*     file_name_edit,
			  ModalWindow* dialog_box) :
	canvas_manager (canvas_manager),
	file_name_edit (file_name_edit),
	dialog_box     (dialog_box)
	{}

	void operator()() override;
};

struct OpeningParams : ButtonFunction
{
	Window* 	   main_window;
	EventManager*  event_manager;
	Font 		   font;
	ToolManager*   tool_manager;
	FilterManager* filter_manager;
	CanvasManager* canvas_manager;

	OpeningParams() :
	main_window    (nullptr),
	event_manager  (nullptr),
	tool_manager   (nullptr),
	filter_manager (nullptr)
	{}

	OpeningParams(Window* 	   main_window,
				  EventManager* event_manager,
				  Font 		   font,
			 	  ToolManager*   tool_manager,
			 	  FilterManager* filter_manager,
				  CanvasManager* canvas_manager) :
	main_window   (main_window),
	event_manager (event_manager),
	font 		  (font),
	tool_manager  (tool_manager),
	filter_manager(filter_manager),
	canvas_manager(canvas_manager)
	{}

	void operator()() override;
};

struct OpenFile : ButtonFunction
{
	Window*		   main_window;
	EditBox*       file_name_edit;  
	ModalWindow*   dialog_box;
	ToolManager*   tool_manager;
	FilterManager* filter_manager;
	CanvasManager* canvas_manager;

	OpenFile() :
	main_window	   (nullptr),
	file_name_edit (nullptr),
	dialog_box     (nullptr),
	tool_manager   (nullptr),
	filter_manager (nullptr)
	{}

	OpenFile(Window*        main_window,
	         EditBox*       file_name_edit,
			 ModalWindow*   dialog_box,
			 ToolManager*   tool_manager,
			 FilterManager* filter_manager,
			 CanvasManager* canvas_manager) :
	file_name_edit (file_name_edit),
	dialog_box     (dialog_box),
	main_window	   (main_window),
	tool_manager   (tool_manager),
	filter_manager (filter_manager),
	canvas_manager (canvas_manager)
	{}

	void operator()() override;
};

struct NewCanvas : ButtonFunction
{
	static int counter;

	Window* 	   main_window;
	ToolManager*   tool_manager;
	FilterManager* filter_manager;
	CanvasManager* canvas_manager;

	NewCanvas(Window* main_window,
			  ToolManager*   tool_manager,
			  FilterManager* filter_manager,
			  CanvasManager* canvas_manager) :
	main_window   (main_window),
	tool_manager  (tool_manager),
	filter_manager(filter_manager),
	canvas_manager (canvas_manager)
	{ }

	void operator()() override
	{
		char window_header[100] = "";
		sprintf(window_header, "NewCanvas%d", counter++);

		fprintf(stderr, "Creating new canvas\n");

		Window* new_window = new Window(plugin::Vec2(400, 400), plugin::Vec2(720, 560), window_header);
		Canvas* new_canvas = new Canvas(plugin::Vec2(410, 450), plugin::Vec2(700, 500), tool_manager, 
										filter_manager, window_header, canvas_manager);

		new_window->registerSubWidget(new_canvas);
		main_window->registerSubWidget(new_window);
	}
};

//==============================FUNCTIONS IMPLEMENTATION========================

void SwitchTool::operator()()
{
	
	tool_manager->setTool(tool);
}

void SwitchColor::operator()()
{
	tool_manager->setColor(color);
}

void SelectFilter::operator()()
{
	if (edit_boxes != nullptr)
	{
		plugin::Array<double> filter_params(edit_boxes->GetLength(), nullptr);
		filter_params.data = new double[edit_boxes->GetLength()];

		for (int i = 0; i < edit_boxes->GetLength(); i++)
    		filter_params.data[i] = atof((*edit_boxes)[i]->GetText());

		filter->setParams(filter_params);
		dialog_box->Close();
	}
	filter_manager->setFilter(filter);
}

void SelectFilterArgs::operator()()
{
	plugin::Array<const char*> filter_args = filter->getParamNames();

	int filter_args_n = filter_args.size;
	if (filter_args_n != 0)
	{
		plugin::Vec2 position = root->getPos() + root->getSize() / 2;
		plugin::Vec2 size(400, 2 * 50 + (filter_args_n + 1) * 100);
		ModalWindow* dialog_box = new ModalWindow(position, size, 
													  "Enter filter params", event_manager);

		position = position + plugin::Vec2(0, 100);
		DynArray<EditBox*>* edit_boxes = new DynArray<EditBox*>(0);

		for (int i = 0; i < filter_args_n; i++)
		{
			EditBox* edit_box = new EditBox(position + plugin::Vec2(200, i * 100), plugin::Vec2(100, 50), 
											font, kLetterWidth, kLetterHeight, 20);
			edit_boxes->PushBack(edit_box);

			dialog_box->registerSubWidget(edit_box);
			dialog_box->registerSubWidget(new Label(position + plugin::Vec2(25, i * 100), 
											font, 20, filter_args.data[i]));
		}

		SelectFilter* select_filter_func = new SelectFilter(filter_manager, 
															filter, 
															edit_boxes, 
															dialog_box);
		TextButton* ok_button = new TextButton(position + plugin::Vec2(200, filter_args_n * 100), 
									   		   plugin::Vec2(50, 50), plugin::Color(255, 255, 255), 
											   font, 20, "Ok", plugin::Color(0, 0, 0),
									   		   select_filter_func);
		dialog_box->registerSubWidget(ok_button);		

		root->registerSubWidget(dialog_box);
    }
	else
		filter_manager->setFilter(filter);
}

void LastFilter::operator()()
{
	filter_manager->applyFilter();
}

void SavingParams::operator()()
{
	plugin::Vec2 position = main_window->getPos() + main_window->getSize() / 2;
	plugin::Vec2 size(400, 300);
	ModalWindow* dialog_box = new ModalWindow(position, size, 
											  "Enter file name params", 
											  event_manager);

	position = position + plugin::Vec2(50, 100);
	dialog_box->registerSubWidget(new Label(position, 
									font, 20, "Filename"));
	EditBox* edit_box = new EditBox(position + plugin::Vec2(200, 0), plugin::Vec2(100, 50), 
									font, kLetterWidth, kLetterHeight, 20);
	dialog_box->registerSubWidget(edit_box);

	SaveInFile* save_canvas_func = new SaveInFile(canvas_manager, edit_box, dialog_box);
		
	TextButton* ok_button = new TextButton(position + plugin::Vec2(200, 100), 
								   		   plugin::Vec2(50, 50), plugin::Color(255, 255, 255), 
										   font, 20, "Ok", plugin::Color(0, 0, 0),
								   		   save_canvas_func);
	dialog_box->registerSubWidget(ok_button);		

	main_window->registerSubWidget(dialog_box);
}

void SaveInFile::operator()()
{
    Image img(canvas_manager->GetActiveCanvas()->GetData()->GetTexture());
	sf::Image image = img.GetImage();
	const char* file_name = file_name_edit->GetText();

	image.saveToFile(file_name);
	dialog_box->Close();
}

void OpeningParams::operator()()
{
	plugin::Vec2 position = main_window->getPos() + main_window->getSize() / 2;
	plugin::Vec2 size(400, 300);
	ModalWindow* dialog_box = new ModalWindow(position, size, 
											  "Enter file name", 
											  event_manager);

	position = position + plugin::Vec2(50, 100);
	dialog_box->registerSubWidget(new Label(position, 
									font, 20, "File"));
	EditBox* edit_box = new EditBox(position + plugin::Vec2(200, 0), plugin::Vec2(100, 50), 
									font, kLetterWidth, kLetterHeight, 20);
	dialog_box->registerSubWidget(edit_box);

	OpenFile* save_canvas_func = new OpenFile(main_window, edit_box, dialog_box, 
											  tool_manager, filter_manager, canvas_manager);
	TextButton* ok_button = new TextButton(position + plugin::Vec2(200, 100), 
								   		   plugin::Vec2(50, 50), plugin::Color(255, 255, 255), 
										   font, 20, "Ok", plugin::Color(0, 0, 0),
								   		   save_canvas_func);
	dialog_box->registerSubWidget(ok_button);		

	main_window->registerSubWidget(dialog_box);
}

void OpenFile::operator()()
{
	const char* file_name = file_name_edit->GetText();

	Texture texture;
	texture.LoadFromFile(file_name);

	plugin::Vec2 position = main_window->getPos() + main_window->getSize() / 10;
	Window* canvas_window = new Window(position          - plugin::Vec2(10, 50), 
									   texture.getSize() + plugin::Vec2(20, 60), file_name);

	Canvas* new_canvas = new Canvas(position, texture.getSize(), tool_manager, filter_manager,
									file_name, canvas_manager);
	new_canvas->GetData()->DrawSprite(plugin::Vec2(0, 0), texture);	
	canvas_window->registerSubWidget(new_canvas);

	main_window->registerSubWidget(canvas_window);

	dialog_box->Close();
}

#endif // SYM_FUNCTORS