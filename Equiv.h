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

#ifndef Equiv_h
#define Equiv_h

#include "Imply.h"

/**
 * @brief This class represents an EQUIVALENCE in a Formula
 * 
 * @see Formula
 */
class Equiv : public Formula
{
  
  public:
    
    /**
     * @brief Constructor with 2 sub-formulae
     * 
     * This function will create an Object representing (left <-> right)
     * 
     * @param[in] left the left part of the implication
     * 
     * @param[in] right the right part of the implication
     */
    Equiv(Formula *left, Formula *right)
    {
      priority = PRIOR_EQUIV; 

      children.push_back(left); 
      children.push_back(right);

      left->father = right->father = this;

      father = NULL;

    } // Equiv(Formula *left, Formula *right)

    /** @brief Default constructor */
    Equiv()
    {
      father = NULL; 
      priority = PRIOR_EQUIV;
    }
  
   /**
    * @brief This function will display the Equiv.
    * 
    * @param[in] f a FILE* if we want to display in a file, by default: standard output.
    */      
    inline void display(FILE *f = stdout)
    {
      assert(children.size() == 2);

      fprintf(f, "(");
      children[0]->display(f);
      fprintf(f, " <-> ");
      children[1]->display(f);
      fprintf(f, ")");
    }
    
};

#endif