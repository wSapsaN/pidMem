#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

#define RPATH "/proc"

int is_numeric(const char* str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i])) return 0;
  }

  return 1;
}


int main(void)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir(RPATH);
  if (dir == NULL)
  {
    perror("Failed open /proc");
    return -1;
  }

  while ((entry = readdir(dir)) != NULL)
  {
    if (is_numeric(entry->d_name)) printf("%s\n", entry->d_name);
  }

  closedir(dir);

  return 0;
}
