/*
** nodes64.h for nm in rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:41:32 2017 brout_m
** Last update Fri Feb 17 16:10:01 2017 brout_m
*/

#ifndef NODES64_H
# define NODES64_H

# include "commons.h"

void      printList64(t_node const *root);
bool      addNode64(t_node **root, char const *name,
                    Elf64_Sym const * const sym,
                    uint32_t type);

#endif /* !NODES_H */
