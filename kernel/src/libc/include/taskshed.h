#ifndef TASKSHED_H
#define TASKSHED_H

#include "process.h"
#include "heap.h"

static process_t *process_pool;
static uint16_t process_count;
static uint16_t *exist_ids;

void init_taskshed(void);
void create_process(void (*process_func)());
void sort_by_priority(void);

#endif