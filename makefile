compile: main.c fun.c fun.h
	gcc main.c fun.c fun.h -o minicrom

#kopiowanie do pliku testowego 
copy: main.c fun.c fun.h
	cp fun.c ./MyNewProject/src/fun.c
	cp fun.h ./MyNewProject/src/fun.h
test:	main.c fun.c fun.h
	cp fun.c ./MyNewProject/src/fun.c
	cp fun.h ./MyNewProject/src/fun.h
	cd MyNewProject && 	ceedling test:all
onlytest:
	cd MyNewProject && 	ceedling test:all