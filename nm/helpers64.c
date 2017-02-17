/*
** helpers64.c for  in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:53:39 2017 brout_m
** Last update Fri Feb 17 16:33:41 2017 brout_m
*/

#include <elf.h>
#include <wchar.h>
#include <stdbool.h>
#include <string.h>
#include <ar.h>

Elf64_Shdr *elf64_sheader(Elf64_Ehdr *elf)
{
  return ((Elf64_Shdr *)((void *)elf + elf->e_shoff));
}

Elf64_Shdr *elf64_section(Elf64_Ehdr *elf, int pos)
{
  return (&elf64_sheader(elf)[pos]);
}

char *elf64_strtable(Elf64_Ehdr *elf)
{
  if (elf->e_shstrndx == SHN_UNDEF)
    return (NULL);
  return ((char *)((void*)elf +
		   elf64_section(elf, elf->e_shstrndx)->sh_offset));
}

char		*elf64_name(Elf64_Ehdr *elf, int off)
{
  char		*strtab;

  strtab = elf64_strtable(elf);
  if (!strtab)
    return  (NULL);
  return (strtab + off);
}
