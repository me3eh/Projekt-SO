#include "fun.h"

int main(int argc, char **argv){

    if(amount_of_arguments(argc, argv[0]) > 0){
        return EXIT_FAILURE;
    }
    if (checking_file_valid(argv[1], false) == NULL)
        return errno;
    printf("fufufu\n");
    return 1;
}

//komentarz bardzo wazny
//dlk

