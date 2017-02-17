/*
** commons.c for nm in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:44:01 2017 brout_m
** Last update Fri Feb 17 15:45:39 2017 brout_m
*/

#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ar.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "elfParser32.h"

size_t		fileSize(char const *filename)
{
  struct stat	file;

  if (stat(filename, &file) == -1)
    {
      fprintf(stderr, "my_nm: '%s': no such file\n", filename);
      return (0);
    }
  if (file.st_size < (int)sizeof(Elf32_Ehdr))
    {
      fprintf(stderr, "my_nm: '%s': Unknown file format\n", filename);
      return (0);
    }
  return ((size_t)file.st_size);
}

void		*createMmap(char const *filename)
{
  int		fd;
  size_t	size;
  void		*data;

  size = fileSize(filename);
  if (!size)
    return ((void*)-1);
  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return ((void*)-1);
  data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  close(fd);
  return (data);
}

bool		isArchitecture64(Elf32_Ehdr const * const elf, bool set)
{
  static bool	architecture = false;

  if (set)
    architecture = (elf->e_ident[EI_CLASS] == ELFCLASS64);
  return (architecture);
}

bool		isElfValid(Elf32_Ehdr const * const elf, const char *filename)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
      elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
      elf->e_ident[EI_CLASS] == ELFCLASSNONE ||
      elf->e_ident[EI_VERSION] == EV_NONE) {
    fprintf(stderr, "my_nm: '%s': Unknown file format\n", filename);
    return (false);
  }
  return (true);
}

inline bool isArchive(char *ar)
{
  return (!strncmp(ar, ARMAG, SARMAG));
}
