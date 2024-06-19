all: drone.exe

drone.exe: drone.o init.o field.o pumpkin.o logic.o
	gcc -o drone drone.o init.o field.o pumpkin.o logic.o

drone.o: drone.c  
	gcc -c --std=c99 drone.c -o drone.o

init.o: init.c
	gcc -c --std=c99 init.c -o init.o

pumpkin.o: pumpkin.c
	gcc -c --std=c99 pumpkin.c -o pumpkin.o

field.o: field.c
	gcc -c --std=c99 field.c -o field.o

logic.o: logic.c
	gcc -c --std=c99 logic.c -o logic.o

clean:
	del *.o 
	del *.exe


