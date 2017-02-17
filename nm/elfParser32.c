/*
** elfParser.c for nmobjdump in /rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon Feb 13 11:00:58 2017 brout_m
** Last update Fri Feb 17 16:16:16 2017 brout_m
*/

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "commons.h"
#include "elfParser32.h"
#include "helpers32.h"
#include "nodes32.h"

static symCmp32 cmptab32[END] = {
  &compareT32,
  &compareA32,
  &compareC32,
  &compareV32,
  &compareW32,
  &compareB32,
  &compareD32,
  &compareG32,
  &compareN32,
  &compareP32,
  &compareR32,
  &compareU32,
  &compareu32,
  &comparei32,
  &compareI32
};

static uint32_t		getType32(void *data, Elf32_Sym *symbole)
{
  char			type;
  int			i;

  i = 0;
  type = 0;
  while (i < END)
    {
      type = cmptab32[i](data, symbole);
      if (type)
	break;
      ++i;
    }
  if (!type)
    type = '?';
  return ((uint32_t)type);
}

static void	*getSectionData32(void *elf,
				  Elf32_Shdr const *shdr,
				  const char *section,
				  int nb)
{
  int		i;
  char		*stringTable;

  i = 0;
  stringTable = elf32_strtable(elf);
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

static bool		addSymbols32(char const *stringTable,
				     void *data,
				     Elf32_Shdr *symboleSection,
				     t_node **root)
{
  int			i;
  uint32_t		type;
  int			nb;
  Elf32_Sym		*symboleArray;

  i = 0;
  nb = (int)symboleSection->sh_size / (int)symboleSection->sh_entsize;
  symboleArray = data + symboleSection->sh_offset;
  while (i < nb)
    {
      if (symboleArray[i].st_name > 0 &&
	  ELF32_ST_TYPE(symboleArray[i].st_info) != STT_FILE)
	{
          type = getType32(data, &symboleArray[i]);
	  if (!addNode32(root,
			 &stringTable[symboleArray[i].st_name],
			 &symboleArray[i], type))
	    return (false);
	}
      ++i;
    }
  return (true);
}

static void	*getSection32(Elf32_Shdr *shdr, uint32_t type, int nb)
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

bool		parseElf32(void *data, t_node **root, const char *filename)
{
  char		*strtab;
  Elf32_Shdr	*symboleSection;
  Elf32_Ehdr	*elf32;

  elf32 = data;
  strtab = getSectionData32(data, elf32_sheader(elf32), ".strtab", elf32->e_shnum);
  if (!strtab)
    {
      fprintf(stderr, "my_nm: %s: aucun symbole\n", filename);
      return (false);
    }
  symboleSection = getSection32(elf32_sheader(elf32), SHT_SYMTAB, elf32->e_shnum);
  if (!symboleSection)
    {
      return (false);
    }
  addSymbols32(strtab, data, symboleSection, root);
  return (true);
}
