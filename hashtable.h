#ifndef HashTable_H
#define HashTable_H

#include "utilesWet2.h"
#include "client.h"
#include "avl.h"
#include <iostream>



class  HashTable{//assum that T have an integer filed calld id
private:
    Avl_Tree<Client>* m_hashTable;
    int m_amount_of_elements;
    int m_hashTable_size;

    static const int INITIAL_HASH_SIZE = 4;
    static const int ENLARGE_PERCENTAGE = 75;
    static const int REDUCE_PERCENTAGE = 25;

    void helperFunction(int newSize);
 
public:
    HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    ~HashTable();

    void insert(Client* newData);
    void remove(Client* newData);
    bool find(Client* newData) const;
    Client* getData(Client* newData);
    void rehashEnlarge();
    void rehashReduce();

    void getAllElements(Client** output) const;
    int getAmountOfClients() const;
};

#endif

