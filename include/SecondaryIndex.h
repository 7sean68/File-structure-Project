#ifndef SECONDARYINDEX_H
#define SECONDARYINDEX_H
#include "ClientData.h"
#include "SecondaryList.h"

using namespace std;

class SecondaryIndex
{
    public:
        SecondaryIndex(string = "");
        void setlName(string);
        string getlName();
        void setFirst(int);
        int getFirst();
        int fnd(istream&);
        friend void createSecodary(istream&, ostream&, ostream&);
    private:
        char lName[15];
        int first;

};

#endif // SECONDARYINDEX_H
void createSecodary(istream&, ostream&, ostream&);
