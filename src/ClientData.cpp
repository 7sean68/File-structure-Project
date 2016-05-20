#include "ClientData.h"

using namespace std;

ClientData::ClientData( int accountNumberValue, int branchIdValue, string lastNameValue, string firstNameValue, double balanceValue ){
    setAccountNumber( accountNumberValue );
    setBranchId(branchIdValue);
    setLastName( lastNameValue );
    setFirstName( firstNameValue );
    setBalance( balanceValue );
}
int ClientData::getAccountNumber() const{
    return accountNumber;
}
void ClientData::setAccountNumber( int accountNumberValue ){
    accountNumber = accountNumberValue;
}
string ClientData::getLastName() const{
    return lastName;
}
void ClientData::setLastName( string lastNameString ){
    lastName = lastNameString;
}
string ClientData::getFirstName() const{
    return firstName;
}
void ClientData::setFirstName( string firstNameString ){
    firstName = firstNameString;
}
double ClientData::getBalance() const{
    return balance;
}
void ClientData::setBalance( double balanceValue ){
    balance = balanceValue;
}
int ClientData::getBranchId() const{
    return branchId;
}
void ClientData::setBranchId( int branchIdValue ){
    branchId = branchIdValue;
}
ostream& operator<<(ostream& out,const ClientData& cd){
    out.write(reinterpret_cast<const char*>("AccNo="), 6);
    out.write(reinterpret_cast<const char*>(&cd.accountNumber), sizeof(int));
    out.write(reinterpret_cast<const char*>("|Brnch="), 7);
    out.write(reinterpret_cast<const char*>(&cd.branchId), sizeof(int));
    out.write(reinterpret_cast<const char*>("|LName="), 7);
    out.write(reinterpret_cast<const char*>(cd.lastName.c_str()), cd.lastName.size());
    out.write(reinterpret_cast<const char*>("|FName="), 7);
    out.write(reinterpret_cast<const char*>(cd.firstName.c_str()), cd.firstName.size());
    out.write(reinterpret_cast<const char*>("|blnce="), 7);
    out.write(reinterpret_cast<const char*>(&cd.balance), sizeof(double));
    out.write(reinterpret_cast<const char*>("|#"), 2);
    return out;
}
istream& operator>>(istream& in,ClientData& cd){
    string s, tmp;
    if(getline(in, s, '#')){
        stringstream ss(s);
        while(getline(ss, tmp, '|')){
            switch(tmp[0]){
            case 'A':
                cd.accountNumber = *reinterpret_cast<int*>(&tmp[6]);break;
            case 'B':
                cd.branchId = *reinterpret_cast<int*>(&tmp[6]);break;
            case 'L':
                cd.lastName = tmp.substr(6);break;
            case 'F':
                cd.firstName = tmp.substr(6);break;
            case 'b':
                cd.balance = *reinterpret_cast<double*>(&tmp[6]);break;
            }
        }
    }
    return in;
}
