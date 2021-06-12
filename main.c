#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#define M 5000

typedef struct _flights {
    char *aofd;
    float distance;
    float duration;
    char *type;
    char *aofa;
    struct _flights *next;
}Flights;

typedef struct _airports {
    char *City;
    char *Country;
    char *Code;
    Flights * flights;
    struct _airports *next;
}Airports;

typedef struct _aux
{
    char * airporto;
    int cont;
}Aux;

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

void listar_voos__(Airports **hash)
{
    Flights *fly = NULL;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {        
            fly = ptr->flights;
            listar_flights(fly);
            ptr = ptr->next;
        }
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
    for(int i = 0;i < M;i++)
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

void listar_voos(Airports **hash)
{
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            printf("%d -> %s \n",i,ptr->Code);
            ptr = ptr->next;
        }
    }
}

void search_airports_cidade(Airports **hash)
{ 
    char* cidade;
    char* cidade123;
    int cont = 0,max = 0;
    int array[M];
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            cont++;
            cidade123 = strdup(ptr->City);
            ptr = ptr->next;
        }

        if(cont > max)
        {
            max = cont;
            cidade = strdup(cidade123);
        }
        cont=0;
    }

    printf("A cidade %s tem mais voos",cidade);
}

bool exists_in_list(Airports *lst, const char* code) {
    bool found = false;
    for ( ; lst && !found ; lst = lst->next) {
        if (strcmp(code,lst->Code) == 0) found = true;
    }
    return found;
}

bool exists_in_hash(Airports **hash, char* code) {
    int h = hash_func(code);
    return exists_in_list(*(hash+h), code);
}

char* busca_code(Airports **hash,const char* city)
{
    char *code = NULL;
    for(int j = 0;j < M;j++)
    {
        Airports *ptr1 = hash[j];
        while (ptr1)
        {
            if(strcmp(ptr1->City,city) == 0)
            {
                code = strdup(ptr1->Code);
                break;
            }
            ptr1 = ptr1->next;
        }
    }
    return code;
}

char * custo_viagem(Airports **hash,const char* inicio,const char* fim,float *custo)
{
    *custo = 0;
    float custo_min;
    float custohehe;
    char *nome;
    int h = hash_func(inicio);
    Airports *ptr = hash[h];
    Flights * fly = ptr->flights;
    //printf("%d %s",h,fim);
    while (fly)
    {
        if(strcmp(fly->aofa,fim) == 0)
        {
            if(fly->type = "normal")
            {
                custo_min = (0.5*fly->duration) + (0.45 * fly->distance) + 0.05 * 1;
                nome = strdup(ptr->Code);
            } 
            else
            {
                if(fly->type = "lowcost")
                {
                    custo_min = (0.5*fly->duration) + (0.45 * fly->distance) + (0.05 * 0);
                    nome = strdup(ptr->Code);
                }   
            }      
        }   
        *custo = custo_min;
        fly = fly->next;
    }
    //printf("%s %.2f",nome,custo_min);
    return nome;   
}

char * readChar(const char *msg, const char *msgErr)
{
    fflush(stdin);
    char ValueString[100];
    printf("%s",msg);
    while ((fgets(ValueString, sizeof(ValueString), stdin) == NULL) || strtok(ValueString, "\n") == NULL)
    {
        printf("%s",msgErr);
    }
    strtok(ValueString, "\n");

    return strdup(ValueString);
}

void custo_aeroporto(Airports **hash)
{
    char *nome;
    char *nome1;
    float custo=0,custo1=0;
    char * fim;
    char * inicio1;
    char *inicio2;

    fim = readChar("Diga o destino -> ","ERRO");
    inicio1 = readChar("Diga a 1 opcao de saida -> ","ERRO");
    inicio2 = readChar("Diga a 2 opcao de saida -> ","ERRO");

    bool a = exists_in_hash(hash,fim);
    bool b = exists_in_hash(hash,inicio1);
    bool c = exists_in_hash(hash,inicio2);

    if(a == true && b == true && c == true)
    {
        nome = custo_viagem(hash,inicio1,fim,&custo);
        nome1 = custo_viagem(hash,inicio2,fim,&custo1);

        if(custo < custo1)
        {
            printf("A melhor opcao para ir para %s e %s com um custo de %.2f\n",fim,nome,custo);
        }
        if(custo1 < custo)
        {
            printf("A melhor opcao para ir para %s e %s com um custo de %.2f\n",fim,nome1,custo1);
        }
        if(custo == custo1)
        {
            printf("O custo e igual\n");
        }
    }
    else
    {
        printf("Nao encontrado\n");
    }
}

void custo_cidade(Airports **hash)
{
    bool a,b,c;
    char *nome;
    char *nome1;
    float custo=0,custo1=0;
    char *fimcidade,*inicio1cidade,*inicio2cidade;
    char *fim;
    char *inicio1;
    char *inicio2;

    fimcidade = readChar("Diga a cidade destino -> ","ERRO");
    inicio1cidade = readChar("Diga a 1 cidade de saida -> ","ERRO");
    inicio2cidade = readChar("Diga a 2 cidade de saida -> ","ERRO");

    fim = busca_code(hash,fimcidade);
    inicio1 = busca_code(hash,inicio1cidade);
    inicio2 = busca_code(hash,inicio2cidade);

    if(fim != NULL) { a = exists_in_hash(hash,fim); } else { a = false; }
    if(inicio1 != NULL) { b = exists_in_hash(hash,inicio1); } else { b = false; }
    if(inicio2 != NULL) { c = exists_in_hash(hash,inicio2); } else { c = false; }

    if(a == true && b == true && c == true)
    {
        nome = custo_viagem(hash,inicio1,fim,&custo);
        nome1 = custo_viagem(hash,inicio2,fim,&custo1);

        if(custo < custo1)
        {
            printf("A melhor opcao para ir para %s e %s com um custo de %.2f\n",fimcidade,inicio1cidade,custo);
        }
        if(custo1 < custo)
        {
            printf("A melhor opcao para ir para %s e %s com um custo de %.2f\n",fimcidade,inicio2cidade,custo1);
        }
        if(custo == custo1)
        {
            printf("O custo e igual\n");
        }
    }
    else
    {
        printf("Nao encontrado\n");
    }
}

void internacional(Airports **hash)
{
    int tam = M,j = 0,cont[tam];
    char * country;
    char * aeroportos[tam];
    //country = readChar("Diga o Pais -> ","ERRO");
    country = strdup("Portugal");

    for(int x = 0;x<tam;x++)
    {
        cont[x] = 0;
        aeroportos[x] = strdup(" ");
    }

    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            if(strcmp(ptr->Country,country) == 0)
            {
                aeroportos[j] = strdup(ptr->Code);
                j++;
                break;
            }
            ptr = ptr->next;
        }
    }

    int k = 0;
    int x = 0;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            for(int x = 0;x<tam;x++)
            {
                if(strcmp(ptr->Code,aeroportos[x]) == 0)
                {
                    cont[k]++;
                }
            }
            ptr = ptr->next;
            k++;
        }
    }

    /*
    for(j=0;j<tam;j++)
    {
        int h = hash_func(aeroportos[j]);
        Airports *ptr = hash[h];
        while (ptr)
        {
            cont[j] = cont[j] + 1;
            ptr = ptr->next;
        }
    }
    */
    
    for(int x = 0;x<tam;x++)
    {
        if(cont[x]!=0)
        {
            printf("%d ",cont[x]);
        }   
    }
    
}

bool verificar_Aux(Aux aux[M],const char * code)
{
    for(int x = 0;x<M;x++)
    {
        if(strcmp(aux[x].airporto,code) == 0)
        {
            return true;
        }
    }
    return false;
}

int pos_aux(Aux aux[M],const char * code)
{
    for(int x = 0;x<M;x++)
    {
        if(strcmp(aux[x].airporto,code) == 0)
        {
            return x;
        }
    }

    return 0;
}

void cidade_mais_partidas(Airports **hash)
{
    Aux aux[M];
    bool existe;
    for(int x = 0;x<M;x++)
    {
        aux[x].airporto = strdup(" ");
        aux[x].cont = 0;
    }

    int k=0;
    int j=0;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];        
        while (ptr)
        {
            Flights * fly = ptr->flights;    
             while (fly)
            {
                existe = verificar_Aux(aux,fly->aofd);
                if(existe == false)
                {
                    aux[j].airporto = strdup(fly->aofd);
                    aux[j].cont = aux[j].cont + 1;
                    j++;
                }
                else
                {
                    k = pos_aux(aux,fly->aofd);
                    aux[k].cont++;
                }
                fly = fly->next;
            }
            ptr = ptr->next;
        }
    }

    int max = 0;
    char * code;

    for(int x = 0;x<M;x++)
    {
        if(max < aux[x].cont)
        {
            max =  aux[x].cont;
            code = strdup(aux[x].airporto);
        }
    }
    char * cidade;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];   
        while(ptr)
        {
            if(strcmp(ptr->Code,code)==0)
            {
                cidade = strdup(ptr->City);
            }
            ptr = ptr->next;
        }
    }

    printf("A cidade com mais partidas e %s com %d partidas\n",cidade,max);
}

void cidade_mais_chegadas(Airports **hash)
{
   Aux aux[M];
    bool existe;
    for(int x = 0;x<M;x++)
    {
        aux[x].airporto = strdup(" ");
        aux[x].cont = 0;
    }

    int k=0;
    int j=0;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];        
        while (ptr)
        {
            Flights * fly = ptr->flights;    
             while (fly)
            {
                existe = verificar_Aux(aux,fly->aofa);
                if(existe == false)
                {
                    aux[j].airporto = strdup(fly->aofa);
                    aux[j].cont = aux[j].cont + 1;
                    j++;
                }
                else
                {
                    k = pos_aux(aux,fly->aofa);
                    aux[k].cont++;
                }
                fly = fly->next;
            }
            ptr = ptr->next;
        }
    }

    int max = 0;
    char * code;

    for(int x = 0;x<M;x++)
    {
        if(max < aux[x].cont)
        {
            max =  aux[x].cont;
            code = strdup(aux[x].airporto);
        }
    }
    char * cidade;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];   
        while(ptr)
        {
            if(strcmp(ptr->Code,code)==0)
            {
                cidade = strdup(ptr->City);
            }
            ptr = ptr->next;
        }
    }

    printf("A cidade com mais partidas e %s com %d partidas\n",cidade,max);
}

void Alterar_duracao_distancia(Airports **hash)
{
    char * aofd;
    char * aofa;
    char * type;
    float distancia,duration;
    int cont=0;
    aofd = readChar("Diga o AOFD -> ","ERRO");
    aofa = readChar("Diga o AOFA -> ","ERRO");
    type = readChar("Diga o Type -> ","ERRO");
    system("Clear || CLS");
    Flights *fly = NULL;
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            fly = ptr->flights;
            while (fly)
            {   
                if(strcmp(fly->aofa,aofa) == 0 && strcmp(fly->aofd,aofd) == 0 && strcmp(fly->type,type) == 0)
                {
                    cont++;
                    printf("Diga a distancia -> "); scanf("%f",&distancia);
                    printf("Diga a Duration -> "); scanf("%f",&duration);
                    fly->distance = distancia;
                    fly->duration = duration;
                }
                fly = fly->next;
            }
            ptr = ptr->next;
        }
    }

    if(cont == 0)
    {
        printf("Nao encontrado\n");
    }
}

void AdicionarAeroporto(Airports **hash)
{
    char *city,*code,*country;
    bool existe;
    int cont=0,contCidade = 0;

    city = readChar("Diga a cidade -> ","ERRO");

    for(int i = 0;i < M;i++)
    {
        if(cont < 0)
        {
            break;
        }
        Airports *ptr = hash[i];
        while (ptr)
        {
            if(strcmp(ptr->City,city)==0)
            {
                contCidade++;
                if(cont == 0)
                {
                    code = readChar("Diga o code -> ","ERRO");
                    existe = exists_in_hash(hash,code);
                    if(existe == false && cont == 0)
                    {
                        hash_insert(hash, code, 0, 0, NULL, NULL); 
                        set_Flight(hash,city,ptr->Country,code);
                        cont++;
                    }
                    else
                    {
                        printf("Ja existe\n");
                    }
                }

            }
            ptr = ptr->next;
        }
    }

    if(contCidade == 0)
    {
        printf("Essa cidade nao existe\n");
    }
    
}

void ligacao_Air(Airports **hash)
{
    char *aofd,*aofa,*type;
    float duration,distance;
    int typee=0;
    bool existe,exitefim;
    aofd = readChar("Diga o AOFD -> ","ERRO");
    aofa = readChar("Diga o AOFA -> ","ERRO");
    printf("Diga a distance -> "); scanf("%f",&distance);
    printf("Diga a duration -> "); scanf("%f",&duration);

    printf("Diga o type (0 - Normal | 1 - Lowcost ) -> "); scanf("%d",&typee);
    switch (typee)
    {
        case 0: type = strdup("normal"); break;
        case 1: type = strdup("lowcost"); break;
        default: type = strdup("normal"); break;
    }

    existe = exists_in_hash(hash,aofd);

    if(existe == true)
    {
        exitefim = exists_in_hash(hash,aofa);
        if(exitefim == true)
        {
            if(strcmp(aofd,aofa)!=0)
            {
                hash_insert(hash, aofd, distance, duration, type, aofa); 
            }
            else
            {
                printf("Impossivel levantar e aterrar no mesmo Airport\n");
            }
        }
        else
        {
            printf("Esse Airport de chegada nao existe\n");
        }     
    }
    else 
    {
        printf("Esse Airport de partida nao existe\n");
    }
}

bool verificar_city(Airports **hash,const char *city)
{
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            if(strcmp(ptr->City,city) == 0)
            {
                return true;
            }
            ptr = ptr->next;
        }
    }
    return false;
}

void adicionar_city(Airports **hash)
{
    bool existe,exite_cod;
    char *city,*code;
    city = readChar("Diga a city -> ","ERRO");

    existe = verificar_city(hash,city);

    if(existe == false)
    {
        code = readChar("Diga a Code -> ","ERRO");
        exite_cod = exists_in_hash(hash,code);
        if(exite_cod == false)
        {
            hash_insert(hash, code, 0, 0, NULL, NULL); 
            set_Flight(hash,city,NULL,code);
        }
        else
        {
            printf("Esse codigo ja existe\n");
        }
    }
    else
    {
        printf("Essa cidade ja existe\n");
    }
}

void listar_cidade(Airports **hash)
{
    for(int i = 0;i < M;i++)
    {
        Airports *ptr = hash[i];
        while (ptr)
        {
            printf("%s\n",ptr->City);
            ptr = ptr->next;
        }
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

int main() 
{
    int op=0;
    bool ola;
    Airports **hash;
    hash = (Airports**) calloc(M, sizeof(Airports*));
    Read_flights_PT(hash);
    Read_airports_PT(hash);

    do
    {
        system("Clear || CLS");
        printf("Menu:\n");
        printf("1 -> Listar Voos\n");
        printf("2 -> Listar Airposts\n");
        printf("3 -> Custo Aeroporto\n");
        printf("4 -> Custo Cidade\n");
        printf("5 -> Mais Partidas\n");
        printf("6 -> Mais Chegadas\n");
        printf("7 -> Intenacional\n");
        printf("Extras-> \n");
        printf("8 -> Alterar Duracao e distancia\n");
        printf("9 -> Adicionar por cidade\n");
        printf("10 -> Adicionar ligacao\n");
        printf("11 -> Adicionar Cidade\n");
        printf("0 -> Sair\n");
        printf("Opcao-> "); scanf("%d",&op);
        switch (op)
        {
            case 1: system("Clear || CLS"); listar_voos(hash); system("pause"); break;
            case 2: system("Clear || CLS"); listar_voos__(hash); system("pause"); break;
            case 3: system("Clear || CLS"); custo_aeroporto(hash); system("pause"); break;
            case 4: system("Clear || CLS"); custo_cidade(hash);  system("pause"); break;
            case 5: system("Clear || CLS"); cidade_mais_partidas(hash);  system("pause"); break;
            case 6: system("Clear || CLS"); cidade_mais_chegadas(hash);  system("pause"); break;
            case 7: system("Clear || cls"); internacional(hash); system("pause"); break;
            case 8: system("Clear || cls"); Alterar_duracao_distancia(hash); system("pause"); break;
            case 9: system("Clear || cls"); AdicionarAeroporto(hash); system("pause"); break;
            case 10: system("Clear || cls"); ligacao_Air(hash); system("pause"); break;
            case 11: system("Clear || cls"); adicionar_city(hash); system("pause"); break;
        }
    } while (op < 1 && op > 10 || op != 0);

    return 0;
}