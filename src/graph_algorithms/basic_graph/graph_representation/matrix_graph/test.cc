#include <iostream>

#include "matrix_graph.h"
#include "matrix_graph.cc"

int main() {
	MatrixGraph<8> matrixGraph(-1, "D:/cppRepos/clrs/src/graph_algorithms/data/tinyEWG.txt");
	std::cout << matrixGraph << std::endl;
	std::cout << matrixGraph.weight(0, 4) << std::endl;
}
