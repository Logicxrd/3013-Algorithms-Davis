## P01 - Database Index
### Tairique Davis
### Description:

This program reads in data from a json file that was randomly generated data using Mackaroo, into AVL trees and linked lists in order to compare search complexity times. Main purpose of this project is to demonstrate the superiority of constant time Olog(n).
There were many ways to implement this program, however my approach is as follows:<br>
<br>
1.Out of the 16 fields in the json file, the following 10 were chosen: id, first name, last name, email, address, state, city, car, car model, car color<br>
<br>
2. Imported/Modified classes for Avl Tree and Linked list respectively - each class had to be able to insert, search and delete data of types string and int<br>
<br>
3. Created a counter variable 'comparisons' and included into search methods of both classes in order to count how many nodes/trees were visited before the correct value was found<br>
<br>
4. Created a 'Tree Manager class' that inherits from Avl Tree class, included a method 'set tree' to create the 10 trees corresponding to the decided fields<br>
<br>
5. Imported nlohmann's library in order to streamline opening,reading and parsing json data <br>
<br>
6. For flexibility, program has two methods of searching data either via a manual search or modifying hard coded pre-defined searches<br>
<br>
7. Imported timer class to record duration of each search, added a new method 'compare' that accepts 2 doubles, finds the smallest value and returns the difference between the two doubles.
this was done to more precisely display the difference in search duration between the two data structures

### Files

|   #   | File     | Description                      |
| :---: | -------- | -------------------------------- |
|   1   | main.cpp | Main driver of program. |
|   2   | json.hpp | json library implementation |
|   3   | linkedList.hpp | Linked List implementation |
|   4   | Timer.hpp | timer class to time search times |
|   5   | person_data.json | example json info to read in |
|   6   | output.txt | example output of program |
|   7   | AvlTree.hpp | AVL tree implementation |
|   8   |output_ss.pdf| screenshots of program|
|   9   |person.hpp| user defined struct of json fields for linked list|
|  10   | Banner.txt| banner showing: course code, name and project name|



### Instructions:

- Create object of Tree manager and use 'set tree' to create trees corresponding to json field
- Create object of linked list in main
- To reduce modifications to code, rename any json files to 'person_data.json'. This file should be placed directly in your project folder
- Highly recommended to use the manual search feature when using other json files besides the one included in this project, reason being
  the pre-defined searches were created using data from a specific file that may not be present in another. 
- When swapping between pre-defined searches and manual searches, simply place the unnecessary method in a comment block or store in a file for future use.
- When reading in json ensure proper format is used, nlohmann's repository on Github is an excellent resource to get up to speed
- Apart from that, feel free to have fun and play around with the code!


