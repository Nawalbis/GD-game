# Geometry Dash en C/SDL2

Jeu de plateforme 2D développé en C avec SDL2. Le joueur contrôle un cube qui doit éviter obstacles et pièges à travers 3 niveaux de difficulté croissante.

## Description

GD game est un projet de jeu vidéo développé en C avec la bibliothèque SDL2. Le jeu reproduit les mécaniques de Geometry Dash : un cube qui avance automatiquement et doit sauter pour éviter les obstacles. Ce projet m'a permis de maîtriser la programmation graphique, la détection de collisions et l'architecture modulaire.

## Niveaux

- Niveau 1 (Facile) : Introduction progressive au jeu avec obstacles espacés
- Niveau 2 (Moyen) : Rythme plus soutenu avec plateformes et sauts précis
- Niveau 3 (Difficile) : Parcours technique avec obstacles rapprochés et sections complexes

## Fonctionnalités

- Menu de sélection des niveaux avec navigation par flèches
- Scrolling automatique fluide avec fonds en boucle
- Système de physique (gravité + saut)
- Détection de collisions directionnelle (verticale vs latérale)
- Musique de fond
- Sprite de victoire en fin de niveau
- 3 niveaux avec difficulté progressive



## Technologies

- Langage : C 
- Graphique : SDL2
- Images : SDL2_image (PNG)
- Audio : SDL2_mixer
- Compilation : GCC / Make
- Architecture : Modulaire (8 fichiers sources)

## Installation
```
Sur Mac (Homebrew):
    brew install sdl2 sdl2_image sdl2_mixer
Sur Debian:
    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev


git clone https://github.com/votre-username/geometry-dash.git
cd geometry-dash
make

./geometry_dash
```



## Structure
```
geometry-dash/
├── src/                    # Code source
│   ├── main.c             # Boucle principale du jeu
│   ├── cube.c             # Gestion du personnage
│   ├── obstacles.c        # Définition des obstacles par niveau
│   ├── background.c       # Gestion des arrière-plans
│   ├── levels.c           # Chargement des fonds de niveau
│   ├── jeu.c              # Logique du scrolling
│   ├── menu.c             # Menu de sélection
│   ├── audio.c            # Gestion de la musique
│   └── win.c              # Écran de victoire
├── include/               # Headers (.h)
├── assets/                # Ressources
│   └── images/
│       ├── backgrounds/   # Fonds d'écran
│       ├── obstacles/     # Sprites des obstacles
│       └── player/        # Sprite du cube
├── screenshots/           # Captures d'écran
├── Makefile              # Compilation
└── README.md             # Ce fichier
```

## Utilisation

1. Lancer le jeu avec ./geometry_dash
2. Utiliser les flèches gauche/droite pour choisir un niveau (1, 2 ou 3)
3. Cliquer sur Play pour commencer
4. Appuyer sur Espace pour sauter et éviter les obstacles
5. Atteindre le triangle de fin pour gagner le niveau

## Auteur

BISIAUX Nawal - Projet réalisé dans le cadre de ma formation en école d'ingénieur