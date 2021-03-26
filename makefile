compile: main.c fun.c fun.h
	gcc main.c fun.c fun.h -o outcome	

#kopiowanie do pliku testowego 
copy: main.c fun.c fun.h
	cp main.c ./MyNewProject/src/main.c
	cp fun.c ./MyNewProject/src/fun.c
	cp fun.h ./MyNewProject/src/fun.h
test:
	cd MyNewProject && 	ceedling test:all && cd ..