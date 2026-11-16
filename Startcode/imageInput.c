#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageInput.h"

#define BUFFER_SIZE 100
#define FILE_HEADER_STRING "__info2_image_file_format__"

// TODO Implementieren Sie geeignete Hilfsfunktionen für das Lesen der Bildserie aus einer Datei
// 
static int checkFileHeader(FILE *file){
    char *headerBuffer = malloc(strlen(FILE_HEADER_STRING) + 1);
    if(headerBuffer != NULL){
        if(fread(headerBuffer, 1, strlen(FILE_HEADER_STRING), file) == strlen(FILE_HEADER_STRING)){
            headerBuffer[strlen(FILE_HEADER_STRING)]= '\0';
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

static int readUnsignedShort(FILE *file, unsigned short int *value){
    if(fread(value, 1, sizeof(unsigned short int), file) == sizeof(unsigned short int)){
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
    unsigned short int imageCount;
    unsigned short int imageWidth;
    unsigned short int imageHeight;
    if(readUnsignedShort(file, &imageCount) == 1 && readUnsignedShort(file, &imageWidth) == 1 && readUnsignedShort(file, &imageHeight) == 1){
        series = calloc(1, sizeof(GrayScaleImageSeries));
        if(series == NULL){
            fclose(file);
            return NULL;
        }

        series->count = imageCount;
        series->images = calloc(imageCount, sizeof(GrayScaleImage));
        series->labels = malloc(imageCount * sizeof(unsigned char));
        
        if(series->images == NULL || series->labels == NULL){
            clearSeries(series);
            fclose(file);
            return NULL;
        }
        for(unsigned int i = 0; i < imageCount; i++){
            series->images[i].width = imageWidth;
            series->images[i].height = imageHeight;
            series->images[i].buffer = malloc (imageWidth * imageHeight * sizeof(GrayScalePixelType));
            if(series->images[i].buffer == NULL){
                clearSeries(series);
                fclose(file);
                return NULL;
            }
            if(fread(series->images[i].buffer, 1, imageWidth * imageHeight, file) != imageWidth * imageHeight){
                clearSeries(series);
                fclose(file);
                return NULL;
            }
            if(fread(&series->labels[i], 1, 1, file) != 1){
                clearSeries(series);
                fclose(file);
                return NULL;
            }  
            }
            fclose(file);
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
    if(series->images != NULL){
        for (unsigned int i = 0; i < series->count; i++){
            free(series->images[i].buffer);
        }
    }
    

    //Speicher der Array freigeben
    free(series->images);
    free(series->labels);

    //Die Struktur freigeben
    free(series);

}