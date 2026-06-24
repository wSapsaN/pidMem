#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define SERVICE_SIZE 200
#define LINE_SIZE    256

// A structure that stores process data.
struct PIDdata
{
  char serviceName[SERVICE_SIZE];
  unsigned memory;
};

// Deep analysis function.
void deep(struct PIDdata*, char*);
