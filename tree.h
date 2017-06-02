#include <stdio.h>
#include <stdlib.h>

typedef struct element{

    int number;

}t_element;

typedef struct node{

    struct no *left;
    t_element dado;
    struct no *right;

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

int insert_right(t_tree tree, t_element father, t_element son){

    t_node *aux_son,
           *aux_father,
           *new;

    aux_son = search_node(tree, son);
    if(aux_son != NULL) 
        return 0;

    aux_father = search_node(tree, father);
    if(aux_father != NULL) 
        return 0;
    
    if (aux_father->right != NULL)
        return 0;

    new->dado = son;
    aux_father->right = new;
    return 1;

}

int insert_left(t_tree tree, t_element father, t_element son){

    t_node *aux_son,
           *aux_father,
           *new;

    aux_son = search_node(tree, son);
    if(aux_son != NULL) 
        return 0;

    aux_father = search_node(tree, father);
    if(aux_father != NULL) 
        return 0;
    
    if (aux_father->left != NULL)
        return 0;

    new->dado = son;
    aux_father->left = new;
    return 1;

}

void display_pre_order(t_tree tree){

    if(tree != NULL){

        printf("%d", tree->dado.number);
        display_pre_order(tree->left);
        display_pre_order(tree->right);

    }

}

void display_in_order(t_tree tree){

    if(tree != NULL){

        display_in_order(tree->left);
        printf("%d", tree->dado.number);
        display_in_order(tree->right);

    }

}

void display_post_order(t_tree tree){

    if(tree != NULL){
        
        display_post_order(tree->left);
        display_post_order(tree->right);
        printf("%d", tree->dado.number);

    }

}

void display_graphically(t_tree tree, int column, int line, int Displacement){

    if(tree == NULL)
        return;
    
    gotoxy(column, line);
    
    printf("%s", tree->dado.number);

    if(tree->left != NULL)
        display_graphically(tree->left, column - Displacement, line + 2, (Displacement / 2) + 1);

    if(tree->right != NULL)
        display_graphically(tree->right, column - Displacement, line + 2, (Displacement / 2) + 1);

}

int drain_out(t_tree *tree){

    if(*tree == NULL)
        return 0;

    drain_out(&(*tree)->left);
    drain_out(&(*tree)->right);
    free(*tree);
    *tree = NULL;

    return 1;

}