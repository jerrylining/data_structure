#pragma once
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "../stdafx.h"
#include <stddef.h>
#include "Comparable.h"

enum DIR_T{
	LEFT = 0,
	RIGHT
};

template<class KeyType>
class AvlNode{
public:

	enum { MAX_SUBTREES = 2 };
	static DIR_T Opposite(DIR_T dir){
		return DIR_T(1 - (int)dir);
	}

	AvlNode(Comparable<KeyType> *item = NULL);

	virtual ~AvlNode();

	Comparable<KeyType>*
		Data()const { return data_; }

	KeyType
		Key()const{ return data_->Key(); }

	short
		Balance()const{ return balance_; }

	AvlNode*
		SubTree(DIR_T dir)const{ return sub_[dir]; }
public:
	//查找
	static Comparable<KeyType>*
		Search(KeyType key, AvlNode<KeyType>*root, CMP_T cmp = EQ_CMP);

	//插入
	static Comparable<KeyType>*
		Insert(AvlNode<KeyType>* item, AvlNode<KeyType> * &root);
	//删除
	static Comparable<KeyType>*
		Delete(KeyType key, AvlNode<KeyType>* &root, CMP_T cmp = EQ_CMP);

	//树高度
	int
		Height()const;

	int 
		Check()const;

private:
	void Reset(){
		balance_ = 0;
		sub_[LEFT] = sub_[RIGHT] = NULL;
	}

	static Comparable<KeyType>*
		InsetInternal(AvlNode<KeyType>* item, AvlNode<KeyType> *&root, int &change);

	static Comparable<KeyType>*
		DeleteInternal(KeyType key, AvlNode<KeyType>* &root, int &change, CMP_T cmp = EQ_CMP);
	
	//一次旋转
	static int
		RotateOnce(AvlNode<KeyType> *&root, DIR_T dir);

	//两次旋转
	static int
		RotateTwice(AvlNode<KeyType> *&root, DIR_T dir);

	CMP_T
		Compare(KeyType key, CMP_T cmp = EQ_CMP)const;
	
	CMP_T
		Compare(const KeyType &key, CMP_T cmp = EQ_CMP)const;

private:
	AvlNode(const AvlNode<KeyType>&);
	AvlNode & operator=(const AvlNode<KeyType>&);
private:
	Comparable<KeyType>* data_;

	short balance_;

	AvlNode<KeyType> *sub_[MAX_SUBTREES];
};

template<class KeyType>
class AvlTree
{
public:
	AvlTree() :root_(NULL){}

	~AvlTree(){ if (root_){ delete root_; root_ = NULL; } };

	void
		DumpTree(std::ostream & os)const;
	
	bool 
		IsEmpty()const{
			return (root_ == NULL);
		}

	Comparable<KeyType>*
		Search(KeyType key, CMP_T cmp = EQ_CMP){
			return AvlNode<KeyType>::Search(key, root_, cmp);
		}

	Comparable<KeyType>*
		Insert(Comparable<KeyType> *item){
			return AvlNode<KeyType>::Insert(item, root_);
		}

	Comparable<KeyType>*
		Delete(KeyType key, CMP_T cmp = EQ_CMP){
			return AvlNode<KeyType>::Delete(key, root_, cmp);
		}
	//AVL树的健康检查 无效节点检验
	bool Check()const{
		return (root_) ? root_->Check() : false;
	}
private:
	AvlTree(const AvlTree<KeyType>&);
	AvlTree & operator=(const AvlTree<KeyType>&);

	AvlNode<KeyType> *root_;
};

#endif