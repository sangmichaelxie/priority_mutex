# the compiler: gcc for C program, define as g++ for C++
  CXX = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CPPFLAGS  = -g -Wall -pedantic -O0 -std=c++11 -std=c++0x -I/usr/include -D_GLIBCXX_USE_SCHED_YIELD 
LDFLAGS = -lm -lpthread -L/usr/lib

HEADERS = priority_mutex.h

SOURCES = priorityMutexTest.cc

EXTRAS = priority_mutex.cc

OBJECTS = $(SOURCES:.cc=.o) $(EXTRAS:.cc=.o)

TARGETS = $(SOURCES:.cc=)

default = $(TARGETS)

priorityMutexTest: priorityMutexTest.o
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)
Makefile.dependencies:: $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) -MM $(SOURCES) > Makefile.dependencies

.PHONY: clean spartan
clean:
	@rm -f $(TARGETS) $(OBJECTS) core Makefile.dependencies
spartan: clean
	@rm -f *~
