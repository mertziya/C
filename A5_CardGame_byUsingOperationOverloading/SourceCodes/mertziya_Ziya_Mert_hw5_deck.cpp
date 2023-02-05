#include "mertziya_Ziya_Mert_hw5_deck.h"

Deck::Deck() : cards_size(0) { // constructor
    card_array = NULL;
}



Deck::Deck(const Deck &copy){  // deep copy constructor
    card_array = copy.clone();
    cards_size = copy.cards_size;
}



Deck::~Deck(){                 // destructor
    delete [] card_array;
    card_array = NULL;
    cards_size = 0;
}



Card * Deck:: get_array ()     // it gets the *cardarray from the private.
{
    return card_array;
}



int Deck :: get_size() const { return cards_size; } // it gets the cards_size from the private.



Card  *Deck :: clone () const{ // function for deep copy constructor. (makes a clone)
    if(card_array == NULL){
        return card_array;
    }
    Card *clone = new Card[cards_size];
    for(int i = 0; i < cards_size; i++){
        clone[i].name = card_array[i].name;
        clone[i].energy = card_array[i].energy;
    }
    return clone;
}



void Deck :: delete_array()   // for deleting a pointer. (which points to array.) (for '=')
{
    delete [] card_array;
    card_array = NULL;
    cards_size = 0;
}



const Deck & Deck::operator=(const Deck & rhs) // // '=' operator.
{ 
    if(this != &rhs){
        delete_array();
        card_array = rhs.clone();
        cards_size = rhs.cards_size;
    }
    return *this;
}



Deck Deck:: operator+(Card rhs) // Deck + Card operator member function.
{
    Deck temp(*this);
    
    if(card_array == NULL){
        temp.card_array = new Card[1];
        temp.card_array[0].name = rhs.name;
        temp.card_array[0].energy = rhs.energy;
        
    }
    else{
        temp.card_array = new Card[cards_size+1];
        for(int i = 0; i < cards_size ; i++){
            temp.card_array[i].name = card_array[i].name;
            temp.card_array[i].energy = card_array[i].energy;
        }
    }
    temp.card_array[cards_size].name = rhs.name;
    temp.card_array[cards_size].energy = rhs.energy;
    temp.cards_size++;
    return temp;
}



Deck Deck:: operator+(Deck rhs){ // Deck + Deck operator member function.
    Deck temp(*this);
    int combined = cards_size + rhs.cards_size;
    temp.cards_size = combined;
    temp.card_array = new Card[combined];
    for (int i = 0; i < cards_size; i++){
        temp.card_array[i].name = card_array[i].name;
        temp.card_array[i].energy = card_array[i].energy;
    }
    for(int j = cards_size; j < combined; j++){
        temp.card_array[j].name = rhs.card_array[j-cards_size].name;
        temp.card_array[j].energy = rhs.card_array[j-cards_size].energy;
    }
    return temp;
}





ostream &  operator << (ostream & os, Deck & a) // '<<' operator by "cout << 'Deck object';" it prints the object's cardarray's energy and name.
{
    Card *temp;
    temp = a.get_array();
    int temp_size = a.get_size();
    for(int i = 0; i < temp_size; i++){
        
        os << i+1 <<": " << temp[i].name << " - " << temp[i].energy << endl;
    }
    return os;
}




const Deck & Deck :: operator+=(Deck rhs) // Returns the cutted deck (with larger number on the bottom).
{
    *this = *this + rhs;
    return *this;
}



Deck Deck:: operator-(const int & top){  // the removes tha last 'top' card from the deck
    Deck copy(*this);
    if(copy.card_array == NULL){
        return copy;
    }
    else if(top >= copy.cards_size){
        copy.card_array = NULL;
        copy.cards_size = 0;
        return copy;
    }
    else{
        int new_size = copy.cards_size - top;
        copy.card_array = new Card[new_size];
        copy.cards_size = new_size;
        for(int i = 0; i < new_size; i++){
            copy.card_array[i].name = this->card_array[top+i].name;
            copy.card_array[i].energy = this->card_array[top+i].energy;
        }
    }
    return copy;
}



bool operator==(Deck lhs, Deck rhs){ // checks if the total energy of the deck of lhs and rhs is equal and returns true if they are equal.
    Card * c_l = lhs.get_array();
    Card * c_r = rhs.get_array();
    int c_l_s = lhs.get_size();
    int c_r_s = rhs.get_size();
    int sum_l = 0;
    int sum_r = 0;
    for(int i = 0; i < c_l_s;i++){
        sum_l += c_l[i].energy;
    }
    for(int j = 0; j < c_r_s;j++){
        sum_r += c_r[j].energy;
    }
    if(sum_l == sum_r){return true;}
    return false;
}



bool operator <(Deck lhs, Deck rhs)  // returns true if the total energy of lhs is smaller than total energy of rhs.
{
    Card * c_l = lhs.get_array();
    Card * c_r = rhs.get_array();
    int c_l_s = lhs.get_size();
    int c_r_s = rhs.get_size();
    int sum_l = 0;
    int sum_r = 0;
    for(int i = 0; i < c_l_s;i++){
        sum_l += c_l[i].energy;
    }
    for(int j = 0; j < c_r_s;j++){
        sum_r += c_r[j].energy;
    }
    if(sum_l < sum_r){return true;}
    return false;
}



bool operator > (Deck lhs, int rhs){ // returns true if Deck's 'cards_size' is larger than the rhs
    int count = lhs.get_size();
    if(count > rhs){return true;}
    return false;
}



bool operator <= (Card lhs, Deck rhs){ // if the Card "lhs" exist in the Deck "rhs" (same name and same energy at the same time) it returns true.
    int size = rhs.get_size();
    Card *arr = rhs.get_array();
    for(int i = 0; i < size; i++){
        if(arr[i].name == lhs.name && arr[i].energy == lhs.energy){
            return true;
        }
    }
    return false;
}



Card Deck :: operator[](int index) const{  // it gives the 'index'th element of the card_array.
    Deck temp(*this);
    Card *i;
    i = & temp.card_array[index];
    return *i;
}

