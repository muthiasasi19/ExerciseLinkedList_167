#include <iostream>
#include <string>
using namespace std;

// change the initial current to muthia
// change the initial previous to marsa

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
    Node* prev;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode(int rollno, string name);
    bool search(int rollno, Node** muthia, Node** marsa);
    bool listEmpty();
    bool delNode(int rollno);
    void traverse();
};


void CircularLinkedList::addNode(int rollno, string name) { // implementasi fungsi addNode() dalam kelas DoubleLinkedList untuk menambah node baru
    int rollno;
    string name;

    Node* newNode = new Node;  // mengalokasikan memory untuk new node
    newNode->rollNumber = rollno; // menetapkan nilai data field utk new node
    newNode->name = name;

    // add node at the beginning 
    if (LAST == NULL || rollno <= LAST->rollNumber) {
        if (LAST != NULL && rollno == LAST->rollNumber) {
            cout << "\nData yang ditambahkan sudah tersedia" << endl;
            return;
        }
        newNode->next = LAST;		// Membuat  next fields dari new node menjadi Last 
        if (LAST != NULL)
            LAST->next = newNode;	//membuat previous Last ke new node
        newNode->prev= NULL;		//membuat previous field new node menjadi Null
        LAST = newNode;			//membuat Last menjadi new node
        return;
    }


   // add node in the middle 
    Node* muthia = LAST;			// membuat current ke first node 
    Node* marsa = NULL;			//membuat previous tmenjadi Null
    while (muthia->next != NULL && muthia->next->rollNumber < rollno)
    {
        marsa = muthia;			// membuat previous menjadi current
        muthia = muthia->next;	// membuat current point to the next
    }


    newNode->next = muthia->next;	//Membuat  next fields dari new node menjadi next current 
    newNode->prev = muthia;		// membuat previous dari newnode menjadi current point
    if (muthia->next != NULL)
        muthia->next->prev = newNode;
    muthia->next = newNode;		
  

}

bool CircularLinkedList::search(int rollno, Node** marsa, Node** muthia) {
    *marsa = LAST->next;
    *muthia = LAST->next;
    while (*muthia != LAST) {
        if (rollno == (*muthia)->rollNumber) {
            return true;
        }
        *marsa = *muthia;
        *muthia = (*muthia)->next;
    }
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}



bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}


bool CircularLinkedList::delNode(int rollno) {
    Node* marsa;
    Node* muthia;

    if (search(rollno, &marsa, &muthia)) {
        if (muthia == LAST->next) { // Beginning of the list
            if (LAST == LAST->next) { // Only one node in the list
                LAST = NULL;
            }
            else {
                LAST->next = muthia->next;
            }
        }
        else if (muthia == LAST) { // End of the list
            marsa->next = LAST->next;
            LAST = marsa;
        }
        else { // Between two nodes in the list
            marsa->next = muthia->next;
        }

        delete muthia;
        return true;
    }
    else {
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* muthiaNode = LAST->next;
        while (muthiaNode != LAST) {
            cout << muthiaNode->rollNumber << " " << muthiaNode->name << endl;
            muthiaNode = muthiaNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";

            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                int rollno;
                string name;
                cout << "Enter roll number: ";
                cin >> rollno;
                cout << "Enter name: ";
                cin >> name;
                obj.addNode(rollno, name);
                break;
            }
            case '2': {
                int rollno;
                cout << "Enter roll number: ";
                cin >> rollno;
                if (obj.delNode(rollno)) {
                    cout << "Record deleted" << endl;
                }
                else {
                    cout << "Record not found" << endl;
                }
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}