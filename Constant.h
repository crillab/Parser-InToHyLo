/****************************************************************************************
* Copyright (c) 2016 Artois University
*
* This file is part of Parser-InToHyLo
*
* MDK-Verifier is free software: you can redistribute it and/or modify it 
* under the terms of the GNU General Public License as published by the Free Software Foundation, 
* either version 3 of the License, or (at your option) any later version.
*
* MDK-Verifier is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with MDK-Verifier. 
* If not, see http://www.gnu.org/licenses/.
*
# Contributors:
#       - Jean Marie Lagniez  (lagniez@cril.fr)
#       - Daniel Le Berre     (leberre@cril.fr)
#       - Tiago de Lima       (delima@cril.fr)
#       - Valentin Montmirail (montmirail@cril.fr)
***************************************************************************************************/


#ifndef Constant_h
#define Constant_h

#include "Formula.h"

/**
 * @brief This class represents a TRUE in a Formula
 * 
 * @see Formula
 */
class Top : public Formula
{

 public:

  /** 
      Default constructor of a Top
   */    
  Top(){priority = PRIOR_TOP; father = NULL;}

  inline int getType() { return IS_TRUE; }

  inline void display(FILE *f = stdout) { fprintf(f, "true"); }

};

/* --------------------------------------------------------------------------------------------------------- */

/**
 * @brief This class represents a FALSE in a Formula
 * 
 * @see Formula
 */
class Bottom : public Formula
{

 public:
  		
  /** 
      Default constructor of a Bottom
  */
  Bottom() 
    { 
      priority = PRIOR_BOTTOM; 
      father = NULL; 
    }

  inline int getType() { return IS_FALSE; }

  inline void display(FILE *f = stdout) { fprintf(f, "false"); }
  
};

#endif
