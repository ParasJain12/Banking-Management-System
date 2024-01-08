#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <process.h>
#include <dos.h>
#include <conio.h>
using namespace std;
class Menus
{
    public:
      void showmenu(void);
    private:
      void closemenu(void);
};
struct date {
    int da_day;
    int da_mon;
    int da_year;
};
class dispRecords
{
    public:
      void addDetails(int, char name[30],char address[60],float);
      void displayCustomers(void);
      void deleteaccount(int);
      void updateBalance(int,float);
      void Updatecustomer(void);
      int lastaccount(void);
      int accountExist(int);
      char *getname(int);
      char *getaddress(int);
      float getbalance(int);
      int getrecord(int);
      void display(int);
      void displaylist(void);
      int accountnumber;
      char name[50],address[50];
      float intbalance;
};
class AccountTransactions
{
    public:
      void newaccount(void);
      void closeaccount(void);
      void displayaccount(void);
      void transaction(void);
      void addDetails(int,int,int,int,char,char typetransaction[15],float,float,float);
      void Deleteaccount(int);
      int datediffer(int,int,int,int,int,int);
      float getinterest(int,float);
      void display(int);
      void showaccount(int);
      int accountnumber,dday,mmonth,yyear;
      char trantype[10];
      char transactions;
      float intinterest,intamount,intbalance;
      static float calcInterset;
      void showInterest(void);
};
void getdate(struct date* dateval) {
    time_t currentTime = time(nullptr);
    struct tm* localTime = localtime(&currentTime);

    // Assign values to dateval
    dateval->da_day = localTime->tm_mday;
    dateval->da_mon = localTime->tm_mon + 1; // Note: tm_mon is 0-based
    dateval->da_year = localTime->tm_year + 1900; // Note: tm_year is years since 1900
}
void Menus :: showmenu(void)
{
    char choice;
    while(1)
    {
        cout << "\n\n***Welcome To My Banking System Application***\n" << endl;
        cout << "Choose from Options" << endl;
        cout << "1. Open an account\n";
        cout << "2. View an account\n";
        cout << "3. Show all accounts\n";
        cout << "4. Make a transaction\n";
        cout << "5. Calculate Interest\n";
        cout << "6. Close an account\n";
        cout << "7. Exit\n";
        cout << "Please select a choice\n";
        //cin >> choice;
        choice = getche();
        if(choice == '1')
        {
            AccountTransactions objAT;
            objAT.newaccount();
        }
        else if(choice == '2')
        {
            AccountTransactions objAT;
            objAT.displayaccount();
        }
        else if(choice == '3')
        {
            dispRecords newRec;
            newRec.displayCustomers();
        }
        else if(choice == '4')
        {
            AccountTransactions objAT;
            objAT.transaction();
        }
        else if(choice == '5')
        {
            AccountTransactions objAT;
            objAT.showInterest();
        }
        else if(choice == '6')
        {
            closemenu();
        }
        else if(choice == '7')
        {
            cout << "\n Thank for using this application\n";
            cout << "Hope you loved this application\n";
            getch();
            break;
        }
    }
}
void Menus :: closemenu(void)
{
    char choice;
    while(1)
    {
        cout << "***Close Menu***" << endl;
        cout << "1. Close or Delete an account\n";
        cout << "0. Exit from this\n" << endl;
        cout << "Select from above choice\n";
        //cin >> choice;
        choice = getche();
        if(choice == '1')
        {
            AccountTransactions at;
            at.closeaccount();
            break;
        }
        else if(choice == '0')
        {
            cout << "Exit from this menu\n\n";
            getch();
            break;
        }
    }
}
int dispRecords :: lastaccount(void)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        count = accountnumber;
    }
    filename.close();
    return count;
}
int dispRecords :: getrecord(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        count++;
        if(retrieveAccNo == accountnumber)
        {
            break;
        }
    }
    filename.close();
    return count;
}
void dispRecords :: display(int retrieveAccNo)
{
    int record;
    record = getrecord(retrieveAccNo);
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::end);
    int location;
    location = (record) * sizeof(dispRecords);
    filename.seekp(location);
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        if(retrieveAccNo == accountnumber)
        {
            cout << "\n Account No.: " << accountnumber;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Balance: " << intbalance;
            break;
        }
    }
    filename.close();
}
char *dispRecords :: getname(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    char retrieveCustName[40];
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        if(accountnumber == retrieveAccNo)
        {
            strcpy(retrieveCustName,name);
        }
    }
    filename.close();
    return retrieveCustName;
}
char *dispRecords :: getaddress(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    char retrieveAddress[80];
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        if(accountnumber == retrieveAccNo)
        {
            strcpy(retrieveAddress,address);
        }
    }
    filename.close();
    return retrieveAddress;
}
float dispRecords :: getbalance(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    float iBalance;
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        if(accountnumber == retrieveAccNo)
        {
            iBalance = intbalance;
        }
    }
    filename.close();
    return iBalance;
}
int dispRecords :: accountExist(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    filename.seekg(0,ios::beg);
    int count=0;
    while(filename.read((char *)this,sizeof(dispRecords)))
    {
        if(accountnumber == retrieveAccNo)
        {
            count = 1;
            break;
        }
    }
    filename.close();
    return count;
}
void dispRecords :: displaylist()
{
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    cout << "\n Date: " << day1 << "/" << month1 << "/" << year1 << "\n";
    cout << setw(80) << "________________________________________";
    cout << setw(23) << "Account No.";
    cout << setw(23) << "Name of Person";
    cout << setw(23) << "Balance\n";
    cout << setw(80) << "________________________________________";
}
void dispRecords :: displayCustomers()
{
    int len1;
    int row=8,check;
    fstream filename;
    FILE *pFile;
    pFile = fopen("newrecords.dat","r");
    if(pFile == NULL)
    {
        cout << "\nAccount does not exists\n";
        getch();
        return;
    }
    else
    {
        displaylist();
        filename.open("newrecords.dat",ios::in);
        filename.seekg(0,ios::beg);
        while(filename.read((char *)this,sizeof(dispRecords)))
        {
            check=0;
            cout.fill(' ');
            cout << setw(20);
            cout.setf(ios::right,ios::adjustfield);
            cout << accountnumber;
            cout.fill(' ');
            cout << setw(25);
            cout.setf(ios::internal,ios::adjustfield);
            cout << name;
            cout << setw(23);
            cout.setf(ios::right,ios::adjustfield);
            cout << intbalance << "\n";
            row++;
            if(row == 23)
            {
                check = 1;
                row = 8;
                cout << "\n\nContinue the Application\n";
                getch();
                displaylist();
            }
        }
    }
    filename.close();
    if(!check)
    {
        cout << "\n\nContinue the application\n";
        getch();
    }
}
void dispRecords :: addDetails(int retrieveAccNo,char retrieveCustName[40],char retrieveAddress[80],float iBalance)
{
    accountnumber = retrieveAccNo;
    strcpy(name,retrieveCustName);
    strcpy(address,retrieveAddress);
    intbalance = iBalance;
    fstream filename;
    filename.open("newrecords.dat",ios::out | ios::app);
    filename.write((char *)this,sizeof(dispRecords));
    filename.close();
}
void dispRecords :: deleteaccount(int retrieveAccNo)
{
    fstream filename;
    filename.open("newrecords.dat",ios::in);
    fstream temp;
    temp.open("calculations.txt",ios::out);
    filename.seekg(0,ios::beg);
    while(!filename.eof())
    {
        filename.read((char *)this,sizeof(dispRecords));
        if(filename.eof())
        {
            break;
        }
        if(accountnumber != retrieveAccNo)
        {
            temp.write((char *)this,sizeof(dispRecords));
        }
    }
    filename.close();
    temp.close();
    filename.open("newrecords.dat",ios::out);
    temp.open("calculations.txt",ios::in);
    temp.seekg(0,ios::beg);
    while(!temp.eof())
    {
        temp.read((char *)this,sizeof(dispRecords));
        if(temp.eof())
        {
            break;
        }
        filename.write((char *)this,sizeof(dispRecords));
    }
    filename.close();
    temp.close();
}
void dispRecords :: updateBalance(int retrieveAccNo,float iBalance)
{
    int record;
    record = getrecord(retrieveAccNo);
    fstream filename;
    filename.open("newrecords.dat",ios::out | ios::ate);
    intbalance = iBalance;
    int location;
    location = (record-1) * sizeof(dispRecords);
    filename.seekp(location);
    filename.write((char *)this,sizeof(dispRecords));
    filename.close();
}
void AccountTransactions :: addDetails(int retrieveAccNo,int day1,int month1,int year1,char t_tran,char typetransaction[15],float interest_accured,float t_amount,float iBalance)
{
    fstream filename;
    filename.open("transactions.dat",ios::app);
    accountnumber = retrieveAccNo;
    dday = day1;
    mmonth = month1;
    yyear = year1;
    transactions = t_tran;
    strcpy(trantype,typetransaction);
    intinterest = interest_accured;
    intamount = t_amount;
    intbalance = iBalance;
    filename.write((char *)this,sizeof(AccountTransactions));
    filename.close();
}
void AccountTransactions :: Deleteaccount(int retrieveAccNo)
{
    fstream filename;
    filename.open("transactions.dat",ios::in);
    fstream temp;
    temp.open("calculations.txt",ios::out);
    filename.seekg(0,ios::beg);
    while(!filename.eof())
    {
        filename.read((char *)this,sizeof(AccountTransactions));
        if(filename.eof())
        {
            break;
        }
        if(accountnumber != retrieveAccNo)
        {
            temp.write((char *)this,sizeof(AccountTransactions));
        }
    }
    filename.close();
    temp.close();
    filename.open("transactions.dat",ios::out);
    temp.open("calculations.txt",ios::in);
    temp.seekg(0,ios::beg);
    while(!temp.eof())
    {
        temp.read((char *)this,sizeof(AccountTransactions));
        if(temp.eof())
        {
            break;
        }
        filename.write((char *)this,sizeof(AccountTransactions));
    }
    filename.close();
    temp.close();
}
void AccountTransactions :: newaccount(){
    char choice;
    int i,check;
    dispRecords newRec;
    cout << "Press 0 to go back previous\n";
    cout << "\n Open a bank account\n";
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    int retrieveAccNo;
    retrieveAccNo = newRec.lastaccount();
    retrieveAccNo++;
    if(retrieveAccNo == 1)
    {
        newRec.addDetails(retrieveAccNo,"Aman","Gupta",1.1);
        newRec.deleteaccount(retrieveAccNo);
        addDetails(retrieveAccNo,1,1,2000,'D',"default value",1.1,1.1,1.1);
        Deleteaccount(retrieveAccNo);
    }
    char retrieveCustName[40],tran_acc[10],retrieveAddress[80];
    float t_bal,iBalance;
    cout << "Date: " << day1 << "/" << month1 << "/" << year1 << "\n";
    cout << "Account No.: " << retrieveAccNo;
    do
    {
        cout << "\n Please enter name of account holder: ";
        check=1;
        gets(retrieveCustName);
        if(retrieveCustName[0] == '0')
        {
            cout << "\n\t Invalid Customer name";
            getch();
            return;
        }
        strupr(retrieveCustName);
        if(strlen(retrieveCustName) == 0 || strlen(retrieveCustName) > 40)
        {
            check = 0;
            cout << "\n\tCustomer name is empty or length greater than 40 charcter";
            getch();
        }
    }while(!check);
    do
    {
        cout << "\n Please enter address of account holder: ";
        check=1;
        gets(retrieveAddress);
        if(retrieveAddress[0] == '0')
        {
            cout << "\n\t Invalid Customer address";
            getch();
            return;
        }
        strupr(retrieveAddress);
        if(strlen(retrieveAddress) < 1 || strlen(retrieveAddress) > 80)
        {
            check = 0;
            cout << "\n\tCustomer address is empty or length greater than 80 charcter";
            getch();
        }
    }while(!check);
    do
    {
        char chr_verifyingPerson[40];
        cout << "\n Please enter name of the verifying person of the account holder: ";
        check=1;
        gets(chr_verifyingPerson);
        if(chr_verifyingPerson[0] == '0')
        {
            cout << "\n\t Invalid Verifying person name";
            getch();
            return;
        }
        strupr(chr_verifyingPerson);
        if(strlen(chr_verifyingPerson) < 1 || strlen(chr_verifyingPerson) > 40)
        {
            check = 0;
            cout << "\n\tVerifying person name is empty or length greater than 40 charcter";
            getch();
        }
    }while(!check);
    do
    {
        cout << "\n Please enter deposit amount while opening an account: ";
        check = 1;
        gets(tran_acc);
        t_bal = atof(tran_acc);
        iBalance = t_bal;
        if(strlen(tran_acc) < 1)
        {
            cout << "\n Invalid Transaction value";
            getch();
            return;
        }
        if(iBalance < 1000)
        {
            check = 0;
            cout << "\n\tMinimum deposit amount should be Rs.1000";
            getch();
        }
    }while(!check);
    do
    {
        cout << "\n Do you want to save the record(y/n): ";
        //cin >> choice;
        choice = getche();
        choice = toupper(choice);
    }while(choice != 'N' && choice != 'Y');
    if(choice == 'N' || choice == 'n')
    {
        cout << "\n\t Customer Account is not created";
        getch();
        return;
    }
    float t_amount,interest_accured;
    t_amount = iBalance;
    interest_accured = 0.0;
    char t_tran,typetransaction[10];
    t_tran = 'D';
    strcpy(typetransaction," ");
    newRec.addDetails(retrieveAccNo,retrieveCustName,retrieveAddress,iBalance);
    addDetails(retrieveAccNo,day1,month1,year1,t_tran,typetransaction,interest_accured,t_amount,iBalance);
    cout << "\n\t New account is successfully created";
    getch();
}
void AccountTransactions :: showaccount(int retrieveAccNo)
{
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    cout << "Date: " << day1 << "/" << month1 << "/" << year1 << "\n";
    cout << "Account No.: " << retrieveAccNo;
    dispRecords newRec;
    char retrieveCustName[40];
    strcpy(retrieveCustName,newRec.getname(retrieveAccNo));
    char retrieveAddress[80];
    strcpy(retrieveAddress,newRec.getaddress(retrieveAccNo));
    cout << setw(25) << "\nAccount Holder name: " << retrieveCustName;
    cout << "\n Address: " << retrieveAddress;
    cout << setw(80) << "\n_______________________\n";
    cout << setw(10) << "Dated";
    cout << setw(12) << "Details";
    cout << setw(12) << "Deposited";
    cout << setw(15) << "Withdrawn";
    cout << setw(12) << "         ";
    cout << setw(10) << "Balance";
    cout << setw(80) << "\n________________________\n";
}
void AccountTransactions :: displayaccount()
{
    char t_acc[10];
    int tran_acc,retrieveAccNo;
    dispRecords obj2;
    cout << "Press 0 to go back\n";
    cout << "Please enter account number you want to view: \n";
    gets(t_acc);
    tran_acc = atoi(t_acc);
    retrieveAccNo = tran_acc;
    if(retrieveAccNo == 0)
    {
        cout << "You have pressed 0 to exit\n";
        getch();
        return;
    }
    dispRecords newRec;
    AccountTransactions aa;
    int row=8,check;
    fstream filename;
    FILE *pFile;
    pFile = fopen("newrecords.dat","r");
    if(pFile == NULL)
    {
        cout << "\n No such account exist. Create a new Account\n";
        getch();
        return;
    }
    else if(!newRec.accountExist(retrieveAccNo))
    {
        cout << "\t\n Account does not exists";
        getch();
        return;
    }
    else
    {
        showaccount(retrieveAccNo);
        filename.open("transactions.dat",ios::in);
        while(filename.read((char *)this,sizeof(AccountTransactions)))
        {
            if(accountnumber  == retrieveAccNo){
                check = 0;
                cout << setw(3) << dday << "/" << mmonth << "/" << yyear;
                cout << setw(10) << trantype;
                if(transactions == 'D')
                {
                    cout.setf(ios::right,ios::adjustfield);
                    cout << setw(15);
                    cout << intamount;
                    cout << setw(20);
                    cout << " ";
                }
                else
                {
                    cout.setf(ios::right,ios::adjustfield);
                    cout << setw(25);
                    cout << intamount;
                    cout << setw(20);
                    cout << "  ";
                }
                cout << setw(15);
                cout.setf(ios::right,ios::adjustfield);
                cout << intbalance << "\n";
                row++;
                if(row == 23)
                {
                    check = 1;
                    row = 8;
                    cout << "\n\n Please continue with application";
                    getch();
                    showaccount(retrieveAccNo);
                }
            }
        }
    }
    filename.close();
    if(!check)
    {
        cout << "Press any key to continue\n";
        getch();
    }
}
int AccountTransactions :: datediffer(int day1,int month1,int year1,int day2,int month2,int year2)
{
    static int monthArr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int days = 0;
    while(day1 != day2 || month1 != month2 || year1 != year2)
    {
        days++;
        day1++;
        if(day1 > monthArr[month1-1])
        {
            day1 = 1;
            month1++;
        }
        if(month1 > 12)
        {
            month1 = 1;
            year1++;
        }
    }
    return days;
}
float AccountTransactions :: getinterest(int retrieveAccNo,float iBalance)
{
    fstream filename;
    filename.open("transactions.dat",ios::in);
    dispRecords newRec;
    filename.seekg(0,ios::beg);
    int day1,month1,year1,month_day;
    while(filename.read((char *)this,sizeof(AccountTransactions)))
    {
        if(accountnumber == retrieveAccNo)
        {
            day1 = dday;
            month1 = mmonth;
            year1 = yyear;
            iBalance = newRec.getbalance(retrieveAccNo);
            break;
        }
    }
    int day2,month2,year2;
    struct date dateval;
    getdate(&dateval);
    day2 = dateval.da_day;
    month2 = dateval.da_mon;
    year2 = dateval.da_year;
    float interest_accured = 0.0;
    int yeardiff = year2 - year1;
    if((year2<year1) || (year2==year1 && month2<month1) || (year2==year1 && month2==month1 && day2<day1))
    {
        return interest_accured;
    }
    month_day = datediffer(day1,month1,year1,day2,month2,year2);
    int months;
    if(month_day >= 30)
    {
        months = month_day/30;
    }
    else
    {
        months = month_day/30;
    }
    if(interest_accured == 0 && yeardiff == 1)
    {
        interest_accured = ((iBalance*0.5)/100) * (months);
    }
    else if(yeardiff > 1 && yeardiff < 25 && interest_accured == 0)
    {
        interest_accured = ((iBalance*0.5)/100) * (months);
    }
    else
    {
        interest_accured = 0;
    }
    filename.close();
    return interest_accured;
}
void AccountTransactions :: showInterest(){
    char t_acc[10];
    int tran_acc,retrieveAccNo,check;
    cout << strupr("\n Interest should be generated only once in year\n");
    cout << "\n Press 0 to go back";
    cout << "\nTo view the transaction, please enter it: ";
    gets(t_acc);
    tran_acc = atoi(t_acc);
    retrieveAccNo = tran_acc;
    if(retrieveAccNo == 0)
    {
        return;
    }
    dispRecords newRec;
    if(!newRec.accountExist(retrieveAccNo))
    {
        cout << "\t\n Account does not exist";
        getch();
        return;
    }
    cout << "Press 0 to go back to previous menu";
    cout << "\n Please enter account no. to generate intrerst: \n";
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    cout << "\n Date: " << day1 << "/" << month1 << "/" << year1;
    cout << "\nAccount No.: " << retrieveAccNo;
    char retrieveCustName[40];
    char retrieveAddress[80];
    float iBalance;
    strcpy(retrieveCustName,newRec.getname(retrieveAccNo));
    strcpy(retrieveAddress,newRec.getaddress(retrieveAccNo));
    iBalance = newRec.getbalance(retrieveAccNo);
    cout << "\n Customer name: " << retrieveCustName;
    cout << "\n Customer Address: " << retrieveAddress;
    cout << "\n Bank Balance: " << iBalance;
    float interest_accured;
    interest_accured = getinterest(retrieveAccNo,iBalance);
    cout << "\n Interest Generated: " << interest_accured;
    getch();
    iBalance = iBalance + interest_accured;
    dispRecords obj2;
    obj2.updateBalance(retrieveAccNo,iBalance);
    addDetails(retrieveAccNo,day1,month1,year1,'D',"Interest",interest_accured,interest_accured,iBalance);
}
void AccountTransactions :: transaction()
{
    char t_acc[10];
    int tran_acc,retrieveAccNo,check;
    cout << "\n Press 0 to go back";
    cout << "\nTo view the transaction, please enter it: ";
    gets(t_acc);
    tran_acc = atoi(t_acc);
    retrieveAccNo = tran_acc;
    if(retrieveAccNo == 0)
    {
        return;
    }
    dispRecords newRec;
    if(!newRec.accountExist(retrieveAccNo))
    {
        cout << "\t\n Account does not exist";
        getch();
        return;
    }
    cout << "Press 0 to go back to previous menu";
    cout << "\n Make correct entry for the Transaction below: \n";
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    cout << "\n Date: " << day1 << "/" << month1 << "/" << year1;
    cout << "\nAccount No.: " << retrieveAccNo;
    char retrieveCustName[40];
    char retrieveAddress[80];
    float iBalance;
    float interest_accured = 0.0;
    strcpy(retrieveCustName,newRec.getname(retrieveAccNo));
    strcpy(retrieveAddress,newRec.getaddress(retrieveAccNo));
    iBalance = newRec.getbalance(retrieveAccNo);
    cout << "\n Customer name: " << retrieveCustName;
    cout << "\n Customer Address: " << retrieveAddress;
    cout << "\n Bank Balance: " << iBalance;
    char tranDetails,typetransaction[10],tm[10];
    float t_amount,t_amt;
    do
    {
        cout << "\n Please enter D for deposit or W for withdrawal of Amount: ";
        //cin >> tranDetails;
        tranDetails = getche();
        if(tranDetails == '0')
        {
            cout << "\n\t You have pressed to exit";
            getch();
            return;
        }
        tranDetails = toupper(tranDetails);
    }while(tranDetails != 'W' && tranDetails != 'D');
    do
    {
        cout << "\n Transaction type is either cash or cheque";
        check=1;
        cout << " (Cash/Cheque): ";
        gets(typetransaction);
        strupr(typetransaction);
        if(typetransaction[0] == '0')
        {
            cout << "\n\t You have pressed 0 to exit";
            getch();
            return;
        }
        if(strlen(typetransaction) < 1 || strcmp(typetransaction,"CASH") && strcmp(typetransaction,"CHEQUE"))
        {
            check = 0;
            cout << "\nTransaction is invalid. Please enter either CASH or CHEQUE\n";
            getch();
        }
    }while(!check);
    do
    {
        cout << "\n Please enter the amount: ";
        check = 1;
        cout << "\nAmount: Rs. ";
        gets(tm);
        t_amt = atof(tm);
        t_amount = t_amt;
        if(t_amount < 1 || (tranDetails == 'W' && t_amount > iBalance))
        {
            check=0;
            cout << "\n Either amount is not a numeric value or it is a blank or you are tring to withdraw amount more than in account";
            getch();
        }
    }while(!check);
    char choice;
    do
    {
        cout << "\n Save the changes made in transaction details?(y/n)";
        //cin >> choice;
        choice = getche();
        choice = toupper(choice);
    }while(choice != 'N' && choice != 'Y');
    if(choice == 'N' || choice == 'n')
    {
        cout << "\n\t Transaction is not saved";
        getch();
        return;
    }
    if(tranDetails == 'D')
    {
        cout << "\n Amount is deposited in your account";
        getch();
        iBalance = iBalance + t_amount;
    }
    else
    {
        cout << "\n Amount is withdrawn from the Bank";
        getch();
        iBalance = iBalance - t_amount;
    }
    newRec.updateBalance(retrieveAccNo,iBalance);
    addDetails(retrieveAccNo,day1,month1,year1,tranDetails,typetransaction,interest_accured,t_amount,iBalance);
}
void AccountTransactions :: closeaccount()
{
    char t_acc[10];
    int tran_acc,retrieveAccNo;
    cout << "\n Press 0 to go back to previous menu\n";
    cout << "\n Please enter the account you want to close: ";
    gets(t_acc);
    tran_acc = atoi(t_acc);
    retrieveAccNo = tran_acc;
    dispRecords newRec;
    if(!newRec.accountExist(retrieveAccNo))
    {
        cout << "\t\n You have entered an inavlid account or it does not exist\n";
        cout << "\n Please try again";
        getch();
        return;
    }
    cout << "\n Press 0 to go back to previous menu";
    cout << "\n Closing this account";
    int day1,month1,year1;
    struct date dateval;
    getdate(&dateval);
    day1 = dateval.da_day;
    month1 = dateval.da_mon;
    year1 = dateval.da_year;
    cout << "\n Date: " << day1 << "/" << month1 << "/" << year1;
    char choice;
    newRec.display(retrieveAccNo);
    do
    {
        cout << "\n Are you sure you want to close this account?(y/n)";
        //cin >> choice;
        choice = getche();
        choice = toupper(choice);
    }while(choice != 'N' && choice != 'Y');
    if(choice == 'N' || choice == 'n')
    {
        cout << "\n Account is not closed";
        getch();
        return;
    }
    newRec.deleteaccount(retrieveAccNo);
    Deleteaccount(retrieveAccNo);
    cout << "\t\n Record deleted successfully\n";
    cout << " Please continue with the application\n";
    getch();
}
int login()
{
    char username[9],ch;
    char username1[] = "banking";
    int i=0;
    char a,b[9],pass[]="tatahill";
    cout << "\n\n Login to Banking Application\n";
    cout << "\n Please enter the username: ";
    cin >> username;
    cout << "\n Please enter the password: ";
    fflush(stdin);
    do
    {
        ch = getch();
        if(isalnum(ch))
        {
            b[i] = ch;
            cout << "*";
            i++;
        }
        else
        {
            if(ch == '\r')
            {
                b[i] = '\0';
            }
            else if(ch == '\b')
            {
                i--;
                cout << "\b\b";
            }
        }
    }while(ch != '\r');
    b[i] = '\0';
    fflush(stdin);
    if((strcmp(b,pass)==0)&&strcmp(username1,username)==0)
    {
        cout << "\n\n\t You have entered successfully";
        return 1;
    }
    else
    {
        cout << "\t\n\n Incorrect Username or password";
        return 0;
    }
}
int main()
{
    int val,ch;
    a: val = login();
    if(val == 0)
    {
        cout << "\n\t Want to try again?\n";
        cout << "\t 1.Try again";
        cout << "\n\t 2. Exit";
        cout << "\n\n\t Enter your choice";
        cin >> ch;
        if(ch == 1)
        {
            goto a;
        }
        else
        {
            exit(0);
        }
    }
    Menus obj1;
    obj1.showmenu();
}