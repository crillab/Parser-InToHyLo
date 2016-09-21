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

#ifndef Diamond_h
#define Diamond_h

#include "Formula.h"

/**
 * @brief This class represents a DIAMOND in a Formula.
 * 
 * It has an agent ID and at maximum one child.
 * 
 * @see Formula
 */
class Diamond : public Formula
{
  protected:
    
    /** @brief the ID of the agent in the relation created by this Diamond. */
    int idxAgent;
  
  public:

   /**
    * @brief To construct a Diamond, we need an agent ID.
    * 
    * @param[in] id the identifier of the agent.
    *
    */
    Diamond(int id): idxAgent(id) 
    {
      father = NULL; 
      priority = PRIOR_DIAMOND;
      
    } // Diamond(unsigned int id)

   /**
    * @brief To construct a Diamond, we need an agent ID and a child.
    * 
    * @param[in] id the identifier of the agent.
    * 
    * @param[in] f the futur child of the current diamond.
    *
    */
    Diamond(int id, Formula *f) : idxAgent(id)
    {
      priority = PRIOR_DIAMOND; 
      children.push_back(f);
      f->father = this;
      father = NULL;

    } // Diamond(unsigned int id, Formula *f)

    /**
       @brief This function will display the Diamond by:     
       - indicating its agent ID     
       - calling the display function of its child.       
       @param[in] f a FILE* if we want to display in a file, by default: standard output.
    */
    inline void display(FILE *f = stdout) 
    { 
      fprintf(f, "<r%d>", idxAgent);
      if(children.size()) children[0]->display(f); else fprintf(f, "empty");
    } // display
    
   /**
    * @brief This function is returning the type of the current object.
    * 
    * @return IS_DIAMOND.
    */
    inline int getType() { return IS_DIAMOND; }
    
};

#endif
