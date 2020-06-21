CC := g++

CFLAGS := -std=c++11
INCLUDE := -I./include

SRC := $(wildcard *.cpp)
targets := $(patsubst %.cpp,%.out,$(SRC))

all: $(targets)

%.out: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(targets)
