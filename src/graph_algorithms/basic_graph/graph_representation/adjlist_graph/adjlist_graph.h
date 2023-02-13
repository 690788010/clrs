/**
 * @file adjlist_graph.h
 * @brief ͷ�ļ�
 * @details ͼ���ڽӱ�ʵ��
 * @author yangqiao
 * @version beta 1.0
 * @date 2023.02.10
 * @copyright 
 */

#pragma once

#include <array>
#include <vector>
#include <set>
#include <stdexcept>
#include <fstream>
#include <string>
#include <tuple>
#include <iostream>

/**
 * @brief ͼ���ڽӱ��ʾ���㷨����22��22.1��
 * @details ͼ���ڽӱ���Ҫ����һ�����ݣ�
 * - `_array`���ڽӱ�����Ϊ`std::array<std::vector<std::pair<VIDType,EWeightType>>,V> `��Ϊ`V`�У�ÿһ�д���һ���ڵ�
 */
template<int V> class ADJListGraph {
public:
	typedef int VIDType;		///< �����ŵ�����
	typedef float EWeightType;	///< Ȩ�ص�����
	typedef std::tuple<VIDType, VIDType, EWeightType> EdgeTupleType;	///< �ߵ���Ԫ�أ�����1��ţ�����2��ţ�Ȩ�أ���ɵ�Ԫ��

	/**
	* @brief ���캯��
	*/
	ADJListGraph();

	/**
	* @brief ���캯��
	* @param filename ������Ӧ��ʽͼ��Ϣ���ļ���·��
	*/
	ADJListGraph(const std::string& filename);

	/**
	* @brief ���һ����
	* @param edge_tuple һ���ߵ���Ԫ��Ԫ��
	* @return void
	* @details Ϊ�˱��ڼ��㣬��ӱ�ʱ���������`Edge`���ͣ�����`std::tuple<VIDType,VIDType,EWeightType>`���͵�ֵ��
	* 
	* ���ָ���ڵ�֮��ı��Ѿ����ڣ����׳�`std::invalid_argument`�쳣
	* 
	* Ҫ��ߵĶ������`[0,V)`�����հ뿪���䡣����κ�һ��ֵ��������������Ϊ����`id`��Ч��ֱ�ӷ��ض��������
	*/
	void add_edge(const EdgeTupleType& edge_tuple);

	/**
	* @brief �޸�һ���ߵ�Ȩ��
	* @param id1 ���޸ıߵĵ�һ������id
	* @param id2 ���޸ıߵĵ�һ������id
	* @param wt �µ�Ȩ��
	* @return void
	* @details Ҫ��`id1`��`id2`����`[0,N)`�����հ뿪���䡣����κ�һ��ֵ��������������Ϊ����`id`��Ч�����׳�`std::invalid_argument`�쳣��
	*
	* �޸Ķ���`id1`��`id2`ֱ�ӵıߵ�Ȩ��Ϊ`wt`�����ָ�����֮��ı߲����ڣ����׳�`std::invalid_argument`�쳣��
	*/
	void update_weight(VIDType id1, VIDType id2, EWeightType wt);

	/**
	* @brief �ж�ͼ��ָ������֮���Ƿ���ڱ�
	* @param id_from: ��һ�������`id`
    * @param id_to: �ڶ��������`id`
	* @return bool
	* @details ��`id_from`��`id_to`��Чʱ���׳��쳣
	*/
	bool has_edge(VIDType id_from, VIDType id_to) const;

	/**
	 * @brief ���ض���v���ڽӶ���id�ļ���
	 * @param id �����`id`
	 * @return  ����v���ڽӶ���id�ļ���
	 */
	const std::set<VIDType> adj(VIDType id) const;

	/**
	 * @brief ����ͼ�����бߵ���Ԫ��Ԫ�鼯�ϣ����Ｏ�ϲ���`std::vector<std::tuple<VIDType,VIDType,EWeightType>>`
	 * @return ͼ�����бߵ���Ԫ��Ԫ�鼯�� 
	 */
	const std::vector<EdgeTupleType> edge_tuples() const;

	/**
	 * @brief ����ͼ��ָ������֮��ıߵ�Ȩ��
	 * @param id_from ��һ�������`id`
	 * @param id_to �ڶ��������`id`
	 * @return ��һ������͵ڶ�������֮��ıߵ�Ȩ��
	 * @details Ҫ��ߵĶ������`[0,V)`�����հ뿪���䡣����κ�һ��ֵ��������������Ϊ����`id`��Ч
	 * 
	 * ���ҽ���`id_from`��`id_to`֮����ڱ�ʱ���ظñߵ�Ȩ�ء����ָ�����֮��ı߲����ڣ����׳�`std::invalid_argument`�쳣��
	 */
	EWeightType weight(VIDType id_from, VIDType id_to) const;

	/**
	* @brief ��֤�������Ƿ���Ч
	* @param vid ����֤�Ķ�����
	* @return bool
	* @details Ҫ��ߵĶ������`[0,V)`�����հ뿪���䡣����κ�һ��ֵ��������������Ϊ����`id`��Ч
	*/
	bool validate_vid(VIDType vid) const;
	
	/**
	* @brief �Զ�����Ա�׼��������������
	*/
	template<int V>
	friend std::ostream& operator<<(std::ostream& os, ADJListGraph<V> adjListGraph);
private:
	std::array<std::vector<std::pair<VIDType, EWeightType>>, V> _array;	///< ͼ���ڽӱ�
	int _v;
	int _e;
};

template<int V>
std::ostream& operator<<(std::ostream& os, ADJListGraph<V> adjListGraph);
