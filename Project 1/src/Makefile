#-*-Makefile-*-



prog: main.o help.o allocate.o write.o disp.o freee.o ext.o invert.o write_pattern.o verify_pattern.o Pattern_gen.o
	gcc main.o help.o allocate.o write.o disp.o freee.o ext.o invert.o write_pattern.o verify_pattern.o Pattern_gen.o  -lm -o prog
main.o: main.c ../inc/main.h ../inc/help.h
	gcc -c main.c 
help.o: help.c ../inc/help.h
	gcc -c help.c 
allocate.o: allocate.c ../inc/allocate.h
	gcc -c allocate.c
write.o: write.c ../inc/write.h ../inc/allocate.h
	gcc -c write.c
disp.o: disp.c ../inc/disp.h ../inc/allocate.h ../inc/write.h
	gcc -c disp.c 
freee.o: freee.c ../inc/freee.h ../inc/allocate.h
	gcc -c freee.c 
invert.o: invert.c ../inc/invert.h ../inc/allocate.h ../inc/write.h
	gcc -c invert.c 
write_pattern.o: write_pattern.c ../inc/write_pattern.h ../inc/write.h ../inc/Pattern_gen.h ../inc/allocate.h ../inc/disp.h
	gcc -c write_pattern.c 
verify_pattern.o: verify_pattern.c ../inc/verify_pattern.h ../inc/write.h ../inc/Pattern_gen.h ../inc/allocate.h ../inc/disp.h
	gcc -c verify_pattern.c 
Pattern_gen.o: Pattern_gen.c ../inc/Pattern_gen.h
	gcc -lm -c Pattern_gen.c 
ext.o: ext.c ../inc/ext.h
	gcc -c ext.c 
test: prog testf.txt
	./prog <testf.txt
clean:
	rm *.o
