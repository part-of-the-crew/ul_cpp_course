appname := merch

#CXX = g++-10
CXX = clang++-12

CXXFLAGS := -Wall -Wextra -Wpedantic -g -std=c++20

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)


depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects) $(appname) *~ .depend

dist-clean: clean
	rm -f *~ .depend
	
#include .depend
