#pragma once
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "../stdafx.h"
#include <stddef.h>
#include <iostream>
/**
二叉平衡树四种失衡类型
1.单左旋   在左子树插入左孩子节点 导致平衡因子绝对值由1增加至2
2.单右旋   在右子树插入右孩子节点 导致平衡因子绝对值由1增加至2
3.先左旋后右旋    在左子树插入右孩子节点 导致平衡因子绝对值由1增加至2
4.先右旋后左旋    在右子树插入左孩子节点 导致平衡因子绝对值由1增加至2

LL
1. R            R                    C
    \            \                 /  \
	 C    ==>     C        ==>    R     I
	               \
				    I


RR
2.   R             R                 C
    /    ==>      /       ==>       / \
   C             C                 I   R
                /
			   I

RL
3.
       R               R                  R                        R  
	  / \             / \    L Spin      / \      R Spin          / \
	 LC  RC  ==>     LC  RC   ==>      LC   RC     ==>          I   RC
	/               /                  /                        /\
   G               G                  I                        G  LC
                    \                /
					 I              G

LR
4.     R                  R                     R                      R
      / \                / \     R Spin        / \       L Spin       / \
	 LC  RC   ==>       LC  RC    ==>         LC  RC      ==>        LC  I
	      \                  \                     \                    / \
		   G                  G                     I                  RC  G
		                     /                       \
							I                         G
*/

#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))

template<typename T>
struct AVLTreeNode {
	AVLTreeNode(T value, AVLTreeNode<T> *l, AVLTreeNode<T> *r)
		:key(value), left(l), right(r),height(0) {}

	T key;
	int height;
	AVLTreeNode<T> *left;
	AVLTreeNode<T> *right;
};

template<typename T>
class AVLTree {
public:
	AVLTree(){};
	~AVLTree(){};

	void PreOrder();
	void InOrder();
	void PostOrder();

	void Dump();
	void Destory();

	void Insert(T key);
	void Remove(T key);

	AVLTreeNode<T> *SearchByRecurse(T key);
	AVLTreeNode<T> *SearchByIterator(T key);

	T Min();
	T Max();

	int Height(AVLTreeNode<T> *pnode);
	int Height();

private:
	AVLTreeNode<T> *root_;

protected:
	void PreOrder(AVLTreeNode<T> *pnode) const ;
	void InOrder(AVLTreeNode<T> *pnode) const;
	void PostOrder(AVLTreeNode<T> *pnode) const;

	void Dump(AVLTreeNode<T>* pnode, T key, int direction) const;
	void Destory(AVLTreeNode<T>* &pnode);

	AVLTreeNode<T>* Insert(AVLTreeNode<T>* &pnode, T key);
	AVLTreeNode<T>* Remove(AVLTreeNode<T>* &pnode, T key);

	AVLTreeNode<T>* Min(AVLTreeNode<T> *pnode) const;
	AVLTreeNode<T>* Max(AVLTreeNode<T> *pnode) const;

	AVLTreeNode<T>* SearchByRecurse(AVLTreeNode<T> *pnode, T key) const;
	AVLTreeNode<T>* SearchByIterator(AVLTreeNode<T> *pnode, T key) const;

	AVLTreeNode<T>* LeftRotate(AVLTreeNode<T> *pnode);
	AVLTreeNode<T>* RightRotate(AVLTreeNode<T> *pnode);
	AVLTreeNode<T>* LeftRightRotate(AVLTreeNode<T> *pnode);
	AVLTreeNode<T>* RightLeftRotate(AVLTreeNode<T> *pnode);
};

template<typename T>
int AVLTree<T>::Height(AVLTreeNode<T> *pnode)
{
	if (pnode != nullptr) {
		return pnode->height;
	}

	return 0;
}
template<typename T>
int AVLTree<T>::Height()
{
	return Height(root_);
}

template<typename T>
AVLTreeNode<T>* 
AVLTree<T>::LeftRotate(AVLTreeNode<T> *pnode)
{
	AVLTreeNode<T> *right = pnode->right;
	pnode->right = right->left;
	right->left = pnode;

	pnode->height = MAX(Height(pnode->left), Height(pnode->right)) + 1;
	right->height = MAX(Height(right->left), Height(right->right)) + 1;
	return right;
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::RightRotate(AVLTreeNode<T> *pnode)
{
	AVLTreeNode<T> *left = pnode->left;
	pnode->left = left->right;
	left->right = pnode;

	pnode->height = MAX(Height(pnode->left), Height(pnode->right)) + 1;
	left->height =  MAX(Height(left->left), Height(left->right)) + 1;
	return left;
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::LeftRightRotate(AVLTreeNode<T> *pnode)
{
	pnode->left = LeftRotate(pnode->left);

	return RightRotate(pnode);
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::RightLeftRotate(AVLTreeNode<T> *pnode)
{
	pnode->right = RightRotate(pnode->right);

	return LeftRotate(pnode);
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::Insert(AVLTreeNode<T>* &pnode, T key)
{
	if (pnode == nullptr) {
		pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
	}
	else if (key > pnode->key) {
		pnode->right = Insert(pnode->right, key);
		if ((Height(pnode->right) - Height(pnode->left)) == 2)
		{
			if (key > pnode->right->key)
				pnode = LeftRotate(pnode);
			else if (key < pnode->right->key)
				pnode = RightLeftRotate(pnode);
		}
	}
	else if (key < pnode->key) {
		pnode->left = Insert(pnode->left, key);
		if ((Height(pnode->left) - Height(pnode->right)) == 2)
		{
			if (key < pnode->left->key)
				pnode = RightRotate(pnode);
			else if (key > pnode->left->key)
				pnode = LeftRightRotate(pnode);
		}
	}

	pnode->height = MAX(Height(pnode->left), Height(pnode->right)) + 1;
	return pnode;
}

template<typename T>
void AVLTree<T>::Insert(T key)
{
	root_ = Insert(root_, key);
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::Remove(AVLTreeNode<T>* &pnode, T key)
{
	if (pnode != nullptr) {

		if (key == pnode->key) {
			if (pnode->left != nullptr && pnode->right != nullptr)
			{
				if (Height(pnode->left) > Height(pnode->right))
				{
					AVLTreeNode<T>* ppre = Max(pnode->left);
					pnode->key = ppre->key;
					pnode->left = Remove(pnode->left, ppre->key);
				}
				else {
					AVLTreeNode<T>* psuc = Min(pnode->right);
					pnode->key = psuc->key;
					pnode->right = Remove(pnode->right, psuc->key);
				}
			}
			else {
				AVLTreeNode<T> *ptemp = pnode;
				if (pnode->left != nullptr)
					pnode = pnode->left;
				if (pnode->right != nullptr)
					pnode = pnode->right;
				delete ptemp;
				return nullptr;
			}
		}
		else if (key > pnode->key){
			pnode->right = Remove(pnode->right, key);
			if (Height(pnode->left) - Height(pnode->right) == 2){
				if (Height(pnode->left->right) > Height(pnode->left->left))
					pnode = LeftRightRotate(pnode);
				else
					pnode = RightRotate(pnode);
			}
		}
		else if (key < pnode->key) {
			pnode->left = Remove(pnode->left, key);
			if (Height(pnode->right) - Height(pnode->left) == 2) {
				if (Height(pnode->right->left) > Height(pnode->right->right))
					pnode = RightLeftRotate(pnode);
				else
					pnode = LeftRotate(pnode);
			}
		}

		return pnode;
	}
	return nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::SearchByRecurse(T key)
{
	return SearchByRecurse(root_, key);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::SearchByRecurse(AVLTreeNode<T> *pnode, T key) const
{
	if (pnode != nullptr) {
		if (pnode->key == key) 
			return pnode;
		if (key > pnode->key)
			return SearchByRecurse(pnode->right, key);
		else
			return SearchByRecurse(pnode->left, key);
	}

	return nullptr;
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::SearchByIterator(T key)
{
	AVLTreeNode<T>* pnode = root_;
	return SearchByIterator(pnode, key);
}

template<typename T>
AVLTreeNode<T>* 
AVLTree<T>::SearchByIterator(AVLTreeNode<T> *pnode, T key) const
{
	while (pnode)
	{
		if (pnode->key == key)
			return pnode;
		else if (key > pnode->key)
			pnode = pnode->right;
		else
			pnode = pnode->left;
	}

	return nullptr;
}

template<typename T>
void AVLTree<T>::PreOrder(AVLTreeNode<T> *pnode)const
{
	if (pnode != NULL)
	{
		std::cout << pnode->key <<" ";
		InOrder(pnode->left);
		InOrder(pnode->right);
	}
}

template<typename T>
void AVLTree<T>::PreOrder()
{
	return PreOrder(root_);
}

template<typename T>
void AVLTree<T>::InOrder(AVLTreeNode<T> *pnode)const
{
	if (pnode != NULL)
	{
		InOrder(pnode->left);
		std::cout << pnode->key << " ";
		InOrder(pnode->right);
	}
}

template<typename T>
void AVLTree<T>::InOrder()
{
	return InOrder(root_);
}

template<typename T>
void AVLTree<T>::PostOrder(AVLTreeNode<T> *pnode)const
{
	if (pnode != NULL)
	{
		InOrder(pnode->left);
		InOrder(pnode->right);
		std::cout << pnode->key << " ";
	}
}

template<typename T>
void AVLTree<T>::PostOrder()
{
	return PostOrder(root_);
}

template<typename T>
void AVLTree<T>::Destory(AVLTreeNode<T>* &pnode)
{
	if (pnode != nullptr)
	{
		Destory(pnode->left);
		Destory(pnode->right);
		delete pnode;
		pnode = nullptr;
	}
}

template<typename T>
void AVLTree<T>::Destory()
{
	Destory(root_);
}

template<typename T>
AVLTreeNode<T>* 
AVLTree<T>::Min(AVLTreeNode<T> *pnode) const
{
	if (pnode != nullptr)
	{
		while (pnode->left != nullptr)
			pnode = pnode->left;

		return pnode;
	}
	return nullptr;
}

template<typename T>
T AVLTree<T>::Min()
{
	AVLTreeNode<T> *pnode = root_;

	AVLTreeNode<T> *result = Min(pnode);
	return result->key;
}

template<typename T>
AVLTreeNode<T>*
AVLTree<T>::Max(AVLTreeNode<T> *pnode)const
{
	if (pnode != nullptr)
	{
		while (pnode->right != nullptr)
			pnode = pnode->right;

		return pnode;
	}

	return nullptr;
}

template<typename T>
T AVLTree<T>::Max()
{
	AVLTreeNode<T> *pnode = root_;
	AVLTreeNode<T> *result = Max(pnode);
	return result->key;
}

#endif