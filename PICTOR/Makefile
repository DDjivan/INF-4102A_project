CXX = g++
CXXSTD = -std=c++17
CXXDEV = -lGL -lGLU -lglut
CXXFLAGS = $(CXXSTD) #-Wall



SOURCES = \
    Eleve.cpp \
	Color.cpp \
    GL.cpp \
    Graphics.cpp \
    picoPNG.cpp \
    Texture.cpp \
    V2.cpp

HEADERS = \
    Color.h \
    Event.h \
    Graphic.h \
    Model.h \
    ObjAttr.h \
    ObjGeom.h \
    Tool.h \
    V2.h \
    jpeg_decoder.h

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = Eleve.out



all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(CXXDEV)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
# 	rm -f *.o *.out



# END
