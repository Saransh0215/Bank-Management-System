#include <iostream>
#include <windows.h>
#include <sstream>
#include <time.h>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

//This is the log linked list
struct log
{
	string LOG;
	log * down;
	log()
	{
		LOG = "";
		down = NULL;
	}
};

struct log_handler
{
	int Account_Number;
	log_handler * next;
	log * down;
	log_handler()
	{
		Account_Number = 0;
		next = NULL;
		down = NULL;
	}
};

log_handler *head = NULL;

void deletion_for_log(int account_number)
{
	if(head==NULL)
		return;

	if(head->Account_Number==account_number)
	{
		log_handler *temp=head;
		head=head->next;
		delete temp;
		return;
	}
	log_handler *temp=head;
	while(temp->next!=NULL)
	{
		if(temp->next->Account_Number==account_number)
		{
			log_handler *n=temp->next->next;
			log_handler *todel=temp->next;
			temp->next=n;
			delete todel;
			return;
		}
	}
}

void insertion_for_log(int account_number)	//Insertion of Account number in linked list
{
	log_handler *newnode = new log_handler();
	log_handler *temp = NULL;
	log_handler *temp2 = NULL;
	if (head == NULL)
	{
		newnode->Account_Number = account_number;
		newnode->next = NULL;
		newnode->down = NULL;
		head = newnode;
	}
	else
	{
		for (temp2 = head; temp2->next != NULL; temp2 = temp2->next) {}

		temp = new log_handler();
		temp->Account_Number = account_number;
		temp2->next = temp;
		temp->next = NULL;
		temp->down = NULL;
	}
}

void insert_log(int number, string nn)	//Insertion of transaction logs in linked list. The string is the full "Amount ...withdrawn"
{
	log_handler *temp2 = NULL;	// This will become the head of the accounts head list
	log *temp = NULL;	//This will become the first transaction of the transaction list if it is not empty.
	log *newnode = new log();
	newnode->LOG = nn;
	newnode->down = NULL;
	for (temp2 = head; temp2 != NULL; temp2 = temp2->next)
	{
		if (temp2->Account_Number == number)
		{
			if (temp2->down == NULL)
			{
				temp2->down = newnode;
			}
			else
			{
				temp = temp2->down;
				while (temp->down != NULL)
				{
					temp = temp->down;
				}

				temp->down = newnode;
			}

			return;
		}
	}

	cout << "                                          Account number not found" << endl;
	return;
}

void display(int acc_num)	//Display Function 
{
	log_handler *temp = NULL;
	log *temp2 = NULL;
	if (head == NULL)
	{
		return;
	}

	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->Account_Number == acc_num)
		{
			for (temp2 = temp->down; temp2 != NULL; temp2 = temp2->down)
			{
				cout << "                                 -> " << temp2->LOG << endl;
			}
		}
	}
}

int display1(int acc_num)	//This will find whether any logs for the user exist or not 
{
	log_handler *temp = NULL;
	log *temp2 = NULL;
	if (head == NULL)
	{
		return 2;
	}

	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->Account_Number == acc_num)
		{
			if (temp->down != NULL)
				return 1;
			else
				return 0;
		}
	}

	return 2;
}

//AVL code Start
struct node
{
	string Name;
	string AADHAR;
	string Gender;
	string Type;
	int Acc_Number;
	string pin;
	int bala;
	node *right, *left;
	int height;
	node()
	{
		Name = "";
		AADHAR = "";
		Gender = "";
		Type = "";
		Acc_Number = 0;
		pin = "";
		bala = 0;
		right = NULL;
		left = NULL;
		height = 0;
	}
};
node *temp, *temp1, *temp2, *tempcell = NULL;
// Max Function
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// Height Function
int height(node *temp)
{
	if (temp == NULL)
	{
		return 0;
	}

	return 1 + max(height(temp->left), height(temp->right));
}

// Left Rotation Function
node* left_rotation(node *temp2)
{
	temp1 = temp2->right;
	temp2->right = temp1->left;
	temp1->left = temp2;

	return temp1;
}

// Right Rotation Function
node* right_rotation(node *temp2)
{
	temp1 = temp2->left;
	temp2->left = temp1->right;
	temp1->right = temp2;

	return temp1;
}

// right left rotation
node* right_left_rotation(node *temp)
{
	temp->right = right_rotation(temp->right);
	return left_rotation(temp);
}

// Left right rotation
node* left_right_rotation(node *temp)
{
	temp->left = left_rotation(temp->left);
	return right_rotation(temp);
}

//Minimum Function{
node* min(node *temp)	//this is getting right successor
{
	if (temp == NULL)
	{
		return NULL;
	}

	if (temp->left == NULL)
	{
		return temp;
	}
	else
	{
		return min(temp->left);
	}
}

// balance function
node* balance(node *temp)
{
	if (temp == NULL)
	{
		return NULL;
	}

	if (height(temp->left) - height(temp->right) > 1)
	{
		if (height(temp->left->left) >= height(temp->left->right))	//left left case
		{
			temp = right_rotation(temp);
		}
		else
		{
			temp = left_right_rotation(temp);	//left right case
		}
	}
	else if (height(temp->right) - height(temp->left) > 1)
	{
		if (height(temp->right->right) >= height(temp->right->left))	//left left case
		{
			temp = left_rotation(temp);
		}
		else
		{
			temp = right_left_rotation(temp);	//left rgiht case
		}
	}

	return temp;
}

/////////////////////////////////////////////////////////////////////////////////////////END of main Functions in AVL

node* insertion(node *temp, string name, string aad, string gen, string type, int account_no, string PIN, int bal)
{
	if (temp == NULL)
	{
		temp = new node();
		temp->Name = name;
		temp->AADHAR = aad;
		temp->Gender = gen;
		temp->Type = type;
		temp->Acc_Number = account_no;
		temp->pin = PIN;
		temp->bala = bal;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}

	if (account_no < temp->Acc_Number)
	{
		temp->left = insertion(temp->left, name, aad, gen, type, account_no, PIN, bal);	//normal insertion in bst
		if (height(temp->left) - height(temp->right) == 2)
		{
			if (account_no < temp->left->Acc_Number)	//left left
			{
				temp = right_rotation(temp);
			}
			else
			{
				temp = left_right_rotation(temp);	//left right
			}
		}
	}

	if (account_no > temp->Acc_Number)	//normal insertion in bst1
	{
		temp->right = insertion(temp->right, name, aad, gen, type, account_no, PIN, bal);
		if (height(temp->right) - height(temp->left) == 2)
		{
			if (account_no > temp->right->Acc_Number)	//right right
			{
				temp = left_rotation(temp);
			}
			else
			{
				temp = right_left_rotation(temp);	//right left
			}
		}
	}

	return temp;
}

node* deletion(node *temp, int x)	//this is 99.9% gfg delete function
{
	if (temp == NULL)
	{
		return temp;
	}
	else if (x < temp->Acc_Number)
	{
		temp->left = deletion(temp->left, x);
	}
	else if (x > temp->Acc_Number)
	{
		temp->right = deletion(temp->right, x);
	}
	else if (temp->left && temp->right)
	{
		tempcell = min(temp->right);
		temp->Acc_Number = tempcell->Acc_Number;
		temp->right = deletion(temp->right, tempcell->Acc_Number);
	}
	else
	{
		tempcell = temp;
		if (temp->left == NULL)
		{
			temp = temp->right;
		}
		else if (temp->right == NULL)
		{
			temp = temp->left;
		}

		delete tempcell;
	}	//idhar tak normal deletion hai
	//from here we balance the AVL
	if (temp != NULL)
	{
		temp = balance(temp);
	}

	return temp;
}

int findMax(node *root)
{
	if (root == NULL)
	{
		return 0;
	}

	temp = root;
	while (temp->right != NULL)
	{
		temp = temp->right;
	}

	return temp->Acc_Number;
}

bool search(node *temp, int x)
{
	while (temp != NULL)
	{
		if (x > temp->Acc_Number)
			temp = temp->right;
		else if (x < temp->Acc_Number)
			temp = temp->left;
		else
			return true;
	}

	return false;
}

//inputs are the root of the tree and the account number. This will print the details of a particular bank account
void print_data(node *temp, int x)	///////////////////////// Print Function
{
	while (temp != NULL)
	{
		// pass right subtree as new tree
		if (x > temp->Acc_Number)
			temp = temp->right;

		// pass left subtree as new tree
		else if (x < temp->Acc_Number)
			temp = temp->left;
		else
		{
			cout << "        ####################################################################################################################################" << endl;
			cout << endl;
			cout << "          " << "ACC_Number" << "                 " << "NAME" << "                   " << "AADHAR" << "                     " << "GENDER" << "            " << "Type" << "          " << "Balance" << endl;
			cout << endl;
			cout << "        ####################################################################################################################################" << endl;
			cout << endl;
			cout << "             ";
			cout << temp->Acc_Number;
			cout << "            ";
			cout << setw(18) << temp->Name;
			cout << "           ";
			cout << temp->AADHAR;
			cout << "                ";
			cout << temp->Gender;
			cout << "                ";
			cout << temp->Type;
			cout << "             ";
			cout << temp->bala << endl;
			return;
		}
	}

	cout << "                              Account not found!" << endl;
	return;
}

//this will print all the account details present in the AVL. Inorder traversal hai ye basically
void print_for_admin(node *temp)	////////////////////////// print For order function
{
	if (temp == NULL)
		return;

	if (temp->left != NULL)
	{
		print_for_admin(temp->left);
	}

	cout << "             ";
	cout << temp->Acc_Number;
	cout << "            ";
	cout << setw(18) << temp->Name;
	cout << "           ";
	cout << temp->AADHAR;
	cout << "                ";
	cout << temp->Gender;
	cout << "                ";
	cout << temp->Type;
	cout << "         ";
	cout << temp->pin;
	cout << "          ";
	cout << temp->bala << endl;
	if (temp->right != NULL)
	{
		print_for_admin(temp->right);
	}
}

int deposit(node *temp, int acc_num, string PIN, int bal)	///////////////////////// deposit Balance
{
	while (temp != NULL)
	{
		if (acc_num > temp->Acc_Number)
		{
			temp = temp->right;
		}
		else if (acc_num < temp->Acc_Number)
		{
			temp = temp->left;
		}
		else
		{
			if (temp->pin == PIN)
			{
				temp->bala = temp->bala + bal;
			}
			else if (temp->pin != PIN)
			{
				return -1;
			}

			return 1;
		}
	}

	return 0;
}

int with_draw(node *temp, int acc_num, string PIN, int bal)	/////////////////////////  with_draw balance
{
	while (temp != NULL)
	{
		if (acc_num > temp->Acc_Number)
		{
			temp = temp->right;
		}
		else if (acc_num < temp->Acc_Number)
		{
			temp = temp->left;
		}
		else
		{
			if (temp->pin == PIN)
			{
				if ((temp->bala < bal))
				{
					return -1;
				}
				else
				{
					temp->bala = temp->bala - bal;
				}
			}
			else if (temp->pin != PIN)
			{
				return -2;
			}

			return 1;
		}
	}

	return 0;
}

int change_info(node *temp, string name, string aad, string gender, string type, int acc_num, string PIN)	///////////////////////// Change Info
{
	while (temp != NULL)
	{
		if (acc_num > temp->Acc_Number)
		{
			temp = temp->right;
		}
		else if (acc_num < temp->Acc_Number)
		{
			temp = temp->left;
		}
		else
		{
			if (temp->Acc_Number == acc_num)
			{
				temp->Name = name;
				temp->AADHAR = aad;
				temp->Gender = gender;
				temp->pin = PIN;
				temp->Type = type;
			}

			return 1;
		}
	}

	return 0;
}

int check_acc_pin(node *temp, int acc_num, string PIN)	///////////////////////// check acc &PIn number
{
	while (temp != NULL)
	{
		if (acc_num > temp->Acc_Number)
		{
			temp = temp->right;
		}
		else if (acc_num < temp->Acc_Number)
		{
			temp = temp->left;
		}
		else
		{
			if (temp->pin == PIN)
			{
				return 1;
			}
			else if (temp->pin != PIN)
			{
				return -1;
			}
		}
	}

	return 0;
}

bool aadharcheck(string aad)
{
	for (int i = 0; i < 13; i++)
	{
		if (i == 4 || i == 8)
		{
			if (aad[i] != ' ')
				return false;
		}
		else
		{
			if (((int)(aad[i]) >= 48) && ((int)(aad[i]) <= 57))
				continue;
			else
				return false;
		}
	}

	return true;
}

int main();
node *root = NULL;
int sleep_value = 2500;
string admin_pswd = "1122";
string staff_pswd = "2233";

int create_Acc()
{
	string full_name;
	string aad;
	string Acc_type;
	string g;
	int acc_no;
	string pin;
	long long Balance;
	int load = 0;
	int a = 1;
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                            Create User Account" << endl;
	cout << endl;
	cout << "                                            Enter Customer's Full Name : ";
	cin.ignore();
	getline(cin, full_name);
	cout << endl;
	cout << "                                            Enter AADHAR (XXXX XXX XXXX) : ";
	getline(cin, aad);
	while (!aadharcheck(aad))
	{
		cout << "                                            That is the wrong input" << endl;
		cout << "                                            Enter AADHAR (XXXX XXX XXXX) : ";
		getline(cin, aad);
	}

	cout << endl;
	cout << "                                            Enter Gender  (M/F) : ";
	getline(cin, g);
	while (g != "M" && g != "F")
	{
		cout << "                                            Please enter M for Male or F for female" << endl;
		cout << "                                            Enter Gender  (M/F) : ";
		cin >> g;
	}

	cout << endl;
	cout << "                                            Enter Account Type (C/S) : ";
	cin >> Acc_type;
	while (Acc_type != "C" && Acc_type != "S")
	{
		cout << "                                            Please enter C for current or S for Savings" << endl;
		cout << "                                            Enter Account Type (C/S) : ";
		cin >> Acc_type;
	}

	cout << endl;
	load = findMax(root);
	acc_no = load + 1;
	cout << "                                            Your Account Number is : " << acc_no << endl;
	cout << endl;
	cout << "                                            Enter Pin : ";
	cin.ignore();
	getline(cin, pin);
	cout << endl;

	jump2:
		cout << "                                            Enter Balance (Min:500) : ";
	cin >> Balance;
	if (Balance >= 500)
	{
		goto jump3;
	}
	else
	{
		cout << "                                            Minimum Balance is 500Rs. " << endl;
		goto jump2;
	}

	jump3:
		root = insertion(root, full_name, aad, g, Acc_type, acc_no, pin, Balance);	//insertion(root)
	insertion_for_log(acc_no);
	return 1;
}

void displayByDate(int date, string month)
{
	log_handler *temp = NULL;
	log *temp2 = NULL;
	if (head == NULL)
	{
		return;
	}

	for (temp = head; temp != NULL; temp = temp->next)
	{
		for (temp2 = temp->down; temp2 != NULL; temp2 = temp2->down)
		{
			string k = temp2->LOG;
			string delim = " ";	// delimiter

			int pos = 0;
			string token1;	// define a string variable
			vector<string> alpha;

			// use find() function to get the position of the delimiters
			while ((pos = k.find(delim)) != string::npos)
			{
				token1 = k.substr(0, pos);	// store the substring
				alpha.push_back(token1);
				k.erase(0, pos + delim.length()); /*erase() function store the current positon and move to next token. */
			}

			if (stoi(alpha[8]) == date && alpha[7] == month)
			{
				cout << "                                 -> Account number in concern: " << temp->Account_Number << " ; " << temp2->LOG << endl;
			}
		}
	}
}

void admin_panel()
{
	string b;
	int admin_delete_cin;
	int admin_search_cin;
	int result_admin_1;
	int result_admin_2;
	int result_admin_3;
	int result_admin_4;
	int admin_return;
	int date;
	string month;
	int acc_1;
	string pin_1;
	string aad_1;
	string gen_1;
	string acc_type_1;
	string new_aad_1;
	string new_pin_1;
	string new_acc_1;
	int admin_logs_cin;

	jump2:
		system("cls");
	system("Color B");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       	********************************************" << endl;
	cout << "                                                       	*************ADMIN|||PANEL******************" << endl;
	cout << "                                                       	********************************************" << endl;
	cout << "                                                       	*Press 1 To Create Account            	   *" << endl;
	cout << "                                                       	*Press 2 To Delete Account            	   *" << endl;
	cout << "                                                       	*Press 3 To Search Account            	   *" << endl;
	cout << "                                                       	*Press 4 To Show List of All Accounts 	   *" << endl;
	cout << "                                                       	*Press 5 To Edit Information          	   *" << endl;
	cout << "                                                       	*Press 6 To Show Logs of Accounts     	   *" << endl;
	cout << "                                                        *Press 7 To Show Logs of Accounts by date  *" << endl;
	cout << "                                                       	*Press 8 To Go Back to Main Menu           *" << endl;
	cout << "                                                       	********************************************" << endl;
	cout << "                                                       	Enter an Option : ";
	cin >> b;
	if (b == "1")
	{
		admin_1: system("cls");
		create_Acc();
		admin_2: cout << endl;
		cout << "                                            Press 1 to create another account or Press 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 1)
		{
			goto admin_1;
		}
		else
		{
			cout << "                                            Wrong input, please input 1 or 8: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_2;
		}
	}
	else if (b == "2")
	{
		admin_3: system("cls");
		cout << "                                         Enter the Account Number to Delete :";
		cin >> admin_delete_cin;
		cout << endl;
		result_admin_1 = search(root, admin_delete_cin);
		if (result_admin_1 == 1)
		{
			cout << "                                         Account number Found....!!!" << endl;
			root = deletion(root, admin_delete_cin);
			deletion_for_log(admin_delete_cin);
			cout << "                                         Account is Deleted....!!!" << endl;
		}
		else
		{
			cout << "                                         Account not found ....!!!" << endl;
		}

		admin_4: cout << "                                         Press 2 to Delete another account or Press 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 2)
		{
			goto admin_3;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 2 or 8 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_4;
		}
	}
	else if (b == "3")
	{
		admin_5: system("cls");
		cout << "                                         Enter the Account Number to Search : ";
		cin >> admin_search_cin;
		result_admin_2 = search(root, admin_search_cin);
		if (result_admin_2 == 1)
		{
			cout << endl;
			cout << "                                         User Found..!!" << endl;
			cout << endl;
			print_data(root, admin_search_cin);
			cout << endl;
		}
		else if (result_admin_2 == 0)
		{
			cout << endl;
			cout << endl;
			cout << "                                         User not found..!!" << endl;
			cout << endl;
			cout << endl;
		}

		cout << endl;
		admin_6: cout << endl;
		cout << endl;
		cout << "                                         Press 3 to Search another account or Press 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 3)
		{
			goto admin_5;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 3 or 8 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_6;
		}
	}
	else if (b == "4")
	{
		admin_7: system("cls");
		cout << "        ####################################################################################################################################" << endl;
		cout << endl;
		cout << "          " << "ACC_Number" << "                 " << "NAME" << "                   " << "AADHAR" << "                     " << "GENDER" << "            " << "Type" << "          " << "PIN" << "          " << "BALANCE" << endl;
		cout << endl;
		cout << "        ####################################################################################################################################" << endl;
		cout << endl;
		print_for_admin(root);
		admin_8: cout << endl;
		cout << endl;
		cout << "                                         Press 4 to Show list of accounts or Press 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 4)
		{
			goto admin_7;
		}
		else
		{
			cout << "                                         IInvalid Input. Please enter 4 or 8 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_8;
		}
	}
	else if (b == "5")
	{
		admin_9: system("cls");
		cout << "                                            Change Information of Account " << endl << endl;
		cout << "                                            Enter User Account Number : ";
		cin >> acc_1;
		result_admin_3 = check_acc_pin(root, acc_1, pin_1);
		if (result_admin_3 == 0)
		{
			cout << "                                            Account is not Present...!!!" << endl;
			goto admin_10;
		}
		cout << endl;
		cout << "                                            Enter User Account PIN number : ";
		cin.ignore();
		getline(cin, pin_1);
		result_admin_3 = check_acc_pin(root, acc_1, pin_1);
		if (result_admin_3 == 1)
		{
			cout << endl;
			cout << "                                            Enter New Name / previous Name : ";
			getline(cin, new_acc_1);
			cout << endl;
			cout << "                                            Enter New Aadhar / Previous Aadhar : ";
			getline(cin, new_aad_1);
			while (!aadharcheck(new_aad_1))
			{
				cout << "                                            That is the wrong input" << endl;
				cout << "                                            Enter New Aadhar / Previous Aadhar : ";
				getline(cin, new_aad_1);
			}

			cout << endl;
			cout << "                                            Enter Gender (M/F): ";
			getline(cin, gen_1);
			while (gen_1 != "M" && gen_1 != "F")
			{
				cout << "                                            Please enter M for Male or F for female" << endl;
				cout << "                                            Enter Gender  (M/F) : ";
				cin >> gen_1;
			}

			cout << endl;
			cout << "                                            Enter Account Type C/S : ";
			cin >> acc_type_1;
			while (acc_type_1 != "C" && acc_type_1 != "S")
			{
				cout << "                                            Please enter C for current or S for Savings" << endl;
				cout << "                                            Enter Account Type (C/S) : ";
				cin >> acc_type_1;
			}

			cout << endl;
			cout << "                                            Enter New PIN / Previous PIN : ";
			cin.ignore();
			getline(cin, new_pin_1);
			change_info(root, new_acc_1, new_aad_1, gen_1, acc_type_1, acc_1, new_pin_1);
			cout << endl;
			cout << "                                            Account information is Sucessfully Changed" << endl;
		}
		else if (result_admin_3 == -1)
		{
			cout << "                                            PIN is Incorrect...!!!" << endl;
		}
		else
		{
			cout << "                                            Account is not Present...!!!" << endl;
		}

		admin_10: 
		cout << endl;
		cout << endl;
		cout << "                                            Press 5 to Change other Account info or Press 8 to return to ADMIN PANEL:  ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 5)
		{
			goto admin_9;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 5 or 8 onl: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_10;
		}
	}
	else if (b == "6")
	{
		admin_11: system("cls");
		cout << "                                         Enter Account Number: ";
		cin >> admin_logs_cin;
		result_admin_4 = display1(admin_logs_cin);
		print_data(root, admin_logs_cin);
		if (result_admin_4 == 1)
		{
			cout << "" << endl;
			cout << "" << endl;
			display(admin_logs_cin);
		}
		else if (result_admin_4 == 2)
		{
			cout << "" << endl;
			cout << "" << endl;
			cout << "                                     The account does not exist" << endl;
		}
		else
		{
			cout << endl << endl;
			cout << "                                 No logs found" << endl;
		}

		admin_12: cout << endl;
		cout << "                                 Press 6 to Check Logs of  another account or Press 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 6)
		{
			goto admin_11;
		}
		else if (admin_return == 8)
		{
			goto jump2;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 6 or 8 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_12;
		}
	}
	else if (b == "7")
	{
		admin_20: system("cls");
		cout << endl;
		cout << "                                           Enter the date: ";
		cin >> date;
		cout << "                                           Enter the month:";
		cin.ignore();
		getline(cin, month);
		cout << endl;
		cout << endl;
		displayByDate(date, month);
		cout << endl;
		cout << endl;
		admin_18: cout << "                                           Please Enter 7 to search for another date or 8 to return to ADMIN PANEL: ";
		cin >> admin_return;
		if (admin_return == 8)
		{
			goto jump2;
		}
		else if (admin_return == 7)
		{
			goto admin_20;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 8 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto admin_18;
		}
	}
	else if (b == "8")
	{
		main();
	}
	else
	{
		cout << "                                                        That is an invalid input, please enter a number between 0 and 9: ";
		Sleep(sleep_value);
		system("cls");
		goto jump2;
	}
}

void user_panel(int acc_no, string pin_no)
{
	int user_acc_no = acc_no;
	string user_pin_no = pin_no;
	int user_amount_to_dep;
	int user_amount_to_wdraw_1;
	string c;
	int user_return;
	int result_user_2;
	int result_user_3;
	int result_user_4;
	int trash;

	jump3:
		system("cls");
	system("Color B");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *************USER|||PANEL*************" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *Press 1 To Check Account Info      *" << endl;
	cout << "                                                       *Press 2 To Deposit Cash            *" << endl;
	cout << "                                                       *Press 3 To Withdraw Cash           *" << endl;
	cout << "                                                       *Press 4 To Check Logs              *" << endl;
	cout << "                                                       *Press 5 To Go Back to Main Menu    *" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       Enter an Option : ";
	cin >> c;
	if (c == "1")
	{
		system("cls");
		print_data(root, user_acc_no);
		cout << endl << endl;
		staff_2:
			cout << "                                         Press 5 to return to USER PANEL: ";
		cin >> user_return;
		if (user_return == 5)
		{
			goto jump3;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 5 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto staff_2;
		}
	}
	else if (c == "2")
	{
		user_3: system("cls");
		cout << "                                         Enter the amount to deposit : ";
		cin >> user_amount_to_dep;
		cout << endl << endl;
		cout << "                                                   Status "
		"BEFORE"
		" Depositing Amount in ACCOUNT" << endl;
		cout << endl;
		print_data(root, user_acc_no);
		result_user_2 = deposit(root, user_acc_no, user_pin_no, user_amount_to_dep);
		cout << endl;
		cout << endl;
		cout << "                                                   Status "
		"AFTER"
		" Depositing Amount in ACCOUNT" << endl;
		cout << endl;
		print_data(root, user_acc_no);
		cout << endl;
		cout << endl;
		time_t now = time(0);
		char *dt = asctime(localtime(&now));
		dt[strlen(dt) - 1] = '\0';
		string str1 = to_string(user_amount_to_dep);
		string add = "Amount " + str1;
		string add1 = add + " has been deposited at " + dt;
		cout << "                                         Amount " << user_amount_to_dep << " has been Deposited in Account Number " << user_acc_no << endl;
		insert_log(user_acc_no, add1);
		cout << endl;
		cout << endl;

		user_4: cout << "                                         Press 2 to Deposit again or 5 to return to USER PANEL: ";
		cin >> user_return;
		if (user_return == 2)
		{
			goto user_3;
		}
		else if (user_return == 5)
		{
			goto jump3;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 2 or 5 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto user_4;
		}
	}
	else if (c == "3")
	{
		user_5: system("cls");
		cout << "                                         Enter The Amount to be withdrawn : ";
		cin >> user_amount_to_wdraw_1;
		result_user_3 = with_draw(root, user_acc_no, user_pin_no, user_amount_to_wdraw_1);
		if (result_user_3 == -1)
		{
			cout << endl << endl;
			cout << "                                                     Account Balance is Insufficient. Redirecting to main menu.";
			Sleep(sleep_value);
			goto jump3;
		}

		trash = deposit(root, user_acc_no, user_pin_no, user_amount_to_wdraw_1);
		cout << endl << endl;
		cout << "                                                   Status "
		"BEFORE"
		"WITHDRAWING Amount from ACCOUNT" << endl;
		cout << endl;
		print_data(root, user_acc_no);
		result_user_3 = with_draw(root, user_acc_no, user_pin_no, user_amount_to_wdraw_1);
		cout << endl;
		cout << endl;
		cout << "                                                   Status "
		"AFTER"
		"WITHDRAWING Amount from ACCOUNT" << endl;
		cout << endl;
		print_data(root, user_acc_no);
		cout << endl;
		cout << endl;
		time_t now = time(0);
		char *dt = asctime(localtime(&now));
		dt[strlen(dt) - 1] = '\0';
		string str1 = to_string(user_amount_to_wdraw_1);
		string add2 = "Amount " + str1;
		string add3 = add2 + " has been Withdrawn at " + dt;
		cout << "                                         Amount " << user_amount_to_wdraw_1 << " has been Withdraw from Account Number " << user_acc_no << endl;
		insert_log(user_acc_no, add3);
		cout << endl;
		cout << endl;

		user_6: cout << "                                         Press 3 to Withdraw again or 5 to return to USER PANEL: ";
		cin >> user_return;
		if (user_return == 3)
		{
			goto user_5;
		}
		else if (user_return == 5)
		{
			goto jump3;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 3 or 5 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto user_6;
		}
	}
	else if (c == "4")
	{
		user_7: system("cls");
		result_user_4 = display1(user_acc_no);
		print_data(root, user_acc_no);
		if (result_user_4 == 1)
		{
			cout << "" << endl;
			cout << "" << endl;
			display(user_acc_no);
		}
		else
		{
			cout << endl << endl;
			cout << "                                         Logs Not Found....!!!" << endl << endl;
		}

		user_8: cout << endl;
		cout << endl;
		cout << "                                   Press 5 to return to USER PANEL: ";
		cin >> user_return;
		if (user_return == 5)
		{
			goto jump3;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter only 5: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto user_8;
		}
	}
	else if (c == "5")
	{
		main();
	}
	else
	{
		cout << "                                                       That is an invalid input, please enter a number between 0 and 6.";
		Sleep(sleep_value);
		system("cls");
		goto jump3;
	}
}

void valid_user()
{
	int acc_no;
	string pin_no;
	int checker;
	bool z;
	int y;

	user_1:
		system("cls");
	cout << "                                         Enter account number: ";
	cin >> acc_no;
	z = search(root, acc_no);
	if (z == false)
	{
		cout << endl;
		cout << "                                         Account not Found!" << endl;
		Sleep(sleep_value);
		system("cls");
		goto user_2;
	}

	cout << "                                         Enter Account PIN : ";
	cin.ignore();
	getline(cin, pin_no);
	y = check_acc_pin(root, acc_no, pin_no);
	if (y == -1)
	{
		cout << endl;
		cout << "                                         PIN is Incorrect" << endl;
		Sleep(sleep_value);
		system("cls");
		goto user_2;
	}
	else
		goto user_3;

	user_2:
		system("cls");
	cout << "                                         Press 1 to try again or 2 to return to Main menu: ";
	cin >> checker;
	if (checker == 1)
	{
		goto user_1;
	}
	else if (checker == 2)
	{
		main();
	}
	else
	{
		cout << "                                         Invalid Input. Please enter 1 or 2 only: " << endl;
		Sleep(sleep_value);
		system("cls");
		goto user_2;
	}

	user_3:
		user_panel(acc_no, pin_no);
}

void atm_panel()
{
	string d;
	int atm_acc_no;
	string atm_pin_no;
	int atm_amount_to_wdraw;
	int atm_amount_to_dep;
	int result_atm;
	int atm_return;
	bool z;
	int y;
	int trash;

	jump4:
		system("cls");
	system("Color B");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *******************ATM*****************" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *Press 1 To Withdraw Cash             *" << endl;
	cout << "                                                       *Press 2 To Deposit Cash              *" << endl;
	cout << "                                                       *Press 3 To Go Back to Main Menu      *" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       Enter an Option : ";
	cin >> d;
	if (d == "1")
	{
		atm_1: system("cls");
		cout << "                                         Enter account number: ";
		cin >> atm_acc_no;
		z = search(root, atm_acc_no);
		if (z == false)
		{
			cout << endl;
			cout << "                                         Account not Found!" << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_2;
		}

		cout << "                                         Enter Account PIN : ";
		cin.ignore();
		getline(cin, atm_pin_no);
		y = check_acc_pin(root, atm_acc_no, atm_pin_no);
		if (y == -1)
		{
			cout << endl;
			cout << "                                         PIN is Incorrect" << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_2;
		}

		cout << "                                         Enter the amount to withdraw : ";
		cin >> atm_amount_to_wdraw;
		cout << endl << endl;
		result_atm = with_draw(root, atm_acc_no, atm_pin_no, atm_amount_to_wdraw);
		if (result_atm == -1)
		{
			cout << endl << endl;
			cout << "                                                     Account Balance is Insufficient. Redirecting to ATM menu.";
			Sleep(sleep_value);
			goto jump4;
		}

		trash = deposit(root, atm_acc_no, atm_pin_no, atm_amount_to_wdraw);
		cout << "                                                   Status "
		"BEFORE"
		" WIITHDRAWING Amount from ACCOUNT" << endl;
		cout << endl;
		print_data(root, atm_acc_no);
		cout << endl;
		cout << endl;
		result_atm = with_draw(root, atm_acc_no, atm_pin_no, atm_amount_to_wdraw);
		if (result_atm == 1)
		{
			cout << "                                                   Status "
			"AFTER"
			" WITHDRAWING Amount from ACCOUNT" << endl;
			cout << endl;
			print_data(root, atm_acc_no);
			cout << endl;
			cout << endl;
			time_t now = time(0);
			char *dt = asctime(localtime(&now));
			dt[strlen(dt) - 1] = '\0';
			string str1 = to_string(atm_amount_to_wdraw);
			string add = "Amount " + str1;
			string add1 = add + " has been withdrawn at " + dt;
			cout << "                                         Amount " << atm_amount_to_wdraw << " has been withdrawn from Account Number " << atm_acc_no << endl;
			insert_log(atm_acc_no, add1);
		}

		cout << endl;
		cout << endl;
		atm_2: cout << "                                         Press 1 to withdraw from another account or 4 to return to ATM: ";
		cin >> atm_return;
		if (atm_return == 1)
		{
			goto atm_1;
		}
		else if (atm_return == 4)
		{
			goto jump4;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 1 or 4 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_2;
		}
	}
	else if (d == "2")
	{
		atm_3: system("cls");
		cout << "                                         Enter account number: ";
		cin >> atm_acc_no;
		z = search(root, atm_acc_no);
		if (z == false)
		{
			cout << endl;
			cout << "                                         Account not Found!" << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_4;
		}

		cout << "                                         Enter Account PIN : ";
		cin.ignore();
		getline(cin, atm_pin_no);
		y = check_acc_pin(root, atm_acc_no, atm_pin_no);
		if (y == -1)
		{
			cout << endl;
			cout << "                                         PIN is Incorrect" << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_4;
		}

		cout << "                                         Enter the amount to deposit : ";
		cin >> atm_amount_to_dep;
		cout << endl << endl;
		cout << "                                                   Status "
		"BEFORE"
		" Depositing Amount in ACCOUNT" << endl;
		cout << endl;
		print_data(root, atm_acc_no);
		result_atm = deposit(root, atm_acc_no, atm_pin_no, atm_amount_to_dep);
		cout << endl;
		cout << endl;
		if (result_atm == 1)
		{
			cout << "                                                   Status "
			"AFTER"
			" Depositing Amount in ACCOUNT" << endl;
			cout << endl;
			print_data(root, atm_acc_no);
			cout << endl;
			cout << endl;
			time_t now = time(0);
			char *dt = asctime(localtime(&now));
			dt[strlen(dt) - 1] = '\0';
			string str1 = to_string(atm_amount_to_dep);
			string add = "Amount " + str1;
			string add1 = add + " has been deposited at " + dt;
			cout << "                                         Amount " << atm_amount_to_dep << " has been Deposited in Account Number " << atm_acc_no << endl;
			insert_log(atm_acc_no, add1);
		}

		cout << endl;
		cout << endl;
		atm_4: cout << "                                         Press 2 to Deposit amount in another account or 4 to return to ATM menu: ";
		cin >> atm_return;
		if (atm_return == 2)
		{
			goto atm_3;
		}
		else if (atm_return == 4)
		{
			goto jump4;
		}
		else
		{
			cout << "                                         Invalid Input. Please enter 2 or 4 only: " << endl;
			Sleep(sleep_value);
			system("cls");
			goto atm_2;
		}
	}
	else if (d == "3")
	{
		main();
	}
	else
	{
		cout << "                                                       That is an invalid input, please enter a number between 0 and 4.";
		Sleep(sleep_value);
		system("cls");
		goto jump4;
	}
}

void readFile()
{
	ifstream Database;
	Database.open("Database.txt");
	char mychar;
	string k;
	if (Database.is_open())
	{
		while (Database)
		{
			mychar = Database.get();
			k = k + mychar;
		}
	}

	string delim = "*";	// delimiter

	int pos = 0;
	string token1;	// define a string variable
	vector<string> alpha;
	vector<vector < string>> beta;

	// use find() function to get the position of the delimiters
	while ((pos = k.find(delim)) != string::npos)
	{
		token1 = k.substr(0, pos);	// store the substring
		alpha.push_back(token1);
		k.erase(0, pos + delim.length()); /*erase() function store the current positon and move to next token. */
	}

	pos = 0;
	delim = ";";
	for (auto it: alpha)
	{
		vector<string> gamma;
		while ((pos = it.find(delim)) != string::npos)
		{
			token1 = it.substr(0, pos);	// store the substring
			gamma.push_back(token1);
			it.erase(0, pos + delim.length()); /*erase() function store the current positon and move to next token. */
		}

		beta.push_back(gamma);
	}

	for (auto it: beta)
	{
		int acc_no = 0;
		for (auto kt: it)
		{
			if (kt == it[0])
			{
				vector<string> delta;
				delim = ":";
				pos = 0;
				while ((pos = kt.find(delim)) != string::npos)
				{
					token1 = kt.substr(0, pos);	// store the substring
					delta.push_back(token1);
					kt.erase(0, pos + delim.length()); /*erase() function store the current positon and move to next token. */
				}

				root = insertion(root, delta[0], delta[1], delta[2], delta[3], stoi(delta[4]), delta[5], stoi(delta[6]));
				acc_no = stoi(delta[4]);
				//cout<<"Insertion due to input file"<<endl;
				insertion_for_log(acc_no);
			}
			else
			{
				insert_log(acc_no, kt);
			}
		}
	}
}

void writeToFile(log_handler *temp)
{
	ofstream Database;
	Database.open("Database.txt", ios::out | ios::trunc);
	Database << "*";

	while (temp != NULL)
	{
		node *y = root;
		int x = temp->Account_Number;
		while (y != NULL)
		{
			if (y->Acc_Number > x)
			{
				y = y->left;
			}
			else if (y->Acc_Number < x)
			{
				y = y->right;
			}
			else
			{
				log *h = temp->down;
				string k;
				while (h != NULL)
				{
					k = k + h->LOG + ";";
					h = h->down;
				}

				Database << y->Name << ":" << y->AADHAR << ":" << y->Gender << ":" << y->Type << ":" << y->Acc_Number << ":" << y->pin << ":" << y->bala << ":" << ";" << k << "*";
				break;
			}
		}

		temp = temp->next;
	}
}

int main()
{
	readFile();
	ofstream Database;
	Database.open("Database.txt", ios::trunc);
	string a;
	string b;
	//system("MODE 150, 40");
	jump1:
		cout << "\n";
	cout << "\n";
	system("cls");
	system("Color B");
	cout << "\n";
	cout << "                   ____              _      __  __                                                   _      _____           _                  " << endl;
	cout << "                  |  _ \\            | |    |  \\/  |                                                 | |    / ____|         | |                 " << endl;
	cout << "                  | |_) | __ _ _ __ | | __ | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ___   " << endl;
	cout << "                  |  _</ _` | '_ \\| |/ / | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\  " << endl;
	cout << "                  | |_) | (_| | | | |<| |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_   ____) | |_| \\__ \\ ||  __/ | | | | | " << endl;
	cout << "                  |____/ \\__,_|_| |_|_|\\_\\ |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_| " << endl;
	cout << "                                                                      __/ |                                        __/ |                       " << endl;
	cout << "                                                                     |___/                                        |___/                        " << endl;
	cout << "                                                                                                                                               " << endl;
	cout << "\n" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       **********LOGIN||PANEL**********" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       *Press 1 For ADMIN Login       *" << endl;
	cout << "                                                       *Press 2 For USER Login        *" << endl;
	cout << "                                                       *Press 3 For ATM Service       *" << endl;
	cout << "                                                       *Press 4 To  Exit              *" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "\n" << endl;
	cout << "                                                       Enter Your Choice : ";
	cin >> a;
	if (a == "1")
	{
		jump2: system("cls");
		system("Color B");
		cout << "\n";
		cout << "\n";
		cout << "                                                       Enter Admin Pin : ";
		cin >> b;
		if (b == admin_pswd)
		{
			admin_panel();
		}
		else
		{
			cout << "                                                       That is the wrong pin. Please Try again.";
			Sleep(sleep_value);
			goto jump2;
		}
	}
	else if (a == "2")
	{
		jump3: system("cls");
		system("Color B");
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "\n";
		valid_user();
	}
	else if (a == "3")
	{
		atm_panel();
	}
	else if (a == "4")
	{
		writeToFile(head);
		exit(0);
	}
	else
	{
		cout << "                                                       That is an invalid input. Please input an integer between 0 and 5.";
		Sleep(sleep_value);
		goto jump1;
	}
}
