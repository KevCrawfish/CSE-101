#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                     makes Lex
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make check1              checks DictionaryClient for memory leaks
#  make check2              checks Lex for memory leaks on in4
#------------------------------------------------------------------------------

TOP              = Lex
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = $(ADT)Client
TEST2            = $(ADT)Test
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
TEST2_OBJ        = $(TEST2).o
TEST2_SRC        = $(TEST2).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c -g
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)

$(TEST) : $(TEST_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

$(TEST2) : $(TEST2_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST2) $(TEST2_OBJ) $(ADT_OBJ)

$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)

$(TEST_OBJ) : $(TEST_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC)

$(TEST2_OBJ) : $(TEST2_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST2_SRC)

$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST_OBJ) $(TEST2) $(TEST2_OBJ) $(ADT_OBJ)

check1 : $(TEST)
	$(MEMCHECK) $(TEST)

check2 : $(TOP)
	$(MEMCHECK) $(TOP) in4 junk4
