# Compilers
CXX = g++

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Include directories 
INCLUDES = -I./include 


ifeq ($(BUILD_TYPE), debug)
    CXXFLAGS += -O0 -DDEBUG -g 
else
    CXXFLAGS += -O3 -DRELEASE
endif

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Find all C++ sources (.cpp) and CUDA sources (.cu)
CPP_SOURCES := $(shell find $(SRCDIR) -type f -name '*.cpp')

# Convert sources to object files (preserving directory structure)
CPP_OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(CPP_SOURCES))

# Place main.o at the beginning if it exists
CPP_OBJECTS := $(if $(filter $(OBJDIR)/main.o, $(CPP_OBJECTS)), \
             $(OBJDIR)/main.o $(filter-out $(OBJDIR)/main.o, $(CPP_OBJECTS)), \
             $(CPP_OBJECTS))

# Final target: link both C++ and CUDA object files
TARGET = $(BINDIR)/kademlia_client

# Ensure necessary directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

all: $(TARGET)

$(TARGET): $(CPP_OBJECTS) 
	$(CXX) $(CXXFLAGS) $(CPP_OBJECTS) -o $@ $(CXXLIB) 

# Rule to compile C++ (.cpp) files into .o files.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Dependency tracking for C++ sources (if needed)
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< -o $@

# Include dependency files (if they exist)
-include $(CPP_OBJECTS:.o=.d)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
