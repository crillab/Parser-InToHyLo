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

#ifndef PropositionalVariable_h
#define PropositionalVariable_h

#include "Formula.h"

/**
 * @brief This class represents a VARIABLE in a Formula
 * 
 * @see Formula
 */
class PropositionalVariable : public Formula {

 protected:
    
  /** @brief the ID of the variable. */
  int idxVar;

 public:

  /**
     @brief This constructor will create the variable with an ID.     
     @param[in] id the ID of the futur variable
  */
 PropositionalVariable(int id) : idxVar(id) 
  {

    priority = PRIOR_VAR;
    
    father = NULL;
  }
  
  inline int getIdxVar() { return idxVar; }              // This function will return the ID of the variable
       
  inline int getType() { return IS_PROP; }               // This function is returning the type of the current object.
  
  /**
     @brief This function will display the PropositionalVariable.
     @param[in] f a FILE* if we want to display in a file, by default: standard output.
   */
  inline void display(FILE *f = stdout) { fprintf(f, "%sp%d", idxVar < 0 ? "~" : "", idxVar< 0 ? -idxVar : idxVar); }   

};

#endif
