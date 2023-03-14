# Darwin's Odyssey
PROJET LIFAPCD : Jeu sous la forme de 2D Platformer en coop (2 joueurs sur un même ordinateur). Il faudra résoudre des énigmes pour retracer l’évolution de l’homme.

Bienvenue dans Darwin's Odyssey, le projet final de Césaire Viegas (p2109844) et Jofre Coll (p2105932)

Pour compiler sur Linux:

## Avant de complier, vous devez d'abord "Update and install the compiler, related build tools, and libraries required to build PixelGameEngine applications."

### Ubuntu:
sudo apt update
sudo apt install build-essential libglu1-mesa-dev libpng-dev

### Arch Linux:
sudo pacman -Sy
sudo pacman -S gcc glibc libpng mesa

### Fedora 34:
sudo dnf groupinstall "Development Tools" "Development Libraries"
sudo dnf install gcc-c++ glew-devel glm-devel libpng-devel

## Après cela, vous pouvez compiler.

make

## Pour executer:
./exemple
