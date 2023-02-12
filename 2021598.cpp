/* 
CS-Project
Shehryar Ahmad (2021598)
Hamza Ahmad Zuberi (2021193)


Username For Teacher = Teacher
Password For Teacher = Password123

*/
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<stdlib.h>

using namespace std;

int tcheck(bool t)    //Function to check the Passoword
{
    cout << "< < < < Welcome Teacher > > > > \n";
    int attempts=0;
    string username={"Teacher"}, password={"Password123"};
    string Username,Password;

    while (attempts < 3)
    {
        cout << "Enter Username: ";
        cin >> Username;
        cout << "Enter passoword: ";
        cin >> Password;
        
        if (Username != username || Password != password)
        {
            
            cout<<"Incorrect username or password, try again.";
            cout<<"\nAttempts remaining: "<<3-attempts <<"\n";
            attempts++;
        }
        else
        {
            cout << "Access Granted";
            cout << "\nWelcome Teacher";
            return t = true;
            break;
            
        }
    }
    if(attempts==3)
    {
        cout<<"\nOut of attempts";
        cout << "\nAccess Denied";
        return t = false;
    }

}

void AddUser(string regNos[],string names[],string NBooks[],int index)     //Function to Add a New User To the library.
{
    string nreg, nname,nbook;
    bool found = false;
    cout<<"\nEnter Reg# :";
    cin>>nreg;
    while(stoi(nreg)<100 || stoi(nreg)>999)
    {
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin >> nreg;
    }
    cout<<"\nEnter Name: ";
    cin.ignore();
    getline(cin,nname);
    for(int i = 0; i<index;i++)
    {
        if(nreg == regNos[i]){
            cout<<"\nUser Exists."<<endl;
            found = true;
            break;
            }
    }
    if(!found)
    {
        fstream File;
        File.open("Users.txt", ios::app);
        regNos[index] = nreg;
        names[index] = nname;
        NBooks[index] = nbook;
        File<<endl<<regNos[index]<<","<<names[index]<<","<<NBooks[index];
        File.close();
        cout<<"\nNew User Added!\n";
    }
}

void IssueBook(string regnos[], string sname[], string BooksLoaned[], string booknames[], string NoOfCopies[], int p, int q)   //Function to Issue a Book to a user.
{
    string reg, bookn;
    int i, Lbooks,nCopies;

    cout<<"\nEnter Reg# of the user who wants to issue a book: ";
    cin>>reg;

    while(stoi(reg)<100 || stoi(reg)>999){
        cout<<"\nReg# must be of 3 digits. Enter again: ";
        cin>>reg;
    }

    for(i = 0; i<p; i++){
        if(reg == regnos[i])
        {
            break;
        }
    }
    if(BooksLoaned[i] == "3")
    {
        cout<<"\nUser Has Max Books!";

    }
    else if(BooksLoaned[i] >="0" && BooksLoaned[i] < "3")
    {
        cout<<"\nEnter Name of the Book: ";
        cin.ignore();
        getline(cin,bookn);    

        bool found = false;
        while(found == false){
            for(int k = 0; k<q;k++){
                if(bookn == booknames[k])
                found = true;
            }
            if(found==false){
            cout<<"\nBook Not Found! ";
            break;
            }
        }
        int j;
        for(j = 0; j<q;j++){
            if(bookn == booknames[j])
                break;
        }
        if(NoOfCopies[j] > "0"){
        cout<<"\nBook Issued Successfully To:  "<<sname[i];
        nCopies = stoi(NoOfCopies[j]) - 1;
        NoOfCopies[j] = to_string(nCopies);
        Lbooks = stoi(BooksLoaned[i]) + 1;
        BooksLoaned[i] = to_string(Lbooks);
        fstream userfile;
        userfile.open("Users.txt", ios::out);
            for(int k = 0; k<p; k++){
                userfile<<regnos[k]<<","<<sname[k]<<","<<BooksLoaned[k];
                if (k<p-1)
                {
                    userfile << endl;
                }
            }

        userfile.close();

        fstream bookfile;
        bookfile.open("Books.txt", ios::out);
        for(int z = 0; z<q;z++){
                bookfile<<booknames[z]<<","<<NoOfCopies[z];
                if(z<q-1)
                    bookfile<<endl;
        }
        bookfile.close();
        }
        else{
            cout<<"\nBook NOT Available!";
        }

    }
}

void ReturnBook(string regnos[],string stdName[] ,string booknames[],string nBooksloaned[],string bookcopies[],int Ssize,int booksize)   //Function to return an issued Book Back 
{
    string reg, currentNBooks, bookn;

    string CurrentNBooks;
    for(int i = 0; i <Ssize; i++){
        if(reg == regnos[i]){
            CurrentNBooks = nBooksloaned[i];

            break;
        }
    }
    cout<<"\nEnter Reg# (Last Three Digits): ";
    cin>>reg;
    while(stoi(reg)<100 || stoi(reg)>999){         //Check for Reg# to be in range.
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>reg;
    }
    if(currentNBooks != "0"){
        cout<<"\nEnter Name of the Book (To be returned)\n----> ";
        cin.ignore();
        getline(cin, bookn);

        bool found = false;
        while(found == false){
            for(int k = 0; k<booksize;k++){
                if(bookn == booknames[k])
                found = true;
            }
            if(found==false){
            cout<<"\nNo Book Found! \nPlease Re-enter the name of the book: ";
            getline(cin, bookn);
            }
        }
        int i = 0;
        for(i = 0; i<booksize;i++){
            if(bookn == booknames[i])
            break;
        }
        int UpdatedNBooks = stoi(bookcopies[i]) + 1;
        bookcopies[i] = to_string(UpdatedNBooks);
        fstream booksfile;
        booksfile.open("Books.txt", ios::out);
        for(int k = 0; k<booksize; k++){
            booksfile<<booknames[k]<<","<<bookcopies[k];
            if(k<booksize-1)
            booksfile<<endl;
        }
        booksfile.close();

        int j;
        for(j = 0; j<Ssize; j++)
        {
            if(reg == regnos[j])
            break;
        }
        int Lbooks = stoi(nBooksloaned[j]) - 1;
        nBooksloaned[j] = to_string(Lbooks); 
        fstream usersfile;
        usersfile.open("Users.txt", ios::out);
        for(int k = 0; k<Ssize;k++){
            usersfile<<regnos[k]<<","<<stdName[k]<<","<<nBooksloaned[k];
            if(k<Ssize-1)
            usersfile<<endl;
        }
        usersfile.close();
        cout<<"\nBook Returned!\n";    
    }
}

void DisplayBooks(string bookname[], string BookCopies[], int index) //Function to Show the File of Books
{
    cout<<"\nName of books:\n";
    for(int i = 0; i<index;i++)
    {
        cout<< bookname[i]<< "           Available = " << BookCopies[i]<< endl;
    }
}

void UsersSorted(string sname[],string NBooksLoaned[], int size)   //Function to Show Sorted Users 
{
    int i;
    string temp;
    for(int i = size; i>0; i--){
        for(int j = 0; j<i; j++){
            if(sname[j] > sname[j+1]){
                temp = sname[j];
                sname[j] = sname[j+1];
                sname[j+1] = temp;
            }
        }
    }
    cout<<endl<<"*****Current Users in File*****\n";
    for(int i = 0; i <=size; i++){
        cout<< sname[i];
    }
}

void UserBooks(string sname[], string NBooks[], int size)   //Function to Show Users And the Books they issued.
{
    for(int i = 0; i <=size-1; i++)
    {
        cout<< sname[i]<< "     Books issued: " << NBooks[i] <<  endl;
    }
}

void OBooks(string regn[],string sname[], string NBooksLoaned[], int size) //Function to Show Books from file and the available copies.
{
    string reg;
    cout<<"\nEnter Reg# (Last Three digits) to check Details: ";
    cin>>reg; 
    while(stoi(reg)<100 || stoi(reg)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>reg;
    }
    cout<<"\nIssued Books:\n";
    for(int i = 0; i<size; i++){
        if(reg == regn[i]){
            cout<<"\n  Reg# : "<<regn[i]<<"\n  Name: "<<sname[i]<<"\n Issued Books: "<<NBooksLoaned[i]<<endl;
            break;
        }
    }

}

void DeleteUser(string regn[], string sname[], string booksloaned[], string booknames[], string NoOfcopies[], int studentsize, int booksize)  //Funtion to Delete A user from Library
{

    string reg, currentNBooks;
    cout<<"\nEnter Reg# of the student you want to Delete: ";  //check function for valid reg no
    cin>>reg;  

    while(stoi(reg)<100 || stoi(reg)>999){
        cout<<"\nEnter Reg# (Last three digits) ";
        cin>>reg;
    }                          
        int i;
        for(i = 0; i <studentsize; i++){
        if(reg == regn[i]){
            break;
        }
        }
        int j;
        for(j = i;j<=studentsize-1;j++){
            regn[j] = regn[j+1];
            sname[j] = sname[j+1];
            booksloaned[j] = booksloaned[j+1];
        }
        fstream usersfile;
        usersfile.open("Users.txt", ios::out);
        for(int i = 0; i<studentsize-1;i++){
            
            usersfile<<regn[i]<<","<<sname[i]<<","<<booksloaned[i];
            if(i<studentsize-2)
            usersfile<<endl;
        }
        usersfile.close();
        cout<<"\nUSER DELETED!\n";
        
}

int main()
{
    string regNos[10] , names[10];    //A total of 10 Students.
    string uALL[10];
    string BookName[6], BookCopies[9], NBooks[10];;    //A total of 54 Books in the library.
    string bALL[10];        
    int i = 0;
    int j=0;               
    bool UserExists;
    fstream File;
    File.open("Users.txt",ios::in);
    if(!File)
        cout << "File1 not opened!"<<endl;
    else
        
    while(!File.eof()){
        getline(File,uALL[i],'\n');
        regNos[i] = (uALL[i].substr(0,3));
        names[i] = uALL[i].substr(4,uALL[i].length()-6);
        NBooks[i] = (uALL[i].substr(uALL[i].length()-1,1));
        i++;
    }
    File.close();

    ifstream BFile("Books.txt");
    if(!BFile)
        cout << "File2 Not opened"<<endl;
    else
    while(!BFile.eof())
    {
        getline(BFile, bALL[j],'\n');
        BookName[j] = bALL[j].substr(0,bALL[j].length()-2);
        BookCopies[j] = bALL[j].substr(bALL[j].length()-1,1);
        j++;   
    }
    BFile.close();
    
    cout << "******L I B R A R Y M A N A G E M E N T S Y S T E M******\n";
    cout << "                     W E L C O M E                  \n";
    bool t=true;
    int btn;
    tcheck(t);
    if(t == true)
    {
        cout << "\nTeacher Login is successfull.";
        cout << "\n1. Enter a new User.";
        cout << "\n2. Issue a book.";
        cout << "\n3. Return a Book.";
        cout << "\n4. List of All Books.";
        cout << "\n5. Delete a student.";
        cout << "\n6. List of All Users.";
        cout << "\n7. Search User.";
        cout << "\n8. Show issued Boooks.";
        cout << "\n9. Exit.";
        cout << "\n Press any button to continue: ";
        cin >> btn;
    }
    switch(btn)
    {
        case 1:
            AddUser(regNos,names,NBooks,i);
            break;
        case 2:
            IssueBook(regNos,names,NBooks,BookName,BookCopies,i,j);
            break;
        case 3:
            ReturnBook(regNos,names,BookName,NBooks,BookCopies,i,j);
            break;
        case 4:
            DisplayBooks(BookName,BookCopies,j);
            break;
        case 5:
            DeleteUser(regNos,names,NBooks,BookName,BookCopies,i,j);
            break;
        case 6:
             UsersSorted(names, NBooks, i);
             break;
        case 7:
            OBooks(regNos,names,NBooks,i); 
            break;
        case 8:
            UserBooks(names, NBooks, i);     
            break;     
        case 9:
            break;
        default:
            cout << "Invalid! please try again.";
            break;
    }
    return 0;
}