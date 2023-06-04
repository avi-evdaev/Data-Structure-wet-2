#ifndef Record_H
#define Record_H

struct Record{
    int m_parent;
    int m_rootSize;
    int m_extra;
    int m_height;

    Record() : m_parent(0), m_rootSize(0), m_extra(0), m_height(0) {}

    void init(int number_of_record, int stock){
        m_parent = number_of_record;
        m_rootSize = 1; 
        m_extra = 0;
        m_height = stock;
    }
};


#endif