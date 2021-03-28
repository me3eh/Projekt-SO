#include "fun.h"

int main(int argc, char **argv){
    
    if(amount_of_arguments(argc, argv[0]) > 0){
        return EXIT_FAILURE;
    }
    
    FILE * file_check;
    
    if ((file_check = checking_file_valid(argv[1], false)) == NULL)
        return errno;
    
    task * array_of_programs;
    printf("dup");
    if (( array_of_programs = file_in_good_format(file_check) )== NULL){
        return EINVAL;
    }
    // fclose(file_check);
    // FILE * file;
    // if ((file = checking_file_valid(argv[1], false)) == NULL)
        // return errno;

    for(int i=0; i< 2; ++i)
        printf("%ld", array_of_programs[i].minutes);

    quicksort(array_of_programs, 0,1);
    for(int i=0; i< 2; ++i)
        printf("%ld", array_of_programs[i].minutes);
    free(array_of_programs);
    // free(array_of_programs);
    return 0;
    // free(array_of_programs);
// for(int i=0; i< 2; ++i)
    // printf("%s", array_of_programs[i].program);
}
//komentarz bardzo wazny
//dlk

