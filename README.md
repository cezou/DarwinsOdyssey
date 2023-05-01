
# Darwin's Odyssey
## PROJET LIFAPCD C++
Jeu C++ utilisant sous la forme de 2D Platformer en coop (2 joueurs sur un même ordinateur). Il faudra résoudre des énigmes et réussir des mini-jeux pour retracer l’évolution de l’homme, suivant la théorie de Darwin.



<br>

## Fait par:

    	COLL Jofre P2105932 
    	VIEGAS Césaire P2109844

    

<br>

# Sommaire:
- ### [Organisation des dossiers](#organisation-des-fichiers)
- ### [Compilation](#compilation-et-exécution)
- ### [Utilisation de Valgrind](#valgrind)
- ### [Manuel](#manuel-dutilisation-de-darwins-odyssey)

<br>







## Organisation des fichiers



- **src** : ce dossier contient les fichiers sources du projet: 
    - Map.h et Map.cpp pour la classe Carte
    - Player.h et Player.cpp pour la classe Joueur, 
    - Ennemi_Fish.h et Ennemi_Fish.cpp pour la classe Ennemi_Fish,
    - Menu.h et Menu.cpp pour le Menu Pause.
<br><br>
- **bin** : ce dossier contient les exécutables test2regression et darwin.
- **obj** : ce dossier contient les fichiers .o générés par la compilation des fichiers sources. On y trouve Map.o, Player.o,  mainTest2Regression.o, et mainDarwin.o.
- **data** : ce dossier contient les images utilisées comme "Decal" (Sprite utilisé par le GPU) dans le jeu.
- **doc** : ce dossier contient la documentation Doxygen du module.


<br>
    
## Compilation et exécution

## [Compiler sous Linux](https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Compiling-on-Linux):
Avant de compiler, il faut installer les dépendances de olcPixelGameEngine suivantes:
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
<br>

Pour compiler le projet, il suffit d'exécuter la commande "make" à partir de la racine du projet. Cette commande générera les fichiers .o dans le dossier obj, les exécutables dans le dossier bin. Pour executer il faut juste taper le nom du fichier qu'on veut executer (ex: ./bin/test2regression)
	
	L'executable ./bin/test2regression execute le test de regression qui verifie que le module marche bien
	L'executable ./bin/darwin est le jeu Darwin's Odyssey qui execute le main de mainDarwin.cpp
<br>

## Compiler sous Windows:

Pouvoir compiler sous plusieurs OS était un facteur du choix de la librairie olcPixelGameEngine. Ainsi, vous pouvez accéder au dossier Windows pour pouvoir lancer le fichier Darwin.exe sous Windows.

<br>

## Valgrind:
Nous avons testé le programme le plus simple possible avec la bibliothèque **olcPixelGameEngine**, et nous avons constaté qu'il y avait déjà beaucoup de memoryleaks. J'ai ainsi mit toutes ces erreurs dans un fichier de suppression grâce à cette [Documentation](https://wiki.wxwidgets.org/Valgrind_Suppression_File_Howto): 

Ainsi, vous pouvez taper cette commande qui utilise le fichier de suppression:
```bash
    valgrind --tool=memcheck --leak-check=full --suppressions=./fichier2suppressionvalgrind.supp ./darwin
```
<br>

## Manuel d'utilisation de Darwin's Odyssey

Nous avons suivi la théorie de l'évolution de **Darwin** pour créer ce jeu. Ainsi, vous allez commencer par incarner une cellule qui va devoir évoluer pour devenir un homme. (Primant qualité à la quantité, nous avons pour l'instant ces deux phases: **Cellule** et **Poisson**).

Pour cela, vous allez devoir résoudre des énigmes et réussir des mini-jeux.

### **Cellule**:

Vous devez devenir des cellules multi-cellulaires. Ainsi, il faut que vous récupériez vos cellules respectives dans l'environnement cellulaire labyrinthique. Mais attention, le joueur 1 voit uniquement les cellules à récupérer du joueur 2 et vice versa ! Vous devez donc communiquer pour vous retrouver. Pour que le joueur 1 (de l'écran gauche) récupère ses celulles, il doit se mettre à l'endroit où se situe une cellule, et utiliser la touche "E". Pour le joueur 2, la touche "SHIFT".

### **Poisson**:

Dans ce niveau on doit survivre entre différents poissons de différentes tailles qui passent à côté de nous. L'objectif est de manger les poissons plus petits pour devenir plus grand et finalement pouvoir sortir de l'eau. Vous devrez vous communiquer et jouer ensemble pour arriver à la fin car si un des deux n'a pas assez de points pour devenir plus gros et passer au suivant niveau, l'autre ne peut pas avancer. Alors, les deux joueurs seront toujours dans le même niveau et ils devront collaborer pour survivre.





























