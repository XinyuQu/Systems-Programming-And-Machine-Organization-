#ifndef M61_H
#define M61_H 1
#include <stdlib.h>
#include <inttypes.h>


typedef int bool;
#define true 1
#define false 0

void* m61_malloc(size_t sz, const char* file, int line);
void m61_free(void* ptr, const char* file, int line);
void* m61_realloc(void* ptr, size_t sz, const char* file, int line);
void* m61_calloc(size_t nmemb, size_t sz, const char* file, int line);
void print_heavy_hitter_report();


struct m61_statistics {
    unsigned long long nactive;         // # active allocations
    unsigned long long active_size;     // # bytes in active allocations
    unsigned long long ntotal;          // # total allocations
    unsigned long long total_size;      // # bytes in total allocations
    unsigned long long nfail;           // # failed allocation attempts
    unsigned long long fail_size;       // # bytes in failed alloc attempts
    char* heap_min;                     // smallest allocated addr
    char* heap_max;                     // largest allocated addr

    struct metadata *head;              // head of the linked list for metadata
    struct heavy_hitter *first          // head of the linked list for heavy hitter
    

};


void m61_getstatistics(struct m61_statistics* stats);

void m61_printstatistics(void);
void m61_printleakreport(void);

#if !M61_DISABLE
#define malloc(sz)              m61_malloc((sz), __FILE__, __LINE__)
#define free(ptr)               m61_free((ptr), __FILE__, __LINE__)
#define realloc(ptr, sz)        m61_realloc((ptr), (sz), __FILE__, __LINE__)
#define calloc(nmemb, sz)       m61_calloc((nmemb), (sz), __FILE__, __LINE__)
#endif

void* base_malloc(size_t sz);
void base_free(void* ptr);
void base_disablealloc(int is_disabled);

#endif
