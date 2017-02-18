/*
** dump32.h for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 17:44:36 2017 brout_m
** Last update Sat Feb 18 17:45:28 2017 brout_m
*/

#ifndef DUMP32_H
# define DUMP32_H

# include <stdint.h>
# include <stdbool.h>
# include <elf.h>
#include "dump64.h"

typedef struct	s_head32
{
  Elf32_Half	key;
  const char	*value;
}               t_head32;

bool nodeifyElf32(Elf32_Ehdr *, t_dump **, unsigned int *);
void dumpList32(t_dump const *);
void dumpHeader32(Elf32_Ehdr *, const char *, unsigned int);

#endif /* !DUMP_H */
