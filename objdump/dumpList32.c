/*
** dumpList32.c for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 17:30:27 2017 brout_m
** Last update Sat Feb 18 18:48:26 2017 brout_m
*/

#include <stdio.h>
#include <ctype.h>
#include "helpers32.h"
#include "dump32.h"

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
  void		*data;
  uint64_t	off;
  size_t	i;

  i = 0;
  data = cur->data;
  off = cur->off;
  while (i < cur->size)
    {
      printf(" %04llx", (long long)off);
      dumpHexa(data, i, cur->size);
      i += dumpChar(data, i, cur->size);
      off += 16;
    }
}

void		dumpList32(t_dump const *root)
{
  t_dump const	*cur;

  cur = root;
  while (cur)
    {
      printf("Contents of section %s_:\n", cur->sh_name);
      dumpData(cur);
      cur = cur->next;
    }
}
