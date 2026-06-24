#include "deepMem.h"

int vmrss(const char *line)
{
  /*
    Function to search for a string and return the memory
    consumption as an integer value in decimal notation.
  */

  char sizemem[LINE_SIZE] = {0}; // contains the symbolic number of occupied memory from the file.
  char tmp[LINE_SIZE / 2] = {0}; // contains the characters of the search string for comparison.

  unsigned int i        = 0; // Index for line.
  unsigned int flagW    = 0; // A flag after which tells when to collect numerical data.
  unsigned int indexTMP = 0; // Index counter for temporary character arrays.
  
  // read the line.
  while (line[i] != '\0')
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

    // copy value on line.
    tmp[indexTMP] = line[i];
    indexTMP++;
    tmp[indexTMP] = '\0';

    if (strcmp(tmp, "VmRSS") == 0) 
    {
      flagW = 1;
      indexTMP = 0;
      i++; // here is the repeat increment for index i to jump over ":".
    }

    i++;
  }

  // Here we convert the memory consumption value 
  // which was a character data type into an integer type.
  char *endptr;
  errno = 0;

  int num = strtol(sizemem, &endptr, 10);

  return num;
}

void deep(struct PIDdata* data, char* path)
{
  /*
    The function's task is to parse the process status data 
    and fill it into the structure.
  */

  char tmpName[LINE_SIZE] = {0}; // Name proccess.
  char buffer[LINE_SIZE];        // Buffer for read files.
  unsigned int flagName = 0;     // The flag is needed to read and write the first line to the tmpName variable.
  // This is necessary to avoid re-reading the file each time.

  FILE* fp = fopen(path, "r");
  if (fp)
  {
    while ((fgets(buffer, sizeof(buffer), fp)) != NULL)
    {
      if (!flagName)
      {
        flagName = 1;
        strncpy(tmpName, buffer, LINE_SIZE);

        continue;
      }
      
      // We get the value the application consumed from memory.
      // If the value is greater than the previous one, the data in
      // the structure is overwritten with more current data.
      int mem = vmrss(buffer);
      if (mem > data->memory)
      {
        data->memory = mem;
        strncpy(data->serviceName, tmpName, sizeof(data->serviceName));
      }
    }
    
    fclose(fp);
  }

}
