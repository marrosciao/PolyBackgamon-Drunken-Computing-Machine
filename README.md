# PolyBackgammon
Backgamon game with an IA using SDL

It's a project for 3rd year in IT ingeneering school with C programming language.

## Auteurs
### Partie graphique / arbitre
BONNEVALLE Vincent - Logique arbitre

LABAT Jean - Affichage graphique

### Partie AI
FOURRIER Mikaël - Generation de toutes les possibilités & création d'une ArrayList

FRANCO Andrès - Implémentation de l'algorithme alphabeta

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

```
$ ./interface/bin/PolyBackgammon [nombre-de-points] [chemin-vers-ai1] [chemin-vers-ai2]
```
Si les deux chemins sont précisés, le match se déroule entre les deux IA. Si un
seul chemin est précise, l'IA affronterai un joueur humain. Sinon, il s'agit
d'un match humain contre humain.

nombre-de-points doit etre une valeur positive non nulle. Il s'agit du nombre de points nécessaires pour gagner le set de match, et non du nombre de matchs joués au total par les deux IA.

Note : Si vous executez 2 fois la même IA avec le même fichier, leurs variables globales seront partagées
Si vous souhaitez qu'une IA affronte son double, il faut donc copier l'IA dans un dossier différent.
Exemple :
```
$ cp ./strategy/bin/libpote.so /tmp/lib.so
$ ./interface/bin/PolyBackgammon 15 /tmp/lib.so ./strategy/bin/libpote.so
```
Dans cet exemple l'IA se battra contre elle même dans une partie en 15 points.

## Particularités
### IA

L'IA marche sur un algorithme très simple mais très efficace et connu depuis de nombreuses années : l'algorithme alpha-beta, une version améliorée de l'algorithme minimax.

Le principe est de calculer, à partir d'un état de jeu donné (celui dans lequel l'IA est en ce moment), toutes les possibilités disponibles. À partir de ces possibilités, on obtient encore des états de plateau, d'où on peut calculer encore toutes les possibilités, du point du vue du joueur adverse.
On peut continuer cette étape p fois; on appelle p la profondeur. Quand on arrive à la p-ieme étape, on s'arrête et on donne une valeur kentière représentant l'avantage du joueur sur son adversaire. Une valeur élevée et positive équivaut à un avantage pour le joueur, tantdis qu'une valeur faible ou négative équivaut à un désavantage pour le joueur.
L'objectif de cet objectif est de minimiser nos pertes, en choisisant le
mouvement qui les minimise.

L'algorithme alpha beta est une optimisation du minimax. Lorsque l'on voit que l'on commence à calculer un branche dont le résultat pour nous est plus faible qu'une branche voisine, on abandonne le calcul de cette branche. De la même manière, si on commence à calculer une branche où les gains de l'adversaire sont plus grands que ceux calculés dans une autre branche, on arrête le calcul de cette branche. De toute manière on n'aurait pas choisi cette branche, donc pourquoi la calculer ?

Il faut être prudent en choisissant la profondeur de cet algorithme, car sans les optimisations nécessaires, une profondeur de 2 peut tout de même durer jusqu'à quelques secondes (par ex dans le cas d'un double dé pour le backgammon).
Les optimisations peuvent etre les suivantes :
* Ajout d'options de compilation permettant l'accélération de l'exécution
* Filtrage des résultats doubles ( par exemple, si on a comme dés 4 et 3, bouger un pion de 1 à 8 est la meme chose si on utilise les dés 4 puis 3 ou 3 puis 4 s'il n'y a pas de pion adverse sur 4 ou 5)
* Envoyer les structures par pointeur à la place de par valeur lorsque possible : sur un petit programme il n'y a aucune différence, mais sur ~2000 * ~2000 appels récursifs, la différence peut se sentir

### Interface

Contrôles:

Action                                                       | Touche
-------------------------------------------------------------|------------------
Pour selectionner un pion                                    | [Clic gauche]
Pour poser un pion                                           | [Clic droit]
Annuler les coups joués ce tour                              | [BackSpace]
Valider son tour                                             | [Enter]
Accepter le videau, ou doubler le videau ( quand demandé )   | [o]
Refuser le videau, ou de doubler le videau ( quand demandé ) | [n]

Particularité: en humain contre humain, il sera demandé si on veut doubler le videau, puis, si le joueur veut doubler, il sera 
demandé instantanement si on accepte le videau, c'est évidement au joueur qui n'a pas doublé le videau de repondre.
Si votre coup est annulé, c'est que vous avez fait un coup invalide.


La partie inteface est séparée en deux sous parties : la partie interface graphique, et la partie arbitre.

La partie arbitre s'occupe de vérifier que les mouvements renvoyé par l'IA ou le joueur humain, sont correcte selon les règles du backgammon.

L'arbitre vérifie tout d'abord que le joueur dont c'est le tour peut et veux augmenter la mise. Il ne peut le faire que si il n'est pas le dernier joueur
a avoir doublé la mise. Si il double la mise, on demande a l'autre joueur si il veux suivre ou abandonner.
Ensuite, l'arbitre appelle l'IA (ou le joueur humain) pour lui demander les mouvements à effectuer, test si les mouvements sont valide, puis les effectue.
Pour qu'un mouvement soit valide, il faut que : 

* Si il y a une dame du joueur dans la barre , cette dame soit déplacé
* Le mouvement soit d'un distance égale a la valeur du dé (a part si le joueur essaie de sortir une dame)
* Le joueur utilise le maximum de dé possible
* La case de destination soit des dames du joueur, soit des au maximum une dame adverse (qui sera alors mangé)
* Si le joueur veut sortir une dame du plateau, il faut que :
  * toutes ses dames soit dans le dernier quart du plateau
  * que la dame à déplacer soit exactement à une distance de la fin égale à la valeur du dé ou qu'elle soit la plus loin de la fin

Une fois que toutes ces vérfications sont faites, l'arbitre effectue les mouvements demandé par le joueur et on passe au joueur suivant.
Si une condition n'est pas remplie, les mouvements sont annulés et on passe au joueur suivant.
Le joueur subit une pénalité, au bout de trois pénalité, le joueur est eliminé.


La partie interface graphique à deux utilités: Afficher le jeu, et permettre à des joueurs humains de jouer.
- Pour afficher le jeu, à chaque fois qu'un joueur à fait un deplacement ou qu'un dé est tiré, le main va actualiser l'affichage, en affichant le fond du jeu, puis en dessinant les pions et les dés par dessus.
- Pour avoir un joueur humain, nous avons la même fonction PlayTurn que pour une IA. Cependant, pour que le joeur puisse faire ses actions, il faut que la  partie que s'occupe de faire jouer les joueurs humains ait accès à l'interface graphique, il y a donc une fonction d'initialisation de plus: StartScreen.

Cette fonction permet de stocker une variable globale que gardera le screen.
Cette fonction renvoie egalement des pointeurs de fonctions vers les mêmes fonctions que les librairies d'IA,
ce qui permet à l'arbitre de ne plus faire de difference entre humain et IA.

Pour ce qui est du fonctionnenment de la fonction PlayTurn,
on attend un clic gauche de la part du joueur qui corresponde bien à une case ou il a un pion,
puis on attend un clic droit qui correspond à une case ou il peut aller.
On enregistre les point de depart et d'arrivé et on recommence.

Ce qui aurait pu être ajouté à cette interface, c'est le fait que quand un joueur humain fait une coup invalide, il puisse le rejouer au lieu
de se faire annuler son coup par l'arbitre.
Pour cela, on aurait pu utiliser les fonctions de l'arbitre pour analyser les coups du joueur avant de les transmettre.


