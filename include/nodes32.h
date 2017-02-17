/*
** nodes32.h in brout_m/rendu/system/PSU_2016_nmobjdump
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri Feb 17 15:41:04 2017 brout_m
** Last update Fri Feb 17 15:41:21 2017 brout_m
*/

#ifndef NODES32_H
# define NODES32_H

# include "commons.h"

void      printList32(t_node const *root);
bool      addNode32(t_node **root, char const *name,
                    Elf32_Sym const * const sym,
                    uint32_t type);

#endif /* !NODES_H */
