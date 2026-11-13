# Image Convolution Filters (C)

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
