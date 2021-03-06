#include "fun.h"

#define GOOD_FORMAT "^((2{0,1}[0-3])|([0-1]{0,1}[0-9])):([0-5]?[0-9]):([a-zA-Z0-9\\|:,. -])*:[0-2]$"
#define WRITE_END 1
#define READ_END 0
//wielkosc sciezki dostepowej
#define SIZE_PATH 300
//wielkosc bufora
#define SIZE 200
// bool first_time = true;
volatile bool import_from_file = false;
volatile bool print_to_log = false;
volatile bool is_abort = false;

int lines_in_file = 0;

int amount_of_arguments(int arg, char* word){
    if(arg != 3){
        fprintf(stderr, "Usage: %s <taskfile> <outfile> \n", word);
        return EINVAL;
    }
    return 0;
}

bool equal_namings(char* naming_input, char* naming_output){
    if(strcmp(naming_input, naming_output) == 0){
        fprintf(stderr,"Input and output file cannot have the same name");
        return true;
    }
    return false;
}

FILE* checking_file_valid(char * naming, char*PATH){
    
    if(chdir(PATH) < 0){
        // syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        printf("In function pipe_for_stuff():%s", strerror(errno));
        
        return NULL;
    }

    FILE * file = fopen(naming, "r");
    if(file == NULL){
        syslog(LOG_ERR,"%s:%s", naming, strerror(errno));
    }
    if(chdir("/") < 0){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return NULL;
    }
    return file;
}

int check_format(FILE * file){
    if(file == NULL){
        syslog(LOG_ERR,"In function check_format():%s",strerror(errno));
        return -1;
    }
    char buffer[SIZE];
    int line = 0;
    regex_t regex;

    int to_find = regcomp(&regex, GOOD_FORMAT, REG_EXTENDED|REG_NEWLINE);
    if(to_find != 0){
        syslog(LOG_ERR,"In function check_format():%s",strerror(errno));
        return -1;
    }

    while(fgets(buffer, SIZE, file) != NULL){
    	int found = regexec(&regex, buffer, 0, NULL, 0);
        if(found == 0)
            ++line;
        else if( found == REG_NOMATCH){
            syslog(LOG_ERR,"In function check_format():\nBad format in file - line:%d Usage: <hours>:<minutes>:<code>:<mode>\n", line+1);
            return -1;
        }
        else{
            syslog(LOG_ERR,"In function check_format():%s",strerror(errno));
            return -1;
        }
        if(preventing_pipe_at_end(buffer) == -1)
            return -1;
    }

    regfree(&regex);

    //powrot do poczatku pliku
    rewind(file);
    if(line == 0){
        syslog(LOG_ERR, "In function check_format(): File is empty");
        return -1;
    }
    //przypisanie do globalnej zmiennej
    lines_in_file = line;

    return line;
}

int length_of_file(){
    return lines_in_file;
}

task_temp * get_array_of_tasks(FILE * file){
    if(file == NULL){
        syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
        return NULL;
    }
    int line = 0;
    char buffer[SIZE];
    int length_of_everything = 0;
    char *token, *lil_buffa;
    char pol[200] = "";
    //zmienna pomocnicza do zmiennej buffer
    char *save_buffer = NULL;
    int amount_of_programs = 0;
    int i = 0;
    bool in = false;
    int columns = check_format(file);
    if(columns == -1)
        return NULL;

    task_temp *array_task = (task_temp*)malloc(columns * sizeof(task_temp));

    if(array_task == NULL){
        syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
        return NULL;
    }
    while(fgets(buffer, SIZE, file) != NULL){
        array_task[line].original_command_from_file = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        if(array_task[line].original_command_from_file == NULL){
            syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
            return NULL;
        }
        strcpy(array_task[line].original_command_from_file, buffer);

        length_of_everything = strlen(buffer);
        amount_of_programs = amount_of_pipes(buffer);
        //wczytanie godziny o ktorej uruchomi?? polecenie
        token = strtok_r(buffer, ":", &save_buffer);
        length_of_everything -= (strlen(token) + 1);
        array_task[line].hours = strtol(token, &lil_buffa, 10);
        token = strtok_r(NULL, ":", &save_buffer);

        length_of_everything -= (strlen(token) + 1);
        array_task[line].minutes = strtol(token, &lil_buffa, 10);

        //wczytanie programow oraz alokacja pamieci
        array_task[line].program = (char***)malloc(amount_of_programs * sizeof(char**));
        array_task[line].how_many_arguments_in_program = (int*)malloc(amount_of_programs * sizeof(int));
        
        for(int a =0 ; a< amount_of_programs; ++a)
            array_task[line].how_many_arguments_in_program[a] = 0;
        if(array_task[line].program == NULL){
            syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
            return NULL;
        }
        if(array_task[line].how_many_arguments_in_program == NULL){
            syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
            return NULL;
        }
        array_task[line].no_pipes = amount_of_programs;
        while( i < (amount_of_programs - 1) ){
            token = strtok_r(NULL, "|", &save_buffer);
            strcpy(pol, token);
            in = false;
            while(pol[strlen(pol)-1] == '\\'){
                if(in == false){
                    strcat(pol, "|");
                    in = true;
                }
                else{
                    strcat(pol, token);
                    strcat(pol, "|");
                }
                token = strtok_r(NULL, "|", &save_buffer);
            }
            array_task[line].program[i] = string_to_array(pol, &array_task[line].how_many_arguments_in_program[i]);
            if(array_task[line].program[i] == NULL){
                syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
                return NULL;
            }
            length_of_everything -= (strlen(pol) + 1);
            ++i;
        };
        //usuniecie jednego dwukropka rozdzielajacego polecenia/polecenie od stanu
        length_of_everything -= 1;
        //usuniecie znaku nowej linii, jezeli nie jest to ostatnia linia
        if((lines_in_file - 1) != line )
            length_of_everything -= 1;

        token = strtok_r(NULL, ":", &save_buffer);
        strcpy(pol, token);

        while(length_of_everything <= strlen(pol)){
            strcat(pol, ":");
            token = strtok_r(NULL, ":", &save_buffer);
            strcat(pol, token);
        }
        
        array_task[line].program[i] = string_to_array(pol, &array_task[line].how_many_arguments_in_program[i]);
        if(array_task[line].program[i] == NULL){
            syslog(LOG_ERR,"In function get_array_of_tasks():%s",strerror(errno));
            return NULL;
        }
        token = strtok_r(NULL, ":", &save_buffer);
        
        array_task[line].state = strtol(token, &lil_buffa, 10);
        ++line;
        i = 0;
    }
    return array_task;
}

int amount_of_pipes(char* pol){
    regex_t regex;
    const int n_matches = 20;
    regmatch_t m[n_matches];
    int no_of_pipes = 1;
    char * p = pol;
    int value = regcomp(&regex, "[a-zA-Z.,: -][|]", REG_EXTENDED|REG_NEWLINE);
    if(value != 0){
        syslog(LOG_ERR,"In function amount_of_pipes():%s",strerror(errno));
        return -1;
    }
    while (1) {
        int i = 0;
        int nomatch = regexec (&regex, p, n_matches, m, 0);
        if (nomatch == REG_NOMATCH) {
            break;
        }
        else if(nomatch == 0){
            for (i = 0; i < n_matches; i++) {
                if (m[i].rm_so != -1)
                    ++no_of_pipes;
                else
                    break;
            }
            p += m[0].rm_eo;
        }
        else{
            syslog(LOG_ERR,"In function amount_of_pipes():%s",strerror(errno));
            return -1;
        }
    }
    regfree(&regex);
    return no_of_pipes;
}

// struct tm {
//     int tm_sec;         /* seconds */
//     int tm_min;         /* minutes */
//     int tm_hour;        /* hours */
//     int tm_mday;        /* day of the month */
//     int tm_mon;         /* month */
//     int tm_year;        /* year */
//     int tm_wday;        /* day of the week */
//     int tm_yday;        /* day in the year */
//     int tm_isdst;       /* daylight saving time */
// };


void set_time_to_exec_temp(task_temp * array, int length){

    time_t rawtime;
    time (&rawtime);

    struct tm * timeinfo = localtime(&rawtime);
    
    for (int i =0; i< length; ++i){
        array[i].time_to_exec = 0;
        if( timeinfo->tm_hour == array[i].hours && timeinfo->tm_min == array[i].minutes )
            // array[i].time_to_exec = 0;
            continue;
        else{
            if( timeinfo->tm_hour > array[i].hours || ( timeinfo->tm_hour == array[i].hours && timeinfo->tm_min > array[i].minutes ) )
                array[i].time_to_exec += 24 * 3600;

            array[i].time_to_exec += (array[i].hours * 3600 + array[i].minutes * 60);
            array[i].time_to_exec -= (timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec );
        }
    }
}

void set_time_to_sleep_temp(task_temp * array, int length){
    long temp = 0;
    for(int i = 0; i < length; ++i){
        array[i].time_to_sleep_before_exec = array[i].time_to_exec - temp;
        temp = array[i].time_to_exec;
    }
}

int comparator_temp(const void *p, const void *q)
{
    task_temp *l = (task_temp* )p;
    task_temp *r = (task_temp *)q;
    if( l->time_to_exec > r->time_to_exec )
        return +1;
    else if( l->time_to_exec < r->time_to_exec)
        return -1;
    else
        return 0;
}

void free_space(task_temp * array){
    for(int i = 0; i < lines_in_file; ++i){
        for(int j=0; j<array[i].no_pipes;++j){
            for(int t=0; t<array[i].how_many_arguments_in_program[j]; ++t)
                free(array[i].program[j][t]);
            free(array[i].program[j]);
        }
        free(array[i].how_many_arguments_in_program);
        free(array[i].program);
        free(array[i].original_command_from_file);
    }
    free(array);
}
char ** string_to_array(char * text, int * size){
    char ** array = (char**)malloc(1 * sizeof(char*));
    char * save_text = NULL;
    char * token1 = strtok_r(text, " ", &save_text);
    int i = 0;
    if(( array[i] = (char*)malloc( (strlen(token1)+1) * sizeof(char))) == NULL){
        syslog(LOG_ERR,"In function string_to_array():%s",strerror(errno));
        return NULL;
    }
    strcpy(array[i], token1);
    token1 =strtok_r(NULL, " ", &save_text);
    while(token1 != NULL){
        ++i;
        if((array = (char**)realloc( array, (i + 1) * sizeof(char*))) == NULL){
            syslog(LOG_ERR,"In function string_to_array():%s",strerror(errno));
            return NULL;
        }
        if(( array[i] = (char*)malloc( (strlen(token1)+1) * sizeof(char))) == NULL){
            syslog(LOG_ERR,"In function string_to_array():%s",strerror(errno));
            return NULL;
        }
        strcpy(array[i], token1);
        token1 =strtok_r(NULL, " ", &save_text);
    }
    //zwiekszamy, gdyz zwiekszy sie o NULL
    ++i;
    if((array = (char**)realloc( array, (i + 1) * sizeof(char*))) == NULL){
        syslog(LOG_ERR,"In function string_to_array():%s",strerror(errno));
        return NULL;
    }
    array[i] = NULL;
    // i bylo liczone od 0, dlatego zwracany size + 1
    *size = (i+1);
    return array;
}
int title_in_file(char*original_line_in_file, char*outfile, bool first_time, char * PATH, int * a){
    int file;

    if(chdir(PATH) < 0){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return -1;
    }

    if(first_time){
        for(int s=0; s<3; ++s){
            dup2(a[s], s);
        }
        if((file = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0){
            syslog(LOG_ERR,"In function title_in_file():%s",strerror(errno));
            return -1;
        }
    }
    else{
        if((file = open(outfile, O_WRONLY | O_APPEND, 0666)) < 0){
            syslog(LOG_ERR,"In function title_in_file():%s",strerror(errno));
            return -1;
        }
    }
    if(first_time){
        write(file, original_line_in_file, strlen(original_line_in_file));
        char p [] = "----------------------------\n";
        write(file, p, strlen(p));
    }
    else{
        write(file, "\n\n", 2);
        write(file, original_line_in_file, strlen(original_line_in_file));
        char p [] = "----------------------------\n";
        write(file, p, strlen(p));
    }
    if( close(file) == -1){
        syslog(LOG_ERR,"In function title_in_file():%s",strerror(errno));
        return -1;
    }
    if(chdir("/") < 0){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return -1;
    }
    return 0;
}


int pipe_fork_stuff(char *** array, int length, char * outfile, int state, task_temp*ar, char*original_command_from_file, char*PATH){

    pid_t pid;
    int file, file_null;
    int fd[length][2];
    if(chdir(PATH) < 0){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return -1;
    }
    if((file = open(outfile, O_WRONLY | O_APPEND)) < 0){
        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
        return -1;
    }
    if((file_null = open("/dev/null", O_WRONLY)) < 0){
        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
        return -1;
    }
    if(state >= 1)
        if( dup2(file, STDERR_FILENO) == -1 ){
            syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
            return -1;
        }
    for(int i = 0 ; i < length; ++i)
        if( pipe(fd[i]) != 0){
            syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
            return -1;
        }
    for(int i = 0 ; i < length ; ++i){
        pid = fork();
        if(pid == 0){
            if((i == length - 1) && (i == 0)){
                if(state  == 0){
                    if( dup2(file, STDOUT_FILENO) == -1){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                    if( dup2(file_null, STDERR_FILENO) == -1){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                }
                if(state == 1)
                    if( dup2(file_null, STDOUT_FILENO) == -1){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                if(state == 2)
                    if( dup2(file, STDOUT_FILENO) == -1){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }

                execvp(array[0][0], array[0]);
                fprintf(stderr, "%s: %s", array[0][0],strerror(errno));
                //zwalnianie pamieci wedlug valgrinda nie doprowadza do wyciekow
                free_space(ar);
                exit(errno);
            }
            else if(( i == length - 1 ) && ( i != 0 )){
                // close(fd[i-1][WRITE_END]);
                dup2(fd[i-1][READ_END], STDIN_FILENO);
                
                if(state == 0){
                    dup2(file, STDOUT_FILENO);
                    dup2(file_null, STDERR_FILENO);
                }
                if(state == 1)
                    dup2(file_null, STDOUT_FILENO);
                if(state == 2)
                    dup2(file, STDOUT_FILENO);
                execvp(array[i][0], array[i]);
                fprintf(stderr, "%s: %s", array[i][0],strerror(errno));
                //zwalnianie pamieci wedlug valgrinda nie doprowadza do wyciekow
                free_space(ar);
                exit(errno);
            }
            else{
                if(i != 0){
                    // close(fd[i-1][WRITE_END]);
                    dup2(fd[i-1][READ_END], STDIN_FILENO);
                }

                if( close(fd[i][READ_END]) == -1 ){
                    syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                    return -1;
                }
                
                if( dup2(fd[i][WRITE_END], STDOUT_FILENO) == -1){ 
                    syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                    return -1;
                }
                if(state == 0)
                    close(STDERR_FILENO);

                execvp(array[i][0], array[i]);
                fprintf(stderr, "%s: %s\n", array[i][0],strerror(errno));
                //zwalnianie pamieci wedlug valgrinda nie doprowadza do wyciekow
                free_space(ar);
                exit(errno);
            }
        }
        else if(pid > 0){
            int status;
            int exit_status;
            waitpid(pid, &status, 0);
            if(WIFEXITED(status)){
                if( (exit_status = WEXITSTATUS(status)) != 0){
                    if( close(fd[i][WRITE_END]) == -1 ){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                    if( close(file) == -1 ){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                    if( close(file_null) == -1 ){
                        syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                        return -1;
                    }
                    syslog(LOG_INFO, "Exit status of %s --> %d", original_command_from_file, exit_status);
                    if(chdir("/") < 0){
                        syslog(LOG_ERR, "In function pipe_fork_stuff during changing directory:%s", strerror(errno));
                    }
                    return 0;
                }
            }
            if( close(fd[i][WRITE_END]) == -1){
                syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                return -1;
            }
            if( i != 0)
                if( close(fd[i-1][READ_END]) == -1 ){
                    syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                    return -1;
                }
            if((i == length - 1)){
                if( close(file) == -1 ){
                    syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                    return -1;
                }
                if( close(file_null) == -1 ){
                    syslog(LOG_ERR, "In function pipe_fork_stuff():%s", strerror(errno));
                    return -1;
                }
                syslog(LOG_INFO, "Exit status of %s --> %d", original_command_from_file, exit_status);
            }
        }
    }
    if(chdir("/") < 0){
        syslog(LOG_ERR, "In function pipe_fork_stuff during changing directory:%s", strerror(errno));
    }
    return 0;
}

bool status_if_import(){
    return import_from_file;
}
void change_status_import_from_file(bool t){
    import_from_file = t;
}
bool status_if_print(){
    return print_to_log;
}
bool status_abort(){
    return is_abort;
}
void change_status_print_to_log(bool t){
    print_to_log = t;
}

void handler(int signum){
    if(signum == 2){
        is_abort = true;
    }
    if(signum == 10){
        import_from_file = true;
    }
    if(signum == 12){
        print_to_log = true;
    }
}

void print_to_log_function(task_temp * array, int i, int max_length){
    syslog(LOG_INFO, "\nTasks to complete:");
    syslog(LOG_INFO, "---------------------------------------------");
    while (i != max_length){
        syslog(LOG_INFO, "%s", array[i].original_command_from_file);
        ++i;
    }
    syslog(LOG_INFO, "---------------------------------------------");
}
int preventing_pipe_at_end(char* pol){

    regex_t regex2;
    int to_find = regcomp(&regex2, "[^\\][|][ ]*:[0-2]$", REG_EXTENDED|REG_NEWLINE);
    if(to_find != 0){
        syslog(LOG_ERR,"Inside function check_format() -> In function preventing_pipe_at_end():%s",strerror(errno));
        return -1;
    }
    int found = regexec(&regex2, pol, 0, NULL, 0);
        if(found == 0){
            syslog(LOG_ERR, "Inside function check_format() -> In function preventing_pipe_at_end(): character of pipe at the end of line");
            regfree(&regex2);
            return -1;
        }
        else if( found == REG_NOMATCH){
            regfree(&regex2);
            return 0;
        }
        else{
            syslog(LOG_ERR,"Inside function check_format() -> In function preventing_pipe_at_end():%s",strerror(errno));
            return -1;
        }
    return -1;
}

int checking_file_access(char * naming, char*PATH){
    if(chdir(PATH) < 0){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return -1;
    }
    int return_value;
    if( ( return_value = access(naming, R_OK) ) != 0 ){
        fprintf(stderr, "File do not exist or do not have a permission to read.\n");
    }
    if( chdir("/") < 0 ){
        syslog(LOG_ERR, "In function pipe_for_stuff():%s", strerror(errno));
        return -1;
    }
    return return_value;
}