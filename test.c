#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define TIMESTAMP 256

char date[TIMESTAMP];
char title[TIMESTAMP];
char key[TIMESTAMP];

FILE *questionFile;
FILE *keyFile;

void timestamp()
{
	time_t now;
	time(&now);
	struct tm *local = localtime(&now);

	strftime(date, TIMESTAMP, "%Y_%m_%d_%H_%M_%S", local);

	strcpy(key, date);
	strcat(key, "_key");
	strcat(key, ".txt");
	
	strcpy(title, date);
	strcat(title, ".txt");

	FILE *questionFile;
	questionFile = fopen(title, "w");

	fprintf(questionFile, "Name:\n");
	fprintf(questionFile, "Date: ");
	fprintf(questionFile, "%s\n\n", date);

	fclose(questionFile);

}

int rng(int limit)
{
	int result;
	result = rand() % limit;
	return (result + 1);
}

int question_generator(FILE* filehandle, int a, int b, int sign)
{
	switch (sign)
    {
        case 1:
        {
            fprintf(filehandle, "%d + %d =", a, b);
            return a + b;
        }
        case 2:
        {
            if (a > b)
            {
                fprintf(filehandle, "%d - %d =", a, b);
                return a - b;
            }
            else 
            {
                fprintf(filehandle, "%d - %d =", b, a);
                return b - a;
            }
        }
        case 3:
        {
            fprintf(filehandle, "%d x %d =", a, b);
            return a * b;
        }
        default:
        {
            while(1)
            {
                if (a / b <= 5 || b == 0)
                {
                    a = rng(1000);
                    b = rng(1000);
                }
                else
                {
                    break;
                }
            }   
            fprintf(filehandle, "%d / %d =", a, b);
            return a / b;
        }
    }
    
	
}

void write_key(FILE* filehandle, int number, int answer)
{
    fprintf(filehandle, "%3d. %-7d\t", number, answer);
	if (number % 3 == 0)
	{
		fprintf(filehandle, "\n");
	}
	else
	{
		fprintf(filehandle, "\t");
	}
}

int main()
{
	int a, b;
	int operator;
	int answer;

	time_t now;
	srand(time(&now));

    timestamp();

	keyFile = fopen(key, "w");
	fprintf(keyFile, "Key\n");
	fclose(keyFile);

	keyFile = fopen(key, "a");
    if(keyFile == NULL)
    {
        printf("Error, no value in keyFile\n");
        return 0;
    }
	questionFile = fopen(title, "a");
    if(questionFile == NULL)
    {
        printf("Error, no value in questionFile\n");
        return 0;
    }

	for (int i = 0; i < 100; ++i)
	{
        a = rng(1000);
		b = rng(1000);
		while (1) 
        {
            if (a == b)
		    {
		  	   b = rng(1000);
            }
            else
            {
                break;
            }
        }
		operator = rng(4);
		fprintf(questionFile, "%d. ", i + 1);
		answer = question_generator(questionFile, a, b, operator);
		if ((i + 1) % 3 == 0)
		{
			fprintf(questionFile, "\n\n");
		}
        else
        {
            fprintf(questionFile, "\t\t\t");
        }
		write_key(keyFile, i + 1, answer);
	}
	fclose(questionFile);
    fclose(keyFile);
}