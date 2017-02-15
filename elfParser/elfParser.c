/*
** elfParser.c for nmobjdump in /home/brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 11:00:58 2017 brout_m
** Last update Tue Feb 14 15:33:41 2017 brout_m
*/

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <ctype.h>
#include "elfParser.h"

inline Elf64_Shdr *elf64_sheader(Elf64_Ehdr *elf)
{
    return ((Elf64_Shdr *)((void *)elf + elf->e_shoff));
}

inline Elf64_Shdr *elf64_section(Elf64_Ehdr *elf, int pos)
{
    return (&elf64_sheader(elf)[pos]);
}

inline Elf32_Shdr *elf32_sheader(Elf32_Ehdr *elf)
{
    return ((Elf32_Shdr *)((void *)elf + elf->e_shoff));
}

inline Elf32_Shdr *elf32_section(Elf32_Ehdr *elf, int pos)
{
    return (&elf32_sheader(elf)[pos]);
}

inline char *elf64_strtable(Elf64_Ehdr *elf)
{
    if (elf->e_shstrndx == SHN_UNDEF)
        return (NULL);
    return ((char *)((void*)elf + elf64_section(elf, elf->e_shstrndx)->sh_offset));
}

inline      char *elf64_name(Elf64_Ehdr *elf, int off)
{
    char    *strtab;

    strtab = elf64_strtable(elf);
    if (!strtab)
        return  (NULL);
    return (strtab + off);
}

inline char *elf32_strtable(Elf32_Ehdr *elf)
{
    if (elf->e_shstrndx == SHN_UNDEF)
        return (NULL);
    return ((char *)((void*)elf + elf32_section(elf, elf->e_shstrndx)->sh_offset));
}

inline      char *elf32_name(Elf32_Ehdr *elf, int off)
{
    char    *strtab;

    strtab = elf32_strtable(elf);
    if (!strtab)
        return  (NULL);
    return (strtab + off);
}


static size_t	fileSize(char const *filename)
{
  struct stat	file;

  if (stat(filename, &file) == -1)
    {
      fprintf(stderr, "my_nm: '%s': no such file\n", filename);
      return (0);
    }
  if (file.st_size < (int)sizeof(Elf32_Ehdr))
    {
      fprintf(stderr, "my_nm: '%s': Unknown file format\n", filename);
      return (0);
    }
  return ((size_t)file.st_size);
}

bool		isArchitecture64(Elf32_Ehdr *elf, bool set)
{
  static bool	architecture = false;

  if (set)
    architecture = (elf->e_ident[EI_CLASS] == ELFCLASS64);
  return (architecture);
}

bool		isElfValid(Elf32_Ehdr *elf, const char *filename)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
      elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
      elf->e_ident[EI_CLASS] == ELFCLASSNONE ||
      elf->e_ident[EI_VERSION] == EV_NONE)
    {
      fprintf(stderr, "my_nm: '%s': Unknown file format\n", filename);
      return (false);
    }
  return (true);
}

void		*createMmap(char const *filename)
{
  int		fd;
  size_t	size;
  void		*data;

  size = fileSize(filename);
  if (!size)
    return ((void*)-1);
  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return ((void*)-1);
  data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  close(fd);
  return (data);
}

bool        addNode64(t_node **root, char const *name, Elf64_Sym *sym, uint32_t type)
{
  t_node    *node;
    t_node  *cur;

  if (!(node = malloc(sizeof(*node))))
    return (false);
  if (name)
    {
      if (!(node->symbol = strdup(name)))
	return (false);
    }
  else
    node->symbol = NULL;
  node->addr = sym->st_value;
  node->type = type;
  node->next = NULL;
  if (!*root)
    *root = node;
  else
    {
        cur = *root;
        while (cur->next)
            cur = cur->next;
      cur->next = node;
    }
  return (true);
}

bool        addNode32(t_node **root, char const *name, Elf32_Sym *sym)
{
  t_node    *node;

  if (!(node = malloc(sizeof(*node))))
    return (false);
  if (name)
    {
      if (!(node->symbol = strdup(name)))
	return (false);
    }
  else
    node->symbol = NULL;
  node->addr = sym->st_value;
  node->type =sym->st_info;
  node->next = NULL;
  if (!*root)
    *root = node;
  else
    {
      node->next = *root;
      *root = node;
    }
  return (true);
}

bool        notEnd(const char *str, const char *end)
{
  size_t    pos1;
  size_t    pos2;

  pos1 = strlen(str) - 1;
  pos2 = strlen(end) - 1;
  while (pos1 > 0 && pos2 > 0 && str[pos1] == end[pos2])
    {
      --pos1;
      --pos2;
    }
  return (str[pos1] - end[pos2]);
}


void	*getSectionData64(void *elf,
                          Elf64_Shdr const *shdr,
                          const char *section,
                          int nb)
{
    int   i;
    char  *stringTable;

    i = 0;
    stringTable = (char*)(elf + shdr[((Elf64_Ehdr*)elf)->e_shstrndx].sh_offset);
    while (i < nb)
    {
        if (!strcmp(section, &stringTable[shdr[i].sh_name]))
            return (elf + shdr[i].sh_offset);
        ++i;
    }
    return (NULL);
}

void	*getSectionData32(void *elf,
                          Elf32_Shdr const *shdr,
                          const char *section,
                          int nb)
{
    int   i;
    char  *stringTable;

    i = 0;
    stringTable = (char*)(elf + shdr[((Elf32_Ehdr*)elf)->e_shstrndx].sh_offset);
    while (i < nb)
    {
        if (!strcmp(section, &stringTable[shdr[i].sh_name]))
            return (elf + shdr[i].sh_offset);
        ++i;
    }
    return (NULL);
}

symCmp cmptab64[END] = {
        &compareT64,
        &compareA64,
        &compareB64,
        &compareC64,
        &compareW64,
        &compareD64,
        &compareG64,
        &compareN64,
        &compareP64,
        &compareR64,
        &compareV64,
        &compareU64,
        &compareu64,
        &comparei64,
        &compareI64
};

uint32_t    getType64(void *data, Elf64_Sym *symbole)
{
    char    type;
    int     i;

    i = 0;
    type = 0;
    while (i < END)
    {
        type = cmptab64[i](data, symbole);
        if (type)
            break;
        ++i;
    }
    if (!type)
        type = '?';
    return ((uint32_t)type);
}

bool		addSymbols64(char const *stringTable,
                         void *data,
			            Elf64_Shdr *symboleSection,
			            t_node **root)
{
  int		i;
    uint32_t type;
    int     nb;
    Elf64_Sym *symboleArray;

  i = 0;
    nb = (int)symboleSection->sh_size / (int)symboleSection->sh_entsize;
    symboleArray = data + symboleSection->sh_offset;
  while (i < nb)
    {
      if (symboleArray[i].st_name > 0 &&
              ELF64_ST_TYPE(symboleArray[i].st_info) != STT_FILE)
      {
          type = getType64(data, &symboleArray[i]);
        if (!addNode64(root,
		       &stringTable[symboleArray[i].st_name],
		       &symboleArray[i], type))
          return (false);
      }
      ++i;
    }
  return (true);
}

bool		addSymbols32(char const *stringTable,
			     Elf32_Sym *symboleSection,
			     int nb,
			     t_node **root)
{
  int		i;

  i = 0;
  while (i < nb)
    {
      if (symboleSection[i].st_name > 0 &&
              ELF32_ST_TYPE(symboleSection[i].st_info) != STT_FILE)
	{
	  if (!addNode32(root,
			 &stringTable[symboleSection[i].st_name],
			 &symboleSection[i]))
	    return (false);
	}
      ++i;
    }
  return (true);
}

void	*getSection64(Elf64_Shdr *shdr, uint32_t type, int nb)
{
  int	i;

  i = 0;
  while (i < nb)
    {
      if (shdr[i].sh_type == type)
	return (&shdr[i]);
      ++i;
    }
  return (NULL);
}

void	*getSection32(Elf32_Shdr *shdr, uint32_t type, int nb)
{
  int	i;

  i = 0;
  while (i < nb)
    {
      if (shdr[i].sh_type == type)
	return (&shdr[i]);
      ++i;
    }
  return (NULL);
}

bool		parseElf64(void *data, t_node **root)
{
  char		*strtab;
  Elf64_Shdr	*symboleSection;
  Elf64_Ehdr	*elf64;

  elf64 = data;
  strtab = getSectionData64(data, elf64_sheader(elf64), ".strtab", elf64->e_shnum);
  symboleSection = getSection64(elf64_sheader(elf64), SHT_SYMTAB, elf64->e_shnum);
  addSymbols64(strtab, data, symboleSection, root);
  return (true);
}

bool		parseElf32(void *data, t_node **root)
{
  char		*strtab;
  Elf32_Shdr	*symboleSection;
  Elf32_Ehdr	*elf32;

  elf32 = data;
  strtab = getSectionData32(data, elf32_sheader(elf32), ".strtab", elf32->e_shnum);
  symboleSection = getSection32(elf32_sheader(elf32), SHT_SYMTAB, elf32->e_shnum);
  addSymbols32(strtab, (data + symboleSection->sh_offset),
	       (int)symboleSection->sh_size /
	       (int)symboleSection->sh_entsize, root);
  return (true);
}

int       mystrcmp(char const *str1, char const *str2)
{
  int     pos1;
  int     pos2;
    int     res;

  pos1 = pos2 = 0;
  while (str1[pos1] && !isalnum(str1[pos1]))
    ++pos1;
  while (str2[pos2] && !isalnum(str2[pos2]))
    ++pos2;
  while (str1[pos1]  && str2[pos2])
    {
        while (str1[pos1] && !isalnum(str1[pos1]))
            ++pos1;
        while (str2[pos2] && !isalnum(str2[pos2]))
            ++pos2;
      if (tolower(str1[pos1]) != tolower(str2[pos2]))
        break;
      ++pos1;
      ++pos2;
    }

    res = tolower(str1[pos1]) - tolower(str2[pos2]);

  return (res);
}

void		swapNodes(t_node *cur, t_node *next)
{
  t_node	tmp;

  tmp.symbol = cur->symbol;
  tmp.addr = cur->addr;
  tmp.type = cur->type;
  cur->symbol = next->symbol;
  cur->type = next->type;
  cur->addr = next->addr;
  next->symbol = tmp.symbol;
  next->addr = tmp.addr;
  next->type = tmp.type;
}


void        sortListAsc(t_node **root)
{
  bool      swap;
  t_node    *cur;

  swap = true;
  while (swap)
  {
    cur = *root;
    swap = false;
    while (cur->next)
    {
      if (mystrcmp(cur->symbol, cur->next->symbol) > 0)
	{
	  swapNodes(cur, cur->next);
	  swap = true;
	}
      cur = cur->next;
    }
  }
}

void      printList(t_node *root)
{
  t_node  *cur;

  cur = root;
  while (cur)
    {
      if (cur->addr == 0)
	printf("                 %c %s\n", cur->type, cur->symbol);
      else
	{
	  if (isArchitecture64(NULL, false))
            printf("%016llx %c %s\n",
		   (long long)cur->addr, cur->type, cur->symbol);
	  else
            printf("%016lx %c %s\n", cur->addr, cur->type, cur->symbol);
	}
      cur = cur->next;
    }
}

void		freeList(t_node **root)
{
  t_node	*cur;
  t_node	*tmp;

  cur = *root;
  while (cur)
    {
      tmp = cur->next;
      free(cur);
      cur = tmp;
    }
  *root = NULL;
}

int            parseFile(const char *file)
{
  t_node      *root;
  void        *data;

  root = NULL;
  if ((data = createMmap(file)) == (void*)-1)
    return (1);
  if (!isElfValid(data, file))
    return (2);
  if (isArchitecture64(data, true))
    {
      parseElf64(data, &root);
      sortListAsc(&root);
      printList(root);
      freeList(&root);
    }
  else
    {
      parseElf32(data, &root);
      sortListAsc(&root);
      printList(root);
      freeList(&root);
    }
  return (0);
}


int		main(int ac, char **av)
{
  int		i;

  if (ac < 2)
    {
      if (parseFile("a.out"))
	return (84);
    }
  else
    {
      i = 1;
      while (i < ac)
	{
	  if (parseFile(av[i]))
            return (84);
	  ++i;
	}
    }
  return (0);
}
