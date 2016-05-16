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
#variables for "x" player
x11=0
x12=0
x13=0
x21=0
x22=0
x23=0
v31=0
v32=0
x33=0

#variables for "o" player
o11=0
o12=0
o13=0
o21=0
o22=0
o23=0
v31=0
v32=0
o33=0

#symbols
v11=" "
v12=" "
v13=" "
v21=" "
v22=" "
v23=" "
v31=" "
v32=" "
v33=" "

echo "Current board: "
echo "|$v11|$v12|$v13|"
echo "|$v21|$v22|$v23|"
echo "|$v31|$v32|$v33|"

end_of_game=false
while [ true ]
do
	echo "$player1 move: (x,y)"
	read player1_move
	echo "$player1_move"
	
	check_for_end
done
