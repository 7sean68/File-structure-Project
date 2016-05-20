#ifndef SECONDARYLIST_H
#define SECONDARYLIST_H
#include <bits/stdc++.h>

using namespace std;


class SecondaryList
{
    public:
        SecondaryList(int = 0, int = -1);
        void setAcNo(int);
        int getAcNo();
        void setNext(int);
        int getNext();
        friend istream& operator>>(istream&, SecondaryList&);
        friend ostream& operator<<(ostream&, SecondaryList&);
    private:
        int acNo;
        int next;

};

#endif // SECONDARYLIST_H
