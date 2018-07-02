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
 *  - clock
 */
#include <time.h>
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
    bool linear = true;

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
        cout << "Desenvolvido por: Anni Provietti, Gabriella Felgas e Igor Abreu\n";
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
     * Inicia o contador de tempo
     */
    clock_t tStart = clock();
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
    Factory* components = new Factory(0);
    /**
     * Incializa a construcao dos objetos de componentes
     * e pega a matriz de objetos
     */
    components->setup(elementsList->getElements());
    /**
     * Logica para pegar o numero de nos
     */
    int nos = 0;
    vector<string> nodes;
    nodes = components->getAllNodes();
    nos = nodes.size();
    vector<string> nosSaida = components->getNosdeSaida();
    int numeroComponentes = components->getComponents().size();
    int loopsDeConvergencia = 0;
    double tempoMaxDeLoop = 0;

    vector<Components*> listaDeComponetesAnterior(numeroComponentes);
    vector<double> resultado(nos);
    vector<double> resultadoAnterior(nos);
    /**
     * Linhas e colunas que devem ser somadas pela reducao de ampOp
     */
    vector<vector<int> > somaLinhas = linhasSomadas(components->getComponents(), components->getNodesSize());
    vector<vector<int> > somaColunas = colunasSomadas(components->getComponents(), components->getNodesSize());

    ofstream outfile ("resultados.tab");
    outfile << "t";
    for(unsigned int n = 1; n < nosSaida.size(); n++) {
        outfile << " " << nosSaida[n];
    }
    outfile << endl;
    for (double t = components->getTempo(); t <= components->getTempoFinal() + 10e-15; t += components->getPasso()) { // 10e-15 para comparacao com double
        /**
         * Criando vetor de condutancai e correntes
         * de acordo com o numero de nos no netlist
         */
        vector<vector<double> > condutancia(nos, vector<double>(nos));
        vector<double> correntes(nos);

        /**
         * Verificar se alguns dos componentes e um capacitor
         * para definir uma corrente inicial.
         */
        for (int i = 0; i < numeroComponentes; i++) {
            components->getComponents()[i]->setTempo(t);
            /**
             * Verificar se existe algum componente nao linear
             */
            if (! components->getComponents()[i]->isLinear()) {
                linear = false;
            }
            /**
             * Caso especifico para quando o componente e um capacitor
             * e temos que definir a corrente que passa pelo capacitor
             */
            if (components->getComponents()[i]->getNome().substr(0,1) == "C") {
                if (t == 0) {
                    /**
                     * Corrente para quando o instante de tempo e zero
                     */
                    components->getComponents()[i]->setCorrente(0);
                } else {
                    /**
                     * Pega a corrente que passa pelo capacitor em um instante de tempo anterior e define como
                     * corrente a ser utilizada no lugar de j0
                     */
                    components->getComponents()[i]->setCorrente(listaDeComponetesAnterior[i]->getCorrente());
                }
            }
            components->getComponents()[i]->estampar(condutancia, correntes, nodes, resultado);
        }
        resultadoAnterior = resultado;
        resultado = gauss(condutancia, correntes, components->getNodesSize(), components->getComponents(), nodes, somaLinhas, somaColunas);

        /**
         * Teste de adicionar a corrente apos o calculo
         */
        for (int i = 0; i < numeroComponentes; i++) {
            if (components->getComponents()[i]->getNome().substr(0,1) == "C") {
                int noA = components->getComponents()[i]->getNoA();
                int noB = components->getComponents()[i]->getNoB();
                /**
                 * Pega a tensao nodal para a matriz de resultados atuais e estampas atuais
                 * @todo se nao exisitir igualar a zero !IMPORTANT
                 */
                double tensaoRamo = resultado[noA] - resultado[noB];
                /**
                 * Ignorar a tensao no no 0
                 */
                if (noA == 0) {
                    tensaoRamo = -1*resultado[noB];
                }
                if (noB == 0) {
                    tensaoRamo = resultado[noA];
                }
                /**
                 * Pega a corrente passando no resistor no instante de tempo atual
                 */
                double correnteResistor = ((2* components->getComponents()[i]->getCapacitancia()) / components->getPasso()) * tensaoRamo;
                /**
                 * Pega a corrente no resistor e subtrai pela corrente na fonte de corrente no modelo
                 * do trapezio
                 */
                components->getComponents()[i]->setCorrente(
                    correnteResistor -
                    components->getComponents()[i]->getCorrente()
                );
            }
        }
        /**
         * Caso a netlist possua elementos nao lineares devemos fazer newton raphson
         * newton raphson
         */
        if (linear == false) { // @todo VERIFICAR SE VAI FUNCIONAR COM A REMOCAO DO NO
            bool converge = false;
            for (int n = 1; n <= 50; n++) {
                for (int i = 0; i < numeroComponentes; i++) {
                    if (components->getComponents()[i]->getNome().substr(0,1) == "D" ||
                        components->getComponents()[i]->getNome().substr(0,1) == "Q") {
                        /*Desestampa e reestampa componentes nao lineares*/
                        components->getComponents()[i]->desestampar(condutancia, correntes, resultadoAnterior);
                        components->getComponents()[i]->estampar(condutancia, correntes, nodes, resultado);
                    }
                }
                resultadoAnterior = resultado;
                resultado = gauss(condutancia, correntes, components->getNodesSize(), components->getComponents(), nodes, somaLinhas, somaColunas);

                converge = comparar(resultadoAnterior, resultado);
                if (converge == true) {
                    break;
                }
                if (n > loopsDeConvergencia) {
                    loopsDeConvergencia = n;
                    tempoMaxDeLoop = t;
                }
            }
        }

        /**
         * Salva a lista de componentes no instante anterior
         */
        listaDeComponetesAnterior = components->getComponents();

        outfile << t;
        for(int x = 1; x < (int) resultado.size(); x++) {
            outfile << " " << resultado[x];
        }
        outfile << endl;
    }
    outfile.close();
    printf("Tempo de processamento: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    cout << "Convergiu em: " << loopsDeConvergencia << " em t = " << tempoMaxDeLoop << endl;

}
