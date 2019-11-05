.PHONY: run, build


run:
	make build && ./interface 2

build:
	gcc -o interface interface.c

clean:
	rm -rf interface