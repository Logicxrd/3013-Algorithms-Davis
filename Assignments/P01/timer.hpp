///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Terry Griffin
// Email:            terry.griffin@msutexas.edu
// Title:            Timer Class
// Semester:         Spring 2020
// Date:             3 Feb 2020
//
// Description:
//       This is a simple class that wraps the "chrono" data type and allows a user
//       to time code snippets at the granularity of seconds or milliseconds.
//       
// Usage: 
//      #include "timer.hpp"
//      
//
//      Timer T;
//      T.Start();
//
//      // do stuff to be timed here
//
//      T.End(); 
//
//      double s = T.Seconds();
//      long m = T.MilliSeconds();
//      
//      cout <<s << " seconds" <<endl;
//      cout <<m << " milli" <<endl;
//      
/////////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <chrono> 
#include <thread>


typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds Msec;
typedef std::chrono::duration<float> Fsec;
using std::chrono::duration_cast;
using std::this_thread::sleep_for;


class Timer{
private:
    int seed;
    int micro;
    Time::time_point start;
    Time::time_point end;
    Fsec seconds;
    Msec milliseconds;

public:
    Timer(){
    }

    void Start(){
        start = Time::now();
    }

    void End(){
        end = Time::now();
    }

    double Seconds(){
        auto dur = end - start;
        auto secs = duration_cast<Fsec>(dur);
        return secs.count();
    }

    long MilliSeconds(){
        auto dur = end - start;
        auto millis = duration_cast<Msec>(dur);
        return millis.count();
    }

    void Sleep(long x){
        sleep_for(Msec(x));
    }

    //************************************************************************
    // Method Name: compare
    //
    // Public
    //
    // Purpose: compares difference between two doubles, in this program
    //          to record the time difference between searches.
    //
    // Arguments: double x, double y and output file
    //
    // Returns: double
    //*************************************************************************
    double compare(double x, double y, ofstream&o)
    {
        //compare Search times 
        if (x < y)
        {
            double z = y - x;
            cout << "Record was found.... " << z << " seconds faster using Avl Tree!";
            o << "Record was found.... " << z << " seconds faster using Avl Tree!";
            return z;
        }
        else if (y < x)
        {
            double z = x - y;
            cout << "Record was found.... " << z << " seconds faster using Linked List!";
            o << "Record was found.... " << z << " seconds faster using Linked List!";
            return z;
        }
         else
        {
            double z = y;
            cout << "Record found at the same time!";
            o << "Record found at the same time!";
            return z;
        }
    }
};