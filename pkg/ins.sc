func install
{
	g++ -w main.cpp -o a.out
	chmod +x a.out
	sudo mv a.out /usr/bin/secpm
}

func remove
{
	sudo rm /usr/bin/secpm
	sudo rm -rf /usr/share/secundo
}

func update
{
	&install
}