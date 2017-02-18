/*
** dump64.h for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 17:44:36 2017 brout_m
** Last update Sat Feb 18 17:45:28 2017 brout_m
*/

#ifndef DUMP64_H
# define DUMP64_H

# include <stdint.h>
# include <stdbool.h>
# include <elf.h>

typedef struct	s_dump
{
  char		*sh_name;
  void		*data;
  uint64_t	size;
  uint64_t	off;
  struct s_dump *next;
}		t_dump;

typedef struct	s_head64
{
  Elf64_Half	key;
  const char	*value;
}               t_head64;

bool nodeifyElf64(Elf64_Ehdr *, t_dump **, unsigned int *);
void dumpList64(t_dump const *);
void dumpHeader64(Elf64_Ehdr *, const char *, unsigned int);

#endif /* !DUMP_H */
