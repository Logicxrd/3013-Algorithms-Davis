/*
 
   ______    ______     __     ______                                                                                
  /      \  /      \  _/  |   /      \                                                                               
 /$$$$$$  |/$$$$$$  |/ $$ |  /$$$$$$  |                                                                              
 $$ ___$$ |$$$  \$$ |$$$$ |  $$ ___$$ |                                                                              
   /   $$< $$$$  $$ |  $$ |    /   $$<                                                                               
  _$$$$$  |$$ $$ $$ |  $$ |   _$$$$$  |                                                                              
 /  \__$$ |$$ \$$$$ | _$$ |_ /  \__$$ |                                                                              
 $$    $$/ $$   $$$/ / $$   |$$    $$/                                                                               
  $$$$$$/   $$$$$$/  $$$$$$/  $$$$$$/                                                                                
                                                                                                                     
                                                                                                                     
                                                                                                                     
   ______    ______   __    __                                                                                       
  /      \  /      \ /  |  /  |                                                                                      
 /$$$$$$  |/$$$$$$  |$$ |  $$ |                                                                                      
 $$ |__$$ |$$$  \$$ |$$ |__$$ |                                                                                      
 $$    $$ |$$$$  $$ |$$    $$ |                                                                                      
 $$$$$$$$ |$$ $$ $$ |$$$$$$$$ |                                                                                      
 $$ |  $$ |$$ \$$$$ |      $$ |                                                                                      
 $$ |  $$ |$$   $$$/       $$ |                                                                                      
 $$/   $$/  $$$$$$/        $$/                                                                                       
                                                                                                                     
                                                                                                                     
                                                                                                                     
  ________         __            __                                      _______                        __           
 /        |       /  |          /  |                                    /       \                      /  |          
 $$$$$$$$/______  $$/   ______  $$/   ______   __    __   ______        $$$$$$$  |  ______   __     __ $$/   _______ 
    $$ | /      \ /  | /      \ /  | /      \ /  |  /  | /      \       $$ |  $$ | /      \ /  \   /  |/  | /       |
    $$ | $$$$$$  |$$ |/$$$$$$  |$$ |/$$$$$$  |$$ |  $$ |/$$$$$$  |      $$ |  $$ | $$$$$$  |$$  \ /$$/ $$ |/$$$$$$$/ 
    $$ | /    $$ |$$ |$$ |  $$/ $$ |$$ |  $$ |$$ |  $$ |$$    $$ |      $$ |  $$ | /    $$ | $$  /$$/  $$ |$$      \ 
    $$ |/$$$$$$$ |$$ |$$ |      $$ |$$ \__$$ |$$ \__$$ |$$$$$$$$/       $$ |__$$ |/$$$$$$$ |  $$ $$/   $$ | $$$$$$  |
    $$ |$$    $$ |$$ |$$ |      $$ |$$    $$ |$$    $$/ $$       |      $$    $$/ $$    $$ |   $$$/    $$ |/     $$/ 
    $$/  $$$$$$$/ $$/ $$/       $$/  $$$$$$$ | $$$$$$/   $$$$$$$/       $$$$$$$/   $$$$$$$/     $/     $$/ $$$$$$$/  
                                          $$ |                                                                       
                                          $$ |                                                                       
                                          $$/                                                                        
 
*/


#include <iostream>

using namespace std;
/*****************************************************************************
*                    
*  Author:           Tairique Davis
*  Email:            tadavis0910@my.msutexas.edu
*  Label:            A04
*  Title:            Circular Array Queue
*  Course:           CMPS 3013
*  Semester:         Spring 2023
* 
*  Description:
*   This program implements a circular array based queue data struct
    using class CircularArrayQue. It uses a number of private
     mem var to keep track of front, rear size + mem functions such
     as Push()/Pop() to allow items to be added/removed from 
     queue. Also has a boolean check to ensure the queue does
     not exceed its container. Uses friend function "ostream"
     to overload "< <" operator and output items in queue. Finally
     it creates an object of class in main to do all of the above
     and display it.


* 
*  Files:      
-  - main.cpp      
*****************************************************************************/

/**
 * CircularArrayQue
 * 
 * Description:
 *     Implements a circular queue based data struct. Has
        a number of private mem var to keep track of front, rear
        size + public mem functions to allow items to be added/removed from
        queue and checks to ensure the queue does not exceed its container.
 * 
 * Public Methods:
 *      - CircularArrayQue() //contructor
 *      - CircularArrayQue(int) //overloaded contructor
 *      - void Push() //void no return type
 *      - int Pop(int) //return int temp
 * 
 * Private Methods:
 *      - void init() 
 *      - bool Full() //boolean check if queue is full if true returns true
 *      
 * 
 * Usage: 
 * 
 *      -Any sceneario where a First-in-First-Out principle is appropriate 
 *         for example storing appointment schedules, online call queues, 
 *          delivery services with a wait based system...etc.
 */
/**
    
**/
class CircularArrayQue {
private:
    int *Container;
    int Front;
    int Rear;
    int QueSize; // items in the queue
    int CurrentSize;
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {    //default queue size of 10
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {    //create queue with user-defined size
        Container = new int[size];
        init(size);
    }

    void Push(int item) {   // add items to rear of queue
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    int Pop() {         //pop items from front of queue
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other); //overloads << to output items in queue
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5); //create object of class with size 5

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);     //add items to queue
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl; //print items

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}
