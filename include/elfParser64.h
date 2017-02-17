/*
** elfParser.h in /rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 13:23:53 2017 brout_m
** Last update Fri Feb 17 15:40:09 2017 brout_m
*/

#ifndef ELFPARSER64_H_
# define ELFPARSER64_H_

# include <elf.h>
# include <stdbool.h>
# include "commons.h"

bool parseElf64(void *data, t_node **root, const char *filename);

char compareA64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareB64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareC64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareD64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareG64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char comparei64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareI64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareN64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareP64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareR64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareT64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareu64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareU64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareV64(Elf64_Ehdr *elf, Elf64_Sym *symbol);
char compareW64(Elf64_Ehdr *elf, Elf64_Sym *symbol);

#endif /* !ELFPARSER_H_ */
