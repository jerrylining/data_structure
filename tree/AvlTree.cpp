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
	LEFT_HEAVY = -1,
	BALANCED = 0,
	RIGHT_HEAVY = 1
};

enum height_effect_t
{
	HEIGHT_NOCHANGE = 0,
	HEIGHT_CHANGE = 1
};

enum TraversalOrder
{
	LTREE,
	KEY,
	RTREE
};

inline static bool
LEFT_IMBALANCE(short balance){
	return (balance < LEFT_HEAVY);
}

inline static int
RIGHT_IMBALANCE(short balance){
	return (balance > RIGHT_HEAVY);
}

static inline std::ostream &
Indent(std::ostream & os, int len){
	for (int i = 0; i < len; i++){
		os << ' ';
	}
	return os;
}
template<class KeyType>
AvlNode<KeyType>::AvlNode(Comparable<KeyType> *item)
:data_(item), balance_(0){
	//	Reset();
}

template<class KeyType>
AvlNode<KeyType>::~AvlNode(){
	if (sub_[LEFT]){ delete sub_[LEFT]; sub_[LEFT] = NULL };
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
	while (root && (result == root->Compare(key, cmp)))
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

template<class KeyType>
Comparable<KeyType>*
AvlNode<KeyType>::InsetInternal(AvlNode<KeyType>* item, AvlNode<KeyType> *&root, int &change)
{
	if (root == NULL){
		root = new AvlNode<KeyType>(item);
		change = HEIGHT_CHANGE;
		return NULL;
	}

	Comparable<KeyType> *found = NULL;
	int increase = 0;

	CMP_T result = root->Compare(item->Key());
	DIR_T dir = (result == MIN_CMP) ? LEFT : RIGHT;
	if (result != EQ_CMP){
		found = InsetInternal(item, root[dir], change);
		if (found)return found;
		increase = result *change;
	}
	else{
		increase = HEIGHT_NOCHANGE;
		return root->Data();
	}

	root->balance_ += increase;

	change = (increase && root->balance_) ? (1 - Rebalance(root)) : HEIGHT_NOCHANGE;

	return NULL;
}

template<class KeyType>
Comparable<KeyType>*
AvlNode<KeyType>::DeleteInternal(KeyType key, AvlNode<KeyType>* &root, int &change, CMP_T cmp)
{
	if (root == NULL){
		change = HEIGHT_NOCHANGE;
		return NULL;
	}

	Comparable<KeyType>* found = NULL;
	int decrease = 0;

	CMP_T result = root->Compare(key, cmp);
	DIR_T dir = (result == MIN_CMP) ? LEFT : RIGHT;

	if (result != EQ_CMP){
		found = DeleteInternal(key, root->sub_[dir], change, cmp);
		if (!found)return found;
		decrease = result* change;
	}
	else{
		found = root->Data();
	}

	/*分三种情况进行删除
	1.节点为叶子节点 直接删除返回
	2.节点为父节点 有一个子节点 需要对子节点指向调整
	3.节点为父节点 有两个子节点 需要对两个子节点指向调整
	*/

	if (root->sub_[LEFT] == NULL && root->sub_[RIGHT] == NULL){
		delete root;
		root = NULL;
		change = HEIGHT_CHANGE;
		return found;
	}
	else if (root->sub_[LEFT] == NULL || root->sub_[RIGHT] == NULL){
		AvlNode<KeyType> *delNode = root;

		root = root->sub_[(root->sub_[RIGHT]) ? RIGHT : LEFT];
		change = HEIGHT_CHANGE;
		delNode->sub_[LEFT] = delNode->sub_[RIGHT] = NULL;
		return found;
	}
	else{
		root->Data() = DeleteInternal(key, root->sub_[RIGHT], decrease, MIN_CMP);
	}

	root->balance_ -= decrease;

	change = (decrease) ? (root->Balance() ? Rebalance(root) : HEIGHT_CHANGE) : HEIGHT_NOCHANGE;
	return found;
}

template<class KeyType>
int
AvlNode<KeyType>::Height()const
{

	int leftHeight  = sub_[LEFT] ? sub_[LEFT]->Height() : 0;
	int rightHeight = sub_[RIGHT] ? sub_[RIGHT]->Height() : 0;

	return (1 + MAX(leftHeight, rightHeight));
}

template<class KeyType>
int
AvlNode<KeyType>::RotateOnce(AvlNode<KeyType> *&root, DIR_T dir)
{
	DIR_T other = Opposite(dir);

	AvlNode<KeyType>* oldRoot = root;

	int heightChange = (root->sub_[other]->Balance() == 0)
		               ? HEIGHT_NOCHANGE
		               : HEIGHT_CHANGE;

	root = oldRoot->sub_[other];

	oldRoot->sub_[other] = root->sub_[dir];
	root->sub_[dir] = oldRoot;

	oldRoot->Balance() = -((dir == LEFT) ? --root->Balance() : ++root->Balance());

	return heightChange;
}

template<class KeyType>
int 
AvlNode<KeyType>::RotateTwice(AvlNode<KeyType> *&root, DIR_T dir)
{
	DIR_T other = Opposite(dir);

	AvlNode<KeyType>* oldRoot = root;

	AvlNode<KeyType>* oldOtherDirSubTree = root->sub_[other];

	//第一次旋转
	root = oldRoot->sub_[other]->sub_[dir];
	oldRoot->sub_[other] = root->sub_[dir];
	root->sub_[dir] = oldRoot;

	//第二次旋转
	oldOtherDirSubTree->sub_[dir] = root->sub_[other];
	root->sub_[other] = oldOtherDirSubTree;

	root->sub_[LEFT]->Balance()  = -MAX(root->Balance(), 0);
	root->sub_[RIGHT]->Balance() = -MIN(root->Balance(), 0);

	return HEIGHT_CHANGE;
}

template<class KeyType>
int 
AvlNode<KeyType>::Rebalance(AvlNode<KeyType> *&root)
{
	int heightChange = HEIGHT_NOCHANGE;

	if (LEFT_IMBALANCE(root->Balance())){
		//左子树右子节点重RL 需要进行两次旋转
		if (root->sub_[LEFT]->Balance() == RIGHT_HEAVY){
			heightChange = RotateTwice(root, RIGHT);
		}
		else{
			//RR 旋转一次即可
			heightChange = RotateOnce(root, RIGHT);
		}
	}
	else{
		//右子树左节点中LR 需进行两次旋转LR
		if (root->sub_[RIGHT]->Balance() == LEFT_HEAVY){
			heightChange = RotateTwice(root, LEFT);
		}
		else{
			//LL 旋转一次即可
			heightChange = RotateOnce(root, LEFT);
		}
	}

	return heightChange;
}

template<class KeyType>
int 
AvlNode<KeyType>::Check()const
{
	int valid = 1;

	if (sub_[LEFT]) valid *= sub_[LEFT]->Check();
	if (sub_[RIGHT])valid *= sub_[RIGHT]->Check();

	int leftHeight  = (sub_[LEFT]) ? sub_[LEFT]->Height() : 0;
	int rightHeight = (sub_[RIGHT]) ? sub_[RIGHT]->Height() : 0;

	int diff = rightHeight - leftHeight;

	if (LEFT_IMBALANCE(diff) || RIGHT_IMBALANCE(diff)){
		valid = 0;
		std::cerr << "Height Difference is " << diff
			      << "at node" << Key() << std::endl;
	}

	if (diff != balance_){
		valid = 0;
		std::cerr << "Height difference " << diff
			<< " doesnt match balance-factor of " << balance_
			<< " at node " << Key() << std::endl;
	}

	if ((sub_[LEFT]) && sub_[LEFT]->Compare(Key()) == MIN_CMP){
		std::cerr << "Node " << Key() << " is *smaller* than left subtree"
			<<sub_[LEFT]->Key() << std::endl;
	}

	if ((sub_[RIGHT]) && sub_[RIGHT]->Compare(Key()) == MAX_CMP){
		std::cerr << "Node " << Key() << " is *bigger* than right subtree"
			<< sub_[RIGHT]->Key() << std::endl;
	}
}

template<class KeyType>
static void
Dump(std::ostream & os, TraversalOrder order, AvlNode<KeyType>* node,int level)
{
	unsigned  len = (level * 5) + 1;
	if ((order == LTREE) && (node->Subtree(LEFT) == NULL)) {
		Indent(os, len) << "     **NULL**" << endl;
	}
	if (order == KEY) {
		Indent(os, len) << node->Key() << ":" << node->Bal() << endl;
	}
	if ((order == RTREE) && (node->Subtree(RIGHT) == NULL)) {
		Indent(os, len) << "     **NULL**" << endl;
	}
}

template<class KeyType>
static void
Dump(std::ostream& os, const AvlNode<KeyType> *node, int level = 0)
{
	if (node == NULL){
		os << "***EMPTY TREE***" << endl;
	}
	else{
		Dump(os, RTREE, node, level);

		if (node->sub_[RTREE] != NULL)Dump(os, node->sub_[RTREE], level + 1);

		Dump(os, KEY, node, level);

		if (node->sub_[LTREE] != NULL)Dump(os, node->sub_[LTREE], level + 1);

		Dump(os, LTREE, node, level);
	}
}

template<class KeyType>
void AvlTree<KeyType>::DumpTree(std::ostream & os)const
{
	Dump(os, root_);
}