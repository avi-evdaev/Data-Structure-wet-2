#include "recordsCompany.h"

RecordsCompany::RecordsCompany() :m_number_of_clients(0), m_number_of_records(0),m_number_of_members(0),
                m_records_stocks(nullptr), m_records_bought(nullptr) {}

RecordsCompany::~RecordsCompany() {
    //deleting the avl tree
    if(m_number_of_members>0){
        MemberClient** temp_arry = new MemberClient*[m_number_of_members];        
        m_membersTree.getAllDataArry(temp_arry);
        for(int i =0;i<m_number_of_members;i++){
            delete temp_arry[i];
        }
        delete[] temp_arry;        
    }


    //deleting the hashtable:
    if(m_number_of_clients>0){
        Client** temp_hashtable_arry= new Client*[m_number_of_clients];
        m_clientsHashTable.getAllElements(temp_hashtable_arry);
        for(int i =0;i<m_number_of_clients;i++){
            delete temp_hashtable_arry[i];
        }
        delete[] temp_hashtable_arry;
    }

    //deleting the records dataStructure:
    if(m_records_bought){
        delete[] m_records_bought;
    }
    if(m_records_stocks){
        delete[] m_records_stocks;
    } 
} 

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    m_number_of_records = number_of_records;
    if(number_of_records<0){
        return StatusType::INVALID_INPUT;
    }

    m_membersTree.intializeExtra();

    MemberClient** temp_arry;
    try{
        temp_arry = new MemberClient*[m_number_of_members];
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    m_membersTree.getAllDataArry(temp_arry);
    for(int i =0;i<m_number_of_members;i++){
        temp_arry[i]->eraseDebt();
    }
    delete[] temp_arry;

    try{
        m_recordsGroups.init(records_stocks, number_of_records);
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }    
    
    int* temp1;
    int* temp2;

    try{
        temp1 = new int[number_of_records];
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        temp2 = new int[number_of_records];
    }
    catch(...){
        delete temp1;
        return StatusType::ALLOCATION_ERROR;
    }

    for(int i =0; i<number_of_records;i++){
        temp2[i] =0;
        temp1[i] = records_stocks[i];
    }

    if(m_records_stocks){
        delete[] m_records_stocks;
    }
    if(m_records_bought){
        delete[] m_records_bought;
    }

    m_records_stocks = temp1;
    m_records_bought = temp2;
    
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone){
    if(c_id<0 || phone<0){
        return StatusType::INVALID_INPUT;
    }
    
    Client* newClient;
    try{
        newClient = new Client(c_id,phone);        
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }

    if(m_clientsHashTable.find(newClient)){
        delete newClient;
        return StatusType::ALREADY_EXISTS;
    }

    try{
        m_clientsHashTable.insert(newClient);
    }
    catch(...){
        delete newClient;
        return StatusType::ALLOCATION_ERROR;
    }
    m_number_of_clients++;
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id) {
    if(c_id<0){
        return Output_t<int>(StatusType::INVALID_INPUT);
    }

    Client newClient = Client(c_id);

    if(!m_clientsHashTable.find(&newClient)){
        return Output_t<int>(StatusType::DOESNT_EXISTS);
    }

    Client* temp = m_clientsHashTable.getData(&newClient);
    return Output_t<int>(temp->getPhoneNumber());

}

StatusType RecordsCompany::makeMember(int c_id) {
    if(c_id<0){
        return StatusType::INVALID_INPUT;
    }
    Client newClient = Client(c_id);

    if(!m_clientsHashTable.find(&newClient)){
        return StatusType::DOESNT_EXISTS;
    }
    Client* temp = m_clientsHashTable.getData(&newClient);
    
    MemberClient* newMember;
    try{
        newMember = new MemberClient(c_id);
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }

    if(m_membersTree.isVertexExist(newMember)){
        delete newMember;
        return StatusType::ALREADY_EXISTS;
    }

    try{
        m_membersTree.InsertNode(newMember);
    }
    catch(...){
        delete newMember;
        return StatusType::ALLOCATION_ERROR;
    }
    
    temp->setIsMember(true);
    m_number_of_members++;
    return StatusType::SUCCESS;

}

Output_t<bool> RecordsCompany::isMember(int c_id) {
    if(c_id<0){
        return Output_t<bool>(StatusType::INVALID_INPUT);
    }
    Client newClient = Client(c_id);

    if(!m_clientsHashTable.find(&newClient)){
        return Output_t<bool>(StatusType::DOESNT_EXISTS);
    }
    Client* temp = m_clientsHashTable.getData(&newClient);
    return Output_t<bool>(temp->getIsMember());
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if(c_id<0 || r_id<0){
        return StatusType::INVALID_INPUT;
    }
    Client newClient = Client(c_id);

    if(!m_clientsHashTable.find(&newClient) || r_id>=m_number_of_records){
        return StatusType::DOESNT_EXISTS;
    }

    if(isMember(c_id).ans()){
        MemberClient newMemberClient = MemberClient(c_id);
        MemberClient* temp = m_membersTree.getVertex(&newMemberClient);
        temp->increaseDebt(RECORD_PRICE + m_records_bought[r_id]);
    }

    m_records_bought[r_id]++;                        //DONT YOU NEED TO CHECK THAT YOU HAVE ENOUGH REOCRDS ???
    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){

    if(amount<=0 || c_id1 <0 || c_id1> c_id2){
        return StatusType::INVALID_INPUT;
    }

    MemberClient t1 = MemberClient(c_id1-1);
    MemberClient t2 = MemberClient(c_id2-1);
    m_membersTree.addPrize(&t1,&t2,amount);
    return StatusType::SUCCESS;
}


Output_t<double> RecordsCompany::getExpenses(int c_id) {
    if(c_id<0){
        return Output_t<double>(StatusType::INVALID_INPUT);
    }

    Client newClient = Client(c_id);

    if(!m_clientsHashTable.find(&newClient)){
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    double res;
    if(isMember(c_id).ans()){
        MemberClient newMemberClient = MemberClient(c_id);
        MemberClient* temp = m_membersTree.getVertex(&newMemberClient);
        res = (double)(temp->getDebt()) - m_membersTree.find_prize(temp);   
    }
    else{
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    
    return Output_t<double>(res);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if(r_id1 <0 || r_id2<0){
        return StatusType::INVALID_INPUT;
    }
    if(r_id1>=m_number_of_records || r_id2>=m_number_of_records){
        return StatusType::DOESNT_EXISTS;
    }
    int find_r_id1 = m_recordsGroups.Find(r_id1);
    int find_r_id2 = m_recordsGroups.Find(r_id2); 

    if(find_r_id1==find_r_id2 ){
        return StatusType::FAILURE;
    }
    m_recordsGroups.Union(find_r_id1,find_r_id2);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if(r_id <0 || column == nullptr || hight == nullptr ){
        return StatusType::INVALID_INPUT;
    }
    if(r_id>=m_number_of_records){
        return StatusType::DOESNT_EXISTS;
    }
    *column = m_recordsGroups.getColumn(r_id);
    *hight = m_recordsGroups.getHeight(r_id);
    return StatusType::SUCCESS;
}
