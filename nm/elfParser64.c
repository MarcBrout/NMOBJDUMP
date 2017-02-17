/*
** elfParser.c for nmobjdump in rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 11:00:58 2017 brout_m
** Last update Fri Feb 17 16:16:21 2017 brout_m
*/

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "commons.h"
#include "elfParser64.h"
#include "helpers64.h"
#include "nodes64.h"

static symCmp64 cmptab64[END] = {
  &compareT64,
  &compareA64,
  &compareC64,
  &compareV64,
  &compareW64,
  &compareB64,
  &compareD64,
  &compareG64,
  &compareN64,
  &compareP64,
  &compareR64,
  &compareU64,
  &compareu64,
  &comparei64,
  &compareI64
};

static uint32_t		getType64(void *data, Elf64_Sym *symbole)
{
  char			type;
  int			i;

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

static void	*getSectionData64(void *elf,
				  Elf64_Shdr const *shdr,
				  const char *section,
				  int nb)
{
  int		i;
  char		*stringTable;

  i = 0;
  stringTable = elf64_strtable(elf);
  if (!stringTable)
    return (NULL);
  while (i < nb)
    {
      if (!strcmp(section, &stringTable[shdr[i].sh_name]))
	return (elf + shdr[i].sh_offset);
      ++i;
    }
  return (NULL);
}

static bool		addSymbols64(char const *stringTable,
				     void *data,
				     Elf64_Shdr *symboleSection,
				     t_node **root)
{
  int			i;
  uint32_t		type;
  int			nb;
  Elf64_Sym		*symboleArray;

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

static void	*getSection64(Elf64_Shdr *shdr, uint32_t type, int nb)
{
  int		i;

  i = 0;
  while (i < nb)
    {
      if (shdr[i].sh_type == type)
	return (&shdr[i]);
      ++i;
    }
  return (NULL);
}

bool		parseElf64(void *data, t_node **root, const char *filename)
{
  char		*strtab;
  Elf64_Shdr	*symboleSection;
  Elf64_Ehdr	*elf64;

  elf64 = data;
  strtab = getSectionData64(data, elf64_sheader(elf64), ".strtab", elf64->e_shnum);
  if (!strtab)
    {
      fprintf(stderr, "my_nm: %s: aucun symbole\n", filename);
      return (false);
    }
  symboleSection = getSection64(elf64_sheader(elf64), SHT_SYMTAB, elf64->e_shnum);
  if (!symboleSection)
    {
      return (false);
    }
  addSymbols64(strtab, data, symboleSection, root);
  return (true);
}
