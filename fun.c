#include "fun.h"

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
    return line;
}
task*  file_in_good_format(FILE * file){
    int line = 0;
    int size = 200;
    int counter = 0;
    char pol [size]; 
    char * token, *cp;
    // int columns = colons_in_file(file);
    int columns = 2;
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
    // for(int i=0; i< 1; ++i)
            // printf("%ld", array_of_programs[0].minutes);    
    return array_of_programs;
}

int partition(task*array, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
    int x = array[p].hours*60+array[p].minutes; // obieramy x
    long i = p, j = r;
    task w; // i, j - indeksy w tabeli
    while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
    {
        while (array[j].hours*60+array[j].minutes > x) // dopoki elementy sa wieksze od x
            j--;
        while (array[i].hours*60+array[i].minutes < x) // dopoki elementy sa mniejsze od x
            i++;
        if (i < j) /* zamieniamy miejscami gdy i < j*/{
            w = array[i];
            array[i] = array[j];
            array[j] = w;
            i++;
            j--;
        }
        else{ // gdy i >= j zwracamy j jako punkt podzialu tablicy
            // free(w);
            return  j;
        }
    }
}
 
void quicksort(task * array, int p, int r) // sortowanie szybkie
{
    int q;
    if (p < r)
    {  
        q = partition(array,p,r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
        quicksort(array, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
        quicksort(array, q+1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
    }
}
