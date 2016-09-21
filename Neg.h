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

#ifndef Neg_h
#define Neg_h

#include "PropositionalVariable.h"
#include "Constant.h"

/**
 * @brief This class represents a NOT in a Formula
 * 
 * @see Formula
 */
class Neg : public Formula {

	public:
  	
  		/** 
  		 * @brief Default constructor, creating a Neg without any child.
  		 */
  		Neg() { father = NULL; }  

  		/**
		* @brief This constructor will create an Neg
		* 
		* this Neg will just have one child : f
		*
		* @param[in] f the child of the Neg
  		*/
  		Neg(Formula *f) 
  		{ 
  			f->father = this; 
  			father = NULL; 
  			priority = PRIOR_NEG; 
  			children.push_back(f); 
  		}  

       /**
      	* @brief This function will display the Neg by: displaying '~' and call display of the child.
      	* 
      	* @param[in] f a FILE* if we want to display in a file, by default: standard output.
      	*/
  		inline void display(FILE *f = stdout) 
  		{ 
  			fprintf(f, "~("); 
  			children[0]->display(f); 
  			fprintf(f, ")"); 
  		}
};

#endif