# Secundo Package Manager
There's an english translation at the end of the page.

# DE - Deutsch

**Disclaimer:** Ich übernehme keine Haftung für Beschädigung von Daten oder deren Verlust. Außerdem distanziere ich mich von allen Projekten, die SecundoPM als Paketmanager benutzen und nicht in den GitHub-Accounts von https://github.com/triploit/ oder https://github.com/survari/ enthalten sind. Jeder, der diesen Paketmanager benutzt, tut dies mit **eigener Verantwortung.** 

Ihr habt ein supertolles Tool entwickelt, das Usern helfen soll, aber keine Ahnung wie ihr es ihnen bereit stellt?

Hier ist die Lösung! Um aufwendiges Kompilieren und verschieben von Dateien nicht dem User zu überlassen, habe ich einen einfachen Paketmanager gebaut.

Lasst uns ihn folgendermaßen auf Linux installieren:
```bash
git clone https://github.com/triploit/secundo-pm
cd secundo-pm
cmake .
make
./secpm install triploit:secundo-pm
cd ..
rm -rf secundo-pm
```

**Offiziell gibt es keinen Windows-Support.** Zwar stehen alle Funktionen dazu bereit, doch habe ich zu wenige Kentnisse um in meine Projekte und SecPM orgentliche Build-Dateien für Windows einzubauen.

## Wie man ein Paket erstellt

Und hier wird man auch gleich sehen, warum der Disclaimer oben existiert.

Möchte man nun sein GitHub-Projekt in ein SecundoPM Paket umwandeln, muss ein Ordner mit dem Namen "pkg" im Wurzelverzeichnis des Projektes angelegt werden. In diesem Ordner wird nun eine Datei angelegt, mit dem Namen "ins.sc".
Das muss dann so aussehen:
```
meinprojekt
├── main.cpp
├── main.hpp
└── pkg
    └── ins.sc
```

In diese Datei kommen nun das Installer-Skript rein.
Schreiben wir mal folgendes:
```
func install {
    echo "Kompiliere  ..."
    g++ main.cpp -o programm
    echo "Installiere ..."
    sudo mv programm /usr/bin/programm
    echo "Fertig !"
}

func update {
    &install
}

func install_win {
    &werror
}

func update_win
{
    &install_win
}

func remove_win {
    &werror
}

func werror {
    @echo "Leider gibt es keinen Windows-Support."
}
```
So, was wir hier sehen ist also eine einfache Form des Skriptes. Wir haben verschiedene Funktionen definiert. Funktionen in SC (SeCundo Script, ja eigentlich SCS,  aber jetzt egal :smile: ) können keine Argumente oder Parameter entgegennehmen. Weiterhin ist es möglich Funktionen aufzurufen, indem man in einer leeren Zeile `&funktionsname` schreibt.

Funktionen, die als Standart erwartet werden, sind (auf Linux):
* `install`    - Zum Installieren von Paketen
* `update`    - Zum Aktualisieren von Paketen
* `remove`    - Zum Löschen von Paketen

Auf Windows heißen die Funktionen ähnlich: Sie haben nur ein `_win` (z.B. `install_win`) am Ende dran (auch im Beispiel).

Wenn wir uns das Skript nun weiter anschauen, fällt folgendes auf: Shellbefehle.
In den Funktionen stehen Shellbefehle. In `_win` Funktionen müssen also CMD-Befehle stehen und in Linux-Funktionen Bash-/Shellbefehle. Und daher auch der Disclaimer. SecPM fragt zwar vor dem installieren, ob man die Skript-Datei vorher sehen will, jedoch installiert man immer auf **eigene Gefahr**.

Wichtig ist hier noch zu sagen: Die Funktionen sind kein Shellscript. Sie werden zeilenweise unabhängig voneinander ausgeführt.

Wenn ihr Variablen und ein eigenes Shellscript nutzen wollt, geht das folgendermaßen:

```
func install {
    <[
        echo "Dies ist ein vollwertiges Shellscript!";
        i="Hallo Welt!";
        echo $i;
    ]>
}
```

Alles was in `<[ ... ]>` steht, wird als eine komplette Datei ausgeführt.
Verkürzt geht das natürlich auch so:

```
func install {<[
    echo "Dies ist ein vollwertiges Shellscript!";
    i="Hallo Welt!";
    echo $i;
]>}
```

Außerdem ist es möglich Abhängikeiten zu definieren. Beispielsweise benötigt das Projekt aml_server das Paket aml, um zu funktionieren. Da aml und aml_server beides SecPM-Pakete sind, können wir einfach folgendes machen: Wir schreiben am Anfang der Installer-Datei folgendes:

```
dep triploit:aml
```

`dep` steht für "Dependency", was "Abhängigkeit" bedeutet. Wie bei der Nutzung von SecPM gilt bei den Paketnamen: user:projekt. 
aml_server ist daher von aml Abhängig. Ist das Programm aml dann nicht installiert, installiert SecPM dieses. Wenn man mehrere Abhängigkeiten hat, kann man folgendes machen:

```
dep user:projekt1
dep user:projekt_abc
dep user_b:projekt5e
...
```

## Pakete installieren, entfernen, ...

### Installation

```
sudo secpm install triploit:aml
```
Das Paket https://gitub.com/triploit/aml wird installiert.

```
sudo secpm ins triploit:aml ins triploit:tsmi
```
Abkürzung für "install" ist "ins". Die Pakete https://github.com/triploit/aml und https://github.com/triploit/tsmi  werden installiert.

```
sudo secpm install mustermax:projekt
```
Das Paket https://github.com/mustermax/projekt wird installliert.

### Entfernen

```
sudo secpm remove triploit:aml
```
Das Paket https://gitub.com/triploit/aml wird entfernt.

```
sudo secpm rem triploit:aml rem triploit:tsmi
```
Abkürzung für "remove" ist "rem". Die Pakete https://github.com/triploit/aml und https://github.com/triploit/tsmi werden entfernt.

```
sudo secpm rem mustermax:projekt
```
Das Paket https://github.com/mustermax/projekt wird entfernt.

### Installieren von lokalen Paketen

```
sudo secpm local /pfad/zum/projekt/
```
Der Ordner `/pfad/zum/projekt/` wird installiert. Das Skript `/pfad/zum/projekt/pkg/ins.sc` wird ausgeführt.

### Leuten vertrauen

Da jedes Paket eine potentielle Gefahr ist, fragt SecPM ob man das Installer-Script vor dem Installieren ansehen möchte und fragt danach noch einmal, ob man sicher ist, dass man das Paket installieren kann. Es gibt nun die Möglichkeit, für bestimmte Organisationen oder GitHub-Accounts, denen man wirklich vertrauen sollte, diese Nachrichten auszuschalten:

```
sudo secpm trust user
```

Ich, zum Beispiel, vertraue mir selbst :D

```
sudo secpm trust survari trust triploit
```

Um einen Nutzer von der Liste vertrauenswürdiger Personen zu entfernen, gibt es:

```
sudo secpm untrust user
```

Alle Leute anzeigen, denen man vertraut:

```
sudo secpm showtrust
```

## EN - English

**Disclaimer:** I assume no liability for damaged data or their loss. As well I dissociate myself from all projects, which use SecundoPM as a package manager and aren't properity of https://github.com/triploit/ or https://github.com/survari/. Everyone, who uses this package manager **does it on own risk.** 

So you created a nice tool for users but don't know how you should easily let them install it? To prevent the tricky compiling and moving of programs, i build an package manager for GitHub projects.

Let's install it. This is the hardest part:
```bash
git clone https://github.com/triploit/secundo-pm
cd secundo-pm
cmake .
make
./secpm install triploit:secundo-pm
cd ..
rm -rf secundo-pm
```

**Officially there's no windows support yet.** Actually it can work on Windows and has all functions for this but I don't have the knowledge for Batch scripts and CMD for the installer files, which you will see in the next chapter.

## How to create a package

And here's, why I had written a disclaimer:

If you want to add SecundoPM support to your GitHub project, you have to create a directory with the nam "pkg" in the root-directory of the project. In this directory, you must create a file called `ins.sc`.
The directory tree have to look like this:
```
myproject
├── main.cpp
├── main.hpp
├── other.go
├── works_with_every_programming_language.py
└── pkg
    └── ins.sc
```
In this file (`ins.sc`), you have to write something like this:
```
func install {
    echo "compiling  ..."
    g++ main.cpp -o programm
    echo "installing ..."
    sudo mv programm /usr/bin/programm
    echo "finished !"
}

func update {
    &install
}

func install_win {
    &werror
}

func update_win
{
    &install_win
}

func remove_win {
    &werror
}

func werror {
    @echo "There's no Windows support in this project."
}
```
So, what you're seeing is an easy kind of the installer script. We define some functions. But functions in **S**e**C**undo (**`ins.sc`**) script can't have arguments or parameters. It's possible to call functions with `&functionname`.

Functions, expectet as standard (on Linux):
* `install`    - To install a package to your computer
* `update`    - To update a package on your computer
* `remove`    - To uninstall/remove a package from your computer

(On Windows functions are the same but they end with `_win` (eg. `install_win`) (like in the example).)

If you look throug the installer script, there's something special: shell commands.
In are shell commands. In `_win` functions you have to write CMD commands and in Linux functions (the 3 standard functions without `_win`) you have to write shell commands. And therefor: the disclaimer. SecPM asks if you want to see the installer script and if you really want to install this package, but you are installing packages  **at own risk**.

Important is: The functions aren't a complete shellscript. The script will be runned line by line. The commands are independent.

If you want to use a shell script and variables, you have to do this:

```
func install {
    <[
        echo "Dies ist ein vollwertiges Shellscript!";
        i="Hallo Welt!";
        echo $i;
    ]>
}
```

Everything that is in `<[ ... ]>`, will be runned as a complete file.
This is also possible:

```
func install {<[
    echo "Dies ist ein vollwertiges Shellscript!";
    i="Hallo Welt!";
    echo $i;
]>}
```

Also it's possible to define dependencies. For example: The project aml_server needs the package aml to work. Because both are SecPM packages, it's possible to add this at the top of the installer file:

```
dep triploit:aml
```

`dep` means "dependency". Like down below, the rule is: user:project.
Is the program aml not installed, SecPM will install it. When you have more than one dependencies, you can write this:

```
dep user:project1
dep user:project_abc
dep user_b:project5e
...
```

## Installing, updating and removing packages

### Installation

```
sudo secpm install triploit:aml
```
The package https://gitub.com/triploit/aml will be installed.

```
sudo secpm ins triploit:aml ins triploit:tsmi
```
Shortcut for "install" is "ins". The packages https://github.com/triploit/aml and https://github.com/triploit/tsmi  will be installed.

```
sudo secpm install mustermax:project
```
The package https://github.com/mustermax/project will be installed.

### Removing

```
sudo secpm remove triploit:aml
```
The package https://gitub.com/triploit/aml will be removed.

```
sudo secpm rem triploit:aml rem triploit:tsmi
```
Shortcut of "remove" is "rem". The packages https://github.com/triploit/aml and https://github.com/triploit/tsmi will be removed.
```
sudo secpm rem mustermax:projekt
```
The package https://github.com/mustermax/project will be removed.

### Installing of local directories

```
sudo secpm local /path/to/project/
```
The package directory `/path/to/project/` wird installiert. Das Skript `/pfad/zum/projekt/pkg/ins.sc` wird ausgeführt.

### Trust people
Since every package is a potential hazard, SecPM asks some questions before installing the package (like: `Do you want to see the script file?` or `Are you really sure?`). But theres a possibility to trust GitHub accounts (eg. from friends or your own). But you have to be **really sure**, because if the package contains dangerous code, SecPM won't ask.
```
sudo secpm trust user
```

I'm trusting myself :D

```
sudo secpm trust survari trust triploit
```

Remove a person from trusted users:

```
sudo secpm untrust user
```

Show the list of people, you are trusting:

```
sudo secpm showtrust
```
