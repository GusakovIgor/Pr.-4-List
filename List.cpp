#include "List.h"


int main ()
{
    size_t capacity = 0;
    scanf ("%ld", &capacity);
    List* lst = ListConstruct (capacity);
    
    printf ("\nOK\n");

    for (int val = 10; val < 30; val += 10)
    {
        InsertHead(lst, val);
    }
    
    elem_t check = ExtractHead(lst);
    printf ("\nCheck = %lg\n\n", check);
    
    //
    printf ("List:\n");
    printf ("head = %d\n",  lst->head);
    printf ("tail = %d\n",  lst->tail);
    printf ("size = %ld\n", lst->size);
    printf ("free = %d\n",  lst->free);
    
    printf ("i:   data:   next:   prev:\n");
    for (int i = 0; i < lst->capacity; i++)
    {
        printf ("%-7d ",  i);
        printf ("%-7lg ", lst->nodes[i].data);
        printf ("%-7d ",  lst->nodes[i].next);
        printf ("%-7d ",  lst->nodes[i].prev);
        printf ("\n");
    }
    //
    
    InsertRandomAfter (lst, GetIndex(lst, 1), 90);
    
    LogicalLogsMaker  (lst);
    PhysicalLogsMaker (lst);
    
    lst = ListDestruct (lst);
    
    return 0;
}



List* ListConstruct (size_t capacity)
{
    
    LogsCleaner ();
    
    capacity++;         // Cause we indexing from 0, but use zero element as error indexing (like NULL indexing)
    if (capacity == 0)
    {
        int err = 1;
    }
    if (capacity < MIN_CAPACITY)
    {
        capacity = MIN_CAPACITY + 1;
    }
    
    List* lst = (List*) calloc (1, sizeof (List));
    
    lst->nodes = (Node*) calloc (capacity, sizeof (Node));
    assert (lst->nodes);
    
    lst->capacity = capacity;
    
    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;
    
    lst->size = 0;
    
    error_t err = ListStartFiller (lst);
    assert (!err);
    
    return lst;
}

List* ListDestruct (List* lst)
{
    free (lst->nodes);
    free (lst);
    
    return NULL;
}

error_t ListStartFiller (List* lst)
{
    for (int i = 1; i < lst->capacity; i++)
    {
        lst->nodes[i].next = (i < lst->capacity - 1) ? (i + 1) : 0;
        lst->nodes[i].prev = (i > 1                ) ? (i - 1) : 0;
    }
    
    assert (lst->nodes[0].data == 0);
    assert (lst->nodes[0].next == 0);
    assert (lst->nodes[0].prev == 0);
    
    return 0;
}


void InsertHead (List* lst, elem_t value)
{
    ListDump (lst, "InsertHead", 0);
    
    InsertRandomAfter (lst, 0, value);
    
    ListDump (lst, "InsertHead", 0);
}

void InsertRandomAfter (List* lst, int index, elem_t value)
{
    int old_free = lst->free;
    lst->free = lst->nodes[old_free].next;
    lst->nodes[lst->free].prev = 0;
    
    lst->nodes[old_free].prev = index;
    lst->nodes[old_free].data = value;
    
    if (index == 0)
    {
        lst->nodes[old_free].next = lst->head;
        lst->head = old_free;
    }
    else
    {
        lst->nodes[old_free].next = lst->nodes[index].next;
    }
    
    if (index != 0)
        lst->nodes [lst->nodes[old_free].prev].next  = old_free;
    
    if (lst->nodes[old_free].next != 0)
        lst->nodes[lst->nodes[old_free].next].prev = old_free; 
    
    lst->size++;
}

elem_t ExtractHead (List* lst)
{
    ListDump (lst, "ExtractHead", 0);
    
    elem_t value = 0;
    int old_free = 0;
    int old_head = 0;
    
    lst->nodes[lst->free].prev = lst->head;

    old_free = lst->free;
    old_head = lst->head;
    if (lst->size != 1)
    {
        lst->head = lst->nodes[old_head].next;
        lst->nodes[lst->head].prev = 0;
    }
    
    lst->free = old_head;
    lst->nodes[lst->free].next = old_free;
    value = lst->nodes[lst->free].data;
    lst->nodes[lst->free].data = 0;
    
    lst->size--;
    
    ListDump (lst, "ExtractHead", 0);
    
    return value;
}


int GetIndex (List* lst, int logical_index)
{
    int count = 1;
    int iter  = lst->head;
    
    while (iter != 0)
    {
        if (count == logical_index)
            break;
            
        count++;
        iter = lst->nodes[iter].next;
    }
    
    if (iter == 0)
    {
        printf ("ERROR with GetIndex, your logical index greater than number of elements in list\n");
        assert (!"OK");
    }
    
    return iter;
}