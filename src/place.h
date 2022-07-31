#define placeWayLength 10

typedef struct way {
    int distance;
    struct place *to;
} WAY;

typedef struct place {
    char *name;
    struct way ways[placeWayLength];
} PLACE;

struct place * place_new(const char *name);
struct place * place_get(const char *name);
struct way * place_get_next_way(struct place *p, struct way *last);
void place_add_way(struct place *p, struct place *to, int distance);
void place_free(PLACE *p);
void place_dump(PLACE *p);

int place_get_route(const char *start, const char *destination, char *buffer);
int place_get_route(PLACE *start, const char *destination, char *buffer);