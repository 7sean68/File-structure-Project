#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H
#include <bits/stdc++.h>

using namespace std;

class PrimaryIndex
{
    public:
        PrimaryIndex(int = 0, int = 0);
        void setAccountNumber(int);
        int getAccountNumber();
        void setByte(int);
        int getByte();
        void add(fstream&);
        friend void sft(int, fstream&);
        friend void createPrimary(istream&, ostream&);
        friend int fnd(int, fstream&, bool);
    private:
        int AccountNumber;
        int Byte;

};

#endif // PRIMARYINDEX_H

void createPrimary(istream&, ostream&);

int fnd(int, fstream&, bool = 0);

void sft(int, fstream&);

