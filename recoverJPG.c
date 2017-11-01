#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{

    FILE* infile = fopen(argv[1], "r");
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image %d\n", argc );
        return 1;
    }
    
    if (infile == NULL)
    {
        fprintf(stderr, "Image unusable. Exit %d\n", argc);
        return 2;
    }

    unsigned char buffer[512];

    int fc = 0;
    int jc = 0;
    FILE* image = NULL;
    
    while (fread(buffer, 512, 1, infile) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jc == 1)
            {
                fclose(image);
            }
            else
            {
                jc = 1;
            }

            char fn[8];
            sprintf(fn, "%03d.jpg", fc);
            image = fopen(fn, "a");
            fc++;
        }
        if (jc == 1)
        {
            fwrite(&buffer,512, 1, image);
        }
    }
    fclose(infile);
    fclose(image);
    return 0;            
}
