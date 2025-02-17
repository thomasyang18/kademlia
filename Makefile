# Compilers
CXX = g++

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Include directories
INCLUDES = -I./include

# Linker flags
LDFLAGS = -lboost_system -lpthread -lgtest -lgtest_main

ifeq ($(BUILD_TYPE), debug)
    CXXFLAGS += -O0 -DDEBUG -g
else
    CXXFLAGS += -O3 -DRELEASE
endif

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

# Find all C++ sources (.cpp) excluding main.cpp
CPP_SOURCES := $(shell find $(SRCDIR) -type f -name '*.cpp' ! -name 'main.cpp')
TEST_SOURCES := $(shell find $(TESTDIR) -type f -name '*.cpp')

# Convert sources to object files (preserving directory structure)
CPP_OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(CPP_SOURCES))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SOURCES))
MAIN_OBJECT = $(OBJDIR)/main.o

# Final targets
TARGET = $(BINDIR)/kademlia_client
TEST_TARGET = $(BINDIR)/kademlia_tests

# Ensure necessary directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

all: $(TARGET)

$(TARGET): $(CPP_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) $(CPP_OBJECTS) $(MAIN_OBJECT) -o $@ $(LDFLAGS)

tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(CPP_OBJECTS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(CPP_OBJECTS) -o $@ $(LDFLAGS)

# Rule to compile C++ (.cpp) files into .o files.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Dependency tracking for C++ sources (if needed)
# $(OBJDIR)/%.d: $(SRCDIR)/%.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< -o $@

# Include dependency files (if they exist)
-include $(CPP_OBJECTS:.o=.d)
-include $(TEST_OBJECTS:.o=.d)
-include $(OBJDIR)/main.o.d

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)

.PHONY: all clean tests
