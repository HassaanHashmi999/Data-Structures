#include <iostream>
#include <cmath>
#include <ctime>
#include<cstring>
using namespace std;
class MNode;  //declaration of the machine node so it can be used to declare a pointer in Routing table node
class Rtnode  //doubly linked list NODE
{
public:
	int index; //index of table
	MNode* point;//pointer pointing to the next machine wrt to machine id and index
	Rtnode* pre, * next;//doubly linkeed list
	int getNextMachID();//to get id of the pointer
	Rtnode()//constructor of Rtnode
	{
		pre = NULL;
		next = NULL;
	}


};
class Table
{
	Rtnode* front, * end;
	//doubly linked list

public:
	Table()//constructor
	{
		front = NULL;
		end = NULL;
	}
	void insert(int value, MNode* ptr)//function to insert into the list 
	{
		Rtnode* newnode;
		newnode = new Rtnode();
		newnode->index = value;//loop itendation from machine function
		newnode->point = ptr;//ptr being set with the pointer being passed pointing to a machine

		if (front == NULL)//check so the front can be intialized
		{
			front = newnode;
			end = newnode;
		}
		else
		{
			end->next = newnode;//movement to next node so tail can be declared
			newnode->pre = end;//setting the previous node
			end = newnode;//moving tail to the end

		}
	}
	void display()
	{
		Rtnode* temp = front;//tranversing from front to end (head to tail)
		while (temp != NULL)
		{
			cout<<temp->index<<"  " << temp->getNextMachID();//output the id and the index it is pointing at
			cout << endl;
			temp = temp->next;//moving to the next node
		}
	}


};
class Tnode//avl tree node
{
public:
	int datID;
	int key;
	string value;
	Tnode* right, *left;
	int height;
	Tnode()//constructur
	{
		datID = 0;
		height = 1;
		left = NULL;
		right = NULL;
	}
};
class Tree//avl tree
{

private:



public:
	Tnode* root = NULL;
	void find(int num, string s) {
		//The function starts from the root
		Tnode* nodePtr = root;
		nodePtr = new Tnode();
		while (nodePtr != NULL) {
			if (nodePtr->datID == num)
			{
				nodePtr->key = num;//attacing the key 
				nodePtr->value = s;//attaching the string
			}  // value is found
			else if (num < nodePtr->datID)
				nodePtr = nodePtr->left;
			else
				nodePtr = nodePtr->right;
		}
		// value not found
	}
	
	// height of the tree
	int height(Tnode* N)
	{
		if (N == NULL)
			return 0;//for null node
		return N->height;//height being added whenever the function is called
	}


	int max(int h1, int h2)//returning the greater height
	{
		if (h1 > h2)
			return h1;
		else 
			return h2;
	}


	Tnode* newNode(int key)
	{
		Tnode* node = new Tnode();
		node->datID = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 1; //initial height setting to 1 when node is added
		return(node);
	}

	// A utility function to right
	// rotate subtree rooted with y
	// See the diagram given above.
	Tnode* rightRotate(Tnode* y)
	{
		Tnode* x = y->left;
		Tnode* T2 = x->right;

		// Perform rotation
		x->right = y;
		y->left = T2;

		// Update heights
		y->height = max(height(y->left),
			height(y->right)) + 1;
		x->height = max(height(x->left),
			height(x->right)) + 1;

		// Return new root
		return x;
	}

	// A utility function to left
	// rotate subtree rooted with x
	// See the diagram given above.
	Tnode* leftRotate(Tnode* x)
	{
		Tnode* y = x->right;
		Tnode* T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		x->height = max(height(x->left),
			height(x->right)) + 1;
		y->height = max(height(y->left),
			height(y->right)) + 1;

		// Return new root
		return y;
	}

	// Get Balance factor of node N
	int getBalance(Tnode* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}
	Tnode* insert(Tnode* node, int key)
	{
		
		if (node == NULL)
			return(newNode(key));

		if (key < node->datID)
			node->left = insert(node->left, key);
		else if (key > node->datID)
			node->right = insert(node->right, key);
		else {
			cout << "Duplicate value found"<<endl;// Equal keys are not allowed in BST
			return node;
		}
		// 2. Changing the height of this ancestor node 
		node->height = 1 + max(height(node->left),
			height(node->right));

		//check balence
		int balance = getBalance(node);

		// If this node becomes unbalanced, then
		// there are 4 cases

		// Right Shift
		if (balance > 1 && key < node->left->datID)
			return rightRotate(node);
		// Left shift
		if (balance < -1 && key > node->right->datID)
			return leftRotate(node);


		// L-R shift
		if (balance > 1 && key > node->left->datID)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		// R-L Shift
		if (balance < -1 && key < node->right->datID)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		/* return the (unchanged) node pointer */
		return node;
	}
	void preOrder(Tnode* node)
	{
		if (node == NULL)
			return;

		cout << node->datID << " ";//root
		preOrder(node->left);//left subtree
		preOrder(node->right);//right subtree
	}
};
class MNode//circle list node
{
public:
	int Id;
	Tree Tobj;
	Table RTobj;
	MNode* next;
	MNode()
	{
		Id = 0;
		next = NULL;
	}
};

class Machine//circular list
{
	MNode* head;
	MNode* tail;


public:
	Machine()//constructor
	{
		head = NULL;
		tail = NULL;
	}
	void insert(int value)
	{
		MNode* newnode;
		newnode = new MNode();
		newnode->Id = value;

		if (head == NULL)//check so the head can be intialized
		{
			head = newnode;
			tail = newnode;
		}
		else
		{
			tail->next = newnode;//movement to next node so tail can be declared
			tail = newnode;//tail moving the end node which was added  
			tail->next = head;//the next will be head
		}
	}
	void in(int arr[], int nmachine)//array with machine ids
	{
		for (int i = 0; i < nmachine; i++)//with the number of machines
		{
			insert(arr[i]);//passing the machine ids one by one to insert into the list
		}
	}
	void C_T()//creating tree function
	{
		int last = 0;
		MNode* temp = head;
		temp->Tobj.root = NULL;//root of tree is declared null at first

		if (temp != NULL)//check if head is not null
		{
			do
			{
				for (int i = last; i <= temp->Id; i++)//from the last to the machine id
				{
					temp->Tobj.root = temp->Tobj.insert(temp->Tobj.root, i);//root is being changed again and again
				}
				last = temp->Id + 1;//increasing 1 as loop is less than equal to
				temp = temp->next;//moving to the next node

			} while (temp != head);
		}
	}
	void C_RT(int bit,int inbit)
	{
		int set;

		MNode* point = head->next;//point will point at the next machine
		MNode* ptr = head->next;//same with comparison
		MNode* temp = head;//to tranverse through the machines
		if (temp != NULL)
		{

			do
			{
				
				for (int i = 1; i <= bit; i++)
				{
					set = temp->Id + pow(2, i - 1);
					
					if (set <= point->Id)
					{
						temp->RTobj.insert(i, point);
						ptr = ptr->next;
					}
					else 
					{
							
						point = point->next;
							if (set <= point->Id)
							{
								temp->RTobj.insert(i, point);
							}
							else
								temp->RTobj.insert(i, ptr);
						
					}
		
				}
				temp = temp->next;
				point = temp->next;
				ptr = temp->next;
			} while (temp != head);
		}
		//temp->RTobj.display();

	}
	void T()//displaying the trees
	{

		MNode* temp = head;


		if (temp != NULL)
		{
			do
			{
				temp->Tobj.preOrder(temp->Tobj.root);//displaying in preorder
				temp = temp->next;//movint to the next
				cout << endl;
			} while (temp != head);//whlie the temp is not head
		}

	}
	void DT(int search)//displaying the tree asked by the user
	{

		MNode* temp = head;


		if (temp != NULL)
		{
			do
			{
				if (temp->Id == search)//if the id is found that tree is printed
				{
					temp->Tobj.preOrder(temp->Tobj.root);
					cout << endl;
				}
				temp = temp->next;
				
			} while (temp != head);
		}

	}
	void find(int id, string s)
	{
		cout << "THE KEY IS  :" << id << endl;//key is generated and shown
		int last = 0;
		char X;//for input of choice
		MNode* temp = head;
		if (temp != NULL)
		{
			do
			{
				if (id <= temp->Id && id > last)
				{

					cout << "The machine id is:" << temp->Id << endl;
					temp->Tobj.find(id, s);
					cout << "Do you want to print the Tree of this Machine??[y/n]";
					cin >> X;
					if (X == 'y' || X == 'Y')
					{
						temp->Tobj.preOrder(temp->Tobj.root);
						cout << endl;
					}

				}
				last = temp->Id;
				temp = temp->next;
			} while (temp != head);
		}
	}
};
int Rtnode::getNextMachID() {
	return point->Id;
}
void Sort(int a[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		temp = a[i];//storing the first to temp
		a[i] = a[min];//check for the minimum and storing it at the first of the array
		a[min] = temp;//exchange with where before minimum was stored
	}
}
int hashing(string x, int M) {
	int HASH = 0;

	for (int i = 0; i < x.length(); i++)//run till length
		HASH += x[i];
	return HASH % M;//mod with the number according bits
}
int main()
{

	char X;//choice for random
	int Nmachines, SIDs, Dit;//no of machines,size in  bits,pow of 2 for syestem
	cout << "Enter the No.Machines You Want to create::";
	cin >> Nmachines;
	int* M_ID = new int[Nmachines];
	int tmp;
	cout << "Enter The Size of identifiers in bits::";
	cin >> SIDs;
	Dit = pow(2, SIDs) - 1;
	cout << "Do you want to assign machine ids' yourself? (y/n):";
	cin >> X;
	if (X == 'y' || X == 'Y')
	{
		for (int i = 0; i < Nmachines; i++)
		{
		again:
			cout << "Enter the no." << i + 1 << " Machine id:";
			cin >> tmp;
			if (tmp <= Dit)
			{
				M_ID[i] = tmp;
			}
			else
			{
				cout << "Try Again!!" << "Machine id should be less then or Equal to :" << Dit << endl;
				--i;
			}
			for (int j = 0; j < i; j++)
			{
				if (M_ID[i] == M_ID[j])//check for duplicate values
					goto again;//jump to again label
			}
		}
	}
	else if (X == 'n' || X == 'N')
	{
		for (int i = 0; i < Nmachines; i++)
		{
			srand(time(NULL));
		again2:
			tmp = rand() % Dit;//creating machines according to the bits
			M_ID[i] = tmp;
			for (int j = 0; j < i; j++)
			{
				if (M_ID[i] == M_ID[j])
				{
					goto again2;//if duplicate is found jump back
				}
			}
		}
	}
	int key;
	string value;
	Sort(M_ID, Nmachines);//sorting the array through selectionn sort
							//creating machines
	Machine obj;
	obj.in(M_ID, Nmachines);//creating the circular linked list
	obj.C_T();//creating Tree
	string data;//the dat ato be input and stored into the tree
	cout << "\nNOW WE WILL STORE THE DATA(STRING) ENTER 0 to exit or 1 to store string in machine::";
	cin >> tmp;
	if (tmp == 1)
		do {
			cout << "Enter data string::";
			cin >> data;
			obj.find(hashing(data, Dit), data);//hashing the ascii
			cout << "DO YOU WANT TO STORE MORE DATA(STRING) \nENTER 0 to exit\nENTER 1 to store string in machine\nYour Choice::";
			cin >> tmp;//asking for users choice
		} while (tmp == 1);
		//obj.DT(id);
		//obj.T();//view the all the Trees formed
		obj.C_RT(SIDs,Dit);//creating routing table
}