# DungeonAutoBattle

## Description

DungeonAutoBattle est un mini-jeu de combat automatique développé en C++, inspiré des jeux de type auto-battle et RPG.
Le jeu met en scène des héros aux classes différentes, chacun possédant ses propres statistiques, compétences et mécaniques de combat.

Deux joueurs s’affrontent avec des équipes de héros générées aléatoirement. Les combats se déroulent sans intervention du joueur, uniquement selon les statistiques, la vitesse et les capacités spéciales de chaque héros.

## Fonctionnalités

* Génération aléatoire de héros avec statistiques variables
* Plusieurs classes de héros avec comportements uniques :
* Guerrier, Mage, Archer, Paladin, Assassin, Druide
* Système de combat automatique tour par tour
* Gestion des effets : saignement, brûlure, bouclier, régénération, esquive et coups critiques
* Combat individuel entre deux héros
* Combat d’équipes (3 héros contre 3 héros)
* Restauration automatique des PV du vainqueur après chaque duel
* Sécurité contre les boucles infinies (limite de tours)

## Compilation

* Compilation avec g++
`g++ -o DungeonAutoBattle main.cpp`
* Exécution
`./DungeonAutoBattle`

## Exemple de sortie

Équipe de Imane :
Guerrier PV : 92 Attaque : 61 Defense : 88 Vitesse : 54
Mage PV : 78 Attaque : 95 Defense : 56 Vitesse : 70
Archer PV : 84 Attaque : 73 Defense : 59 Vitesse : 92

Équipe de Saci :
Paladin PV : 101 Attaque : 65 Defense : 80 Vitesse : 50
Assassin PV : 66 Attaque : 98 Defense : 54 Vitesse : 85
Druide PV : 89 Attaque : 70 Defense : 67 Vitesse : 60

Combat entre : Imane (Héros : 1) et Saci (Héros : 1)
Imane remporte ce duel !

Combat terminé !
Imane gagne le combat d'équipes !


## Classes Principales

- **`Hero`**: Classe de base abstraite qui représente tous les héros, contenant les attributs et méthodes communs. Les attributs incluents les points de vie, l'attaque, la défense, et la vitesse.
- **`Guerrier`**, **`Mage`**, **`Archer`**, **`Paladin`**, **`Assasin`**, **`Druide`**: Classes dérivées représentant les différents types de Héro, avec des méthodes spécifiques et rédéfinies pour chaque type, pour calculer les multiplicateurs de dégâts en fonction des types.
- **`Joueur`**: Classe représentant un joueur avec une équipe de héros. Permet l'ajout de Héro, la sélection de l'équipe pour les combats et le suivi des victoires et des défaites.

## Utilisation

1. Lancer le programme
2. Deux joueurs sont créés automatiquement
3. Chaque joueur reçoit une équipe aléatoire de héros
4. Les équipes sont affichées
5. Les combats se lancent automatiquement jusqu’à la victoire d’un joueur