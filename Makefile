.PHONY: run, build


run:
	make build && ./serial

build:
	gcc -o serial serial.c

clean:
	rm -rf serial
