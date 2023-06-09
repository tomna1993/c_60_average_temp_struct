#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CITY_LENGTH 20
#define DATA_MAX 70

struct DataStruct
{
    char City[CITY_LENGTH];
    float Temp;
};

void read_by_delimiter(FILE *fp, char stream[], int stream_length);
float atoi_float(char number_text[]);
void sort_cities(struct DataStruct sort_data[], int string_length, int data_length);
void print_struct(struct DataStruct print_data[], int array_length);


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

    sort_cities(tempData, CITY_LENGTH, DATA_MAX);

    print_struct(tempData, DATA_MAX);

    fclose(fileHandle);

    return 0;
}

// Read file by comma ',' and newline '\n' delimiters
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

// Convert number string to decimal number
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

// Sort data (selection sort) by temperature from the highest value to the lowest
void sort_cities(struct DataStruct sort_data[], int string_length, int data_length)
{
    for (int start = 0; start < data_length - 1; start++)
    {
        int minVal_index = start;

        // Sort the values from lower to the highest
        // for (int step = start + 1; step < data_length; step++)
        // {
        //     // Find the lowest value and save its index
        //     if (sort_data[minVal_index].Temp > sort_data[step].Temp)
        //     {
        //         minVal_index = step;
        //     }   
        // }

        // Sort the values from the highest to the lowest
        for (int step = start + 1; step < data_length; step++)
        {
            // Find the lowest value and save its index
            if (sort_data[minVal_index].Temp < sort_data[step].Temp)
            {
                minVal_index = step;
            }   
        }

        // Move the lowest value to the beginning of the array
        if (minVal_index != start)
        {
            // Swap city
            char tmp_city[string_length];

            strcpy(tmp_city, sort_data[start].City);
            strcpy(sort_data[start].City, sort_data[minVal_index].City);
            strcpy(sort_data[minVal_index].City, tmp_city);

            // Swap temp
            float tmp_temp = sort_data[start].Temp;
            sort_data[start].Temp = sort_data[minVal_index].Temp;
            sort_data[minVal_index].Temp = tmp_temp;    
        }
    }

    return;
}

// Print the data structure
void print_struct(struct DataStruct print_data[], int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        if (strlen(print_data[i].City) == 0)
        {
            continue;
        }
        printf ("%s: %.2f\n", print_data[i].City, print_data[i].Temp);
    }

    return;
}