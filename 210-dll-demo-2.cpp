//Eduardo Avila
//COMSC - 210 - 5293
//Lab 22 - Upgrade DLL Class

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) {
            cout << "Empty list. No value to delete." << endl;
            return; // Empty list
        }

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
    
    //New method that deletes based on position
    void delete_pos(int position) {
        //First checks if position is valid
        if (position < 0){
            cout << "Invalid position." << endl;
            return;
        }
        if (!head) {
            cout << "Empty list. No position to delete." << endl;
            return;
        }

        Node *temp = head;

        //Move to position
        for (int i = 0; i < position && temp; i++){
            temp = temp -> next;
        }

        //Checks if position is over the list
        if (!temp) {
            cout << "Position is over the list." << endl;
            return;
        }

        if (temp->prev) 
            temp->prev->next = temp->next;
        else 
            head = temp->next;

        if (temp->next) 
            temp->next->prev = temp->prev;
        else 
            tail = temp->prev;

        delete temp;
    }

    //New method to delete head node
    void pop_front(){
        if (!head) {
            cout << "Empty list. No head node to delete." << endl;
            return;
        }

        Node *temp = head;

        head = head -> next;

        if (head)
            head -> prev = nullptr;
        else
            tail = nullptr;

        delete temp;
    }

    //New method to delete tail node
    void pop_back(){
        if (!tail) {
            cout << "Empty list. No tail node to delete." << endl;
            return;
        }
        
        Node *temp = tail;

        tail = tail -> prev;

        if (tail)
            tail -> next = nullptr;
        else
            head = nullptr;

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;

    //Pushing values into list
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);
    list.push_back(20);
    list.push_back(67);

    cout << "Unedited Values: " << endl;
    list.print();

    //delete_pos test
    cout << "Values with 3rd position deleted: " << endl;
    list.delete_pos(2);
    list.print();

    //pop_front test
    cout << "Values with head deleted:" << endl;
    list.pop_front();
    list.print();

    //pop_back test
    cout << "Values with tail deleted:" << endl;
    list.pop_back();
    list.print();

    //delete_val test
    cout << "Value 10 delete: " << endl;
    list.delete_val(10);
    list.print();

    //testing user errors
    cout << "Emptying list: " << endl;
    list.pop_front();
    list.print();

    cout << "Attempting to delete in empty list..." << endl;
    list.pop_front();
    list.pop_back();

    list.delete_pos(1);
    list.delete_pos(-1);

    list.delete_val(67);

    cout << "\nTesting complete. You have survived." << endl;

    return 0;
}
