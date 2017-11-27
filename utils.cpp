#ifndef UTILS
#define UTILS
/**
 * Inclui:
 *  - istringstream
 */
#include <sstream>
 /**
 * Inclui:
 *  - vector
 */
#include <vector>
 /**
 * Inclui:
 *  - vector
 */
#include <vector>
/**
 * Tratamento de excecoes
 */
#include <stdexcept>

/* Necessario para nao precisar escrever std:: */
using namespace std;

/**
 * Transformar uma string em elementos de um array utilizando um caracter delimitador
 * Ex. explode("Hello World", ' ')
 * Retorna:
 *     vector[0] = "Hello"
 *     vector[1] = "World"
 */
const vector<string> explode(const string& phrase, char delim)
{
    vector<string> result;
    istringstream iss(phrase);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

/**
 * Retorna as tensoes nodais quando voce passa a matriz de condutancia
 * e a matriz de corrente, aplica a eliminacao de gauss para transformar a matriz
 * de condutividade em uma matriz identidade.
 */
vector<double> gauss(vector<vector<double> > condutancia, vector<double> correntes)
{
    int condutanciaRows = condutancia.size();
    int correnteRows = correntes.size();

    /**
     * Matrizes de condutancia e conrrente devem ter os
     * mesmos numeros de linhas
     */
    if (condutanciaRows != correnteRows) {
        throw invalid_argument("Matrizes de condutancia e corrente nao tem o msm tamanho");
    }
    /**
     * Analisa cada linha da matriz de conduntancias
     */
    for(int row = 0; row < condutanciaRows; row++) {
        double pivot = condutancia[row][row];
        /**
         * Evita divisao por 0
         */
        if (pivot == 0) {
            pivot = 10e9;
        }

        int column = condutancia[row].size();
        if (condutanciaRows != column) {
            throw invalid_argument("Matrizes de condutancia deve ser quadrada");
        }

        correntes[row] /= pivot;
        for(int col = 0; col < column; col++) {
            condutancia[row][col] /= pivot;
        }

        for(int r = 0; r < condutanciaRows; r++) {
            if (r != row) {
                double fator = condutancia[r][row];
                correntes[r] -= correntes[row] * fator;
                for(int c = 0; c < column; c++) {
                    condutancia[r][c] -= condutancia[row][c] * fator;
                }
            }
        }
    }
    return correntes;
}

bool comparar(vector<double> vetor1, vector<double> vetor2)
{
    int nosIguais = 0;
    double limite = 10e9;
    int sizeOne = vetor1.size();
    int sizeTwo = vetor2.size();

    if (sizeOne != sizeTwo) {
        throw invalid_argument("Matrizes de condutancia e corrente nao tem o msm tamanho");
    }

    for(int i = 0; i < sizeOne; i++) {
        double lLimit = vetor1[i] - (vetor1[i] * limite);
        double uLimit = vetor1[i] + (vetor1[i] * limite);
        if (vetor2[i] <= uLimit && vetor2[i] >= lLimit) {
            nosIguais++;
        }
    }
    if (nosIguais == sizeOne) {
        return true;
    }
    return false;
}
#endif