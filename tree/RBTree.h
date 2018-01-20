#ifndef __RBTREE_H__
#define __RBTREE_H__
#pragma once
/*
红黑树特性
1.每个节点不是红色，就是黑色
2.根节点是黑色的
3.每个叶子节点是黑色的
4.如果一个节点是红色的，那么其子节点必为黑色
5.从一个节点到该节点的子孙节点所有路径上包含相同数目的黑节点
*/

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_set_black(r) do { (r)->color = BLACK;}while(0)
#define rb_set_red(r) do {(r)->color == RED;}while(0)
#define rb_set_parent(r, p) do {(r)->parent = p; }while(0)
#define rb_set_color(r, c) do { (r)->color = c;}while(0)

enum RBColor { RED, BLACK };

template<typename T>
struct RBTreeNode {
	RBColor color;
	T key;

	RBTreeNode *left;
	RBTreeNode *right;
	RBTreeNode *parent;

	RBTreeNode(T value, RBColor clr, RBTreeNode *p,
		RBTreeNode *l, RBTreeNode *r) :
		key(value), color(c), parent(p), left(l), right(r){}

};

template<typename T>
class RBTree {
public:
	RBTree();
	~RBTree();

	void PreOrder();
	void InOrder();
	void PostOrder();

	RBTreeNode<T> *SearchByRecurse(T key);
	RBTreeNode<T> *SearchByIterator(T key);

	T Min();
	T Max();

	RBTreeNode<T>* successor(RBTreeNode<T> *pnode);
	RBTreeNode<T>* predecessor(RBTreeNode<T> *pnode);
	
	void Insert(T key);
	void Remove(T key);
	void Destroy();
	void Print();

protected:
	void PreOrder(RBTreeNode<T> *pnode) const;
	void InOrder(RBTreeNode<T> *pnode) const;
	void PostOrder(RBTreeNode<T> *pnode) const;

	RBTreeNode<T> *Min(RBTreeNode<T>* &pnode, T key);
	RBTreeNode<T> *Max(RBTreeNode<T>* &pnode, T key);

	RBTreeNode<T> *SearchByRecurse(RBTreeNode<T> *pnode, T key) const;
	RBTreeNode<T> *SearchByIterator(RBTreeNode<T> *pnode, T key) const;

	RBTreeNode<T> *LeftRotate(RBTreeNode<T>* &pnode);
	RBTreeNode<T> *RightRotate(RBTreeNode<T>* &pnode);
	RBTreeNode<T> *Insert(RBTreeNode<T>* &pnode, T key);
	RBTreeNode<T> *Remove(RBTreeNode<T>* &pnode, T key);

	void Destroy(RBTreeNode<T>* &pnode);
	void Dump(RBTreeNode<T>* &pnode);
};

#endif