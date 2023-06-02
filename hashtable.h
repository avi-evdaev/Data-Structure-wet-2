#ifndef HashTable_H
#define HashTable_H

#include "utilesWet2.h"
#include "client.h"


class  HashTable{//assum that T have an integer filed calld id
private:
    LinkedList<Client>* m_hashTable;
    int m_amount_of_elements;
    int m_hashTable_size;

    static const int INITIAL_HASH_SIZE = 7;
    static const double ENLARGE_PERCENTAGE = 75.0;
    static const double REDUCE_PERCENTAGE = 25.0;

    void helperFunction(int newSize);
 
public:
    HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    ~HashTale();

    void insert(Client* newData);
    void remove(Client* newData);
    bool find(Client* newData) const;
    Client* getData(Client* newData);
    void rehashEnlarge();
    void rehashReduce();

    void getAllElements(Client** output) const;
    int getAmountOfClients() const
};

int hashFunction(Client* client, int x){
    return client->getId % x;
}


HashTable:: HashTable(){
    m_amount_of_elements = 0;
    m_hashTable_size = INITIAL_HASH_SIZE;
    m_hashTable = new LinkedList<Client>[m_hashTable_size];
}

void HashTable::insert(Client* newData){
    int key = hashFunction(newData,m_hashTable_size);
    m_hashTable[key].insert(newData);
    m_amount_of_elements++;
    rehashEnlarge();
}

void HashTable::remove(Client* newData){
    int key = hashFunction(newData, m_hashTable_size);
    m_hashTable[key].remove(newData);
    m_amount_of_elements--;
    rehashReduce();
}


bool HashTable::find(Client* newData) const{
    int key = hashFunction(newData,m_hashTable_size);
    return m_hashTable[key].find(newData);
}

Client* HashTable::getData(Client* newData){
    int key = hashFunction(newData,m_hashTable_size);
    return m_hashTable[key].getData(newData);
}


void HashTable::rehashEnlarge(){
    double fillingPercentage = ((double)m_amount_of_elements/m_hashTable_size)*100;
    if(fillingPercentage < ENLARGE_PERCENTAGE)
    {
        return;
    }
    int newSize = 2*m_hashTable_size +1;//TO CHEKC IN THE FUTURE !!
    helperFunction(newSize);
}



void HashTable::rehashReduce(){
    double fillingPercentage = ((double)m_amount_of_elements/m_hashTable_size)*100;
    if(fillingPercentage > REDUCE_PERCENTAGE || m_hashTable_size<=INITIAL_HASH_SIZE)
    {
        return;
    }
    int newSize = (m_hashTable_size-1)/2 ;//TO CHEKC IN THE FUTURE !!
    helperFunction(newSize);
}


void HashTable::helperFunction(int newSize){
    LinkedList<Client>* newHashTable = new LinkedList<Client>[newSize];
    Client* allData = new Client*[m_amount_of_elements];

    int sum =0;
    for(i=0; i<m_hashTable_size;++i){
        int temp = m_hashTable[i].getSize();
        m_hashTable[i].getAllElements(allData+sum);
        sum+=temp;   
    }

    for(int i =0; i<m_amount_of_elements;i++)
    {
        int key = hashFunction(allData[i],newSize);
        newHashTable[key].insert(allData[i]);
    }
    
    delete[] m_hashTable;
    delete[] allData;

    m_hashTable = newHashTable;
    m_hashTable_size = newSize;
}

int HashTable::getAmountOfClients() const{
    return m_amount_of_elements;
}

void HashTable::getAllElements(Client** output) const{
    int sum =0;
    for(i=0; i<m_hashTable_size;++i){
        int temp = m_hashTable[i].getSize();
        m_hashTable[i].getAllElements(output+sum);
        sum+=temp;   
    }
}


HashTable::~ HashTable(){ 
    delete[] m_hashTable;
}

#endif




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
    LinkedList(){
        head = new Node<T>();
        size =0;
    }

    ~LinkedList(){
        Node<T>* current = head;
        while(current!=nullptr){      
            Node<T>* temp = current;
            current = current->m_next;
            delete temp;
        }
    }

    int getSize() const{
        return size;
    }

    bool find(T* newData){
        Node<T>* current = head->m_next;
        while(current!=nullptr){
            if(*(current->m.data)== *(newData->m_data)){
                return true;
            }
            current = current->m_next;
        }
        return false;
    }

    T* getData(T* newData){
        Node<T>* current = head->m_next;
        while(current!=nullptr){
            if(*(current->m.data)== *(newData->m_data)){
                return current->m_data;
            }
            current = current->m_next;
        }
        return nullptr;
    }

    void insert(T* newData) {
        Node<T>* newNode = new Node<T>(newData,head->m_next);
        head->m_next = newNode;
        size++;
    }

    void remove(T* newData){
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

    void getAllElements(T** output){
        Node<T>* current = head->m_next;
        while (current)
        {
            *output = current->m_data;
            output++;
            current = current->m_next
        }
    }

};

