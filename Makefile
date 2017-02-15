##
## Makefile for nmobjdump in /home/brout_m/rendu/system/PSU_2016_nmobjdump
##
## Made by brout_m
## Login   <marc.brout@epitech.eu>
##
## Started on  Wed Feb 15 17:27:52 2017 brout_m
## Last update Wed Feb 15 17:44:52 2017 brout_m
##

DEBUG=		no

NM=		my_nm

OBJDUMP=	my_objdump

NMFOLDER=	elfParser/

NMFILES=	elfParser.c \
		sym_abcdg64.c \
		sym_iinpr64.c \
		sym_tuuvw64.c

NMSRC=		$(addprefix $(NMFOLDER), $(NMFILES))

NMOBJ=		$(NMSRC:.c=.o)

INC=		-Iinclude/

CC=		gcc

ifeq ($(DEBUG), yes)
CFLAGS=		-g -W -Wall -Wextra -Werror $(INC) -O2
else
CFLAGS=		-W -Wall -Wextra -Werror $(INC) -O2
endif

$(NM): $(NMOBJ)
	$(CC) -o $(NM) $(NMOBJ) $(INC)

all: $(NM)

clean:
	rm -rf $(NMOBJ)

fclean: clean
	rm -rf $(NM)

re: fclean all

.PHONY: all clean fclean re
