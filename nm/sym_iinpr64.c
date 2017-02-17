/*
** sym_iinpr.c for brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:32:52 2017 brout_m
** Last update Fri Feb 17 16:05:58 2017 brout_m
*/

#include <elf.h>
#include <string.h>
#include "helpers64.h"
#include "elfParser64.h"

char		comparei64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type != SHN_ABS &&
      ELF64_ST_TYPE(symbol->st_info) == STT_FUNC)
    return ('i');
  return (0);
}

char		compareI64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type != SHN_ABS &&
      ELF64_ST_TYPE(symbol->st_info) != STT_FUNC)
    return ('I');
  return (0);
}

char		compareN64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;
  char		*strtable;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  strtable = elf64_strtable(elf);
  if (!strtable)
    return (0);
  if (!strcmp(&strtable[section->sh_name], ".debug"))
    {
      return ('N');
    }
  return (0);
}

char		compareP64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;
  char		*strtable;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  strtable = elf64_strtable(elf);
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

char		compareR64(Elf64_Ehdr *elf, Elf64_Sym *symbol)
{
  Elf64_Shdr	*section;

  section = elf64_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (section->sh_type == SHT_PROGBITS &&
      section->sh_flags & SHF_ALLOC &&
      !(section->sh_flags & SHF_WRITE))
    {
      if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('R');
      else
	return ('r');
    }
  return (0);
}
