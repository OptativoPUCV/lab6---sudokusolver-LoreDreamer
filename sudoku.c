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

int is_valid(Node *n) {
    int i, j;

    // Check rows
    for (i = 0; i < 9; i++) {
        int row_check[10] = {0};
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (row_check[num] == 1) {
                    return 0;
                } else {
                    row_check[num] = 1;
                }
            }
        }
    }

    // Check columns
    for (j = 0; j < 9; j++) {
        int col_check[10] = {0};
        for (i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (col_check[num] == 1) {
                    return 0;
                } else {
                    col_check[num] = 1;
                }
            }
        }
    }

    // Check submatrices
    for (int k = 0; k < 9; k++) {
        int sub_check[10] = {0};
        for (int p = 0; p < 9; p++) {
            int x = 3 * (k / 3) + (p / 3);
            int y = 3 * (k % 3) + (p % 3);
            int num = n->sudo[x][y];
            if (num != 0) {
                if (sub_check[num] == 1) {
                    return 0;
                } else {
                    sub_check[num] = 1;
                }
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
   
   List* list = createList();
   int i, j;

   for(i = 0; i < 9; i++) {
      for(j = 0; j < 9; j++) {
         
         if(n->sudo[i][j] == 0) {
            
            for(int num = 1; num <= 9; num++) {
               
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = num;
                    pushBack(list, new_node);
               
                }
                return list;
            }
        }
    }
    return list;
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