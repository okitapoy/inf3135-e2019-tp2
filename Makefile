OPTIONS = -Wall -pedantic -std=c11
CP = cp.txt

default: tp2 

tp2: tp2.o
	gcc $(OPTIONS) -o tp2 tp2.o

tp2.o: tp2.c
	gcc $(OPTIONS) -c tp2.c


data:
	wget -q https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip
	unzip crypto-data.zip  -d ./data
	cp ./data/crypto-msg01.alphabet ./data/alphabet.txt
	rm crypto-data.zip 


resultat:
	git add note-du-tp.txt
	git commit -m "ajout resultat"
	git push origin master

test:
	./tp2 -c OKIK08078702 -e -k 17 -a ./data  -i ./data/crypto-msg01.in -o ./data/crypto-msg01.out


test2:
	./tp2 -c OKIK08078702 -e -k 80

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./tp2 


.PHONY: clean
clean:
	-rm tp2 tp2.o
	rm -rf data

