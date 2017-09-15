#include <iostream>
using std::cout;
using std::endl;

#include "binaryTree.h"

int main (){
	Node<int> *node = new Node<int>(1);
	BinaryTree<int> *tree = new BinaryTree<int>(1);

	//cout << "Node Level: " << node->getLevel() << endl; 
	//cout << "Tree: Root Level: " << tree->getRoot()->getLevel() << endl; 
	tree->insert(2);
	tree->insert(3);
	tree->insert(4);
	
	tree->insert(5);
	tree->insert(6);
	tree->insert(3);
	
	for(int i=0; i<8; i++){
		if(tree->find(i)) cout << i << " Finded" << endl;
		else cout << i << " Not finded" << endl;
	}

	delete node;
	delete tree;

	return 0;
}
