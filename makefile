#****************************************************************************************
#* Copyright (c) 2016 Artois University
#*
#* This file is part of Parser-InToHyLo
#*
#* MDK-Verifier is free software: you can redistribute it and/or modify it 
#* under the terms of the GNU General Public License as published by the Free Software Foundation, 
#* either version 3 of the License, or (at your option) any later version.
#*
#* MDK-Verifier is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
#* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
#* See the GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License along with MDK-Verifier. 
#* If not, see http://www.gnu.org/licenses/.
#*
#* Contributors:
#*      - Jean Marie Lagniez  (lagniez@cril.fr)
#*       - Daniel Le Berre     (leberre@cril.fr)
#*       - Tiago de Lima       (delima@cril.fr)
#*       - Valentin Montmirail (montmirail@cril.fr)
#***************************************************************************************************/

# compiler :
COMPILER = g++

COPTIONS = -O3 -Wall -Wextra -Wno-unused-parameter -std=c++11

#LOPTIONS += -static

UNAME_S := $(shell uname -s)

EXECUTABLE = parser-intohylo

# -------------------------------------------------------------------
#  Emplacement des sources et des objets, des includes et de l'executable
# -------------------------------------------------------------------

# path:
CODE = $(shell pwd)

# folder for the executable 
EXEDIR = $(CODE)/bin

# adress of the source code, objects and include files:
SRCDIR = $(CODE)
OBJDIR = $(CODE)/obj

# create the list of file sources:
SRC = $(wildcard $(SRCDIR)/*.cc)

# list the files:
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(NOM)))

.PHONY: help

# link edition
install: faire_dossier $(OBJ) 
	$(COMPILER) -o $(EXEDIR)/$(EXECUTABLE) $(OBJ) $(LOPTIONS)

# rules to do the folders
faire_dossier: makedir
	@echo "folders created"

# compilation rules
$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(SRCDIR)/%.h
	$(COMPILER) -c $(COPTIONS) -o $@ $< $(LOPTIONS)

# -------------------------------------------------------------------
#  to create the objects folder
# -------------------------------------------------------------------

# creation of the folder $(OBJDIR) if it is necessary:
makedir: 
	mkdir -p $(OBJDIR)
	mkdir -p $(EXEDIR)

# -------------------------------------------------------------------
#  cleaning rules
# -------------------------------------------------------------------

.PHONY: clean purge

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(EXEDIR)
	@rm -rf *~


help:
	@echo "--------------------------------------------------------------------------"
	@echo " Disponible rules"
	@echo
	@echo " install : compilation and executable creation"
	@echo " clean   : remove the object files"
	@echo " purge   : remove the object files and the executable"
	@echo " help    : print this comments (defautl)"
	@echo "--------------------------------------------------------------------------"
	@echo
