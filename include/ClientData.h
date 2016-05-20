#ifndef CLIENTDATA_H
#define CLIENTDATA_H
#include <bits/stdc++.h>

using namespace std;
class ClientData {
    public:
        ClientData( int = 0, int = 0, string = "", string = "", double = 0.0 );
        void setAccountNumber( int );
        int getAccountNumber() const;
        void setLastName( string );
        string getLastName() const;
        void setFirstName( string );
        string getFirstName() const;
        void setBalance( double );
        double getBalance() const;
        void setBranchId(int);
        int getBranchId() const;
        friend ostream& operator<<(ostream&,const ClientData&);
        friend istream& operator>>(istream&,ClientData&);
    private:
        int accountNumber;
        int branchId;
        string lastName;
        string firstName;
        double balance;
    };
#endif
