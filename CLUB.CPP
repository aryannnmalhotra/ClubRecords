#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
class clubmember
  {
    char name[80];
    char grade[20];
    int mno;
    int attendance;
    char zone[80];
    char prof[80];
    char add[80];
    char clubrel[80];
   public:
    void gradeassign()
     {
      if(attendance<30)
	strcpy(grade,"Bronze");
      else if(attendance>=30 && attendance<35)
	strcpy(grade,"Silver");
      else if(attendance>=35 && attendance<39)
	strcpy(grade,"Gold");
     }
    void getdata()
     {
       cout << "Enter Name"<<'\n';
       gets(name);
       cout<<"Enter Membership ID"<<'\n';
       cin>>mno;
       cout<<"Enter last season attendance"<<'\n';
       cin>>attendance;
       gradeassign();
       cout<<"Enter seating zone"<<'\n';
       gets(zone);
       cout<<"Enter profession"<<'\n';
       gets(prof);
       cout<<"Enter address"<<'\n';
       gets(add);
       cout<<"Specify the relation with the club"<<'\n';
       gets(clubrel);
     }
    void display()
       { cout<<"Name : "<<name<<'\n';
	 cout<<"Membership ID : "<<mno<<'\n';
	 cout<<"Last season attendance : "<<attendance<<'\n';
	 cout<<"Grade : "<<grade<<'\n';
	 cout<<"Seating zone : "<<zone<<'\n';
	 cout<<"Profession : "<<prof<<'\n';
	 cout<<"Address : "<<add<<'\n';
	 cout<<"Club relation : "<<clubrel<<'\n';
       }
    int retmno()
       {
	return mno;
       }
    char*retname()
       {
	return name;
       }
    int retattendance()
       {
	return attendance;
       }
    char*retgrade()
       {
	return grade;
       }

  };
char ans;
clubmember c1,c2;
fstream file,temp;
void create()
  {
   file.open("data.dat",ios::out|ios::binary);
   do
   {
   c1.getdata();
   file.write((char*)&c1,sizeof(c1));
   cout<<"Do you want to enter another record?: (Y/N)"<<'\n';
   cin>>ans;
   }while(ans=='Y'||ans=='y');
   file.close();
  }
void showfile()
  {
   clrscr();
   int r=0;
   file.open("data.dat",ios::in|ios::binary);
   while(file.read((char*)&c1,sizeof(c1)))
    {
     r++;
     cout<<'\n';
     cout<<"Record Number : "<<r<<'\n';
     cout<<"_____________________"<<'\n';
     c1.display();
     cout<<"_____________________";

    }
   file.close();
  }
void append()
  {
   file.open("data.dat",ios::app|ios::binary);
   do
    {
     c1.getdata();
     file.write((char*)&c1,sizeof(c1));
     cout<<"Do you want to enter another record?: (Y/N)"<<'\n';
     cin>>ans;
    }while(ans=='Y'||ans=='y');
   file.close();
  }
void nsearch()
 {
  file.open("data.dat",ios::in|ios::binary);
  char mname[15];
  cout<<"Enter name to search"<<'\n';
  gets(mname);
  while(file.read((char*)&c1,sizeof(c1)))
   {
    if(strcmp(mname,c1.retname())==0)
     {
      clrscr();
      c1.display();
      break;
     }
   }
  file.close();
 }
void msearch()
 {
  file.open("data.dat",ios::in|ios::binary);
  int no;
  cout<<"Enter membership ID to search by"<<'\n';
  cin>>no;
  while(file.read((char*)&c1,sizeof(c1)))
   {
    if(c1.retmno()==no)
     {
      clrscr();
      c1.display();
      break;
     }
   }
  file.close();
 }

void attcount()
 {
  file.open("data.dat",ios::in|ios::binary);
  int a;
  cout<<"Enter minimum attendance to be considered: "<<'\n';
  cin>>a;
  int r=0;
  while(file.read((char*)&c1,sizeof(c1)))
   {
    if(c1.retattendance()>a)
      r++;
   }
  file.close();
  clrscr();
  cout<<"The number of members having an attendance > "<<a<<" is "<<r<<'\n';
 }
void grcount()
 {
  file.open("data.dat",ios::in|ios::binary);
  char gr[15];
  cout<<"Enter grade to be considered: "<<'\n';
  cin>>gr;
  int r=0;
  while(file.read((char*)&c1,sizeof(c1)))
   {
    if(strcmp(c1.retgrade(),gr)==0)
      r++;
   }
  file.close();
  clrscr();
  cout<<"The number of members belonging to the grade "<<gr<<" is "<<r<<'\n';
 }
void editname()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("new.dat",ios::out|ios::binary);
  char mname[15];
  cout<<"Enter the name of the member whose details you want to edit: "<<'\n';
  gets(mname);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    if(strcmp(c2.retname(),mname)==0)
     {
      cout<<"Enter new details"<<'\n';
      c2.getdata();
     }
    temp.write((char*)&c2,sizeof(c2));
   }
  temp.close();
  file.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void editmno()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("data.dat",ios::out|ios::binary);
  int er;
  cout<<"Enter the membership ID of the record you want to edit: "<<'\n';
  cin>>er;
  file.seekg(0);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    if(er==c2.retmno())
     {
      cout<<"Enter new details: "<<'\n';
      c2.getdata();
     }
    temp.write((char*)&c2,sizeof(c2));
   }
  temp.close();
  file.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void delmno()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("new.dat",ios::out|ios::binary);
  int no;
  cout<<"Enter membership ID of the member you want to delete from the records: "<<'\n';
  cin>>no;
  file.seekg(0);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    if(c2.retmno()!=no)
      temp.write((char*)&c2,sizeof(c2));
   }
  file.close();
  temp.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void delname()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("new.dat",ios::out|ios::binary);
  char mname[15];
  cout<<"Enter name of the member you want to delete from the records: "<<'\n';
  gets(mname);
  file.seekg(0);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    if(strcmp(c2.retname(),mname)!=0)
      temp.write((char*)&c2,sizeof(c2));
   }
  file.close();
  temp.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void insmno()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("new.dat",ios::out|ios::binary);
  int no;
  cout<<"Enter the membership ID of the member after which you want to enter the new record: "<<'\n';
  cin>>no;
  file.seekg(0);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    temp.write((char*)&c2,sizeof(c2));
    if(c2.retmno()==no)
     {
      cout<<"Enter details of the member to be inserted: "<<'\n';
      c1.getdata();
      temp.write((char*)&c1,sizeof(c1));
     }
   }
  file.close();
  temp.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void insname()
 {
  file.open("data.dat",ios::in|ios::binary);
  temp.open("new.dat",ios::out|ios::binary);
  char mname[15];
  cout<<"Enter the name of the member after which you want to insert the new record: "<<'\n';
  gets(mname);
  file.seekg(0);
  while(file.read((char*)&c2,sizeof(c2)))
   {
    temp.write((char*)&c2,sizeof(c2));
    if(strcmp(c2.retname(),mname)==0)
    {
     cout<<"Enter details of the member you want to insert: "<<'\n';
     c1.getdata();
     temp.write((char*)&c1,sizeof(c1));
    }
   }
  file.close();
  temp.close();
  remove("data.dat");
  rename("new.dat","data.dat");
 }
void countrec()
 {
  file.open("data.dat",ios::in|ios::binary);
  file.seekg(0,ios::end);
  int lp=file.tellg();
  int s=sizeof(c1);
  int lr=lp/s;
  clrscr();
  cout<<"The total number of members is "<<lr<<'\n';
  file.close();
 }
void main()
 {
  char ch1;
  int ch;
  char choice;
  clrscr();
  do
   {
    clrscr();
    cout<<"Choose an option from the following menu"<<'\n';
    cout<<"1)Create a file for all club members"<<'\n';
    cout<<"2)Display the details of all club members"<<'\n';
    cout<<"3)Add member records to the existing records"<<'\n';
    cout<<"4)Edit records"<<'\n';
    cout<<"5)Search records"<<'\n';
    cout<<"6)Count records"<<'\n';
    cout<<"7)Insert records"<<'\n';
    cout<<"8)Delete records"<<'\n';
    cin>>ch;
    switch(ch)
     {
      case 1:  create();
	       break;
      case 2:  showfile();
	       break;
      case 3:  append();
	       break;
      case 4:  cout<<"Choose from the following"<<'\n';
	       cout<<"a)Edit on the basis of a user given name"<<'\n';
	       cout<<"b)Edit on the basis of membership ID"<<'\n';
	       cin>>choice;
	       if(choice=='a')
		 editname();
	       else if(choice=='b')
		 editmno();
	       else
		 cout<<"Invalid choice"<<'\n';
	       break;
      case 5:  cout<<"Choose from the following"<<'\n';
	       cout<<"a)Search on the basis of name"<<'\n';
	       cout<<"b)Search on the basis of membership ID of the member"<<'\n';
	       cin>>choice;
	       if(choice=='a')
		 nsearch();
	       else if(choice=='b')
		 msearch();
	       else
		 cout<<"Invalid choice"<<'\n';
	       break;
      case 6:  cout<<"Choose from the following"<<'\n';
	       cout<<"a)Count the members on the basis of the membership grade"<<'\n';
	       cout<<"b)Count the members having a minimum attendance"<<'\n';
	       cout<<"c)Count the total number of members in the club"<<'\n';
	       cin>>choice;
	       if(choice=='a')
		 grcount();
	       else if(choice=='b')
		 attcount();
	       else if(choice=='c')
		 countrec();
	       else
		 cout<<"Invalid choice"<<'\n';
	       break;
      case 7:  cout<<"Choose from the following"<<'\n';
	       cout<<"a)Insert details after a given member name"<<'\n';
	       cout<<"b)Insert details after a given membership ID"<<'\n';
	       cin>>choice;
	       if(choice=='a')
		 insname();
	       else if(choice=='b')
		 insmno();
	       else
		 cout<<"Invalid choice"<<'\n';
	       break;
      case 8:  cout<<"Choose from the following"<<'\n';
	       cout<<"a)Delete member details on the basis of a given member name"<<'\n';
	       cout<<"b)Delete member details on the basis of a given membership ID"<<'\n';
	       cin>>choice;
	       if(choice=='a')
		 delname();
	       else if(choice=='b')
		 delmno();
	       else
		 cout<<"Invalid choice"<<'\n';
	       break;
      default: cout<<"Invalid choice"<<'\n';
     }
    cout<<'\n';
    cout<<"Do you want to go back to the main menu? : (Y/N)"<<'\n';
    cin>>ch1;
   }while(ch1=='y'||ch1=='Y');
 }


