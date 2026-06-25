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
    if (!isdigit(str[i])) return 0; // If the symbol is not a number, then 0 is returned.
  }

  return 1;
}

char* getPath(const char *pid)
{
  /* 
    A function that returns the path to the process status file containing the necessary data for analysis.
    This function may not be as efficient as it uses the heap in a loop.
  */

  char *status = "status";
  unsigned int totalsize = strlen(pid) + strlen(RPATH) + strlen(status) + 3;
  char* path = malloc(totalsize);
  if (path == NULL)
  {
    perror("Bad memory\n");
    exit(-1); // Fatal Error
  }

  // we combine words into a path
  snprintf(path, totalsize, "%s/%s/%s", RPATH, pid, status);

  return path;

}

int main(void)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir(RPATH); // Browsing the catalog.
  if (dir == NULL) // If file cannot opened, then error is returned.
  {
    perror("Failed open /proc");
    return -1;
  }
  
  // the structure that will contain the winner of the memory eating contest
  struct PIDdata data = {
    .serviceName = "None",
    .memory      = 0
  };

  char* path;
  while ((entry = readdir(dir)) != NULL) // read catalog.
  {
    if (is_numeric(entry->d_name)) { // check simbol on numeric.
      
      path = getPath(entry->d_name);

      // we pass the structure object to the deep analysis function
      deep(&data, path);

      free(path);
    }
  }

  // Output result.
  printf("%sVmRSS:\t%d kB\n", data.serviceName, data.memory);

  closedir(dir);

  return 0;
}
