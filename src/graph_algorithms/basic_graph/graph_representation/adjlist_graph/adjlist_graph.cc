#include "adjlist_graph.h"

template<int V>
ADJListGraph<V>::ADJListGraph() {
	_v = V;
	_e = 0;
};

template<int V>
ADJListGraph<V>::ADJListGraph(const std::string& filename) : _v{ V }, _e{ 0 } {
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

	if (e != _e) {
		throw std::invalid_argument("The e info in the file is incorrect.");
	}
};

template<int V>
void ADJListGraph<V>::add_edge(const EdgeTupleType& edge_tuple) {
	VIDType id1 = std::get<0>(edge_tuple);
	VIDType id2 = std::get<1>(edge_tuple);
	EWeightType wt = std::get<2>(edge_tuple);

	if (!validate_vid(id1) || !validate_vid(id2)) {
		throw std::invalid_argument("vertex id is invalid!");
	}

	if (has_edge(id1, id2)) {
		throw std::invalid_argument("edge add error,edge has already exist.");
	}

	_array.at(id1).push_back(std::make_pair(id2, wt));
	_e++;
};

template<int V>
void ADJListGraph<V>::update_weight(VIDType id1, VIDType id2, EWeightType wt) {
	if (!validate_vid(id1) || !validate_vid(id2)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	if (!has_edge(id1, id2)) {
		throw std::invalid_argument("edge's weight update error, edge does not exist.");
	}
	auto& vec = _array.at(id1);
	for (auto& pair : vec) {
		if (pair.first == id2) {
			pair.second = wt;
			break;
		}
	}
}

template<int V>
bool ADJListGraph<V>::has_edge(VIDType id_from, VIDType id_to) const {
	if (!validate_vid(id_from) || !validate_vid(id_to)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	auto& vec = _array.at(id_from);
	for (const auto& pair : vec) {
		if (pair.first == id_to) {
			return true;
		}
	}
	return false;
};

template<int V>
const std::set<typename ADJListGraph<V>::VIDType> ADJListGraph<V>::adj(VIDType id) const {
	if (!validate_vid(id)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	std::set<int> res;
	for (const auto& pair : _array.at(id)) {
		res.insert(pair.first);
	}
	return res;
};

template<int V>
const std::vector<typename ADJListGraph<V>::EdgeTupleType> ADJListGraph<V>::edge_tuples() const {
	std::vector<EdgeTupleType> res;
	for (int i = 0; i < _v; i++) {
		for (const auto& pair : _array.at(i)) {
			res.push_back(std::make_tuple(i, pair.first, pair.second));
		}
	}
	return res;
};

template<int V>
typename ADJListGraph<V>::EWeightType ADJListGraph<V>::weight(VIDType id_from, VIDType id_to) const {
	if (!validate_vid(id_from) || !validate_vid(id_to)) {
		throw std::invalid_argument("vertex id is invalid!");
	}
	if (!has_edge(id_from, id_to)) {
		throw std::invalid_argument("edge does not exist.");
	}
	const auto& vec = _array.at(id_from);
	for (const auto& pair : vec) {
		if (pair.first == id_to) {
			return pair.second;
		}
	}
};

template<int V>
bool ADJListGraph<V>::validate_vid(VIDType vid) const {
	if (vid < 0 || vid >= V) {
		return false;
	}
	return true;
};

template<int V>
std::ostream& operator<<(std::ostream& os, ADJListGraph<V> adjListGraph) {
	int v = adjListGraph._v;
	os << "V = " << v << ", E = " << adjListGraph._e << "\n";
	for (int i = 0; i < v; i++) {
		os << i << ": ";
		auto& vec = adjListGraph._array.at(i);
		for (const auto& pair : vec) {
			os << pair.first << ":" << pair.second << ", ";
		}
		os << "\n";
	}
	return os;
}
