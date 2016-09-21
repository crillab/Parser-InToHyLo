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

#ifndef Or_h
#define Or_h

#include "Box.h"

/**
 * @brief This class represents an OR in a Formula
 * 
 * It has 2 children
 * 
 * @see Formula
 */ 
class Or : public Formula
{

 public:
  
 /**
  * @brief Constructor of a logical OR with 2 sub-formulae
  * 
  * @param[in] f1 the left sub-formula of the logical OR.
  *
  * @param[in] f2 the right sub-formula of the logical OR.
  */
  Or(Formula *f1, Formula *f2)
    {
      priority = PRIOR_OR; 

      children.push_back(f1); 
      children.push_back(f2);

      f1->father = f2->father = this;
      father = NULL;
    }

 /**
  * @brief Constructor of a logical OR with N sub-formulae
  *
  * @param[in] list a list of sub-formulae that will be connected to each other
  * with a logical OR.
  */
  Or(vector<Formula *> & list)
    { 
      priority = PRIOR_OR; 
      children = list;
      for(auto & child : list) child->father = this;
      father = NULL;
    }
    
 /**
  * @brief Constructor of an empty OR.
  * during the parsing, 
  * we are often creating an OR without knowing in advance what it will store.
  */
  Or(){father = NULL; priority = PRIOR_OR;}

 /** 
  * @brief Return the type of the OR
  * 
  * @return IS_OR
  */
  inline int getType() { return IS_OR; }
  
 /**
  * @brief polymorphic method to display the sub-formula when it is starting with an AND. 
  *
  * @param[in] f a file if we want to write inside, stdout otherwise
  */  
  inline void display(FILE *f = stdout)
  { 
    unsigned int size = children.size();

    assert(size >= 2);

    fprintf(f, "(");
    for(unsigned int i = 0 ; i < size; ++i)
      {
        if(i) fprintf(f, " | ");
        children[i]->display(f);
      }
    fprintf(f, ")");
  } // display

};

#endif
