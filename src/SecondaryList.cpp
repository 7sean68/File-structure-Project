#include "SecondaryList.h"

using namespace std;

SecondaryList::SecondaryList(int x, int y):acNo(x), next(y){}

void SecondaryList::setAcNo(int n){
    acNo = n;
}

int SecondaryList::getAcNo(){
    return acNo;
}

void SecondaryList::setNext(int n){
    next = n;
}

int SecondaryList::getNext(){
    return next;
}

istream& operator>>(istream& secondary, SecondaryList& lst){
    secondary.read(reinterpret_cast<char*>(&lst), sizeof(SecondaryList));
    return secondary;
}

ostream& operator<<(ostream& secondary, SecondaryList& lst){
    secondary.write(reinterpret_cast<char*>(&lst), sizeof(SecondaryList));
    return secondary;
}

