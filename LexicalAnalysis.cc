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

#include "LexicalAnalysis.h"

/**
 * @brief Read the flux and return the next token. 
 * The value is also save.
 * 
 * @return the next token.
 */
int LexicalAnalyser::nextToken()
{
  if(savedToken.size())
    {
      int ret = savedToken.back();
      savedToken.pop_back();
      currentValue = savedId.back();
      savedId.pop_back();
      return ret;
    }
  
  if(cin == NULL) 
  {
    std::cerr << "c Problem with the file: Not existing or not enough rights to open it... " << std::endl;
    std::cerr << "c The solver will not abort its execution..." << std::endl;
    exit(-1);
  }

  int c = getc(cin);
  while(c == ' ' || c == '\t' || c == '\n') c = getc(cin);
   
  if(c == '#') return COMMENT;

  else if(c == '<')
    {
      c = getc(cin);
      switch(c)
        {
        case '-' : c = getc(cin);             if(c == '>') return EQUIV;   else break;
        case 'r' : parseInt(); c = getc(cin); if(c == '>') return DIAMOND; else break;
        }
    }

  else if(c == '-')
    {
      c = getc(cin);
      if(c == '>') return IMPLY;      
    }

  else if(c == '[')
    {
      c = getc(cin);
      if(c == 'r') { parseInt(); c = getc(cin); if(c == ']') return BOX; }
    }

  else if(c == '&') return AND;
  else if(c == '|') return OR;
  else if(c == '~') return NOT;
  else if(c == '(') return PAR_LEFT;
  else if(c == ')') return PAR_RIGHT;
  else if(c == 't' || c == 'T') return checkWord("true", 1) ? TRUE : ERROR;
  else if(c == 'f' || c == 'F') return checkWord("false", 1) ? FALSE : ERROR;
  else if(c == 'b' || c == 'B') return checkWord("begin", 1) ? BEGIN : ERROR;
  else if(c == 'e' || c == 'E') return checkWord("end", 1) ? END : ERROR;
  else if(c == 'r' || c == 'R') return RELATION;

  else if(c == 'p' || c == 'P')
    {
      parseInt();
      return PROPOSITIONAL;
    }

  else if(c == EOF) return END_FILE;

  std::cerr << "c Error Lexical Analysis: the character " << (char) c << " is unknown" << std::endl;
  exit(2);
} // nextToken

/** 
 * @brief This function check if the word s starts at the position 'start'
 * 
 * @param[in] s the word that we are checking
 * 
 * @param[in] start the index of the first character.
 *
 * @return true if the word starts, false otherwise.
 */ 
bool LexicalAnalyser::checkWord(string s, int start)
{
  for(unsigned int i = start ; i<s.size() ; i++)
    {
      int c = getc(cin);
      if(c != s[i] && c != (s[i] - 'a' + 'A') && c != (s[i] - 'A' + 'a')) return false;
    }
  return true;

} // checkWord

