#changing platform dependant stuff, do not change this
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -std=c++11
CC=g++
EXEEXT=
MATH_LIB = PMath
SG_LIB = SceneGraph

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
	# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

PROGRAM_NAME= starFoxClone

#run target to compile and build, and then launch the executable
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

$(PROGRAM_NAME): main.o $(MATH_LIB)/PVector.o $(MATH_LIB)/PPoint.o $(SG_LIB)/node.o $(SG_LIB)/nodeGroup.o $(SG_LIB)/nodeModel.o $(SG_LIB)/nodeTransform.o $(SG_LIB)/sceneGraph.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o $(PROGRAM_NAME)$(EXEEXT) $(MATH_LIB)/*.o $(SG_LIB)/*.o