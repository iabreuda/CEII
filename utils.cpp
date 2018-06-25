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
 * Tratamento de excecoes
 */
#include <stdexcept>
/**
 * Inclui
 *  - fabs
 */
#include <math.h>
/**
 * Inclui
 *  - sort
 */
#include <algorithm>
/**
 * Modelo basico para componentes
 */
#include "components.cpp"

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
vector<double> gauss(vector<vector<double> > condutancia, vector<double> correntes, int nos, vector<Components*> componentes)
{
    int numeroComponentes = componentes.size();
    int condutanciaRows = condutancia.size();
    int correnteRows = correntes.size();
    vector<vector<int> > somaLinhas(nos, vector<int>(nos, 0));
    vector<vector<int> > somaColunas(nos, vector<int>(nos, 0));
    /**
     * numero de nos de tensao
     */
    vector<vector<string> > nosSomar;
    /**
     * Montar matriz do que tem que ser somado
     */
    for (int i = 0; i < numeroComponentes; i++) {
        if (componentes[i]->getNome().substr(0,1) == "V" || // Tensao
            componentes[i]->getNome().substr(0,1) == "E" || // Tensao por tensao ou Amp de Tensao
            componentes[i]->getNome().substr(0,1) == "H") { // Tensao por corrente ou Transresistor
                somaLinhas[componentes[i]->getNoA()][componentes[i]->getNoB()] = 1;
                somaLinhas[componentes[i]->getNoB()][componentes[i]->getNoA()] = 1;
        }
        if (componentes[i]->getNome().substr(0,1) == "F" || // Corrente por corrente ou Amp de Corrente
            componentes[i]->getNome().substr(0,1) == "H") { // Tensao por corrente ou Transresistor
                somaColunas[componentes[i]->getNoD()][componentes[i]->getNoC()] = 1;
                somaColunas[componentes[i]->getNoC()][componentes[i]->getNoD()] = 1;
        }
    }
    /**
    for (int x = 0; x < somaLinhas.size(); x++) {
        for (int y = 0; y < somaLinhas[x].size(); y++) {
            cout << somaLinhas[x][y] << " " ;
        }
        cout << endl;
    }
    */

    /**
     * Cria uma matriz de linhas para serem somadas com a reducao por AmpOp
     */
    for (int linha = somaLinhas.size() - 1; linha >= 0; linha--) { // considera o no 0
        for (int coluna = somaLinhas[linha].size() - 1; coluna >= 0; coluna--) {
            if (somaLinhas[linha][coluna] == 1) {
                for (int col = somaLinhas[coluna].size() - 1; col >= 0; col--) {
                    if (somaLinhas[coluna][col] == 1 && col != linha) {
                        somaLinhas[linha][col] = 1;
                        somaLinhas[coluna][col] = 0;
                    } else if (col == linha) {
                        somaLinhas[coluna][col] = 0;
                    }
                }
            }
        }
    }

    /**
     * Cria uma matriz de linhas para serem somadas com a reducao por AmpOp
     */
    for (int linha = somaLinhas.size() - 1; linha >= 0; linha--) { // considera o no 0
        for (int coluna = somaLinhas[linha].size() - 1; coluna >= 0; coluna--) {
            if (somaLinhas[linha][coluna] == 1) {
                for (int col = somaLinhas[coluna].size() - 1; col >= 0; col--) {
                    if (somaLinhas[coluna][col] == 1 && col != linha) {
                        somaLinhas[linha][col] = 1;
                        somaLinhas[coluna][col] = 0;
                    } else if (col == linha) {
                        somaLinhas[coluna][col] = 0;
                    }
                }
            }
        }
    }

    /**
    for (int x = 0; x < somaLinhas.size(); x++) {
        for (int y = 0; y < somaLinhas[x].size(); y++) {
            cout << somaLinhas[x][y] << " " ;
        }
        cout << endl;
    }
    */

    /*
    for (int x = 0; x < somaLinhas.size(); x++) {
        for (int y = 0; y < somaLinhas[x].size(); y++) {
            cout << somaLinhas[x][y] << " " ;
        }
        cout << endl;
    }
    */

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
    for(int row = 1; row < condutanciaRows; row++) {
        double maxValue = 0;
        int maxIndex = 0;

        for (int linha = 1; linha < condutanciaRows; linha++) {
            if (fabs(condutancia[linha][row]) > maxValue && linha >= row) {
                maxValue = fabs(condutancia[linha][row]);
                maxIndex = linha;
            }
        }
        /**
         * Troca as linhas de condutancia e corrente de acordo
         * com o valor maximo
         */
        swap(condutancia[row], condutancia[maxIndex]);
        swap(correntes[row], correntes[maxIndex]);

        double pivot = condutancia[row][row];
        if (pivot == 0) {
            throw invalid_argument("Matrizes Singular");
        }

        int column = condutancia[row].size();
        if (condutanciaRows != column) {
            throw invalid_argument("Matrizes de condutancia deve ser quadrada");
        }

        correntes[row] /= pivot;
        for(int col = 1; col < column; col++) {
            condutancia[row][col] /= pivot;
        }
        /**
         * Transforma a matriz de condutancia em uma identidade
         */
        for(int r = 1; r < condutanciaRows; r++) {
            if (r != row) {
                double fator = condutancia[r][row];
                correntes[r] -= correntes[row] * fator;
                for(int c = 1; c < column; c++) {
                    condutancia[r][c] -= condutancia[row][c] * fator;
                }
            }
        }
    }

    return correntes;
}

/**
 * Compara 2 vetores e verifica se eles estao proximos por uma margem de erro
 * @param  vetor1
 * @param  vetor2
 * @return        True se igual False  se diferente
 */
bool comparar(vector<double> vetor1, vector<double> vetor2)
{
    int nosIguais = 0;
    double limite = 10e-5; //Esse limete pode ser modificado para aumentar a exatidao da comparacao
    int sizeOne = vetor1.size();
    int sizeTwo = vetor2.size();

    if (sizeOne != sizeTwo) {
        throw invalid_argument("Matrizes de condutancia e corrente nao tem o msm tamanho");
    }

    for(int i = 0; i < sizeOne; i++) {
        double lLimit = fabs(vetor1[i]) - (fabs(vetor1[i]) * limite);
        double uLimit = fabs(vetor1[i]) + (fabs(vetor1[i]) * limite);
        if (fabs(vetor2[i]) <= uLimit && fabs(vetor2[i]) >= lLimit) {
            nosIguais++;
        }
    }
    if (nosIguais == sizeOne) {
        return true;
    }
    return false;
}

/**
 * Retirada do stack overflow para comparar numeros no formato de string
 */
bool is_not_digit(char c)
{
    return ! isdigit(c);
}

/**
 * Retirada do stack overflow para ordenar corretamente os nos
 * de acordo com suas posicoes
 */
bool numeric_string_compare(const string& s1, const string& s2)
{
    string::const_iterator it1 = s1.begin(), it2 = s2.begin();

    if (isdigit(s1[0]) && isdigit(s2[0])) {
        int n1, n2;
        stringstream ss(s1);
        ss >> n1;
        ss.clear();
        ss.str(s2);
        ss >> n2;

        if (n1 != n2) return n1 < n2;

        it1 = find_if(s1.begin(), s1.end(), is_not_digit);
        it2 = find_if(s2.begin(), s2.end(), is_not_digit);
    }

    return lexicographical_compare(it1, s1.end(), it2, s2.end());
}
#endif