#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct node{  // struct for linked list, contains one value and one pointer.
    char ch;
    node *next;
};

void read_files(string & filename1, string & filename2, ifstream & input1, ifstream & input2){ // function for reading the files.
    
    do{
        cout << "Please enter the file 1 name: ";
        cin >> filename1;
        input1.open(filename1.c_str());
    }while(input1.fail());  // asks the user to enter an input until the program opens the first file
        
    do{
        cout << "Please enter the file 2 name: ";
        cin >> filename2;
        input2.open(filename2.c_str());
    }while(input2.fail()); // asks the user to enter an input until the program opens the second file

}

void print(node *head, const int list_num){ // function for printing the all elements of linked list.
    node *temp = head; // creates a  temporary pointer.
    while(temp != NULL){ // loops until the temp points to nothing(null).
        char out = temp -> ch;
        cout << out;
        temp = temp -> next; // temp is updated in order to reach the next element of the linked list
    }
    cout << endl;
}

void deletion(node * &head, char c, const int list_num){ // function for deleting an element from the linked list.
    node *ptr = head; // there is no head -> ch value, but head -> next equals beginning of linked list.
    bool check = true;
    while (ptr != NULL){
        node *current = ptr -> next; // current -> ch is the first element of linked list.
        if(current == NULL){ // important line, because if current is null the program will give the error of "EXC_BAD_ACCESS" (current -> ch is not being created)
            ptr = ptr -> next;
        }
        else if(current -> ch == c){
            ptr -> next = current -> next;
            check = false;
        }
        else{
            ptr = ptr -> next;
            current = NULL;
        }
    }
    if(check == true){ // check is true if no deletion is happened.
        cout << "No deletion as the value " << c << " was not found in the list\n"<< endl;
    }
    else{ // if the deletion is happened.
        cout << "Deleting all occurrences of " << c << " in List" << list_num << "." <<endl;
        cout << "The current content of List" << list_num << " is: ";
        print(head, list_num);
        cout << endl;
    }
}

void insertion(node * &h, char insert_arg, char find_arg2,const int listnum){ // function for inserting a character after the first occurance of another character.
    bool find = false;
    node * temp = h -> next; // temp contains the first ch value of the linked list
    while(temp != NULL && !find){
        node * temp_new = new node; // creates a node which doesn't linked to anywhere.
        if(temp -> ch == find_arg2){ // links the node between the two another nodes.
            temp_new -> ch = insert_arg;
            temp_new -> next = temp -> next;
            temp -> next = temp_new;
            find = true;
        }
        temp_new = NULL;
        temp = temp -> next;
    }
    if(find == false){ // if there is no base point for inserting the new char, new char is going to be inserted to the beggining of the linked list.
        node * temp_new = new node;
        temp_new -> ch = insert_arg;
        temp_new -> next = h -> next;
        h -> next = temp_new;
        temp_new = NULL;
    }
    if(find){ // gives the output if the new char is inserted after the base point
        cout << "Inserting " << insert_arg << " after " << find_arg2 << " in List"<< listnum <<".\n";
        cout << "The node with "<< insert_arg<< " has been inserted after the first occurrence of a node with " << find_arg2 << " value.\n";
        cout << "The current content of List" << listnum <<" is: ";
        print(h, listnum);
        cout << endl;
    }
    else{  // gives the output if there is no base point.
        cout << "Inserting " << insert_arg << " after " << find_arg2 << " in List"<< listnum<<".\n";
        cout << "The node with " << find_arg2 << " value does not exist. "<<
        "Therefore, Inserting " << insert_arg << " at the beginning of the list.\n";
        cout << "The current content of List" << listnum << " is: ";
        print(h, listnum);
        cout << endl;
    }
}

void sim(node * &h1, node * &h2, const int list_num1, const int list_num2){ // gives the similarity between the 2 lists. (the characters must be same and must be on the same place.)
    cout << "Displaying the contents of the two lists:\n";
    cout << "List1: "; print(h1, list_num1);
    cout << "List2: "; print(h2, list_num2);
    
    int sim_count = 0;
    node *temp1 = h1 -> next;
    node *temp2 = h2 -> next;
    while( temp1 != NULL && temp2 != NULL){
        if(temp1 -> ch == temp2 -> ch){
            sim_count++;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    cout << "There is/are " << sim_count << " letter(s) matched in the same positions in both lists.\n" << endl;
}
    
void list_builder(node * &h1, node * &t1, node * &n1, ifstream & input1){ // function for building one linked list.
    char ch1;
    bool check = true;
    while(input1 >> ch1){ // in the THE2 file it is assumed to be there are only (lowercase letter) characters, that is why this is the best method.
        if(check){
            n1 = new node;
            n1 -> ch = ch1;
            h1 = n1; t1 = n1;
            check = false;
        }
        else{
            n1 = new node;
            n1 -> ch = ch1;
            t1 -> next = n1;
            t1 = t1 -> next;
        }
    }
    n1->next = NULL;
    node *begin = new node;
    begin -> next = h1;
    h1 = begin;
    input1.close();
}


int main(){
    string filename1, filename2;
    ifstream input1, input2;
    char argument = '0', argument2 = '0';
    node *h1 = nullptr, *t1 = nullptr, *n1 = nullptr;
    node *h2 = nullptr, *t2 = nullptr, *n2 = nullptr;
    
    read_files(filename1, filename2, input1, input2);
    list_builder(h1, t1, n1, input1);
    list_builder(h2, t2, n2, input2);
    h2 -> ch = 0;
    cout << "List1: ";
    print(h1,1);
    cout << "List2: ";
    print(h2,2);
    cout << endl;
    
    string word;
    string command;
    while(true){ // infinite loop until the user enters the "exit" operation.
        bool operation_check = false; // operation is false until the command and the argument(s) are correct.
        while(operation_check == false){
            stringstream input;
            cout << "Enter a command and its corresponding argument(s), if any: ";
            cin >> word;
            command = word;
            getline(cin,word,'\n');
            input << word;
            
            if(command == "del1" || command == "del2"){
                input >> argument;
                if(islower(argument)){ operation_check = true;}
                else {cout << "Invalid arguments.\n" << endl;}
            }
            
            else if(command == "insert1" || command == "insert2"){
                input >> argument >> argument2;
                if(islower(argument) && islower(argument2)){ operation_check = true; }
                else{cout << "Invalid arguments.\n" << endl;}
            }
            
            else if(command == "sim"){
                operation_check = true;
            }
            else if(command == "exit"){
                cout << "Clearing the two lists and saying Goodbye!\n" <<endl;
                while(h1 != NULL){
                    node * ptr2 = h1;
                    h1 = h1 -> next;
                    delete ptr2;
                    ptr2 = NULL;
                }
                delete h1;
                while(h2 != NULL){
                    node * ptr3 = h2;
                    h2 = h2 -> next;
                    delete ptr3;
                    ptr3 = NULL;
                }
                delete h2;
                return 0;
            }
            else {
                cout << "Invalid command.\n" << endl;
                
            }
        }
        if(command == "del1"){deletion(h1,argument,1);}
        else if(command == "del2"){deletion(h2,argument,2);}
        else if(command == "insert1"){insertion(h1,argument,argument2,1);}
        else if(command == "insert2"){insertion(h2,argument,argument2,2);}
        else if(command == "sim"){sim(h1,h2,1,2);}
        
    }
    return 0;
}
