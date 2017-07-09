#pragma once
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "../stdafx.h"
#include <stddef.h>
#include "Comparable.h"
/**
����ƽ��������ʧ������
1.������   ���������������ӽڵ� ����ƽ�����Ӿ���ֵ��1������2
2.������   �������������Һ��ӽڵ� ����ƽ�����Ӿ���ֵ��1������2
3.������������    �������������Һ��ӽڵ� ����ƽ�����Ӿ���ֵ��1������2
4.������������    ���������������ӽڵ� ����ƽ�����Ӿ���ֵ��1������2

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
	//����
	static Comparable<KeyType>*
		Search(KeyType key, AvlNode<KeyType>*root, CMP_T cmp = EQ_CMP);

	//����
	static Comparable<KeyType>*
		Insert(AvlNode<KeyType>* item, AvlNode<KeyType> * &root);
	//ɾ��
	static Comparable<KeyType>*
		Delete(KeyType key, AvlNode<KeyType>* &root, CMP_T cmp = EQ_CMP);

	static Comparable<KeyType>*
		Min(AvlNode<KeyType>* &root);

	static Comparable<KeyType>*
		Max(AvlNode<KeyType>* &root);
	//���߶�
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
	
	//һ����ת
	static int
		RotateOnce(AvlNode<KeyType> *&root, DIR_T dir);

	//������ת
	static int
		RotateTwice(AvlNode<KeyType> *&root, DIR_T dir);

	CMP_T
		Compare(KeyType key, CMP_T cmp = EQ_CMP)const;
	
	CMP_T
		Compare(const KeyType &key, CMP_T cmp = EQ_CMP)const;

	//���µ���ƽ��
	int
		Rebalance(AvlNode<KeyType> *&root);
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
	//AVL���Ľ������ ��Ч�ڵ����
	bool Check()const{
		return (root_) ? root_->Check() : false;
	}

	//��С�ڵ�
	Comparable<KeyType>*
		Min(){
			return AvlNode<KeyType>::Min(root_);
		}
	//���ڵ�
	Comparable<KeyType>*
		Max(){
			return AvlNode<KeyType>::Max(root_);
		}
private:
	AvlTree(const AvlTree<KeyType>&);
	AvlTree & operator=(const AvlTree<KeyType>&);

	AvlNode<KeyType> *root_;
};

#endif