CXXFLAGS += -std=c++11 -I/usr/X11/include -I/opt/local/include -W -Wall -Wno-unused-parameter -Wno-deprecated-declarations
LDFLAGS += -L/usr/X11/lib -L/opt/local/lib

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: main.exe

run: main.exe
	./main.exe

main.exe: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) -lglut -lGLU -lGL -lGLEW -ldl -lpthread

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	-\rm *.o *.exe

