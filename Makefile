
OPTIONS = -Wall -pedantic -std=c11
CP = cp.txt

default: tp1 

tp1: tp1.o
	gcc $(OPTIONS) -o tp1 tp1.o

tp1.o: tp1.c
	gcc $(OPTIONS) -c tp1.c


data:
	wget -q https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip
	unzip crypto-data.zip  -d ./data
	rm crypto-data.zip 


resultat:
	git add note-du-tp.txt
	git commit -m "ajout resultat"
	git push origin master

test:
	./tp1 -c OKIK08078702 -e -k 17  -i ./data/crypto-msg01.in -o ./data/crypto-msg01.out


test2:
	./tp1 -c OKIK08078702 -e -k 80 


.PHONY: clean
clean:
	-rm tp1 tp1.o
	rm -rf data


