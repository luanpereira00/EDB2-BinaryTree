#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_ 

#include <math.h>

using std::nullptr_t;

template <typename T>
class Node{
	private:
		T data;
		int level;
		Node<T>* Sae_ptr;
		Node<T>* Sad_ptr; 

	public:
		/*Node(){
			level = -1;
			//data=NULL;
			Sae_ptr=nullptr;
			Sad_ptr=nullptr;
		}*/

		Node(T d){
			data = d;
			level = -1;
			Sae_ptr=nullptr;
			Sad_ptr=nullptr;
		}

		~Node(){
			level = -1;
			//data=NULL;
			Sae_ptr=nullptr;
			Sad_ptr=nullptr;
		}

		T getData(){ 
			return data; 
		}
		int getLevel(){ 
			return level; 
		}
		Node<T>* getSae(){ 
			return Sae_ptr; 
		}
		Node<T>* getSad(){ 
			return Sad_ptr; 
		}

		void setData(T d){ 
			data = d; 
		}
		void setLevel(int l){ 
			level = l; 
		}
		void setSae(Node<T>* s){ 
			Sae_ptr = s; 
		}
		void setSad(Node<T>* s){ 
			Sad_ptr = s; 
		}

		/** 
		* @brief Sobrecarga do operador de atribuicao (para Data)
		* @param	d Data que sera passada por atribuicao  
		* @return	Retorna a Data atribuida
		*/
		Node& operator=(const Node d){
			data = d.data;
			level = d.level;
			Sae_ptr = d.Sae_ptr;
			Sad_ptr = d.Sad_ptr;

			return *this;
		}
};


template <typename T>
class BinaryTree{
private:
	Node<T>* root;
	Node<T>* nodeFinded; //Only used in searchs
	Node<T>* nodeNextIsNull;

	//flags
	bool searchFlag;
	bool fullFlag;
	bool needNextNullFlag;

	int treeHeight;
	int maxNodePerLevel;
	int nodePerLevel;
	
	Node<T>* getFinded(){
		return nodeFinded;
	}

	Node<T>* getNextNull(){
		return nodeNextIsNull;
	}

	void upNodePerLevel(){
		nodePerLevel++;
		checkIfNeedGrowUp();
	}

	void checkIfNeedGrowUp(){
		if(nodePerLevel>maxNodePerLevel) growTree();
	}

	void growTree(){
		fullFlag = false; //do i need it?
		treeHeight++;
		maxNodePerLevel=pow(treeHeight, 2);
		nodePerLevel=0;
	}

	void setFinded(Node<T>* n){
		nodeFinded = n;
	}

	void setNextNull(Node<T>* n){
		needNextNullFlag = false;
		nodeNextIsNull = n;
	}

	void setOnSearch(){
		searchFlag = true;
	}

	void setOffSearch(){
		searchFlag = false;
	}

	bool findWhoPointsTo(Node<T>* node){
		if(root->getData()==node->getData()){
			setFinded(root);
			setOffSearch();
			return true;
		}
		if(checkIfIsNext(root, node)){
			return true;
		}
		
		setOnSearch();

		bool resultSae = false;
		bool resultSad = false;
		if(searchFlag and root->getSae()) resultSae = findIn(root->getSae(), node);
		if(!root->getSae()) setNextNull(root);

		if(searchFlag and root->getSad()) resultSad = findIn(root->getSad(), node);
		if(!root->getSad()) setNextNull(root);

		setOffSearch();
		return resultSae or resultSad;
	}

	bool checkIfIsNext(Node<T>* rt, Node<T>* node){
		//cout << rt->getData() << " - " <<  node->getData() << endl;
		if(searchFlag and rt->getSae()){
			if(rt->getSae()->getData() == node->getData()) {
				setFinded(rt);
				setOffSearch();
				return true;
			}
		}	
		if(searchFlag and rt->getSad()){
			if(rt->getSad()->getData() == node->getData()) {
				setFinded(rt);
				setOffSearch();
				return true;
			}
		}
		return false;
	}

	bool findIn(Node<T>* rt, Node<T>* node){
		if(checkIfIsNext(rt, node)){
			setFinded(rt);
			setOffSearch();
			return true;
		}

		bool resultSae = false;
		bool resultSad = false;
		if(searchFlag and rt->getSae()) resultSae = findIn(rt->getSae(), node);
		if(rt->getLevel()==treeHeight and !rt->getSae()) setNextNull(rt);

		if(searchFlag and rt->getSad()) resultSad = findIn(rt->getSad(), node);
		if(rt->getLevel()==treeHeight and !rt->getSad()) setNextNull(rt);

		
		return resultSae or resultSad;
	}

	void insertIntoTree(Node<T>* node){
		Node<T>* next = getNextNull();
		if(!next->getSae()){
			next->setSae(node);
			cout << node->getData() <<" Inserido na esquerda de " << next->getData() << endl;
		} else if(!next->getSad()){
			next->setSad(node);
			cout << node->getData() <<" Inserido na direita de " << next->getData() << endl;
		} else {
			cout << "Deu erro" << endl;
		}
	}

public:
	/*BinaryTree(){
		searchFlag = false;
		root = new Node<T>();
	}*/

	BinaryTree(T value){
		root = new Node<T>(value);
		root->setLevel(0);
		setFinded(root);
		setNextNull(root);

		needNextNullFlag = false;
		searchFlag = false;
		fullFlag = true;

		treeHeight=1;
		growTree();
	}

	~BinaryTree(){
		searchFlag = false;
		//delete root;
	}

	Node<T>* getRoot(){
		return root;
	}

	void insert(T value){
		upNodePerLevel();
		//cout << "H: " << treeHeight << "\tMaxNode: " << maxNodePerLevel << "\tNode: " <<  nodePerLevel << endl;
		
		Node<T>* node = new Node<T>(value);
		node->setLevel(treeHeight);
		if(findWhoPointsTo(node)){
			cout << "já existe" << endl;
		} else {
			needNextNullFlag=true;
			insertIntoTree(node);
		}
	}

	bool find(T value){
		Node<T>* node = new Node<T>(value); 
		bool result = findWhoPointsTo(node);
		delete node;

		return result;
	}
};





#endif
