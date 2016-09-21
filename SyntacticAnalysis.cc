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

#include "SyntacticAnalysis.h"

/**
 * @brief Parse the file (saved in lx) to extract the formula.
 * 
 * @param[out] formulas the formula that we extracted from the parsed file.
 */
void SyntacticAnalyser::parseFormula(vector<Formula *> &formulas)
{
  prepareParser();
  int tk = lx->nextToken(), id = lx->currentValue;

  while(tk != END_FILE)
    {  
      while(tk == COMMENT){lx->eatLine(); tk = lx->nextToken(); id = lx->currentValue;}

      if(tk == PROPOSITIONAL || tk == TRUE || tk == FALSE) // simple formula
        {
          switch(tk)
            {
            case PROPOSITIONAL : stackFormula.push_back(new PropositionalVariable(id)); break;
            case TRUE : stackFormula.push_back(new Top()); break;
            case FALSE : stackFormula.push_back(new Bottom()); break;
            }
          stackToken.push_back(FORMULA);
        }
      else if(tk == PAR_LEFT || tk == BEGIN || tk == PAR_RIGHT || tk == END) pushNull(tk);
      else if(tk == BOX || tk == DIAMOND) pushUnary(tk, id);      
      else if(tk == NOT || tk == IMPLY || tk == EQUIV || tk == OR || tk == AND) pushUnary(tk);

      while(tk != COMMENT && reduce());

      if(tk == END) formulas.push_back(getFormula());
      
      tk = lx->nextToken();
      id = lx->currentValue;      
    }
} // parseFormula

/**
 * @brief Combine elements on the stack.
 * 
 * @return true if everything is ok, false otherwise.
 */
extern inline bool SyntacticAnalyser::reduce()
{
    
  if(stackToken.size() < 3) return false; 

  // we always have BEGIN as first element
  assert(stackToken[0] == BEGIN);
  assert(stackToken.size() == stackFormula.size());

  int last = stackToken.size() - 1;

  if(stackToken[last] == FORMULA)
    {
      switch(stackToken[last - 1])
        {
        case BOX :
        case DIAMOND :
        case NOT :
          stackFormula[last - 1]->addChild(stackFormula[last]);
          stackToken[last - 1] = FORMULA;
          stackFormula.pop_back(); stackToken.pop_back();            
          assert(stackToken.size() == stackFormula.size());            
          return true;
        }        
    }

  else if(stackToken[last] == PAR_RIGHT || stackToken[last] == END)
    {
      if(stackToken[last - 1] == FORMULA && stackToken[last - 2] == PAR_LEFT) merge(PAR_LEFT, FORMULA, PAR_RIGHT);
      else if(stackToken[last - 1] == FORMULA && stackToken[last - 2] == BEGIN) merge(BEGIN, FORMULA, END);
      else
        {            
          assert(stackToken.size() > 4);
          assert(stackToken[last - 1] == FORMULA && stackToken[last - 3] == FORMULA);
          
          stackFormula[last - 2]->addChild(stackFormula[last - 3]);
          stackFormula[last - 2]->addChild(stackFormula[last - 1]);
            
          stackFormula[last - 3] = stackFormula[last - 2];
          stackFormula[last - 2] = stackFormula[last];
          stackToken[last - 3] = FORMULA;
          stackToken[last - 2] = stackToken[last];
            
          stackFormula.pop_back(); stackFormula.pop_back();
          stackToken.pop_back(); stackToken.pop_back();
        }
      assert(stackToken.size() == stackFormula.size());
      return true;
    }

  else if(stackToken[last] == AND || stackToken[last] == OR || stackToken[last] == IMPLY || stackToken[last] == EQUIV)
    {
      if(stackToken[last - 2] == AND || stackToken[last - 2] == OR || stackToken[last - 2] == IMPLY || stackToken[last - 2] == EQUIV)
        {
          if(stackFormula[last]->priority <= stackFormula[last - 2]->priority)
            {
              assert(stackFormula.size() > 4);
              stackFormula[last - 2]->addChild(stackFormula[last - 3]);
              stackFormula[last - 2]->addChild(stackFormula[last - 1]);

              stackFormula[last - 3] = stackFormula[last - 2];
              stackFormula[last - 2] = stackFormula[last];
              stackToken[last - 3] = FORMULA;
              stackToken[last - 2] = stackToken[last];

              stackFormula.pop_back(); stackFormula.pop_back();
              stackToken.pop_back(); stackToken.pop_back();
              assert(stackToken.size() == stackFormula.size());
              return true;
            }
        }
    }

  assert(stackToken.size() == stackFormula.size());
  return false;

} // reduce
