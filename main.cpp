/**
 * Inclui:
 *  - cin
 *  - cout
 */
#include <iostream>
/**
 * Inclui:
 *  - system
 */
#include <cstdlib>
 /**
 * Inclui:
 *  - ifstream
 */
#include <fstream>
/**
 * Inclui:
 *  - Vector
 */
#include <vector>
/**
 * Classe parceadora de Net List
 */
#include "parser.cpp"
/**
 * Fabrica construtora dos modelos dos elementos
 */
#include "factory.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

int main()
{
    string fileName;
    bool repeat;
    ifstream myNet;
    double tempo = 0;

    do {
        //system("cls"); /*Limpa o console do Windows*/
        system("clear"); /*Limpa o console do Linux*/

        if (repeat == true) {
            cout << "Arquivo " << fileName << " nao foi encontrado, tente novamente.\n";
            cout << "Obs. O Arquivo deve estar na mesma pasta do executavel.\n\n";
        }
        repeat = true;

        cout << "EEL525 - Circutos Eletricos II\n";
        cout << "UFRJ/Poli/DEL - Departamento de Engenharia Eletronica\n";
        cout << "Desenvolvido por: Igor Abreu\n";
        cout << "Programa de analise no dominio do tempo de elementos lineares e nao lineares\n";
        cout << "Nome do arquivo contendo a NetList: [ex. minha.net] ";
        cin >> fileName;
        /* Abrindo a net list*/
        myNet.open(fileName);
        if (myNet.is_open()) {
            repeat = false;
        }
    } while (repeat == true);

    /**
     * Lista de elementos a serem construidos
     * @param  myNet Arquivo da netlist
     * @return       Vetor de vetores devidamente separados com os componentes
     */
    Parser* elementsList = new Parser(myNet);
    /**
     * inicializa a fabrica de componentes com a constante tempo
     * inicialmente zerada
     */
    Factory* components = new Factory(tempo);
    /**
     * Incializa a construcao dos objetos de componentes
     * e pega a matriz de objetos
     */
    components->setup(elementsList->getElements());
    vector<Components*> listaDeComponetes = components->getComponents();
    /**
     * Logica para pegar o numero de nos
     */
    int nos = 0;
    vector<string> nodes;
    nodes = components->getAllNodes();
    nos = nodes.size();
    int numeroComponentes = listaDeComponetes.size();
    /**
     * Criando vetor de condutancai e correntes
     * de acordo com o numero de nos no netlist
     */
    vector<vector<double> > condutancia(nos, vector<double>(nos));
    vector<vector<double> > correntes(nos, vector<double>(1));

    ofstream outfile ("resultados.tab");
    outfile << "t";
    for(int n = 1; n < nos; n++) {
        outfile << " " << nodes[n];
    }
    outfile << endl;

    for (double t = components->getTempo(); t < components->getTempoFinal(); t += components->getPasso()) {
        components->setTempo(t);
        components->setup(elementsList->getElements());
        for (int i = 0; i < numeroComponentes; i++) {
            listaDeComponetes[i]->estampar(condutancia, correntes, nodes);
        }

        /**
         * Eliminacao de gauss para encontrar as tensoes
         * nodais
         */
        vector<vector<double> > resultado = gauss(condutancia, correntes);
        /**
         * transforma o terra em valor = 0;
         */
        double terra = resultado[0][0];
        for(int n = 0; n < components->getNodesSize(); n++) {
            resultado[n][0] -= terra;
        }
        /**
         * Remove o no de terra;
         */
        outfile << t;
        for(int x = 1; x < resultado.size(); x++) {
            outfile << " " << resultado[x][0];
            cout << nodes[x] << " = " << resultado[x][0] << endl;
        }
        outfile << endl;
    }
    outfile.close();
}
