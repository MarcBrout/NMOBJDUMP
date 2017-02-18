#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "flags.h"
#include "commons.h"
#include "dump64.h"

void		freeDumpList(t_dump *root)
{
  t_dump	*freed;
  t_dump	*tmp;

    freed = root;
    while (freed)
    {
        tmp = freed->next;
        free(freed);
        freed = tmp;
    }
}

bool		processElf64(void *data, const char *file, bool mult)
{
    t_dump	*root;
    unsigned int flags;

    root = NULL;
    flags = BFD_NO_FLAGS;
    if (!nodeifyElf64(data, &root, &flags))
        return (84);
    if (mult)
        printf("\n%s:\n", file);
        dumpHeader64(data, file, flags);
        dumpList64(root);
    freeDumpList(root);
    return (0);
}

int		parseFile(const char *file, bool mult)
{
  void		*data;

  if ((data = createMmap(file)) == (void*)-1)
    return (1);
  if (!isElfValid(data, file))
    return (2);
  if (isArchitecture64(data, true))
    {
      if (processElf64(data, file, mult))
	return (false);
    }
/*        else if (processElf32(data, file, mult))
            return (false); */
  return (0);
}

int		main(int ac, char **av)
{
  int		i;

  if (ac < 2)
    {
      if (parseFile("a.out", false))
	return (84);
      return (0);
    }
  i = 1;
  while (i < ac)
    {
      if (parseFile(av[i], ac > 2))
	return (84);
        ++i;
    }
  return (0);
}
