#include "fun.h"

int main(int argc, char **argv){
    
    if(amount_of_arguments(argc, argv[0]) > 0)
        return EXIT_FAILURE;

    if(equal_namings(argv[1], argv[0])){
        fprintf(stderr,"Input and output file cannot have the same namings");
        return EINVAL;
    }

    FILE * file;

    if ((file = checking_file_valid(argv[1])) == NULL)
        return EINVAL;
    
    task_temp * array_of_programs;

    if (( array_of_programs = get_array_of_tasks(file) )== NULL){
        return EINVAL;
    }
    int length = length_of_file();
    
    set_time_to_exec_temp(array_of_programs, length);
    qsort(array_of_programs, length, sizeof(*array_of_programs), comparator_temp);
    set_time_to_sleep_temp(array_of_programs, length);

    for(int i=0; i< length; ++i){    
        printf("Godz:%ld\n", array_of_programs[i].hours);
        printf("Minuty:%ld\n", array_of_programs[i].minutes);
        printf("Ilosc:%ld\n", array_of_programs[i].time_to_exec);
        printf("Ilosc snu:%ld\n", array_of_programs[i].time_to_sleep_before_exec);
        for(int j=0; j<array_of_programs[i].amount_programs; ++j)
            printf("Pupa kupa%s\n\n", array_of_programs[i].program[j]);
    }
    for(int i = 0; i < length; ++i){
        for(int j=0; j<array_of_programs[i].amount_programs;++j)
            free(array_of_programs[i].program[j]);
        free(array_of_programs[i].program);
    }
    free(array_of_programs);
    fclose(file);
    return 0;
}
