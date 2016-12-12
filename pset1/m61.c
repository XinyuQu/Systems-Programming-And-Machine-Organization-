#define M61_DISABLE 1
#include "m61.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <limits.h>


typedef int bool;
#define false 0
#define true 1




/// m61_malloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
///    The memory is not initialized. If `sz == 0`, then m61_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.


#define ALLOCATED 4578906
#define FREED 34567890
#define CANARY 462073

<<<<<<< HEAD
void heavy_hitters(size_t sz, const char* file, int line);

struct m61_statistics statistics = {0, 0, 0, 0, 0, 0, NULL, NULL, NULL};
  

  struct counter
{
    int line_number;
    char* file_name;             
    size_t bytes_alloc;
    int number_of_alloc;
};

=======
struct m61_statistics statistics = {0, 0, 0, 0, 0, 0, NULL, NULL, NULL};
  
>>>>>>> 7924c06e84449b51a2929ca37fbbdad508cd3be8
struct metadata
{
    size_t size; 
    int allocation;
    struct metadata *prev;
    struct metadata *nxt; 
    
    char* file_name;
    int line_number;

};

<<<<<<< HEAD
bool zero_counter;
        int zero_ctr_place;
        bool changed_2 = false;
        bool changed = false;

struct counter counters[5] = {{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0}};

struct counter counters_updated[5] = {{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0},{0,NULL,0, 0}};
=======

struct heavy_hitter
 {
int line_number;
char* file_name;              
size_t bytes_alloc;
struct heavy_hitter *nxt;
struct heavy_hitter *prev;
}
heavy-hitter* heavy-hitter-head;
;



>>>>>>> 7924c06e84449b51a2929ca37fbbdad508cd3be8


void* m61_malloc(size_t sz, const char* file, int line) {
    (void) file, (void) line;   // avoid uninitialized variable warnings
   


    if (sz + 2*sizeof(struct metadata) <= sz) {
        statistics.nfail ++;
        statistics.fail_size += sz;
        return NULL;
    }

    struct metadata *meta = base_malloc(sz + 2*sizeof(struct metadata));

    if(meta)
    {


        //save sz in the size field of metadata 
        meta->size = sz;
        meta->allocation = ALLOCATED;

          meta->file_name = file;
          meta->line_number=line;

    
        char *address = (char *)(meta) + meta->size + sizeof(struct metadata);
        *(int *)address = CANARY;

        statistics.ntotal ++;
        statistics.nactive ++;
        statistics.total_size += sz;
        statistics.active_size += sz;
       

        if (statistics.head == NULL)
        {

            statistics.head = meta;
            meta->prev = NULL;
            meta->nxt = NULL;
        }

        else {
            meta->nxt = statistics.head;
            meta->prev = NULL;
            statistics.head->prev = meta; 
            statistics.head = meta;    
        
        }

         
        if (statistics.heap_min==NULL || statistics.heap_min > meta)
        { 
            statistics.heap_min = meta;
        }


        if (statistics.heap_max==NULL || statistics.heap_max < (meta + sz)) 
        {
            statistics.heap_max = meta + sz;
        } 
<<<<<<< HEAD
    



        return meta + 1;


        heavy_hitters(sz, file, line);

 
}

=======
        
        return meta + 1;

    }
    
>>>>>>> 7924c06e84449b51a2929ca37fbbdad508cd3be8

    else{

        statistics.nfail ++;
        statistics.fail_size += sz;
        return NULL;
    }
    
 
<<<<<<< HEAD
}


void heavy_hitters(size_t sz, const char* file, int line) {
/*
Sample nth allocation

Either that's a new line file/ make new mode and keep track of it

Or you've already been keeping track of it it / so add byte
*/

  if(drand48() <= 0.2)
  {
    if heavy-hitter-head->size_t_bytes_alloc > 0.2 
    {

        if (!heavy_hitter)
            heavy_hitter-head*ptr; //malloc
        else 
            curr_ptr*head;
        if file* line
            bytes_alloc+=sz;

    }
}
 
 if(curr-ptr == NULL) //MALLOC
   

}

/*



        for (int j = 0; j < 5; j++)
            {
            if (counters[j].number_of_alloc == 0)
            {
                zero_counter = true;
                zero_ctr_place = j;
            }
        }
        for (int i, x = 0; i,x < 5; x,i++)
        {
            if ((counters[i].file_name != file) && (counters[i].line_number != line)) //&& (zero_counter))
            {
                counters[zero_ctr_place].number_of_alloc = 1;
                counters[zero_ctr_place].bytes_alloc = sz;
                counters[zero_ctr_place].file_name = file;
                counters[zero_ctr_place].line_number = line;

                counters_updated[zero_ctr_place].bytes_alloc = sz;
                counters_updated[zero_ctr_place].line_number = line;
                counters_updated[zero_ctr_place].file_name = file;

            }

            else if ((counters[i].file_name == file) && (counters[i].line_number == line))
            { 
                counters[i].number_of_alloc ++;
                counters[i].bytes_alloc += sz;

                counters_updated[i].bytes_alloc = sz - counters[i].bytes_alloc;

            }
            else

            {

   for (int k = 0; k < 5; k++)
                {
                    counters[k].number_of_alloc --;
                      if ((counters[k].bytes_alloc - sz <= 0) && (changed == false))
                        {
                            counters[k].bytes_alloc = sz - counters[k].bytes_alloc;
                            counters[k].line_number = line;
                            counters[k].file_name = file;


                           
                        }
                       if ((counters[k].bytes_alloc - sz <= 0) && (changed))   
                    {
                        counters[k].bytes_alloc = 0;
                    }
                    else
                    {
                        counters[k].bytes_alloc -= sz;
                    }
    }


 }
    
    }
=======
>>>>>>> 7924c06e84449b51a2929ca37fbbdad508cd3be8
}
*/


        void print_heavy_hitter_report() {

for (int i=0; i<5; i++) {
counters[i].bytes_alloc = 0.2 * statistics.total_size;
printf("%.2f ", counters[i].bytes_alloc);


}
}





/// m61_free(ptr, file, line)
///    Free the memory space pointed to by `ptr`, which must have been
///    returned by a previous call to m61_malloc and friends. If
///    `ptr == NULL`, does nothing. The free was called at location
///    `file`:`line`.

void m61_free(void *ptr, const char *file, int line) {
    (void) file, (void) line;   // avoid uninitialized variable warnings
    struct metadata *meta = (struct metadata *)ptr - 1;
    if (ptr == NULL) 
    {
        return NULL;
    }
    if ((ptr == (void *) 0x1) || (ptr > statistics.heap_max) || (ptr < statistics.heap_min))
    {
        printf("MEMORY BUG %s:%i: invalid free of pointer %p, not in heap\n",file, line, ptr);
  
    }

    else
    {
           
        if (meta->allocation == FREED)
       {
            printf("MEMORY BUG: %s:%i: invalid free of pointer %p, not in heap\n",file, line, ptr);
       
            if (meta->prev != NULL && meta->prev->nxt!=meta)
             {
             printf(" %s:%i: ??? is 100 bytes inside a %p byte region allocated here\n", file, line, ptr);  
             }

            if (meta->prev == NULL && meta != statistics.head)
            {
            printf(" %s:%i: ??? is 100 bytes inside a %p byte region allocated here\n", file, line, ptr);  
            }
<<<<<<< HEAD
=======


            }
       else if (meta->allocation != ALLOCATED)
            {
            printf("MEMORY BUG: %s:%i: invalid free of pointer %p, not allocated\n", file, line, ptr);

   
            if (meta->prev == NULL && meta != statistics.head)
            {
            printf("  %s:%i: ??? is 100 bytes inside a 2001 byte region allocated here\n", file, line-1, ptr);  
            }

       } 

       else {
        char *address = (char *)(meta) + meta->size + sizeof(struct metadata);

        if  (*(int *)address != CANARY)
        {   
            printf("MEMORY BUG: %s:%i: detected wild write during free of pointer %p\n",file, ptr );
            
            abort();

        } 

        if (meta->prev != NULL && meta->prev->nxt!=meta) //&& meta->prev != NULL)
            {  
             printf("MEMORY BUG???: invalid free of pointer ???, not allocated\n");  
          
            }

            if (meta-> nxt != NULL && meta->nxt->prev !=meta)
            {  
            printf("MEMORY BUG???: invalid free of pointer ???, not allocated//!\n");  
         } 
>>>>>>> 7924c06e84449b51a2929ca37fbbdad508cd3be8

       
        else 
        {
            
        statistics.active_size -= meta->size;
        statistics.nactive --;
        base_free(meta);
        meta->allocation = FREED;
        meta = (struct metadata*)ptr - 1;

        if (meta == statistics.head) 

         {
            statistics.head = meta->nxt;
        }
          
         if (meta->nxt != NULL)
                meta->nxt->prev = meta->prev;
                
         if (meta->prev != NULL)
                meta->prev->nxt = meta->nxt;
              
            }

        }
   
        }

    }
    

            }
       else if (meta->allocation != ALLOCATED)
            {
            printf("MEMORY BUG: %s:%i: invalid free of pointer %p, not allocated\n", file, line, ptr);

   
            if (meta->prev == NULL && meta != statistics.head)
            {
            printf("  %s:%i: ??? is 100 bytes inside a 2001 byte region allocated here\n", file, line-1, ptr);  
            }

       } 

       else {
        char *address = (char *)(meta) + meta->size + sizeof(struct metadata);

        if  (*(int *)address != CANARY)
        {   
            printf("MEMORY BUG: %s:%i: detected wild write during free of pointer %p\n",file, ptr );
            
            abort();

        } 

        if (meta->prev != NULL && meta->prev->nxt!=meta) //&& meta->prev != NULL)
            {  
             printf("MEMORY BUG???: invalid free of pointer ???, not allocated\n");  
          
            }

            if (meta-> nxt != NULL && meta->nxt->prev !=meta)
            {  
            printf("MEMORY BUG???: invalid free of pointer ???, not allocated//!\n");  
         } 

       
        else 
        {
            
        statistics.active_size -= meta->size;
        statistics.nactive --;
        base_free(meta);
        meta->allocation = FREED;
        meta = (struct metadata*)ptr - 1;

        if (meta == statistics.head) 

         {
            statistics.head = meta->nxt;
        }
          
         if (meta->nxt != NULL)
                meta->nxt->prev = meta->prev;
                
         if (meta->prev != NULL)
                meta->prev->nxt = meta->nxt;
              
            }

        }
   
        }

    }
    

/// m61_realloc(ptr, sz, file, line)
///    Reallocate the dynamic memory pointed to by `ptr` to hold at least
///    `sz` bytes, returning a pointer to the new block. If `ptr` is NULL,
///    behaves like `m61_malloc(sz, file, line)`. If `sz` is 0, behaves
///    like `m61_free(ptr, file, line)`. The allocation request was at
///    location `file`:`line`.

void* m61_realloc(void* ptr, size_t sz, const char* file, int line) {
    void* new_ptr = NULL;
    size_t old_size = sizeof(ptr);
    if (base_malloc(sz + old_size)) {


        if (sz)
            new_ptr = m61_malloc(sz, file, line);
        if (ptr && new_ptr) {
            if (sz < old_size) 
            {
                memcpy(new_ptr, ptr, old_size);
            }
            else 
            {
                memcpy(new_ptr, ptr, sz);
            }
        }
        m61_free(ptr, file, line);
        return new_ptr;
    }
    else 
        return NULL;
}


/// m61_calloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. The memory
///    is initialized to zero. If `sz == 0`, then m61_malloc may
///    either return NULL or a unique, newly-allocated pointer value.
///    The allocation request was at location `file`:`line`.

void* m61_calloc(size_t nmemb, size_t sz, const char* file, int line) {
    // Your code here (to fix test014).
    
    {


        if (((nmemb * sz) / sz) != nmemb || (sz == 0))
        {
            statistics.nfail ++; 
            return NULL;

        }

        else 
        {
            void* ptr = m61_malloc(nmemb * sz, file, line);
            if (ptr)
                memset(ptr, 0, nmemb * sz);
                return ptr;
        }
        
    }
}


/// m61_getstatistics(stats)
///    Store the current memory statistics in `*stats`.

void m61_getstatistics(struct m61_statistics* stats) {
    // Stub: set all statistics to enormous numbers
    memset(stats, 255, sizeof(struct m61_statistics));
    memcpy(stats, &statistics, sizeof(struct m61_statistics));
    // Your code here.
}


/// m61_printstatistics()
///    Print the current memory statistics.

void m61_printstatistics(void) {
    struct m61_statistics stats;
    m61_getstatistics(&stats);

    printf("malloc count: active %10llu   total %10llu   fail %10llu\n",
           stats.nactive, stats.ntotal, stats.nfail);
    printf("malloc size:  active %10llu   total %10llu   fail %10llu\n",
           stats.active_size, stats.total_size, stats.fail_size);
}


/// m61_printleakreport()
///    Print a report of all currently-active allocated blocks of dynamic
///    memory.

void m61_printleakreport(void) {
    // Your code here.
  struct m61_statistics stats; 

 // statistics.head=meta;
       struct metadata* curr_ptr = statistics.head;
     // char* a = file_name;
       //meta->line_number=line;
       while (curr_ptr != NULL)
       {
        size_t size = curr_ptr->size;
        //LEAK CHECK: test???.c:18: allocated object ??pointer?? with size ??size??`
         //printf("LEAK CHECK: %s:%i: allocated object %p size %lu\n",  curr_ptr->file_name, curr_ptr->line_number, curr_ptr + 1, curr_ptr->size);
         printf("LEAK CHECK: %s:%i: allocated object %p with size %lu\n",  curr_ptr->file_name, curr_ptr->line_number, curr_ptr + 1, curr_ptr->size);
         //19

         //printf("%d, %d\n", meta->line_number, meta->file_name);

         //printf("lEAK CHECK: %s:%i: allocated object %p with size %zu\n",curr_ptr->file, curr_ptr->line, curr_ptr, curr_ptr->size); 
         curr_ptr = curr_ptr->nxt; 
       }
}
