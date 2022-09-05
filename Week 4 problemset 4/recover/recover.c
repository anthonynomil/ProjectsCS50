#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // If more than 3 commands has been written printf the correct usage and return 1;
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Open the memory card file and create the .jpeg file
    FILE *card = fopen(argv[1], "r");
    FILE *jpeg = NULL;

    // Create the jpeg_file array to read and write on files, a jpeg_file counter / number
    BYTE jpeg_file[BLOCK_SIZE];
    int jpeg_file_count = 0;

    //Allocate memory for the file name
    char *filename = malloc(8);

    // While it has 512 bytes readable keep reading
    while (fread(jpeg_file, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // If the 4 first bytes are 0xff & 0xd8 & 0xff & 0xe0 or 0xe1 or 0xe2 etc...
        if (jpeg_file[0] == 0xff && jpeg_file[1] == 0xd8 && jpeg_file[2] == 0xff && (jpeg_file[3] & 0xf0) == 0xe0)
        {
            // If it's the first image sprintf the name, open the jpeg and add one to the jpeg counter
            if (jpeg_file_count == 0)
            {
                sprintf(filename, "%03i.jpg", jpeg_file_count);
                jpeg = fopen(filename, "w");
                fwrite(&jpeg_file, sizeof(BYTE), BLOCK_SIZE, jpeg);
                ++jpeg_file_count;
            }
            // If the jpeg counter is > than 0 close the last jpeg, sprintf the name of the file, open  the jpeg of the name before write the file and add 1 to the count
            else if (jpeg_file_count > 0)
            {
                fclose(jpeg);
                sprintf(filename, "%03i.jpg", jpeg_file_count);
                jpeg = fopen(filename, "w");
                fwrite(jpeg_file, sizeof(BYTE), BLOCK_SIZE, jpeg);
                ++jpeg_file_count;
            }
        }
        else if (jpeg_file_count > 0)
        {
            // If it's not the first bytes keep writing
            fwrite(jpeg_file, sizeof(BYTE), BLOCK_SIZE, jpeg);
        }
    }

    //Close the files
    free(filename);
    fclose(card);
    fclose(jpeg);
}