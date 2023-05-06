/**************************************************************************************
*
*  Author:           Tairique Davis
*  Email:            tadavis0910@my.msutexas.edu
*  Label:            P02
*  Title:            AutoComplete in Linear Time
*  Course:           CMPS-3013
*  Semester:         Spring 2023
*
*  Description:
*            Reads in words from dictionary.txt These words are then read
             and stored in a linked list. After the 1st letter is typed, the
 *           list is searched for words that match what the user has
 *           entered so far. 10 words are displayed that begin with the same
 *           letters as what has been entered.
 *
*  Usage:
*        Read in words typed by user and compare whether those words are in the
dictionary
*
*  Files:            main.cpp
                     List.hpp
                     timer.hpp
                     mygetch.hpp
                     termcolor.hpp
                     dictionary.txt
***************************************************************************************/
#include "List.hpp"
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

#define RED termcolor::red
#define BLUE termcolor::blue
#define YELLOW termcolor::yellow
#define GREEN termcolor::green
#define MAGENTA termcolor::magenta
#define GREY termcolor::grey

/**
 * public: load_list
 * Description: Takes a List by reference, and populates it with data from an
 * input file.
 *
 * Parameter: L An empty list to populate with values.
 * Parameter: file_name The name of the file to be used.
 * Return void
 */
void load_list(List &L, string file_name);

/**
 * public: get_matches
 * Description: Clears a List and populates it with values from another List,
 * but only values that partially/wholey match (prefix matches) the specified
 * substring. Ignores empty strings.
 *
 * Parameter: L A List filled with string values.
 * Parameter: matches An List to populate with matches from List L.
 * Parameter: substring A substring to be used for finding matches.
 * Return void
 */
void get_matches(const List &L, List &matches, string substring);

int main() {
  char k;           // holder for character being typed
  string word = ""; // var to concatenate letters to
  List dictionary;  // List to hold words
  List matches;     // any matches found in List of dictionary
  int loc;          // location of substring to change its color
  int numMatches;   // loop control variable for printing matches

  // Program Header
  cout << YELLOW << string(90, '#')
       << "\nProgram 2 - AutoComplete in Linear Time\nCMPS 3013\nTairique "
          "Davis\n"
       << string(90, '#') << '\n'
       << termcolor::reset;

  Timer T;   // create a timer
  T.Start(); // start it

  load_list(dictionary, "dictionary.txt");

  T.End(); // end the current timer

  // print out how long it took to load the dictionary file
  cout << YELLOW << T.Seconds() << termcolor::reset
       << " seconds to read in data from dictionary.txt\n";
  cout << BLUE << T.MilliSeconds() << termcolor::reset
       << " milliseconds to read in data from dictionary.txt\n";

  cout << "Type keys and watch what happens. Type capital Z to quit." << '\n';

  // While capital Z is not typed keep looping
  while ((k = getch()) != 'Z') {

    // Tests for a backspace and if pressed deletes
    // last letter from "word".
    if ((int)k == 127) {
      if (word.size() > 0) {
        word = word.substr(0, word.size() - 1);
      }
    } else {
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) {
        cout << "Letters only!" << endl;
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      word += k; // append char to word
    }

    T.Start(); // Start timer for finding matches

    // Find any strings in the array that partially match
    // our substr word
    get_matches(dictionary, matches, word);

    T.End(); // End timer for finding matches

    if ((int)k != 32) { // if k is not a space print it

      cout << YELLOW << T.Seconds() << termcolor::reset
           << " seconds to get matches.\n";
      cout << BLUE << T.MilliSeconds() << termcolor::reset
           << " milliseconds to get matches\n";
      cout << "Keypressed: " << BLUE << k << " = " << (int)k << termcolor::reset
           << '\n';
      cout << "Current Substring: " << RED << word << termcolor::reset << '\n';
      cout << matches.size() << " possible match(es).\n" << GREEN;

      // If more than 10 matches, only show first 10, else use total amount
      numMatches = matches.size() > 10 ? 10 : matches.size();

      // This prints out 10 found matches
      for (int i = 0; i < numMatches; i++) {
        // find the substring in the word
        loc = matches[i].find(word);
        // if its found
        if (loc != string::npos) {
          // print one letter at a time turning on red or green
          //  depending on if the matching subtring is being printed
          for (int j = 0; j < matches[i].size(); j++) {
            // if we are printing the substring turn it red
            if (j >= loc && j <= loc + word.size() - 1) {
          cout << MAGENTA;
            } else {
              cout << GREEN;
            }
            cout << matches[i][j];
          }
          cout << GREEN;
        }
        cout << " ";
      }
      cout << termcolor::reset << "\n\n";
    }
  }
  cout << GREEN << string(90, '#') << termcolor::reset
       << '\n'; // Footer just to show program ended
  return 0;
}

/**
 * public: load_list
 * Description: Takes a List by reference, and populates it with data from an
 * input file.
 *
 * Parameter: L An empty list to populate with values.
 * Parameter: file_name The name of the file to be used.
 * Return void
 */
void load_list(List &L, string file_name) {
  ifstream fin; // file to get animal names
  string x;
  fin.open(file_name); // open file for reading

  while (fin >> x) {
    for (auto &c : x) {
      c = tolower(c);
    }
    L.push_back(x);
  }
  fin.close();
}

/**
 * public: get_matches
 * Description: Clears a List and populates it with values from another List,
 * but only values that partially/wholey match (prefix matches) the specified
 * substring. Ignores empty strings.
 *
 * Parameter: A List filled with string values.
 * Parameter: matches List to populate with matches from List L.
 * Parameter: substring A substring to be used for finding matches.
 * Return void
 */
void get_matches(const List &L, List &matches, string substring) {
  size_t found; // size_t is an integer position of
                // found item. -1 if its not found.

  matches.clear(); // It is quicker to directly clear and repopulate this list

  if (substring == "") // If empty string, don't bother searching
  {
    return;
  }
  for (int i = 0; i < L.size(); i++) // loop through List
  {
    found = L[i].find(substring); // check for substr match
    if (found == 0)               // if found = 0
    {
      matches.push_back(L[i]); // add to matches
    }
  }
}
