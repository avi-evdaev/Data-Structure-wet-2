#include "unionfind.h"


UnionFindRecords::UnionFindRecords(): m_number_of_records(0), m_records_arry(nullptr), m_initalized(false) {}

UnionFindRecords::~UnionFindRecords(){
    if(m_initalized){
        delete[] m_records_arry;
    }
}

void UnionFindRecords::init(int *records_stocks, int number_of_records){//remember to check the allocation outside !

    Record* temp = new Record[number_of_records];
    if(m_initalized){
        delete[] m_records_arry;         
    }

    m_records_arry = temp;
    m_number_of_records = number_of_records;
    m_initalized = true;

    for(int i=0;i<number_of_records;++i){
        m_records_arry[i].init(i,records_stocks[i]);
    }
}

int UnionFindRecords::Find(int record_number){
    int root = record_number;
    int sum = 0;
    while (m_records_arry[root].m_parent != -1){
        sum += m_records_arry[root].m_extra;        
        root = m_records_arry[root].m_parent;
    }

    int current = record_number;
    int toSubtract=0;
    while(current!=root){
        int temp = m_records_arry[current].m_extra;
        m_records_arry[current].m_extra = sum - toSubtract;
        toSubtract+=temp;
        current = m_records_arry[current].m_parent;
        m_records_arry[current].m_parent = root;            
    }
    return root;
}

void UnionFindRecords::Union(int b, int a){
    int a_extra_old = m_records_arry[a].m_extra;
    int h_a = m_records_arry[a].m_height;

    if (m_records_arry[a].m_rootSize >=m_records_arry[b].m_rootSize){ 
        m_records_arry[b].m_extra += h_a - a_extra_old;
        m_records_arry[b].m_parent = a;
        m_records_arry[a].m_rootSize += m_records_arry[b].m_rootSize;
        m_records_arry[a].m_height += m_records_arry[b].m_height;
        m_records_arry[b].m_rootSize = 0;
        m_records_arry[b].m_height = 0;
        m_records_arry[b].m_column = 0;
    }
    else{
        m_records_arry[b].m_extra += h_a;
        m_records_arry[a].m_extra -= m_records_arry[b].m_extra;
        m_records_arry[a].m_parent = b;
        m_records_arry[b].m_rootSize += m_records_arry[a].m_rootSize;
        m_records_arry[b].m_height += m_records_arry[a].m_height;
        m_records_arry[a].m_rootSize = 0;
        m_records_arry[a].m_height = 0;
        m_records_arry[b].m_column = m_records_arry[a].m_column;
        m_records_arry[a].m_column = 0;        
    }
}

int UnionFindRecords::getHeight(int record_number) const {
        int root = record_number;
        int sum = 0;
        while (m_records_arry[root].m_parent != -1){
            sum += m_records_arry[root].m_extra;
            root = m_records_arry[root].m_parent;
        }
        sum += m_records_arry[root].m_extra;
        return sum;
}

int UnionFindRecords::getColumn(int record_number) const {
        int root = record_number;
        
        while (m_records_arry[root].m_parent != -1){
            root = m_records_arry[root].m_parent;
        }

        return m_records_arry[root].m_column;
}

