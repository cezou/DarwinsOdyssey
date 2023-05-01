
# Darwin's Odyssey
## PROJET LIFAPCD C++
Jeu C++ utilisant sous la forme de 2D Platformer en coop (2 joueurs sur un même ordinateur). Il faudra résoudre des énigmes et réussir des mini-jeux pour retracer l’évolution de l’homme, suivant la théorie de Darwin.




## Fait par:

    	COLL Jofre P2105932 
    	VIEGAS Césaire P2109844

    


## Organisation des fichiers :

    	src : ce dossier contient les fichiers sources du projet: 
            - Map.h et Map.cpp pour la classe Carte
            - Player.h et Player.cpp pour la classe Joueur, 
            - Ennemi_Fish.h et Ennemi_Fish.cpp pour la classe Ennemi_Fish,
            - Menu.h et Menu.cpp pour le Menu Pause.
    	bin : ce dossier contient les exécutables test2regression et darwin.
    	obj : ce dossier contient les fichiers .o générés par la compilation des fichiers sources. On y trouve Map.o, Player.o, mainTest2Regression.o, et mainDarwin.o.
    	data : ce dossier contient les images utilisées comme "Decal" (Sprite utilisé par le GPU) dans le jeu.
    	doc : ce dossier contient la documentation Doxygen du module.
    
## Compilation et executution:

### Compiler sous Linux:
Avant de compiler, il faut installer les dépendances suivantes pour utiliser olcPixelGameEngine:
### Ubuntu:
```bash
sudo apt update
sudo apt install build-essential libglu1-mesa-dev libpng-dev
```
### Arch Linux:
```bash
sudo pacman -Sy
sudo pacman -S gcc glibc libpng mesa
```
### Fedora:
```bash
sudo dnf groupinstall "Development Tools" "Development Libraries"
sudo dnf install gcc-c++ glew-devel glm-devel libpng-devel
```

Pour compiler le projet, il suffit d'exécuter la commande "make" à partir de la racine du projet. Cette commande générera les fichiers .o dans le dossier obj, les exécutables dans le dossier bin. Pour executer il faut juste taper le nom du fichier qu'on veut executer (ex: ./bin/test2regression)
	
	L'executable ./bin/test2regression execute le test de regression qui verifie que le module marche bien
	L'executable ./bin/darwin est le jeu Darwin's Odyssey qui execute le main de mainDarwin.cpp
	
	
