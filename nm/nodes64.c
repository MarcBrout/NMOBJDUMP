/*
** nodes64.c for  in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:57:12 2017 brout_m
** Last update Fri Feb 17 16:33:40 2017 brout_m
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons.h"

void		printList64(t_node const *root)
{
  t_node  const *cur;

  cur = root;
  while (cur)
    {
      if (cur->type == 'U' || cur->type == 'w')
	printf("                 %c %s\n", cur->type, cur->symbol);
      else
        {
	  printf("%016llx %c %s\n",
		 (long long)cur->addr, cur->type, cur->symbol);
        }
      cur = cur->next;
    }
}

bool		addNode64(t_node **root,
			  char const *name,
			  Elf64_Sym const * const sym,
			  uint32_t type)
{
  t_node	*node;
  t_node	*cur;

  if (!(node = malloc(sizeof(*node))))
    return (false);
  if (name)
    {
      if (!(node->symbol = strdup(name)))
	return (false);
    }
  else
    node->symbol = NULL;
  node->addr = sym->st_value;
  node->type = type;
  node->next = NULL;
  if (!*root)
    *root = node;
  else
    {
      cur = *root;
      while (cur->next)
	cur = cur->next;
      cur->next = node;
    }
  return (true);
}
