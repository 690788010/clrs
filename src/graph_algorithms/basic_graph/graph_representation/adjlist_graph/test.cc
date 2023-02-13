#include <iostream>

#include "adjlist_graph.h"
#include "adjlist_graph.cc"

int main() {
	ADJListGraph<250> adjListGraph("D:/cppRepos/clrs/src/graph_algorithms/data/mediumEWG.txt");
	
	std::cout << adjListGraph.weight(1, 72) << std::endl;
}
