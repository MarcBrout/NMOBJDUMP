/*
** dumpList64.c for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 17:30:27 2017 brout_m
** Last update Fri Feb 24 17:23:15 2017 brout_m
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "helpers64.h"
#include "dump64.h"

static void spaceComble(size_t cur, size_t target, bool mod)
{
  while (cur < target)
    {
      if (mod)
	printf("  ");
      else
	printf(" ");
      if (mod && !(cur % 4))
	printf(" ");
      ++cur;
    }
}

static size_t		dumpHexa(void *data,
				 size_t pos,
				 uint64_t max)
{
  size_t		i;
  unsigned char		*val;

  i = 0;
  val = data + pos;
  while (i < 16 && pos + i < max)
    {
      if (!(i % 4))
	printf(" ");
      printf("%02x", val[i]);
      ++i;
    }
  spaceComble(i, 16, true);
  return (i);
}

static size_t		dumpChar(void *data,
				 size_t pos,
				 uint64_t max)
{
  size_t		i;
  unsigned char		*val;

  i = 0;
  val = data + pos;
  printf("  ");
  while (i < 16 && pos + i < max)
    {
      if (isprint(val[i]))
	printf("%c", val[i]);
      else
	printf(".");
      ++i;
    }
  spaceComble(i, 16, false);
  printf("\n");
  return (i);
}

static void	dumpData(t_dump const *cur)
{
  char	       snum[100];
  void		*data;
  uint64_t	off;
  int		digit;
  size_t	i;

  i = 0;
  data = cur->data;
  off = cur->off;
  sprintf(snum, "%llx", (long long)(off + cur->size));
  digit = strlen(snum);
  while (i < cur->size)
    {
      printf(" %0*llx", digit > 4 ? digit : 4, (long long)off);
      dumpHexa(data, i, cur->size);
      i += dumpChar(data, i, cur->size);
      off += 16;
    }
}

void		dumpList64(t_dump const *root)
{
  t_dump const	*cur;

  cur = root;
  while (cur)
    {
      printf("Contents of section %s:\n", cur->sh_name);
      dumpData(cur);
      cur = cur->next;
    }
}
