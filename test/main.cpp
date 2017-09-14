#include <iostream>
using std::cout;
using std::endl;

#include "binaryTree.h"

int main (){
	cout << "De volta ao C++" << endl;
	Node<int> *node = new Node<int>(1);
	BinaryTree<int> *tree = new BinaryTree<int>(1);

	cout << "Node Level: " << node->getLevel() << endl; 
	cout << "Tree: Root Level: " << tree->getRoot()->getLevel() << endl; 
	cout << "Tree: " << tree->getRoot()->getLevel() << endl; 

	tree->insert(2);

	if(tree->find(2)) cout << "Finded" << endl;
	else cout << "Not founded" << endl;

	delete node;
	delete tree;

	return 0;
}