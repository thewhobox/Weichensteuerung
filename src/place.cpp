#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include "place.h"


#define debug   printf

struct place *places[100];
int placeCount = 0;

struct place * place_new(const char *name){
    struct place *p = (struct place *)malloc(sizeof(struct place));
    p->name = (char*)malloc(strlen(name) + 1);
    strcpy(p->name, name);
    p->ways[0].to = NULL;
    bzero(p->ways, sizeof(WAY) * placeWayLength);
    places[placeCount++] = p;
    return p;
}

struct place * place_get(const char *name){
    for(int i = 0; i < placeCount; i++)
    {
        place *p = places[i];
        if(strcmp(name, p->name) == 0)
            return p;
    }
    debug("returned null");
    return nullptr;
}

struct way * place_get_next_way(struct place *p, struct way *last){
    WAY *next;
    if(last == NULL)
        next = &p->ways[0];
    else
        next = ++last;

    if(next->to == NULL)
        return NULL;
    return next;
}

void place_add_way(struct place *p, struct place *to, int distance){
    int i;
    for(i = 0; i < placeWayLength; i++){
        if(p->ways[i].to == NULL)
            break;
    }
    p->ways[i].distance = distance;
    p->ways[i].to = to;

}

void place_dump(PLACE *p){
    printf("Place %s\n", p->name);
    WAY *w = NULL;
    while((w = place_get_next_way(p, w))){
        printf("\t--(%4d)--> %s\n", w->distance, w->to->name);
    }
}

void place_free(PLACE *p){
    free(p->name);
    free(p);
}

int _place_get_route(PLACE *start, const char *destination, char *buffer, char *visited){
    char *run_mem = (char *)malloc(410);
    int ret = 0;

    //char new_visited[200];
    char *new_visited = &run_mem[0];

    sprintf(new_visited, ",%s,%s", start->name, visited);
    //debug(new_visited);
    //char new_buffer[100];
    char *new_buffer = &run_mem[200];
    new_buffer[0] = '\0';

    //char shortest_buffer[100];
    char *shortest_buffer = &run_mem[300];
    shortest_buffer[0] = '\0';
    int shortest = INT_MAX;
    WAY *w = NULL;

    if(strcmp(start->name, destination) == 0){
        strcpy(buffer, destination);
        ret = 0;
        goto end;
    }
  
    while((w = place_get_next_way(start, w))){
        //char needle[100];
        //Nadel ist immer nur 4 lang: ,E2,
        char *needle = &run_mem[400];
        sprintf(needle, ",%s,", w->to->name);

        if(strstr(new_visited, needle) != NULL)
            continue;

        if(w->to->name[1] > '2')
        {
            int counter = 0;

            //von ASCII 3 bis 6
            for(int i = 51; i < 55; i++)
            {
                char buffer[3] = { w->to->name[0], i, '\0' };
                sprintf(needle, ",%s,", buffer);
                if(strstr(new_visited, needle) != NULL)
                    counter++;
            }
            if(counter >= 2)
                continue;
        }


        int distance = _place_get_route(w->to, destination, new_buffer, new_visited);
        if(strlen(new_buffer) == 0){
            continue;
        }
        sprintf(buffer, "%s - %s", start->name, new_buffer);
        distance = w->distance + distance;
        debug("%d : %s\n", distance, buffer);

        if(shortest > distance){
            strcpy(shortest_buffer, buffer);
            shortest = distance;
        }
    }

    if(shortest != INT_MAX){
        strcpy(buffer, shortest_buffer);
        ret = shortest;
        goto end;
    }

end:
    free(run_mem);
    return ret;
}

int place_get_route(const char *start, const char *destination, char *buffer){
    return place_get_route(place_get(start), destination, buffer);
}

int place_get_route(PLACE *start, const char *destination, char *buffer){
    return _place_get_route(start, destination, buffer, "");
}