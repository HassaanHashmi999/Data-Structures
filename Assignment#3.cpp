#include<iostream>
#include <queue>
using namespace std;
//binary Tree
struct node {
    int data;// node data int value
    node* lefty;//left child
    node* righty;//right child
};
//binary search tree node
class Node {
public:
    int value; //data int type for binary search tree
    Node* left;//left child of  node
    Node* right;//right child of a node

    Node()//constructur
    {
        //setting left and right childs to null
        left = NULL;
        right = NULL;
    }
    //another constructor
    Node(int val)// a value is passed and a node is created to place in tree
    {
        value = val;//value of a node is set
    }

};



class Tree//class of a binary search tree
{
private:
    //task 4
    void arrays(Node* root)//the root of the tree is passed 
    {
        cout << "Array 1:";
        arrP1(root);//root is sent to display array 1
        cout << endl;
        cout << "Array 2:";
        arrP2(root);//root sent to another function to display the second array formed
        cout << endl;
    }
    int maxH(Node* node)//height is calculated
    {
        if (node == NULL)
            return -1;//setting height at begininng to negitive 1
        else
        {
            int LH = maxH(node->left);//height of left sub tree
            int RH = maxH(node->right);//height of right sub tree
            //returning the greater height
            if (LH > RH)
                return(LH + 1);
            else return(RH + 1);
        }
    }
    //printing the two arrays formed
    //in the first P1 funtion left sub tree is displayed first then the second while in P2 right subtree is displayed first 
    void arrP1(Node* root) {
        if (root != NULL) {
            cout << root->value << "_";
            arrP1(root->left);
            arrP1(root->right);
        }
    }
    void arrP2(Node* root) {
        if (root != NULL) {
            cout << root->value << "_";
            arrP2(root->right);
            arrP2(root->left);

        }
    }



public:
    Node* root;
    Tree()//constructor
    {
        root = NULL;//setting root to NuLL
    }


    void insert(Node in) //a node is passed with a given data and attached with the tree at the sepcified place
    {
        Node* newNode = new Node(in.value);//new node created with the value of the node passed
        Node* nodePtr;// a node ptr
        if (!root)
            root = newNode;//if tree is empty place at the root position
        else {
            nodePtr = root;//let the node type ptr point at the root
            while (nodePtr != NULL) {
                if (in.value < nodePtr->value)//if value is less then root value making it left child
                {
                    if (nodePtr->left)//if left exists insert C
                    {
                        nodePtr = nodePtr->left;//iterate
                    }
                    else {
                        nodePtr->left = newNode;//insert to tree
                        break;//break loop as node is added
                    }
                }
                else if (in.value > nodePtr->value) //if value is greater then root value making it right child
                {       
                    //same as for left
                    if (nodePtr->right)
                    {
                        nodePtr = nodePtr->right;
                    }
                    else
                    {
                        nodePtr->right = newNode;
                        break;
                    }
                }
                else { cout << "Duplicate value found in tree.\n"; break; }//as it is a binary search tree
            }
        }
    }



    void print() {
        arrP1(root);
    }


    //Task 1
    int arrayin(int arr[], int size)//array is passed and its size
    {
        static int rec = 0;

        Node node(arr[rec]);//a new node is created after every recursion with increment in rec
        rec++;
        insert(node);//node inserted into the tree
        if (rec == size)
            return maxH(root);
        else
            arrayin(arr, size);

    }
    //Task 4
    void arr()
    {
        arrays(root);//public fuction call
    }

};
//node for link list
struct nodel
{
    int dat;
    nodel* next;
};
class list
{
    nodel* head;
    nodel* tail;

public:
    list()
    {
        head = NULL;
        tail = NULL;
    }

    nodel* insert(int x) {
        nodel* newNode = new nodel;
        newNode->dat = x;
        newNode->next = head;
        head = newNode;
        return newNode;
    }
    int create(int inc, node* nod)
    {		// inc is the no. of node list needed to be created 
        list* dep = new list[inc];//a list type array is created 

        int i = inc;//inc is given to iterate
        if (nod == NULL) {
            cout << "The tree is Empty" << endl;
        }
        else {
            queue<node*> q;// a ue is crated
            q.push(nod);//root node is inserted into a list by queue
            dep[i].insert(nod->data);
            --i;// moving on to the next list creation
            while (1) {
                node* temp = q.front();
                q.pop();

                if (temp->lefty != NULL)
                {
                    dep[i].insert(temp->lefty->data);//left into list no.2 and so on while the loop runs
                }
                if (temp->righty != NULL)
                {
                    dep[i].insert(temp->righty->data);//right into list no.2 and so on while the loop runs
                }
                if (temp->righty != NULL && temp->lefty != NULL)
                {

                    q.push(temp->lefty);
                    q.push(temp->righty);

                }
                else 
                    return inc;//height return

                --i;//onto the next list
            }
        }
    }

};




class BTree
{


    int depth(node* node)
    {
        if (node == NULL)
            return 0;
        else
        {
            int LD = depth(node->lefty);//lenght is being added after each recursion
            int RD = depth(node->righty);//same for right
            if (LD > RD)//return the greater lenght to add
                return(LD + 1);
            else return(RD + 1);
        }

    }
    bool isBalanced(node* root) {
        if (root == NULL) {
            return true;
        }
        int hDiff;
        hDiff = depth(root->lefty) - depth(root->righty);//left depth diff righty to check difference
        if (hDiff > 1 || hDiff < -1)  
		{
            return false;
        }
        else 
		{
            return isBalanced(root->lefty) && isBalanced(root->righty);
        }
    }
    int nopaths(node* root, int num)
    {
        static int i = 0;
        int sum = 0;
        if (root == NULL)
        {
            cout << "The tree is empty" << endl;
            return 0;
        }
        else {
            queue<node*> q;
            q.push(root);

            while (1) {
                node* temp = q.front();
                sum += temp->data;
                if (sum > num)
                    sum = 0;

                q.pop();

                if (temp->lefty != NULL)
                    sum += temp->lefty->data;

                if (sum == num)
                {
                    ++i;
                    sum = temp->data;

                }

                if (temp->righty != NULL)
                    sum += temp->righty->data;

                if (sum == num)
                {
                    ++i;
                    sum = temp->data;

                }
                if (temp->righty != NULL && temp->lefty != NULL)
                {
                    q.push(temp->lefty);
                    q.push(temp->righty);
                }
                else
                {
                    return i;
                    break;
                }
            }
        }
    }
public:
    node* root;
    BTree()
    {
        root = NULL;
    }

    bool isempty()
    {
        return(root == NULL);
    }



    node* CreateNode(int data)
    {
        node* newNode = new node();
        if (!newNode)
        {
            cout << "Memory error\n";
            return NULL;
        }
        newNode->data = data;
        newNode->lefty = newNode->righty = NULL;
        return newNode;
    }


    void Insert(int data)
    {

        if (root == NULL) {
            root = CreateNode(data);
            return;
        }
        else {

            queue<node*> q;
            q.push(root);

            while (1) {
                node* temp = q.front();
                q.pop();

                if (temp->lefty != NULL)
                    q.push(temp->lefty);
                else {
                    temp->lefty = CreateNode(data);
                    return;
                }

                if (temp->righty != NULL)
                    q.push(temp->righty);
                else {
                    temp->righty = CreateNode(data);
                    return;
                }
            }
        }
    }

    void display()

    {

        if (root == NULL) {
            cout << "The tree is Empty" << endl;
        }
        else {
            cout << endl << " TREE::" << endl;
            queue<node*> q;
            q.push(root);
            cout << root->data << " ";
            while (1) {
                node* temp = q.front();
                q.pop();

                if (temp->lefty != NULL)
                    cout << temp->lefty->data << " ";
                if (temp->righty != NULL)
                    cout << temp->righty->data << " ";
                if (temp->righty != NULL && temp->lefty != NULL)
                {
                    q.push(temp->lefty);
                    q.push(temp->righty);
                }
                else
                    break;
            }
        }
    }
    bool balence()
    {
        return isBalanced(root);
    }
    int createlist()
    {
        list n;
        return n.create(depth(root), root);

    }
    bool chksubT(BTree T1, BTree T2)
    {
        int chk = 0, chk1 = 1;
        if (T2.root == NULL) {
            cout << "The Tree is Empty" << endl;
        }
        else {

            queue<node*> q1;
            queue<node*> q2;
            q1.push(T1.root);


            while (1)
            {
                node* temp = q1.front();

                if (temp->data == T2.root->data)
                {
                    q2.push(T2.root);
                    while (1) {
                        node* tem = q1.front();
                        node* temp1 = q2.front();

                        q1.pop();
                        q2.pop();

                        if (T1.depth(tem) == T2.depth(temp1))
                        {
                            if (tem->lefty != NULL && temp1->lefty != NULL)
                                if (tem->lefty->data == temp1->lefty->data)
                                    chk = 1;
                                else if (tem->lefty->data != temp1->lefty->data)
                                {
                                    chk1 = 0;
                                }

                            if (tem->righty != NULL && temp1->righty != NULL)
                                if (tem->righty->data == temp1->righty->data)
                                    chk = 1;
                                else if (tem->righty->data != temp1->righty->data)
                                {
                                    chk1 = 0;
                                }

                            if (tem->righty != NULL && tem->lefty != NULL && temp1->righty != NULL && temp1->lefty != NULL)
                            {
                                q1.push(tem->lefty);
                                q1.push(tem->righty);
                                q2.push(temp1->lefty);
                                q2.push(temp1->righty);
                            }
                            else  if (chk == 1 && chk1 == 1)
                            {
                                return 1;
                                break;
                            }
                            else
                            {
                                return 0;
                                break;
                            }
                        }

                    }
                }
                q1.pop();

                if (temp->lefty != NULL)
                {
                    q1.push(temp->lefty);
                }
                else if (temp->righty != NULL)
                {
                    q1.push(temp->righty);
                }
                else
                    break;
            }
        }
    }
    int npaths(int num)
    {
        return nopaths(root, num);
    }
};


int main()
{
    int i = 0, min, dup;
    Node node;
    Tree bst;
    int size, element;
    BTree bt, bt2;
    bt.Insert(3);
    bt.Insert(4);
    bt.Insert(5);
    bt.Insert(1);
    bt.Insert(2);
    bt.Insert(2);
    cout << "Firstly!!!\nCreate Array for Task 1 and 4  " << endl;
    cout << "Enter the size of the array:";
    cin >> size;
    int* arr;
    arr = new int[size];
    int x;
    for (int i = 0; i < size; i++)//task 1
    {
        cout << "Enter " << i + 1 << " Element of array:";
        cin >> element;
        if (i > -1)
        {
            if (element > arr[i - 1])
                arr[i] = element;
            else
            {
                cout << "TRY AGAIN!!!" << endl;
                --i;
            }
        }
    }
    do {
        cout << "1.Task no.1" << endl;
        cout << "2.Task no.2" << endl;
        cout << "3.Task no.3" << endl;
        cout << "4.Task no.4" << endl;
        cout << "5.Task no.5" << endl;
        cout << "6.Task no.6" << endl << "0.EXIT" << endl << "Enter Choice::";
        cin >> x;
        switch (x) {
        case 1:
            cout << "\nHeight of BST created with array::" << bst.arrayin(arr, size) << endl;
            break;
        case 2:
            cout << "The linked list is Created:" << bt.createlist() << endl;//task 2
            break;

        case 3:
            cout << "The Tree is balenced or not::" << bt.balence() << endl;//task 3
            break;

        case 4:
            //task 4 arrays
            cout << "ARRAYS Formed are::" << endl;
            bst.arr();
            break;
            //print to check
        case 5:
            bt2.Insert(4);
            bt2.Insert(1);
            bt2.Insert(2);
            cout << endl << "Is Tree 2 a Sub-Tree of Tree 1::";
            cout << bt.chksubT(bt, bt2) << endl;//task 5
            break;
        case 6:
            int n;
            cout << "Enter the Value::";
            cin >> n;
            cout << "The paths found with sum value given are::" << bt.npaths(n);
            break;
        }

        return 0;




    } while (x != 0);

}
