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

: '
try_validate_move() {
	{ # this is my bash try block

	    validate_move "$1" "$2" "$3" &&
	    #save your output
	    result=$?
	    return $result

	} || { # this is catch block
	    # save log for exception 
	    echo "fu"
	    return 0
	}
} '

validate_move() {
	#echo "$1 $2"
	if [ "$1" -le 2 -a "$2" -le 2 -a "$1" -ge 0 -a "$2" -ge 0 ] 2>/dev/null #catch error
	then
		return 1
	fi
	return 0

	#$2 contains info for which player are we checking
	#TODO: check if there is already something on the position
}

echo "Име на играч 1 - O:"
read player1
echo "Име на играч 2 - X:"
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
x00=0
x01=0
x02=0
x10=0
x11=0
x12=0
x20=0
x21=0
x22=0

#variables for "o" player
o00=0
o01=0
o02=1
o10=0
o11=0
o12=1
o20=0
o21=0
o22=1

#symbols
v00=" "
v01=" "
v02=" "
v10=" "
v11=" "
v12=" "
v20=" "
v21=" "
v22=" "

echo "Current board: "
echo "|$v00|$v01|$v02|"
echo "|$v10|$v11|$v12|"
echo "|$v20|$v21|$v22|"


xrows=$(( ($x00 & $x01 & $x02) | ( $x10 & $x11 & $x12 ) | ( $x20 & $x21 & $x22 ) ))
xcols=$(( ($x00 & $x10 & $x20) | ( $x01 & $x11 & $x21 ) | ( $x02 & $x12 & $x22 ) ))
xdiags=$(( ($x00 & $x11 & $x22) | ( $x02 & $x11 & $x20 ) ))
xwins=$(( $xrows | $xcols | $xdiags ))
#echo "$xcols $xrows $xdiags $xwins"

orows=$(( ($o00 & $o01 & $o02) | ( $o10 & $o11 & $o12 ) | ( $o20 & $o21 & $o22 ) ))
ocols=$(( ($o00 & $o10 & $o20) | ( $o01 & $o11 & $o21 ) | ( $o02 & $o12 & $o22 ) ))
odiags=$(( ($o00 & $o11 & $o22) | ( $o02 & $o11 & $o20 ) ))
owins=$(( $orows | $ocols | $odiags ))
#echo "$ocols $orows $odiags $owins"

end_of_game=false
while [ true ]
do
	echo "$player1 - изберете поле (ред,колона): "
	valid=0
	while [ "$valid" -eq 0 ]
	do

		read player1_move
		row=$(expr substr "$player1_move" 2 1)
		col=$(expr substr "$player1_move" 4 1)

		validate_move "$row" "$col" 1
		valid=$?

		if [ "$valid" -ne 1 ] 
		then
			echo "Невалидна позиция. Моля въведете отново: "
		fi
	done

	echo "$player2 - изберете поле (ред,колона): "
	valid=0
	while [ "$valid" -eq 0 ]
	do

		read player2_move
		row=$(expr substr "$player2_move" 2 1)
		col=$(expr substr "$player2_move" 4 1)

		validate_move "$row" "$col" 2
		valid=$?

		if [ "$valid" -ne 1 ] 
		then
			echo "Невалидна позиция. Моля въведете отново: "
		fi
	done
	echo "valid"
	check_for_end
done
