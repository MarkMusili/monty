#include "monty.h"

void push(stack_t **stack, unsigned int line_number)
{
    stack_t *new_node;
    int value;

    value = line_number;
    if (value == 0)
    {
        fprintf(stderr, "L %d: missing argument for push\n", line_number);
        exit(EXIT_FAILURE);
    }

    /*Convert the value to a an integer*/
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        perror("Error: malloc failed");
        exit(1);
    }
    
    new_node->n = line_number;
    new_node->next = NULL;
    new_node->prev = *stack;

    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *temp = *stack;

    while (temp != NULL)
    {
        printf("%d\n", temp->n);
        temp = temp->prev;
    }
    /*Supress the arguments*/
    (void)stack;
    (void)line_number;
}
