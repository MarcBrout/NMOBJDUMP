/*
** commons.h for nm in /rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:38:47 2017 brout_m
** Last update Fri Feb 24 10:21:28 2017 marc brout
*/

#ifndef COMMONS_H
# define COMMONS_H

# include <stddef.h>
# include <stdbool.h>
# include <elf.h>

typedef struct		s_node
{
  char			*symbol;
  uint32_t		type;
  uintptr_t		addr;
  struct s_node		*next;
}			t_node;

enum e_symcmp
{
    A = 0,
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

typedef char (*symCmp32)(Elf32_Ehdr *, Elf32_Sym *);
typedef char (*symCmp64)(Elf64_Ehdr *, Elf64_Sym *);

void sortListAsc(t_node **root);
void freeList(t_node **root);
size_t fileSize(char const *prog, char const *filename);
void *createMmap(char const *prog, char const *filename, size_t *size);
bool isArchitecture64(Elf32_Ehdr const * const elf, bool set);
bool isElfValid(const char * const prog,
		Elf32_Ehdr const * const elf,
		const char *filename,
		bool nm);
bool isArchive(char *ar);
int checkSize64(Elf64_Ehdr *elf, char const *prog,
		char const *filename,
		size_t size);
int checkSize32(Elf32_Ehdr *elf, char const *prog,
		char const *filename,
		size_t size);

#endif /* !COMMONS_H */
