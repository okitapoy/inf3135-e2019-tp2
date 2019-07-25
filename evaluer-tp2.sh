#!/bin/bash
# evaluer-tp2.sh
if [ -z $1 ]
then
  correction=inf3135-e2019-tp1.correction
else
  correction=$1
fi
if [ ! -f ${correction} ]
then
  wget -q https://github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/${correction} -O ${correction}
fi
if [ ! -f ${correction} ]
then
  echo "erreur fatale, fichier correction inexistant."
  exit 1
fi

cp=`cat cp.txt`
n=1
y="resussi"
x="echec"
score="pts"
total=0

while read line; do
lineCols=( $line )
#echo -e "$n : $?" >> output.txt
#cut -d' ' -f3,5
points="${lineCols[0]}"
temps="${lineCols[1]}"
retour="${lineCols[2]}"
description="${lineCols[3]}"
couper=$temps"s"

commande=${line:29}

start=$(date +%s)

if [ $temps -gt 0 ]
then
eval timeout $couper $commande  > /dev/null 2>&1
else
eval $commande  > /dev/null 2>&1
fi

codeRetour=$?
end=$(date +%s)
time=$(( $end - $start ))

if [ $codeRetour -eq $retour -a $time -le $temps ]
then
echo "$n : $y $points $score"
total=$((total+points))
else
echo "$n : $x"
fi

n=$((n+1))
done < $correction

echo "Note (total) pour $cp dans inf3135-e2019-tp2: $total"
echo "$cp	$total"
