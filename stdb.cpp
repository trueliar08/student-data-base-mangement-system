/*                                                          STUDENT DATABASE MANAGEMENT SYSTEM
                                                              C++ Project using File Handling
                                   

                                    Features of the Project:
                                    1)Adding new student.
                                    2)Searching record.
                                    3)Modifying record.
                                    4)Deleting record.
*/
#include<fstream>
//library for using file handling
#include<iostream>
#include<stdio.h>
using namespace std;
class Student
{
 int reg_no;
 char name[20];
 long yoj;
 int Semester;
 char Branch[3];

 public:
 void getdata();//function to accept data from user
 void display();//function to display data
 int getno()//funtion to return registration Number which is private and unique
 {
    return reg_no;
}
 int getSemester()//funtion to return semester which is private.
 {
   return Semester;
 }
 int getYearOfJoining()//funtion to return year of joining which is private.
 {
   return yoj;
 }
}s;

void Student::getdata()
{
 cout<<"Enter Registration Number : ";
 cin>>reg_no;
 cout<<"Enter Name : ";
 cin>>name;
 cout<<"Enter Semester : ";
 cin>>Semester;
 cout<<"Enter Year Of Joining :";
 cin>>yoj;
 cout<<"Enter Branch :";
 cin>>Branch;


}
void Student::display()
{
 cout<<"=================================================\n";
 cout<<"Registration Number : "<<reg_no<<"\tName  : "<<name<<"\n";
 cout<<"Semester    : "<<Semester <<"\tYear Of Joining  :   "<<yoj<<"\tBranch   :   "<<Branch<<"\n";
// cout<<"=================================================\n";
}

//Prototyping of functions for menu
void menu();
void search();
void add();
void displayall();
void Semesterwise();
void yojwise();
void Modify();
void Delete();
void options();
void Trash();
int main()
{
 int n,rno,i;
 fstream fio("stud.dat",ios::in|ios::out|ios::binary);
 menu();
 return 0;
}

void options()
{
 cout<<"\n\t\t\t\t***MENU OF PROGRAM***\n";
 cout<<"\t\t\t\t0. EXIT\n";
 cout<<"\t\t\t\t1. Add the record\n";
 cout<<"\t\t\t\t2. Search the record\n";
 cout<<"\t\t\t\t3. Display all records\n";
 cout<<"\t\t\t\t4. Display Semester wise records\n";
 cout<<"\t\t\t\t5. Modify the Record\n";
 cout<<"\t\t\t\t6. Delete the Record\n";
 cout<<"\t\t\t\t7. View Deleted Records\n";
 cout<<"\t\t\t\t8. Display Year of joining wise records\n";
 cout<<"\nEnter Your Choice  : ";
}

void menu()
{
 int ch;
 options();
 cin>>ch;
 while(ch)
 {
  switch(ch)
  {
  case 1:
        add();
        break;
  case 2:
        search();
        break;
  case 3:
        displayall();
        break;
  case 4:
        Semesterwise();
        break;
  case 5:
        Modify();
        break;
  case 6:
        Delete();
        break;
  case 7:
        Trash();
        break;
  case 8:
        yojwise();
        break;
  default:
        cout<<"Ooops!!!\n";
        cout<<"Wrong Input please enter the correct value";
  }
  options();
  cin>>ch;
 }
}
void yojwise()
{
  int y;
  cout<<"Enter the year of joining :";
  cin>>y;
  ifstream fin("stud.dat",ios::in|ios::binary);
  while(fin.read((char*)&s,sizeof(s)))
  {

    if(s.getYearOfJoining()==y)
    {
      s.display();
    }
  }
}


void search()
{
 ifstream fin("stud.dat",ios::in|ios::binary);
 int rno,i=0;
 char found='n';
 cout<<"\nEnter Registration Number to be searched : ";
 cin>>rno;

 while(fin.read((char*)&s,sizeof(s)))
 {
  if(s.getno()==rno)
  {
   s.display();
   found='y';
  }
  i++;
 }
 if(found=='n') cout<<"\nThe Registration Number "<<rno<<" is not in the file...\n";
 fin.close();
}

//For Displaying the all data of the students.
void displayall()
{
 ifstream fin("stud.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {

  s.display();
 }
 fin.close();
// int x=gcount();
// cout<<"\n"<<x<<" Bytes read from file...\n";
}

//For adding the data into the file.
void add()
{
 char ch='y';
 ofstream fout("stud.dat",ios::out|ios::app|ios::binary);
 while(ch=='y'||ch=='Y')
 {
  s.getdata();
  fout.write((char*)&s,sizeof(s));
  cout<<"\nDo you want to add more : ";
  cin>>ch;
 }
 cout<<"\nData Appended and Transferred to file...\n";
 fout.close();
}

void Semesterwise()
{
 ifstream fin("stud.dat",ios::in|ios::binary);
 int std;
 char found='n';
 cout<<"\nEnter the Semester to be searched : ";
 cin>>std;

 while(fin.read((char*)&s,sizeof(s)))
 {
  if(s.getSemester()==std)
  {
   s.display();
   found='y';
  }
 }
 if(found=='n') cout<<"\nThe Semester "<<std<<" is not in the file...\n";
 fin.close();
}

void Modify()
{
 fstream fio("stud.dat",ios::in|ios::out|ios::binary);
 int rno;
 char found='n';
 fio.seekg(0);
 cout<<"\nEnter the Registration Number whose record is to be modified: ";
 cin>>rno;
int D=0;
 while(fio&&D==0)
 {
  int loc=fio.tellg();
  fio.read((char*)&s,sizeof(s));
//  fio.read((char*)&s,sizeof(s));
  if(s.getno()==rno)
  {
  s.getdata();
  found='y';
  fio.seekg(loc);
  fio.write((char*)&s,sizeof(s));
  cout<<"\nYour record of Registration Number "<<rno
     <<" has been updated....";
     D=1;
  }

 }
 if(found=='n') cout<<"\nThe Semester "<<rno<<" is not in the file...\n";
 fio.close();
}

void Delete()
{
 int rno;
 char found='n';
 fstream fio("stud.dat",ios::in|ios::out|ios::binary|ios::app);
 ofstream fout("temp.dat",ios::out|ios::binary|ios::app);
 ofstream out("trash.dat",ios::out|ios::binary|ios::app);

 cout<<"\nEnter the Registration Number whose record is to be deleted: ";
 cin>>rno;

 while(fio.read((char*)&s,sizeof(s)))
 {
  if(s.getno()==rno)
  {
   out.write((char*)&s,sizeof(s));
   found='y';
  }
  else
  {
   fout.write((char*)&s,sizeof(s));
  }
 }
 if(found=='n') cout<<"\nThe Registration Number"<<rno<<" is not in the file...\n";
 fio.close();
 fout.close();
 remove("stud.dat");
 rename("temp.dat","stud.dat");
}

void Trash()
{
 ifstream fin("trash.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.display();
 }
 fin.close();
}
