/*
** my_objdump.c for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 18:35:45 2017 brout_m
** Last update Mon Feb 20 09:23:44 2017 marc brout
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "flags.h"
#include "commons.h"
#include "dump64.h"
#include "dump32.h"

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

bool		processElf64(void *data, const char *file)
{
  t_dump	*root;
  unsigned int	flags;

  root = NULL;
  flags = BFD_NO_FLAGS;
  if (!nodeifyElf64(data, &root, &flags))
    return (84);
  dumpHeader64(data, file, flags);
  dumpList64(root);
  freeDumpList(root);
  return (0);
}

bool		processElf32(void *data, const char *file)
{
  t_dump	*root;
  unsigned int	flags;

  root = NULL;
  flags = BFD_NO_FLAGS;
  if (!nodeifyElf32(data, &root, &flags))
    return (84);
  dumpHeader32(data, file, flags);
  dumpList32(root);
  freeDumpList(root);
  return (0);
}

int		parseFile(const char *file)
{
  void		*data;

  if ((data = createMmap(file)) == (void*)-1)
    return (1);
  if (!isElfValid(data, file))
    return (2);
  if (isArchitecture64(data, true))
    {
      if (processElf64(data, file))
	return (false);
    }
  else if (processElf32(data, file))
    return (false);
  return (0);
}

int		main(int ac, char **av)
{
  int		i;

  if (ac < 2)
    {
      if (parseFile("a.out"))
	return (84);
      return (0);
    }
  i = 1;
  while (i < ac)
    {
      if (parseFile(av[i]))
	return (84);
      ++i;
    }
  return (0);
}
