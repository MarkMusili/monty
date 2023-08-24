#include "monty.h"

stack_t *stack = NULL;
instruction_t opcodes[] =
{
    {"push", push},
    {"pall", pall},
    {NULL, NULL}
};

int main(int argc, char *argv[])
{
    int fd, i;
    char line[100];
    char command[10];
    int value;
    
    /*Check number of arguments passed*/
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*Open the  .m file*/
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error: Can't open file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), stdin))
    {
        
        if (sscanf(line, "%s %d", command, &value) == 2)
        {
            for (i = 0; opcodes[i].opcode != NULL; i++)
            {
                if (strcmp(command, opcodes[i].opcode) == 0)
                {
                    opcodes[i].f(&stack, value);
                }
                else if (opcodes[i].opcode == NULL)
                {
                    fprintf(stderr, "L %d: unknown instruction %s\n", value, command);
                    close(fd);
                    exit(EXIT_FAILURE);
                }
            }
        }
        
    }
    close(fd);
    return (0);
}