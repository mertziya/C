#include <iostream>
#include <string>
using namespace std;

struct node{  // struct for the each node in the linked list.
    char data;
    node *right;
    node *down;
};


class TwoDLinkedList{
    
private:
    node * head;  // head will always be equal to top_left node until the option '7'.
    
    
public:
    void add_row_sorted(string s);           // creates a 2D n by n matrix.
    
    void displayFullMatrix();                // displays the matrix in order.
    
    void displayFullMatrixReversed();        // displays the matrix in reverse order.
    
    void display_rows_starting_with(char c); // display the rows starting with the given input.
    
    void display_cols_starting_with(char c); // display the columns starting with the given input.
    
    int  delete_rows_starting_with(char c);  // delete the rows starting with the given input, and returns the integer value of how many rows are deleted.
    
    int  delete_cols_starting_with(char c);  //delete the columns starting with the given input, and returns the integer value of how many columns are deleted.
    
    void clear();                            // deletes all the elements in the 2D matrix
    
};
