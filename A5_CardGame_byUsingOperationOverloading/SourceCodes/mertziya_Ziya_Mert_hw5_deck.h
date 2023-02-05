#include <iostream>
#include <string>
#include <sstream>
using namespace std;


struct Card{
    string name;
    int energy;
};

class Deck{
private:
    
    Card *card_array;
    int cards_size;
    
public:
    
    Deck();                           // constructor.
    
    Deck(const Deck &temp);           // deep copy constructor.
    
    ~Deck();                          // destructor.
    
    Card * get_array();               // it gets the *cardarray from the private.
    
    int get_size() const;             // it gets the cards_size from the private.
    
    void delete_array();              // for deleting a pointer. (which points to array.) (for '=')
    
    Card * clone() const;             // function for deep copy constructor. (makes a clone)
    
    const Deck & operator=(const Deck &rhs); // '=' operator.
    
    Deck operator+(Card rhs);         // Deck + Card operator member function.
    
    Deck operator+(Deck rhs);         // Deck + Deck operator member function.
    
    const Deck & operator+=(Deck rhs);// Returns the cutted deck (with larger number on the bottom).
    
    Deck operator-(const int &top);   // the removes tha last 'top' card from the deck
    
    Card operator[](int index) const; // it gives the 'index'th element of the card_array.

    
};


ostream &  operator << (ostream & os, Deck & a); // '<<' operator by "cout << 'Deck object';" it prints the object's cardarray's energy and name.

bool operator==(Deck lhs, Deck rhs); // checks if the total energy of the deck of lhs and rhs is equal and returns true if they are equal.

bool operator<(Deck lhs, Deck rhs); // returns true if the total energy of lhs is smaller than total energy of rhs.

bool operator>(Deck lhs, int rhs);   // returns true if Deck's 'cards_size' is larger than the rhs

bool operator<=(Card lhs, Deck rhs); // if the Card "lhs" exist in the Deck "rhs" (same name and same energy at the same time) it returns true.


