#include "hashtable.h"

int hashFunction(Client* client, int x){
    return client->getId() % x;
}


HashTable:: HashTable(){
    m_amount_of_elements = 0;
    m_hashTable_size = INITIAL_HASH_SIZE;
    m_hashTable = new Avl_Tree<Client>[m_hashTable_size];
}

void HashTable::insert(Client* newData){
    int key = hashFunction(newData,m_hashTable_size);
    m_hashTable[key].InsertNode(newData);
    m_amount_of_elements++;
    rehashEnlarge();
}

void HashTable::remove(Client* newData){
    int key = hashFunction(newData, m_hashTable_size);
    m_hashTable[key].DeleteNode(newData);
    m_amount_of_elements--;
    rehashReduce();
}


bool HashTable::find(Client* newData) const{
    int key = hashFunction(newData,m_hashTable_size);
    return m_hashTable[key].isVertexExist(newData);
}

Client* HashTable::getData(Client* newData){
    int key = hashFunction(newData,m_hashTable_size);
    return m_hashTable[key].getVertex(newData);
}


void HashTable::rehashEnlarge(){
    double fillingPercentage = ((double)m_amount_of_elements/m_hashTable_size)*100;
    if(fillingPercentage <= (double)ENLARGE_PERCENTAGE)
    {
        return;
    }
    int newSize = 2*m_hashTable_size;
    helperFunction(newSize);
}



void HashTable::rehashReduce(){
    double fillingPercentage = ((double)m_amount_of_elements/m_hashTable_size)*100;
    if(fillingPercentage >= (double)REDUCE_PERCENTAGE || m_hashTable_size<=INITIAL_HASH_SIZE)
    {
        return;
    }
    int newSize = m_hashTable_size/2 ;
    helperFunction(newSize);
}


void HashTable::helperFunction(int newSize){
    Avl_Tree<Client>* newHashTable = new Avl_Tree<Client>[newSize];
    Client** allData = new Client*[m_amount_of_elements];

    int sum =0;
    for(int i=0; i<m_hashTable_size;++i){
        int temp = m_hashTable[i].getSize();
        m_hashTable[i].getAllDataArry(allData+sum);
        sum+=temp;   
    }

    for(int i =0; i<m_amount_of_elements;i++)
    {
        int key = hashFunction(allData[i],newSize);
        newHashTable[key].InsertNode(allData[i]);
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
    for(int i=0; i<m_hashTable_size;++i){
        int temp = m_hashTable[i].getSize();
        m_hashTable[i].getAllDataArry(output+sum);
        sum+=temp;   
    }
}


HashTable::~ HashTable(){ 
    delete[] m_hashTable;
}
