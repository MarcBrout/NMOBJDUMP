/*
** elfParser.h in /rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 13:23:53 2017 brout_m
** Last update Fri Feb 17 15:39:54 2017 brout_m
*/

#ifndef ELFPARSER32_H_
# define ELFPARSER32_H_

# include <elf.h>
# include <stdbool.h>
# include "commons.h"

bool parseElf32(void *data, t_node **root, const char *filename);

char compareA32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareB32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareC32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareD32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareG32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char comparei32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareI32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareN32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareP32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareR32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareT32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareu32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareU32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareV32(Elf32_Ehdr *elf, Elf32_Sym *symbol);
char compareW32(Elf32_Ehdr *elf, Elf32_Sym *symbol);

#endif /* !ELFPARSER_H_ */
