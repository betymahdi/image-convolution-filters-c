# Image Convolution Filters (C)

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white) ![Traitement d'image](https://img.shields.io/badge/Traitement_d'image-convolution_2D-informational)

Implémentation en C d'un filtre gaussien par convolution 2D appliqué à une image en niveaux de gris. Projet réalisé en groupe dans le cadre de la formation d'ingénieur.

## Principe

La convolution consiste à faire glisser un noyau (filtre) sur chaque pixel d'une image et à calculer la somme pondérée des pixels voisins. Ici, le noyau est une gaussienne qui lisse l'image (effet de flou).

## Ce que fait le programme

1. Construit une image de test de 5 x 5 pixels
2. Ajoute une bordure de zéros (zero padding) pour conserver la taille de l'image
3. Génère un filtre gaussien 3 x 3 (sigma = 1) normalisé
4. Applique la convolution et affiche l'image d'origine, l'image avec padding, le filtre et le résultat

## Compilation et exécution

```bash
gcc gaussian_convolution.c -o convolution -lm
./convolution
```

## Exemple de sortie

Image de test (dégradé), puis résultat après filtrage. Les bords sont plus sombres car le zero padding ajoute des pixels nuls autour de l'image.

```text
Image originale :          Après filtre gaussien :
  0  25  50  75 100          9  25  43  61  52
 25  50  75 100 125         25  50  75 100  83
 50  75 100 125 150         43  75 100 125 102
 75 100 125 150 175         61 100 125 150 120
100 125 150 175 200         52  83 102 120  95
```

Noyau gaussien 3 x 3 (sigma = 1) :

```text
0.0751 0.1238 0.0751
0.1238 0.2042 0.1238
0.0751 0.1238 0.0751
```

## Structure du code

- `appliquerPaddingZero` : ajout de la bordure de zéros
- `creerFiltreGaussien` : calcul et normalisation du noyau gaussien
- `appliquerFiltreGaussien` : produit de convolution, avec bornage des valeurs entre 0 et 255
- `afficher` : affichage matriciel d'une image

## Pistes d'amélioration

- Lecture et écriture de vraies images (PGM/PPM)
- Autres noyaux : détection de contours (Sobel), netteté
- Taille de filtre et sigma passés en paramètres

## Technologies

C (bibliothèque standard, math.h)
