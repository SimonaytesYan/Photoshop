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
#include "Image/Image.h"

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

	void operator()() override;

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

	void operator()() override;
};

struct SelectFilter : ButtonFunction
{
	FilterManager*      filter_manager;
	Filter* 	        filter;
	DynArray<EditBox*>* edit_boxes;
	ModalWindow*		dialog_box;	
	
	SelectFilter()
	{}

	SelectFilter(FilterManager* filter_manager, Filter* filter, 
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
	FilterManager* filter_manager;
	Filter*        filter;
	Font           font;
	EventManager*  event_manager;
	Widget*		   root;
	
	SelectFilterArgs()
	{}

	SelectFilterArgs(FilterManager* filter_manager, Filter* filter, 
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
	Window* 	  main_window;
	EventManager* event_manager;
	Canvas* 	  canvas;
	Font 		  font;

	SavingParams() :
	main_window   (nullptr),
	event_manager (nullptr),
	canvas        (nullptr)
	{}

	SavingParams(Window* 	   main_window,
				 EventManager* event_manager,
				 Canvas* 	   canvas,
				 Font 		   font) :
	main_window   (main_window),
	event_manager (event_manager),
	canvas        (canvas),
	font 		  (font)
	{}

	void operator()() override;
};

struct SaveInFile : ButtonFunction
{
	Canvas*	     canvas;
	EditBox*     file_name_edit;  
	ModalWindow* dialog_box;

	SaveInFile() :
	canvas         (nullptr),
	file_name_edit (nullptr),
	dialog_box     (nullptr)
	{}

	SaveInFile(Canvas*     canvas, 
			  EditBox*     file_name_edit,
			  ModalWindow* dialog_box) :
	canvas         (canvas),
	file_name_edit (file_name_edit),
	dialog_box     (dialog_box)
	{}

	void operator()() override;
};

//==============================FUNCTIONS IMPLEMENTATION========================

void SwitchTool::operator()()
{
	tool_manager->ChangeTool(tool);
}

void SwitchColor::operator()()
{
	tool_manager->ChangeColor(color);
}

void SelectFilter::operator()()
{
	if (edit_boxes != nullptr)
	{
		DynArray<double> filter_params(edit_boxes->GetLength());

		for (int i = 0; i < edit_boxes->GetLength(); i++)
    		filter_params[i] = atof((*edit_boxes)[i]->GetText());

		filter->SetParams(filter_params);
		dialog_box->Close();
	}
	filter_manager->SetFilter(filter);
}

void SelectFilterArgs::operator()()
{
	DynArray<const char*> filter_args = filter->GetParamNames();

	int filter_args_n = filter_args.GetLength();
	if (filter_args_n > 0)
	{
		Vector position = root->GetPosition() + root->GetSize() / 2;
		Vector size(400, 2 * 50 + (filter_args_n + 1) * 100);
		ModalWindow* dialog_box = new ModalWindow(position, size, 
													  "Enter filter params", event_manager);

		position = position + Vector(0, 100);
		DynArray<EditBox*>* edit_boxes = new DynArray<EditBox*>(0);

		for (int i = 0; i < filter_args_n; i++)
		{
			EditBox* edit_box = new EditBox(position + Vector(200, i * 100), Vector(100, 50), 
											font, kLetterWidth, kLetterHeight, 20);
			edit_boxes->PushBack(edit_box);

			dialog_box->AddObject(edit_box);
			dialog_box->AddObject(new Label(position + Vector(25, i * 100), 
											font, 20, filter_args[i]));
		}

		SelectFilter* select_filter_func = new SelectFilter(filter_manager, 
															filter, 
															edit_boxes, 
															dialog_box);
		TextButton* ok_button = new TextButton(position + Vector(200, filter_args_n * 100), 
									   		   Vector(50, 50), Color(255, 255, 255), 
											   font, 20, "Ok", Color(0, 0, 0),
									   		   select_filter_func);
		dialog_box->AddObject(ok_button);		

		root->AddObject(dialog_box);
    }
}

void LastFilter::operator()()
{
	filter_manager->ApplyLastFilter();
}

void SavingParams::operator()()
{
	Vector position = main_window->GetPosition() + main_window->GetSize() / 2;
	Vector size(400, 300);
	ModalWindow* dialog_box = new ModalWindow(position, size, 
											  "Enter file name params", 
											  event_manager);

	position = position + Vector(50, 100);
	dialog_box->AddObject(new Label(position, 
									font, 20, "Filename"));
	EditBox* edit_box = new EditBox(position + Vector(200, 0), Vector(100, 50), 
									font, kLetterWidth, kLetterHeight, 20);
	dialog_box->AddObject(edit_box);

	SaveInFile* save_canvas_func = new SaveInFile(canvas, edit_box, dialog_box);
		
	TextButton* ok_button = new TextButton(position + Vector(200, 100), 
								   		   Vector(50, 50), Color(255, 255, 255), 
										   font, 20, "Ok", Color(0, 0, 0),
								   		   save_canvas_func);
	dialog_box->AddObject(ok_button);		

	main_window->AddObject(dialog_box);
}

void SaveInFile::operator()()
{
    Image img(canvas->GetData()->GetTexture());
	sf::Image image = img.GetImage();
	const char* file_name = file_name_edit->GetText();

	image.saveToFile(file_name);
	dialog_box->Close();
}

#endif // SYM_FUNCTORS