#This file is modified to run the RSA algorithm
#author : Md Jubaer Hossain Pantho

################
# Paths and Flags
################
SHELL = /bin/bash
TARGET_PATH = ../bin
TARGET_NAME_OPT = obj
OBJ_PATH = ../$(TARGET_NAME_OPT)
UNAME = $(shell uname -s)
COMPILER=g++
CFLAGS = -Wall -Wvla -pedantic -std=c++11
OPT_LFLAGS = 
OPT_CFLAGS = $(CFLAGS) -O3

################
# Source
################

CPP_FILES =\
	main.cpp\
	BigInteger.cpp\
	RSABigInteger.cpp\

################
# Lists
################

TEMP_LIST_OPT = $(CPP_FILES:%=$(OBJ_PATH)/%)
OBJECTS_OPT = $(TEMP_LIST_OPT:%.cpp=%.o)
DEPS_OPT = $(TEMP_LIST_OPT:%.cpp=%.d)

################
# Rules
################

.DELETE_ON_ERROR:

opt : $(TARGET_PATH)/$(TARGET_NAME_OPT)

usage:


# This rule makes the optimized binary by using g++ with the optimized ".o" files
$(TARGET_PATH)/$(TARGET_NAME_OPT) : partialcleanopt $(OBJECTS_OPT)
	@if [ ! -d "$(TARGET_PATH)" ]; then mkdir -p "$(TARGET_PATH)"; fi
	g++ $(OPT_CFLAGS) -o $(TARGET_PATH)/$(TARGET_NAME_OPT) $(OBJECTS_OPT) $(OPT_LFLAGS)


# This includes all of the ".d" files. Each ".d" file contains a
# generated rule that tells it how to make .o files. (The reason these are generated is so that
# dependencies for these rules can be generated.)
-include $(DEPS_OPT)

# This rule makes the optimized ".d" files by using "g++ -MM" with the corresponding ".cpp" file
# The ".d" file will contain a rule that says how to make an optimized ".o" file.
# "$<" refers to the ".cpp" file, and "$@" refers to the ".d" file
$(DEPS_OPT) : $(OBJ_PATH)/%.d : %.cpp
	@if [ "$${USER}" == "root" ]; then false; fi # don't generate dependencies as root
	@echo -e "Computing opt dependencies for $<"
	@-rm -f $$(dirname $@)/$$(basename $@ .d).o
	@if [ ! -d "$$(dirname $@)" ]; then mkdir -p "$$(dirname $@)"; fi
	@echo -en "$$(dirname $@)/" > $@
	@$(COMPILER) $(OPT_CFLAGS) -MM $< >> $@
	@echo -e "	$(COMPILER) $(OPT_CFLAGS) -c $< -o $$(dirname $@)/$$(basename $@ .d).o" >> $@



partialcleanopt :
	rm -f $(TARGET_PATH)/$(TARGET_NAME_OPT)

clean : partialcleanopt
	rm -f $(OBJECTS_OPT)
	rm -f $(DEPS_OPT)

.PHONY: clean partialcleanopt install uninstall opt
