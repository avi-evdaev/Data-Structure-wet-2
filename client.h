
#ifndef CLIENT_H
#define CLIENT_H

#include "utilesWet2.h"

class Client {
private:
    int m_id;
    int m_phoneNumber;
    int m_debt;
    bool m_isMember;
public:
    Client(int id, int phone);
    Client(const Client& other) = default;
    Client& operator=(const Client& other) = default;
    ~Client() = default;
    
    int getDebt() const;
    int increaseDebt(int x);
    bool getIsMember() const;
    void setIsMember(bool isMember);
    int getPhoneNumber() const;
    bool getId() const;

    bool operator==(const Client& other){
        return m_id == other.m_id;
    }
};




#endif //CLIENT_H