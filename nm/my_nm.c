/*
** my_nm.c for in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:54:21 2017 brout_m
** Last update Fri Feb 17 16:19:01 2017 brout_m
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

bool            processArchive(void *data, const char *file)
{
  size_t	size;
  struct ar_hdr *ar;
  void          *elf;

  ar = data + SARMAG;
  size = fileSize(file);
  while ((void *)ar < (data + size))
    {
      elf = (void*)ar + sizeof(*ar);
      if (!isElfValid(elf, file))
	return (false);
      if (isArchitecture64(elf, true))
	{
	  if (processElf64(elf, file, true))
	    return (false);
        }
      else if (processElf32(elf, file, true))
	return (false);
      ar = ((void*)ar + strtol(ar->ar_size, NULL, 0));
    }
  return (true);
}

int		parseFile(const char *file, bool mult)
{
  void		*data;

  if ((data = createMmap(file)) == (void*)-1)
    return (1);
  if (isArchive(data))
    {
      if (processArchive(data, file))
	return (84);
      return (0);
    }
  else
    {
      if (!isElfValid(data, file))
	return (2);
      if (isArchitecture64(data, true))
	{
	  if (processElf64(data, file, mult))
	    return (false);
        }
      else if (processElf32(data, file, mult))
	return (false);
    }
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
