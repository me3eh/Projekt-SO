#include "fun.h"

#define GOOD_FORMAT "^(2[0-3]|[0-1]?[0-9]):([0-5]?[0-9]):[a-zA-Z\\|: -]*:[0-2]$"
#define WRITE_END 1
#define READ_END 0
bool first_time = true;
int lines_in_file = 0;

int amount_of_arguments(int arg, char* word){
    if(arg != 3){
        fprintf(stderr, "In function amount_of_arguments():\nUsage: %s <taskfile> <outfile> \n", word);
        return EINVAL;
    }
    return 0;
}

bool equal_namings(char* naming_input, char* naming_output){
    fprintf(stderr,"Input and output file cannot have the same namings");
    return (strcmp(naming_input, naming_output) == 0);
}

FILE* checking_file_valid(char * naming){
    FILE * file = fopen(naming, "r");
    if(file == NULL)
        perror("In function checking_file_valid()\n:File error");
    return file;
}

int check_format(FILE * file){
    if(file == NULL){
        perror("In function check_format: File is not found");
        return -1;
    }
    int size_buffer = 200; 
    char buffer[size_buffer];
    int line = 0;
    char * token;
    regex_t regex;
    
    int to_find = regcomp(&regex, GOOD_FORMAT, REG_EXTENDED|REG_NEWLINE);
    if(to_find != 0){
        perror("In function check_format():\nRegex error:");
        return -1;
    }

    while(fgets(buffer, size_buffer, file) != NULL){
    	int found = regexec(&regex, buffer, 0, NULL, 0);
        if(found == 0)
            ++line;
        else if( found == REG_NOMATCH){
            fprintf(stderr, "In function check_format():\nBad format in file - line:%d Usage: <hours>:<minutes>:<code>:<mode>\n", line);
            return -1;
        }
        else{
            fprintf(stderr, "In function check_format():\nAn error occured with regex occured:%s\n", strerror(errno));
            return -1;
        }
    }

    regfree(&regex);

    //powrot do poczatku pliku
    rewind(file);
    if(line == 0){
        fprintf(stderr,"In function check_format(): File is empty");
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
        perror("In function get_array_of_tasks: File is not found:");
        return NULL;
    }
    int line = 0;
    int size_buffer = 200;
    char buffer[size_buffer]; 
    int length_of_everything = 0;
    char *token, *lil_buffa;
    char pol[200] = "";
    //zmienna pomocnicza do zmiennej buffer
    char *save_buffer = NULL;
    int amount_of_programs = 0;
    int i = 0;
    int j = 0;
    bool in = false;
    int columns = check_format(file);
    if(columns == -1)
        return NULL;
    
    task_temp * array_task = (task_temp*)malloc(columns * sizeof(task_temp));
    
    if(array_task == NULL){
        perror("In function get_array_of_tasks():\nAllocation memory:");
        return NULL;
    }

    while(fgets(buffer, size_buffer, file) != NULL){ 
        
        length_of_everything = strlen(buffer);
        printf("\n***** ***->%d\n", length_of_everything);
        amount_of_programs = amount_of_pipes(buffer); 
        //wczytanie godziny o ktorej uruchomić polecenie
        token = strtok_r(buffer, ":", &save_buffer); 
        if(token == NULL){
            perror("Sprawdzenie");
            return NULL;
        }
        length_of_everything -= (strlen(token) + 1);
        array_task[line].hours = strtol(token, &lil_buffa, 10);
        token = strtok_r(NULL, ":", &save_buffer);
        if(token == NULL){
            perror("Sprawdzenie");
            return NULL;
        }
        length_of_everything -= (strlen(token) + 1);
        array_task[line].minutes = strtol(token, &lil_buffa, 10);
        
        //wczytanie programow oraz alokacja pamieci
        array_task[line].program = (char***)malloc(amount_of_programs * sizeof(char**));
        array_task[line].how_many_arguments_in_program = (int*)malloc(amount_of_programs * sizeof(int));
        if(array_task[line].program == NULL){
            perror("In function get_array_of_tasks():\nAllocation error:");
            return NULL;
        }
        if(array_task[line].how_many_arguments_in_program == NULL){
            perror("In function get_array_of_tasks():\nAllocation error:");
            return NULL;
        }
        array_task[line].amount_programs = amount_of_programs;

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
            if(token == NULL){
                fprintf(stderr, "In function get_array_of_tasks():\nSomething went wrong with function strtok. Line:%d", line);
                return NULL;
            }

            array_task[line].program[i] = string_to_array(pol, &array_task[line].how_many_arguments_in_program[i]);
            if(array_task[line].program[i] == NULL){
                perror("In function get_array_of_tasks():\nAllocation error:");
                return NULL;
            }
            length_of_everything -= (strlen(pol) + 1);
            ++i;
        };
        length_of_everything -= 2;
        token = strtok_r(NULL, ":", &save_buffer);
        if(token == NULL){
            perror("Something goes wrong");
            return NULL;
        }

        array_task[line].program[i]= string_to_array(token,&array_task[line].how_many_arguments_in_program[i]);
        if(array_task[line].program[i] == NULL){
            perror("In function get_array_of_tasks():\n");
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
    int value = regcomp(&regex, "[a-zA-Z ][|]", REG_EXTENDED|REG_NEWLINE);
    if(value != 0){
        fprintf(stderr, "In function amount_of_pipes():\n");
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
            fprintf(stderr, "In function amount_of_pipes():\n");
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

        if(timeinfo->tm_hour > array[i].hours || (timeinfo->tm_hour == array[i].hours && timeinfo->tm_min > array[i].minutes))
            array[i].time_to_exec += 24*60;

        array[i].time_to_exec += (array[i].hours * 60 + array[i].minutes);
        array[i].time_to_exec -= (timeinfo->tm_hour * 60 + timeinfo->tm_min);
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
    if( l->time_to_exec > r->time_to_exec)
        return +1;
    else if( l->time_to_exec < r->time_to_exec)
        return -1;
    else
        return 0;
}

void free_space(task_temp * array){
    for(int i = 0; i < lines_in_file; ++i){
        for(int j=0; j<array[i].amount_programs;++j){
            for(int t=0; t<array[i].how_many_arguments_in_program[j]; ++t)
                free(array[i].program[j][t]);
            free(array[i].program[j]);
        }
        free(array[i].how_many_arguments_in_program);
        free(array[i].program);
    }
    free(array);
}
char ** string_to_array(char * text, int * size){
    char ** array = (char**)malloc(1 * sizeof(char*));
    char * save_text = NULL;
    char * token1 = strtok_r(text, " ", &save_text);
    int i = 0;
    if(( array[i] = (char*)malloc( (strlen(token1) + 1) * sizeof(char))) == NULL){
        fprintf(stderr, "In function string_to_array: %s", strerror(errno));
        return NULL;
    }
    strcpy(array[i], token1);
    token1 =strtok_r(NULL, " ", &save_text);
    while(token1 != NULL){
        ++i;
        if((array = (char**)realloc( array, (i + 1) * sizeof(char*))) == NULL){
            fprintf(stderr, "In function string_to_array: %s", strerror(errno));
            return NULL;
        }
        if(( array[i] = (char*)malloc( (strlen(token1) + 1) * sizeof(char))) == NULL){
            fprintf(stderr, "In function string_to_array: %s", strerror(errno));
            return NULL;
        }
        strcpy(array[i], token1);
        token1 =strtok_r(NULL, " ", &save_text);
    }
    *size = (i+1);
    return array;
}

int pipe_fork_stuff(char *** array, int length, char * outfile, int state){
    pid_t pid;
    int file;
    int fd[length-1][2];
    for(int i = 0 ; i < length-1 ; ++i)
        pipe(fd[i]);
    for(int i = 0 ; i < length ; ++i){
        pid = fork();
        if(pid == 0){
            if((i == length - 1) && (i == 0)){
                //first_time zmienna globalna
                if(first_time){
                    first_time = false;
                    if((file = open("polko.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0){
                        perror("Error");
                        return 55;
                    }
                }
                else
                    if((file = open("polko.txt", O_WRONLY | O_APPEND, 0777)) < 0){
                        perror("Error");
                        return 55;
                    }
                dup2(file, STDOUT_FILENO);
                execvp(array[0][0], array[0]);
                close(file);
            }
            else if(( i == length - 1 ) && ( i != 0 )){
                dup2(fd[i-1][READ_END], STDIN_FILENO);
                if(first_time){
                    first_time = false;
                    if(file = open("polko.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777) < 0){
                        perror("Error");
                        return 55;
                    }
                }
                dup2(file, STDOUT_FILENO);
                execvp(array[i][0], array[i]);
            }
            else{
                if(i != 0)
                    dup2(fd[i-1][READ_END], STDIN_FILENO);

                close(fd[i][READ_END]);
                dup2(fd[i][WRITE_END], STDOUT_FILENO);
                execvp(array[i][0], array[i]);
                return -1;
            }
        }
        else if(pid > 0){
            int status;
            waitpid(pid, &status, 0);
            if( i != (length-1))
                close(fd[i][WRITE_END]);
            if((i == length - 1)){
                close(file);
            }
        }
    }
}