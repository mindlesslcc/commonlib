
OPT ?= -O2 -g2 -Werror

CXX=g++

INCLUDE_PATH = -I./

LDFLAGS = 

CXXFLAGS = -std=c++11 -Wall -fPIC $(OPT)

SRC = lru.cc

TEST = lru_test
LIBS = liblru.a liblru.so

all: $(LIBS) $(TEST)
	@echo 'Done'

lru_test: lru.o lru_test.o
	$(CXX) $^ -o $@ $(LDFLAGS)

liblru.a: lru.o
	$(AR) -rs $@ lru.o

liblru.so: lru.cc
	g++ $(CXXFLAGS) -shared -fPIC $(INCLUDE_PATH) -o $@ lru.cc  \

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(LIBS) $(TEST)

.PHONY: test
test:
