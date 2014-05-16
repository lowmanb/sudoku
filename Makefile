CXX      = $(shell fltk-config --cxx)
DEBUG    = -g
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags ) -O3 -I.
LDFLAGS  = $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK     = $(CXX)
POSTBUILD  = fltk-config --post

TARGET = sudoku
OBJS = main.cpp startWindow.cpp manInput.cpp board.cpp timer.cpp outWindow.cpp

.SUFFIXES: .o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
main.o: main.cpp
startWindow.o: startWindow.cpp startWindow.h
manInput.o: manInput.cpp manInput.h
board.o: board.cpp board.h
timer.o: timer.cpp timer.h
outWindow.o: outWindow.cpp outWindow.h

clean: $(TARGET) $(OBJS)
	@rm -f *.o 2> /dev/null
	@rm -f $(TARGET) 2> /dev/null	
