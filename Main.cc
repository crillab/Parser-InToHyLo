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

#include <algorithm>
#include <sys/types.h>
#include <sys/wait.h>

#include "SyntacticAnalysis.h"


/**
 * @brief This function will display a help message to explain the user how to use the solver.
 * 
 * @param[in] arg0 the name of the program (which is the argv[0] in the main.
 */
inline void help(char* arg0) 
{
  std::cout << "c ------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  std::cout << "c " << std::endl;
  std::cout << "c Execute as follow: " << arg0 << " ./path-to-InToHyLo formula"                                                                                     << std::endl;
  std::cout << "c " << std::endl;
  std::cout << "c ------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  std::cout << "c This file may contain multiple intohylo formula, all embedded between 'begin' and 'end'. "                                                        << std::endl;
  std::cout << "c An InToHyLo formula is constructed recursively as follow: "                                                                   << std::endl << "c" << std::endl;
  std::cout << "c\t $file$ ::= begin $formula$ end "          << std::endl << "c" << std::endl;
  std::cout << "c\t $formula$ ::= ( $formula$ ) "           << std::endl;
  std::cout << "c\t      |    ::= true"                     << std::endl;
  std::cout << "c\t      |    ::= false"                    << std::endl;
  std::cout << "c\t      |    ::= p$id$"                    << std::endl;
  std::cout << "c\t      |    ::= ~$formula$"               << std::endl;
  std::cout << "c\t      |    ::= [r$id$] $formula$ "       << std::endl;
  std::cout << "c\t      |    ::= <r$id$> $formula$ "       << std::endl; 
  std::cout << "c\t      |    ::= $formula$ & $formula$"    << std::endl;
  std::cout << "c\t      |    ::= $formula$ | $formula$"    << std::endl;
  std::cout << "c\t      |    ::= $formula$ -> $formula$"   << std::endl;
  std::cout << "c\t      |    ::= $formula$ <-> $formula$"  << std::endl;
  std::cout << "c" << std::endl;
  std::cout << "c\t Where identifiers $id$ are numerical sequences. "                                                                                                 << std::endl;
  std::cout << "c ================================================================================================================================================" << std::endl;

  exit(1);

} // help


inline void displayFormulas(vector<Formula*> & formulas)
{
 
  for(const auto & formula : formulas) 
  {
    formula->display(stdout);
    std::cout << std::endl;    
  }

} // displayFormulas


/**
   This function is the main entrance of the program. 
   
   @param[in] argc the number of arguments for the main.
   @param[in] argv all the arguments of the main in a format char*.
   
   \return 0 if everything went as expected, something else otherwise.
*/
int main(int argc, char **argv) 
{

  vector<Formula *> formulas;

  setbuf(stdout, NULL);
  if(argc <= 1) help(argv[0]);

  SyntacticAnalyser sx(argv[1]);
  sx.parseFormula(formulas);
 
  displayFormulas(formulas); 

  formulas.clear();

  return 0;
} // main

