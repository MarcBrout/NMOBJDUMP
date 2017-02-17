/*
** helpers64.h for nm in /rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:40:51 2017 brout_m
** Last update Fri Feb 17 15:41:00 2017 brout_m
*/

#ifndef HELPERS64_H
# define HELPERS64_H

# include <elf.h>
# include <stdbool.h>

Elf64_Shdr *elf64_sheader(Elf64_Ehdr *elf);
Elf64_Shdr *elf64_section(Elf64_Ehdr *elf, int pos);
char *elf64_strtable(Elf64_Ehdr *elf);
char *elf64_name(Elf64_Ehdr *elf, int off);

#endif /* !PSU_2016_NMOBJDUMP_HELPERS_H */
