/**
 * Inclui:
 *  - Vector
 */
#include <vector>
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
            while (myNet.good()) {
                getline(myNet, line);
                auto componentLine = explode(line, ' ');
                listOfElements.push_back(componentLine);
            }
        }
};