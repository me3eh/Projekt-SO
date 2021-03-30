#include "fun.h"

int main(int argc, char **argv){
    
    if(amount_of_arguments(argc, argv[0]) > 0){
        return EXIT_FAILURE;
    }
    
    FILE * file_check;
    
    if ((file_check = checking_file_valid(argv[1], false)) == NULL)
        return errno;
    
    task * array_of_programs;

    if (( array_of_programs = file_in_good_format(file_check) )== NULL){
        return EINVAL;
    }
    // fclose(file_check);
    // FILE * file;
    // if ((file = checking_file_valid(argv[1], false)) == NULL)
        // return errno;
    int length = daj_ilosc();
    for(int i=0; i< length; ++i){
        printf("Godz:%ld\n", array_of_programs[i].hours);
        printf("Minuty:%ld\n", array_of_programs[i].minutes);
    }
    qsort(array_of_programs, length, sizeof(*array_of_programs), comparator);
    printf("\n");
    for(int i=0; i< length; ++i){    
        printf("Godz:%ld\n", array_of_programs[i].hours);
        printf("Minuty:%ld\n", array_of_programs[i].minutes);
    }
    free(array_of_programs);
    // free(array_of_programs);
    return 0;
}
//komentarz bardzo wazny
//dlk

