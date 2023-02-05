#include "mertziya_Ziya_Mert_hw3_myfuncs.h"


static int row = 0; // for the implementation in 'add_row_sorted(s)' function and 'display_reverse'.


void TwoDLinkedList::add_row_sorted(string s){
    int len = (int)s.length();
    node *h1 = new node;
    node *t1 = h1, *n1 = h1;
    n1 -> data = s.at(0);
    n1 = new node;
    for(int i = 1; i < len && s.at(i) != '\r'; i++){ // somehow the last caharacter of some string 's' are '\r' and this breaks the code if i dont check this in the loop. (in THE3 pdf file, it has been said that there will be not white spaces that's why i did not check for '\t', '\n' , ' '...
        n1 -> data = s.at(i);
        t1 -> right = n1;
        t1 = n1;
        n1 = new node;
    } // this loop creates the row.
    
    n1 = NULL; delete n1;
    t1 -> right = NULL;
    
    node *temp1 = h1;
    node *temp1_up = nullptr;
    if(row == 0){head = temp1;} // head is equal to temp1 if this function is called for the first time.
    
    else{ // temp1_up will be equal to 0th column of the row before the temp1.
        temp1_up = head;
        for(int i = 1; i < row; i++){
            temp1_up = temp1_up -> down;
        }
    }
    
    node *temp1_copy = temp1;
    node *temp1_copy2 = temp1;
    node *temp1_up_copy = temp1_up;
    
    while(temp1_copy2 != NULL){ // this loop makes the each column of current row's down goes to NULL.
        temp1_copy2 -> down = NULL;
        temp1_copy2 = temp1_copy2 -> right;
    }
    
    while(temp1_up_copy != NULL && temp1_copy != NULL){ // this loop connects the previous row's down to current row.
        temp1_up_copy -> down = temp1_copy;
        temp1_up_copy = temp1_up_copy -> right;
        temp1_copy = temp1_copy -> right;
    }
    
    node *alpha_ptr = head;
    node *alpha_ptr_up = alpha_ptr; // pointers for checking the alphabetical order.
    node *ptr_head_const = head;
    
    bool check_replacement = true;
    bool if_up = false;
    
    for(int k = 0; k < row && check_replacement; k++){
        if( (int)(temp1 -> data) <= (int)(alpha_ptr -> data) ){ // ASCII number is smaller means  it is alphabetically before
            node *temp1_copy3 = temp1;
            while(temp1 != NULL){ // connects the links in appropriate way.
                temp1 -> down = alpha_ptr;
                temp1_up -> down = NULL;
                if(if_up){alpha_ptr_up -> down = temp1;}
                temp1 = temp1 -> right;
                alpha_ptr = alpha_ptr -> right;
                temp1_up = temp1_up -> right;
                alpha_ptr_up = alpha_ptr_up -> right;
            }
            check_replacement = false; // when this bool equals to false, the for loop will not be called anymore.
            if( (int) (temp1_copy3 -> data) <= (int) (ptr_head_const -> data) ){
                head = temp1_copy3;
            }
        }
        else{
            alpha_ptr = alpha_ptr -> down; // pointers are being updated
            if(if_up){alpha_ptr_up = alpha_ptr_up -> down;} // pointers are being updated
            if_up = true; // alpha_ptr_up should be the previous row of alpha pointer.
        }
    }
    
    row++;
}





void TwoDLinkedList::displayFullMatrix(){ // it simply displays the matrix.
    node *ptr_row = head;
    while(ptr_row != NULL){
        node *ptr_col = ptr_row;
        while(ptr_col != NULL){
            cout << ptr_col -> data;
            ptr_col = ptr_col -> right;
        }
        cout << endl;
        ptr_row = ptr_row -> down;
    }
}





void TwoDLinkedList::displayFullMatrixReversed(){
    int rows = row;
    while(rows > 0){
        node *ptr_reverse = head;
        for(int i = rows; i > 1; i--){  // after the loop ptr_reverse points to last row, if the row isn't printed.
            ptr_reverse = ptr_reverse -> down;
        }
        while(ptr_reverse != NULL){
            cout << ptr_reverse -> data;
            ptr_reverse = ptr_reverse -> right;
        }
        cout << endl;
        rows--;
    }
}





void TwoDLinkedList::display_rows_starting_with(char c){
    node *ptr_startingwith = head;
    while(ptr_startingwith != NULL){
        node *ptr_copy = ptr_startingwith;
        if(ptr_startingwith -> data == c){ // condition for printing.
            while(ptr_copy != NULL){
                cout << ptr_copy -> data;
                ptr_copy = ptr_copy -> right;
            }
            cout << endl;
        }
        
        ptr_startingwith = ptr_startingwith -> down; // updates the pointer.
    }
}




void TwoDLinkedList::display_cols_starting_with(char c){
    node *ptr_startingwith = head;
    while(ptr_startingwith != NULL){
        node *ptr_copy = ptr_startingwith;
        if(ptr_startingwith -> data == c){   // condition for printing.
            while(ptr_copy != NULL){
                cout << ptr_copy -> data << endl;
                ptr_copy = ptr_copy -> down;
            }
            cout << endl;
        }
        ptr_startingwith = ptr_startingwith -> right; // updates the pointer.
    }
}




int TwoDLinkedList::delete_rows_starting_with(char c){
    int deleted_rows = 0;
    node *ptr_delrow = head;                    // row of deletion
    node *ptr_delrow_up = ptr_delrow;           // upper row of deletion
    node *ptr_delrow_down = ptr_delrow -> down; // lower row of deletion
    
    while(ptr_delrow != NULL){
        
        if(ptr_delrow -> data == c){  // condition for deleting the row.
            deleted_rows++;
            node *ptr_next = ptr_delrow;
            node *ptr_delrow_copy = ptr_delrow;
            while(ptr_delrow_copy != NULL){  // deletes the row.
                ptr_next = ptr_next -> right;
                ptr_delrow_copy = NULL;delete ptr_delrow_copy;
                ptr_delrow_copy = ptr_next;
            }
            delete ptr_delrow_copy; delete ptr_next; // deletes the NULL ptr's.
            
            if(ptr_delrow == head){  // if head has deleted it assign a new head.
                head = ptr_delrow_down;
                ptr_delrow = ptr_delrow_down; // updates the deleted row, because it is deleted
            }
            
            else if(ptr_delrow_down == NULL){ // if the final row has been deleted it assigns the previous rows -> down's to NULL
                node *up_copy = ptr_delrow_up;
                while(up_copy != NULL){
                    up_copy -> down = NULL;
                    up_copy = up_copy -> right;
                }
                up_copy = NULL;delete up_copy;
            }
            
            else{  // if a row between first and last row is deleted it connects the previous row to next row.
                node *up_copy = ptr_delrow_up;
                node *down_copy = ptr_delrow_down;
                while(down_copy != NULL){
                    up_copy -> down = down_copy;
                    up_copy = up_copy -> right;
                    down_copy = down_copy -> right;
                }
                up_copy = NULL;delete up_copy;
                down_copy = NULL;delete down_copy;
                ptr_delrow = ptr_delrow_up; // updates the deleted row, because row is deleted.
            }
        }
        ptr_delrow_up = ptr_delrow; // updates the row
        ptr_delrow = ptr_delrow_down; // updates the row
        if(ptr_delrow_down != NULL){ptr_delrow_down = ptr_delrow_down -> down;} // updates the row
        
    }
    ptr_delrow = NULL;delete ptr_delrow; // deletes the unnecessary nodes.
    ptr_delrow_up = NULL; delete ptr_delrow_up; // deletes the unnecessary nodes.
    ptr_delrow_down = NULL; delete ptr_delrow_down; // deletes the unnecessary nodes.
    
    return deleted_rows;
}




int TwoDLinkedList::delete_cols_starting_with(char c){ // same logic with the previous function.
    int deleted_cols = 0;
    node *ptr_delcol = head;
    node *ptr_delcol_pre = ptr_delcol;
    node *ptr_delcol_next = ptr_delcol -> right;
    while(ptr_delcol != NULL){
        
        if(ptr_delcol -> data == c){
            deleted_cols++;
            node *ptr_down = ptr_delcol;
            node *ptr_delcol_copy = ptr_delcol;
            while(ptr_delcol_copy != NULL){
                ptr_down = ptr_down -> down;
                ptr_delcol_copy = NULL;delete ptr_delcol_copy;
                ptr_delcol_copy = ptr_down;
            }
            delete ptr_delcol_copy; delete ptr_down;
            
            if(ptr_delcol == head){
                head = ptr_delcol_next;
                ptr_delcol = ptr_delcol_next;
            }
            
            else if(ptr_delcol_next == NULL){
                node *pre_copy = ptr_delcol_pre;
                while(pre_copy != NULL){
                    pre_copy -> right = NULL;
                    pre_copy = pre_copy -> down;
                }
                pre_copy = NULL;delete pre_copy;
            }
            
            else{
                node *pre_copy = ptr_delcol_pre;
                node *next_copy = ptr_delcol_next;
                while(next_copy != NULL){
                    pre_copy -> right = next_copy;
                    pre_copy = pre_copy -> down;
                    next_copy = next_copy -> down;
                }
                pre_copy = NULL;delete pre_copy;
                next_copy = NULL;delete next_copy;
                ptr_delcol = ptr_delcol_pre;
            }
        }
        ptr_delcol_pre = ptr_delcol;
        ptr_delcol = ptr_delcol_next;
        if(ptr_delcol_next != NULL){ptr_delcol_next = ptr_delcol_next -> right;}
        
    }
    ptr_delcol = NULL;delete ptr_delcol;
    ptr_delcol_pre = NULL; delete ptr_delcol_pre;
    ptr_delcol_next = NULL; delete ptr_delcol_next;
    
    return deleted_cols;
}




void  TwoDLinkedList::clear(){ // it cleans the 2D matrix by deleting all the nodes in it.
    node *head_down = nullptr;
    while(head != NULL){
        head_down = head -> down;
        node *head_right = head;
        node *head1 = head;
        while(head_right != NULL){
            head_right = head_right -> right;
            head1 = NULL; delete head1;
            head1 = head_right;
        }
        delete head1; delete head_right;
        head = head_down;
    }
    delete head;
    delete head_down;
}

