#ifndef CITIZENSDB_H
#define CITIZENSDB_H
#include <string>

#include<iostream>
#include <string>
#include<fstream>
#include<sstream>

using namespace std;
struct CCID_NODE;
struct CBID_NODE;
template <class T>
struct Data {
	T info;//string name, father name ....for CBID,crime & punishment... for CCID
	Data* next;			//Node structure for data pipeline, implement data members as per requirement
};
template <class T>
class DataPipeline {


	Data <T>* front;//begining of the list
	Data <T>* rear;//ending 
	int count;
public:

	DataPipeline()
	{
		front = NULL;//declare null when an object is declared to prevent from garbage value
		rear = NULL;
		count = 0;//check for empty
	}


	T face() {

		T dat;
		dat = front->info;//string stroed at begining
		if (is_empty())
		{
			cout << "The queue is empty.\n";
		}
		return dat;//string return
	}
	T back() {
		T dat;
		dat = rear->info;//string stroed at begining
		if (is_empty())
		{
			cout << "The queue is empty.\n";
		}
		return dat;//string return
	}


	void enqueue(T data)
	{
		Data<T>* newnode;//new node 
		newnode = new Data<T>;//dynamically declared
		newnode->info = data + " ";//string stored in new node's data

		if (is_empty()) //check so the head can be intialized
		{
			front = newnode;
			rear = newnode;
		}
		else
		{
			rear->next = newnode;//movement to next node so tail can be declared
			rear = newnode;
		}
		count++;
	}

	T dequeue() {
		Data<T>* temp;
		T dat;
		if (is_empty())
			cout << "The queue is empty.\n";
		else
		{
			dat = front->info;
			temp = front->next;//when output is given to dat temp front is deleted and moved to the next node and that is why temp is used
			delete front;
			front = temp;
			count--;
			if (count == 0)
				rear = NULL;
		}
		return dat;

	}
	void print()//it was declared only to check the input given
	{
		Data<T>* tmp;
		tmp = front;
		while (tmp != NULL)//until reahces rear's next (null)
		{
			cout << tmp->info << endl;
			tmp = tmp->next;
		}
	}


	bool is_empty() {
		if (count > 0)
		{
			return 0;
		}
		else
			return 1;
	}
	~DataPipeline() {
		while (!is_empty()) {
			Data<T>* n = front;
			front = front->next;
			delete n;
		}
	}
};


struct CBID_NODE {
	int cnic;//data members
	string name, fname, address, nation;//data members
	char gen[1];
	CBID_NODE* next, * prev;//moving back and fro
	CCID_NODE* link;//for connecting with ccid
}obj;
struct CCID_NODE {//same as cbid with slight variation of membertype
	int Cnic;
	string fine;
	string crime, punishment;
	CCID_NODE* nex, * pre;
	CBID_NODE* link;
}objt;

template <class T>
class CBIDList {
	CBID_NODE* head, * tail;//front & end
public:
	void insert(CBID_NODE obj)//obj coming from dequeue
	{
		CBID_NODE* newnode;//new node 
		newnode = new CBID_NODE();//dynamically declared
		newnode->cnic = obj.cnic;//obj data being stored into a new node cnic name fname.....
		newnode->name = obj.name;//obj data being stored into a new node cnic name fname.....
		newnode->fname = obj.fname;//obj data being stored into a new node cnic name fname.....
		newnode->gen[0] = obj.gen[0];//obj data being stored into a new node cnic name fname.....
		newnode->address = obj.address;
		newnode->nation = obj.nation;

		if (head == NULL)//check so the head can be intialized
		{
			head = newnode;
			tail = newnode;
		}
		else
		{
			tail->next = newnode;//movement to next node so tail can be declared
			tail = newnode;
		}
	}
	void display()//displaying for checking only not used though
	{
		CBID_NODE* tmp;
		tmp = head;
		while (tmp != NULL)
		{
			cout << tmp->cnic << endl;
			cout << tmp->name << endl;
			cout << tmp->fname << endl;
			cout << tmp->gen[0] << endl;
			cout << tmp->address << endl;
			cout << tmp->nation << endl << endl;
			tmp = tmp->next;
		}

	}
	void bubbleSort()
	{
		int swapped;
		CBID_NODE* ptr;
		CBID_NODE* test = NULL;


		if (head == NULL)
		{
			cout << " The LIST is Empty" << endl;
		}


		else
		{
			do
			{
				swapped = 0;
				ptr = head;

				while (ptr->next != test)
				{
					if (ptr->cnic > ptr->next->cnic)//find if exists
					{
						swap(ptr->cnic, ptr->next->cnic);//swaping
						swapped = 1;
					}
					ptr = ptr->next;
				}
				test = ptr;
			} while (swapped);
		}
	}


	CBID_NODE* linki(int CNIC, CCID_NODE* link) {
		if (head==NULL) {
			return NULL;
		}
		CBID_NODE* LK = head;
		for (; LK; LK = LK->next) {
			if (LK->cnic == CNIC) {
				LK->link = link;//link with ccid
				return LK;
			}
		}
		return NULL;
	}
	T look(int CNIC) {
		T out;
		if (head==0) {
			out = "\0";
			return out;
		}
		CBID_NODE* temp = head;
		while (temp) {
			if (temp->cnic == CNIC) {
				out = temp->cnic +" " + temp->name +" " + temp->fname+ " " + temp->address + " " + temp->gen[0] + " " + temp->nation;//cbid data
				if (temp->link)
					out = out +" " + temp->link->crime + " " + temp->link->punishment + " " + temp->link->fine;//(ccid data)comments in ccid look
				else 
					return out;

			}
			temp = temp->next;
		}
		return out;
	}

	bool uname(T Name , int CNIC) {
		if (head==NULL) {
			return false;//return 0
		}
		CBID_NODE* temp = head;
		while (temp) {
			if (temp->cnic == CNIC) {
				temp->name = Name;//swap name when cnic found
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool ufname(T Name, int CNIC) {
		if (head == NULL) {
			return false;
		}
		CBID_NODE* temp = head;
		while (temp) {
			if (temp->cnic == CNIC) {
				temp->fname = Name;//swap father name when cnic found
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool uaddress(T add, int CNIC) {
		if (head == NULL) {
			return false;
		}
		CBID_NODE* temp = head;
		while (temp) {
			if (temp->cnic == CNIC) {
				temp->address = add;//swap address when cnic found
				return true;
			}
			temp = temp->next;//swap nation when cnic found
		}
		return false;
	}
	bool unationality(T nat, int CNIC) {
		if (head == NULL) {
			return false;
		}
		CBID_NODE* temp = head;
		while (temp) {
			if (temp->cnic == CNIC) {
				temp->nation = nat;//swap nation when cnic found
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
};
template <class T>
class CCIDList {

	CCID_NODE* top, * bottom;
public:
	void in(CCID_NODE objt)
	{
		CCID_NODE* newnode;
		newnode = new CCID_NODE();
		newnode->Cnic= objt.Cnic;
		newnode->crime = objt.crime;
		newnode->punishment = objt.punishment;
		newnode->fine = objt.fine;
		

		if (top== NULL)
		{
			top = newnode;
			bottom = newnode;
		}
		else
		{
			bottom->nex = newnode;
			bottom = newnode;
		}
	}
	void display()
	{
		T* tmp;
		tmp = top;

		while (tmp != NULL)
		{
			cout << tmp->Cnic << endl;
			cout << tmp->crime << endl;
			cout << tmp->punishment << endl;
			cout << tmp->fine << endl;
			tmp = tmp->nex;
		}

	}
	CCID_NODE* linki(int CNIC, CBID_NODE* link) {//linking cnic check with database
		if (top == NULL) {
			return NULL;
		}
		CCID_NODE* LK = top;
		for (; LK; LK = LK->nex) {
			if (LK->Cnic == CNIC) {
				LK->link = link;//linking
				return LK;
			}
		}
		return NULL;
	}
	T look(int CNIC) {
		T out;
		if (top == 0) {
			out = "\0";
			return out;
		}
		CCID_NODE* temp = top;
		while (temp) {
			if (temp->Cnic == CNIC ) {
				out = temp->Cnic + " " + temp->crime + " " + temp->punishment + " " + temp->fine; //ccid info
				if (temp->link)
				out = temp->link->name + " " + temp->link->fname + " " + temp->link->address + " " + temp->link->gen[0] + " " + temp->link->nation + " "+ out;//cbid info added
				else
					return out;

			}
			temp = temp->nex;
		}
		return out;
	}
	bool dCrime(int CNIC, T cr, T punishment, T fine) {
		if (top==NULL) {
			return false;
		}
		CCID_NODE* temp = top;
		
		while (temp) {
			if (temp->Cnic == CNIC && temp->crime == cr&& temp->punishment == punishment && temp->fine == fine)//checking if it it exists
				{
				temp->nex->pre = temp->pre;
				temp->pre->nex = temp->nex;
					delete temp;//deleting after prev and next are set
					return true;
				}
			else
			{
				return false;
			}
			temp = temp->nex;//inc
		}
		
	}
	bool uCrime(int CNIC, T cr, T punishment, T fine) {
		if (top == NULL) {
			return false;
		}
		CCID_NODE* temp = top;

		while (temp) {
			if (temp->Cnic == CNIC)//person with that cnic
			 {										
			 	//new info added
				temp->crime = cr;
				temp->punishment = punishment;
				temp->fine = fine;
				
				return true;
			}
			temp = temp->nex;
		}
		return false;
	}
	bool aCrime(int CNIC, T cr, T punishment, T fine) //adding a new node that is why a new node is declared at the end and the rear  is moved
	{
		if (top == NULL) {
			return false;
		}
		CCID_NODE* newnode;
		newnode = new CCID_NODE();
		newnode->Cnic = CNIC;
		newnode->crime = cr;
		newnode->punishment = punishment;
		newnode->fine = fine;
		
			bottom->nex = newnode;
			bottom = newnode;

		return true;
	}
};
template <class T>
class Database {

	CBIDList<T> cbid; //CBID Database
	CCIDList<T> ccid; //CCID Database
	DataPipeline<T> dataPipeline;

public:

	Database()
	{
		DataPipeline <T>D;

		T a1, a2, a3, a;
		T b, b1, b2, b3, b4;
		int found;
		bool chk1 = 1;
		int ichk = 0;
		bool chk2 = 1;
		int jchk = 0;
		ifstream in;
		T st;
		in.open("CBID.txt");

		while (getline(in, st))//get line as string
		{

			D.enqueue(st);//insert in pipe line
			stringstream ss(D.dequeue());//out & delete from 
			T word;//string
			while (ss >> word)//taking a word in from stringstream one by one
			{

				if (chk1 && ichk == 0)
					if (stringstream(word) >> found)//into int
					{

						obj.cnic = found;
						chk1 = 0;
					}

				if (ichk == 1)
				{
					obj.name = word;//second word and so on
				}
				if (ichk == 2)
				{
					obj.fname = word;
				}

				if (ichk == 3)
				{
					obj.gen[0] = word[0];//string into char( gender)
				}
				if (ichk == 4)
				{
					a1 = word;
				}
				if (ichk == 5)
				{
					a2 = word;
				}
				if (ichk == 6) {
					a3 = word;
					a = a1 + " " + a2 + " " + a3;
					obj.address = a;
				}
				if (ichk == 7)
				{
					obj.nation = word;
				}
				ichk++;
			}
			cbid.insert(obj);
			
			ichk = 0;
			chk1 = 1;
		}
		cbid.bubbleSort();
		
		in.close();
		DataPipeline <T> K;
		in.open("CCID.txt");
		while (getline(in, st))//same as cbid for ccid comments
		{
			K.enqueue(st);
			stringstream dd(K.dequeue());
			string word1;
			while (dd >> word1)
			{
				if (chk2 && jchk == 0)
				{
					stringstream L(word1);
					int x = 0;
					L >> x;
					objt.Cnic = x;
					chk2 = 0;
				}
				if (jchk == 1)
				{
					objt.crime = word1;
				}
				if (jchk == 2)
				{
					b1 = word1;
				}
				if (jchk == 3)
				{
					b2 = word1;
				}
				if (jchk == 4)
				{
					b3 = word1;
				}
				if (jchk == 5)
				{
					b4 = word1;
					b = b1 + " " + b2 + " " + b3 + " " + b4;
					objt.punishment = b;
				}

				if (jchk == 6)
				{
					objt.fine = word1;
				}
				jchk++;
			}
			ccid.in(objt);
			jchk = 0;
			chk2 = 1;
			CBID_NODE* temp1;
			CCID_NODE* temp2;
			temp2 = new CCID_NODE();
			temp2->Cnic = objt.Cnic;
			temp2->crime = objt.crime;
			temp2->punishment = objt.punishment;
			temp2->fine = objt.fine;
			temp1 = cbid.linki(objt.Cnic, temp2);
			temp2 = ccid.linki(objt.Cnic, temp1);
		}
		
	}
	T CBID_Search_by_CNIC(int cnic) {

		T j = cbid.look(cnic);
		return j;
	}
	T CCID_Search_by_CNIC(int cnic) {

		T j = ccid.look(cnic);
		return j;
	}
	bool updateCBIDName(T Name, int cnic) {
		return cbid.uname(Name, cnic);
	}
	bool updateCBIDFName(T Father_Name, int cnic) {
		return cbid.ufname(Father_Name, cnic);
	}
	bool updateCBIDAddress(T Address, int cnic) {
		return cbid.uaddress(Address, cnic);
	}
	bool updateCBIDNationality(T Nationality, int cnic) {
		return cbid.unationality(Nationality,cnic);
	}
	bool deleteCrime(int cnic, T charges, T punishment, T fine) {
		return ccid.dCrime(cnic, charges, punishment, fine);
	}
	bool updateCrime(int cnic, T charges, T punishment, T fine) {
		return ccid.uCrime(cnic, charges, punishment, fine);
	}
	bool ADDCrime(int cnic, T charges, T punishment, T fine) {
		return ccid.aCrime(cnic, charges, punishment, fine);
	}
	};


#endif
