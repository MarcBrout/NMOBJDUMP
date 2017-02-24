/*
** my_nm.c for in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:54:21 2017 brout_m
** Last update Fri Feb 24 17:20:23 2017 brout_m
*/

#include <ar.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "nodes32.h"
#include "nodes64.h"
#include "elfParser64.h"
#include "elfParser32.h"

bool		processElf32(void *data, const char *file, bool mult)
{
  t_node	*root;

  root = NULL;
  if (!parseElf32(data, &root, file))
      return (0);
  if (mult)
    printf("\n%s:\n", file);
  sortListAsc(&root);
  printList32(root);
  freeList(&root);
  return (0);
}

bool		processElf64(void *data, const char *file, bool mult)
{
  t_node	*root;

  root = NULL;
  if (!parseElf64(data, &root, file))
    return (84);
  if (mult)
    printf("\n%s:\n", file);
  sortListAsc(&root);
  printList64(root);
  freeList(&root);
  return (0);
}

int		parseFile(const char * const prog,
			  const char *file, bool mult)
{
  void		*data;
  size_t	size;

  if ((data = createMmap(prog, file, &size)) == (void*)-1)
    return (1);
  if (!isElfValid(prog, data, file, true))
    return (2);
  if (isArchitecture64(data, true))
    {
      if (checkSectionHeaders64(data, prog, file, size) ||
	  checkSize64(data, prog, file, size) ||
	  processElf64(data, file, mult))
	return (1);
    }
  else if (checkSectionHeaders32(data, prog, file, size) ||
	   checkSize32(data, prog, file, size) ||
	   processElf32(data, file, mult))
    return (1);
  return (0);
}

int		main(int ac, char **av)
{
  int		i;
  int		count;

  if (ac < 2)
    {
      if (parseFile(av[0], "a.out", false))
	return (1);
      return (0);
    }
  i = 1;
  count = 0;
  while (i < ac)
    {
      if (parseFile(av[0], av[i], ac > 2))
	++count;
      ++i;
    }
  return (count);
}
