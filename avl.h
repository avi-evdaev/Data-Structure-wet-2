#ifndef AVL_TREE_H_
#define AVL_TREE_H_


#include <iostream>


template <class T>
class Node {
public: 
    T* data; 
    Node* left;
    Node* right;
    Node* father;
    double extra;
    int height;
    Node(T* new_data,int extra =0 , Node* left_son = nullptr, Node* right_son = nullptr, Node* new_father = nullptr, int newHeight = 0) :
         data(new_data), left(left_son), right(right_son), father(new_father), extra(extra), height(newHeight)  {}
};


template <class T>
class Avl_Tree{
private:
    void rotateRight(Node<T>* vertex);
    void rotateLeft(Node<T>* vertex);

    void LLrotation(Node<T>* vertex);
    void RLrotation(Node<T>* vertex);
    void RRrotation(Node<T>* vertex);
    void LRrotation(Node<T>* vertex);
    Node<T>* getVertexNode(T* newData) const;
    void helperDestruct(Node<T>* root);

    int balanceFactor(Node<T>* vertex) const;
    void update_height(Node<T>* vertex);
    void DeleteNode(T* newData);
    void helperIntializerExtra(Node<T>* node);
public:
    Node<T>* root;
    Avl_Tree(): root(nullptr) {}
    ~Avl_Tree();

    void InsertNode(T* newData);

    T* getVertex(T* newData) const;
    bool isVertexExist(T* newData) const;

    void getAllDataArry(T** output);
    int helperGetAllDataArry(T** output, Node<T>* root);
    T* giveMax() const;

    void add(T* i, int x);
    double find_prize(T* vertex);
    void addPrize(T* t1, T* t2, double amount);

    void intializeExtra();
};

template <class T>
void Avl_Tree<T>::intializeExtra() {
    helperIntializerExtra(root);
}

template <class T>
void Avl_Tree<T>::helperIntializerExtra(Node<T>* node){
    if(!node){
        return;
    }
    node->extra = 0;
    helperIntializerExtra(node->right);
    helperIntializerExtra(node->left);

}

template <class T>
void Avl_Tree<T>::addPrize(T* t1, T* t2, double amount){
    add(t2,amount);
    add(t1,-amount);
}



template <class T>
void Avl_Tree<T>::add(T* i, int x){ //מי שמאמין לא מתעד 
    Node<T>* current = root;
    bool last_turn_is_right = false;
    while(current != nullptr){
        if(*(current->data) < *i){
            if(!last_turn_is_right){
                current->extra += x;
            }
            current = current->right;
            last_turn_is_right = true;
        }
        else if (*(current->data) > *i){
            if(last_turn_is_right){
                current->extra -= x;
            }
            current = current->left;
            last_turn_is_right = false;
        }
        else{
            if(!last_turn_is_right){
                current->extra += x;
            }
            if(current->right){
                current->right->extra -= x; 
            }
            return;
        }
    }
}



template <class T>
double Avl_Tree<T>::find_prize(T* vertex){///CHECK THIS IN THE FUTURE
    Node<T>* temp = getVertexNode(vertex);
    int sum = 0;
    while(temp != root){
        sum += temp->extra;
        temp = temp->father;
    }
    sum += root->extra;
    return sum;
}    






template <class T>
T* Avl_Tree<T>::giveMax() const{
    Node<T>* current = root;
    if(!current) return nullptr;
    while(current->left){
        current = current->left;
    }
    return current->data;
}


template <class T>
Avl_Tree<T>::~Avl_Tree(){
    helperDestruct(root);
}

template <class T>
void Avl_Tree<T>::helperDestruct(Node<T>* root){
    if(!root){
        return;
    }
    helperDestruct(root->left);
    helperDestruct(root->right);
    delete root;
    return;
}

template <class T>
void Avl_Tree<T>::getAllDataArry(T** output) {
    helperGetAllDataArry(output,root);
}

template <class T>
int Avl_Tree<T>::helperGetAllDataArry(T** output, Node<T>* root){
    if(!root) return 0;
    int finished = helperGetAllDataArry(output,root->left);
    output[finished] = root->data;
    
    finished+=helperGetAllDataArry(output+finished+1,root->right);
    finished++;
    return finished;
}





template <class T>
void Avl_Tree<T>::DeleteNode(T* newData){
    Node<T>* badNode = getVertexNode(newData);
    Node<T>* v;
    if(badNode==nullptr){
        return;
    }
 

    if(badNode->height==0){
        if(badNode == root){
            root = nullptr;
            delete badNode;
            return;
        }

        if(badNode->father->right==badNode){
            badNode->father->right = nullptr;
        }
        else{
            badNode->father->left = nullptr;
        }


        v = badNode->father;
        delete badNode;
    }
    else if(badNode->right==nullptr){

        if(badNode==root){
            root= badNode->left;        
        }
        else if(badNode->father->right==badNode){
            badNode->father->right= badNode->left;
        }
        else{
            badNode->father->left= badNode->left;
        }

        badNode->left->father = badNode->father;
        v = badNode->father;
        delete badNode;
    }
    else if(badNode->left==nullptr){

        if(badNode==root){
            root= badNode->right;        
        }
        else if(badNode->father->right==badNode){
            badNode->father->right= badNode->right;
        }
        else{
            badNode->father->left= badNode->right;
        }

        badNode->right->father = badNode->father;
        v = badNode->father;
        delete badNode;
    }
    else{
        Node<T>* next = badNode->right;
        while (next->left)
        {
            next = next->left;
        }
        
        T* temp = badNode->data;
        badNode->data = next->data;
        next->data = temp;

        if(next->father->right == next){
            if(next->right){
               next->father->right = next->right;
               next->right->father = next->father;
            }
            else{
                next->father->right = nullptr;                
            }
        }
        else{
            if(next->right){
               next->father->left = next->right;
               next->right->father = next->father;
            }
            else{
            next->father->left = nullptr;                
            }

        }
        v = next->father;
        delete next;

    }

    if(!v){
        return;
    }

    while(v!=nullptr){
        int old_v_height = v->height;
        update_height(v);

        int bf = balanceFactor(v);

        if(bf==-2 || bf==2){
            if(bf==2){
                if(balanceFactor(v->left)>=0){
                    LLrotation(v);
                }
                else{
                    LRrotation(v);
                }
            }
            else if(bf==-2){
                if(balanceFactor(v->right)<=0){
                    RRrotation(v);
                }
                else{
                    RLrotation(v);
                }
            }
            v = v->father;
        }

        if(old_v_height==v->height){
            return;
        }
        else{
            v = v->father;
        }       
    }
}




template <class T>
T* Avl_Tree<T>::getVertex(T* newData) const {
    Node<T>* temp = getVertexNode(newData);
    if(temp){
        return temp->data;
    }
    return nullptr;
}

template <class T>
bool Avl_Tree<T>::isVertexExist(T* newData) const {
    return nullptr!=getVertexNode(newData);
}



template <class T>
Node<T>* Avl_Tree<T>::getVertexNode(T* newData) const {
    if (this->root == nullptr){
        return nullptr;
    }

        Node<T>* current = this->root;
   

    while (1){
        if (*current->data < *newData){//implement < for T
            if(current->right == nullptr){
                return nullptr;
            }
            current = current->right;
        }
        else if(*current->data > *newData){
            if(current->left == nullptr){
                return nullptr;
            }
            current = current->left;
        }
        else{
            return current;
        }
    }
}


template<class T>
void Avl_Tree<T>:: rotateRight(Node<T>* vertex) {
    

    Node<T>* B = vertex;
    Node<T>* A = vertex->left;
    Node<T>* A_R = A->right;
    Node<T>* C = vertex->father;
    int old_b = B->extra;
    int old_a = A->extra;

    
    if(vertex == root ){
        this->root = A;
    }
    else if(vertex==vertex->father->left){
        vertex->father->left = A;
    }
    else if(vertex==vertex->father->right){
        vertex->father->right = A;
    }

    A->right = B;
    B->left = A_R;
    update_height(B);
    update_height(A);
    A->father = C;
    if(A_R!=nullptr){
        A_R->father = B;
    }
        
    B->father = A;

    A->extra = old_a+old_b;
    B->extra = -old_a;
    if(A_R)
    {
        A_R->extra += old_a;
    }
}

template<class T>
void Avl_Tree<T>::rotateLeft(Node<T>* vertex) {
    
    Node<T>* A = vertex;
    Node<T>* B = vertex->right;
    Node<T>* B_L = B->left;
    Node<T>* C = vertex->father;
    int old_b = B->extra;
    int old_a = A->extra;



    if(vertex==root){
        this->root = B;
    }
    else if(vertex==vertex->father->left){
        vertex->father->left = B;
    }
    else if(vertex==vertex->father->right){
        vertex->father->right = B;
    }

    B->left = A;
    A->right = B_L;
    update_height(A); 
    update_height(B);
    A->father = B;
    if(B_L!=nullptr){
        B_L->father = A;
    }
    B->father = C;
    
    B->extra = old_a + old_b;
    A->extra =  -old_b;

    if(B_L){
        B_L->extra += old_b;
    }

}


template<class T>
void Avl_Tree<T>::LLrotation(Node<T>* vertex) {
    this->rotateRight(vertex);
}


template<class T>
void Avl_Tree<T>::RLrotation(Node<T>* vertex) {
    this->rotateRight(vertex->right);
    this->rotateLeft(vertex);         
}



template<class T>
void Avl_Tree<T>::RRrotation(Node<T>* vertex) {
    this->rotateLeft(vertex);
}



template<class T>
void Avl_Tree<T>::LRrotation(Node<T>* vertex) {
    this->rotateLeft(vertex->left);
    this->rotateRight(vertex);
}


template<class T>
void Avl_Tree<T>::InsertNode(T* newData){
    if(this->isVertexExist(newData)){
        return;
    }
    Node<T>* newNode;
    try{
        newNode = new Node<T>(newData);
    }
    catch(...){
        throw;
    }
    Node<T>* current = this->root;
    if (this->root == nullptr){
        this->root = newNode;
        return;
    }
   

    while (1){
        if (*(current->data) < *newData){//implement < for T
            if(current->right == nullptr){
                current->right = newNode;
                newNode->father = current;
                newNode->extra = -find_prize(current->data);
                current = current->right;
                break;
            }
            current = current->right;
        }
        else{
             if(current->left == nullptr){
                current->left = newNode;
                newNode->father = current;
                newNode->extra = -find_prize(current->data);
                current = current->left;
                break;
            }
            current = current->left;
        }
    }

    Node<T>* v = current;
    Node<T>* p;


    while(v!=root){

        p = v->father;

        if(p->height > v->height){
            break;
        }
        else{
            p->height = v->height +1;
        }

        int currentBalanceFactor = balanceFactor(p);

        if(currentBalanceFactor==2){
            if(balanceFactor(p->left)>=0){
                LLrotation(p);
            }
            else{
                LRrotation(p);
            }
            break;
        }
        else if(currentBalanceFactor==-2){
            if(balanceFactor(p->right)<=0){
                RRrotation(p);
            }
            else{
                RLrotation(p);
            }
            break;
        }
        else{
            v = p;
        }
    }


}  



template<class T>
int Avl_Tree<T>::balanceFactor(Node<T>* p) const{

    if(p==nullptr){
        return 0;
    }

    int left_son_height =-1;
    int right_son_height =-1;

    if(p->left != nullptr){
        left_son_height = p->left->height;
    }
    if(p->right != nullptr){
        right_son_height = p->right->height;
    }  

    int currentBalanceFactor = left_son_height - right_son_height;
    return currentBalanceFactor;
}
     
template <class T>
void Avl_Tree<T>::update_height(Node<T>* p){
    if(p==nullptr){
        return;
    }

    int left_son_height =-1;
    int right_son_height =-1;

    if(p->left != nullptr){
        left_son_height = p->left->height;
    }
    if(p->right != nullptr){
        right_son_height = p->right->height;
    }

    p->height = 1+((left_son_height>right_son_height) ? left_son_height:right_son_height );
}



#endif //AVL_TREE_H_