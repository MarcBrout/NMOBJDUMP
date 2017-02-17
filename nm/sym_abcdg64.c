/*
** sym_abcdg64.c for brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:32:52 2017 brout_m
** Last update Fri Feb 17 16:01:54 2017 brout_m
*/

#include <elf.h>
#include "helpers64.h"
#include "elfParser64.h"

char		compareA64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHN_ABS)
    return ('A');
  return (0);
}

char          compareB64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr  *section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHT_NOBITS &&
      section->sh_flags & SHF_ALLOC &&
      section->sh_flags & SHF_WRITE)
    {
      if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('B');
      else
	return ('b');
    }
  return (0);
}

char		compareC64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHN_COMMON)
    {
      return ('C');
    }
  return (0);
}

char		compareD64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if ((section->sh_type == SHT_PROGBITS &&
       section->sh_flags & SHF_ALLOC &&
       section->sh_flags & SHF_WRITE) ||
      section->sh_type == SHT_DYNAMIC)
    {
      if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('D');
      else
	return ('d');
    }
  return (0);
}

char		compareG64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT &&
      section->sh_type == SHT_PROGBITS &&
      section->sh_flags & SHF_ALLOC &&
      section->sh_flags & SHF_WRITE)
    {
      if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('G');
      else
	return ('g');
    }
  return (0);
}
