build: 
	gcc -Wall task1.c task1.h task2.h task2.c task3.h task3.c bonus.h bonus.c  main.c -o minimax
clean: 
	rm -rf minimax
style:
	./style.pl --ignore SPDX_LICENSE_TAG,NEW_TYPEDEFS,CONST_STRUCT --no-tree --terse -f *.c *.h > styleErrors.txt