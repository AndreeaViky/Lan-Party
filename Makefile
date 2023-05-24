

build:
	gcc -Wall -Wextra -std=c99 -o lanParty main.c functii.c

run:
	./lanParty

clean:
	rm lanParty