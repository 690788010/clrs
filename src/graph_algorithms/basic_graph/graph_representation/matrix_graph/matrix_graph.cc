#include "matrix_graph.h"

template<int V>
MatrixGraph<V>::MatrixGraph(EWeightType val) : INVALID_WEIGHT{ val }, _v{ V }, _e{ 0 } {
	for (int i = 0; i < _v; i++) {
		for (int j = 0; j < _v; j++) {
			_matrix.at(i).at(j) = INVALID_WEIGHT;
		}
	}
}

template<int V>
void MatrixGraph<V>::add_edge(const EdgeTupleType& edge_tuple) {
	VIDType id1 = std::get<0>(edge_tuple);
	VIDType id2 = std::get<1>(edge_tuple);
	EWeightType wt = std::get<2>(edge_tuple);

	if (!validate_vid(id1) || !validate_vid(id2)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	if (has_edge(id1, id2)) {
		throw std::invalid_argument("edge add error,edge has already exist.");
	}

	_matrix.at(id1).at(id2) = wt;
	_e++;
};

template<int V>
void MatrixGraph<V>::update_weight(VIDType id1, VIDType id2, EWeightType wt) {
	if (!validate_vid(id1) || !validate_vid(id2)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	if (!has_edge(id1, id2)) {
		throw std::invalid_argument("edge's weight update error, edge does not exist.");
	}

	_matrix.at(id1).at(id2) = wt;
};

template<int V>
bool MatrixGraph<V>::has_edge(VIDType id_from, VIDType id_to) const {
	if (!validate_vid(id_from) || !validate_vid(id_to)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	return _matrix.at(id_from).at(id_to) != INVALID_WEIGHT;
};
