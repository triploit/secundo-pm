func main
{
	echo "START!"
	<[
		#!/bin/bash
		echo "Hallo Welt!"
		echo "Gib mir was: "
		read a;
		echo "Du hast \"$a\" gesagt!"
	]>
	echo "ENDE!"
}
