#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_ 

#include <cstdlib>

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

		/** @brief Sobrecarga do operador de atribuicao (para Data)
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

/*template <typename T>
class Level{
	private:
		Node<T>* node;
		int level; 

	public:
		Node(){
			level = -1;
			//data=NULL;
			Sae_ptr=nullptr;
			Sad_ptr=nullptr;
		}

		Level(T value){
			node = new Node<T>(value);
			level = 0;
		}

		~Level(){
			delete node;
		}

		Node<T>* getNode(){ 
			return node; 
		}

		int getLevel(){ 
			return level; 
		}

		void upLevel(){ 
			level++; 
		}

		/** @brief Sobrecarga do operador de atribuicao (para Data)
		* @param	d Data que sera passada por atribuicao  
		* @return	Retorna a Data atribuida
		*/
		/*Node& operator=(const Node d){
			node = d;
			level = d.level;
			Sae_ptr = d.Sae_ptr;
			Sad_ptr = d.Sad_ptr;

			return *this;
		}
};*/

template <typename T>
class BinaryTree{
private:
	Node<T>* root;
	Node<T>* nodeFinded; //Only used in searchs

	//flags
	bool searchFlag;
	bool fullFlag;

	int treeHeight;
	int maxNodePerLevel;
	int nodePerLevel;
	
	Node<T>* getFinded(){
		return nodeFinded;
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

	void setOnSearch(){
		searchFlag = true;
	}

	void setOffSearch(){
		searchFlag = false;
	}

	bool findWhoPointsTo(Node<T>* node){
		if(checkIfIsHere(root, node)){
			setFinded(root);
			setOffSearch();
			return true;
		}
		
		setOnSearch();

		bool resultSae = false;
		bool resultSad = false;
		if(root->getSae()) resultSae = findIn(root->getSae(), node);
		if(root->getSad()) resultSad = findIn(root->getSad(), node);

		setOffSearch();
		return resultSae or resultSad;
	}

	bool checkIfIsHere(Node<T>* rt, Node<T>* node){
		//cout << rt->getData() << " - " <<  node->getData() << endl;
		if(rt->getData() == node->getData())  {
			return true;
		}
		if(rt->getSae()){
			if(rt->getSae()->getData() == node->getData()) {
				return true;
			}
		}	
		if(rt->getSad()){
			if(rt->getSad()->getData() == node->getData()) {
				return true;
			}
		}
		return false;
	}

	bool findIn(Node<T>* rt, Node<T>* node){
		if(checkIfIsHere(rt, node)){
			setFinded(rt);
			setOffSearch();
			return true;
		}

		bool resultSae = false;
		bool resultSad = false;
		if(rt->getSae()) resultSae = findIn(rt->getSae(), node);
		if(rt->getSad()) resultSad = findIn(rt->getSad(), node);

		return resultSae or resultSad;
	}

	//I need to find the first null in the same level
	Node<T>* findFirstNullInLevel(Node<T> *rt, int level){
		if(level<treeHeight){
			Node<T>* result_Sae = nullptr;
			Node<T>* result_Sad = nullptr;

			if(rt->getSae()) result_Sae = findFirstNullInLine(rt->getSae(), level+1);
			if(rt->getSad()) result_Sad = findFirstNullInLine(rt->getSad(), level+1);
		
			return result_Sae or result_Sad;
		} else if(level==treeHeight){
			if(!rt->getSae()) {
				
				return rt;
			}
			if(!rt->getSad()) {
				
				return rt;
			}
			return nullptr;
		}
		else {
			return nullptr;
		}
	}

	insertInto(node, value);


public:
	/*BinaryTree(){
		searchFlag = false;
		root = new Node<T>();
	}*/

	BinaryTree(T value){
		root = new Node<T>(value);
		root->setLevel(0);

		searchFlag = false;
		fullFlag = true;
		treeHeight=0;
		
	}

	~BinaryTree(){
		searchFlag = false;
		//delete root;
	}

	Node<T>* getRoot(){
		return root;
	}

	void insert(T value){
		int level=0;

		upNodePerLevel();
		Node<T>* node = findFirstNullInLevel(root, level);
		if(node) insertInto(node, value);
		else cout << "Something is going wrong" << endl;
	}

	bool find(T value){
		Node<T>* node = new Node<T>(value); 
		bool result = findWhoPointsTo(node);
		delete node;

		return result;
	}
};





#endif