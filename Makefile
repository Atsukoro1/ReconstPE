CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -mwindows \
	-Iexternal/imgui \
	-Iexternal/imgui/backends \
	-Iexternal/phnt/include \
	-Iexternal/compat

LIBS := \
	-ld3d11 \
	-ldxgi \
	-ld3dcompiler \
	-luser32 \
	-lgdi32 \
	-limm32 \
	-lole32 \
	-loleaut32 \
	-luuid \
	-ldwmapi

SRC := \
	src/main.cpp \
	src/PEParser.cpp \
	src/Gui.cpp \
	external/imgui/imgui.cpp \
	external/imgui/imgui_draw.cpp \
	external/imgui/imgui_tables.cpp \
	external/imgui/imgui_widgets.cpp \
	external/imgui/backends/imgui_impl_win32.cpp \
	external/imgui/backends/imgui_impl_dx11.cpp

OUT := app.exe

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)