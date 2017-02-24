/*
** nodeify32.c for objdump in PSU_2016_nmobjdump/objdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Feb 18 18:35:24 2017 brout_m
** Last update Thu Feb 23 17:50:14 2017 marc brout
*/

#include <stdbool.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include "flags.h"
#include "helpers32.h"
#include "dump32.h"

static bool	addDumpNode32(void *data,
			      Elf32_Shdr *section,
			      t_dump **root)
{
  t_dump	*node;
  t_dump	*cur;

  node = malloc(sizeof(*node));
  if (!node)
    return (false);
  node->data = data + section->sh_offset;
  node->sh_name = elf32_name(data, section->sh_name);
  node->size = section->sh_size;
  node->off = section->sh_addr;
  node->next = NULL;
  if (!*root)
    *root = node;
  else
    {
      cur = *root;
      while (cur->next)
	cur = cur->next;
      cur->next = node;
    }
  return (true);
}

bool		isPrintableSection32(Elf32_Ehdr *elf,
				     Elf32_Shdr *section)
{
  char		*name;

  name = elf32_name(elf, section->sh_name);
  if (!name)
    return (false);
  return ((!(elf->e_type == ET_REL && (section->sh_type == SHT_RELA ||
				       section->sh_type == SHT_REL)) &&
	  (section->sh_type != SHT_NOBITS &&
	   section->sh_type != SHT_NULL &&
	   section->sh_type != SHT_STRTAB &&
	   section->sh_type != SHT_SYMTAB)) ||
	   !strcmp(name, ".dynstr"));
}

static unsigned int checkSection(Elf32_Ehdr *elf,
				 Elf32_Shdr *section,
				 unsigned int flags)
{
  (void)elf;
  if ((section->sh_type == SHT_REL ||
       section->sh_type == SHT_RELA) && elf->e_type == ET_REL)
    flags = flags | HAS_RELOC;
  else if (section->sh_type == SHT_SYMTAB ||
	   !strcmp(".dynstr", elf32_name(elf, section->sh_name)))
    flags = flags | HAS_SYMS;
  else if (section->sh_type == SHT_DYNSYM)
    flags = flags | D_PAGED;
  return (flags);
}

bool		nodeifyElf32(Elf32_Ehdr *elf,
			     t_dump **root,
			     unsigned int *flags)
{
  int		i;
  Elf32_Shdr	*section;

  i = 0;
  while (i < elf->e_shnum)
    {
      section = elf32_section(elf, i);
      if (!section)
	return (true);
      if (section->sh_type == SHT_NOBITS)
        {
	  ++i;
	  continue;
        }
      *flags = checkSection(elf, section, *flags);
      if (isPrintableSection32(elf, section) &&
	  section->sh_size != 0 &&
	  !addDumpNode32(elf, section, root))
	return (true);
      ++i;
    }
  return (true);
}
