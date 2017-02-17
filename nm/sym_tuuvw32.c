/*
** sym_iinpr.c for brout_m/rendu/system/PSU_2016_nmobjdump/elfParser
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Feb 14 21:32:52 2017 brout_m
** Last update Fri Feb 17 16:07:13 2017 brout_m
*/

#include <elf.h>
#include <string.h>
#include "helpers32.h"
#include "elfParser32.h"

char		compareT32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if ((section->sh_type == SHT_PROGBITS &&
       ELF32_ST_BIND(symbol->st_info) != STB_WEAK &&
       section->sh_flags == (SHF_EXECINSTR | SHF_ALLOC)) ||
      section->sh_type == SHT_FINI_ARRAY ||
      section->sh_type == SHT_INIT_ARRAY ||
      section->sh_type == SHT_PREINIT_ARRAY)
    {
      if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
	return ('T');
      else
	return ('t');
    }
  return (0);
}

char		compareU32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (ELF32_ST_TYPE(symbol->st_info) == STT_NOTYPE ||
      section->sh_type == SHN_UNDEF)
    return ('U');
  return (0);
}

char          compareu32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  (void)elf;
  if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
    {
      return ('u');
    }
  return (0);
}

char		compareV32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  Elf32_Shdr	*section;
  char		*strtable;

  section = elf32_section(elf, symbol->st_shndx);
  if (!section)
    return (0);
  if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK &&
      ELF32_ST_TYPE(symbol->st_info)  == STT_OBJECT)
    {
      strtable = elf32_strtable(elf);
      if (strtable &&
          strcmp(&strtable[section->sh_name], ".dynsym"))
	{
          if (ELF32_ST_VISIBILITY(symbol->st_other) == STV_DEFAULT ||
              ELF32_ST_VISIBILITY(symbol->st_other) == STV_HIDDEN)
	    return ('V');
          else
	    return ('v');
	}
    }
  return (0);
}

char        compareW32(Elf32_Ehdr *elf, Elf32_Sym *symbol)
{
  (void)elf;
  if ((ELF32_ST_TYPE(symbol->st_info)  == STT_NOTYPE ||
       symbol->st_shndx == SHN_UNDEF || symbol->st_other == STV_DEFAULT) &&
      ELF32_ST_BIND(symbol->st_info) == STB_WEAK)
    {
      if (symbol->st_shndx != SHN_UNDEF)
	return ('W');
      else
	return ('w');
    }
  return (0);
}
