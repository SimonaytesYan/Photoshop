DEBUG_SHARED_FLAGS   = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DEBUG_FLAGS   		 = -Wl,--export-dynamic -fPIE -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
RELEASE_FLAGS 		 = -Wl,--export-dynamic -fPIE -O2 -fsanitize=address
SFML_FLAGS    		 = -lsfml-graphics -lsfml-window -lsfml-system
SHARED_OBJ_LAB_FLAGS = -c -fPIC
SHARED_LAB_FLAGS     = -shared

GREEN_COLOR   = '\033[0;32m'
DEFAULT_COLOR = '\033[0m'

EXE_FILE = Exe/run

debug: compile_plugins widget_debug button_debug menu_debug render_target_debug texture_debug font_debug label_debug window_debug clip_region_debug region_set_debug canvas_debug brush_debug tool_manager_debug circle_tool_debug shape_tool_debug rect_tool_debug line_tool_debug polyline_tool_debug fill_tool_debug  spline_tool_debug cut_mull_rom_debug event_manager_debug filter_manager_debug brightness_filter_debug vertical_menu_debug horizontal_menu_debug edit_box_debug scrollbar_debug gui_debug rect_widget_debug get_plugins_debug canvas_manager_debug
	g++ $(SFML_FLAGS) $(DEBUG_FLAGS) Src/main.cpp Obj/Widget.o Obj/Button.o Obj/Menu.o Obj/RenderTarget.o Obj/Texture.o Obj/Font.o Obj/Label.o Obj/Window.o Obj/ClipRegion.o Obj/RegionSet.o Obj/Canvas.o Obj/Brush.o Obj/ToolManager.o Obj/ShapeTool.o Obj/CircleTool.o Obj/RectTool.o Obj/LineTool.o Obj/PolylineTool.o Obj/FillTool.o Obj/SplineTool.o Obj/CutMullRom.o Obj/EventManager.o Obj/FilterManager.o Obj/BrightnessFilter.o Obj/HorizontalMenu.o Obj/VerticalMenu.o Obj/EditBox.o Obj/ScrollBar.o Obj/Gui.o Obj/RectangleWidget.o Obj/GetPlugins.o Obj/CanvasManager.o -o $(EXE_FILE)
	echo $(GREEN_COLOR) Compilation ends successfully! $(DEFAULT_COLOR)
release: compile_plugins widget_release button_release menu_release render_target_release texture_release font_release label_release window_release clip_region_release region_set_release canvas_release brush_release tool_manager_release circle_tool_release shape_tool_release rect_tool_release line_tool_release polyline_tool_release fill_tool_release  spline_tool_release cut_mull_rom_release event_manager_release filter_manager_release brightness_filter_release vertical_menu_release horizontal_menu_release edit_box_release scrollbar_release gui_release rect_widget_release get_plugins_release canvas_manager_release
	g++ $(SFML_FLAGS) $(RELEASE_FLAGS) Src/main.cpp Obj/Widget.o Obj/Button.o Obj/Menu.o Obj/RenderTarget.o Obj/Texture.o Obj/Font.o Obj/Label.o Obj/Window.o Obj/ClipRegion.o Obj/RegionSet.o Obj/Canvas.o Obj/Brush.o Obj/ToolManager.o Obj/ShapeTool.o Obj/CircleTool.o Obj/RectTool.o Obj/LineTool.o Obj/PolylineTool.o Obj/FillTool.o Obj/SplineTool.o Obj/CutMullRom.o Obj/EventManager.o Obj/FilterManager.o Obj/BrightnessFilter.o Obj/HorizontalMenu.o Obj/VerticalMenu.o Obj/EditBox.o Obj/ScrollBar.o Obj/Gui.o Obj/RectangleWidget.o Obj/GetPlugins.o Obj/CanvasManager.o -o $(EXE_FILE)
	echo $(GREEN_COLOR) Compilation ends successfully! $(DEFAULT_COLOR)

compile_plugins: compile_curve_plugin compile_brush_plugin compile_white_black_plugin
	echo $(GREEN_COLOR) Plugins are compiled! $(DEFAULT_COLOR)

compile_brush_plugin:
	g++ $(SHARED_OBJ_LAB_FLAGS) -o Obj/CutMulRomPlug.o Plugins/Brush/CutMullRom/CutMullRom.cpp
	g++ $(SHARED_OBJ_LAB_FLAGS) -o Obj/BrushPlug.o Plugins/Brush/Brush.cpp
	gcc $(SHARED_LAB_FLAGS) -o Plugins/Brush.so Obj/BrushPlug.o Obj/CutMulRomPlug.o

compile_white_black_plugin:
	g++ $(SHARED_OBJ_LAB_FLAGS) -o Obj/WhiteBlack.o Plugins/WhiteBlack.cpp 
	gcc $(SHARED_LAB_FLAGS) -o Plugins/WhiteBlack.so Obj/WhiteBlack.o 

compile_curve_plugin:
	g++ -g $(SHARED_OBJ_LAB_FLAGS) -o Obj/CurveCutMulRom.o Plugins/Curve/CutMullRom.cpp
	g++ -g $(SHARED_OBJ_LAB_FLAGS) -o Obj/CurvePlugin.o Plugins/Curve/Curve.cpp 
	gcc $(SHARED_LAB_FLAGS) -o Plugins/SymCurve.so Obj/CurvePlugin.o Obj/CurveCutMulRom.o

get_plugins_debug:
	g++ -c $(DEBUG_FLAGS) Src/GetPlugins/GetPlugins.cpp -o Obj/GetPlugins.o
get_plugins_release:
	g++ -c $(RELEASE_FLAGS) Src/GetPlugins/GetPlugins.cpp -o Obj/GetPlugins.o

canvas_manager_debug:
	g++ -c $(DEBUG_FLAGS) Src/CanvasManager/CanvasManager.cpp -o Obj/CanvasManager.o
canvas_manager_release:
	g++ -c $(RELEASE_FLAGS) Src/CanvasManager/CanvasManager.cpp -o Obj/CanvasManager.o

widget_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Widget.cpp -o Obj/Widget.o
widget_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Widget.cpp -o Obj/Widget.o

button_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Button/Button.cpp -o Obj/Button.o
button_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Button/Button.cpp -o Obj/Button.o

scrollbar_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/ScrollBar/ScrollBar.cpp -o Obj/ScrollBar.o
scrollbar_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/ScrollBar/ScrollBar.cpp -o Obj/ScrollBar.o

menu_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Menu/Menu.cpp -o Obj/Menu.o
menu_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Menu/Menu.cpp -o Obj/Menu.o

vertical_menu_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Menu/VerticalMenu/VerticalMenu.cpp -o Obj/VerticalMenu.o
vertical_menu_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Menu/VerticalMenu/VerticalMenu.cpp -o Obj/VerticalMenu.o

horizontal_menu_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Menu/HorizontalMenu/HorizontalMenu.cpp -o Obj/HorizontalMenu.o
horizontal_menu_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Menu/HorizontalMenu/HorizontalMenu.cpp -o Obj/HorizontalMenu.o

label_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Label/Label.cpp -o Obj/Label.o
label_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Label/Label.cpp -o Obj/Label.o

window_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Window/Window.cpp -o Obj/Window.o
window_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Window/Window.cpp -o Obj/Window.o

rect_widget_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/RectangleWidget/RectangleWidget.cpp -o Obj/RectangleWidget.o
rect_widget_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/RectangleWidget/RectangleWidget.cpp -o Obj/RectangleWidget.o

canvas_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Canvas/Canvas.cpp -o Obj/Canvas.o
canvas_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Canvas/Canvas.cpp -o Obj/Canvas.o

edit_box_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/EditBox/EditBox.cpp -o Obj/EditBox.o
edit_box_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/EditBox/EditBox.cpp -o Obj/EditBox.o

render_target_debug:
	g++ -c $(DEBUG_FLAGS) Src/RenderTarget/RenderTarget.cpp -o Obj/RenderTarget.o
render_target_release:
	g++ -c $(RELEASE_FLAGS) Src/RenderTarget/RenderTarget.cpp -o Obj/RenderTarget.o

texture_debug:
	g++ -c $(DEBUG_FLAGS) Src/Texture/Texture.cpp -o Obj/Texture.o
texture_release:
	g++ -c $(RELEASE_FLAGS) Src/Texture/Texture.cpp -o Obj/Texture.o

gui_debug:
	g++ -c $(DEBUG_FLAGS) Src/Gui/Gui.cpp -o Obj/Gui.o
gui_release:
	g++ -c $(RELEASE_FLAGS) Src/Gui/Gui.cpp -o Obj/Gui.o

font_debug:
	g++ -c $(DEBUG_FLAGS) Src/Font/Font.cpp -o Obj/Font.o
font_release:
	g++ -c $(RELEASE_FLAGS) Src/Font/Font.cpp -o Obj/Font.o

cut_mull_rom_debug:
	g++ -c $(DEBUG_FLAGS) Src/CutMullRom/CutMullRom.cpp -o Obj/CutMullRom.o
cut_mull_rom_release:
	g++ -c $(RELEASE_FLAGS) Src/CutMullRom/CutMullRom.cpp -o Obj/CutMullRom.o

clip_region_debug:
	g++ -c $(DEBUG_FLAGS) Src/ClipRegion/ClipRegion.cpp -o Obj/ClipRegion.o
clip_region_release:
	g++ -c $(RELEASE_FLAGS) Src/ClipRegion/ClipRegion.cpp -o Obj/ClipRegion.o

region_set_debug:
	g++ -c $(DEBUG_FLAGS) Src/RegionSet/RegionSet.cpp -o Obj/RegionSet.o
region_set_release:
	g++ -c $(RELEASE_FLAGS) Src/RegionSet/RegionSet.cpp -o Obj/RegionSet.o

brush_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/Brush/Brush.cpp -o Obj/Brush.o
brush_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/Brush/Brush.cpp -o Obj/Brush.o

fill_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/FillTool/FillTool.cpp -o Obj/FillTool.o
fill_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/FillTool/FillTool.cpp -o Obj/FillTool.o

shape_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/ShapeTool/ShapeTool.cpp -o Obj/ShapeTool.o
shape_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/ShapeTool/ShapeTool.cpp -o Obj/ShapeTool.o

circle_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/ShapeTool/CircleTool/CircleTool.cpp -o Obj/CircleTool.o
circle_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/ShapeTool/CircleTool/CircleTool.cpp -o Obj/CircleTool.o

rect_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/ShapeTool/RectTool/RectTool.cpp -o Obj/RectTool.o
rect_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/ShapeTool/RectTool/RectTool.cpp -o Obj/RectTool.o

line_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/ShapeTool/LineTool/LineTool.cpp -o Obj/LineTool.o
line_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/ShapeTool/LineTool/LineTool.cpp -o Obj/LineTool.o

polyline_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/PolylineTool/PolylineTool.cpp -o Obj/PolylineTool.o
polyline_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/PolylineTool/PolylineTool.cpp -o Obj/PolylineTool.o

spline_tool_debug:
	g++ -c $(DEBUG_FLAGS) Src/Tool/SplineTool/SplineTool.cpp -o Obj/SplineTool.o
spline_tool_release:
	g++ -c $(RELEASE_FLAGS) Src/Tool/SplineTool/SplineTool.cpp -o Obj/SplineTool.o

tool_manager_debug:
	g++ -c $(DEBUG_FLAGS) Src/ToolManager/ToolManager.cpp -o Obj/ToolManager.o
tool_manager_release:
	g++ -c $(RELEASE_FLAGS) Src/ToolManager/ToolManager.cpp -o Obj/ToolManager.o

event_manager_debug:
	g++ -c $(DEBUG_FLAGS) Src/EventManager/EventManager.cpp -o Obj/EventManager.o
event_manager_release:
	g++ -c $(RELEASE_FLAGS) Src/EventManager/EventManager.cpp -o Obj/EventManager.o

filter_manager_debug:
	g++ -c $(DEBUG_FLAGS) Src/FilterManager/FilterManager.cpp -o Obj/FilterManager.o
filter_manager_release:
	g++ -c $(RELEASE_FLAGS) Src/FilterManager/FilterManager.cpp -o Obj/FilterManager.o

brightness_filter_debug:
	g++ -c $(DEBUG_FLAGS) Src/Filter/BrightnessFilter/BrightnessFilter.cpp -o Obj/BrightnessFilter.o
brightness_filter_release:
	g++ -c $(RELEASE_FLAGS) Src/Filter/BrightnessFilter/BrightnessFilter.cpp -o Obj/BrightnessFilter.o

clean:
	cd Obj
	rm *.o
	cd ..
	rm $(EXE_FILE)

run:
	./$(EXE_FILE)

preparation:
	mkdir Obj
	mkdir Exe
