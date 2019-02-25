
.PHONY: all
all : srcComplexity srcMLXPathCount_t

srcComplexity : srcComplexity.o srcMLXPathCount.o
	g++ -std=c++11 srcComplexity.o srcMLXPathCount.o -lxml2 -o srcComplexity

srcComplexity.o : srcComplexity.cpp srcMLXPathCount.hpp
	g++ -std=c++11 -I/usr/include/libxml2 -c srcComplexity.cpp

srcMLXPathCount.o : srcMLXPathCount.cpp srcMLXPathCount.hpp
	g++ -std=c++11 -I/usr/include/libxml2 -c srcMLXPathCount.cpp

srcMLXPathCount_t : srcMLXPathCount_t.o srcMLXPathCount.o
	g++ -std=c++11 srcMLXPathCount_t.o srcMLXPathCount.o -lxml2 -o srcMLXPathCount_t

srcMLXPathCount_t.o : srcMLXPathCount_t.cpp srcMLXPathCount.hpp
	g++ -std=c++11 -c srcMLXPathCount_t.cpp

.PHONY: run
run : srcComplexity
	./srcComplexity srcMLXPathCount.cpp.xml

.PHONY: test
test : srcMLXPathCount_t
	./srcMLXPathCount_t

.PHONY: clean
clean :
	@rm -f srcComplexity srcComplexity.o srcMLXPathCount.o srcMLXPathCount_t srcMLXPathCount_t.o
