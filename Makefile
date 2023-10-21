DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
RELEASE_FLAGS = -O2
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system

EXE_FILE = Exe/run

debug: vector_debug widget_debug button_debug menu_debug render_target_debug texture_debug font_debug label_debug window_debug clip_region_debug region_set_debug canvas_debug brush_debug tool_manager_debug circle_tool_debug shape_tool_debug rect_tool_debug line_tool_debug polyline_tool_debug fill_tool_debug image_debug spline_tool_debug cut_mull_rom_debug
	g++ $(SFML_FLAGS) $(DEBUG_FLAGS) Src/main.cpp Obj/Vector.o Obj/Widget.o Obj/Button.o Obj/Menu.o Obj/RenderTarget.o Obj/Texture.o Obj/Font.o Obj/Label.o Obj/Window.o Obj/ClipRegion.o Obj/RegionSet.o Obj/Canvas.o Obj/Brush.o Obj/ToolManager.o Obj/ShapeTool.o Obj/CircleTool.o Obj/RectTool.o Obj/LineTool.o Obj/PolylineTool.o Obj/FillTool.o Obj/Image.o Obj/SplineTool.o -o $(EXE_FILE)
release: vector_release widget_release button_release menu_release render_target_release texture_release font_release label_release window_release clip_region_release region_set_release canvas_release brush_release tool_manager_release circle_tool_release shape_tool_release rect_tool_release line_tool_release polyline_tool_release fill_tool_release image_release spline_tool_release cut_mull_rom_release
	g++ $(SFML_FLAGS) $(RELEASE_FLAGS) Src/main.cpp Obj/Vector.o Obj/Widget.o Obj/Button.o Obj/Menu.o Obj/RenderTarget.o Obj/Texture.o Obj/Font.o Obj/Label.o Obj/Window.o Obj/ClipRegion.o Obj/RegionSet.o Obj/Canvas.o Obj/Brush.o Obj/ToolManager.o Obj/ShapeTool.o Obj/CircleTool.o Obj/RectTool.o Obj/LineTool.o Obj/PolylineTool.o Obj/FillTool.o Obj/Image.o Obj/SplineTool.o Obj/CutMullRom.o -o $(EXE_FILE)

widget_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Widget.cpp -o Obj/Widget.o
widget_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Widget.cpp -o Obj/Widget.o

button_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Button/Button.cpp -o Obj/Button.o
button_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Button/Button.cpp -o Obj/Button.o

menu_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Menu/Menu.cpp -o Obj/Menu.o
menu_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Menu/Menu.cpp -o Obj/Menu.o

label_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Label/Label.cpp -o Obj/Label.o
label_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Label/Label.cpp -o Obj/Label.o

window_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Window/Window.cpp -o Obj/Window.o
window_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Window/Window.cpp -o Obj/Window.o

canvas_debug:
	g++ -c $(DEBUG_FLAGS) Src/Renderable/Widget/Canvas/Canvas.cpp -o Obj/Canvas.o
canvas_release:
	g++ -c $(RELEASE_FLAGS) Src/Renderable/Widget/Canvas/Canvas.cpp -o Obj/Canvas.o

vector_debug:
	g++ -c $(DEBUG_FLAGS) Src/Vector/Vector.cpp -o Obj/Vector.o
vector_release:
	g++ -c $(RELEASE_FLAGS) Src/Vector/Vector.cpp -o Obj/Vector.o

render_target_debug:
	g++ -c $(DEBUG_FLAGS) Src/RenderTarget/RenderTarget.cpp -o Obj/RenderTarget.o
render_target_release:
	g++ -c $(RELEASE_FLAGS) Src/RenderTarget/RenderTarget.cpp -o Obj/RenderTarget.o

texture_debug:
	g++ -c $(DEBUG_FLAGS) Src/Texture/Texture.cpp -o Obj/Texture.o
texture_release:
	g++ -c $(RELEASE_FLAGS) Src/Texture/Texture.cpp -o Obj/Texture.o

image_debug:
	g++ -c $(DEBUG_FLAGS) Src/Image/Image.cpp -o Obj/Image.o
image_release:
	g++ -c $(RELEASE_FLAGS) Src/Image/Image.cpp -o Obj/Image.o

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

run:
	./$(EXE_FILE)

preparation:
	mkdir Obj
	mkdir Exe

