#include "ClientData.h"
#include "PrimaryIndex.h"

using namespace std;

PrimaryIndex::PrimaryIndex(int x, int y):AccountNumber(x), Byte(y)
{
    //ctor
}

void PrimaryIndex::setAccountNumber(int n){
    AccountNumber = n;
}

int PrimaryIndex::getAccountNumber(){
    return AccountNumber;
}

void PrimaryIndex::setByte(int n){
    Byte = n;
}

int PrimaryIndex::getByte(){
    return Byte;
}

void PrimaryIndex::add(fstream& primary){
    int x = fnd(AccountNumber, primary);
    if(x < 0){
        x = -(x + sizeof(PrimaryIndex));
        primary.clear();
        primary.seekg(x);
        PrimaryIndex m(0, -5);
        primary.read(reinterpret_cast<char*>(&m), sizeof(PrimaryIndex));
        primary.clear();
        if(m.Byte > -1)sft(x, primary);
        primary.clear();
        primary.seekp(x);
        primary.write(reinterpret_cast<char*>(this), sizeof(PrimaryIndex));
    }
}

void createPrimary(istream& read, ostream& primary){
    int number,byte = 0;
    map<int,int> mymap;
    PrimaryIndex p;
    ClientData client;
    read.clear();
    read.seekg(0);
    primary.seekp(0);
    if(read.eof())return;
    read >> client;
    while(!read.eof()){
        if(number = client.getAccountNumber()){
            mymap[number] = byte;
            byte = read.tellg();
        }
        read >> client;
    }
    for(map<int,int>::iterator it = mymap.begin(); it != mymap.end(); it++){
        p.AccountNumber = it->first;
        p.Byte = it->second;
        primary.write(reinterpret_cast<char*>(&p), sizeof(PrimaryIndex));
    }
}

void sft(int off, fstream& primary){
    PrimaryIndex p, r;
    primary.seekg(off);
    primary.seekp(off);
    primary.clear();
    primary.read(reinterpret_cast<char*>(&r), sizeof(PrimaryIndex));
        while(!primary.eof() && r.Byte + 1){
            off += sizeof(PrimaryIndex);
            p = r;
            primary.seekg(off);
            primary.read(reinterpret_cast<char*>(&r), sizeof(PrimaryIndex));
            primary.seekp(off);
            if(primary.eof()){
                primary.clear();
                primary.write(reinterpret_cast<char*>(&p), sizeof(PrimaryIndex));
                break;
            }
            primary.write(reinterpret_cast<char*>(&p), sizeof(PrimaryIndex));
        }
        primary.clear();
}

int fnd(int x, fstream& primary, bool b){
    primary.seekg(0, primary.end);
    primary.clear();
    int l = 0, h = (primary.tellg()) / sizeof(PrimaryIndex) - 1, cr;
    PrimaryIndex p;
    while(l <= h){
        cr = (l + h) / 2;
        primary.seekg(cr * sizeof(PrimaryIndex));
        primary.read(reinterpret_cast<char*>(&p), sizeof(PrimaryIndex));
        if(p.AccountNumber < x)l = cr + 1;
        else if(p.AccountNumber > x)h = cr - 1;
        else if(b){
            primary.clear();
            int x = p.Byte;
            p.Byte = -1;
            primary.seekp(cr * sizeof(PrimaryIndex));
            primary.write(reinterpret_cast<char*>(&p), sizeof(PrimaryIndex));
            return x;
        }else return (p.Byte == -1? -(cr + 1) * sizeof(PrimaryIndex): p.Byte);
    }
    return -(h + 2) * sizeof(PrimaryIndex);
}
