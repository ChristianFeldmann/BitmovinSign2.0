CC=g++
src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

CCFLAGS = -std=c++11
LDFLAGS = -lm -lbcm2835
%.o: %.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

bin/Animator: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: 
	rm -f $(obj) bin/Animator
