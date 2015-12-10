Pour avoir OpenGL, GLEW et GLUT sur VisualStudio, il faut aller dans 
Tools -> Library Package Manager -> Package Manager Console.

Écrire la commande Install-Package nupengl.core

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