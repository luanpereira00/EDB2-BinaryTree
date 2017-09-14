#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_ 

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
		void setLeve(int l){ 
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

template <typename T>
class BinaryTree{
private:
	Node<T>* root;
	bool searchFlag;
	Node<T>* nodeFinded;

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
		cout << rt->getData() << " - " <<  node->getData() << endl;
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

	Node<T>* getFinded(){
		return nodeFinded;
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

public:
	/*BinaryTree(){
		searchFlag = false;
		root = new Node<T>();
	}*/

	BinaryTree(T value){
		Node<T>* node = new Node<T>(value);
		searchFlag = false;
		root = node;
	}

	~BinaryTree(){
		searchFlag = false;
		//delete root;
	}

	Node<T>* getRoot(){
		return root;
	}

	void insert(Node<T>* no){
		Node<T>* node = new Node<T>(); 
		*node = *no;
	}

	bool find(T value){
		Node<T>* node = new Node<T>(value); 
		bool result = findWhoPointsTo(node);
		delete node;

		return result;
	}
};





#endif