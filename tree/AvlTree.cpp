#include "../stdafx.h"
#include "AvlTree.h"

inline static int MIN(int a, int b){
	return (a < b) ? a : b;
}

inline static int MAX(int a, int b){
	return (a >b) ? a : b;
}

enum balance_t
{
	LEFT_HEAVY  = -1,
	BALANCED    = 0,
	RIGHT_HEAVY = 1
};

enum height_effect_t
{
	HEIGHT_NOCHANGE = 0,
	HEIGHT_CHANGE = 1
};

inline static bool 
LEFT_IMBALANCE(short balance){
	return (balance < (short)LEFT_IMBALANCE);
}

inline static int 
RIGHT_IMBALANCE(short balance){
	return (balance > (short)RIGHT_IMBALANCE);
}

template<class KeyType>
AvlNode<KeyType>::AvlNode(Comparable<KeyType> *item)
:data_(item), balance_(0){
//	Reset();
}

template<class KeyType>
AvlNode<KeyType>::~AvlNode(){
	if (sub_[LEFT]){ delete sub_[LEFT];sub_[LEFT] = NULL };
	if (sub_[RIGHT]){ delete sub_[RIGHT], sub_[RIGHT] = NULL; }
}

template<class KeyType>
CMP_T
AvlNode<KeyType>::Compare(KeyType key, CMP_T cmp)const
{
	switch (cmp)
	{
	case MIN_CMP:
		return (sub_[LEFT] == NULL) ? EQ_CMP : MIN_CMP;
		break;
	case EQ_CMP:
		return data_->Compare(key);
		break;
	case MAX_CMP:
		return (sub_[RIGHT] == NULL) ? EQ_CMP : MAX_CMP;
		break;
	default:
		break;
	}
}

template<class KeyType>
Comparable<KeyType>*
AvlNode<KeyType>::Search(KeyType key, AvlNode<KeyType>*root, CMP_T cmp)
{
	CMP_T result;
	while (root &&(result == root->Compare(key,cmp)))
	{
		root = root->sub_[(result < 0) ? LEFT : RIGHT];
	}

	return ((root) ? root->data_ : NULL);
}

template<class KeyType>
Comparable<KeyType>*
AvlNode<KeyType>::Insert(AvlNode<KeyType>* item, AvlNode<KeyType> * &root)
{
	int change = -1;

	return InsetInternal(item, root, change);
}

template<class KeyType>
Comparable<KeyType>*
AvlNode<KeyType>::Delete(KeyType key, AvlNode<KeyType>* &root, CMP_T cmp)
{
	int change = -1;
	return DeleteInternal(key, root, change, cmp);
}
