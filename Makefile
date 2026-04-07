###
### Makefile for Gerp Project
###
### Author:  YOUR NAME HERE

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra
LDFLAGS = -g3 

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

run_test: processing.o main.o 
	$(CXX) $(LDFLAGS) -o run_test main.o processing.o FSTree.o DirNode.o

main.o: main.cpp
	$(CXX) $(LDFLAGS) -c main.cpp -o main.o

processing.o: processing.h processing.cpp
	$(CXX) $(LDFLAGS) -c processing.cpp -o processing.o


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

