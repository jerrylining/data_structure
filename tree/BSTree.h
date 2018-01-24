#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <iostream>

template<typename T>
struct BSTreeNode {
	BSTreeNode(T value, BSTreeNode<T>* l, BSTreeNode<T> *r)
		:key(value), left(l), right(r){}
	BSTreeNode(T value)
		:key(value), left(nullptr), right(nullptr){}

	T key;
	BSTreeNode<T> *left;
	BSTreeNode<T> *right;
	BSTreeNode<T> *parent;
};

template<typename T>
class BSTree {
public:
	BSTree(){}
	~BSTree(){}

	void PreOrder();
	void InOrder();
	void PostOrder();

	void Dump();
	void Destroy();

	void Insert(T key);
	void Remove(T key);

	void Insert(BSTreeNode<T>* pnode);
	

	BSTreeNode<T> *SearchByRecurse(T key);
	BSTreeNode<T> *SearchByIterator(T key);

	T Min();
	T Max();

protected:
	void PreOrder(BSTreeNode<T> *pnode) const;
	void InOrder(BSTreeNode<T> *pnode) const;
	void PostOrder(BSTreeNode<T> *pnode) const;

	void Dump(BSTreeNode<T> *pnode, T key, int direction) const;
	void Destroy(BSTreeNode<T> * &pnode);

	BSTreeNode<T>* Predecessor(BSTreeNode<T> *pnode);
	BSTreeNode<T>* Successor(BSTreeNode<T> *pnode);

	BSTreeNode<T>* Remove(BSTreeNode<T>* &pnode, T key);

	BSTreeNode<T>* Min(BSTreeNode<T> *pnode) const;
	BSTreeNode<T>* Max(BSTreeNode<T> *pnode) const;

	BSTreeNode<T>* SearchByRecurse(BSTreeNode<T>* pnode, T key);
	BSTreeNode<T>* SearchByIterator(BSTreeNode<T>* pnode,T key);

private:
	BSTreeNode<T>* root_;
};

template<typename T>
void BSTree<T>::Insert(T key)
{
	BSTreeNode<T>* pnode = root_;
	BSTreeNode<T>* parent = nullptr;

	while (pnode != nullptr)
	{
		parent = pnode;
		if (key > pnode->key)
			pnode = pnode->right;
		else if (key < pnode->key)
			pnode = pnode->left;
		else break;
	}

	pnode = new BSTreeNode<T>(key);
	if (parent == nullptr) {
		root_ = pnode;
	}
	else {
		if (key > parent->key)
		{
			parent->right = pnode;
		}
		else
			parent->left = pnode;
	}

	pnode->parent = parent;
}

template<typename T>
void BSTree<T>::Insert(BSTreeNode<T>* pnode)
{
	if (pnode == nullptr) return;

	BSTreeNode<T>* node = root_;
	BSTreeNode<T>* parent = nullptr;

	T key = pnode->key;

	while (node != nullptr)
	{
		parent = node;
		if (key > node->key)
			node = node->right;
		else if (key < node->key)
			node = node->left;
		else break;
	}

	if (parent == nullptr) {
		root_ = pnode;
	}
	else {
		if (key > parent->key)
		{
			parent->right = pnode;
		}
		else
			parent->left = pnode;
	}

	pnode->parent = parent;
}

template<typename T>
void 
BSTree<T>::PreOrder()
{
	PreOrder(root_);
}

template<typename T>
void 
BSTree<T>::PreOrder(BSTreeNode<T> *pnode) const
{
	if (pnode != nullptr) {
		std::cout << pnode->key << " ";
		PreOrder(pnode->left);
		PreOrder(pnode->right);
	}
}

template<typename T>
void 
BSTree<T>::InOrder()
{
	BSTreeNode<T> *pnode = root_;
	InOrder(pnode);
}

template<typename T>
void 
BSTree<T>::InOrder(BSTreeNode<T> *pnode)const
{
	if (pnode != nullptr){
		InOrder(pnode->left);
		std::cout << pnode->key << " ";
		InOrder(pnode->right);
	}
}

template<typename T>
void 
BSTree<T>::PostOrder()
{
	BSTreeNode<T> *pnode = root_;
	PostOrder(pnode);
}

template<typename T>
void 
BSTree<T>::PostOrder(BSTreeNode<T> *pnode)const
{
	if (pnode != nullptr) {
		PostOrder(pnode->left);
		PostOrder(pnode->right);
		std::cout << pnode->key << " ";
	}
}

template<typename T>
BSTreeNode<T>* 
BSTree<T>::Predecessor(BSTreeNode<T> *pnode)
{
	BSTreeNode<T> *node = pnode->left;

	if (node != nullptr) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	node = pnode;
	BSTreeNode<T>* parent = node->parent;
	while (parent != nullptr && parent->left == node) {
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

template<typename T>
BSTreeNode<T>*
BSTree<T>::Successor(BSTreeNode<T> *pnode)
{
	BSTreeNode<T> *node = pnode->right;

	if (node != nullptr) {
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	node = pnode;
	BSTreeNode<T>* parent = node->parent;
	while (parent != nullptr && parent->right == node)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

template<typename T>
void BSTree<T>::Remove(T key)
{
	Remove(root_, key);
}

template<typename T>
BSTreeNode<T>*
BSTree<T>::Remove(BSTreeNode<T> * &pnode, T key)
{
	if (pnode != nullptr) {
		if (pnode->key == key) {
			BSTreeNode<T>* pdel = nullptr;

			if (pnode->left == nullptr && pnode->right == nullptr)
				pdel = pnode;
			else
				pdel = Predecessor(pnode);

			BSTreeNode<T>* pchild = nullptr;
			if (pdel->left != nullptr)
				pchild = pdel->left;
			else
				pchild = pdel->right;

			if (pchild != nullptr) {
				pchild->parent = pdel->parent;
			}

			if (pdel->parent == nullptr) {
				root_ = pchild;
			}

			else if (pdel->parent->left == pdel) {
				pdel->parent->left = pchild;
			}
			else
				pdel->parent->right = pchild;

			if (pnode->key != pdel->key) {
				pnode->key = pdel->key;
			}
			delete pdel;
		}
		else if (key > pnode->key) {
			Remove(pnode->right, key);
		}
		else
			Remove(pnode->left, key);
	}

	return pnode;
}

template<typename T>
BSTreeNode<T>* BSTree<T>::SearchByRecurse(T key)
{
	return SearchByRecurse(root_, key);
}

template<typename T>
BSTreeNode<T>* BSTree<T>::SearchByRecurse(BSTreeNode<T> *pnode, T key)
{
	if (pnode != nullptr) {
		if (pnode->key == key)
			return pnode;
		if (key > pnode->key)
			return SearchByRecurse(pnode->left, key);
		else
			return SearchByRecurse(pnode->right, key);
	}

	return nullptr;
}

template<typename T>
BSTreeNode<T>* BSTree<T>::SearchByIterator(T key)
{
	return SearchByIterator(root_, key);
}

template<typename T>
BSTreeNode<T>* BSTree<T>::SearchByIterator(BSTreeNode<T> *pnode, T key)
{
	BSTreeNode<T> *node = pnode;

	while (node != nullptr) {
		if (node->key == key)
			return node;
		else if (node->key < key)
			node = node->right;
		else
			node = node->left;
	}

	return nullptr;
}

template<typename T>
T BSTree<T>::Min()
{
	BSTreeNode<T> *pnode = Min(root_);
	if (pnode != nullptr) {
		return pnode->key;
	}
	return root_->key;
}

template<typename T>
BSTreeNode<T>*
BSTree<T>::Min(BSTreeNode<T>* pnode)const
{
	BSTreeNode<T> *node = pnode;

	while (node->left != nullptr) {
		node = node->left;
	}

	return node;
}

template<typename T>
T BSTree<T>::Max()
{
	BSTreeNode<T> *pnode = Max(root_);

	if (pnode != nullptr)
		return pnode->key;

	return root_->key;
}

template<typename T>
BSTreeNode<T>*
BSTree<T>::Max(BSTreeNode<T> *pnode)const
{
	BSTreeNode<T> *node = pnode;

	while (node->right != nullptr)
	{
		node = node->right;
	}

	return node;
}

template<typename T>
void BSTree<T>::Destroy()
{
	Destroy(root_);
}
template<typename T>
void BSTree<T>::Destroy(BSTreeNode<T>* &pnode)
{
	if (pnode != nullptr) {
		if (pnode->left != nullptr)
			Destroy(pnode->left);
		if (pnode->right != nullptr)
			Destroy(pnode->right);

		delete pnode;
		pnode = nullptr;
	}
}

#endif