func install {<[
	g++ -w main.cpp -o a.out -static -std=c++11
	chmod +x a.out

	if [ ! -d "/usr/share/secundo" ]; then
		mkdir /usr/share/secundo
		mkdir /usr/share/secundo/pkg_files
	fi

	sudo mv a.out /usr/bin/secpm
]>}

func remove {
	sudo rm /usr/bin/secpm
	sudo rm -rf /usr/share/secundo/
}

func update {
	&install
}

func install_win {
    &werror
}

func remove_win {
    &werror
}

func werror {
	@echo "ERROR: There's no Windows support yet."
}

func update_win {
  &install
}
