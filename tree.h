#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>

void gotoxy(int coluna, int linha){ 

   COORD point;
   point.X = coluna;
   point.Y = linha;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

}
#else
void gotoxy(int x, int y){

   printf("\033[%d;%df", y, x);
   fflush(stdout);

}
#endif

typedef struct element{

    int number;

}t_element;

typedef struct node{

    struct node *left;
    t_element dado;
    struct node *right;

}t_node;

typedef t_node *t_tree;

t_node *create_node(){

    t_node *node = (t_node*) malloc(sizeof(t_node));

    if(node)
        node->left = node->right = NULL;

    return node;

}

int node_is_empty(t_node *node){
    return (node == NULL);
}

int compare(t_element dado1, t_element dado2){
    
    int found;

    if(dado1.number == dado2.number)
        found = 0;
    else if(dado1.number < dado2.number)
        found = -1;
    else
        found = 1;

    return found;

}

t_node *search_node(t_tree tree, t_element dado){

    t_node *found;

    if(tree == NULL)
        return NULL;

    if (compare(tree->dado, dado) == 0 )
        return tree;

    found = search_node(tree->left, dado);

    if(found == NULL)   
        found = search_node(tree->right, dado);

    return found;

}

t_node *search(t_tree tree, t_element dado){

    if(tree == NULL)
        return NULL;
    
    if(compare(tree->dado, dado) > 0)
        return search(tree->left, dado);
    else
        return search(tree->right, dado);

}

int insert_root(t_tree *tree, t_element dado){

    t_node *new;

    if(*tree != NULL)
        return 0;

    new = create_node();

    if(new == NULL)
        return 0;
    
    new->dado = dado;
    *tree = new;

    return 1;

}

void display_pre_order(t_tree tree){

    if(tree != NULL){

        printf("%d ", tree->dado.number);
        display_pre_order(tree->left);
        display_pre_order(tree->right);

    }

}

void display_in_order(t_tree tree){

    if(tree != NULL){

        display_in_order(tree->left);
        printf("%d ", tree->dado.number);
        display_in_order(tree->right);

    }

}

void display_post_order(t_tree tree){

    if(tree != NULL){
        
        display_post_order(tree->left);
        display_post_order(tree->right);
        printf("%d ", tree->dado.number);

    }

}

void display_graphically(t_tree tree, int column, int line, int Displacement){

    if(tree == NULL)
        return;
    
    gotoxy(column, line);
    
    printf("%d", tree->dado.number);

    if(tree->left != NULL)
        display_graphically(tree->left, column - Displacement, line + 2, Displacement / 2 + 1);

    if(tree->right != NULL)
        display_graphically(tree->right, column + Displacement, line + 2, Displacement / 2 + 1);

}

void drain_out(t_tree *tree){

    if(*tree == NULL)
        return;

    drain_out(&(*tree)->left);
    drain_out(&(*tree)->right);
    free(*tree);
    *tree = NULL;

}

t_node *search_set_father(t_tree tree, t_element dado, t_node **father){

    if(tree == NULL){
        *father = NULL;
        return NULL;
    }

    if(compare(tree->dado, dado) == 0)
        return tree;

    if(compare(tree->dado, dado) > 0){
        *father = tree;
        return search_set_father(tree->left, dado, father);
    }else{
        *father = tree;
        return search_set_father(tree->right, dado, father);
    }

}

int remove_element(t_tree *tree, t_element item){

    t_node *node,
           *father,
           *sub,
           *father_suc,
           *suc;

    node = *tree;
    father = NULL;

    node = search_set_father(*tree, item, &father);

    if(node == NULL)
        return 0;

    if(node->left == NULL){
        sub = node->right;
    }else{

        if(node->right == NULL){
            sub = node->left;
        }else{

            father_suc = node;
            sub = node->right;
            suc = sub->left;

            while(suc != NULL){

                father_suc = sub;
                sub = suc;
                suc = sub->left;

            }

            if(father_suc != node){

                father_suc->left = sub->right;
                sub->right = node->left;

            }

            sub->left = node->left;

        }

    }
    
    if (father == NULL){
       *tree = sub;
    }else{
        
        if (node == father->left)
            father->left = sub;
        else
            father->right = sub;

    }

    free(node); 
    return 1;

}

int insert(t_tree *tree, t_element item){

    int ok;

    if(*tree == NULL){

        *tree = create_node();

        if(*tree == NULL)
            return 0;

        (*tree)->dado = item;
        return 1;

    }

    if(compare((*tree)->dado, item) < 0){
        ok = insert(&((*tree)->right), item);
    }else{

        if(compare((*tree)->dado, item) > 0){
            ok = insert(&((*tree)->left), item);
        }else{
            ok = 0;
        }

    }

    return ok;

}