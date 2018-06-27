#ifndef FACTORY
#define FACTORY
/**
 * Inclui:
 *  - Sort
 *  - Unique
 *  - Reverse
 */
#include <algorithm>
/**
 * Tratamento de excecoes
 */
#include <stdexcept>
/**
 * Modelo basico para componentes
 */
#include "components.cpp"
/**
 * Modelo de resistor linear
 */
#include "resistor.cpp"
/**
 * Modelo de capacitor linear
 */
#include "capacitor.cpp"
/**
 * Modelo de indutor
 */
#include "indutor.cpp"
/**
 * Modelo de Fonte de corrente controlada por corrente
 */
#include "correntecorrente.cpp"
/**
 * Modelo de Fonte de corrente controlada por tensao
 */
#include "correntetensao.cpp"
/**
 * Modelo de Fonte de tensao controlada por tensao
 */
#include "tensaotensao.cpp"
/**
 * Modelo de Fonte de tensao controlada por corrente
 */
#include "tensaocorrente.cpp"
/**
 * Modelo de Transistor Bipolar
 */
#include "bipolar.cpp"
/**
 * Modelo de amplificador operacional
 */
#include "ampop.cpp"
/**
 * Modelo de transformador
 */
#include "transformador.cpp"
/**
 * Modelo de Diodo
 */
#include "diodo.cpp"
/**
 * Modelo de fonte de tensao dc
 */
#include "tensaodc.cpp"
/**
 * Modelo de fonte de corrente dc
 */
#include "correntedc.cpp"
/**
 * Modelo de fonte de corrente senoidal
 */
#include "correntesenoidal.cpp"
/**
 * Modelo de fonte de tensao senoidal
 */
#include "tensaosenoidal.cpp"
/**
 * Modelo de fonte de corrente pulsada
 */
#include "correntepulso.cpp"
/**
 * Modelo de fonte de tensao pulsada
 */
#include "tensaopulso.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Factory
{
    public:
        /**
         * Construtor
         */
        Factory(double t)
        {
            setTempo(t);
        }

        /**
         * Retorna todos os componentes
         */
        vector<Components*> getComponents()
        {
            return componentes;
        }

        /**
         * Retorna o passo de tempo
         */
        double getPasso()
        {
            return passo;
        }

        /**
         * Retorna o tempo final de analise
         */
        double getTempoFinal()
        {
            return tempoFinal;
        }

        /**
         * Restorn os Numeros de pontos por passo
         */
        double getPassoPonto()
        {
            return passoPonto;
        }

        /**
         * Pega o metodo de analise no tempo
         */
        string getMetodo()
        {
            return metodo;
        }

        /**
         * Retorna o instante de tempo
         */
        double getTempo()
        {
            return tempo;
        }

        /**
         * Retorna o valor de teta
         */
        double getTeta()
        {
            return teta;
        }

        /**
         * retorna o numero de nos de tensao
         */
        int getNodesSize()
        {
            return nodes.size();
        }

        /**
         * retorna os de nos de tensao
         */
        vector<string> getNosdeSaida()
        {
            int numeroComponentes = componentes.size();
            vector<string> allNodes;

            for (int index = 0; index < numeroComponentes; index++) {
                nodes.push_back(to_string(componentes[index]->getNoA()));
                nodes.push_back(to_string(componentes[index]->getNoB()));
                if (componentes[index]->getNos() == 4) {
                    nodes.push_back(to_string(componentes[index]->getNoC()));
                    nodes.push_back(to_string(componentes[index]->getNoD()));
                }
            }
            sort(nodes.begin(), nodes.end(), numeric_string_compare);
            nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

            sort(nosSaida.begin(), nosSaida.end());
            nosSaida.erase(unique(nosSaida.begin(), nosSaida.end()), nosSaida.end());

            allNodes.insert(allNodes.end(), nodes.begin(), nodes.end());
            allNodes.insert(allNodes.end(), nosSaida.begin(), nosSaida.end());

            return allNodes;
        }

        /**
         * Retorna o numero de nos auxiliares adicionados por
         * alguns componentes
         */
        int getAuxNodesSize()
        {
            return auxNodes.size();
        }

        /**
         * Retorna um vetor com todos os nos devidamente ordenados
         * e com as duplicadas removidas
         */
        vector<string> getAllNodes()
        {
            int numeroComponentes = componentes.size();
            vector<string> allNodes;

            for (int index = 0; index < numeroComponentes; index++) {
                nodes.push_back(to_string(componentes[index]->getNoA()));
                nodes.push_back(to_string(componentes[index]->getNoB()));
                if (componentes[index]->getNos() == 4) {
                    nodes.push_back(to_string(componentes[index]->getNoC()));
                    nodes.push_back(to_string(componentes[index]->getNoD()));
                }
            }
            sort(nodes.begin(), nodes.end(), numeric_string_compare);
            nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

            sort(auxNodes.begin(), auxNodes.end());
            auxNodes.erase(unique(auxNodes.begin(), auxNodes.end()), auxNodes.end());

            allNodes.insert(allNodes.end(), nodes.begin(), nodes.end());
            allNodes.insert(allNodes.end(), auxNodes.begin(), auxNodes.end());

            return allNodes;
        }

        /**
         * Define o passo
         */
        void setPasso(double v)
        {
            passo = v;
        }

        /**
         * Define o tempo final
         */
        void setTempoFinal(double v)
        {
            tempoFinal = v;
        }

        /**
         * Define o passo por ponto
         */
        void setPassoPonto(double v)
        {
            passoPonto = v;
        }

        /**
         * Define o metodo a ser utilizado na analise
         */
        void setMetodo(string v)
        {
            metodo = v;
        }

        /**
         * Define o instante de tempo a ser analisado
         */
        void setTempo(double t)
        {
            tempo = t;
        }

        /**
         * Define o valor de teta a ser usado no metodo de integracao
         */
        void setTeta(double tet)
        {
            teta = tet;
        }

        /**
         * Verifica se o metodo de analise e teta
         */
        bool isTeta()
        {
            return getMetodo() == "TETA";
        }

        /**
         * Configura a lista de elementos para ser construida
         */
        void setup(vector<vector<string> > listOfElements)
        {
            string type;
            /**
             * Fazemos de tras para frente pois a ultima linha sao
             * as informacoes utlizadas para a analise no tempo
             */
            for (int row = listOfElements.size(); row > 0; row--) {
                //@todo segmentation fault quando uma linha e nula no netlist
                type = listOfElements[row-1][0].substr(0,1);
                build(type, listOfElements[row - 1]);
            }
            /**
             * ultimas linhas passam a ser as primeiras
             */
            reverse(componentes.begin(), componentes.end());
        }

    private:
        /**
         * Tempo final a ser analisado
         */
        double tempoFinal;
        /**
         * Salto entre intervalos de tempo
         */
        double passo;
        /**
         * Numero de passos para cada ponto
         */
        double passoPonto;
        /**
         * Metodo de analise
         */
        string metodo;
        /**
         * Valor de teta a ser considerado no metodo de integracao
         */
        double teta;
        /**
         * Instante de tempo a ser analisado
         */
        double tempo;
        /**
         * numero de nos de tensao
         */
        vector<string> nodes;
        /**
         * numero de nos adicionado como auxiliares
         */
        vector<string> auxNodes;
        /**
         * nos que aparecem no resultado
         */
        vector<string> nosSaida;
        /**
         * lista contendo instancia de todos os componentes
         */
        vector<Components*> componentes;

        /**
         * Constroi instancia para cada componente
         * de acordo com a primeira letra encontrada na netlist
         */
        void build(string type, vector<string> element)
        {
            if (type == "R") { // Constroi o resistor
                Resistor *component = new Resistor(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                componentes.push_back(component);
            } else if (type == "C") {
                Capacitor *component = new Capacitor( // Constroi o capacitor
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                component->setTeta(getTeta());
                component->setPasso(getPasso());
                if (getTempo() == 0) { //Define o passo a ser utilizado no instante 0 do capacitor
                    component->setPasso(0);
                }
                componentes.push_back(component);
            } else if (type == "L") {
                Indutor *component = new Indutor( // Constroi o indutor
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                component->setPasso(getPasso());
                component->setTeta(getTeta());
                if (getTempo() == 0) { //Define o passo a ser utilizado no instante 0 do capacitor
                    component->setPasso(0);
                }
                auxNodes.push_back("j" + component->getNome());
                nosSaida.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                componentes.push_back(component);
            } else if (type == "E") {
                TensaoTensao *component = new TensaoTensao( // Constroi uma fonte de tensao controlada por tensao
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
            } else if (type == "F") {
                CorrenteCorrente *component = new CorrenteCorrente( // Constroi uma fonte de corrente controlada por correte
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                nosSaida.push_back("jx" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
            } else if (type == "G") {
                CorrenteTensao *component = new CorrenteTensao( // Constroi uma fonte de corrente controlada por tensao
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
            } else if (type == "H") {
                TensaoCorrente *component = new TensaoCorrente( //Constroi uma fonte de tensao controlada por corrente
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back("jx" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                nosSaida.push_back("jx" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
            } else if (type == "O") {
                AmpOp *component = new AmpOp(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4])
                );
                componentes.push_back(component);
                auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
            } else if (type == "D") {
                Diodo *component = new Diodo( // Constroi um diodo
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3]),
                    stod(element[4])
                );
                componentes.push_back(component);
            } else if (type == "K") {
                Transformador *component = new Transformador( // Constroi um transformador
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stof(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                nosSaida.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
            } else if (type == "Q") {
                Bipolar *component = new Bipolar( // Constroi um Bipolar
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    0, // Bipolar so tem 3 nos
                    element[4],
                    stod(element[5]),
                    stod(element[6]),
                    stod(element[7]),
                    stod(element[8]),
                    stod(element[9]),
                    stod(element[10])
                );
                componentes.push_back(component);
            } else if (type == "V") {
                if ((element[3]) == "DC") {
                    TensaoDC *component = new TensaoDC( // Constroi uma fonte de tensao DC
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4])
                    );
                    componentes.push_back(component);
                    auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                } else if ((element[3]) == "SIN") {
                    TensaoSenoidal *component = new TensaoSenoidal( // Constroi uma fonte de tensao senoidal
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4]),
                        stod(element[5]),
                        stod(element[6]),
                        stod(element[7]),
                        stod(element[8]),
                        stod(element[9]),
                        stod(element[10]),
                        tempo
                    );
                    componentes.push_back(component); // Adiciona o no auxiliar de acordo com a estampa
                    auxNodes.push_back("j" + component->getNome());
                } else if ((element[3]) == "PULSE") {
                    TensaoPulso *component = new TensaoPulso( // Constroi uma fonte de tensao pulsada
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4]),
                        stod(element[5]),
                        stod(element[6]),
                        stod(element[7]),
                        stod(element[8]),
                        stod(element[9]),
                        stod(element[10]),
                        stod(element[11]),
                        tempo,
                        getPasso()
                    );
                    componentes.push_back(component);
                    auxNodes.push_back("j" + component->getNome()); // Adiciona o no auxiliar de acordo com a estampa
                } else {
                    throw invalid_argument("Tipo de Fonte desconhecida");
                }
            } else if (type == "I") {
                if ((element[3]) == "DC") {
                    CorrenteDC *component = new CorrenteDC( // Constroi uma fonte de corrente DC
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4])
                    );
                    componentes.push_back(component);
                } else if ((element[3]) == "SIN") {
                    CorrenteSenoidal *component = new CorrenteSenoidal( // Constroi uma fonte de corrente senoidal
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4]),
                        stod(element[5]),
                        stod(element[6]),
                        stod(element[7]),
                        stod(element[8]),
                        stod(element[9]),
                        stod(element[10]),
                        tempo
                    );
                    componentes.push_back(component);
                } else if ((element[3]) == "PULSE") {
                    CorrentePulso *component = new CorrentePulso( // Constroi uma fonte de corrente pulsada
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4]),
                        stod(element[5]),
                        stod(element[6]),
                        stod(element[7]),
                        stod(element[8]),
                        stod(element[9]),
                        stod(element[10]),
                        stod(element[11]),
                        tempo,
                        getPasso()
                    );
                    componentes.push_back(component);
                } else {
                    throw invalid_argument("Tipo de Fonte desconhecida");
                }
            } else if (type == ".") { // Inicia parametros da analise por trapezio
                setTempoFinal(stod(element[1]));
                setPasso(stod(element[2]));
                setMetodo(element[3]);
                setTeta(stod(element[4]));
                setPassoPonto(stod(element[5]));
                //@todo melhorar a excecao
                if (! isTeta()) {
                    throw invalid_argument("So faz analise teta, sry");
                }
            } else if (type == "*"){
                //comentario so ignorar
            }
        }
};

#endif