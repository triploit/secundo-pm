name secundo-pm
user triploit
ver 0.1.7.1

func install {<[
	if [ ! -d "/usr/local/include/yaml-cpp" ]; then
		if [ ! -d "/usr/share/include/yaml-cpp" ]; then
			echo ">> INFO: Installing yaml-cpp library..."

			git clone https://github.com/jbeder/yaml-cpp
			cd yaml-cpp
			
			cmake .
			make
			sudo make install

			cd ..
			rm -rf yaml-cpp
		fi
	fi

    cmake .
    make
	chmod +x secpm

	if [ ! -d "/usr/share/secundo" ]; then
		mkdir /usr/share/secundo
	fi	
	
	if [ ! -d "/usr/share/secundo/conf" ]; then
		mkdir /usr/share/secundo/conf

		cp pkg/config.yml /usr/share/secundo/conf/
		cp pkg/trustings.conf /usr/share/secundo/conf/
	fi

	if [ ! -d "/usr/share/secundo/pkg_files" ]; then
		mkdir /usr/share/secundo/pkg_files
	fi

	if [ ! -d "/usr/share/secundo/lang" ]; then
		mkdir /usr/share/secundo/lang
	fi
	
	cp pkg/de.yml /usr/share/secundo/lang/
	cp pkg/en.yml /usr/share/secundo/lang/
	cp pkg/lat.yml /usr/share/secundo/lang/
	
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
