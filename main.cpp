#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct cell{   // struct for specifying the places in matrix
    char letter, color;
};

void get_text(string & letter, int & attempt){  // this function reads the files and modifies letter and attempt
    string filename, Letter, line;
    int Attempt;
    ifstream input;
    bool check = false;
    cout << "Welcome to SWordle!\n";
    while (check == false){
        cout << "Please enter the file name: ";
        cin >> filename;
        input.open(filename.c_str());
        if(input.fail()){
            cout << "Couldn't find the file!\n";
        }
        else{check = true;}
    }
    input >> Attempt;
    input >> Letter;
    letter = Letter;
    attempt = Attempt;
    input.close();
}

void builder(vector<vector<cell>> & guesses, string trial, string text_word, int attempt_num){
    for(int i = 0; i < trial.length(); i++){
        if(trial.at(i) == text_word.at(i)){  // checks if letter exists in word and in correct spot.
            guesses[attempt_num][i].color = 'G';
            guesses[attempt_num][i].letter = (char)trial.at(i);
        }
        else if((trial.at(i) != text_word.at(i))&& (text_word.find(trial.at(i)) != string::npos)){
            guesses[attempt_num][i].color = 'Y';   // checks if letter exists in word but not in correct spot.
            guesses[attempt_num][i].letter = (char)trial.at(i);
        }
        else if((trial.at(i) != text_word.at(i))&&(text_word.find(trial.at(i)) == string::npos)){
            guesses[attempt_num][i].color = 'B'; // checks if letter does not exist and not in correct spot.
            guesses[attempt_num][i].letter = (char)trial.at(i);
        }
    }
}

void vector_output(const vector<vector<cell>> guesses, int length, int attempt){
    for(int i = 0; i < attempt; i++){
        cout << "||";  // this function designs the output and puts "||" and " "  and "," on correct spots.
        for(int j = 0; j < length; j++){
            cout << " " << guesses[i][j].letter << " , " << guesses[i][j].color << " ||";
        }
        cout << endl;
    }
}

bool check_1(const int length, const string trial){ // checks if the input word has enough letters
    if(length != trial.length()){
        if (trial.length() < length){ // checks if the entered word is smaller than the answer
            cout << "The word is too short!" << endl;
        }
        if (trial.length() > length){ //  checks if the entered word is bigger than the answer
            cout << "The word is too long!" << endl;
        }
        return false;
    }
    else{return true;}
}

bool check_2(const string trial){  // checks if all the letters are lower case letters.
    string alpha = "abcdefghijklmnopqrstuvwxyz"; // the only strings allowed to be used in guesses.
    for(int i = 0; i < trial.length(); i++){ // i ==> selects the place of the guess.
        for(int j = 0; j < alpha.length(); j++){ // j ==> selects the place of alpha
            if (alpha.find(trial.at(i)) == string::npos){  // checks if there is an invalid char in the guess.
                cout << "Your input has illegal letters!" << endl;
                return false;
            }
        }
    }
    return true;
}

bool check_3(const string trial){   // checks if there is a duplicate letter in the input word.
    string check = " ";
    for(int i = 0; i < trial.length(); i++){
        check = check + trial.at(i); // adds the i'th char to check in each loop.
        for(int j = 0; j < i+1; j++){
            if(trial.at(i) == check.at(j)){ // controls ther character is repeated in the guess.
                cout << "Your input has a duplicate letter!"<<endl;
                return false;
            }
        }
    }
    return true;
}

bool check_4(const string trial, int attempt_num ,const vector<vector<cell>> guesses){
    for(int i = 0; i < attempt_num; i++){ // selects the i'th row.
        string temp;
        for(int j = 0; j < trial.length(); j++){
            temp = temp + guesses[i][j].letter;
        }
        if(temp == trial){ // temp is the i'th attempt's word ==> if it is equal to trial
            cout << "You've already tried this word!" << endl; // it gives an error output.
            return false;
        }
    }
    return true; // returns true if the word is not used in the previous attempt(s).
}

bool check_5(const string trial, int attempt_num ,const vector<vector<cell>> guesses){
    for(int i = 0; i < attempt_num; i++){
        for(int j = 0; j < trial.length(); j++){
            if(guesses[i][j].color == 'G'){  // checks if the i'th row, j'th col is 'G'
                char temp = guesses[i][j].letter;
                if(trial.at(j) != temp){  // checks if the green color is used in correct place.
                    cout << "You did not use the green letter in your word!" << endl;
                    return false;
                }
            }
        }
    }
    return true; // returns true if the green letter is used in the correct place.
}

bool first_check(const string trial, int length){  // checks if it is true for the first trial.
    if(check_1(length, trial) && check_2(trial) && check_3(trial)){return true;}
    else{return false;} // check_1, check_2, check_3 are enough for checking the first entry
}

   //later check() ==> checks for the second, third... trials.
bool later_check(const string trial, int length, vector<vector<cell>> guesses, int att_num){
    if(first_check(trial, length) && check_4(trial, att_num,guesses) && check_5(trial, att_num,guesses)){return true;}
    else{return false;}  // all check_1, check_2, check_3, check_4, check_5 is reqiured for other enrties.
}

int main(){
    cell c;
    string text_word, trial;
    int text_attempt, word_length;
    get_text(text_word, text_attempt);
    word_length = (int)text_word.length();
    cout << "The word that you will guess has " << word_length << " letters and you have " << text_attempt << " attempts.\n";
    vector<vector<cell>> guesses(text_attempt);
    for(int i = 0; i < text_attempt; i++){      //  this 2 for loop, pumps '-' to all places
        for(int j = 0; j < word_length; j++){   //  in the matrixes. In the beggining size was 0.
            c.letter = '-';
            c.color = '-';
            guesses[i].push_back(c);
        }
    }
    do{
        cout << "What's your guess? ";
        cin >> trial;
    }while(first_check(trial, word_length) == false); // asks for input, until the input is valid.
    int attempt_num = 0;
    builder(guesses, trial, text_word, attempt_num); // modifies the matrixes with trials.
    vector_output(guesses, word_length, text_attempt); // gives the output
    attempt_num++;
    if(trial == text_word){cout << "You win!\n" << endl; return 0; }
    if (text_attempt == 1){  // when text_attempt equals to 1, it gives an error on the second do while loop
                             // that is why there is a special case when text_attempt = 1.
        if(trial == text_word){cout << "You win!\n"; return 0;}
        else{cout << "You lose!" << endl; return 0;}
    }
    do{
        cout << "What's your guess? ";
        cin >> trial;
        if(later_check(trial, word_length, guesses,attempt_num)){
            builder(guesses, trial, text_word, attempt_num);   // modifies the matrixes with trials.
            vector_output(guesses, word_length, text_attempt); // gives the output
            attempt_num++;
        }
        if(trial == text_word){cout << "You win!" << endl; return 0;} // if input equals to answer you win.
    }while(attempt_num < text_attempt); // asks for input, until the input is valid.
    cout << "You lose!" << endl;
    return 0;
}
