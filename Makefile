all:   # Add new files to this target's compil chain
	g++ -o Main main.cpp node.cpp node.h pythonpp.cpp pythonpp.h  tree.cpp tree.h 

run:
	./Main && rm Main

# Each class gets its own target for testing purposes
node:
	g++ -o testNode node.cpp node.h pythonpp.cpp pythonpp.h  

test_node:
	./testNode && rm testNode

tree:
	g++ -o testTree tree.cpp tree.h node.cpp node.h pythonpp.cpp pythonpp.h  

test_tree:
	./testTree && rm testTree

# Nothing here yet
clean:
