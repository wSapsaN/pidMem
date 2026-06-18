#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

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

  while ((entry = readdir(dir)) != NULL) // read catalog.
  {
    if (is_numeric(entry->d_name)) printf("%s\n", entry->d_name); // check simbol on numeric.
  }

  closedir(dir);

  return 0;
}
