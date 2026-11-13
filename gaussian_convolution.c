/* Projet : Produit de Convolution
 Membres du groupe :
 - MOUTAWAKIL Latifa : BDCC
 - MAHDI I btissam   : CCN
 - LEMRANI Kenza     : CCN
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE_MAX 500
#define PI 3.14159265359

typedef struct {
    int largeur;
    int hauteur;
    unsigned char pixels[TAILLE_MAX][TAILLE_MAX];
} Image;

void appliquerPaddingZero(Image *originale, Image *paddee, int taillePadding) {
    paddee->largeur = originale->largeur + 2 * taillePadding;
    paddee->hauteur = originale->hauteur + 2 * taillePadding;

    // Initialize all pixels to zero
    for (int i = 0; i < paddee->hauteur; i++) {
        for (int j = 0; j < paddee->largeur; j++) {
            paddee->pixels[i][j] = 0;
        }
    }

    // Copy original image into the center of the padded image
    for (int y = 0; y < originale->hauteur; y++) {
        for (int x = 0; x < originale->largeur; x++) {
            paddee->pixels[y + taillePadding][x + taillePadding] = originale->pixels[y][x];
        }
    }
}

void creerFiltreGaussien(double **gaussienne, int taille, double sigma) {
    double somme = 0.0;
    int centre = taille / 2;

    // Calculate the Gaussian filter coefficients
    for (int x = -centre; x <= centre; x++) {
        for (int y = -centre; y <= centre; y++) {
            double exponent = -(x * x + y * y) / (2 * sigma * sigma);
            gaussienne[x + centre][y + centre] = exp(exponent) / (2 * PI * sigma * sigma);
            somme += gaussienne[x + centre][y + centre];
        }
    }

    // Normalize the filter
    for (int x = 0; x < taille; x++) {
        for (int y = 0; y < taille; y++) {
            gaussienne[x][y] /= somme;
        }
    }
}

void appliquerFiltreGaussien(Image *imageOriginale, Image *imageResultat, double **gaussienne, int tailleFiltreGaussien, int taillePadding) {
    // Initialize result image dimensions (without padding)
    imageResultat->largeur = imageOriginale->largeur - 2 * taillePadding;
    imageResultat->hauteur = imageOriginale->hauteur - 2 * taillePadding;

    int centre = tailleFiltreGaussien / 2;

    // Apply convolution and store directly in the result image without padding
    for (int y = taillePadding; y < imageOriginale->hauteur - taillePadding; y++) {
        for (int x = taillePadding; x < imageOriginale->largeur - taillePadding; x++) {
            double somme = 0.0;

            for (int ky = -centre; ky <= centre; ky++) {
                for (int kx = -centre; kx <= centre; kx++) {
                    somme += gaussienne[ky + centre][kx + centre] *
                            imageOriginale->pixels[y + ky][x + kx];
                }
            }

            // Store the result in the unpadded position
            imageResultat->pixels[y - taillePadding][x - taillePadding] =
                (unsigned char)(fmin(fmax(somme, 0), 255));
        }
    }
}

void afficher(const Image *img) {
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            printf("%3u ", img->pixels[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    Image imageOriginale, imageResultat, imagePadd;

    // Initialize original image
    imageOriginale.largeur = 5;
    imageOriginale.hauteur = 5;

    // Fill original image
    for (int y = 0; y < imageOriginale.hauteur; y++) {
        for (int x = 0; x < imageOriginale.largeur; x++) {
            imageOriginale.pixels[y][x] = (x + y) * 25; // valeurs <= 200 : reste dans la plage d'un unsigned char
        }
    }

    printf("Image originale :\n");
    afficher(&imageOriginale);

    // Calculate padding size based on Gaussian kernel
    int tailleFiltreGaussien = 3;
    int taillePadding = tailleFiltreGaussien / 2;

    // Apply padding
    appliquerPaddingZero(&imageOriginale, &imagePadd, taillePadding);

    printf("Image avec padding :\n");
    afficher(&imagePadd);

    // Create Gaussian filter
    double sigma = 1.0;
    double **gaussienne = (double **)malloc(tailleFiltreGaussien * sizeof(double *));
    for (int i = 0; i < tailleFiltreGaussien; i++) {
        gaussienne[i] = (double *)malloc(tailleFiltreGaussien * sizeof(double));
    }

    creerFiltreGaussien(gaussienne, tailleFiltreGaussien, sigma);

    printf("Filtre Gaussien :\n");
    for (int i = 0; i < tailleFiltreGaussien; i++) {
        for (int j = 0; j < tailleFiltreGaussien; j++) {
            printf("%.4f ", gaussienne[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Apply Gaussian filter and store result without padding
    appliquerFiltreGaussien(&imagePadd, &imageResultat, gaussienne, tailleFiltreGaussien, taillePadding);

    printf("Image après application du filtre gaussien (sans padding):\n");
    afficher(&imageResultat);

    // Free memory
    for (int i = 0; i < tailleFiltreGaussien; i++) {
        free(gaussienne[i]);
    }
    free(gaussienne);

    return 0;
}
