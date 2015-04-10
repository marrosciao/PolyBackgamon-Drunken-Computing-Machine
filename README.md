# PolyBackgammon
Backgamon game with an IA using SDL

It's a project for 3rd year in IT ingeneering school with C programming language.

## Auteurs
### Partie graphique / arbitre
BONNEVALLE Vincent - Logique arbitre
LABAT Jean - Affichage graphique

### Partie AI
FOURRIER Mikaël - Generation de toutes les possibilités & création d'une ArrayList
FRANCO Andrès - Implémentation de l'algorithme d'intelligence

## Installation
Compilation de l'interface uniquement :
```
$ DEBUG=0 make interface
```
Compilation de l'IA uniquement :
```
$ DEBUG=0 make strategy
```
Compilation des 2 à la fois
```
$ DEBUG=0 make
```

L'interface se trouve à interface/bin/PolyBackgammon après compilation.
La librairie de strategie se trouve à strategy/bin/libpote.so après la compilation
## Utilisation
/!\ Actuellement, les matchs humain contre humain ne sont pas gérés. Il y a donc
au moins une IA parmis les participants.
```
$ ./interface/bin/PolyBackgammon [nombre-de-points] [chemin-vers-ai1] [chemin-vers-ai2]
```
Lorsqu'aucune IA n'est précisée, cela lancera un match humain contre humain. Si il n'y a pas de parametre nombre-de-points utilisé, le programme utilisera une valeur par défaut. Si une seule IA est precisée, un humain devrait jouer contre l'IA. Si deux IA sont en paramètre, elles se battront en duel jusqu'à ce que victoire s'en suive.

nombre-de-points doit etre une valeur positive non nulle. Cela indique le nombre de points nécessaires pour gagner le set de match, cela d'indique PAS le nombre de matchs joués au total par les deux IA.

Note : Si vous executez 2 fois la même IA avec le même fichier, leurs variables globales seront partagées
Si vous souhaitez qu'une IA affronte son double, il faut donc copier l'IA dans un dossier temporairement
Exemple :
```
$ cp ./strategy/bin/libpote.so /tmp/lib.so
$ ./interface/bin/PolyBackgammon 15 /tmp/lib.so ./strategy/bin/libpote.so
```
Dans cet exemple l'IA se battra contre elle même sur autant de matchs qu'il faudra, jusqu'à ce qu'une des deux IA ait 15 points.

## Particularité
### IA

L'IA marche sur un algorithme très simple mais très efficace et connu depuis de nombreuses années : l'algorithme alpha-beta, une version améliorée de l'algorithme minimax

Le principe est de calculer, à partir d'un état de jeu donné (celui dans lequel l'IA est en ce moment), toutes les possibilités disponibles. à partir de ces possibilités, on obtient encore des états de plateau, d'où on peut calculer encore toutes les possibilités, du point du vue du joueur adverse.
On peut continuer cette étape p fois; on apelle p la profondeur. Quand on arrive à la p-ieme étape, on s'arrete et on donne une valeur réelle ou entière représentant l'état du joueur vis à vis du plateau de jeu. Une valeur élevée et positive équivaudra à un avantage pour le joueur, tantdis qu'une valeur faible ou négative équivaudra à un désavantage pour le joueur.
Bien entendu, notre objectif serait que la valeur de la p-ieme étape devrait etre la plus haute possible, sans pour autant qu'il n'y ait de risque que l'on perde en parcourant ce chemin du au fait que l'ennemi aurait choisi les bons mouvements pour nous contrer. L'algorithme minimax s'assure de minimiser les gains de l'adverse et de maximiser lorsque ce n'est pas un compromis de risque.

L'algorithme alpha beta est exactement le meme que minimax, excepté une amélioration : lorsque l'on voit que l'on commence à calculer un branche dont le résultat pour nosu est plus faible qu'une branche voisine, on abandonne le calcul de cette branche. De la meme manière, si on commence à calculer une branche où les gains de l'adversaire sont plus grands que ceux calculés dans une autre branche, on arrete le calcul de cette branche (de toute manière on n'aurait pas choisi cette branche, donc pourquoi la calculer ?)

Il faut etre en revanche prudent en choisissant la profondeur de cet algorithme, car sans les optimisations nécessaires, une profondeur de 2 peut tout de meme durer jusqu'à quelques secondes (par ex dans le cas d'un double dé pour le backgammon).
Les optimisations peuvent etre les suivantes :
* Ajout d'options de compilation permettant l'accélération de l'éxecution
* Filtrage des résultats doubles ( par exemple, si on a comme dés 4 et 3, bouger un pion de 1 à 8 est la meme chose si on utilise les dés 4 puis 3 ou 3 puis 4 s'il n'y a pas de pion adverse sur 4 ou 5)
* Envoyer les structures par pointeur à la place de par valeur lorsque possible : sur un petit programme il n'y a aucune différence, mais sur ~2000 * ~2000 appels récursifs, la différence peut se sentir

### Interface

Les textures des pions sont basés sur de l'acajou (en fait j'en sais rien)

