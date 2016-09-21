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

#ifndef SyntacticAnalysis_h
#define SyntacticAnalysis_h

#include "LexicalAnalysis.h"
#include "And.h"
#include "Equiv.h"
#include "Neg.h"

using namespace std;

/** 
 * @brief This class will perform a Shift and Reduce on our input Formula 
 */
class SyntacticAnalyser
{

  public:
    
   /**
    * @brief Constructor of the Syntactic Analyser 
    * 
    * It will call the LexicalAnalyser on the input file in parameter 
    * 
    * @param[in] file the filename of our input formula in InToHyLo 
    */
    SyntacticAnalyser(const char *file) { lx = new LexicalAnalyser(file); }

    /** @brief Destructor of the SyntaxticAnalyser */
    ~SyntacticAnalyser() { delete lx; }

   /**
    * @brief Parse the file (saved in lx) to extract the formula.
    * 
    * @param[out] formulas the formula that we extracted from the parsed file.
    */
    void parseFormula(vector<Formula *> &formulas);

   /** 
    * @brief This function return the parsed formula 
    * 
    * @return the parsed formula
    */
    inline Formula *getFormula()
    {
      assert(stackToken.size() == 1);
      assert(stackFormula.size() == 1);

      Formula *ret = stackFormula[0];
      prepareParser();
      return ret;
    }
    
   /**
    * @brief this function will clean the 2 stacks (token and formula elements)
    */
    inline void prepareParser()
    {
      stackToken.clear();
      stackFormula.clear();
    }

   /**
    * @brief This function will push an unary element
    * 
    * @param[in] tk our token. It can be a {Box,Diamond,Not,Imply,Equiv,Or,And}
    *
    * @param[in] id the agent ID in case of Box and Diamond.
    */ 
    inline void pushUnary(int tk, int id = 0)
    {
      
      Formula *f = NULL;
      switch(tk) {

        case BOX: 
          f = new Box(id);
          break;
        case DIAMOND:
          f = new Diamond(id);
          break;
        case NOT:
          f = new Neg();
          break;
        case IMPLY:
          f = new Imply();
          break;
        case EQUIV:
          f = new Equiv();
          break;
        case OR:
          f = new Or();
          break;
        case AND:
          f = new And();
          break;
      }
          
      stackToken.push_back(tk);
      stackFormula.push_back(f);
      assert(f);
    } // pushUnary

    /** 
     * @brief This function will push a NULL token
     * 
     * @param[in] tk our token.
     */
    inline void pushNull(int tk)
    {
      stackFormula.push_back(NULL);
      stackToken.push_back(tk);
    } // pushNull
    
   /**
    * @brief This function will merge the stacks
    * 
    * @param[in] v1 should be stackToken[size()-3]
    *
    * @param[in] v2 should be stackToken[size()-2]
    *
    * @param[in] v3 should be stackToken[size()-1]
    */
    inline void merge(int v1, int v2, int v3)
    { 
      unsigned int size = stackToken.size();

      assert(size > 2);

      assert(stackToken[size - 3] == v1);
      assert(stackToken[size - 2] == v2);
      assert(stackToken[size - 1] == v3);
    
      stackFormula[stackFormula.size() - 3] = stackFormula[stackFormula.size() - 2];
      stackFormula.pop_back(); 
      stackFormula.pop_back();

      stackToken[stackToken.size() - 3] = stackToken[stackToken.size() - 2];          
      stackToken.pop_back(); 
      stackToken.pop_back();

      assert(stackToken.size() == stackFormula.size());
    }

   /**
    * @brief Combine elements on the stack.
    * 
    * @return true if everything is ok, false otherwise.
    */
    inline bool reduce();

  private:
    
    /** @brief The Lexical Analyser of our Formula */
    LexicalAnalyser *lx;

    /** @brief By using Shift and Reduce, we will stack every element of our Formula */
    vector<Formula *> stackFormula;

    /** @brief By using Shift and Reduce, we will stack every token */
    vector<int> stackToken;

};

#endif
