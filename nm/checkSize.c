/*
** checkSize.c for nmobjdump in system/PSU_2016_nmobjdump
** 
** Made by marc brout
** Login   <marc.brout@epitech.eu>
** 
** Started on  Fri Feb 24 09:52:00 2017 marc brout
** Last update Fri Feb 24 10:15:09 2017 marc brout
*/

#include <elf.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

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
