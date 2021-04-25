compile: main.c fun.c fun.h
	gcc main.c fun.c fun.h -o minicron -Wall

#kopiowanie do pliku testowego 
copy: main.c fun.c fun.h
	cp fun.c ./MyNewProject/src/fun.c
	cp fun.h ./MyNewProject/src/fun.h
test:
	cd MyNewProject && 	ceedling test:all
log: 
	cat /var/log/syslog | tail -n $(n)
make kill:
	killall minicron -$(n)