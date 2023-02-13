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
MatrixGraph<V>::MatrixGraph(EWeightType val, const std::string& filename) : INVALID_WEIGHT{ val }, _v{ V }, _e{ 0 } {
	for (int i = 0; i < _v; i++) {
		for (int j = 0; j < _v; j++) {
			_matrix.at(i).at(j) = INVALID_WEIGHT;
		}
	}

	std::ifstream ifs;
	ifs.open(filename, std::ios::in);
	if (!ifs.is_open()) {
		throw std::invalid_argument("文件打开失败!");
	}
	std::string buf;
	// 读取顶点数量
	getline(ifs, buf);
	int v = stoi(buf);
	if (v > V) {
		throw std::invalid_argument("the v info in the file must be less than V.");
	}
	// 读取边数量
	getline(ifs, buf);
	int e = stoi(buf);

	// 添加边
	while (getline(ifs, buf)) {
		size_t idx = buf.find(" ");
		size_t idx2 = buf.find(" ", idx + 1);
		VIDType id1 = stoi(buf.substr(0, idx));
		VIDType id2 = stoi(buf.substr(idx + 1, idx2));
		EWeightType wt = stof(buf.substr(idx2 + 1));
		this->add_edge(std::make_tuple(id1, id2, wt));
	}

	// 如果文件头部的边数量信息与实际边数量不相等则抛出异常
	if (e != _e) {
		throw std::invalid_argument("The e info in the file is incorrect.");
	}
};

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

template<int V>
const std::set<typename MatrixGraph<V>::VIDType> MatrixGraph<V>::adj(VIDType id) const {
	if (!validate_vid(id)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	std::set<int> res;
	for (int i = 0; i < _v; i++) {
		if (_matrix.at(id).at(i) != INVALID_WEIGHT) {
			res.insert(i);
		}
	}
	return res;
};

template<int V>
const std::vector<typename MatrixGraph<V>::EdgeTupleType> MatrixGraph<V>::edge_tuples() const {
	std::vector<EdgeTupleType> res;
	for (int i = 0; i < _v; i++) {
		for (int j = 0; j < _v; j++) {
			if (_matrix.at(i).at(j) != INVALID_WEIGHT) {
				res.push_back(std::make_tuple(i, j, _matrix.at(i).at(j)));
			}
		}
	}
	return res;
};

template<int V>
typename MatrixGraph<V>::EWeightType MatrixGraph<V>::weight(VIDType id_from, VIDType id_to) const {
	if (!validate_vid(id_from) || !validate_vid(id_to)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	if (!has_edge(id_from, id_to)) {
		throw std::invalid_argument("edge does not exist.");
	}
	return _matrix.at(id_from).at(id_to);
};

template<int V>
bool MatrixGraph<V>::validate_vid(VIDType vid) const {
	if (vid < 0 || vid >= V) {
		return false;
	}
	return true;
};

template<int V>
std::ostream& operator<<(std::ostream& os, MatrixGraph<V> matrixGraph) {
	int v = matrixGraph._v;
	os << "V = " << v << ", E = " << matrixGraph._e << "\n";
	for (int i = 0; i < v; i++) {
		os << i << ": ";
		for (int j = 0; j < v; j++) {
			std::cout << matrixGraph._matrix.at(i).at(j) << ", ";
		}
		os << "\n";
	}
	return os;
}
