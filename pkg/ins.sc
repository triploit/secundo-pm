name secundo-pm
user triploit
ver 0.1.7.4

func install {<[
	# this = this package installer file
	# a = already installed package file (if exists)

	this_version="${this_major}.${this_minor}.${this_revision}.${this_build}"
	old_version="${a_major}.${a_minor}.${a_revision}.${a_build}"

	echo ">> [${method}] Installing SecPM version ${this_version} ..."

	if [ $old_version = "0.0.0.0" ]; then
		if [ $method = "local" ]; then
			echo ">> Okay... Installing from local directory... I'm ready..."
		else
			echo ">> First installation of SecPM. Here it comes!"
		fi
	elif [ $old_version = $this_version ]; then
		echo ">> Okay... Let's install the same version (old is ${old_version}, this is ${this_version}) of the same package ...?"
	else
		dwg="false"

		if [ "$this_major" -lt "$a_major" ]; then
			dwg="true"
		elif [ "$this_minor" -lt "$a_minor" ]; then
			dwg="true"
		elif [ "$this_revision" -lt "$a_revision" ]; then
			dwg="true"
		elif [ "$this_build" -lt "$a_build" ]; then
			dwg="true"
		fi

		if [ $dwg = "true" ]; then
			echo ">> This is impossible! That would be a downgrade!"

			while [ ! "$yn" = "y" ] && [ ! "$yn" = "n" ]; do
				read -p "Do you want that? [y/n] > " yn
			done

			if [ "$yn" = "y" ]; then
				echo ">> Okay."
			else
				echo "Pleasy, Mr. SecPM! Pleasy don't save the SC-Script!" > dont_save_sc.tmp
				exit
			fi
		else
			echo ">> Updating from version ${old_version} to ${this_version}"
		fi
	fi

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
