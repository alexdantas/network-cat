# small-talk Makefile

EXE     = network-cat
CFLAGS  = -g -Wall -Wextra
LDFLAGS =

CXX      = g++
CXXFILES = $(shell find src -maxdepth 1 -type f -name '*.cpp')
OBJECTS  = $(CXXFILES:.cpp=.o)

all: $(EXE)
	# Build successful!

$(EXE): $(OBJECTS)
	# Linking...
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(CXX) $(CFLAGS) $< -c -o $@

clean:
	# Cleaning
	rm -f $(EXE) $(OBJECTS)

