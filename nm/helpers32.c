/*
** helpers32.c for in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:52:55 2017 brout_m
** Last update Fri Feb 17 16:33:41 2017 brout_m
*/

#include <elf.h>
#include <stddef.h>

Elf32_Shdr *elf32_sheader(Elf32_Ehdr *elf)
{
  return ((Elf32_Shdr *)((void *)elf + elf->e_shoff));
}

Elf32_Shdr *elf32_section(Elf32_Ehdr *elf, int pos)
{
  return (&elf32_sheader(elf)[pos]);
}

char *elf32_strtable(Elf32_Ehdr *elf)
{
  if (elf->e_shstrndx == SHN_UNDEF)
    return (NULL);
  return ((char *)((void*)elf +
		   elf32_section(elf, elf->e_shstrndx)->sh_offset));
}

char		*elf32_name(Elf32_Ehdr *elf, int off)
{
  char		*strtab;

  strtab = elf32_strtable(elf);
  if (!strtab)
    return  (NULL);
  return (strtab + off);
}
