// data_structure.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <ctime>
#include "tree\AvlTree.h"
#include "tree\RBTree.h"
#include "tree\BSTree.h"


struct list {
	list *next;
	int val;
};

static int value = 8000000;
void AvlTreeTest(){
	AVLTree<int> avl;

	for (int i = 0; i < value; i++)
		avl.Insert(i);

	/*std::cout << "Height:" << avl.Height() << std::endl;

	std::cout << "InOrder" << std::endl;
	avl.InOrder();
	std::cout << std::endl;

	std::cout << "PreOrder" << std::endl;
	avl.PreOrder();
	std::cout << std::endl;

	std::cout << "PostOrder" << std::endl;
	avl.PostOrder();
	std::cout << std::endl;

	std::cout << "Max:" << avl.Max() << std::endl;
	std::cout << "Min:" << avl.Min() << std::endl;
*/
	std::cout << "AVLTree:" << std::endl;
	std::cout << GetTickCount() << std::endl;
	AVLTreeNode<int> *node = avl.SearchByIterator(value - 1);

	/*if (node != nullptr)
		std::cout << node->key << std::endl;*/
	std::cout << GetTickCount() << std::endl;
}
void ListTest()
{
	list *head = new list;
	head->val = 0;
	head->next = nullptr;
	list *header = head;

	int val = value;
	for (int i = 1; i <= val; i++) {
		list *ele = new list;
		ele->val = i;
		ele->next = nullptr;

		head->next = ele;
		head = ele;
	}

	std::cout << "List:" << std::endl;
	std::cout << GetTickCount() << std::endl;
	list *ele = header;
	int counter = 0;
	while (ele != nullptr)
	{
		if (ele->val == val)break;

		counter++;
		ele = ele->next;
	}
	std::cout << GetTickCount() << std::endl;
}

void BSTTest()
{
	BSTree<int> bst;

	for (int i = 0; i < 10; i++) {
		BSTreeNode<int> *node = new BSTreeNode<int>(i);
		bst.Insert(node);
	}

	std::cout << "InOrder" << std::endl;
	bst.InOrder();
	std::cout << std::endl;

	std::cout << "PreOrder" << std::endl;
	bst.PreOrder();
	std::cout << std::endl;

	std::cout << "PostOrder" << std::endl;
	bst.PostOrder();
	std::cout << std::endl;

	bst.Remove(1);
	std::cout << "Max:" << bst.Max() << std::endl;
	std::cout << "Min:" << bst.Min() << std::endl;

	bst.Destroy();

	std::cout << "InOrder" << std::endl;
	bst.InOrder();
	std::cout << std::endl;

	std::cout << "PreOrder" << std::endl;
	bst.PreOrder();
	std::cout << std::endl;

	std::cout << "PostOrder" << std::endl;
	bst.PostOrder();
	std::cout << std::endl;
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	BSTTest();
	return 0;
}

