#ifndef MEMBER_CLIENT_H
#define MEMBER_CLIENT_H



class MemberClient {
private:
    int m_id;

public:
    MemberClient(int id) : m_id(id){}
    MemberClient(const MemberClient& other) = default;
    MemberClient& operator=(const MemberClient& other) = default;
    ~MemberClient() = default;

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