func install {<[
    cmake .
    make
	chmod +x secundo_pm

	if [ ! -d "/usr/share/secundo" ]; then
		mkdir /usr/share/secundo
		mkdir /usr/share/secundo/pkg_files
	fi

	sudo mv secundo_pm /usr/bin/secpm
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
