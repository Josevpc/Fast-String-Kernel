#include "suffix_tree.h"
#include "fast-string-kernel.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*DECLARATION OF TOOLS FOR SUFFIX TREE*/
NODE *NODE_FLOOR(NODE *node);

int NODE_LVS(NODE *node);

int NODE_COUNT_LVS(NODE *node);

/*DECLARATION OF MACHING STATISTICS*/
void MATCHING_STATISTICS(SUFFIX_TREE *tree, char *W, NODE **c, DBL_WORD *v);

/*DECLARATION OF FAST STRING KERNEL*/
float FSK_VAL(SUFFIX_TREE *tree, NODE *c, DBL_WORD v, char *weight, float aux);

float FSK_WEIGHT(SUFFIX_TREE *tree, NODE *c, DBL_WORD v, char *weight, float aux);

/*REAL FUNCTIONS*/
void MATCHING_STATISTICS(SUFFIX_TREE *tree, char *W, NODE **c, DBL_WORD *v)
{
   NODE *node = tree->root;

   NODE *son;

   DBL_WORD j = 0, k = 0, i; // Declaração dos indices j, k e i

   // j refere-se a posição inicial da string W
   // k realiza o passo verificando se a variavel é igual a letra

   for (i = 0; i < strlen((const char *)W); i++)
   {
      son = find_son(tree, node, W[j]);

      while ((j < k) && (j + get_node_label_length(tree, son) <= k))
      {
         node = son;
         j = j + (get_node_label_length(tree, node));
         son = find_son(tree, node, W[j]);
      }

      if (j == k)
      {
         while (son != NULL && W[k] == tree->tree_string[son->edge_label_start + k - j])
         {
            k++;
            if (j + get_node_label_length(tree, son) == k)
            {
               node = son;
               j = k;
               son = find_son(tree, node, W[j]);
            }
         }
      }

      v[i] = k - i;

      if (j == k)
      {
         c[i] = node;
      }
      else
      {
         c[i] = find_son(tree, node, W[j]);
      }

      if (node == tree->root && j == k)
      {
         j++;
         k++;
      }

      if (node == tree->root && j < k)
      {
         j++;
      }

      if (node != tree->root)
      {
         node = node->suffix_link;
      }
   }
   node = 0;
   son = 0;

   free(node);
   free(son);
}

NODE *NODE_FLOOR(NODE *node)
{
   return node->father;
}

int NODE_LVS(NODE *node)
{
   // Verifica se o NODE possui filhos.
   if (node->sons != 0)
   {
      // Se o NODE possuir filhos, número de folhas da subárvore vai ser retornado pela função NODE_COUNT_LVS
      return NODE_COUNT_LVS(node);
   }
   else
   {
      // Senão o NODE é uma folha, assim será retornado 0;
      return 0;
   }
}

int NODE_COUNT_LVS(NODE *node)
{
   // Verifica se o NODE possui filhos, se não possuir o mesmo será uma folha.
   if (node->sons == 0)
   {
      return 1;
   }

   // Node recebe o primeiro filho. (os filhos estão ordenados em uma lista encadeada)
   node = node->sons;

   // Verifica se o Node selecionado anteriormente não possui um irmão a direita.
   if (node->right_sibling == 0)
   {
      // Caso o NODE não possua um irmão
      // Verifica se o NODE possui filhos
      if (node->sons != 0)
      {
         // Se possuir retorna a função mandando o primeiro filho da lista
         return (NODE_COUNT_LVS(node->sons));
      }
      else
      {
         // Se não possuir o NODE é uma folha então retorna 1;
         return 1;
      }
   }
   // Faz a chamada da função descendo a árvore para os filhos do node atual e soma com a chamada da função do node irmão ao node atual
   return NODE_COUNT_LVS(node) + NODE_COUNT_LVS(node->right_sibling);
}

float FSK_VAL(SUFFIX_TREE *tree, NODE *c, DBL_WORD v, char *weight, float aux)
{
   if (c == tree->root)
   {
      return 0;
   }
   else
   {
      return NODE_LVS(c) * FSK_WEIGHT(tree, c, v, weight, aux) + FSK_VAL(tree, NODE_FLOOR(c), get_node_label_end(tree, NODE_FLOOR(c)), weight, aux);
   }
}

float FSK_WEIGHT(SUFFIX_TREE *tree, NODE *c, DBL_WORD v, char *weight, float aux)
{
   float w_t = 0, w_floor = 0;

   w_t = v; // τ := |t|

   w_floor = get_node_label_length(tree, NODE_FLOOR(c)); // γ := | floor(t)|

   if (strcmp(weight, "const") == 0) // CONSTANT WEIGHT
   {
      return w_t - w_floor;
   }
   else if (strcmp(weight, "exp") == 0) // EXPONENCIAL DECAY
   {
      float lambda = aux;

      return (pow(lambda, -w_floor) - pow(lambda, -w_t)) / (lambda - 1);
   }
   else if (strcmp(weight, "bound") == 0) // BOUNDED RANGE
   {
      int n = aux;

      return MAX(0, MIN(w_t, n) - w_floor);
   }
   else if (strcmp(weight, "bag") == 0) // BAG OF CHARACTERS
   {
      if (w_floor == 0)
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }
   else {
      //Como default está colocado o peso constante
      return w_t - w_floor;
   }
}

double FAST_STRING_KERNEL(char *x, char *y, char *weight, float aux)
{
   // lenght of string x
   int n = strlen((const char *)x);
   // lenght of string y
   int m = strlen((const char *)y);

   // declaration of the suffix tree of y
   SUFFIX_TREE *SY;

   // constrution of the suffix tree of y
   SY = ST_CreateTree(y, m);

   // lenght of the longest substring of y matching a prefix of x[i:n]
   DBL_WORD *v = (DBL_WORD *)malloc(sizeof(DBL_WORD) * n);

   //**COMENTAR
   NODE **c = (NODE **)malloc(sizeof(NODE) * n);

   // Calculo de Vi e Ci;
   MATCHING_STATISTICS(SY, x, c, v);

   int i;
   double kernel_return = 0;

   for (i = 0; i < n; i++)
   {
      kernel_return += FSK_VAL(SY, c[i], v[i], weight, aux);
      
      c[i] = 0;
      free(c[i]);
   }
   free(c);
   free(v);

   ST_DeleteTree(SY);

   return kernel_return;
}