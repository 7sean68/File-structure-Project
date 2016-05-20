#include <bits/stdc++.h>
#include "ClientData.h"
#include "SecondaryIndex.h"
#include "PrimaryIndex.h"
#include <windows.h>

using namespace std;

int mxF = 11, mxL = 16;

int enterChoice();
void newRecord(fstream&);
void updateRecord(fstream&);
void deleteRecord(fstream&);
void backUp(fstream&);
void reStore(fstream&);
void createTextFile(fstream&);
void srch(fstream&);
enum Choices { NEW = 1, UPDATE, DEL, PRINT, BACK, RESTORE, SEARCH, END };

int main(){
    int choice;
    fstream inOutCredit("credit.dat", ios::in | ios::out | ios::binary);
    if(!inOutCredit){
        inOutCredit.open("credit.dat", ios::in | ios::out | ios::binary | ios::trunc);
        fstream Pindex("PrimaryIndex.dat", ios::in | ios::out | ios::binary | ios::trunc);
    }
    inOutCredit.seekp(0, inOutCredit.end);
    while ( ( choice = enterChoice() ) != END ){
        switch ( choice ){
            case NEW:
                newRecord(inOutCredit);
                break;
            case UPDATE:
                updateRecord(inOutCredit);
                break;
            case DEL:
                deleteRecord( inOutCredit);
                break;
            case PRINT:
                createTextFile(inOutCredit);
                break;
            case BACK:
                backUp(inOutCredit);
                break;
            case RESTORE:
                reStore(inOutCredit);
                break;
            case SEARCH:
                srch(inOutCredit);
                break;
            default:
                cerr << "Incorrect choice" << endl;
                break;
        }
    }
}
int enterChoice(){
    cout << "1 - add a new account\n2 - update an account\n3 - delete an account\n"
        << "4 - print accounts in \"print.txt\"\n"
        <<"5 - backup data\n6 - restore data\n7 - search by last name\n8 - end program\n? ";
    int menuChoice;
    cin >> menuChoice;
    return menuChoice;
}
void newRecord(fstream & file){
    fstream Pindex("PrimaryIndex.dat", ios::in | ios::out | ios::binary);
    if(!Pindex)Pindex.open("PrimaryIndex.dat", ios::in | ios::out | ios::binary | ios::trunc);
    ClientData c;
    PrimaryIndex p;
    string f,l;
    int bid,accountNumber;
    double b;
    cout <<"Enter new account number greater than 0\n";
    cin >> accountNumber;
    while (accountNumber < 1){
        cout <<"invalid input\n";
        cin >> accountNumber;
    }
    Pindex.clear();
    int x = fnd(accountNumber,Pindex);
    if(x < 0)
    {
        file.clear();
        file.seekp(0, file.end);
        x = file.tellp();
        cout <<"Enter BranchID, last name, first name and balance\n";
        cin >> bid>>l>>f>>b;
        mxF = max((unsigned)mxF, f.size() + 1);
        mxL = max((unsigned)mxL, l.size() + 1);
        c.setAccountNumber(accountNumber);
        c.setBranchId(bid);
        c.setFirstName(f);
        c.setLastName(l);
        c.setBalance(b);
        file << c;
        Pindex.clear();
        p.setAccountNumber(accountNumber);
        p.setByte(x);
        p.add(Pindex);
        file.clear();
    }
    else cout<<"Account is already exist !\n";
    Pindex.close();
}
void updateRecord(fstream & file){
    fstream Pindex("PrimaryIndex.dat", ios::in | ios::binary);
    ClientData c;
    double d;
    int bo,accountNumber;
    cout <<"Enter  account number greater than 0\n";
    cin >> accountNumber;
    bo = fnd(accountNumber,Pindex);
    if(bo >= 0){
        cout << "enter update amount\n";
        cin >> d;
        file.seekg(bo);
        file >> c;
        c.setBalance(c.getBalance()+d);
        file.seekp(bo);
        file << c;
        cout << "Account updated !\n";
    }
    else cout << "Account doesn't exist\n";
    file.clear();
    Pindex.close();
}
void backUp(fstream &readFromFile ){
    ofstream backfile( "backup.dat" , ios::out | ios::trunc | ios::binary);
    string s;
    readFromFile.seekg(0);
    ClientData c;
    while( readFromFile >> c)
        backfile << c;
    backfile.close();
    readFromFile.clear();
}
void reStore(fstream &writeToFile ){
    writeToFile.close();
    writeToFile.open( "credit.dat", ios::in | ios::out | ios::binary | ios::trunc);
    ifstream backfile( "backup.dat" , ios::in | ios::binary);
    if ( !backfile){
        cout << "Backup not found\n";
    }
    else{
        ClientData c;
        while( backfile >> c)
            writeToFile << c;
    }
    backfile.close();
    writeToFile.clear();
    fstream Pindex("PrimaryIndex.dat", ios::in | ios::out | ios::binary | ios::trunc);
    if(!Pindex)Pindex.open("PrimaryIndex.dat", ios::in | ios::out | ios::binary | ios::trunc);
    createPrimary(writeToFile, Pindex);
    writeToFile.clear();
    Pindex.close();
}
void createTextFile( fstream &readFromFile ){
    ofstream outPrintFile( "print.txt", ios::out | ios::trunc );
    ifstream Pindex("PrimaryIndex.dat");
    if( !outPrintFile ){
        cerr << "File could not be created." << endl;
        return;
    }
    outPrintFile << left << setw( 10 ) << "Account" << setw( 10 ) << "BranchID" <<setw( mxL )<< "Last Name" << setw( mxF )
                << "First Name" << right << setw( 10 ) << "Balance" << endl;
    Pindex.seekg(0);
    PrimaryIndex p;
    ClientData client;
    Pindex.read(reinterpret_cast <char*> (&p), sizeof(PrimaryIndex));
    readFromFile.clear();
    while( !Pindex.eof() ){
        if (p.getByte() > -1 ){
            readFromFile.seekg(p.getByte());
            readFromFile >> client;
            outPrintFile  << left << setw( 10 ) << client.getAccountNumber() << setw( 10 ) << client.getBranchId()
                << setw( mxL ) << client.getLastName() << setw( mxF ) << client.getFirstName()
                << setw( 10 ) << setprecision( 2 ) << right << fixed << showpoint << client.getBalance() << endl;
        }
        Pindex.read(reinterpret_cast <char*> (&p), sizeof(PrimaryIndex));
    }
    Pindex.close();
    outPrintFile.close();
    readFromFile.clear();
}
void deleteRecord(fstream & file){
    fstream Pindex("PrimaryIndex.dat", ios::in | ios::out | ios::binary);
    ClientData c;
    string s;
    int bo,accountNumber;
    cout <<"Enter  account number greater than 0\n";
    cin >> accountNumber;
    bo = fnd(accountNumber, Pindex, 1);
    if( bo > -1){
        file.clear();
        file.seekg(bo);
        file >> c ;
        c.setAccountNumber(0);
        file.seekp(bo);
        file << c;
        cout<<"account deleted !\n";
    }
    else cout << "account not found !\n";
    file.clear();
    Pindex.close();
}

void srch(fstream& file){
    file.close();
    fstream sindex, slist;
    FILETIME fc, fp;
    {
        HANDLE h1 = CreateFile("credit.dat", GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL)
        ,h2 = CreateFile("SecondaryList.dat", GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL);
        GetFileTime(h1, NULL, NULL, &fc);
        GetFileTime(h2, NULL, NULL, &fp);
        CloseHandle(h1);
        CloseHandle(h2);
    }
    file.open("credit.dat", ios::in | ios::out | ios::binary);
    if(CompareFileTime(&fc, &fp) > -1){
        sindex.open("SecondaryIndex.dat", ios::in | ios::out | ios::binary | ios::trunc);
        slist.open("SecondaryList.dat", ios::in | ios::out | ios::binary | ios::trunc);
        createSecodary(file, slist, sindex);
    }else{
        sindex.open("SecondaryIndex.dat", ios::in | ios::binary);
        slist.open("SecondaryList.dat", ios::in | ios::binary);
    }

    cout << "enter last name: ";
    string s;
    cin >> s;
    SecondaryIndex si(s);
    SecondaryList sl;
    int x = si.fnd(sindex);
    if(x < 0)cout << "Not found!\n";
    while(x > -1){
        slist.seekg(x);
        slist >> sl;
        cout << sl.getAcNo() << ' ';
        x = sl.getNext();
    }
    cout << '\n';
}
