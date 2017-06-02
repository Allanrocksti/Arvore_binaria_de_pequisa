#include <conio.h>
#include "tree.h"
#include "screens.h"

typedef enum boolean{

    True = 1,
    False = 0

}boolean;

void open_file(char *str[]){

    FILE *file;

    file = fopen("doc.txt", "r");
  
    if (file == NULL) 
        printf("Problemas na abertura do arquivo!\n");
    else
        fscanf(file, "%s", str);
    
    fclose(file);

}

void convert_file_to_vector_int(char text[], int *vector[]){

    char *pch;

    pch = strtok(text, ";");
    
    int i;
    while(pch != NULL){
        
        vetor[i] = atoi(pch);
        pch = strtok(NULL, ";");
        i++;

    }

}

void insert_node(t_tree *tree){
    // isso vai para o main
    char text[100];
    open_file(&text);
    int numbers[10];
    convert_file_to_vector_int(text, &numbers);

    insert_root(tree, numbers[0]);

    int i;
    for(i = 1; i < sizeof(numbers); i++){

        if(compare(numbers[i], tree->dado.number) == -1)
            insert_left(tree, tree->dado.number, numbers[i]);
        else if(compare(numbers[i], tree->dado.number) == 1)
            insert_right(tree, tree->dado.number, numbers[i]);

    }

}

void remove_node(){



}

void search_node(){



}

void empty_tree(){



}

void print_tree(){

    char option;
    boolean exit = False;

    while(exit != True){

        display_tree_menu();
        option = getch();

        switch (option){

            case '1':

                //pre
                system("pause");

                break;

            case '2':

                //in
                system("pause");

                break;

            case '3':

                //pos
                system("pause");

                break;

            case '4':

                //pre g
                system("pause");

                break;

            case '5':

                //in g
                system("pause");

                break;

            case '6':

                //pos g
                system("pause");

                break;

            case '7':

                exit = True;

                break;

            default:

                msg_error();
                system("pause");

                break;

        }

        system("cls");

    }

}