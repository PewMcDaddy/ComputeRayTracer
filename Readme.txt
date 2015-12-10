Cette application utilise un framework simple basé sur Glut pour générer un contexte OpenGL.  L'application est un lanceur de rayon implémenté sur GPU en utilisant un "compute shader".  La scène est un bloc transparent contenant un bloc opaque avec des faces de différentes couleurs.

Plusieurs fonctionnalités sont disponibles avec le clavier:

Bouger la caméra : Drag avec la souris pour tourner autour du bloc,
				   Roulette pour zoom-in, zoom-out

Mode Miroir: 'm' : active le mode mirroir
             'n' : augmente le nombre de réflexions par rayon
             'b' : diminue le nombre de réflexions par rayon

Indice de réfraction: '+/=' augmenter l'indice de réfraction
                      '-'   diminuer l'indice de réfraction



Infos sur les librairies graphiques nécessaires
===============================================

Pour avoir OpenGL, GLEW et GLUT sur VisualStudio, il faut aller dans 
Tools -> Library Package Manager -> Package Manager Console. 
Écrire la commande Install-Package nupengl.core

Ça devrait se faire tout seul après un clone à cause du fichier packages.config: à la première compilation, VS va installer les packages manquants.


Pour le faire sur linux il faut installer les versions "devel" des packages OpenGL, freeglut et glew ainsi que GLU.  Par exemple, sur Fedora:

yum install -y
				mesa-libGL
				mesa-libGL-devel
				mesa-libGLU
				mesa-libGLU-devel
				glew
				glew-devel
				freeglut 
				freeglut-devel

Sur OS X, ça va compiler, mais ça ne roulera pas parce que la version d'OpenGL n'est pas supportée.  Il serait surement possible de l'adapter, mais vu que c'est un devoir qui est déjà remis, je passe à autre chose.