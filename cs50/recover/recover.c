#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Ensure one argument only
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open input file (Return error if cant be opened)
    char *input_file_name = argv[1];
    FILE *input_pointer = fopen(input_file_name, "r");
    if (input_pointer == NULL)
    {
        printf("Could not open %s\n", input_file_name);
        return 1;
    }

    //initialize variables
    BYTE buffer[512];
    int count = 0;
    FILE *img_pointer = NULL;
    char filename[8];

    //read 512 bytes to buffer and repeat until end of card
    while (fread(&buffer, 512, 1, input_pointer) == 1)
    {
        //if start of a new JPEG (0xff 0xd8 0xff 0xe*)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if not start of JPEG, close previous file
            if (count != 0)
            {
                fclose(img_pointer);
            }
            //initialise file
            sprintf(filename, "%03i.jpg", count);
            img_pointer = fopen(filename, "w");
            count++;
        }
        //if JPEG has been found, write to file
        if (count != 0)
        {
            fwrite(&buffer, 512, 1, img_pointer);
        }
    }
    fclose(input_pointer);
    fclose(img_pointer);
    return 0;
}