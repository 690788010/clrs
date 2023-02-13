#pragma once

#include <array>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <iostream>

template<int V> 
class MatrixGraph {
public:
	typedef int VIDType;		///< 顶点编号的类型
	typedef float EWeightType;	///< 权重的类型
	typedef std::tuple<VIDType, VIDType, EWeightType> EdgeTupleType;	///< 边的三元素（顶点1编号，顶点2编号，权重）组成的元组

	/**
	 * @brief 默认构造函数，指定`INVALID_WEIGHT`为0
	 */
	MatrixGraph() : MatrixGraph(0) {};

	/**
	 * @brief 构造函数，指定`INVALID_WEIGHT`
	 * @param val 无效权重值
	 */
	MatrixGraph(EWeightType val);

	/**
	 * @brief 构造函数，指定`INVALID_WEIGHT`,并使用包含图信息的文件初始化图
	 * @param val 无效权重值
	 * @param filename 包含对应格式图信息的文件的路径
	 */
	MatrixGraph(EWeightType val, const std::string& filename);

	/**
	* @brief 添加一条边
	* @param edge_tuple 一条边的三元素元组
	* @return void
	* @details 为了便于计算，添加边时并不是添加`Edge`类型，而是`std::tuple<VIDType,VIDType,EWeightType>`类型的值。
	*
	* 如果指定节点之间的边已经存在，则抛出`std::invalid_argument`异常
	*
	* 要求边的顶点均在`[0,V)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效，直接返回而不作添加
	*/
	void add_edge(const EdgeTupleType& edge_tuple);

	/**
	* @brief 修改一条边的权重
	* @param id1 待修改边的第一个顶点id
	* @param id2 待修改边的第一个顶点id
	* @param wt 新的权重
	* @return void
	* @details 要求`id1`和`id2`均在`[0,N)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效，则抛出`std::invalid_argument`异常。
	*
	* 修改顶点`id1`和`id2`直接的边的权重为`wt`。如果指定结点之间的边不存在，则抛出`std::invalid_argument`异常。
	*/
	void update_weight(VIDType id1, VIDType id2, EWeightType wt);

	/**
	* @brief 判断图中指定顶点之间是否存在边
	* @param id_from: 第一个顶点的`id`
	* @param id_to: 第二个顶点的`id`
	* @return bool
	* @details 当`id_from`与`id_to`无效时，抛出异常
	*/
	bool has_edge(VIDType id_from, VIDType id_to) const;

	/**
	 * @brief 返回顶点v的邻接顶点id的集合
	 * @param id 顶点的`id`
	 * @return  顶点v的邻接顶点id的集合
	 */
	const std::set<VIDType> adj(VIDType id) const;

	/**
	 * @brief 返回图中所有边的三元素元组集合，这里集合采用`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
	 * @return 图中所有边的三元素元组集合
	 */
	const std::vector<EdgeTupleType> edge_tuples() const;

	/**
	 * @brief 返回图中指定顶点之间的边的权重
	 * @param id_from 第一个顶点的`id`
	 * @param id_to 第二个顶点的`id`
	 * @return 第一个顶点和第二个顶点之间的边的权重
	 * @details 要求边的顶点均在`[0,V)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效
	 *
	 * 当且仅当`id_from`与`id_to`之间存在边时返回该边的权重。如果指定结点之间的边不存在，则抛出`std::invalid_argument`异常。
	 */
	EWeightType weight(VIDType id_from, VIDType id_to) const;

	/**
	* @brief 验证顶点编号是否有效
	* @param vid 待验证的顶点编号
	* @return bool
	* @details 要求边的顶点均在`[0,V)`这个半闭半开区间。如果任何一个值超过该区间则认为顶点`id`无效
	*/
	bool validate_vid(VIDType vid) const;

	/**
	* @brief 自定义针对标准输出流的输出内容
	*/
	template<int V>
	friend std::ostream& operator<<(std::ostream& os, MatrixGraph<V> matrixGraph);

private:
	std::array<std::array<EWeightType, V>, V> _matrix;	// 图的矩阵
	const EWeightType INVALID_WEIGHT;	// 无效权重，是一个const值，一旦图被初始化之后就无法改变
	int _v;
	int _e;
};

/**
* @brief 自定义针对标准输出流的输出内容
*/
template<int V>
std::ostream& operator<<(std::ostream& os, MatrixGraph<V> matrixGraph);
