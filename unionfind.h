#ifndef UnionFind_H
#define UnionFind_H

#include <iostream>
#include "record.h"

class UnionFindRecords{
private:
    int m_number_of_records;
    Record* m_records_arry;
    bool m_initalized;
    
public:
    UnionFindRecords();
    UnionFindRecords(const UnionFindRecords& other) = delete;
    UnionFindRecords& operator=(const UnionFindRecords& other) = delete;
    ~UnionFindRecords();
    
    void init(int *records_stocks, int number_of_records);
    int Find(int record_number);
    void Union(int b, int a);
};


#endif