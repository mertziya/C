#include <iostream>
#include "mertziya_Ziya_Mert_HW7PrintQueue.h"
#include <string>
#include <time.h>
#include <chrono>
#include <random>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex pass;
mutex pass2;
mutex pass3;

static int ID = 0;
static int ID_for_queue = 0;

struct thread_storage{ // function stores the needed variables for the thread variable.
    int & printjob_s, min_wait_s, max_wait_s, min_page_s, max_page_s, user_place;
    HW7PrintQueue & printer_s;
    vector<int> & pages_s;
    
    thread_storage(int a, int b, int c, int d, int e, int & f, HW7PrintQueue & g, vector<int> & h)
    : user_place(a),min_wait_s(b),max_wait_s(c),min_page_s(d),max_page_s(e),printjob_s(f),printer_s(g),pages_s(h)
    {
    }
    
    
};


void set_values(int & p, int & min, int & max, int & min_page, int & max_page){ // it asks the user for inputs. and sets them.
    int a , b , c, d, e;
    cout << "Please enter the max number of print jobs: ";
    cin >> a;
    cout << "Please enter the min and max values for the waiting time period (in seconds) after creating a print job:" << endl;
    cout << "Min: ";
    cin >> b;
    cout << "Max: ";
    cin >> c;
    cout << "Please enter the min and max values for the number of pages in a print job:\n";
    cout << "Min number of pages: ";
    cin >> d;
    cout << "Max number of pages: ";
    cin >> e;
    p = a; min = b; max = c; min_page = d; max_page = e;
}

int random_range(const int & min, const int & max){ // it takes 2 integer parameters and gives a random value between them.
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}


void time_0_setter(string & h ,string & m, string & s, tm * n){ // it makes the time look better
    // e.g --> if the time is 20:20:3 ==> it becames 20:20:03
    string a = to_string(n->tm_hour);
    string b = to_string(n->tm_min);
    string c = to_string(n->tm_sec);
    if(a.size() == 1){
        a = '0' + a;
    }
    if(b.size() == 1){
        b = '0' + b;
    }
    if(c.size() == 1){
        c = '0' + c;
    }
    h = a; m = b; s = c;
}


void sender(thread_storage & user){ // the function that is being used by the 3 user threads.
    // it enqueues the printer
    
    int wait = random_range(user.min_wait_s, user.max_wait_s);
    this_thread::sleep_for(chrono::seconds(wait));
    pass.lock();
        while(ID < user.printjob_s){
        
            int wait = random_range(user.min_wait_s, user.max_wait_s);
            int page = random_range(user.min_page_s, user.max_page_s);
        
            
        
        
        
            user.pages_s[ID] = page;
            ID++;
            int temp = ID;
            pass.unlock();
            
            pass3.lock();
            user.printer_s.enqueue(ID, page);
            int temp2 = user.printer_s.getCurrentSize();
            pass3.unlock();
                
            pass2.lock();
            
            time_t t = time(0);                    //
            tm* now = localtime(&t);               // ==> This 4 lines of code is used several times.
            string hour, min, sec;                 // ==> it shows the current time.
            time_0_setter(hour, min, sec, now);    //
            
            cout << "User " << user.user_place << " sent new print job with ID " << temp << " sent to the printer queue, "
                 << "number of pages: " << page << " (print queue size: " << temp2 << ")  "
                 << hour << ':' << min << ':' <<  sec << endl;
            pass2.unlock();
                
            this_thread::sleep_for(chrono::seconds(wait));
            pass.lock();
        }
    
    pass.unlock();
}


void printed(thread_storage & printer){ // the function used by the printer thread.
    // it deques the printer with ( waiting time = page number on each order ).
    //
    
    while(ID_for_queue < printer.printjob_s){
        
        bool checker = false; // needed for not printing unnecessary outputs.
        int temp = printer.printer_s.getCurrentSize(); // necessary for not printing the wrong queue size.
        
        pass3.lock();
        if(! printer.printer_s.isEmpty()){
            checker = true;
            temp = printer.printer_s.getCurrentSize();
            ID_for_queue++;
            printer.printer_s.dequeue(ID_for_queue, printer.pages_s[ID_for_queue-1]);
        }
        pass3.unlock();
        
        if(checker){
            
            pass2.lock();
            
            time_t t = time(0);
            tm* now = localtime(&t);
            string hour, min, sec;
            time_0_setter(hour, min, sec, now);
            
            cout << "The printer started to print the job with ID: " << ID_for_queue << ", number of pages: " << printer.pages_s[ID_for_queue-1] << " (queue size is: " << temp -1 << ")  "
                << hour << ':' << min << ':' <<  sec << endl;
            
            
            pass2.unlock();
        
            this_thread::sleep_for(chrono::seconds(printer.pages_s[ID_for_queue-1]));
            
            
            pass2.lock();
            
            time_t t2 = time(0);
            tm* now2 = localtime(&t2);
            string hour2, min2, sec2;
            time_0_setter(hour2, min2, sec2, now2);
            
            cout << "The printer finished printing the job with ID: " << ID_for_queue << ", number of pages: " << printer.pages_s[ID_for_queue-1] << "  " << hour2 << ':' << min2 << ':' <<  sec2 << endl;
            
            pass2.unlock();
        }
        
    }
    
    time_t t2 = time(0);
    tm* now2 = localtime(&t2);
    string hour2, min2, sec2;
    time_0_setter(hour2, min2, sec2, now2);
    
    cout << "End of the simulation ends  " << hour2 << ':' << min2 << ':' <<  sec2 << endl;
    
}


int main(){
    int printjob, min_wait, max_wait, min_page, max_page;
    set_values(printjob, min_wait, max_wait, min_page, max_page);
    time_t t = time(0);
    tm* now = localtime(&t);
    string hour, min, sec;
    time_0_setter(hour, min, sec, now);
    cout << "\nSimulation starts " << hour << ':' << min << ':' <<  sec << endl;
    
    HW7PrintQueue printer; // for taking a printer by deffault.
    vector<int> pages;     // pages are needed in the 'printed' function which is used by thread P.
    
    for(int i = 0; i < printjob; i++){
        pages.push_back(0);
    }
    
    thread_storage user1(1,min_wait,max_wait,min_page,max_page,printjob,printer,pages);
    thread_storage user2(2,min_wait,max_wait,min_page,max_page,printjob,printer,pages);
    thread_storage user3(3,min_wait,max_wait,min_page,max_page,printjob,printer,pages);
    
    thread_storage printer_data = user1;
    
    
    thread U1(&sender, ref(user1));
    thread U2(&sender, ref(user2));
    thread U3(&sender, ref(user3));
    thread P(&printed, ref(printer_data));
    
    P.join();
    U1.join();
    U2.join();
    U3.join();
    
    
    
    return 0;
}

