#ifndef MEMBER_CLIENT_H
#define MEMBER_CLIENT_H



class MemberClient {
private:
    int m_id;
    int m_debt;

public:
    MemberClient(int id) : m_id(id), m_debt(0) {}
    MemberClient(const MemberClient& other) = default;
    MemberClient& operator=(const MemberClient& other) = default;
    ~MemberClient() = default;

    // void increaseDebt(int x);
    // void eraseDebt();
    // int getDebt() const

    void increaseDebt(int x) {
        m_debt+=x;
    }

    void eraseDebt(){
        m_debt=0;
    }

    int getDebt() const{
    return m_debt;
}


    bool operator<(const MemberClient& other) const {
        return m_id<other.m_id;
    }

    bool operator>(const MemberClient& other) const {
        return m_id>other.m_id;
    }
    bool operator==(const MemberClient& other) const {
        return m_id==other.m_id;
    }
};

#endif