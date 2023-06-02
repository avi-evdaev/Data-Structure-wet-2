#include "client.h"


Client::Client(int id, int phone) : m_id(id), m_phoneNumber(phone), m_debt(0), m_isMember(false) {}

int Client::getDebt() const{
    return m_debt;
}

void Client::increaseDebt(int x) {
    m_debt+=x;
}

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
