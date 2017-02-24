/*
** checkSize.c for nmobjdump in system/PSU_2016_nmobjdump
** 
** Made by marc brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Fri Feb 24 09:52:00 2017 marc brout
** Last update Fri Feb 24 16:05:24 2017 marc brout
*/

#include <elf.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "helpers64.h"
#include "helpers32.h"
#include "commons.h"

int		checkSize64(Elf64_Ehdr *elf, char const *prog,
			    char const *filename, size_t size)
{
  FILE		*fd;
  Elf64_Shdr	section;
  
  fd = fopen(filename, "r");
  if (!fd)
    return (-1);
  if (fseek(fd, elf->e_shoff + (elf->e_shnum - 1) *
	    elf->e_shentsize, SEEK_SET) == -1 ||
      fread(&section, 1, elf->e_shentsize, fd) < elf->e_shentsize ||
      section.sh_offset + section.sh_size > size)
    {
      fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
      fclose(fd);
      return (1);
    }
  fclose(fd);
  return (0);
}

int		checkSectionHeaders64(Elf64_Ehdr *elf, char const *prog,
				      char const *filename, size_t size)
{
  int		i;
  Elf64_Shdr	*section;

  if ((uintptr_t)elf + elf->e_shoff > (uintptr_t)elf + size)
    {
      fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
      return (1);
    }
  i = 0;
  while (i < elf->e_shnum)
    {
      section = elf64_section(elf, i);
      if ((uintptr_t)elf + section->sh_offset > (uintptr_t)elf + size ||
	  (section->sh_type != SHT_NOBITS &&
	   (uintptr_t)elf + section->sh_offset + section->sh_size > (uintptr_t)elf + size))
	{
	  fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
	  return (1);
	}
      ++i;
    }
  return (0);
}
				      

int		checkSectionHeaders32(Elf32_Ehdr *elf, char const *prog,
				      char const *filename, size_t size)
{
  int		i;
  Elf32_Shdr	*section;

  if ((uintptr_t)elf + elf->e_shoff > (uintptr_t)elf + size)
    {
      fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
      return (1);
    }
  i = 0;
  while (i < elf->e_shnum)
    {
      section = elf32_section(elf, i);
      if ((uintptr_t)elf + section->sh_offset > (uintptr_t)elf + size ||
	  (section->sh_type != SHT_NOBITS &&
	   (uintptr_t)elf + section->sh_offset + section->sh_size > (uintptr_t)elf + size))
	{
	  fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
	  return (1);
	}
      ++i;
    }
  return (0);
}
				      
int		checkSize32(Elf32_Ehdr *elf, char const *prog,
			    char const *filename, size_t size)
{
  FILE		*fd;
  Elf32_Shdr	section;
  
  fd = fopen(filename, "r");
  if (!fd)
    return (-1);
  if (fseek(fd, elf->e_shoff + (elf->e_shnum - 1) *
	    elf->e_shentsize, SEEK_SET) == -1 ||
      fread(&section, 1, elf->e_shentsize, fd) < elf->e_shentsize ||
      section.sh_offset + section.sh_size > size)
    {
      fprintf(stderr, "%s: %s: File truncated\n", prog, filename);
      fclose(fd);
      return (1);
    }
  fclose(fd);
  return (0);
}
