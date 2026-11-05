#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageInput.h"

#define BUFFER_SIZE 100
#define FILE_HEADER_STRING "__info2_image_file_format__"

// TODO Implementieren Sie geeignete Hilfsfunktionen für das Lesen der Bildserie aus einer Datei
static int checkFileHeader(FILE *file){
    char *headerBuffer = malloc(sizeof(FILE_HEADER_STRING));
    if(headerBuffer != NULL){
        fread(headerBuffer, sizeof(FILE_HEADER_STRING) , 1, file);
        if(fread != NULL){
            strcmp();
        }

    }

}

// TODO Vervollständigen Sie die Funktion readImages unter Benutzung Ihrer Hilfsfunktionen
GrayScaleImageSeries *readImages(const char *path)
{
    GrayScaleImageSeries *series = NULL;
    
    return series;
}

// TODO Vervollständigen Sie die Funktion clearSeries, welche eine Bildserie vollständig aus dem Speicher freigibt
void clearSeries(GrayScaleImageSeries *series)
{


}