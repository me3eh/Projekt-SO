#include "fun.h"
int main(int argc, char **argv){
    // signal(SIGINT, handler);
    signal(SIGUSR1, handler);
    signal(SIGINT, handler);
    signal(SIGUSR2, handler);
    FILE * file;
    char PATH[200];
    getcwd(PATH, sizeof(PATH));
    task_temp * array_of_programs;
    pid_t pid, sid;

    if(amount_of_arguments(argc, argv[0]) > 0)
        exit(EXIT_FAILURE);

    if(equal_namings(argv[1], argv[0]))
        exit(EXIT_FAILURE);
    if ((file = checking_file_valid(argv[1])) == NULL){
        return EINVAL;
    }
    pid = fork();
    if(pid < 0){
        exit(EXIT_FAILURE);
    }
    if(pid > 0){
        exit(EXIT_SUCCESS);
    }
    umask(0);
    openlog("PROJEKT", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Welcome to our lil project");
    sid = setsid();
    if(sid < 0){
        syslog(LOG_ERR, "During initialization session id:%s", strerror(errno));
        perror("HIHIHI");
        exit(EXIT_FAILURE);
    }
    if((chdir("/")) < 0){
        syslog(LOG_ERR, "During changing working directory:%s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    RESTART:

    rewind(file);
    if (( array_of_programs = get_array_of_tasks(file) )== NULL)
        return EINVAL;
    int length = length_of_file();
    set_time_to_exec_temp(array_of_programs, length);
    qsort(array_of_programs, length, sizeof(*array_of_programs), comparator_temp);
    set_time_to_sleep_temp(array_of_programs, length);
    bool first_time =true;
    for(int i = 0; i<length ; ++i){
        // for(int j=0; j<array_of_programs[i].time_to_sleep_before_exec; ++j){
            // for(int k=0 ; k < 60 ; ++k){
            for(int k=0 ; k < 5 ; ++k){

                if(status_if_print() == true){
                    print_to_log_function(array_of_programs, i, length);
                    change_status_print_to_log(false);
                }
                if(status_if_import() == true){
                    change_status_import_from_file(false);
                    free_space(array_of_programs);
                    goto RESTART;
                }
                if(status_abort() == true){
                    syslog(LOG_INFO,"Daemon exited with SIGINT");
                    closelog();
                    free_space(array_of_programs);
                    exit(EXIT_SUCCESS);
                }
                sleep(1);
            }
        // }
        if((title_in_file(array_of_programs[i].original_command_from_file, argv[2], first_time, PATH)) == -1){
            exit(EXIT_FAILURE);
        }
        pipe_fork_stuff(array_of_programs[i].program, array_of_programs[i].no_pipes, argv[2], array_of_programs[i].state, array_of_programs, array_of_programs[i].original_command_from_file, PATH);
        first_time = false;
    }
    free_space(array_of_programs);
    closelog();
    exit(EXIT_SUCCESS);
}
