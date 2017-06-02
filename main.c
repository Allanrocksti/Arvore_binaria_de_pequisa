#include "screens.h"
#include "functions.h"
#include "tree.h" 

int main(){

    boolean exit = False;
    char option;
    
    while(exit != True){

        main_menu();
        option = getch();

        switch (option){

            case '1':

                insert_node();
                system("pause");

                break;

            case '2':

                remove_node();
                system("pause");

                break;

            case '3':

                search_node();
                system("pause");

                break;

            case '4':

                empty_tree();
                system("pause");

                break;

            case '5':

                print_tree();
                system("pause");

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