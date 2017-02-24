/*
** header32.c for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 17:30:57 2017 brout_m
** Last update Thu Feb 23 16:18:27 2017 marc brout
*/

#include <stdio.h>
#include <elf.h>
#include "flags.h"
#include "helpers32.h"
#include "dump32.h"

static t_head32 machines[19] = {
  {EM_NONE, "An unknown machine"},
  {EM_M32, "AT&T WE 32100"},
  {EM_SPARC, "Sun Microsystems SPARC"},
  {EM_386, "i386"},
  {EM_68K, "Motorola 68000"},
  {EM_88K, "Motorola 88000"},
  {EM_860, "Intel 80860"},
  {EM_MIPS, "MIPS RS3000"},
  {EM_PARISC, "HP/PA"},
  {EM_SPARC32PLUS, "SPARC+"},
  {EM_PPC, "PowerPC"},
  {EM_PPC64, "PowerPC 32-bit"},
  {EM_S390, "IBM S/390"},
  {EM_ARM, "Advanced RISC Machines"},
  {EM_SH, "Renesas SuperH"},
  {EM_SPARCV9, "SPARC v9 32-bit"},
  {EM_IA_64, "Intel Itanium"},
  {EM_X86_64, "i386"},
  {EM_VAX, "DEC Vax"}
};

static unsigned int check_header(Elf32_Ehdr *elf,
                                 unsigned int flags)
{
  if (elf->e_type == ET_EXEC)
    {
      flags = flags | EXEC_P;
    }
  else if (elf->e_type == ET_DYN)
    flags = flags | DYNAMIC;
  return (flags);
}

static char *flagsStr[10] = {
  "BFD_NO_FLAGS",
  "HAS_RELOC",
  "EXEC_P",
  "HAS_LINENO",
  "HAS_DEBUG",
  "HAS_SYMS",
  "HAS_LOCALS",
  "DYNAMIC",
  "WP_TEXT",
  "D_PAGED"
};

static void	printFlags(unsigned int flags)
{
  int		i;
  unsigned int	f;
  bool		done;

  if (flags == 0)
    {
      printf("%s\n", flagsStr[flags]);
      return ;
    }
  i = f = 1;
  done = false;
  while (i < 10)
    {
      if (f & flags)
        {
	  if (done)
	    printf(", ");
	  printf("%s", flagsStr[i]);
	  done = true;
        }
      f = f << 1;
      ++i;
    }
  printf("\n");
}

void	dumpHeader32(Elf32_Ehdr *elf, const char *file, unsigned int flags)
{
  int	i;

  i = 0;
  flags = check_header(elf, flags);
  printf("\n%s:     file format elf32-i386\n", file);
  while (i < 19)
    {
      if (machines[i].key == elf->e_machine)
	break;
      ++i;
    }
  printf("architecture: %s, flags 0x%08x:\n", machines[i].value, flags);
  printFlags(flags);
  printf("start address 0x%08llx\n\n", (long long)elf->e_entry);
}
