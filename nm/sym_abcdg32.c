/*
** sym_abcdg32.c for brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:32:52 2017 brout_m
** Last update Fri Feb 17 16:00:45 2017 brout_m
*/

#include <elf.h>
#include "helpers32.h"
#include "elfParser32.h"

char		compareA32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHN_ABS)
    return ('A');
  return (0);
}

char		compareB32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHT_NOBITS &&
      section->sh_flags & SHF_ALLOC &&
      section->sh_flags & SHF_WRITE)
    {
      if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('B');
      else
	return ('b');
    }
  return (0);
}

char		compareC32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHN_COMMON)
    {
      return ('C');
    }
  return (0);
}

char		compareD32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if ((section->sh_type == SHT_PROGBITS &&
       section->sh_flags & SHF_ALLOC &&
       section->sh_flags & SHF_WRITE) ||
      section->sh_type == SHT_DYNAMIC)
    {
      if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('D');
      else
	return ('d');
    }
  return (0);
}

char		compareG32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT &&
      section->sh_type == SHT_PROGBITS &&
      section->sh_flags & SHF_ALLOC &&
      section->sh_flags & SHF_WRITE)
    {
      if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('G');
      else
	return ('g');
    }
  return (0);
}
