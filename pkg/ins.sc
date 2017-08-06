func install
{
	g++ -w main.cpp -o a.out -static -std=c++11
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

func install_win
{
    <[
        @echo off
        IF NOT EXIST "C:\Program Files (x86)\Triploit Software" (
            MKDIR "C:\Program Files (x86)\Triploit Software"
            ECHO Creating Triploit Software directory...
        ) ELSE (
            ECHO Program Directory exists...
        )

        IF NOT EXIST "bin" (
            mkdir bin
        )

        make
        echo Move executable....
        move ".\secpm.exe" "C:\Program Files (x86)\Triploit Software\"
        rmdir /s .\bin\
    ]>
}

func remove_win
{
    <[
        @echo off
        IF NOT EXIST "C:\Program Files (x86)\Triploit Software\secpm.exe" (
            ECHO Warning: There is nothing to remove.
        ) ELSE (
            ECHO Removing...
            del "C:\Program Files (x86)\Triploit Software\secpm.exe"
        )
    ]>
}

func update_win
{
  &install
}
