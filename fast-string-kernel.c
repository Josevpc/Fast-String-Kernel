#include "suffix_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LongestMatchingPrefix(SUFFIX_TREE* tree, char* W, DBL_WORD P, NODE** c, DBL_WORD* v, int n);
NODE* STR_Floor(NODE *node);

int main (){
	//first string x
	//unsigned char *x = NULL;
	//second string y
	//unsigned char *y = NULL;
	char x[] = "abba";
	char y[] = "ababc";
	
	//lenght of string x
	int n = strlen((const char*)x);
	//lenght of string y
	int m = strlen((const char*)y);
	
	//declaration of the suffix tree of y
	SUFFIX_TREE* treeY;
	
	//constrution of the suffix tree of y
	treeY = ST_CreateTree(y,m);
	
	//lenght of the longest substring of y matching a prefix of x[i:n]
	DBL_WORD *v = (DBL_WORD*) malloc(sizeof(DBL_WORD)*n);

	//**COMENTAR
	NODE **c = (NODE**) malloc(sizeof(NODE)*n);
	
	//Calculo de Vi, ViLinha e Ci;
	int i, j;
	for(i = 0; i < n; i++){
            char token[n-i];
            for(j = 0; j < n-i; j++){
                    token[j] = x[i+j];
            }
			LongestMatchingPrefix(treeY, token, n-i, c, v, n);

			printf("i : %d - v : %lu - v_line: %lu \n", i, v[i], (i+v[i])-1);
			printf("c: ");
			ST_PrintFullNode(treeY, c[i]);
			printf("\n");
 	}
		
	return 0;
}

// --Função ST_findSubstring alterada para retornar o maior prefixo de x que faz combinação com S(y)

void LongestMatchingPrefix(SUFFIX_TREE* tree, char* W, DBL_WORD P, NODE** c, DBL_WORD* v, int n){
   NODE* node   = find_son(tree, tree->root, W[0]);
   DBL_WORD k,j = 0, node_label_end;

   while(node!=0){
      //printf("\n\n%d", n-P);

      k=node->edge_label_start;

      //printf("\nVALOR INICAL DE K: %lu", k);
      //printf("\nVALOR INICAL DE P: %lu", P);

      node_label_end = get_node_label_end(tree,node);

      //printf("\nVALOR DO NODE END: %lu", node_label_end);
      
      /* Scan a single edge - compare each character with the searched string */

      //printf("\ntree = %c : W = %c", tree->tree_string[k], W[j]);

      while(tree->tree_string[k] == W[j]){
         if(j == P){
            break;
         }
         if(k <= node_label_end){
            j++;
            k++;
            if(k > node_label_end && tree->tree_string[k] != W[j]){
               if(find_son(tree, node, W[j]) != NULL){
                  node = find_son(tree, node, W[j]);
				  j++;
				  k++;
               }
            }
         } else {
            node = find_son(tree, node, W[j]);
            break;
         }
         //printf("\nj = %lu : k = %lu", j, k);
         //printf("\ntree = %c : W = %c", tree->tree_string[k], W[j]);
      }
      
      /* Checking which of the stopping conditions are true */

      if(tree->tree_string[k] != W[j] || j == P){
            c[n-P] = node;
            v[n-P] = j;
            break;
      }
   }
}

//Função floor (ainda faltam colocar as verificações)
NODE* STR_Floor(NODE *node){

   return node->father;
}