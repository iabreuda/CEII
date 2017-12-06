#ifndef PARSER
#define PARSER

/**
 * Inclui:
 *  - string
 */
#include <string>
/**
 * Inclui:
 *  - Vector
 */
#include <vector>
/**
 * Inclui:
 *  - ifstream
 */
#include <fstream>
/**
 * Funcoes de Utilidades
 */
#include "utils.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Parser
{
    public:
        /**
         * Construtor
         */
        Parser(ifstream &myNet)
        {
            setup(myNet);
        }

        /**
         * Retorna lista de todos os elementos da net list devidamente
         * parseados.
         */
        vector<vector<string> > getElements()
        {
            return listOfElements;
        }

    private:
        /**
         * Matrix bi-dimensional para armazenar todos os componentes e proprieadades
         * em formato de lista
         */
        vector<vector<string> > listOfElements;

        /**
         * Cria uma matrix contendo vetor de vetores
         * Ex: indice[0][0] = Nome do primeiro componente
         *     indice[0][1] = No 1 do primeiro componente
         *     indice[0][2] = No 2 do primeiro componente
         * @param myNet stream do arquivo lido
         */
        void setup(ifstream &myNet)
        {
            string line;
            int lineNumber = 1;
            while (myNet.good()) {
                getline(myNet, line);
                /**
                 * Por default a primeira linha e o nome do circuito
                 * queremos discartar ela e ignora linhas em branco
                 */
                if (lineNumber > 1 && !line.empty()) {
                    auto componentLine = explode(line, ' ');
                    listOfElements.push_back(componentLine);
                }
                lineNumber++;
            }
        }
};

#endif