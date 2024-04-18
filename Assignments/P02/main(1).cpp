// Before starting the code make sure to type this 
// into the shell first: g++ main.cpp -std=c++20 -o main

/*****************************************************************************
*                    
*  Author:           Trinity Wilkins
*  Email:            te01.wilkins@gmial.com
*  Title:            P02
*  Course:           CMPS 3013
*  Semester:         Spring 2024
* 
*  Description:
*          This program uses uses a dictionary to look for partial matches in. 
*          Once the dictionary is loaded. Autosuggestions start appearing 
*          after the first character is typed. Only the first 10 suggestions 
*          are shown that match the partial word. Pressing enter will select 
*          the first suggestion and end the program. The program helps explore 
*          the implementation of json files and how to create search functions.
*          This program uses a "getch" function which means "get character".
*          However, getch does not print the character to the terminal, it lets
*          you decide what to do based on what character you are pressing.
*        
*  Usage: 
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list/array. 
*       
*  Files:            
*       main.cpp       : driver program 
*       dictionary.h   : header file containing the dictionary struct
*       json.hpp       : header file for the json library
*       rang.hpp       : header file for the rang library; depends upon c++ standard library
*       console.h      : header file for the console library
*    
*****************************************************************************/


#include "./headers/console.hpp"
#include "./headers/json.hpp"
#include "./headers/rang.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using json = nlohmann::json;
using namespace std;
using namespace rang;

consoleSize console_size; // used to store the size of console (width=cols and
                          // height=rows)

/**
 * Wilkins
 * 
 * Description:
 *      This class is used to store the data from the json file and then 
 *      using a getch method to read in the user inpu and react accordingly
 * 
 * Public Methods:
 *                          Wordstuff()     
 *      vector<string>      findWords()
 *      string              getDefinition()
 *      void                titleBar()           
 *      void                printHighlightedSubstr()
 *      void                horizontalBar()
 *      void                printMenu()
 *      void                printCurrent()
 *      void                errorMessage()
 
 * Private variables:
 *       vector<string>     found;
 *       json               data;
 * 
 * Usage: 
 * 
 *      Wordstuff(filename)                       // Create Instance of Wordstuff
 *                                                // and start the program
 *      findWords()                               // find words that start with 
 *                                                // the chars users input
 *      getDefinition()                           // get the definition of selected 
 *                                                // words.
 *
 *      titleBar                                  // prints title bar "getch example"
 *      
 *      printHighlightedSubstr()                  // highlights the parts of strings 
 *                                                // that are currently typed out by 
 *                                                // the user
 *
 *      horizontalBar()                           // prints a bar for clarity of 
 *                                                // spacing.
 *
 *      printMenu()                               // prints the menu for the user
 *
 *      printCurrent()                            // prints the suggestiongs
 *
 *      errorMessage()                            // prints error message
 *      
 */
class WordStuff {
  vector<string> found;
  json data;

public:
// constructor
  WordStuff(string filename) {
    ifstream f(filename);
    data = json::parse(f);
  }

// destructor
  vector<string> findWords(string substr) {
    vector<string> matches;

    for (auto &[key, value] : data.items()) {
      // std::cout << key << " : " << value << "\n";
      // found = position of the first letter of the substr
      // string::npos = something like null position 
      std::size_t found = key.find(substr);
      
      if (found != string::npos && found == 0) {
        matches.push_back(key);
      }
    }

    return matches;
  }

/**
 * Public : getDefinition
 * 
 * Description:
 *      prints the definitions of the words that match the user input
 *
 * Params:
 *      [string]  word  :  array of words
 * 
 * Returns:
 *      [type] word   : a pointer to a linked list of words.
 */
  string getDefinition(string word){
    return data[word];
  }

/**
 * Public : titleBar
 * 
 * Description:
 *      prints the getch example bar
 * 
 * Params:
 *      [string] title  :  the title of the program
 *      [int] length    :  size of the consoles width
 */
  void titleBar(string title, int length = console_size.width) {
    string padding = string((length / 2) - (title.size() / 2), ' ');
    title = padding + title + padding;
    cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
  }

/**
 * Public : printHighlightedSubstr
 * 
 * Description:
 *      Highlights the parts of strings that were typed out by the user
 * 
 * Params:
 *      [string] word    :  array of words
 *      [string] substr  :  size of the words
        [int] loc        :  location of the word
 */
  void printHighlightedSubstr(string word, string substr, int loc) {
    for (int j = 0; j < word.size(); j++) {
      // if we are printing the substring turn it red
      if (j >= loc && j <= loc + substr.size() - 1) {
        cout << fg::red << style::underline << word[j] << fg::blue
             << style::reset;
      } else {
        cout << fg::blue << word[j] << fg::reset << style::reset;
      }
    }
  }

/**
 * Public : horizontalBar
 * 
 * Description:
 *      prints a bar for clarity of spacing
 * 
 * Params:
 *      [int] length  :  size of the consoles width
 */
  void horizontalBar(int length = console_size.width) {
    string line = string(length, '_');
    cout << fg::gray << line << fg::reset << bg::reset << endl;
  }

/**
 * Public : printMenu
 * 
 * Description:
 *      prints the menu
 * 
 * Params:
 *      [vector<string>] options  :  the choices for the user
 */
  void printMenu(vector<string> options) {
    int i = 1;
    for (auto s : options) {
      cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
           << s << fg::reset << bg::reset << endl;
      i++;
    }
    cout << fg::reset << bg::reset;
  }


/**
 * Public : printCurrent
 * 
 * Description:
 *      prints the suggestions
 * 
 * Params:
 *      [char] k       :  the character that the user input
 *      [string] word  :  array of words
 */
  void printCurrent(char k, string word) {
    cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
         << fgB::yellow;
    if (int(k) == 127) {
      cout << "del";
    } else {
      cout << k;
    }
    cout << " = " << (int)k << fg::reset << endl;
    cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
         << fgB::blue << word << fg::reset << style::reset << endl;
    cout << endl;
  }

/**
 * Public : errorMessage
 * 
 * Description:
 *      prints the error message
 * 
 * Params:
 *      [string] message  :  array of words
 */     
  void errorMessage(string message) {
    cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
    sleep(1);
  }

};

int main() {

  console_size = getConsoleSize(); // get width and height of console
  char k;                          // holder for character being typed
  string key;                      // string version of char for printing
  string substr = "";              // var to concatenate letters to
  vector<string> matches;          // any matches found in vector of animals
  WordStuff diction("./data/dictionary.json");

  int loc;                     // location of substring to change its color
  bool deleting = false;       // checks if we are deleting a character
  string str = "";             // string to hold the word being typed
  vector<string> mainMenu;     // vector of options for the main menu
  
  mainMenu.push_back("Type letters and watch the results change.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter.");

  clearConsole();
  diction.titleBar("Getch Example", console_size.width);
  diction.printMenu(mainMenu);

  // While capital Z is not typed keep looping
  //Runs thorugh the dictionary and finds the words that match the substring
  while ((k = getch()) != 'Z') {

    clearConsole();
    diction.titleBar("Getch Example", console_size.width);
    diction.printMenu(mainMenu);

    cout << (int)k << endl;
    
    // Tests for a backspace and if pressed deletes
    // last letter from "substr".
    if ((int)k == 127) {
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
      
    //Checks if enter is pressed and prints the definition of the word
    }else if ((int)k == 10) {
     
      cout << endl << diction.getDefinition(matches[0]) << endl;
      return 0; //exits code once enter is pressed and the definition is printed
    }
    
      // Makes sure a letter was pressed and only a letter
      if (!isalpha(k)) {
        diction.errorMessage("Letters only!");
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      substr += k; // append char to substr
    
    diction.horizontalBar();
    diction.printCurrent(k, substr);

    matches = diction.findWords(substr);

    if ((int)k != 32) { // if k is not a space print it

      key = to_string(k);

      diction.horizontalBar();

      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matches.size() << style::reset
           << fg::reset << endl
           << endl;

      for (auto &c : substr)
        c = tolower(c);

      int smaller = std::min((int)matches.size(), 10);
      // This prints out all found matches
      for (int i = 0; i < smaller; i++) {
        // find the substring in the substr
        loc = matches[i].find(substr);
        // if its found
        if (loc != string::npos) {
          diction.printHighlightedSubstr(matches[i], substr, loc);
        }
        cout << " ";
      }
      cout << fg::reset << endl << endl << endl << endl;
      if (matches.size() == 1) {
        cout << diction.getDefinition(matches[0]) << endl;
        // this isn't handled at all, just messin around
      }
    }
  }
  return 0;
}

// g++ main.cpp -std=c++20 -o main
