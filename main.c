#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#define M 15

typedef struct _flights {
    char aofd[1000];
    float distance;
    float duration;
    char type[1000];
    char aofa[1000];
    struct _flights *next;
}Flights;

typedef struct _airports {
    char* City;
    char* Country;
    char* Code;
    Flights *flights;
    struct _airports *next;
}Airports;

int hash_func(const char* x) {
   // 0 -- M  [0, M[
   int tot = 0, len = strlen(x);
   for (int i = 0; i < len; i++) {
       tot += x[i];
   }
   return tot % M;
}

Flights * insert_flights_(Flights* lst, char aofd[], float distance, float duration, char type[], char aofa[]) {
    Flights *rec = malloc(sizeof(Flights));
    strcpy(rec->aofd, aofd);
    strcpy(rec->aofa, aofa);
    strcpy(rec->type, type);
    rec->distance = distance;
    rec->duration = duration;
    rec->next = lst;
    return rec;
}

void listar_flights(Flights* lst)
{
    for(;lst;lst = lst->next)
    {
        printf("%s | %lf | %lf | %s | %s\n",lst->aofd, lst->distance, lst-> duration, lst->type,lst->aofa);
    }
}

void set_Flight(Airports **hash, const char city[], const char country[],const char code[]) {
    int h = hash_func(code);
    Airports *ptr = hash[h];
    while (ptr && strcmp(ptr->Code,code) != 0)  ptr = ptr->next;
    if (ptr) strcpy(ptr->Country,country);
    else { 
        // Este ID é novo (não aparece como partida de nenhuma relação)
        Airports *p = malloc(sizeof(Airports));
        p->Country = strdup(country);
        p->City = strdup(city);
        p->Code = strdup(code);
        p->flights = NULL;
        p->next = hash[h];  // insercao à cabeça 
        hash[h] = p;    // atualizar o hash
    }
}

Airports * insert_Aiport(Airports *lst, char code[],char aofd[], float distance, float duration, char type[], char aofa[]) {
    if (lst == NULL || (strcmp(lst->Code,code) == 0) ) {
        // Insert Product?
        if (!lst) {
            lst = malloc(sizeof(Airports));
            lst->Country = NULL;
            lst->City = NULL;
            lst->Code = code;
            lst->flights = NULL;
        }
        // Insert Suggestion
        lst->flights = insert_flights_(lst->flights, aofd, distance, duration, type, aofa);
    }
    else {
        lst->next = insert_Aiport(lst->next, code, aofd, distance, duration, type, aofa);
    }
    return lst;
}

void hash_insert(Airports **hash, char code[],char aofd[], float distance, float duration, char type[], char aofa[]) {
    int h = hash_func(code);
    hash[h] = insert_Aiport(hash[h], code, aofd, distance, duration, type, aofa);
}

Airports *search_airpots(Airports **hash, const char code[]) {
    //printf("Estou aqui");
    int h = hash_func(code);
    Airports *ptr = hash[h];
    while (ptr && (strcmp(ptr->Code,code)!=0)) ptr = ptr->next;
    return ptr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void * Read_flights_PT(Airports **hash)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/flights-PT.tsv","rt");
    while (!feof(file))
    {
        char string[1000];
        char aofd[1000], type[1000], aofa[1000], distance[1000], duration[1000];
        float distance_,duration_;
       
        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&aofd, &distance, &duration, &type, &aofa);
            strtok(aofa,"\n");
            distance_ = atof(distance);
            duration_ = atof(duration);
            hash_insert(hash, aofd , aofd, distance_, duration_, type, aofa);
        }
        i++;
    }
    fclose(file);

}

void * Read_airports_PT(Airports **hash)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/airports-PT.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char city[1000], country[1000], code[1000];

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t",&city, &country, &code);
            strtok(code,"\n");
            printf("%s",string);
            set_Flight(hash,city,country,code);
            //printf("Eu sou lindo");
        }
        i++;
    }
    fclose(file);

}

void * Read_airports()
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/airport-codes.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char city[1000], Country[1000], code[1000];

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t",&city, &Country, &code);
            strtok(code,"\n");
            printf("%s",string);
        }
        i++;
    }
    fclose(file);
}

Flights * Read_flights(Flights *lista)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/unique_fligts.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char aofd[1000], distance[1000], duration[1000], type[1000], aofa[1000];
        float distance_,duration_;

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",&aofd, &distance, &duration, &type, &aofa);
            strtok(aofa,"\n");
            distance_ = atof(distance);
            duration_ = atof(duration);
            lista = insert_flights_(lista, aofd, distance_, duration_, type, aofa);
        }
        i++;
    }
    fclose(file);
    return lista;
}

int main() 
{
    Airports **hash;
    hash = calloc(M, sizeof(Airports*));
    Flights *lista_flights_pt;
    //lista_flights_pt = Read_flights_PT(lista_flights_pt);
    //listar_flights(lista_flights_pt);

    //Flights *lista_flights;
    //lista_flights = Read_flights(lista_flights);
    //listar_flights(lista_flights);

    Read_flights_PT(hash);
    Read_airports_PT(hash);

    Airports *ports = search_airpots(hash, "OPO"); 
    Flights *fly = ports->flights;

    while(fly)
    {
        Airports *recfly = search_airpots(hash,recfly->Code);
        printf("%s | %s | %s\n",recfly->City,recfly->Country,recfly->Code);
    }   
    //Read_airports();
  
    return 0;
}