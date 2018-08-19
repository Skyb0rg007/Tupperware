CXX=clang++
CXXFLAGS=-Wall -Wextra -std=c++11
RM=rm -f

SRCS=BinarySearchTree.cpp BinaryTree.cpp Survivor.cpp Queue.cpp
OBJS=BinarySearchTree.o BinaryTree.o Survivor.o Queue.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

survivor: $(OBJS) survivor-driver.o
	$(CXX) $(CXXFLAGS) -o survivor $(OBJS) survivor-driver.o

test-bt: $(OBJ) test-bt-driver.o
	$(CXX) $(CXXFLAGS) -o test-bt $(OBJS) test-bt-driver.o

test-bst: $(OBJ) test-bst-driver.o
	$(CXX) $(CXXFLAGS) -o test-bst $(OBJS) test-bst-driver.o

clean:
	$(RM) $(OBJS)

