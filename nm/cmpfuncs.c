/*
** cmpfuncs.c for nm in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:42:06 2017 brout_m
** Last update Fri Feb 17 15:43:55 2017 brout_m
*/

#include <ctype.h>
#include <stdlib.h>
#include "commons.h"

static int	mystrcmpNoCase(char const *str1, char const *str2)
{
  int		pos1;
  int		pos2;

  pos1 = pos2 = 0;
  while (str1[pos1]  && str2[pos2])
    {
      while (str1[pos1] && !isalnum(str1[pos1]))
	++pos1;
      while (str2[pos2] && !isalnum(str2[pos2]))
	++pos2;
      if (tolower(str1[pos1]) != tolower(str2[pos2]))
	break;
      ++pos1;
      ++pos2;
    }
  return (tolower(str1[pos1]) - tolower(str2[pos2]));
}

static int	mystrcmpCase(char const *str1, char const *str2)
{
  int		pos1;
  int		pos2;

  pos1 = pos2 = 0;
  while (str1[pos1]  && str2[pos2])
    {
      while (str1[pos1] && !isalnum(str1[pos1]))
	++pos1;
      while (str2[pos2] && !isalnum(str2[pos2]))
	++pos2;
      if (str1[pos1] != str2[pos2])
	break;
      ++pos1;
      ++pos2;
    }
  return (str2[pos2] - str1[pos1]);
}

static void	swapNodes(t_node *cur, t_node *next)
{
  t_node	tmp;

  tmp.symbol = cur->symbol;
  tmp.addr = cur->addr;
  tmp.type = cur->type;
  cur->symbol = next->symbol;
  cur->type = next->type;
  cur->addr = next->addr;
  next->symbol = tmp.symbol;
  next->addr = tmp.addr;
  next->type = tmp.type;
}

void		freeList(t_node **root)
{
  t_node	*cur;
  t_node	*tmp;

  cur = *root;
  while (cur)
    {
      tmp = cur->next;
        if (cur->symbol)
            free(cur->symbol);
      free(cur);
      cur = tmp;
    }
  *root = NULL;
}

void		sortListAsc(t_node **root)
{
  bool		swap;
  int		ret;
  t_node	*cur;

  swap = true;
  while (swap)
    {
      cur = *root;
      swap = false;
      while (cur->next)
        {
	  ret = mystrcmpNoCase(cur->symbol, cur->next->symbol);
	  if (!ret)
	    ret = mystrcmpCase(cur->symbol, cur->next->symbol);
	  if (ret > 0 ||
	      (!ret && cur->addr > cur->next->addr) ||
	      (!ret && cur->addr <= cur->next->addr &&
	       tolower((char)cur->type) > tolower((char)cur->next->type)))
            {
	      swapNodes(cur, cur->next);
	      swap = true;
            }
	  cur = cur->next;
        }
    }
}
