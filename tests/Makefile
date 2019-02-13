CC=g++
FLAGS=-std=c++0x
TARGETS := MultikeyMap_test MultikeyMap_test2

all : $(TARGETS)

% : %.cpp ../MultikeyMap.h
	$(CC) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
