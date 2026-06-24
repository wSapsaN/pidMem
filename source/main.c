#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "deepMem.h"

#define RPATH "/proc"


int is_numeric(const char* str)
{
  /* Function for cheking only numeric */

  for (int i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i])) return 0; // If the symbol is not a number, then 1 is returned.
  }

  return 1;
}

char* getPath(const char *pid)
{
  char *status = "status";
  unsigned int totalsize = strlen(pid) + strlen(RPATH) + strlen(status) + 3;
  char* path = malloc(totalsize);
  if (path == NULL)
  {
    perror("Bad memory\n");
  }

  snprintf(path, totalsize, "%s/%s/%s", RPATH, pid, status);

  return path;

}

int main(void)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir(RPATH);
  if (dir == NULL) // If file cannot opened, then error is returned.
  {
    perror("Failed open /proc");
    return -1;
  }
  
  struct PIDdata data = {
    .serviceName = "None\0", 
    .memory      = 0
  };

  char* path;
  while ((entry = readdir(dir)) != NULL) // read catalog.
  {
    if (is_numeric(entry->d_name)) { // check simbol on numeric.
      
      path = getPath(entry->d_name);

      deep(&data, path);

      free(path);
    }
  }

  printf("%sVmRSS:\t%d\n", data.serviceName, data.memory);

  closedir(dir);

  return 0;
}
