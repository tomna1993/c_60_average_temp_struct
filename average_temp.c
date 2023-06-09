#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CITY_LENGTH 20
#define DATA_MAX 50

void read_by_delimiter(FILE *fp, char stream[], int stream_length);
float atoi_float(char number_text[]);

struct DataStruct
{
    char City[CITY_LENGTH];
    float Temp;
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

        tempData[i].Temp = atoi_float(number_text);
    }

    for (int i = 0; i < DATA_MAX; i++)
    {
        if (strlen(tempData[i].City) == 0)
        {
            continue;
        }
        printf ("%s: %.2f\n", tempData[i].City, tempData[i].Temp);
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

float atoi_float(char number_text[])
{
    int index = 0;
    float sign = 1.0;

    float integer = 0.0;
    float decimal = 0.0;

    // Exclude any whitespace characters
    while ( number_text[index] == ' ' ||
            number_text[index] == '\t' ||
            number_text[index] == '\n')
    {
        index++;
    }

    if (number_text[index] == '-' || number_text[index] == '+')
    {
        if (number_text[index] == '-')
        {
            sign = -1.0;
        }
        
        index++;
    }

    // Calculate the integer part of the number
    while (  number_text[index] != '\0' && number_text[index] != '.' && 
            (number_text[index] >= '0' && number_text[index] <= '9') )
    {
        integer = (integer * 10.0) + (number_text[index] - '0');
        index++;
    }

    // Calculate the decimal part of the number
    if (number_text[index++] == '.')
    {
        float power_of_ten = 10.0;

        while (  number_text[index] != '\0' && 
                (number_text[index] >= '0' && number_text[index] <= '9') )
        {
            decimal += (number_text[index] - '0') / power_of_ten;

            power_of_ten *= 10.0;

            index++;
        }
    }

    return (integer + decimal) * sign;
}