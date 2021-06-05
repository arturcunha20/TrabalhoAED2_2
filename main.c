#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#define M 5000

typedef struct _flights {
    char* aofd;
    float distance;
    float duration;
    char* type;
    char* aofa;
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
   int tot = 0, len = strlen(x);
   for (int i = 0; i < len; i++) {
       tot += x[i];
   }
   return tot % M;
}

Flights * insert_flights_(Flights* lst, const char *aofd, float distance, float duration,const char *type, const char *aofa) {
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

void set_Flight(Airports **hash, const char *city, const char *country,const char *code) {
    int h = hash_func(code);
    Airports *ptr = hash[h];
    while (ptr && strcmp(ptr->Code,code) != 0)  ptr = ptr->next;
    if (ptr) 
    {
        ptr->Country = strdup(country);
        ptr->City = strdup(city);
    }
    else 
    { 
        Airports *p = (Airports*) malloc(sizeof(Airports));
        p->Country = strdup(country);
        p->Code = strdup(code);
        p->City = strdup(city);
        p->flights = NULL;
        p->next = hash[h];  
        hash[h] = p;   
    }
}

Airports * insert_Aiport(Airports *lst,const char *aofd, float distance, float duration,const char *type, const char *aofa) {
    Airports *ptr = lst;

    while (ptr && strcmp(ptr->Code,aofd) != 0) ptr = ptr->next;

    if(ptr == NULL)
    {
        ptr = (Airports*) malloc(sizeof(Airports));
        ptr->Code = strdup(aofd);
        ptr->City = NULL;
        ptr->Country = NULL;
        ptr->flights = NULL;
        ptr->next = lst;
        lst = ptr;
    }
    Flights *cel = (Flights*) malloc(sizeof(Flights));

    cel->aofa = strdup(aofa);
    cel->aofd = strdup(aofd);
    cel->type = strdup(type); 
    cel->distance = distance;
    cel->duration = duration;
    cel->next = ptr->flights;
    ptr->flights = cel;

    return lst;
}

void hash_insert(Airports **hash, const char *aofd, float distance, float duration,const char *type, const char *aofa) {
    int h = hash_func(aofd);
    hash[h] = insert_Aiport(hash[h], aofd, distance, duration, type, aofa);
}

Airports *search_airpots(Airports **hash, const char *code) {
    int h = hash_func(code);
    Airports *ptr = hash[h];
    while (ptr && (strcmp(ptr->Code,code)!=0)) ptr = ptr->next;
    return ptr;
}

Airports *search_airpots_Country(Airports **hash, const char *country) {
    Airports *a = NULL;
    bool HEHE = false;
    for(int i = 0;i <= M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            if(strcmp(ptr->Country,country) == 0)
            {
                printf("ENCONTREI CRLH");
                a = ptr;
                HEHE = true;
                break;
            }
            ptr = ptr->next;
        }
        if(HEHE ==  true)
        {
            break;
        }
    }

    if(HEHE ==  true)
    {
        
    }

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
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",aofd, distance, duration, type, aofa);
            strtok(aofa,"\n");
            distance_ = atof(distance);
            duration_ = atof(duration);
            //printf("--> %s | %d\n",string,hash_func(aofd));
            hash_insert(hash, aofd, distance_, duration_, type, aofa);

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
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t",city, country, code);
            strtok(code,"\n");
            //printf("%s",string);
            set_Flight(hash,city,country,code);
        }
        i++;
    }
    fclose(file);
}

void * Read_airports(Airports **hash)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/airport-codes.tsv","r");
    while (!feof(file))
    {
        char string[1000];
        char city[1000], country[1000], code[1000];

        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t",city, country, code);
            strtok(code,"\n");
            //printf("%s",string);
            set_Flight(hash,city,country,code);
        }
        i++;
    }
    fclose(file);
}

void * Read_flights(Airports **hash)
{
    FILE *file;
    int i=0;
    file = fopen("Ficheiros/unique_fligts.tsv","rt");
    while (!feof(file))
    {
        char string[1000];
        char aofd[1000], type[1000], aofa[1000], distance[1000], duration[1000];
        float distance_,duration_;
       
        fgets(string,1000,file);
        if(i > 0)
        {
            sscanf(string,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t",aofd, distance, duration, type, aofa);
            strtok(aofa,"\n");
            distance_ = atof(distance);
            duration_ = atof(duration);
            //printf("--> %s | %d\n",string,hash_func(aofd));
            hash_insert(hash, aofd, distance_, duration_, type, aofa);
        }
        i++;
    }
    fclose(file);
}

void listar_voos(Airports **hash)
{
    for(int i = 0;i <= M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            printf("%d -> %s \n",i,ptr->Code);
            ptr = ptr->next;
        }
    }
}

int main() 
{
    Airports **hash;
    hash = (Airports**) calloc(M, sizeof(Airports*));
    Flights *lista_flights_pt;
    //lista_flights_pt = Read_flights_PT(lista_flights_pt);
    //listar_flights(lista_flights_pt);

    //Flights *lista_flights;
    //lista_flights = Read_flights(lista_flights);
    //listar_flights(lista_flights);

    Read_flights(hash);
    Read_airports(hash);

    //listar_voos(hash);

    Airports *ports = search_airpots(hash, "OPO"); 
    Flights *fly = ports->flights;
    while(fly)
    {
        //Airports *recfly = search_airpots(hash,recfly->Code);
        printf("%s | %f | %s\n",fly->aofd,fly->distance,fly->aofa);
        fly = fly->next;
    }   
    //Read_airports();
    
    printf("EU SOU FODA");
    return 0;
}