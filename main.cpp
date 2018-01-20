// data_structure.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "tree\AvlTree.h"
#include "tree\RBTree.h"

void AvlTreeTest(){
	AVLTree<int> avl;

	for (int i = 0; i < 3000; i++)
		avl.Insert(i);

	std::cout << "Height:" << avl.Height() << std::endl;

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

	AVLTreeNode<int> *node = avl.SearchByIterator(9);

	if (node != nullptr)
		std::cout << node->key << std::endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	AvlTreeTest();
	return 0;
}

