.PHONY: run, build


run:
	./interface 2

build:
	gcc -o interface interface.c