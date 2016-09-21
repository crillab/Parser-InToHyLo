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

#ifndef Box_h
#define Box_h

#include "Diamond.h"

/**
 * @brief This class represents a BOX in a Formula.  
 *
 * It has an agent ID and at maximum one child.
 *
 * @see Formula
 */
class Box : public Formula
{  

protected:

  int idxAgent; // the ID of the agent in the relation created by this Box.
 
 public:

  /**
     @brief To construct a Box, we need an agent ID.     
     @param[in] id the identifier of the agent.    
  */
 Box(int id): idxAgent(id)
  {
    father = NULL; 
    priority = PRIOR_BOX;
  }  

  /**
     @brief To construct a Box, we need an agent ID and a child.    
     @param[in] id the identifier of the agent.    
     @param[in] f the futur child of the current diamond.    
  */
 Box(int id, Formula *f): idxAgent(id)
  {
    priority = PRIOR_BOX; 
    children.push_back(f);
    f->father = this;
    father = NULL;
  }


  /**
   * @brief This function will display the Box by:
   * 
   *   - indicating its agent ID 
   *
   *   - calling the display function of its child.
   * 
   * @param[in] f a FILE* if we want to display in a file, by default: standard output.
   */    
  inline void display(FILE *f = stdout)
  {
    fprintf(f, "[r%d]", idxAgent); 
    if(children[0]) children[0]->display(f);

  } // display

  /**
   * @brief This function is returning the type of the current object.
   * 
   * @return IS_BOX.
   */    
  inline int getType(){return IS_BOX;}

};

#endif
