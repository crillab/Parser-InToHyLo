/****************************************************************************************
* Copyright (c) 2016 Artois University
*
* This file is part of Parser-InToHyLo
*
* Parser-InToHyLo is free software: you can redistribute it and/or modify it 
* under the terms of the GNU General Public License as published by the Free Software Foundation, 
* either version 3 of the License, or (at your option) any later version.
*
* Parser-InToHyLo is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with Parser-InToHyLo. 
* If not, see http://www.gnu.org/licenses/.
*
* Contributors:
*       - Jean Marie Lagniez  (lagniez@cril.fr)
*       - Valentin Montmirail (montmirail@cril.fr)
***************************************************************************************************/

#ifndef LexicalAnalysis_h
#define LexicalAnalysis_h

#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
using std::string;

#define MAX_SIZE   1024

#define END_FILE      0
#define BEGIN         1
#define END           2
#define ERROR         3
#define RELATION      4
#define PROPOSITIONAL 5
#define NUMBER        6        
#define OR            7
#define AND           8
#define PAR_LEFT      9
#define PAR_RIGHT    10
#define NOT          11
#define COMMENT      12
#define IMPLY        13
#define EQUIV        14
#define DIAMOND      15
#define BOX          16
#define TRUE         17
#define FALSE        18
#define FORMULA      19

/**
 * @brief This class represents the lexical analysis of the InToHyLo format.
 */
class LexicalAnalyser
{
  
  public:  

    /** @brief the current value during the lexical analysis */
    int currentValue;

    /** @brief the current string during the lexical analysis */
    char currentChar[MAX_SIZE];

    /** @brief a reference to the file that we are reading */
    FILE *cin;  

    /**
     * @brief Constructor of the LexicalAnalyser
     * 
     * This function will just open the file with the filename
     * 
     * @param[in] fileName the file that we want to open
     * 
     */
    LexicalAnalyser(const char *fileName) { cin = fopen(fileName, "r"); }

   /**
    * @brief Default constructor, cin equals NULL after.
    */ 
    LexicalAnalyser() { cin = NULL; }
    
   /**
    * @brief Destructor of the LexicalAnalyser
    * 
    * This function will just close cin if it is still open.
    */
    ~LexicalAnalyser() { if(cin) fclose(cin); }

   /**
    * @brief Read the flux and return the next token. 
    * The value is also save.
    * 
    * @return the next token.
    */
    int nextToken();

   /** 
    * @brief This function will keep the token in the savedToken stack.
    * 
    * @param[in] tk the token that we want to save
    * 
    * @param[in] id the id that we want to save.
    */
    inline void keepToken(int tk, int id)
    {
      savedToken.push_back(tk); 
      savedId.push_back(id);

    } // keepToken

   /**
    * @brief This function will transform a token into a string
    * 
    * @param[in] tk the token from which we want the string equivalent
    * 
    * @return the string equivalent of the parameter
    */
    inline string tokenToChar(int tk)
    {
      switch(tk)
        {
          case TRUE          : return "TRUE";
          case FALSE         : return "FALSE";
          case END_FILE      : return "END_FILE"; 
          case BEGIN         : return "BEGIN";
          case END           : return "END";
          case ERROR         : return "ERROR";
          case RELATION      : return "RELATION";
          case PROPOSITIONAL : return "PROPOSITIONAL";
          case NUMBER        : return "NUMBER";
          case OR            : return "OR";
          case AND           : return "AND";
          case PAR_LEFT      : return "PAR_LEFT";
          case PAR_RIGHT     : return "PAR_RIGHT";
          case NOT           : return "NOT";
          case COMMENT       : return "COMMENT";
          case IMPLY         : return "->";
          case EQUIV         : return "<->";
          case BOX           : return "[]";
          case DIAMOND       : return "<>";
          case FORMULA       : return "FORMULA";
          default            : return "UNKNOW";
        }

    } // tokenToChar

   /** 
    * @brief Read a number from cin. 
    * 
    * @return the number read.
    */
    inline int parseInt()
    {
      currentValue = 0;
      int c = getc(cin);
      assert(c >= '0' && c <= '9');
      
      while(c != EOF && (c >= '0' && c <= '9'))
        {
          currentValue = currentValue * 10 + (c - '0');
          c = getc(cin);
        }
      
      fseek(cin , -1, SEEK_CUR);
      return currentValue;

    } // parseInt

   /** 
    * @brief Consum the current line 
    */
    inline void eatLine()
    {
      int c = getc(cin);
      while(c != '\n' && c != EOF) c = getc(cin);

    } // eatLine
  
  private:
    
   /** 
    * @brief This function check if the word s starts at the position 'start'
    * 
    * @param[in] s the word that we are checking
    * 
    * @param[in] start the index of the first character.
    *
    * @return true if the word starts, false otherwise.
    */ 
    bool checkWord(string s, int start);

    vector<int> savedToken;
    vector<int> savedId;
};


#endif
