
#include <iostream> // For basic I/O
#include <string> // For functions such as getline()
#include <fstream> // For file handling
#include <stdlib.h> // For cls and pausing
#include <ctype.h> // For functions such as toupper()
#include <iomanip> // For functions such as setw()
using namespace std;

struct Items {
	int prodID; // Product ID
	string prodName; // Name of Product
	string category; // What type e.g Mouse, Keyboard, PC
	int quantity; // Any Integer
	float price; // Any Number
};

// Declaring Node for Linked list
struct Node {
	Items data;  // Passes Items (structure) as Data
	Node* next; // Recursive pointer
};

// h = head, t = tail, pointers set to global so it can be used in any function
Node* h = NULL;
Node* t = NULL;

// Initial ID number is 1000
int IDnums = 1000;

// Function Declarations
void AddRecord();
void LoadData();
void SearchItem();
void DisplayAllItems();
void UpdateItem();
void deleteItem();

int main() {
	/* Before starting the program, data must be loaded first
	from the file if this is not the first time the system is used.
	*/

	int choice;
	LoadData(); // Loading from files
	do {
		system("CLS");
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(40) << " " << "| Welcome to Group 6 Hardware Inventory Management System |";
		cout << endl;
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(40) << " " << "What do you want to do (1-6): \n\n";
		cout << left << setw(60) << " " << "1. Add new item\n\n";
		cout << left << setw(60) << " " << "2. Search item\n\n";
		cout << left << setw(60) << " " << "3. Display all items\n\n";
		cout << left << setw(60) << " " << "4. Delete item\n\n";
		cout << left << setw(60) << " " << "5. Update item\n\n";
		cout << left << setw(60) << " " << "6. Exit\n\n";
		cout << left << setw(40) << " " << "Please type your selection: ";

		/*
		Throughout the code this will be used as input validation,
		If the user input is not a desired data type, it will keep
		prompting the user in a loop and it will ignore the input from the cin stream.
		*/

		while (!(cin >> choice)) {
			cout << left << setw(60) << " " << "Invalid input. Please enter an integer: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		switch (choice) {
		case 1: AddRecord(); break;
		case 2: SearchItem(); break;
		case 3: DisplayAllItems(); break;
		case 4: deleteItem(); break;
		case 5: UpdateItem(); break;
		case 6: cout << "Exiting program.\n"; break;
		default: cout << "Invalid selection, please try again.\n";
		}
	} while (choice != 6);

	/*
	Due to the limited number of re-attempts in canvas,
	the project title and names of group members
	were added only in the document.
	*/
	cout << left << setw(40) << " " << "----------------------------------------------------------";
	cout << endl;
	cout << left << setw(40) << " " << "| Welcome to Group 6 Hardware Inventory Management System |";
	cout << endl;
	cout << left << setw(40) << " " << "----------------------------------------------------------\n";
	cout << left << setw(40) << " " << "Members: \n";
	cout << left << setw(40) << " " << "Jaiel Johann Perez\n";
	cout << left << setw(40) << " " << "Harry Caraig\n";
	cout << left << setw(40) << " " << "Ethan Wayne Apoderado\n";
	cout << left << setw(40) << " " << "Kenshin Carl Malait\n";	return 0;
}


void AddRecord() {
	/*
	This function will create a node and store user input into a file, it
	will iterate until the user choses to.
	*/
	do {
		Items newItem; // Declaring newItem, a struct of Items
		cin.ignore();
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(60) << " " << " Adding an item... ";
		cout << endl;
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;

		cout << left << setw(40) << " " << "Enter Product Name: ";
		getline(cin, newItem.prodName);

		/*
		This block of code will check if the entered product name already exists.
		This will only execute if there is already existing nodes.
		It creates a new node and copies the contents of the head and checks to see
		if there are any similar names the node. If none is found it traverses to the next node.
		*/
		Node* temp = h;
		while (temp != NULL) {
			if (temp->data.prodName == newItem.prodName) {
				cout << left << setw(40) << " " << "Product already exists\n";
				system("pause");
				return;
			}
			temp = temp->next;
		}
		newItem.prodID = IDnums++; // Increments the product ID by 1 name is valid.

		cout << left << setw(40) << " " << "Enter Category: ";
		getline(cin, newItem.category);
		cout << left << setw(40) << " " << "Enter Product Quantity: ";

		// Input Validation
		while (!(cin >> newItem.quantity)) {
			cout << left << setw(40) << " " << "Invalid input. Please enter an integer: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		cout << left << setw(40) << " " << "Enter Product Price: ";

		// Input Validation
		while (!(cin >> newItem.price)) {
			cout << left << setw(40) << " " << "Invalid input. Please enter a number: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		/*
		This block of code will store every input gathered and store it into a file named "inventory".
		It will be in append mode so it wont overwrite other data.
		Each data member is seperated by spaces to improve visibility when viewing the file.
		*/
		ofstream ItemStream("inventory.txt", ios::app); // opens/creates a file in writing mode with append type
		if (ItemStream.is_open()) {
			ItemStream << newItem.prodID << " "; // Puts data entered into file.
			ItemStream << newItem.prodName << " ";
			ItemStream << newItem.category << " ";
			ItemStream << newItem.quantity << " ";
			ItemStream << newItem.price;
			ItemStream << endl;
			ItemStream.close(); // closes the file
		}
		else {
			cout << left << setw(40) << " " << "Error opening file.\n";
		}

		/*
		This block of code will create a new node pointer in heap to add to the list.
		Every data inputed is stored into the node and points it NULL (initially).
		*/
		Node* new_node = new Node;
		new_node->data = newItem;
		new_node->next = NULL;

		/*
		Based on whether a node already exists, if the list is empty,
		it sets both head and tail to the new node to be initialized.
		If there is a list, it updates the tail to point to the new node
		establishing a connection. This was done so that we link properly
		the new node and the existing node.
		*/
		if (h == NULL) {
			h = new_node;
			t = new_node;
		}
		else {
			t->next = new_node;
			t = new_node;
		}

		/*
		This code will simply prompt the user to try again.
		*/
		while (true)
		{
			char choice;
			cout << endl;
			cout << left << setw(40) << " " << "Would You Like To Add Another Item? : ";
			cin >> choice;
			cout << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << left << setw(40) << " " << "Invalid input. Please enter Y or N.\n";
				continue;
			}

			if (toupper(choice) == 'Y') {
				break;
			}
			else if (toupper(choice) == 'N') {
				cout << left << setw(60) << " " << "Going Back To Main Menu\n";
				return;
			}
			else {
				cout << left << setw(40) << " " << "Invalid Input. Please choose between 'Y' & 'N' " << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
	} while (true); // infinite loop until it returns
}

void LoadData() {
	/*
	To combat the issue of old nodes not carrying over when the system closes
	(because creating a new node makes a new list instead of adding to the old one), this function was created.
	It simply takes the data stored in the file which is seperated by spaces and adds them into a node.
	*/
	ifstream file("inventory.txt"); // opens file in reading mode (to read only).
	if (!file) {
		cout << "No File Found.\n";
		return;
	}

	Items temp; // defines a temporary structure to store file data.
	int maxID = 1000; // Sets the maximum ID to be 1000 (resets ID counter).

	// stores the data in the file seperated by blankspace to temp and stopping at a new line
	while (file >> temp.prodID >> temp.prodName >> temp.category >> temp.quantity >> temp.price) {
		/*
		This block of code is similar to add record in creating nodes.
		*/
		Node* new_node = new Node;
		new_node->data = temp;
		new_node->next = NULL;

		if (h == NULL) {
			h = new_node;
			t = new_node;
		}
		else {
			t->next = new_node;
			t = new_node;
		}
		/*
		This block of code simply finds the largest ID number and stores it to the maximum ID number
		*/
		if (temp.prodID >= maxID) {
			maxID = temp.prodID;
		}
	}
	file.close();

	IDnums = maxID + 1; // Sets up the next ID number for the adding of items.
}

void SearchItem() {
	/*
	The purpose of this function is to search every item and its
	data members in the node and compare it with a search key (ID).
	*/
	int prodID;

jump:
	cout << left << setw(40) << " " << "----------------------------------------------------------";
	cout << endl;
	cout << left << setw(60) << " " << "Searching an item...";
	cout << endl;
	cout << left << setw(40) << " " << "----------------------------------------------------------";
	cout << endl;
	cout << left << setw(40) << " " << "Enter the Product ID: ";

	while (!(cin >> prodID)) { // Input Validation
		cout << left << setw(40) << " " << "Invalid input. Please enter an integer: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	/*
	This block of code sets up a temporary node named inventory so that it doesnt interfere with the main list.
	*/
	Node* inventory = h; // points the inventory node to head Node
	bool found = false; // initial value if the node was not found

	/*
	This block of code traverses the entire list starting from the
	head and compares its ID member to the entered search key.
	Then, it displays the found data at that specific node.
	*/
	while (inventory != NULL) {
		if (inventory->data.prodID == prodID) { // If it is equal

			// displays data related node
			cout << left << setw(60) << " " << "Product Found!\n\n";
			cout << left << setw(40) << " " << "Product ID: " << inventory->data.prodID << endl;
			cout << left << setw(40) << " " << "Product Name: " << inventory->data.prodName << endl;
			cout << left << setw(40) << " " << "Category: " << inventory->data.category << endl;
			cout << left << setw(40) << " " << "Quantity: " << inventory->data.quantity << endl;
			cout << left << setw(40) << " " << "Price: " << inventory->data.price << endl << endl;
			found = true; // Node found
			break; // breaks the loop
		}
		inventory = inventory->next; // if not found traverses to the next
	}

	// if it reaches the end without finding the ID
	if (!found) {
		cout << endl;
		cout << left << setw(60) << " " << "Product with ID " << prodID << " Not Found.\n\n";
	}

	cin.ignore();

	while (true) // Prompts to try again
	{
		char choice;
		cout << left << setw(40) << " " << "Would You Like To Search For Another Item? : ";
		cin >> choice;
		cout << endl;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << left << setw(60) << " " << "Invalid Input. Please Enter Y or N.\n";
			continue;
		}

		if (toupper(choice) == 'Y') {
			goto jump;
		}
		else if (toupper(choice) == 'N') {
			cout << left << setw(60) << " " << "Going Back To Main Menu\n\n";
			return;
		}
		else {
			cout << left << setw(60) << " " << "Invalid Input. Please Choose Between 'Y' & 'N' " << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}

}

void DisplayAllItems() {
	/*
	This function simply displays every item in the list starting from the head node.
	*/
	Node* inventory = h;  // New node was created so that it doesnt interfere with the main list

	if (inventory == NULL) { // Returns if the list is empty
		cout << left << setw(40) << " " << "Inventory Is Empty.\n";
		system("pause");
		return;
	}

	cout << left << setw(40) << " " << "----------------------------------------------------------";
	cout << endl;
	cout << left << setw(60) << " " << "Displaying Inventory...";
	cout << endl;
	cout << left << setw(40) << " " << "----------------------------------------------------------";
	cout << endl;

	cout << left << setw(40) << " " << setw(15) << "ID"
		<< setw(25) << "Product Name"
		<< setw(20) << "Category"
		<< setw(10) << "Quantity"
		<< setw(10) << "Price"
		<< endl;

	/*
	This block of code simply traverses the list and displays every data on it.
	*/
	while (inventory != NULL) {
		cout << left << setw(40) << " " << setw(15) << inventory->data.prodID
			<< setw(25) << inventory->data.prodName
			<< setw(20) << inventory->data.category
			<< setw(10) << inventory->data.quantity
			<< setw(10) << inventory->data.price
			<< endl;
		inventory = inventory->next; // move to next node
	}

	system("pause");
}

void UpdateItem() {
	/*
	The purpose of this function is to change the characteristics of an item but not its ID number.
	Display function was called for reference of the user.
	After the operation, the updated list will also be reflected in the file.
	*/
	while (true) {
		cout << left << setw(40) << " " << "For reference: ";
		cout << endl;
		DisplayAllItems(); // displays for reference
		int searchID;

		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(60) << " " << "Updating an Item...";
		cout << endl;
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(40) << " " << "Enter Product ID to update: ";
		cin >> searchID;

		/*
		Update node was created to not interfere with the main list.
		*/
		Node* update = h;

		/*
		This block of code traverses the entire list and compares it with the ID entered by the user.
		If found, it prompts the user to enter new data members for that specific node.
		Then, the file is updated by rewriting the entire list so that it has no conflictions with
		the data members after the updated item.
		*/
		while (update != NULL) { // continues while it reaches the end
			if (update->data.prodID == searchID) { // Id compared if equal with search key 

				// if found prompts the user for new input for that data item
				cin.ignore();
				cout << left << setw(40) << " " << "Enter new Product Name : ";
				getline(cin, update->data.prodName);

				cout << left << setw(40) << " " << "Enter new Category: ";
				getline(cin, update->data.category);

				cout << left << setw(40) << " " << "Enter new Quantity: ";
				while (!(cin >> update->data.quantity)) { // Input Validation
					cout << left << setw(60) << " " << "Invalid input. Please enter an integer: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}
				cout << left << setw(40) << " " << "Enter new Price: ";
				while (!(cin >> update->data.price)) { // Input Validation
					cout << left << setw(60) << " " << "Invalid input. Please enter an integer: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}

				/*
				This opens a file in overwrite mode so we can rewrite the entire contents of the file.
				*/
				ofstream file("inventory.txt");
				if (file.fail()) {
					cout << "ERROR: Unable to open file.";
					return;
				}

				/*
				A new node rewrite is created so that it doesnt interfere with the main node
				*/
				Node* rewrite = h;

				/*
				This block of code simply traverses the entire list and for
				every node encountered, it is stored in the file (including the updated node).
				*/
				while (rewrite != NULL) {
					file << rewrite->data.prodID << " " // Puts new set of Nodes into file
						<< rewrite->data.prodName << " "
						<< rewrite->data.category << " "
						<< rewrite->data.quantity << " "
						<< rewrite->data.price << endl;
					rewrite = rewrite->next; // moves to next node
				}
				file.close();

				cout << endl;
				cout << left << setw(40) << " " << "Product updated successfully and saved to file.\n";
				break;
			}
			// If not found try the other node
			update = update->next;
		}
		if (update == NULL) { // if it reaches the end without finding the Node
			cout << left << setw(60) << " " << "Product with ID " << searchID << " not found.\n";
		}


		while (true) // prompts the user again
		{
			char choice;
			cout << left << setw(40) << " " << "Would You Like To Update Another Item? : ";
			cin >> choice;
			cout << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << left << setw(60) << " " << "Invalid Input. Please Enter Y or N.\n";
				continue;
			}

			if (toupper(choice) == 'Y') {
				break;
			}
			else if (toupper(choice) == 'N') {
				cout << left << setw(60) << " " << "Going Back To Main Menu\n\n";
				return;
			}
			else {
				cout << left << setw(60) << " " << "Invalid Input. Please Choose Between 'Y' & 'N' " << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
	}
}


void deleteItem() {
	/*
	The purpose of this function is to delete an item from an existing list.
	It compares the ID member of each node to the entered ID.
	Once the data is deleted, it rewrites the entire file.
	*/
	while (true) {
		cout << left << setw(40) << " " << "For reference: ";
		cout << endl;
		DisplayAllItems();
		int deleteKey;

		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;
		cout << left << setw(60) << " " << "Deleting an Item...";
		cout << endl;
		cout << left << setw(40) << " " << "----------------------------------------------------------";
		cout << endl;

		cout << left << setw(40) << " " << "Insert ID No. to Delete: ";
		cin >> deleteKey;

		/*
		Two nodes are created, temp and prev.
		temp stores the main list so that it doesnt interfere with the main node
		while prev's function is to point to the node previous to temp.
		*/
		Node* temp = h;
		Node* prev = NULL;

		if (h == NULL) { // if there are no nodes
			cout << left << setw(60) << " " << "The list is Empty.\n";
			return;
		}

		/*
		This block of code was made to check if the
		deleted item was the first node in the list.
		The head node in this case will be updated (globally) as
		it will serve as the new head.
		*/
		if (temp != NULL && temp->data.prodID == deleteKey) {
			h = temp->next; // This line severs the connection between the first node and the second node

			if (h == NULL) { // if there are no nodes sets tail to NULL
				t = NULL;
			}

			delete temp; // deletes the first node
			system("CLS");
			cout << left << setw(60) << " " << "Successfully deleted.\n";
		}
		else {
			/*
			This block of code continues traversing the list.
			*/
			while (temp != NULL && temp->data.prodID != deleteKey) {

				/*
				prev is set up so that it places itself in the position of temp,
				and after this temp advances forward.
				*/
				prev = temp;
				temp = temp->next;
			}
			// if it reaches the end and still haven't found the key
			if (temp == NULL) {
				cout << left << setw(60) << " " << "Item not found\n";
				continue;
			}

			/*
			This block of code is for cases such as the deleted node is the last node.
			The previous node will be the new tail (tail is updated globally)
			*/
			if (temp == t) {
				t = prev;  // sets the tail as the previous node
				if (t != NULL)
					t->next = NULL; // disconnects last node
			}
			else {
				/*
				Finally, this will be the last case, if the item
				to be deleted is in the middle of the head and tail,
				This block of code will link the next of temporary to the
				previous node. This severs the connection for the current
				temp node.
				*/
				prev->next = temp->next;
			}

			delete temp; // deletes the current temp node
			cout << left << setw(40) << " " << "Item deleted successfully.\n";
		}

		/*
		Similar to the update function, it opens a file so that it can be overwritten.
		*/
		ofstream file("inventory.txt"); // opens a file in writing mode (can be overwritten)
		if (file.fail()) {
			cout << "ERROR";
			return;
		}

		/*
		This creates a new node traverse so that it doesnt affect the main list.
		The block of code following that simply traverses the list
		amd stores each data member into the file (overwriting the previous list).
		*/
		Node* traverse = h;
		while (traverse != NULL) { // traverses while it reaches the end
			file << traverse->data.prodID << " " // puts the new data in the file
				<< traverse->data.prodName << " "
				<< traverse->data.category << " "
				<< traverse->data.quantity << " "
				<< traverse->data.price << endl;
			traverse = traverse->next; // moves to the next node
		}

		file.close();
		cout << left << setw(60) << " " << "Inventory Updated.\n";
		DisplayAllItems(); // for reference of deleted node

	jump2:
		while (true) // Prompts the user to try again
		{
			char choice;
			cout << left << setw(40) << " " << "Would You Like To Delete Another Item? : ";
			cin >> choice;
			cout << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << left << setw(60) << " " << "Invalid Input. Please Enter Y or N.\n";
				continue;
			}

			if (toupper(choice) == 'Y') {
				break;
			}
			else if (toupper(choice) == 'N') {
				cout << left << setw(60) << " " << "Going Back To Main Menu\n\n";
				return;
			}
			else {
				cout << left << setw(60) << " " << "Invalid Input. Please Choose Between 'Y' & 'N' " << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
	}
}
