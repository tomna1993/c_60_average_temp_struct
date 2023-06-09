#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CITY_LENGTH 20
#define DATA_MAX 20

void read_by_delimiter(FILE *fp, char stream[], int stream_length);

struct DataStruct
{
    char City[CITY_LENGTH];
    int Temp;
};


int main(int argc, string argv[])
{
    struct DataStruct tempData[DATA_MAX];

    if (argc != 2)
    {
        printf ("Usage: ./<program_name> <file_name>\n"); 
        return 1;  
    }

    FILE *fileHandle = fopen(argv[1], "r");

    if (fileHandle == NULL)
    {
        printf ("Cannot open file!\n");
        return 1;
    }

    for (int i = 0; i < DATA_MAX; i++)
    {
        const int number_length = 30;
        char number_text[number_length];

        read_by_delimiter(fileHandle, tempData[i].City, CITY_LENGTH); 
        read_by_delimiter(fileHandle, number_text, number_length);

        tempData[i].Temp = atoi(number_text);
    }

    for (int i = 0; i < DATA_MAX; i++)
    {
        if (strlen(tempData[i].City) == 0)
        {
            continue;
        }
        printf ("%s: %i\n", tempData[i].City, tempData[i].Temp);
    }

    fclose(fileHandle);

    return 0;
}

void read_by_delimiter(FILE *fp, char stream[], int stream_length)
{
    int i = 0;
    int c = fgetc(fp);

    while(!feof(fp) && c != ',' && c != '\n' && i < stream_length - 1) 
    {
        stream[i++] = c;

        c = fgetc(fp);
    }

    stream[i] = '\0';

    return;
}