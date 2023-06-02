#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class Node{
public:
    Node* m_next;
    T* m_data;

    Node(T* newData=nullptr, Node* next=nullptr) : m_data(newData),m_next(next) {}
};



template<class T>
class LinkedList{
private:
    Node<T>* head; 
    int size;
public:
    LinkedList();
    ~LinkedList();
    int getSize() const;
    bool find(T* newData);
    T* getData(T* newData);
    void insert(T* newData);
    void remove(T* newData);
    void getAllElements(T** output);
};


template<class T>
LinkedList<T>::LinkedList(){
    head = new Node<T>();
    size =0;
}

template<class T>
LinkedList<T>::~LinkedList(){
    Node<T>* current = head;
    while(current!=nullptr){      
        Node<T>* temp = current;
        current = current->m_next;
        delete temp;
    }
}

template<class T>
int LinkedList<T>::getSize() const{
    return size;
}

template<class T>
bool LinkedList<T>::find(T* newData){
    Node<T>* current = head->m_next;
    while(current!=nullptr){
        if(*(current->m_data)== *(newData)){
            return true;
        }
        current = current->m_next;
    }
    return false;
}

template<class T>
T* LinkedList<T>::getData(T* newData){
    Node<T>* current = head->m_next;
    while(current!=nullptr){
        if(*(current->m_data)== *(newData)){
            return current->m_data;
        }
        current = current->m_next;
    }
    return nullptr;
}

template<class T>
void LinkedList<T>::insert(T* newData) {
    Node<T>* newNode = new Node<T>(newData,head->m_next);
    head->m_next = newNode;
    size++;
}

template<class T>
void LinkedList<T>::remove(T* newData){
    if(!find(newData)){
        return;
    }

    Node<T>* current = head;
    while(*(current->m_next->m_data)!=*newData){
        current = current->m_next;
    }

    Node<T>* temp = current->m_next;
    current->m_next = temp->m_next;
    delete temp; 
    size--;  
}

template<class T>
void LinkedList<T>::getAllElements(T** output){
    Node<T>* current = head->m_next;
    while (current)
    {
        *output = current->m_data;
        output++;
        current = current->m_next;
    }
}


#endif
