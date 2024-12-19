#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error_args(char *name)
{
    fprintf(stderr, "\n>->->->->\n");
    fprintf(stderr, "[ERROR - Arguments] Try:\n");
    fprintf(stderr, "%s [-v] -t <test> -x <sequential> -y <parallel>\n", name);
    fprintf(stderr, "<-<-<-<-<\n\n");
    exit(1);
}

void error_file()
{
    fprintf(stderr, "\n>->->->->\n");
    fprintf(stderr, "[ERROR - File] Could not use file\n");
    fprintf(stderr, "<-<-<-<-<\n\n");
    exit(1);
}