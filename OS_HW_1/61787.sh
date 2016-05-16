#!/bin/bash

validate_move() {
	if [ "$1" -le 2 -a "$2" -le 2 -a "$1" -ge 0 -a "$2" -ge 0 ] 2>/dev/null #catch error
	then
		return 1
	fi
	return 0
}

echo "Име на играч 1 - O:"
read player1
echo "Име на играч 2 - X:"
read player2

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
o02=0
o10=0
o11=0
o12=0
o20=0
o21=0
o22=0

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

while [ true ]
do

	echo "Текущо състояние на играта: "
	echo "|$v00|$v01|$v02|"
	echo "|$v10|$v11|$v12|"
	echo "|$v20|$v21|$v22|"
	echo ""

	echo "$player1 - изберете поле (ред,колона): "
	valid=0
	while [ "$valid" -eq 0 ]
	do

		read player1_move
		row=$(expr substr "$player1_move" 2 1)
		col=$(expr substr "$player1_move" 4 1)

		validate_move "$row" "$col"
		valid=$?

		if [ "$valid" -ne 1 ] 
		then
			echo "Невалидна позиция. Моля въведете отново: "
		else
			val="v$row$col"
			tmp=${!val}
			if ! [ "$tmp" == " " ] 
			then
				echo "Невалидна позиция. На позицията вече има $tmp. Моля въведете отново: "
				valid=0
			fi
		fi				
	done

	#echo "$row $col"
	var="o$row$col"
	eval $var="1"
	val="v$row$col"
	eval $val="o"
	#echo "${!var}"

	orows=$(( ($o00 & $o01 & $o02) | ( $o10 & $o11 & $o12 ) | ( $o20 & $o21 & $o22 ) ))
	ocols=$(( ($o00 & $o10 & $o20) | ( $o01 & $o11 & $o21 ) | ( $o02 & $o12 & $o22 ) ))
	odiags=$(( ($o00 & $o11 & $o22) | ( $o02 & $o11 & $o20 ) ))
	owins=$(( $orows | $ocols | $odiags ))
	echo "$ocols $orows $odiags $owins"

	if [ "$owins" == "1" ]
	then
		echo "$player1 печели!"
		exit 0
	fi

	echo "Текущо състояние на играта: "
	echo "|$v00|$v01|$v02|"
	echo "|$v10|$v11|$v12|"
	echo "|$v20|$v21|$v22|"
	echo ""

	echo "$player2 - изберете поле (ред,колона): "
	valid=0
	while [ "$valid" -eq 0 ]
	do

		read player2_move
		row=$(expr substr "$player2_move" 2 1)
		col=$(expr substr "$player2_move" 4 1)

		validate_move "$row" "$col"
		valid=$?

		if [ "$valid" -ne 1 ] 
		then
			echo "Невалидна позиция. Моля въведете отново: "
		else
			val="v$row$col"
			tmp=${!val}
			if ! [ "$tmp" == " " ] 
			then
				echo "Невалидна позиция. На позицията вече има $tmp. Моля въведете отново: "
				valid=0
			fi
		fi
	done

	var="x$row$col"
	eval $var="1"
	val="v$row$col"
	eval $val="x"

	xrows=$(( ($x00 & $x01 & $x02) | ( $x10 & $x11 & $x12 ) | ( $x20 & $x21 & $x22 ) ))
	xcols=$(( ($x00 & $x10 & $x20) | ( $x01 & $x11 & $x21 ) | ( $x02 & $x12 & $x22 ) ))
	xdiags=$(( ($x00 & $x11 & $x22) | ( $x02 & $x11 & $x20 ) ))
	xwins=$(( $xrows | $xcols | $xdiags ))
	echo "$xcols $xrows $xdiags $xwins"

	if [ "$xwins" == "1" ]
	then
		echo "$player2 печели!"
		exit 0
	fi
done
