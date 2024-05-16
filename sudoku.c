#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
} Node;

Node* createNode() {
    
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

    for (int i = 0; i < 9; i++) {
        int row_check[10] = {0};
        
        for (int j = 0; j < 9; j++) {
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

    for (int j = 0; j < 9; j++) {
        int col_check[10] = {0};
        
        for (int i = 0; i < 9; i++) {
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


List* get_adj_nodes(Node* n) {
    
    List* list = createList();
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            
            if (n->sudo[i][j] == 0) {
                
                for (int num = 1; num <= 9; num++) {
                    
                    Node* newNode = copy(n);
                        newNode->sudo[i][j] = num;
                    
                    if (is_valid(newNode))
                        pushBack(list, newNode);
                    else 
                        free(newNode); 
                    
                }
                return list;
            }
        }
    }
    return list;
}



int is_final(Node* n) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont) {
    
    Stack* stack = createStack();
    push(stack, initial);

    while (!is_empty(stack)) {
        Node* current_node = top(stack);
        pop(stack);

        if (is_final(current_node)) {
            return current_node;
        }

        List* adj_nodes = get_adj_nodes(current_node);
        Node* adj_node = first(adj_nodes);

        while (adj_node != NULL) {
            push(stack, adj_node);
            cont[0]++;
            adj_node = next(adj_nodes);
        }
    }

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