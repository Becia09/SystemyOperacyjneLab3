#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <math.h>

int main(int argc, char **argv)
{
	int exitStatus;

    if (argc == 1)
    {
        printf ("Brak argumentu\n");
        return(0);
    }




	//***********************************************************ucinanie argumentu do najblizszej potegi 2
    int dlugosc = strlen(argv[1]);
	if (argc == 2)
	{
		int potega = 0;
		while (dlugosc > 1)
		{
			dlugosc /= 2;
			potega++;
		}

		dlugosc = 1;
		for (int i = 0; i < potega; i++)
		{
			dlugosc *= 2;
		}
	}


		//*********************************************************************wyznaczanie argumentow dzieci

	if (dlugosc > 1)
	{
		int pol = dlugosc / 2;

		//printf("argv dziecka1: ");
		char *argvDziecka1 = malloc(sizeof(char)*pol);
		for (int i = 0; i < pol; i++)
		{
			argvDziecka1[i] = argv[1][i];
			//printf("%c", argvDziecka1[i]);
		}

		char *argvDziecka2 = malloc(sizeof(char)*pol);
		int j = 0;
		for (int i = pol; i < dlugosc; i++)
		{
			argvDziecka2[j] = argv[1][i];
			j++;
		}
		int dziecko2 = strlen(argvDziecka2);
		int dziecko1 = strlen(argvDziecka1);


		//**************************************************************sklejanie argumentow rodzicow i dzieci
		int argument;
		if (argc == 2)
		{
			argument = 1;
		}
		else
		{
			argument = 2;
			dlugosc = strlen(argv[2]);
		}
		char *RodzicIdziecko1 = malloc(sizeof(char)*(dlugosc + pol + 1));
		char *RodzicIdziecko2 = malloc(sizeof(char)*(dlugosc + pol + 1));

		for (int i = 0; i < dlugosc; i++)
		{
			RodzicIdziecko1[i] = argv[argument][i];
			RodzicIdziecko2[i] = argv[argument][i];
		}

		strcat(RodzicIdziecko1, " ");
		strcat(RodzicIdziecko1, argvDziecka1);

		strcat(RodzicIdziecko2, " ");
		strcat(RodzicIdziecko2, argvDziecka2);
		//printf("argumenty rodzica i dziecka1 po strcat: %s\n", RodzicIdziecko1);

		//***********************************************************************wywolywanie podprocesow
//		printf("Przed fork, PID rodzica = %d\n", (int)getpid());

		pid_t pidDziecka1 = fork();

		if (pidDziecka1 == 0)      //jesli to dziecko1
		{
//		   printf("Po fork, PID dziecka = %d\n", (int)getpid());
		   execl("lab3", "lab3", argvDziecka1, RodzicIdziecko1, NULL);
		}

		else if (pidDziecka1 > 0)              //jesli to rodzic
		{
            free(argvDziecka1);
			free(RodzicIdziecko1);

			pid_t pidDziecka2 = fork();

			if (pidDziecka2 == 0)                      //jesli to dziecko2
			{
				execl("lab3", "lab3", argvDziecka2, RodzicIdziecko2, NULL);
			}
			free(argvDziecka2);
			free(RodzicIdziecko2);

			wait(NULL);
			wait(NULL);
			printf("%d ", (int)getpid());

			if (argc == 2)
				printf("%s\n", argv[1]);
				//for (int i=0;
			else
				printf("%s\n", argv[2]);
			exit(exitStatus);
		}

	}
	if (dlugosc <= 1)
	{
	   printf ("%d ", (int)getpid());
	   printf ("%s\n", argv[2]);
	   exit(exitStatus);
	}
    return(0);
}