# Specify the compiler
CXX = g++

# Specify compiler flags
CXXFLAGS = -Wall -std=c++17

# Specify the target file
TARGET = car_app

# Specify the source files
SOURCES = VehicleConfiguration.cpp Database.cpp main.cpp Menu.cpp Exceptions.cpp

# Specify the object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# A pattern rule to create ".o" object files from ".cpp" source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Add a clean target
clean:
	rm -f $(TARGET) $(OBJECTS)
