#CC specifies which compiler we're using
CC = g++

#OBJS specifies which files to compile as part of the project
OBJS = ./src/*.cpp ./src/gamestate/*.cpp ./src/fonts/*.cpp

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -I./include -I./include/utils -I./include/fonts -std=c++17

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our executable
OBJ_NAME = ./bin/SDL2_Tactics

clean:
	rm -f $(OBJ_NAME)
	rm -f ./src/*.o

# This is the target that compiles our executable
build : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./bin/SDL2_Tactics

dev: clean build
# Target to clean up compiled files


.PHONY: all clean  # Declares 'all' and 'clean' as phony targets