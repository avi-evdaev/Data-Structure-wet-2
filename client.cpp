#include "client.h"


Client::Client(int id, int phone) : m_id(id), m_phoneNumber(phone), m_isMember(false) {}


bool Client::getIsMember() const {
    return m_isMember;
}

void Client::setIsMember(bool isMember){
    m_isMember=isMember;
}

int Client::getPhoneNumber() const {
    return m_phoneNumber;
}

int Client::getId() const{
    return m_id;
}
