#include "../../libc/include/taskshed.h"
#include "../../libc/include/heap.h"
#include "../../libc/include/string.h"

uint32_t total_weight;

void init_taskshed(void)
{
    process_pool = malloc(sizeof(process_t));
    process_count = 0;
    total_weight = 0;
    exist_ids = malloc(sizeof(uint16_t));
}

void extend_process_pool(void)
{
    process_t *process_temp = malloc(sizeof(process_pool));
    memcpy(process_temp, process_pool, sizeof(process_pool));
    process_pool = realloc(process_pool, sizeof(process_pool) + sizeof(process_t));
    memcpy(process_pool, process_temp, sizeof(process_pool));
}

void reduce_process_pool(void)
{
    if (sizeof(process_pool) - sizeof(process_t) <= 0) {
        return;
    }
    process_t *process_temp = malloc(sizeof(process_pool) - sizeof(process_t));
    memcpy(process_temp, process_pool, sizeof(process_pool) - sizeof(process_t));
    process_pool = realloc(process_pool, sizeof(process_pool) - sizeof(process_t));
    memcpy(process_pool, process_temp, sizeof(process_pool) - sizeof(process_t));
}

void calculate_time_slice() 
{
    total_weight = 0;
    for (int i = 0; i < process_count; i++) {
        total_weight += process_pool[i].priority;
    }
    for (int i = 0; i < process_count; i++) {
        process_pool[i].time_slice = (process_pool[i].priority * 1000) / total_weight;
    }
}

void yield_processes(void) 
{

}