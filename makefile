include colors.mk
CXXFLAGS += -std=c++11 -I/usr/X11/include -I/opt/homebrew/include -W -Wall -Wno-unused-parameter -Wno-deprecated-declarations -Werror=all

# brew install
# - mesa
# - mesa-glu
# - freeglut
# - GLEW
LDFLAGS +=  -L/opt/homebrew/lib

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: main.exe

run: main.exe
	./main.exe

main.exe: $(OBJ)
	$(call make_echo_link_cxx_executable)
	$(at) $(CXX) $(LDFLAGS) -o $@ $(OBJ) -lglut -lGLU -lGL -lGLEW -ldl -lpthread

.cpp.o:
	$(call make_echo_build_cxx_object)
	$(at) $(CXX) $(CXXFLAGS) -c $<

clean:
	$(at) -\rm *.o *.exe

