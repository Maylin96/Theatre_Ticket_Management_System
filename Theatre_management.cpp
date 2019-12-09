#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<process.h>
using namespace std;

using std::cout;
using std::cin;
using std::endl;
struct TIME
{
	char hr[3];
	char min[3];
};

class ticket
{
	char name[20];
	int no,m,price,sno;
	char type[10];
	TIME time;
	
	public:
		char d[3],mn[3],yr[3];
		ticket()
		{
			no=price=sno=m=0;
		}
		void input();
		void output();
		int retno()
		{
			return no;
		}
		char* retname()
		{
			return name;
		}
		int retsno()
		{
			return sno;
		}
		int retm()
		{
			return m;
		}
		int retprice()
		{
			return price;
		}
		
}t;



//using std::cout;

void view(int c)
{
	int n=100,k,l[8];
	char date[3];
	cout<<"Enter today's date(dd):\t";
	cin>>date;
	ifsream f3;
	f3.open("thticket.dat",ios::binary|ios::in);
	cout<<"SEATS AVAILABILITY......>\n\n";
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		if(j==4)	//horizontal divider
		cout<<"\t";
		
		cout<<n<'*';
		k=0;
		//checking for seat bookings for a specific show
		while(f3.read((char*)&t,sizeof(t)))
		{
			if((t.retm()==c)&&(strcmp(date,t.d)==0))
			l[k]=t.retsno();
			k++;
			
		}
		for(k=0;k<8;k++) // symbolizing booked seats
		{
			if(n==l[k])
			cout<<"$*";
		}
		cout<<"\t";
		if(n==139)		//vertical row divider
		cout<<"\n\n";
		n++;
	}
	cout<<"\n\n";
	}
	f3.close();
	cout<<"*$*-Booked seats\n";
	cout<<"*-Unbooked seats\n";
}

void ticket::input()	//to input ticket details
{
	cout<<"\n\nTicket no:\t";
	randomize();
	no=random(9)*1000+random(999);
	cout<<no;
	cout<<"\nEnter the seat number:\t";
	cin>>sno;
	cout<<"\nSelect show no:\t";
	cin>>m;
	cout<<"\nEnter movie name:\t";
	gets(name);
	cout<<"\nEnter the date(dd mm yy):\n";
	cin>>d>>mn>>yr;
	cout<<"Enter the time(format:HH MM)\n";
	cin>>time.hr>>time.min;
	cout<<"Enter the price:\t Rupees";
	cin>>price;
}
void ticket::output()	//to display the details of a ticket
{	
	cout<<"Ticket No:\t"<<no<<endl;
	cout<<"\t\tType:\t";
	puts(type);
	cout<<"\nMovie Name\t:\t"<<name<<endl;
	cout<<"Date\t:\t"<<d<<"/"<<mn<<"/"<<yr<<endl;
	cout<<"\tTime\t:\t"<<time.hr<<":"<<time.min<<endl;
	cout<<"\nSeat no:\t"<<sno<<endl;
	cout<<"\t\tPrice\t:\tRupees"<<price<<"\n\n";
}
int listnos(int m)
{
	int i=0;
	ifstream f2;
	f2.open("thticket.dat",ios::binary|ios::in);
	if(!f2)
	{
		cout<<"\nError";
		getch();
	}
	while(f2.read((char*)&t,sizeof(t)))	
	{
		if(m==0)
		{
			cout<<++i<<"."<<t.retno();
			cout<<endl;
		}
		else if(m==1)
		{
			if(t.retm()==1)
			++i;
		}
		else if(m==2)
		{
			if(t.retm()==2)
			++i;
		}	
	}
	f2.close();
	return i;
}
void inshows()	//to input shows data
{
	clrscr();
	char str[100];
	ofstream f1;
	f1.open("TEMP.txt");
	if(!f1)
	{
		cout<<"\nError";
		getch();
		
	}
	cout<<"\nEnter new shows details \n";
	for(int i=0;i<2;i++)
	{
		cout<<"Show"<<(i+1)<<":";
		get(str);
		f1<<str<<endl;
	}
	f1.close();
	remove("shows.txt");
	rename("TEMP.txt","shows.txt");
	cout<<"\n\nUPDATEd";
	getch();	
}	

void dispshows()	//to display shows data
{
	char str[100];
	ifstream f3;
	f3.open("shows.txt");
	if(!f3)
		cout<<"\n\nNO SHOWS ENTERED \n";
	else if(f3)
		cout<<"SHOWS\n";
	while(f3)
	{
		f3.getline(str,100);
		cout<<str<<endl;
		
	}
	f3.close();
}
void add()	// to append new ticket details to file
{
	getch();
	//clrscr();
	cout<<"\t\t\t TICKET BOOKING----->\n\n";
	char ch='n';
	dispshows();
	ofstream f1;
	f1.open("thticket.dat",ios::binary|ios::app);
	if(!f1)
	{
		cout<<"\nERROR";
		getch();
		
	}
	while(ch=='n')
	{
		t.input();
		cout<<"\n\n Confirm?(y,n or c)\n";
		cin>>ch;
		if(ch=='y'){
			f1.write((char*)&t,sizeof(t));
			cout<<"\n\nDatabase Updated !!\n";
		}
		else if(ch=='c'){
		cout<<"\n\nOperation Canceled!!!\n";
		getch();
		break;
		}
		else{
			cout<<"\n\n Operation Resetting\n";
			getch();
		}
		
	}
	f1.close();
}
void search(){
	clrscr();
	cout<<"\t\t<.......TICKET search........>\n\n";
	int eno;
	ifstream f2;
	int fl=0;
	f2.open("thticket.dat",ios::binary|ios::in);
	if(!f2){
		cout<<"\nError";
		getch();
	}
	cout<<"\n\nEnter the ticket no.: ";
	cin>>eno;
	while(f2.read((char*)&t,sizeof(t)))
	{
		if(eno==t.retno()){
			t.output();
			fl=1;
		}
	}
	f2.close();
	if(!fl)
	cout<<"\n Search is unsuccessful";
}

void modify(){
	clrscr();
	cout<<"\t\t<.......TICKET MODIFICATION.......>\n\n";
	fstream f;
	int fl=0,tn,n;
	f.open("thticket.dat",ios::binary|ios::in|ios::out);
	if(!f){
		cout<<"ERROR";
		getch();
	}
	cout<<"ALL EXISTING TICKET NOS. \n\n\n";
	n=listnos(0);
	cout<<"\n No. of records: "<<n;
	cout<<"\n Enter the Ticket no. to modify :\n";
	cin>>tn;
	clrscr();
	dispshows();
	while(f.read(char*)&t,sizeof(t)){
		if(tn==t.retno()){
			t.input();
			f.seekp(-sizeof(t),ios::cur);
			f.write((char*)&t,sizeof(t));
			fl=1;
			cout<<"TICKET MODIFIED";
			
		}
	}
	f.close();
	if(!fl)
	cout<<"\n\n Search is unsuccessful";
}

void del(){
	int flag = 0, tno,n;
	cout<<"\t\t\tTICKET delete---->\n\n";
	ofstream f1;
	ifstream f2;
	cout<<"ALL EXISTING TICKET NOS:\n\n";
	n=listnos(0);
	cout<<"\nNo. of records"<<n;
	cout<<"\nEnter the ticket no:\n";
	cout>>tno;
	f1.open("temp.dat",ios::binary|ios::out);
	f2.open("thticket.dat",ios::binary|ios::in);
	if((!f1)||(!f2)){
		cout<<"ERROR";
		getch();
	}
	while(f2.read((char*)&t,sizeof(t))){
		if(tno!=t.retno()){
			f1.write((char*)&t,sizeof(t));
			flag=1;
		}
	}
	f1.close();
	f2.close();
	if(!flag)
	cout<<"\n\n Search is unsuccessful";
	else{
		remove("thticket.dat");
		rename("temp.dat","thticket.dat");
		cout<<"\nUpdated!";
	}
}

void display(){
	ifstream f2;
	int i=0;
	f2.open("thticket.dat",ios::binary|ios::in);
	if(!f2){
		cout<<"ERROR";
		getch();
	}
	cout<<"DISPLAYING RECORDS IN THTICKET>DAT----->\n";
	while(f2.read((char*)&t,sizeof(t))){
		i++;
		cout<<"\n\nRECORD NO."<<i<<endl;
		t.output();
		getch();
	}
	f2.close();
	cout<<"\nEnd of records";
}	
int lock(){
	int lk=0,i=0;
	char c,usr[7],pwd[7];
	cout<<"\n\n\t\t\t Fast ticket 6.0";
	cout<<"\n\n\t\t\t Theatre ticket management system";
	cout<<"\n\n\t\t\t A Rapsoft(TM) Product";
	cout<<"\n\n\t\t\t Developed for Cinepolis Dubai";
	cout<<"\n\n\t\t\t -----LOGIN SCREEN------->";
	cout<<"\n\n\t\t\tEnter Username";
	gets(usr);
	cout<<"\t\t Enter Password:";
	
	
	while(c!=13){
		c=getch();
			if(c!=13){
				pwd[i] = c;
				cout<<"*";
				i++;
			}
	}
	if((strcpm("t23",pwd)==0) &&(strcmp("adm",usr)==0)){
		cout<<"\n\n\t\t Logging in..";
		lk=1;
		return lk;
	}
	else{
		cout<<"\n\n\t\t WRONG USERNAME OR PASSWORD!";
		getch();
		lk=0;
		return lk;
	}
}

int income(){
	int sum=0;
	ifstream f2;
	f2.open("thticket.dat",ios::binary|ios::in);
	if(!f2)
	cout<<"Error";
	while(f2.read((char*)&t,sizeof(t))){
		if(m==0)
			sum=sum+t.retprice();
		else if(m==1){
			if(t.retm()==1)
				sum=sum+t.retprice();
		}
		else if(m==2){
			if(t.retm()==2)
			sum=sum+t.retprice();
		}
			
	}
	f2.close();
	return sum;
	
}

void menus(){
	int ch=0,r=0;
	do{
		cout<<"\n\t\t\t FAST TICKET 6.0";
		cout<<"\n\t\t\t Cinepolis, Dubai";
		cout<<"\n\t\t\t---------------------Main Menu----------------------->\n\n";
		dispshows();
		cout<<"Options";
		cout<<"\n\t\t\t 1. Ticket Booking";
		cout<<"\n\t\t\t 2. Edit";
		cout<<"\n\t\t\t 3. List all tickets";
		cout<<"\n\t\t\t 4. Cancel existing ticket";
		cout<<"\n\t\t\t 5. Search for an existing ticket";
		cout<<"\n\t\t\t 6. Log off";
		cout<<"\n\t\t\t 7. Exit";
		cout<<"\n\t\t\t Selection:\t";
		cin>>ch
		switch(ch){
			case 1: int n;
			char a;
			dispshows();
			cout<<"Select show:\t";
			cin>>n;
			view(n);
			cout<<"Proceed with ticket booking? (y or n):\t";
			cin>>a;
			if(a=='y'){
			add();
			getch();
			break;
			}
			
			case 2:clrscr();
			int k;
			cout<"Edit----------->\n\n";
			cout<<"1. Shows\n";
			cout<<"\nSelection:";
			cin>>k;
			switch(k){
				case1:inshows();
				break;
				default:cout<<"Invalid entry!";
				break;
			}
				getch();
				break;
			case 3:clrscr();
			display();
			getch();
			break;
			case 4:del();
			getch();
			break;
			case 5:search();
			getch();
			break;
			case 6:r=1;
			break;
			case 7:exit(0);
			break;
			default:cout<<"\n INVALID ENTRY!";
			getch();
			break;	
			
		}
		
		if(r)
		break;
	}while(ch!=8);
	if(r)
	cout<<"\n\n\n\n\tExiting.......";
}

void main(){
	int l=0;
	int lk=lock();
	do{
		l++;
		switch(lk)
		{
			case 1:menus();
			break;
			case 2:cout<<"exiting";
			break;
		}
		if(l>=3){
			cout<<"\n\n\n\t\tNo. Of Tries Exceeded";
			cout<<"\n\t\tExiting............";
			break;
		}
	}while(lk<1);
	getch();
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
