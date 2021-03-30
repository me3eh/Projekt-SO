#include "fun.h"

int main(int argc, char **argv){
    
    if(amount_of_arguments(argc, argv[0]) > 0){
        return EXIT_FAILURE;
    }
    
    FILE * file_check;
    
    if ((file_check = checking_file_valid(argv[1], false)) == NULL)
        return errno;
    
    task* array_of_programs;

    if (( array_of_programs = file_in_good_format(file_check) )== NULL){
        return EINVAL;
    }
    int length = daj_ilosc();
    set_time_to_exec(array_of_programs, length);
    qsort(array_of_programs, length, sizeof(*array_of_programs), comparator);
    set_time_to_sleep(array_of_programs, length);

    for(int i=0; i< length; ++i){    
        printf("Godz:%ld\n", array_of_programs[i].hours);
        printf("Minuty:%ld\n", array_of_programs[i].minutes);
        printf("Ilosc:%ld\n", array_of_programs[i].time_to_exec);
        printf("Ilosc snu:%ld\n\n", array_of_programs[i].time_to_sleep_before_exec);
    }
    return 0;
}
