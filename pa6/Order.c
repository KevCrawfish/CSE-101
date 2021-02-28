//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa6
// Order.c
// Uses the Dictionary ADT to print keys from the dictionary
//  in the orders given by the tree traversals.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Dictionary.h"

#define MAX_LINE_LEN 300
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)


int main(int argc, char* argv[]){
  Dictionary D = newDictionary(0);
   FILE *in, *out;
   char word[MAX_LINE_LEN];
   int* pI = calloc(10, sizeof(int));
   for (int i=0; i < 10; i++) pI[i]=i+10;

   ////////////////////////////////////////////////////////
   // check command line for correct number of arguments
   //
   if(argc != 3){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
   }
   //
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   // open files for reading and writing
   //
   in = fopen(argv[1], "r");
   if(in == NULL){
     printf("Unable to open file %s for reading\n", argv[1]);
     exit(1);
   }

   out = fopen(argv[2], "w");
   if(out == NULL){
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
   }
   //
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   // read each line of input file
   // save words from file into tree
   //
   while(fgets(word, MAX_LINE_LEN, in) != NULL){
     insert(D, strdup(word), &pI[8]);
   }
   //
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   // Print ordered tree
   //
   fprintf(out, "******************************************************\nPRE-ORDER:\n******************************************************\n");
   printDictionary(out, D, "pre");
   fprintf(out, "\n\n");
   fprintf(out, "******************************************************\nIN-ORDER:\n******************************************************\n");
   printDictionary(out, D, "in");
   fprintf(out, "\n\n");
   fprintf(out, "******************************************************\nPOST-ORDER:\n******************************************************\n");
   printDictionary(out, D, "post");
   fprintf(out, "\n\n");
   //
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   // close files and free memory
   //
   fclose(in);
   fclose(out);
   free(pI);
   freeDictionary(&D);
   //
   ////////////////////////////////////////////////////////




}
