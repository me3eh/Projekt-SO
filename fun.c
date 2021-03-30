#include "fun.h"
int ilosc;
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
    // const int n_matches = 1;
    // regmatch_t m[n_matches];
    int value = regcomp(&regex, "^([0-2]?[0-9]):([0-5]?[0-9]):[a-zA-Z|: -]*:[0-2]$", REG_EXTENDED|REG_NEWLINE);
    while(fgets(pol, size, file) != NULL){
       
    	int lk = regexec(&regex, pol, 0, NULL, 0);
        if(lk == 0)
            ++line;
        else if( lk == REG_NOMATCH){
            fprintf(stderr, "Bad format in file\n Usage: <hours>:<minutes>:<code>:<mode>");
            return -1;
        }
        else{
            fprintf(stderr, "An error occured");
            return -1;
        }
    }
    regfree(&regex);
    rewind(file);
    printf("%d", line);
    ilosc = line;
    return line;
}

int daj_ilosc(){
    return ilosc;
}
task*  file_in_good_format(FILE * file){
    int line = 0;
    int size = 200;
    int counter = 0;
    char pol [size]; 
    char * token, *cp;
    int columns = colons_in_file(file);
    // int columns = 2;
    if(columns == -1)
        return false;
    task * array_of_programs = (task*)malloc(columns * sizeof(task));
    if(array_of_programs == NULL){
        perror("Allocation memory:");
        return NULL;
    }
    // if (file == NULL)
        // return false;
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
