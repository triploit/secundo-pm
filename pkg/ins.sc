name secundo-pm
user triploit
ver 0.1.6.0

func install {<[
    cmake .
    make
	chmod +x secpm

	if [ ! -d "/usr/share/secundo" ]; then
		mkdir /usr/share/secundo
		mkdir /usr/share/secundo/pkg_files
	fi

	sudo mv secpm /usr/bin/secpm
]>}

func remove {
	sudo rm /usr/bin/secpm
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
