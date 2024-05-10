#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Node {
public:
    int value;
    Node *next = nullptr; //points to the next value in the vector
    Node *prev = nullptr; //points to the previous value in the vector
    Node(int val) : value(val), next(nullptr) {}
};

/*****************************************************************************************
 * Vector Class
 *
 * Description:
 *      Uses a linked list to create a vector
 *****************************************************************************************
 * Private variables:
 *   Node *front                            keeps track of the front of the vector
 *   Node *rear;                            keeps track of the rear of the vector
 *
 *****************************************************************************************
 *
 * Public Methods:
 *        Vector ()                         default constructor
 *        Vector (string)                   constructor
 *        Vector (int arr[], int size)      constructor
 *
 *  void  pushFront (int)                   adds a value to the front of the vector
 *  void  pushFront (Vector)                adds a vector to the front of the vector
 *  void  pushRear (int)                    adds a value to the rear of the vector
 *  void  pushRear (Vector)                 adds a vector to the rear of the vector
 *  void  pushAt (int, int)                 adds a value to the vector at a given index
 *
 *  int   popRear ()                        removes the value at the rear of the vector
 *  int   popFront ()                       removes the value at the front of the vector
 *  int   popAt (int)                       removes the value at a given index
 *
 *  int   find (int)                        finds the index of a given value
 *
 *  void  Header (ofstream)                 prints the header
 *  void  print (ofstream)                  prints the vector
 *
 *****************************************************************************************/

class Vector {

private:
  Node *front; // keeps track of the front of the vector
  Node *rear;  // keeps track of the rear of the vector
  
 public: 

  Vector () { // default constructor
    front = rear = nullptr;
  }

// constructor for filling the vector using a file
  Vector (string file) {
    ifstream infile;
    infile.open(file);    // opens input file
    int value;
    while (infile >> value)  {  //reads until file is done  
        if (!front) { //if front is empty push to front
            pushFront(value);
        }
       pushRear(value);          // adds everything else
    }
    infile.close(); //close file
  }

  Vector (int arr[], int size) { //constructor for vector array
      Node *trav = nullptr;
      for (int j = 0; j < size; j++) {
        Node* newNode = new Node(arr[j]);
    
            if (!j) {// if j is empty, set the first place
                front = trav = newNode;
            } else {
                trav->next = newNode;
                trav = trav->next;
            }
        }
        rear = trav; // sets the rear to the end of the array
  } 

  //push single value to front
  void pushFront (int val) {
    Node* newNode = new Node(val);   //node that adds the value to the front

    if (!front) {
      front = rear = newNode;
    } else {
      newNode->next = front;
      front = newNode;
    }
  }

  //push array to front of vector
  void pushFront (Vector V2) {
    Node *trav = V2.front;         //traverses V2
    int num = 0;
    int temp;
    
    while (!trav) {        
      temp = trav->value;
       pushAt(num, temp);                  
       trav = trav->next;
       num++; 
    }
  }
 
  //pushes a value to rear of vector
  void pushRear (int val) {
    Node* newNode = new Node (val);   //node that adds the value to the front

    if (rear == NULL) {
      front = rear = newNode;
    } 
      rear->next = newNode;
      rear = newNode;
  }

  //pushes array onto back of vector
  void pushRear (Vector V2) {
    Node *trav; // traverses V2
    trav = V2.front;
   // Node* newNode = new Node(trav->value);

    while (trav) { // while traversing push values to rear
       Node* newNode = new Node(trav->value);
      newNode->prev = rear;
      rear = newNode;
      trav = trav->next;
    }
  }
  
  //pushes to a specified location
  void pushAt (int loc,int val) {
    Node* previous = front;                     //  creating traveling nodes.
    Node* trav = front;

    if (loc == 0) {                   // if location is equal to the front, push front
      pushFront (val);
    } else if (trav == rear) {     // if location is equal to the rear, push rear
      pushRear (val);   
    } else {
      for (int i = 0; i < loc; i++)       //  traversing the vector until appropriate index is reached.
        {
          previous = trav;
          trav = trav->next;
        }
    } 
    previous->next = trav;
    trav->next->prev = trav;
    trav = nullptr;
    delete trav;    
  }

  // remove from the front
  int popFront () {
    int popped = front->value;
    Node *temp = front;
    front = front->next;

    temp = nullptr;
    delete temp; 
    return popped;
  }
  
  // remove from the rear
  int popRear () {
    int popped = rear->value;  
    Node *temp = rear;
    rear = rear->prev;

    delete temp; 
    return popped;
  }

//remove for a specific location in the vector
  int popAt (int loc){
    Node * previous = front;       
    Node * trav = front;
    Node * temp = nullptr;

    if (loc == 0) {                 // if location is front, pop front
        return popFront();
    } else if (trav == rear) {     // if location is rear, pop rear
      return popRear();   
        
    } else {
      for(int i = 0; i < loc; i++) {       //  traversing listVect until appropriate index is reached.
                previous = trav;
                trav = trav->next;
        }
    } 
   //insert the digit at the new location
    previous->next = trav->next;
    trav->next->prev = previous;
    temp = trav;
    trav = nullptr;
    delete trav; 
    return temp->value;  
  }
  
  //By a search than removal (if it exists)
  //find location of item (index) if it exists
  int find (int val) {
    int count = 0; //counter
    Node *trav = front;
    while (trav) {
          if (val == trav->value) {
              return count;
          } else {
            trav = trav->next;
            count++; // increments since nothing was found
          }
      }
      return 0; 
  }

  void Header (ofstream &outfile) {
      outfile << "Trinity Wilkins\n05/10/24\nSpring 3013\n\n";
  }

  void print (ofstream &outfile) {
    Node *trav = front;
    outfile << "[ ";
      while (trav) {
        outfile << trav->value << ", ";
        trav = trav->next;
      } 
    outfile << " ]" << endl;
  }
};
