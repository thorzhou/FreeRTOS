#ifndef PROJDEFS_H
#define PROJDEFS_H

// typedef void (*TaskFunction_t)(void *); //函数指针，实际就是空指针
typedef void (*TaskFunction_t)( void * );

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)
#define pdPASS (pdTRUE)
#define pdFAIL (pdFALSE)

#endif /*PROJDEFS_H*/
