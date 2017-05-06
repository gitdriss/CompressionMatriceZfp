CompressionMatriceZfp
===
Projet industriel Renault

INTRODUCTION
------------

Dans le cadre de notre formation d’ingénieur, nous participons à un projet pour le groupe Renault.
Le groupe industriel de construction automobile Renault s’est proposé comme client d’un projet, qui concerne la compression de données. En effet, le client est amené, dans le cadre d’une étude des écoulements à traiter des terraoctets de données qui sont très difficiles à stocker.
Le but du projet est donc de trouver une méthode pour compresser les matrices de données (matrice contenant des vecteurs avec la vitesse dans les 3 dimensions et la pression). L’objectif est de fournir un logiciel informatique avec une interface utilisateur de modulation des réglages. Ce logiciel permettrait le stockage des matrices 3D contenant des doubles correspondant à des données d’expériences aérodynamiques sur des voitures Renault.

INSTALLATION DE L'ENVIRONNEMENT
------------
- Developpement

Nous utilisons les bibliothèques standard en C/C++, de plus nous utilisons ces librairies


librairie cmake :

    sudo apt-get install cmake
    
librairie libxt-dev (utilisé par vtk):

    sudo apt-get install libxt-dev
    
librairie OPENGL_gl_LIBRAR (utilisé par vtk):

    sudo apt-get install libxext-dev
    sudo apt-get install libpng-dev
    sudo apt-get install libimlib2-dev
    sudo apt-get install libglew-dev
    sudo apt-get install libxrender-dev
    sudo apt-get install libxrandr-dev
    sudo apt-get install libglm-dev
    
librairie vtk (comptez quelques minutes pour la 5eme commande):

    Télécharger VTK-7.1.1 thttp://www.vtk.org/download/

    cd ~/Bureau
    mkdir vtkbuild
    cd vtkbuild
    cmake ~/Téléchargements/VTK-7.1.1/
    cmake --build .
    cmake --build . --target install

- Visualisation

Nous utilisons le logiciel paraview :

    http://www.paraview.org/download/
    v5.3
    Paraview Binary Installers
    Linux 64 bits
    ...
    Download

UTILISATION
------------
Il est nécessaire d'installer tout l'environnement pour l'utilisation (voir section précédente).

Compilation :

    cmake .
    make
    make -f Makefile2


Exécution :

    make run -f Makefile2
    make run2 -f Makefile2
    make run3 -f Makefile2


Clean :

    make clean -f Makefile2
    make clean2 -f Makefile2



Exécution Nouvelle version (en detail) :
------------
Données Gerris :

    ./exe 0 nouvelEssai.vti
    ./compress 0 matrixU.raw > compressed.zfp
    ./decompress 0 matrix2U.raw < compressed.zfp
    ./compress 0 matrixV.raw > compressed.zfp
    ./decompress 0 matrix2V.raw < compressed.zfp
    ./compress 0 matrixW.raw > compressed.zfp
    ./decompress 0 matrix2W.raw < compressed.zfp
    ./compress 0 matrixP.raw > compressed.zfp
    ./decompress 0 matrix2P.raw < compressed.zfp
    ./exe 1 nouvelEssai2.vti
    ./evaluationerreur matrixU.raw matrix2U.raw matrix3U.raw
    ./evaluationerreur matrixV.raw matrix2V.raw matrix3V.raw
    ./evaluationerreur matrixW.raw matrix2W.raw matrix3W.raw
    ./evaluationerreur matrixP.raw matrix2P.raw matrix3P.raw
    ./exe 2 nouvelEssai3.vti


Données Renault :

    ./exe 0 testRenault.vti
    ./compress 0 matrixU.raw > compressed.zfp
    ./decompress 0 matrix2U.raw < compressed.zfp
    ./compress 0 matrixV.raw > compressed.zfp
    ./decompress 0 matrix2V.raw < compressed.zfp
    ./compress 0 matrixW.raw > compressed.zfp
    ./decompress 0 matrix2W.raw < compressed.zfp
    ./compress 0 matrixP.raw > compressed.zfp
    ./decompress 0 matrix2P.raw < compressed.zfp
    ./exe 1 testRenault2.vti
    ./evaluationerreur matrixU.raw matrix2U.raw matrix3U.raw
    ./evaluationerreur matrixV.raw matrix2V.raw matrix3V.raw
    ./evaluationerreur matrixW.raw matrix2W.raw matrix3W.raw
    ./evaluationerreur matrixP.raw matrix2P.raw matrix3P.raw
    ./exe 2 testRenault3.vti


Ancienne version
------------

    make
    make -f Makefile2
    ./exe 0 test.vti
    ./compress 0 > compressed.zfp
    ./decompress 0 < compressed.zfp
    ./evaluationerreur
    ./exe 1 test2.vti
    ./exe 2 test3.vti
    paraview test2.vti 
    paraview test3.vti
