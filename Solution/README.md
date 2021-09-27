# Maths_Physique_JV_ProjetSession
Construction d’un moteur physique de jeux vidéo
Bienvenue sur la première phase du projet de construction d’un moteur physique de jeux vidéo.

Le groupe est composé de Camille BENOIT, Clara FERRU et Ilona PELTIER

COMMENT LANCER LE PROGRAMME :

Pour compiler et faire fonctionner notre programme, allez dans le dossier "Solution" et ouvrez avec votre IDE le fichier "Math_Physique_JV_ProjetSession.sln".
Une fois ouvert, vérifiez que l'active solution platform est réglée à x86.

Vous avez ensuite juste à runner et le jeu se lancera automatiquement.

Les dépendances relatives à glut et OpenGL sont déjà ajoutées à la solution du projet. 
Cependant si vous avez une erreur en rapport avec les dépendances de glut, consultez la page de propriétés pour ajouter les dépendances. 
Pour cela, allez dans "Debug" > "Maths_Physique_JV_ProjetSession property" puis dans "linker" > "input" dans le champ "Additional Dependencies", 
ajoutez les trois dépendances opengl32.lib, glu32.lib, glut32.lib de cette manière :
opengl32.lib;glu32.lib;glut32.lib;%(AdditionalDependencies)

COMMENT JOUER AU JEU :

Vous pouvez lancer des projectiles en appuyant sur espace, mais aussi faire rotater la caméra avec les touches directionnelles. 
Appuyez sur la touche A pour changer de projectile.