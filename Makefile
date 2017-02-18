##
## Makefile for nmobjdump in /home/brout_m/rendu/system/PSU_2016_nmobjdump
##
## Made by brout_m
## Login   <marc.brout@epitech.eu>
##
## Started on  Wed Feb 15 17:27:52 2017 brout_m
## Last update Sat Feb 18 18:14:23 2017 brout_m
##

DEBUG=		no

NM=		my_nm

OBJDUMP=	my_objdump

NMFOLDER=	nm/

OBJDUMPFOLDER=	objdump/

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

OBJDUMPFILES=	header64.c \
		dumpList64.c \
		my_objdump.c \
		nodeify64.c

NMSRC=		$(addprefix $(NMFOLDER), $(NMFILES))

OBJDUMPSRC=	$(addprefix $(OBJDUMPFOLDER), $(OBJDUMPFILES)) \
		$(NMFOLDER)/helpers64.c \
		$(NMFOLDER)/commons.c


NMOBJ=		$(NMSRC:.c=.o)

OBJDUMPOBJ=	$(OBJDUMPSRC:.c=.o)

INC=		-Iinclude/

CC=		gcc

ifeq ($(DEBUG), yes)
CFLAGS=		-g -W -Wall -Wextra -Werror $(INC)
else
CFLAGS=		-W -Wall -Wextra -Werror $(INC)
endif

$(NM): $(OBJDUMP) $(NMOBJ)
	$(CC) -o $(NM) $(NMOBJ) $(INC)

$(OBJDUMP): $(OBJDUMPOBJ)
	$(CC) -o $(OBJDUMP) $(OBJDUMPOBJ) $(INC)

nm: $(NM)

objdump: $(OBJDUMP)

all: nm objdump

clean:
	rm -rf $(NMOBJ)
	rm -rf $(OBJDUMPOBJ)

fclean: clean
	rm -rf $(NM)
	rm -rf $(OBJDUMP)

re: fclean all

.PHONY: all clean fclean re
