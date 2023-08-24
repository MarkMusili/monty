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
    int i;
    FILE *fd;
    char *line;
    char command[5];
    int value;
    
    /*Check number of arguments passed*/
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*Open the  .m file*/
    fd = fopen(argv[1], O_RDONLY);
    if (fd ==  NULL) {
        perror("Error: Can't open file");
        exit(EXIT_FAILURE);
    }

    line = malloc(sizeof(char) * BUFFER_SIZE);
    if (line == NULL)
    {
        perror("Error: malloc failed,");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fd) != NULL)
    {    
        if (sscanf(line, "%s %d$", command, &value) == 2)
        {
            for (i = 0; opcodes[i].opcode != NULL; i++)
            {
                if (strcmp(command, opcodes[i].opcode) == 0)
                {
                    opcodes[i].f(&stack, value);
                    free(line);
                    break;
                }
            }
            if (opcodes[i].opcode == NULL)
            {
                fprintf(stderr, "L %d: unknown instruction %s\n", value, command);
                fclose(fd);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    free(line);
    fclose(fd);
    return (0);
}