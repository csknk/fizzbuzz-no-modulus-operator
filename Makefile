SOURCES:= $(wildcard *.c) $(wildcard *.h)
OBJECTS:= $(wildcard *.c)
OUT:= bin/main
main: $(SOURCES)
	cc -W -Wall -g -o $(OUT) $(OBJECTS)
