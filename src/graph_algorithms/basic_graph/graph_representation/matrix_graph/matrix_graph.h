#pragma once

#include <array>

template<int V> 
class MatrixGraph {
public:
	typedef int VIDType;		///< �����ŵ�����
	typedef float EWeightType;	///< Ȩ�ص�����
	typedef std::tuple<VIDType, VIDType, EWeightType> EdgeTupleType;	///< �ߵ���Ԫ�أ�����1��ţ�����2��ţ�Ȩ�أ���ɵ�Ԫ��

	/**
	 * @brief Ĭ�Ϲ��캯����ָ��`INVALID_WEIGHT`Ϊ0
	 */
	MatrixGraph() : MatrixGraph(0) {};

	/**
	 * @brief ���캯����ָ��`INVALID_WEIGHT`
	 * @param val ��ЧȨ��ֵ
	 */
	MatrixGraph(EWeightType val);

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

private:
	std::array<std::array<EWeightType, N>, N> _matrix;	// ͼ�ľ���
	const EWeightType INVALID_WEIGHT;	// ��ЧȨ�أ���һ��constֵ��һ��ͼ����ʼ��֮����޷��ı�
	int _v;
	int _e;
};
