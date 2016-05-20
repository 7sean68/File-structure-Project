#include "SecondaryIndex.h"

using namespace std;

SecondaryIndex::SecondaryIndex(string s)
{
    first = -1;
    setlName(s);
}

void SecondaryIndex::setlName(string s){
    memset(lName, 0, sizeof(lName));
    s.copy(lName, min(15u, s.size()));
}

string SecondaryIndex::getlName(){
    return lName;
}

void SecondaryIndex::setFirst(int i){
    first = i;
}

int SecondaryIndex::getFirst(){
    return first;
}

int SecondaryIndex::fnd(istream &secondary){
    secondary.seekg(0, secondary.end);
    int l = 0, h = (secondary.tellg()) / sizeof(SecondaryIndex) - 1, cr;
    SecondaryIndex s;
    while(l <= h){
        cr = (l + h) / 2;
        secondary.seekg(cr * sizeof(SecondaryIndex));
        secondary.read(reinterpret_cast<char*>(&s), sizeof(SecondaryIndex));
        if(string(s.lName) < string(lName))l = cr + 1;
        else if(string(s.lName) > string(lName))h = cr - 1;
        else return (s.first == -1? -(cr + 1) * sizeof(SecondaryIndex): s.first);
    }
    return -(h + 2) * sizeof(SecondaryIndex);
}
void createSecodary(istream& read, ostream& lst, ostream& secondary){
    int byte = 0;
    string s;
    map<string,int> mymap;
    SecondaryList sl;
    ClientData client;
    SecondaryIndex sec;
    read.clear();
    read.seekg(0);
    secondary.seekp(0);
    read >> client;
    lst.seekp(0, lst.end);
    while(!read.eof()){
        if(client.getAccountNumber()){
            s = client.getLastName().substr(0, min(15u, client.getLastName().size()));
            byte = lst.tellp();
            sl.setAcNo(client.getAccountNumber());
            sl.setNext(mymap[s] - 1);
            mymap[s] = byte + 1;
            lst << sl;
        }
        read >> client;
    }
    for(map<string,int>::iterator it = mymap.begin(); it != mymap.end(); it++){
        sec.setlName(it->first);
        sec.first = it->second - 1;
        secondary.write(reinterpret_cast<char*>(&sec), sizeof(SecondaryIndex));
    }
}
