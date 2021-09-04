shell: \
				prompt.c \
				readline.c \
				splitline.c \
				echo.c \
				pwd.c \
				cd.c \
				ls.c \
				execute.c \
				pinfo.c \
				io_redirection.c \
				pipe.c \
				redirection_piping.c \
				setenv.c \
				jobs.c \
				kjob.c \
				fg.c \
				bg.c \
				overkill.c \
				quit.c \
				signal_handler.c
			gcc -g -o shell $^
clean:
	@rm -f *.o shell

prompt.o: shell.h prompt.c
	gcc -g -c prompt.c

readline.o: shell.h readline.c
	gcc -g -c readline.c

splitline.o: shell.h splitline.c
	gcc -g -c splitline.c

echo.o: shell.h echo.c
	gcc -g -c echo.c

pwd.o: shell.h pwd.c
	gcc -g -c pwd.c

cd.o: shell.h cd.c
	gcc -g -c cd.c

ls.o: shell.h ls.c
	gcc -g -c ls.c

execute.o: shell.h execute.c
	gcc -g -c execute.c

pinfo.o: shell.h pinfo.c
	gcc -g -c pinfo.c

io_redirection.o: shell.h io_redirection.c
	gcc -g -c io_redirection.c

pipe.o: shell.h pipe.c
	gcc -g -c pipe.c

redirection_piping.o: shell.h redirection_piping.c
	gcc -g -c redirection_piping.c

setenv.o: shell.h setenv.c
	gcc -g -c setenv.c

jobs.o: shell.h jobs.c
	gcc -g -c jobs.c

kjob.o: shell.h kjob.c
	gcc -g -c kjob.c

fg.o: shell.h fg.c
	gcc -g -c fg.c

bg.o: shell.h bg.c
	gcc -g -c bg.c

overkill.o: shell.h overkill.c
	gcc -g -c overkill.c

quit.o: shell.h quit.c
	gcc -g -c quit.c

signal_handler.o: shell.h signal_handler.c
	gcc -g -c signal_handler.c