/***********************************************************************
 **                                                                   **
 **  UNIVERSIDADE FEDERAL DO RIO DE JANEIRO                           **
 **                                                                   **
 **  CIRCUITOS ELETRICOS II - EEL525 - 2017.2                         **
 **                                                                   **
 **  DESCRIPTION:                                                     **
 **  TEMPORAL CIRCUIT ANALISYS FOR LINEAR AND NONLINEAR ELEMENTS      **
 **                                                                   **
 **  AUTHORS: JONAS DEGRAVE, IGOR ABREU, EDUARDO PIRES                **
 **  EMAIL: jonasdegrave@poli.ufrj.br                                 **
 **                                                                   **
 **  VERSION HISTORY:                                                 **
 **                                                                   **
 **  Version 0.1 (01 Nov 17): Basic program structure.                **
 **  Version 0.2 (10 Nov 17): DrawVector, DrawMatrix, GaussJordan.    **
 **                                                                   **
 **  REFERENCES:                                                      **
 **                                                                   **
 **  (1)                                                              **
 **  Queiroz, A. C. M.                                                **
 **  Circuitos Eletricos, Metodos de Analise e Introducao a Sintese.  **
 **  Retrieved in 08 November 2016 from:                              **
 **  http://www.coe.ufrj.br/~acmq/cursos/CEII.pdf                     **
 **                                                                   **
 **  (2)                                                              **
 **  Queiroz, A. C. M.                                                **
 **  MNA1 (Computer Software                                          **
 **  Retrieved in November 2017 from:                                 **
 **  http://www.coe.ufrj.br/~acmq/cursos/mna1amp.zip                  **
 **                                                                   **
 **  (3)                                                              **
 **  Ruggiero, M. A. e Lopes, V. L. R.                                **
 **  Calculo Numerico: Aspectos Teoricos e Computacionais.            **
 **  2 ed.São Paulo: Pearson Makron Books, 1996.                      **
 **                                                                   **
 **                                                                   **
 **  USAGE INSTRUCTIONS: (REQUIRES C COMPILER)                        **
 **  ~ $ gcc -c <PROGRAMFILE.c>                                       **
 **  ~ $ gcc -o <PROGRAMFILE> <PROGRAMFILE.o>                         **
 **  ~ $ ./PROGRAMFILE <NETLISTFILE.net>                              **
 **  ~ $ cat <CIRCUIT.cir>                                            **
 **                                                                   **
 **                                                                   **
 **  THIS DOCUMENT IS BETTER VIEWED IN A 80 CHARACTER CONSOLE WINDOW  **
 **                                                                   **
 ***********************************************************************/

/*  ###############
    ## Libraries ##
    ###############  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*  ############
    ## Macros ##
    ############  */

#define DEBUG             1

#define MAX_NODES       100
#define MAX_ELEMENTS    100
#define MAX_NAME         10

#define ZERO           1e-9

/*  ################
    ## Data Types ##
    ################  */

/*  ###################################
    ## Low Level Auxiliary Functions ##
    ###################################  */

/* Draws a matrix into the screen. (ignores first line and column) */
int DrawMatrix (double A[MAX_NODES][MAX_NODES], unsigned N)
{
    unsigned i, j;

    if (DEBUG) {printf("\n[Debug] Drawing Matrix A^^ from (A^^ * x^ = b^):\n\n");}

    for (i = 1; i < N; i++)
    {
        for (j = 1; j < N; j++)
        {
            printf("%6.2lf  ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/* Draws a vector into the screen. (ignores first element) */
int DrawVector (double b[MAX_NODES], unsigned N)
{
    unsigned i;

    if (DEBUG) {printf("\n[Debug] Drawing Vector b^ from (A^^ * x^ = b^):\n\n");}

    for (i = 1; i < N; i++)
    {
        printf("%14.10lf  \n", b[i]);
    }
}

/*  ####################################
    ## High Level Auxiliary Functions ##
    ####################################  */

/* Reads the input netlist file and loads elements into circuit. */
int Netlist ()
{
    return 0;
}

/* Gauss-Jordan method for linear system solving with pivoting. */
/* ps: ignores line 0 and column 0. */
int GaussJordan (double A[MAX_NODES][MAX_NODES], double b[MAX_NODES], unsigned N)
{
    /* indexes */
    /* i sweeps diagonals */
    /* j sweeps ?? */
    /* l sweeps lines to find pivot */
    /* a holds position of largest pivot */
    unsigned i, j, l, a;

    /* aux variables */
    /* t hold pivot value */
    /* p holds swapping value */
    double t, p;

    /* pivot limit near zero */
    double zero = ZERO;

    /* sweep diagonal */
    for (i = 1; i < N; i++)
    {
        t = 0.0;
        a = i;
        /* discover largest pivot */
        for (l = i; l <= N; l++)
        {
            if (fabs(A[l][i]) > fabs(t))
            {
                printf("New pivot %.10lf from line %d is greater than %.10lf from line %d.\n", fabs(A[l][i]), l, t, a);
                a = l;
                t = A[l][i];
            }
        }
        /* if largest pivot is not in diagonal, swap lines */
        if (i != a)
        {
            printf("Swapping lines %d and %d..\n", i, a);
            /* swap A */
            for (l = 1; l <= N; l++)
            {
                p = A[i][l];
                A[i][l] = A[a][l];
                A[a][l] = p;
            }
            /* swap b */
            p = b[i];
            b[i] = b[a];
            b[a] = p;

            printf("\nMatrix after pivoting.\n");
            DrawMatrix(A,N);
            DrawVector(b,N);
        }
        else {printf("\nWe shall not pivot.\n");}
        /* check if pivot value is not too close to zero */
        if (fabs(t) < zero)
        {
            printf("Pivot %.10lf is smaller than %.10lf.\n", t, zero);
            printf("ERROR: Singular System!\n");
            return 1;
        }

        /* proceed with gaussian elimination under pivot for b */
        b[i] /= t;
        p = b[i];
        if (p != 0.0)
        {
            for (l = 1; l <= N; l++)
            {
                if (l != i)
                {
                    b[l] -= A[l][i] * p;
                }
            }
        }

        /* proceed with gaussian elimination under pivot for A */
        for (j = N; j > 0; j--)
        {
            /* divide line by pivot */
            A[i][j] /= t;
            /* subtract pivot line from other lines */
            p = A[i][j];
            if (p != 0.0) /* skips operations with zeroes */
            {
                /* loop every line */
                for (l = 1; l <= N; l++)
                {
                    if (l != i) /* protects pivot line */
                    {
                        A[l][j] -= A[l][i] * p;
                    }
                }
            }
        }

        printf("\nMatrix after elimination.\n");
        DrawMatrix(A,N);
        DrawVector(b,N);
    }
    return 0;
}



/* Gauss-Jordan method for linear system solving with pivoting. */
int GaussJordan_backup (double A[MAX_NODES][MAX_NODES], double b[MAX_NODES], unsigned N)
{
    /* indexes */
    /* i sweeps diagonals */
    /* j sweeps ?? */
    /* l sweeps lines to find pivot */
    /* a holds position of largest pivot */
    unsigned i, j, l, a;

    /* aux variables */
    /* t hold pivot value */
    /* p holds ?? */
    double t, p;

    /* pivot limit near zero */
    double zero = ZERO;

    /* sweep diagonal */
    for (i = 1; i <= N; i++)
    {
        t = 0.0;
        a = i;
        /* discover largest pivot */
        for (l = i; l <= N; l++)
        {
            if (fabs(A[l][i]) > fabs(t))
            {
                a = l;
                t = A[l][i];
            }
        }
        /* if largest pivot is not in diagonal, swap lines */
        if (i != a)
        {
            for (l = 1; l <= N+1; l++)
            {
                p = A[i][l];
                A[i][l] = A[a][l];
                A[a][l] = p;
            }
        }
        /* check if pivot value is not too close to zero */
        if (fabs(t) < zero)
        {
            printf("ERROR: Singular System!\n");
            return 1;
        }
        /* proceed with gaussian elimination under pivot */
        for (j = N+1; j > i; j--)
        {
            A[i][j] /= t;
            p = A[i][j];
            if (p != 0.0)
            {
                for (l = 1; l <= N; l++)
                {
                    if (l != i)
                    {
                        A[l][j] -= A[l][i] * p;
                    }
                }
            }
        }
    }
    return 0;
}



/* Newton-Raphson method for operation point determination. */
int NewtonRaphson ()
{
    return 0;
}

/* Draws the circuit into the screen. */
int DrawCircuit ()
{
    return 0;
}

/* Writes a table for output values in a file. */
int WriteOutput ()
{
    return 0;
}

/*  ######################
    ## Main Function ##
    ######################  */

int main (int argc, char *argv[])
{
    if (DEBUG) {printf("\n[Debug] Main function has been initiated.\n");}

    const unsigned N = 11;

    double A[MAX_NODES][MAX_NODES] = {{0,0,0,0,0,0,0,0,0,0,0},{0,2,6,5,1,7,9,8,4,6,7},{0,1,0,4,3,9,7,8,6,2,4,9},{0,2,4,3,5,9,8,9,4,4,2},{0,1,4,1,1,2,7,5,4,2,3,4},
                                    {0,3,6,5,1,1,9,8,4,6,7},{0,6,0,4,3,9,7,8,6,2,4,3},{0,1,4,3,5,9,8,9,0,4,2},{0,9,1,1,1,2,7,5,1,2,3,4},{0,6,4,2,2,7,8,5,1,2,1},{0,7,8,7,6,4,5,6,9,8,9}};

    double b[MAX_NODES] = {0,7,3,8,5,3,6,9,1,0,3};

    printf("\nBEFORE:\n");
    DrawMatrix(A, N);
    DrawVector(b, N);

    printf("\nSOLVING SYSTEM...\n\n");
    GaussJordan(A,b,N);

    printf("\nAFTER:\n");
    DrawMatrix(A, N);
    DrawVector(b, N);

    if (DEBUG) {printf("\n[Debug] Main function is terminating.\n");}

    return 0;
}
