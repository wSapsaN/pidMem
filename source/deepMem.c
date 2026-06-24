#include "deepMem.h"

int vmrss(const char *line)
{
  char sizemem[LINE_SIZE] = {0};
  char tmp[LINE_SIZE / 2] = {0};

  unsigned int i        = 0;
  unsigned int flagW    = 0;
  unsigned int indexTMP = 0;
  
  while (((line[i]) != '\0') || (i <= (LINE_SIZE/2)))
  {
    if (line[0] != 'V') return 0;
    
    if (flagW)
    {
      if (!isspace(line[i]))
      {
        if (line[i] == 'k') break;

        sizemem[indexTMP] = line[i];
        i++;
        indexTMP++;
      } else i++;

      continue;
    }

    // copy name
    tmp[indexTMP] = line[i];
    indexTMP++;

    if (strcmp(tmp, "VmRSS") == 0) 
    {
      flagW = 1; // if line == name. Then flag = setp 2
      indexTMP = 0;
      i++;
    }

    i++;
  }

  char *endptr;
  errno = 0;

  int num = strtol(sizemem, &endptr, 10);

  return num;
}

void deep(struct PIDdata* data, char* path)
{
  char tmpName[LINE_SIZE] = {0};
  char buffer[LINE_SIZE];
  unsigned int flagName = 0;

  FILE* fp = fopen(path, "r");
  if (fp)
  {
    while ((fgets(buffer, 256, fp)) != NULL)
    {
      if (!flagName)
      {
        flagName = 1;
        strncpy(tmpName, buffer, LINE_SIZE);

        continue;
      }
      
      int mem = vmrss(buffer);
      if (mem > data->memory)
      {
        data->memory = mem;
        strcpy(data->serviceName, tmpName);
      }
    }
  }

  fclose(fp);
}
