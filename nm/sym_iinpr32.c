/*
** sym_iinpr.c for brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:32:52 2017 brout_m
** Last update Fri Feb 17 16:03:09 2017 brout_m
*/

#include <elf.h>
#include <string.h>
#include "helpers32.h"
#include "elfParser32.h"

char		comparei32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type != SHN_ABS &&
      ELF32_ST_TYPE(symbol->st_info) == STT_FUNC)
    return ('i');
  return (0);
}

char		compareI32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type != SHN_ABS &&
      ELF32_ST_TYPE(symbol->st_info) != STT_FUNC)
    return ('I');
  return (0);
}

char		compareN32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;
  char		*strtable;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  strtable = elf32_strtable(elf);
  if (!strtable)
    return (0);
  if (!strcmp(&strtable[section->sh_name], ".debug"))
    {
      return ('N');
    }
  return (0);
}

char		compareP32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;
  char		*strtable;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  strtable = elf32_strtable(elf);
  if (!strtable)
    return (0);
  if (!strcmp(&strtable[section->sh_name], ".note.GNU-stack") &&
      section->sh_type == SHT_PROGBITS &&
      section->sh_flags & SHF_EXECINSTR)
    {
      return ('P');
    }
  return (0);
}

char		compareR32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHT_PROGBITS &&
      section->sh_flags & SHF_ALLOC &&
      !(section->sh_flags & SHF_WRITE))
    {
      if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('R');
      else
	return ('r');
    }
  return (0);
}
