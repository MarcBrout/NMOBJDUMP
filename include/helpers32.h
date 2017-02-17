/*
** helpers32.h in /rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:40:15 2017 brout_m
** Last update Fri Feb 17 15:40:29 2017 brout_m
*/

#ifndef HELPERS32_H
# define HELPERS32_H

# include <elf.h>
# include <stdbool.h>

Elf32_Shdr *elf32_sheader(Elf32_Ehdr *elf);
Elf32_Shdr *elf32_section(Elf32_Ehdr *elf, int pos);
char *elf32_strtable(Elf32_Ehdr *elf);
char *elf32_name(Elf32_Ehdr *elf, int off);

#endif /* !PSU_2016_NMOBJDUMP_HELPERS_H */
