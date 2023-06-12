#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "avl.h"
#include "MemberClient.h"
#include "unionfind.h"
#include "hashtable.h"


class RecordsCompany {
  private:
    Avl_Tree<MemberClient> m_membersTree;
    HashTable m_clientsHashTable;
    UnionFindRecords m_recordsGroups;

    int m_number_of_clients;
    int m_number_of_records;
    int m_number_of_members;
    int* m_records_stocks;    
    int* m_records_bought;

    static const int RECORD_PRICE = 100;

  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif