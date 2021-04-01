#include "fun.h"

#define GOOD_FORMAT "^(2[0-3]|[0-1]?[0-9]):([0-5]?[0-9]):[a-zA-Z|: -]*:[0-2]$"
int amount;

int amount_of_arguments(int arg, char* word){
    if(arg != 3){
        fprintf(stderr, "Usage: %s <taskfile> <outfile> \n", word);
        return EINVAL;
    }
    return 0;
}

bool equal_namings(char* naming_input, char* naming_output){
    return (naming_input == naming_output);
}

FILE* checking_file_valid(char * naming, bool for_writing){
    FILE * file = for_writing ? fopen(naming, "w") : fopen(naming, "r");
    if(file == NULL)
        perror("File error");
    return file;
}

int colons_in_file(FILE * file){
    int size = 200; 
    char pol [size];
    int line = 0;
    char * token;
    int counter = 0;
    regex_t regex;
    int value = regcomp(&regex, GOOD_FORMAT, REG_EXTENDED|REG_NEWLINE);
    while(fgets(pol, size, file) != NULL){
       
    	int lk = regexec(&regex, pol, 0, NULL, 0);
        if(lk == 0)
            ++line;
        else if( lk == REG_NOMATCH){
            fprintf(stderr, "Bad format in file - line:%d\n Usage: <hours>:<minutes>:<code>:<mode>", line);
            return -1;
        }
        else{
            fprintf(stderr, "An error occured");
            return -1;
        }
    }

    regfree(&regex);
    rewind(file);
    amount = line;
    return line;
}

int length_of_file(){
    return amount;
}

task*  file_in_good_format(FILE * file){
    
    int line = 0;
    int size = 200;
    int counter = 0;
    char pol [size]; 
    char * token, *cp;
    int columns = colons_in_file(file);
    
    if(columns == -1)
        return false;
    
    task * array_of_programs = (task*)malloc(columns * sizeof(task));
    
    if(array_of_programs == NULL){
        perror("Allocation memory:");
        return NULL;
    }
    
    while(fgets(pol, size, file) != NULL){ 
        token = strtok(pol, ":"); 
        do{
            switch(counter){
                case 0:
                    array_of_programs[line].hours = strtol(token, &cp, 10);
                break;
                case 1:
                    array_of_programs[line].minutes = strtol(token, &cp, 10);
                break;
                case 2:
                    strcpy(array_of_programs[line].program, token);
                break;
                case 3:
                    array_of_programs[line].state = strtol(token, &cp, 10);
                break;
                default:
                    fprintf(stderr, "Incorrect format in file - line %d\nUsage: <hours>:<minutes>:<command>:<mode>\n", line + 1);
                    free(array_of_programs);
                    return NULL;
                break;
            }
            token = strtok(NULL, ":");
            ++counter;
        }while( token != NULL ); 
        
        ++line;
        counter = 0;
    }
    return array_of_programs;
}

task_temp * file_in_good_format_temp(FILE * file){
    int line = 0;
    int size = 200;
    char pol [size]; 
    char *token, *cp;
    int columns = colons_in_file(file);
    
    if(columns == -1)
        return false;
    task_temp * array_of_programs = (task_temp*)malloc(columns * sizeof(task_temp));
    
    if(array_of_programs == NULL){
        perror("Allocation memory:");
        return NULL;
    }
    int amount_of_programs = 0;
    int i = 0;
    while(fgets(pol, size, file) != NULL){ 
        
        amount_of_programs = amount_of_pipes(pol); 
        token = strtok(pol, ":"); 
        if(token == NULL)
            return NULL;
        array_of_programs[line].hours = strtol(token, &cp, 10);

        token = strtok(NULL, ":");
        if(token == NULL)
            return NULL;
        array_of_programs[line].minutes = strtol(token, &cp, 10);
        char temp[100];
        printf("\n-=-=%d: %d\n",line,amount_of_programs);
        array_of_programs[line].program = (char**)malloc(amount_of_programs * sizeof(char*));

        array_of_programs[line].am_of_programs = amount_of_programs;

        while( i < (amount_of_programs-1)){
            token = strtok(NULL, "|");
            if(token == NULL)
                return NULL;
            array_of_programs[line].program[i] = (char*)malloc((strlen(token)+1) * sizeof(char));
            strcpy(array_of_programs[line].program[i], (char*)token);
            // array_of_programs[line].program[i] = (char*)token;
            ++i;
        };
        
        token = strtok(NULL, ":");
        array_of_programs[line].program[i] = (char*)malloc((strlen(token)+1) * sizeof(char));
        strcpy(array_of_programs[line].program[i], token);
        // array_of_programs[line].program[i] = (char*)token;
        token = strtok(NULL, ":");
        array_of_programs[line].state = strtol(token, &cp, 10);
        ++line;
        i = 0;
    }
    return array_of_programs;
}

int amount_of_pipes(char* pol){
    regex_t regex;
    const int n_matches = 20;
    regmatch_t m[n_matches];
    int no_of_pipes = 1;
    char * p = pol;
    int value = regcomp(&regex, "[|]", REG_EXTENDED|REG_NEWLINE);
    if(value != 0){
        fprintf(stderr, "Error with regex");
        return -1;
    }
    
        int nomatch = regexec (&regex, p, n_matches, m, 0);
        if (nomatch == 0)
            for(int i = 0; i < n_matches; ++i){
                if(m[i].rm_so == -1)
                    break;
                else
                    ++no_of_pipes;
            }
        else if(nomatch == REG_NOMATCH)
            return 1;
        else{
            fprintf(stderr, "Something with regex goes wrong");
            return -1;
        }
    regfree(&regex);
    return no_of_pipes;
}
//typy do korzystania z tm

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
void set_time_to_exec(task * array, int length){

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

void set_time_to_sleep(task * array, int length){
    long temp = 0;
    for(int i = 0; i < length; ++i){
        array[i].time_to_sleep_before_exec = array[i].time_to_exec - temp;
        temp = array[i].time_to_exec;
    }
} 

int comparator(const void *p, const void *q) 
{
    task *l = (task* )p;
    task *r = (task *)q;
    if( l->time_to_exec > r->time_to_exec)
        return +1;
    else if( l->time_to_exec < r->time_to_exec)
        return -1;
    else
        return 0;
}
