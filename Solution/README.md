
# Maths_Physique_JV_ProjetSession
Construction d’un moteur physique de jeux vidéo
Bienvenue sur la deuxième phase du projet de construction d’un moteur physique de jeux vidéo.

Le groupe est composé de Camille BENOIT, Clara FERRU et Ilona PELTIER

### PREREQUIS POUR LANCER LE PROGRAMME
* Avoir CMake

   * lien d'installation: https://github.com/Kitware/CMake/releases/download/v3.17.1/cmake-3.17.1-win64-x64.msi
   
 
* Si vous ne l'avez pas ->télecharger et installer MS Visual Studio Community Edition (free for students): https://visualstudio.microsoft.com/downloads/

    * Instructions de télechargement ici: https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2019
    

### Créer la solution Visual Studio . 

Ces étapes vous permettent de créer le project à ouvrir dans VS:

* Extraire le code à l'intérieur d'un dossier. 

* Ouvrir un terminal et aller dans le dossier.

* Executer:

  * 'md build'
  
  * 'cd build'
  
  * 'cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE:STRING=Release ..'
  
  * 'dir'
  
*** Si vous n'avez pas de terminal -> Créer un dossier build
Ouvrir Cmake , source code : le dossier , where to build : dossier/build , choisir comme Generator: Visual Studio 16 2019.
Appuyer sur configure puis sur Generate ***

* Vous devriez trouver un fichier nommé 'MathsPhysique.sln' dans le dossier build


### Compiler, build et lancer

* Ouvrir 'MathsPhysique.sln' dans VS

* build la solution (**Build Solution** from the **Build menu**)

* Depuis le dossier, copier 'freeglut\bin\x64\freeglut.dll' dans 'build'

* Executer le code

  * Selectionner le projet main, faire un click droit dessus et sélectionner **Set as Startup Project** 
  
  * Puis choisir sur la barre du menu **Debug** -> **Start debuggin**

### Comment jouer 
Vous pouvez choisir entre le jeu 1 ou 2
* Pour le jeu 1 :
Vous pouvez lancer des projectiles en appuyant sur espace, mais aussi faire rotater la caméra avec les touches directionnelles. 
Appuyez sur la touche A pour changer de projectile.
* Pour le jeu 2:
Vous pouvez déplacer le blob avec les touches W,A,S,D ou les touches directionnelles.
* Pour le jeu 3:
Appuyez sur la touche espace pour lancer un cube.
* Pour le jeu 4:
Appuyez sur la touche espace pour lancer une simulation d'accident de voitures.