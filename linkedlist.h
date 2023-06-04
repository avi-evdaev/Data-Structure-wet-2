#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class ListNode{
public:
    ListNode* m_next;
    T* m_data;

    ListNode(T* newData=nullptr, ListNode* next=nullptr) : m_next(next), m_data(newData) {}
};



template<class T>
class LinkedList{
private:
    ListNode<T>* head; 
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
    head = new ListNode<T>();
    size =0;
}

template<class T>
LinkedList<T>::~LinkedList(){
    ListNode<T>* current = head;
    while(current!=nullptr){      
        ListNode<T>* temp = current;
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
    ListNode<T>* current = head->m_next;
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
    ListNode<T>* current = head->m_next;
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
    ListNode<T>* newNode = new ListNode<T>(newData,head->m_next);
    head->m_next = newNode;
    size++;
}

template<class T>
void LinkedList<T>::remove(T* newData){
    if(!find(newData)){
        return;
    }

    ListNode<T>* current = head;
    while(*(current->m_next->m_data)!=*newData){
        current = current->m_next;
    }

    ListNode<T>* temp = current->m_next;
    current->m_next = temp->m_next;
    delete temp; 
    size--;  
}

template<class T>
void LinkedList<T>::getAllElements(T** output){
    ListNode<T>* current = head->m_next;
    while (current)
    {
        *output = current->m_data;
        output++;
        current = current->m_next;
    }
}


#endif
