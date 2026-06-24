#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define SERVICE_SIZE 200
#define LINE_SIZE    256

struct PIDdata
{
  char serviceName[SERVICE_SIZE];
  unsigned memory;
};

void deep(struct PIDdata*, char*);
