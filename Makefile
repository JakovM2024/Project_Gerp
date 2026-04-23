###
### Makefile for Gerp Project
###
### Author:  YOUR NAME HERE

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra
LDFLAGS  = -g3

## Main executable
gerp: main.o processing.o hashMap.o wrapper.o
	$(CXX) $(LDFLAGS) -o gerp main.o processing.o hashMap.o wrapper.o \
		FSTree.o DirNode.o

## Per-file compile rules
main.o: main.cpp wrapper.h processing.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

processing.o: processing.cpp processing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp -o processing.o

hashMap.o: hashMap.cpp hashMap.h
	$(CXX) $(CXXFLAGS) -c hashMap.cpp -o hashMap.o

wrapper.o: wrapper.cpp wrapper.h hashMap.h processing.h
	$(CXX) $(CXXFLAGS) -c wrapper.cpp -o wrapper.o

unit_test: unit_test_driver.o processing.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o processing.o DirNode.o FSTree.o

##
## Here is a special rule that removes all .o files besides the provided ones
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and
## a.out produced by running unit_test. First, we find all .o files
## that are not provided files, then we run rm -f on each found file
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
##
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out
