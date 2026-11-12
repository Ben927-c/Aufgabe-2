#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageInput.h"

#define BUFFER_SIZE 100
#define FILE_HEADER_STRING "__info2_image_file_format__"

// TODO Implementieren Sie geeignete Hilfsfunktionen für das Lesen der Bildserie aus einer Datei
// 
static int checkFileHeader(FILE *file){
    char *headerBuffer = malloc(sizeof(FILE_HEADER_STRING));
    if(headerBuffer != NULL){
        if(fread(headerBuffer, sizeof(FILE_HEADER_STRING) , 1, file) == 1){
            if(strcmp(headerBuffer, FILE_HEADER_STRING) == 0){
                free(headerBuffer);
                return 1;
            }
            else{
                free(headerBuffer);
                return 0;
            } 
        }
        else{
            free(headerBuffer);
            return 0;
        }
    }
    else
        return 0;
}

static int readUnsignedInt(FILE *file, unsigned int *value){
    if(fread(value, 1, sizeof(unsigned int), file) == sizeof(unsigned int)){
        return 1;
    }
    else{
        return 0;
    }
}

// TODO Vervollständigen Sie die Funktion readImages unter Benutzung Ihrer Hilfsfunktionen
GrayScaleImageSeries *readImages(const char *path)
{
    GrayScaleImageSeries *series = NULL;

    FILE *file;
    file = fopen(path,"rb");
    if(file == NULL){
        return NULL;
    }
    if(checkFileHeader(file) == 0){
        fclose(file);
        return NULL;
    }
    unsigned int imageCount;
    unsigned int imageWidth;
    unsigned int imageHeight;
    if(readUnsignedInt(file, &imageCount) == 1 && readUnsignedInt(file, &imageWidth) == 1 && readUnsignedInt(file, &imageHeight) == 1){
        series = malloc(sizeof(GrayScaleImageSeries));
        
        if(series == NULL){
            fclose(file);
            return NULL;
        }

        series->count = imageCount;
        series->images = malloc(imageCount * sizeof(GrayScaleImage));
        series->labels = malloc(imageCount * sizeof(unsigned char));
        
        if(series->images == NULL || series->labels == NULL){
            free(series->images);
            free(series->labels);
            free(series);
            fclose(file);
            
            return NULL;
        }
        for(unsigned int i = 0; i < imageCount; i++){
            


        }



        
    }
    else{
        fclose(file);
        return NULL;
    }
   






    return series;
}

// TODO Vervollständigen Sie die Funktion clearSeries, welche eine Bildserie vollständig aus dem Speicher freigibt
void clearSeries(GrayScaleImageSeries *series)
{
    //Prüfen, ob ein gültiger Zeiger übergeben wurde
    if (series == NULL){
        return;
    }
    
    //Pixel-Buffer aller Bilder einzeln freigeben
    for (unsigned int i = 0; i < series->count; i++){
        free(series->images[i].buffer);
    }

    //Speicher der Array freigeben
    free(series->images);
    free(series->labels);

    //Die Struktur freigeben
    free(series);

}