#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   int fil[10], col[10], subMatrix[10];
   
   //verificar filas
   for (int i = 0; i < 9; i++)
   {
      for (int k = 0; k < 10; k++) fil[k] = 0;

      for (int j = 0; j < 9; j++)
      {
         int num = n->sudo[i][j];
         if (num != 0)
         {
            if (fil[num] == 1) return 0;
            fil[num] = 1;
         }
      }
   }
   
   //verificar columanas
   for (int j = 0; j<9; j++)
   {
      for (int k = 0; k < 10; k++) col[k] = 0;

      for (int k = 0; k < 9; k++)
      {
         int num = n->sudo[k][j];
         if (num != 0)
         {
            if (col[num] == 1) return 0;
            col[num] = 1;
         }
      }
   }

   //verificar submatrices 3x3
   for (int k = 0; k < 9; k++) 
   {
   
      for (int m = 0; m < 10; m++) subMatrix[m] = 0;

      for (int p = 0; p<9; p++)
      {
         int i = 3 * (k / 3) + (p % 3) ;
         int j = 3 * (k % 3) + (p / 3) ;
         int num = n->sudo[i][j];
         if (num != 0)
         {
            if (subMatrix[num] == 1) return 0;
            subMatrix[num] = 1;
         }
      } 
   }
   
   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   int fil = -1, col = -1;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
         {
            if (n->sudo[i][j] == 0)
            {
               fil = i;
               col = j;
               break;
            }
         }
      if (fil != -1) break;
      
   }

   //si no hya casillas vacias, retorna NULL (o en su defecto la lista vacia)
   if (col == -1) return list;

   List* adj_node = createList();
   for (int val = 1; val <= 9; val++)
      {
         Node* new_node = copy(n);
         new_node->sudo[fil][col] = val;
         if (is_valid(new_node))
            pushBack(adj_node, new_node);
         else 
            free(new_node);
      }
   
   return adj_node;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/