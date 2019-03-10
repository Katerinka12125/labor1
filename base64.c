#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char * table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void append(unsigned char * write, unsigned char letter, size_t * write_position, int f_value)
{
    write[(*write_position)++] = table[letter];
    if (f_value > 0 && (*write_position + 1) % f_value == 0)
    {
        write[(*write_position)++] = '\n';
    }
}

void encode(FILE * input, FILE * output, int f_value)
{
    int read_by = 1024 * 600;
    int write_by = read_by*4/3 + read_by/f_value + 1;

    unsigned char * write = malloc(sizeof(unsigned char *) * write_by);
    size_t write_position = 0;

    unsigned char * read = malloc(sizeof(unsigned char *) * read_by);
    size_t read_count = fread(read, 1, read_by, input);
    while (read_count != 0)
    {
        if (read_count % 3 != 0)
        {
            read[read_count] = 0;
            if (read_count+1 < read_by) read[read_count+1] = 0;
        }

        for (int i = 0; i < read_count; i += 3)
        {
            unsigned char a = read[i];
            unsigned char b = read[i+1];
            unsigned char c = read[i+2];

            unsigned char letter_1 = (a >> 2);
            unsigned char letter_2 = (b>>4) | ((a<<4) & 48);
            unsigned char letter_3 = ((b<<2) & 63) | (c>>6);
            unsigned char letter_4 = (c & 63);

            append(write, letter_1, &write_position, f_value+1);
            append(write, letter_2, &write_position, f_value+1);
            append(write, letter_3, &write_position, f_value+1);
            append(write, letter_4, &write_position, f_value+1);
        }

        if (read_count % 3 > 0) write[write_position-1] = '=';
        if (read_count % 3 == 1) write[write_position-2] = '=';

        fwrite(write, 1, write_position, output);

        write_position=0;
        read_count = fread(read, 1, read_by, input);
    }

    free(write);
    free(read);
}

// Принимает букву из base64, возвращает её номер в таблице
// Если буквы в таблице нет - возвращает 255
unsigned char from_table(char letter)
{   
    for (int i = 0; i < 64; ++i)
    {
        if (table[i] == letter)
            return i;
    }

    return 255;
}

void decode(FILE * input, FILE * output, int i_flag)
{
    int read_by = 1024 * 600;
    int write_by = read_by*3/4;

    unsigned char * write = malloc(sizeof(unsigned char *) * write_by);
    size_t write_position = 0;

    unsigned char * read = malloc(sizeof(unsigned char *) * read_by);
    size_t read_count = fread(read, 1, read_by, input);

    unsigned char letters[4];
    int letters_count = 0;
    int over = 0;

    while (read_count != 0)
    {
        if (read_count % 4 != 0 && i_flag == 0)
        {
            printf("Invalid file\n");
            return;
        }

        for (int i = 0; i < read_count; i++)
        {
            unsigned char letter = from_table(read[i]);
            if (letter != 255 || read[i] == '=')
            {
                letters[letters_count++] = letter;
            }
            else if (!i_flag)
            {
                printf("Invalid file\n");
                return;
            }

            if (letters_count == 4)
            {
                letters_count = 0;
                if (over)
                {
                    printf("Error == in the middle of file\n");
                    break;
                }
                write[write_position++] = (letters[1]>>4) | (letters[0]<<2);
                if (letters[2] == 255)
                {
                    over = 1;
                    continue;
                }
                write[write_position++] = (letters[1]<<4) | (letters[2]>>2);
                if (letters[3] == 255)
                {
                    over = 1;
                    continue;
                }
                write[write_position++] = (letters[2]<<6) | (letters[3]);
            }
        }

        fwrite(write, 1, write_position, output);

        write_position=0;
        read_count = fread(read, 1, read_by, input);
    }

    free(write);
    free(read);
}

void main(int argc, char ** argv)
{
  int eflag = 0;
  int dflag = 0;
  int iflag = 0;
  int fvalue = -1;
  char * in_file = argv[argc-2];
  char * out_file = argv[argc-1];

  int index;
  int c;
  char * pEnd;

  opterr = 0;

  while ((c = getopt(argc, argv, "eidf:")) != -1)
    switch (c)
      {
      case 'e':
        eflag = 1;
        break;
      case 'd':
        dflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case 'f':
        fvalue = strtol (optarg,&pEnd,10);
        if (pEnd == optarg)
        {
            return;
        }
        break;
      }

    FILE * in = fopen (in_file, "r");
    FILE * out = fopen (out_file, "w");

    if (eflag==1)
        encode(in, out, fvalue);
    else if (dflag==1)
        decode(in, out, iflag);
    else
        printf("Usage: %s -e in out to encode\n%s -d in out to decode\n", argv[0], argv[0]);

    fclose(in);
    fclose(out);
}
