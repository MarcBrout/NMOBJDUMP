/*
** elfParser.h for nmobjdump in /home/brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 13:23:53 2017 brout_m
** Last update Mon Feb 13 16:29:06 2017 brout_m
*/

#ifndef ELFPARSER_H_
# define ELFPARSER_H_

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

Elf64_Shdr *elf64_sheader(Elf64_Ehdr *elf);
Elf64_Shdr *elf64_section(Elf64_Ehdr *elf, int pos);
char *elf64_strtable(Elf64_Ehdr *elf);
char *elf64_name(Elf64_Ehdr *elf, int off);
uint32_t  getType64(void *data, Elf64_Sym *symbole);


enum e_symcmp
{
    A   = 0,
    B,
    C,
    D,
    G,
    i,
    I,
    N,
    P,
    R,
    T,
    u,
    U,
    V,
    W,
    END
};

typedef char (*symCmp)(Elf64_Ehdr *, Elf64_Sym *);

extern symCmp  cmptab64[];

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