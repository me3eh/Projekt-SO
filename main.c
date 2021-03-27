#include "fun.h"

int main(int argc, char **argv){
    
    if(amount_of_arguments(argc, argv[0]) > 0){
        return EXIT_FAILURE;
    }
    
    FILE * file_check;
    
    if ((file_check = checking_file_valid(argv[1], false)) == NULL)
        return errno;
    
    task * array_of_programs;
    
    if (!file_in_good_format(file_check, array_of_programs)){
        fclose(file_check);
        return EINVAL;
    }

    // FILE * file;
    // if ((file = checking_file_valid(argv[1], false)) == NULL)
        // return errno;
    return 1;
}

//komentarz bardzo wazny
//dlk

