.PHONY: clean
.PHONY: all

all:
	gcc -o selfregi selfregi.c
	gcc -o manager manager.c

selfregi: selfregi.c
	gcc -o selfregi selfregi.c

manager: manager.c
	gcc -o manager manager.c

clean:
	rm -f *.out
	rm -f selfregi
	rm -f manager

