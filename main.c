//#include "functions.h"
#include <conio.h>
#include "screens.h"
#include "tree.h" 

typedef enum boolean{

    True = 1,
    False = 0

}t_boolean;

t_boolean is_number(char string[]){

    t_boolean is_number = True;

    int i,
        y,
        aux;

    for(i = 0; string[i] != '\0'; i++){

        aux = 48;
        for(y = 0; y < 10; y++){

            if(string[i] == aux)
                break;
            
            if(y == 9)
				is_number = False;
				
			aux++;
				

        }

        if(is_number == False)
            break;

    }

    return is_number;

}

int main(){

    t_boolean exit = False;
    char option;

    FILE *file;

    char text[100];
    int numbers[9];

    file = fopen("doc.txt", "r");
  
    if (file == NULL) 
        printf("Problemas na abertura do arquivo!\n");
    else
        fscanf(file, "%s", text);
    
    fclose(file);
    
    char *pch;
    pch = strtok(text, ";");
    
    int i;
    while(pch != NULL){
        
        numbers[i] = atoi(pch);
        pch = strtok(NULL, ";");
        i++;

    }

    t_tree tree = NULL;
    t_element aux;

    for(i = 0; i < 9; i++){
        aux.number = numbers[i];
        insert(&tree, aux);
    }

    char number_insert[100];
    int number_node;

    while(exit != True){

        main_menu();
        option = getch();

        switch (option){

            case '1':

                system("cls");
                printf("\n\nDIGITE UM NUMERO PARA SER INSERIDO: ");
                gets(number_insert);

                if(is_number(number_insert) == True){
                    number_node = atoi(number_insert);
                    aux.number = number_node;
                    insert(&tree, aux);
                    printf("\nINSERIDO COM SUCESSO !\n\n");
                    system("pause");
                }else{
                    printf("\nDIGITE UM NUMERO INTEIRO !\n\n");
                    system("pause");
                }

                

                break;

            case '2':

                system("cls");
                printf("\n\nDIGITE UM NUMERO PARA SER REMOVIDO: ");
                gets(number_insert);

                int status;

                if(is_number(number_insert) == True){

                    number_node = atoi(number_insert);
                    aux.number = number_node;
                    status = remove_element(&tree, aux);    

                    if(status == 1)
                        printf("\nREMOVIDO COM SUCESSO !\n\n");
                    else
                        printf("\nNUMERO INEXISTENTE !\n\n");

                }else{
                    printf("\nDIGITE UM NUMERO INTEIRO !\n\n");
                }

                system("pause");

                break;

            case '3':

                system("cls");
                printf("\n\nDIGITE UM NUMERO PARA SER PESQUISADO: ");
                gets(number_insert);

                t_node *aux_search;

                if(is_number(number_insert) == True){
                
                    number_node = atoi(number_insert);
                    aux.number = number_node;
                    aux_search = search_node(tree, aux);

                    
                    if(aux_search != NULL)
                        printf("\nO NUMERO %d EXISTE NA ARVORE!\n\n", number_insert);
                    else
                        printf("\nNUMERO INEXISTENTE!\n\n");

                }else{
                    printf("\nDIGITE UM NUMERO INTEIRO !\n\n");
                }

                system("pause");

                break;

            case '4':

                drain_out(&tree);
                printf("\n\nESVAZIADA COM SUCESSO !\n\n");
                system("pause");

                break;

            case '5':

                if(tree != NULL){

                    printf("\nPRE ORDEM: ");
                    display_pre_order(tree);
                    printf("\nIN ORDEM: ");
                    display_in_order(tree);
                    printf("\nPOS ORDEM: ");
                    display_post_order(tree);
                    printf("\n\n");
                    system("pause");
                    system("cls");
                    printf("\nPRE ORDEM GRAFICO: \n\n");
                    display_graphically(tree, 10, 10, 3);
                    printf("\n\n");
                    system("pause");
                
                }else{
                    printf("\n\nARVORE VAZIA!\n\n");
                    system("pause");
                }

                break;

            case '0':

                printf("\nEncerrando programa...\n");
                system("pause");
                exit = True;

                break;

            default:

                msg_error();
                system("pause");

                break;

        }

        system("cls");

    }

    return 0;

}
