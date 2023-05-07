/*****************************************************************************
*                    
*  Author:           Tairique Davis
*  Email:            tadavis0910@my.msutexas.edu 
*  Label:            A03
*  Title:            Basic Project Organization
*  Course:           CMPS 3013
*  Semester:         Spring 2023
* 
*  Description:
*        This software includes a class that generates a circular array-based queue. 
         There is an array that stores numbers, and as integers are added to the queue, they are added to the rear of the queue.
         Items may only be removed from the front of the queue. 
         This program was  designed to demonstrate correct structure and commenting of future programs written in this CMPS 3013 repository.

* 
*  Usage:
*       - create a CircularArrayQue that can add and pop items from the queue
* 
*  Files:           
*        main.cpp      :        driver program 
*****************************************************************************/

// Libraries used
#include <iostream>

// namespace standard
using namespace std;

/**
 * CircularArrayQue
 * 
 * Description:
 *      Implements array based circular queue. 
 *      - Dynamically allocates with constructors to allow user to set size of the array
 *      - allows user to push items onto the rear of the list and pop items from the front of list. 
 *     
 * 
 * Public Methods:
 *                              CircularArrayQue()
 *                              CircularArrayQue(int)
 *          void                Push(int)
 *          int                 Pop()
 *          friend ostream      &operator << (ostream &, const CircularArrayQue)            
 * 
 * Private Methods:
 *          void                init(int size = 0)
 *          bool                Full()
 * 
 * Usage: 
 * 
 *     CircularArrayQue List1;              // creates queue with default size of 10
 *     CircularArrayQue List2(5);           // creates queue with default size of  5
 *     List1.Push(10);                      // pushes 10 to the rear of list
 *     List1.Pop();                         // takes item at the front of the list off the list
 *     cout << List1;                       // displays the whole list 
 */
class CircularArrayQue {
private:
    //private attributes

    int *Container; //pointer cointaining items of the list
    int Front;  // item at the front of the list
    int Rear;   /// item at the back of the list
    int QueSize; // items in the queue
    int CurrentSize; // the current amount of items in the queue

/**
     * Private : init
     * 
     * Description:
     *     Initialize values inside of class
     * 
     * Params:
     *      int    :  default paramenter which is the size of the list
     * 
     * Returns:
     *      N/A
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }
/**
     * Private : init
     * 
     * Description:
     *     checks whether queue is full
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      bool    :   true or false depending on if the queue is filled (true) or not (false)
     */
    bool Full() {
        return CurrentSize == QueSize;
    }
public:
/**
     * Public : CircularArrayQue
     * 
     * Description:
     *     Default constructor which intilaizes the list to a size of 10
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    CircularArrayQue() {
        Container = new int[10];  //dynamically allocates space 
        init(10);
    }

    /**
     * Public : CircularArrayQue
     * 
     * Description:
     *     Overloaded constructor to intilaize list to the size of whatever value is passed by the user
     *      
     *
     * Params:
     *      int    :       size passed by user
     * 
     * Returns:
     *      N/A
     */

    CircularArrayQue(int size) {
        Container = new int[size];  // initialize size of the list based 
        init(size);                 // on the size passed
    }

  /**
     * Public : Push
     * 
     * Description:
     *      This function add items to the back of the list  
     * 
     * Params:
     *      int    :      the item to be added to the list
     * 
     * Returns:
     *      N/A
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }
/**
     * Public : Pop
     * 
     * Description:
     *      This function removes items from the front of the list and 
     *      returns it  
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      int     :      the item that has been removed from the front of the list
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    // Friend Prototype for overloaded ostream operator
    /**
     * Public : &operator <<
     * 
     * Description:
     *      overloaded ostrema operator to display the entire list  
     * 
     * Params:
     *      ostream       :     ostream variable passed by reference
     *      const CircularArrayQue  :      the queue that will be displayed 
     * 
     * Returns:
     *      ostream     : ostream variable
     */
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
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
 * main driver to call and test the CircularArrayQue class
 * 
 */
int main() {

    // creating instance of queue
    CircularArrayQue C1(5);
    
    C1.Push(1);     // pushing items onto queue
    C1.Push(2);
    C1.Push(3);
    

    // displaying items in queue
    cout << C1 << endl;

    C1.Pop();    // removes item from list

    cout << C1 << endl; //display updated queue