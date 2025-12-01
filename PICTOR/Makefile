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
    Button.h \
    Color.h \
    Event.h \
    glut.h \
    GlutImport.h \
    Graphics.h \
    jpeg_decoder.h \
    Model.h \
    ObjAttr.h \
    ObjGeom.h \
    Tool.h \
    V2.h


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
