#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "instantiate.h"
#include "circular_buffer.h"

struct circular_buffer
{
    char *tail;
    unsigned long length;
    char *head;
    char *current;
    bool isFull;
};

circular_buffer circularBuffer_construct(unsigned long length)
{
    INSTANTIATE(circular_buffer);
    self->tail = self->head = self->current = malloc(length * sizeof(struct circular_buffer));

    self->length = length;
    self->isFull = false;
    return self;
}

void circularBuffer_collect(circular_buffer self)
{
    free(self->tail);
    free(self);
}

void circularBuffer_append_char_at_head(circular_buffer self, char c)
{
    assert(self->head < self->tail + self->length);
    *(self->head)++ = c;
    if (self->head == self->tail + self->length)
    {
        self->head = self->tail;
        self->isFull = true;
    }
}

void circularBuffer_set_current_to_head(circular_buffer self)
{
    self->current = self->head;
}

char circularBuffer_get_char_before_current(circular_buffer self)
{

    if(self->current > self->tail)
    {
        self->current--;
    }
    else if(self->isFull)
    {
        self->current = self->tail + (self->length) -1;
    }
    else if(self->head > self->tail)
    {
        self->current = self->head - 1;
    }
    else 
    {
        return '\0';
    }
    
    // TO COMPLETE :
    //Mon Business est le suivant:
    // si curseur current se trouve après tail , on décrémente current
    //sinon, si buffer est plein, je positionne curseur curent sur le dernier caractère du buffer
    //sinon, si curseur head se trouve après curseur tail, je positionne curseur current la position qui précéde head
    //sinon, buffer est vide , je retourne '\0';

    return *(self->current);
}

unsigned long circularBuffer_get_buffer_length(circular_buffer self)
{
    return self->length;
}