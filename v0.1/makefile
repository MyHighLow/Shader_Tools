PREFIX := D:/usr/local/src/shader_tools/v0.1

CC := cl
CL := link
LB := lib

CC_OPTIONS := /nologo /std:c++latest /EHsc /MD
CL_OPTIONS := /NOLOGO /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup 

ARGS ?= 

DLL_PATHS :=
IPATHS := -I$(PREFIX)/include
LPATHS := /LIBPATH:$(PREFIX)/lib
LIBS := Shell32.lib OpenGL32.lib Gdiplus.lib

# GLFW dependency
DLL_PATHS := $(DLL_PATHS);D:/usr/local/packages/glfw-3.3.3/glfw-3.3.3.bin.WIN64/lib-vc2019
IPATHS := $(IPATHS) -ID:/usr/local/packages/glfw-3.3.3/glfw-3.3.3.bin.WIN64/include
LPATHS := $(LPATHS) /LIBPATH:D:/usr/local/packages/glfw-3.3.3/glfw-3.3.3.bin.WIN64/lib-vc2019
LIBS := $(LIBS) glfw3.lib

# GLEW dependency
DLL_PATHS := $(DLL_PATHS);D:/usr/local/packages/glew-2.1.0-win32/glew-2.1.0/bin/Release/x64
IPATHS := $(IPATHS) -ID:/usr/local/packages/glew-2.1.0-win32/glew-2.1.0/include
LPATHS := $(LPATHS) /LIBPATH:D:/usr/local/packages/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64
LIBS := $(LIBS) glew32.lib

# freeglut dependency
DLL_PATHS := $(DLL_PATHS);D:/usr/local/packages/freeglut/bin
IPATHS := $(IPATHS) -ID:/usr/local/packages/freeglut/include
LPATHS := $(LPATHS) /LIBPATH:D:/usr/local/packages/freeglut/lib
LIBS := $(LIBS) freeglutd.lib

src/%.cpp:
	$(CC) -c $@ $(CC_OPTIONS) $(IPATHS) /Fo$(PREFIX)/obj/$*.obj
	
# LINK:
# 	$(CL) $(wildcard $(PREFIX)/obj/*.obj) $(CL_OPTIONS) $(LPATHS) $(LIBS) /OUT:$(PREFIX)/bin/main.exe

# RUN:
# 	powershell -Command "\$$env:PATH += \"$(DLL_PATHS)\"; $(PREFIX)/bin/main.exe $(ARGS)"

LIB:
	$(LB) /NOLOGO $(PREFIX)/obj/* /out:$(PREFIX)/lib/shader_tools.lib