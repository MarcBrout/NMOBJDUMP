/*
** elfparser32.h brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:38:01 2017 brout_m
** Last update Tue Feb 14 21:38:11 2017 brout_m
*/

#ifndef ELFPARSER32_H_
# define ELFPARSER32_H_

# include <elf.h>
# include <stdbool.h>

typedef struct      s_types
{
    unsigned char   bind;
    unsigned char   type;
    char            value;
}                   t_types;

typedef struct      s_node
{
    char            *symbol;
    uint32_t        type;
    uintptr_t       addr;
    struct s_node   *next;
}                   t_node;

Elf32_Shdr *elf32_sheader(Elf32_Ehdr *elf);
Elf32_Shdr *elf32_section(Elf32_Ehdr *elf, int pos);
char *elf32_strtable(Elf32_Ehdr *elf);
char *elf32_name(Elf32_Ehdr *elf, int off);


#endif /* !ELFPARSER32_H_ */