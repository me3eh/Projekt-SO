#include "fun.h"

int main(int argc, char **argv){
    // signal(SIGINT, handler);

    if(amount_of_arguments(argc, argv[0]) > 0)
        return EXIT_FAILURE;

    if(equal_namings(argv[1], argv[0])){
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
            for(int a=0; a<array_of_programs[i].how_many_arguments_in_program[j]; ++a)
                printf("%s\n\n", array_of_programs[i].program[j][a]);
    }
    fclose(file);
    bool first_time =true;
    for(int i = 0; i < length; ++i){
        title_in_file(array_of_programs[i].original_command_from_file, argv[2], first_time);
        pipe_fork_stuff(array_of_programs[i].program, array_of_programs[i].amount_programs, argv[2], array_of_programs[i].state);
        first_time = false;
    }
    
    // for(int i = 0; i < length; ++i){
    //     for(int j=0; j<array_of_programs[i].amount_programs;++j)
    //         free(array_of_programs[i].program[j]);
    //     free(array_of_programs[i].program);
    // }
    // free(array_of_programs);
    // char *array[] ={"ls -l","grep p"};
    // pipe_fork_stuff(array, 2, "polko.txt");
    free_space(array_of_programs);
    return 0;
}
