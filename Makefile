##
## Makefile for nmobjdump in /home/brout_m/rendu/system/PSU_2016_nmobjdump
##
## Made by brout_m
## Login   <marc.brout@epitech.eu>
##
## Started on  Wed Feb 15 17:27:52 2017 brout_m
## Last update Thu Feb 16 17:20:30 2017 brout_m
##

DEBUG=		no

NM=		my_nm

OBJDUMP=	my_objdump

NMFOLDER=	nm/

NMFILES=	cmpfuncs.c \
		commons.c \
		elfParser32.c \
		elfParser64.c \
		helpers32.c \
		helpers64.c \
		nodes32.c \
		nodes64.c \
		sym_abcdg64.c \
		sym_iinpr64.c \
		sym_tuuvw64.c \
		sym_abcdg32.c \
		sym_iinpr32.c \
		sym_tuuvw32.c \
		my_nm.c

NMSRC=		$(addprefix $(NMFOLDER), $(NMFILES))

NMOBJ=		$(NMSRC:.c=.o)

INC=		-Iinclude/

CC=		gcc

ifeq ($(DEBUG), yes)
CFLAGS=		-g -W -Wall -Wextra -Werror $(INC)
else
CFLAGS=		-W -Wall -Wextra -Werror $(INC)
endif

$(NM): $(NMOBJ)
	$(CC) -o $(NM) $(NMOBJ) $(INC)

nm: $(NM)

all: nm

clean:
	rm -rf $(NMOBJ)

fclean: clean
	rm -rf $(NM)

re: fclean all

.PHONY: all clean fclean re
