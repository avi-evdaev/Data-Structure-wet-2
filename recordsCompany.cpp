#include "recordsCompany.h"

RecordsCompany::RecordsCompany() {}

RecordsCompany::~RecordsCompany() {}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone) {}

Output_t<int> RecordsCompany::getPhone(int c_id) {}

StatusType RecordsCompany::makeMember(int c_id) {}

Output_t<bool> RecordsCompany::isMember(int c_id) {}

StatusType RecordsCompany::buyRecord(int c_id, int r_id) {}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){

    if(amount<=0 || c_id1 <0 || c_id1> c_id2){
        return StatusType::INVALID_INPUT;
    }

    MemberClient t1 = MemberClient(c_id1-1);
    MemberClient t2 = MemberClient(c_id2-1);
    m_membersTree.addPrize(&t1,&t2,amount);
    return StatusType::SUCCESS;
}


Output_t<double> RecordsCompany::getExpenses(int c_id) {}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {}
