CC=g++
FLAGS=-std=c++0x
TARGETS := MultikeyMap_test MultikeyMap_test2

TARGETS := $(patsubst %,$(TAG)%,$(TARGETS))

all : $(TARGETS)

$(TAG)% : %.cpp ../MultikeyMap.h
	$(CC) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
