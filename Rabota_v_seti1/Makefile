# Усложненный make-file.  Введены переменные для параметров компиляции и исполняемых файлов

.PHONY: all debug release clean

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
RELEASE_EXEC  = main
DEBUG_EXEC    = main-dbg
INPUT_FILE	  = main.cpp
#SOURCE        =

all: debug release clean

debug: $(DEBUG_EXEC)

main-dbg: $(INPUT_FILE)
	g++ $(DEBUG_FLAGS) $(INPUT_FILE) -o $(DEBUG_EXEC) 

release: $(RELEASE_EXEC)

main: $(INPUT_FILE)
	g++ $(RELEASE_FLAGS) $(INPUT_FILE) -o $(RELEASE_EXEC)

clean:
	rm -f $(DEBUG_EXEC)

