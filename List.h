#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef double elem_t;
typedef int    error_t;

const size_t MIN_CAPACITY = 20;


enum errors {MEMORY_ERROR = 1, CAPACITY_ERROR = 2, NULL_POINTER_ACCESS = 3};

struct Node
{
    elem_t data;
    int    next;
    int    prev;
};

struct List
{
    int head;
    int tail;
    
    size_t size;
    size_t capacity;
    int free;

    Node* nodes;
};

// List functions
List*   ListConstruct   (size_t capacity);
List*   ListDestruct    (List* lst);
error_t ListStartFiller (List* lst);

int    GetIndex     (List* lst, int logical_index);

void   InsertHead   (List* lst, elem_t value);
elem_t ExtractHead  (List* lst);

void   InsertRandomAfter    (List* lst, int index, elem_t value);
elem_t ExtractRandom        (List* lst, int index);
//-----------------------------------------


// Protection functions
error_t Verify (List* lst);
void    LogsCleaner ();
void    ListDump          (List* lst, char* func, error_t err);
void    LogicalLogsMaker  (List* lst);
void    PhysicalLogsMaker (List* lst);

void    MakePlaces        (List* lst, FILE* GraphicLogs);
void    PrintBranch       (List* lst, FILE* GraphicLogs, int start_index);
//-----------------------------------------------------





