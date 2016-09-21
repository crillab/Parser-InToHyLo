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
# Contributors:
#       - Jean Marie Lagniez  (lagniez@cril.fr)
#       - Daniel Le Berre     (leberre@cril.fr)
#       - Tiago de Lima       (delima@cril.fr)
#       - Valentin Montmirail (montmirail@cril.fr)
***************************************************************************************************/

#ifndef Formula_h
#define Formula_h

#include <vector>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <iostream>

/* ---------------------- */

#define PRIOR_BOX     5
#define PRIOR_DIAMOND 5
#define PRIOR_NEG     5

#define PRIOR_EQUIV   4
#define PRIOR_AND     3
#define PRIOR_IMPLY   2
#define PRIOR_OR      1

#define PRIOR_TOP     0
#define PRIOR_BOTTOM  0
#define PRIOR_VAR     0

/* ---------------------- */

#define IS_UNKNOWN    0
#define IS_BOX        1
#define IS_DIAMOND    2
#define IS_OR         3
#define IS_AND        4
#define IS_PROP       5
#define IS_TRUE       6
#define IS_FALSE      7

/* ---------------------- */


class PropositionalVariable;

using std::vector;

/**
 * @brief This class represents somehow an Abstract element in a modal logic formula
 * 
 * It can be a {Box,Diamond,And,Or,PropositionalVariable,Neg,Imply,Equiv}
 */
class Formula
{

public:
    
  /** @brief the vector to store the children of the term */
  vector<Formula *> children;
    
  /** @brief reference to the father of the term */
  Formula *father;

  int nbFather = 1;                           // we suppose that when a formula is created it is attached to another node (=> 1)

  int priority;                               // Priority of the operator  

public:

  /**
     @brief This destructor will delete all the children.
  */
  virtual ~Formula()
    {
      for(auto * child : children)
        {
          child->nbFather--;
          if(!child->nbFather) delete child;
        }
      
      children.clear();      
    }// destructor

  /**
     This function will display the Top by: displaying 'false'     
     @param[in] f a FILE* if we want to display in a file, by default: standard output.
  */ 
  virtual void display(FILE *f = stdout) = 0;

  /**
     This function is returning the type of the current object.
     \return IS_UNKNOWN.
  */    
  virtual int getType() { return IS_UNKNOWN; }  

  /**
   * @brief This function will add a child to the current object
   * 
   * @param[in] f the new child of 'this'
   */
  inline void addChild(Formula *f) { children.push_back(f); }

  inline void removeChild(unsigned int j) { std::swap(children[j], children.back()); children.pop_back();}
    
};


#endif
