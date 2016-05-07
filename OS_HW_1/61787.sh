#!/bin/bash

check_for_end() {
	echo "End of game?"
	read end
	if [ "$end" = "wins" -o "$end" = "lost" ] 
	then
		break
	fi
	#return 0
}

echo "Player 1 name (o):"
read player1
echo "Player 2 name (x):"
read player2
#echo $player1$player2

#multiline comment
: 'until [ -z "$1" ]             # Until uses up arguments passed...
    do
    	#let "product *= $1"
    	echo "$1"
	shift
    done
'
end_of_game=false
while [ true ]
do
	echo "$player1 move: (x,y)"
	read player1_move
	echo "$player1_move"
	
	check_for_end
done
