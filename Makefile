CXX = g++
CFLAGS = 
CPPFLAGS = -std=c++11 -Wall -Wextra -Wno-sign-compare -Werror

TESTS  = $(wildcard */*_test.cpp)
TARGETS = $(TESTS:.cpp=)

.PHONY : all
all: $(TARGETS)

.PHONY : clean
clean:
	rm $(TARGETS)

$(TARGETS): %:%.cpp gtest/gtest-all.o gtest/gtest_main.o
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ $< gtest/gtest-all.o gtest/gtest_main.o -I.
	$@

%.o:%.cc
	$(CXX) -I. -c $< -o $@
