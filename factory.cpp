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
 * Modelo de resistor linear
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
 * Modelo de resistor nlinear
 */
#include "resistornlinear.cpp"
/**
 * Modelo de amplificador operacional
 */
#include "ampop.cpp"
/**
 * Modelo de transformador
 */
#include "transformador.cpp"
/**
 * Modelo de transformador
 */
#include "chave.cpp"
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

        vector<Components*> getComponents()
        {
            return componentes;
        }

        double getPasso()
        {
            return passo;
        }

        double getTempoFinal()
        {
            return tempoFinal;
        }

        double getPassoPonto()
        {
            return passoPonto;
        }

        string getMetodo()
        {
            return metodo;
        }

        double getTempo()
        {
            return tempo;
        }

        int getNodesSize()
        {
            return nodes.size();
        }

        int getAuxNodesSize()
        {
            return auxNodes.size();
        }

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
            sort(nodes.begin(), nodes.end());
            nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

            sort(auxNodes.begin(), auxNodes.end());
            auxNodes.erase(unique(auxNodes.begin(), auxNodes.end()), auxNodes.end());

            allNodes.insert(allNodes.end(), nodes.begin(), nodes.end());
            allNodes.insert(allNodes.end(), auxNodes.begin(), auxNodes.end());

            return allNodes;
        }

        void setPasso(double v)
        {
            passo = v;
        }

        void setTempoFinal(double v)
        {
            tempoFinal = v;
        }

        void setPassoPonto(double v)
        {
            passoPonto = v;
        }

        void setMetodo(string v)
        {
            metodo = v;
        }

        void setTempo(double t)
        {
            tempo = t;
        }

        bool isTrapezio()
        {
            return getMetodo() == "TRAP";
        }

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
        double tempoFinal;
        double passo;
        double passoPonto;
        string metodo;
        double tempo;
        vector<string> nodes;
        vector<string> auxNodes;

        vector<Components*> componentes;

        void build(string type, vector<string> element)
        {
            if (type == "R") {
                Resistor *component = new Resistor(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                componentes.push_back(component);
            } else if (type == "C") {
                Capacitor *component = new Capacitor(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                component->setPasso(getPasso());
                if (getTempo() == 0) {
                    component->setPasso(0);
                }
                componentes.push_back(component);
            } else if (type == "L") {
                Indutor *component = new Indutor(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
                component->setPasso(getPasso());
                if (getTempo() == 0) {
                    component->setPasso(0);
                }
                auxNodes.push_back("j" + component->getNome());
                componentes.push_back(component);
            } else if (type == "E") {
                TensaoTensao *component = new TensaoTensao(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back("j" + component->getNome());
            } else if (type == "F") {
                CorrenteCorrente *component = new CorrenteCorrente(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back(
                    "j" +
                    to_string(component->getNoC()) +
                    "_" +
                    to_string(component->getNoD())
                );
            } else if (type == "G") {
                CorrenteTensao *component = new CorrenteTensao(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
            } else if (type == "H") {
                TensaoCorrente *component = new TensaoCorrente(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back(
                    "j" +
                    to_string(component->getNoC()) +
                    "_" +
                    to_string(component->getNoD())
                );
                auxNodes.push_back("j" + component->getNome());
            } else if (type == "O") {
                AmpOp *component = new AmpOp(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4])
                );
                componentes.push_back(component);
                auxNodes.push_back(
                    "j" +
                    to_string(component->getNoA()) +
                    "_" +
                    to_string(component->getNoB())
                );
            } else if (type == "N") {
                ResistorNLinear *component = new ResistorNLinear(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3]),
                    stod(element[4]),
                    stod(element[5]),
                    stod(element[6]),
                    stod(element[7]),
                    stod(element[8]),
                    stod(element[9]),
                    stod(element[10])
                );
                componentes.push_back(component);
            } else if (type == "K") {
                Transformador *component = new Transformador(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stof(element[5])
                );
                componentes.push_back(component);
                auxNodes.push_back(
                    "j" +
                    to_string(component->getNoC()) +
                    "_" +
                    to_string(component->getNoD())
                );
            } else if (type == "$") {
                Chave *component = new Chave(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4]),
                    stod(element[5]),
                    stod(element[6]),
                    stod(element[7])
                );
                componentes.push_back(component);
            } else if (type == "V") {
                if ((element[3]) == "DC") {
                    TensaoDC *component = new TensaoDC(
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4])
                    );
                    componentes.push_back(component);
                    auxNodes.push_back("j" + component->getNome());
                } else if ((element[3]) == "SIN") {
                    TensaoSenoidal *component = new TensaoSenoidal(
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
                    auxNodes.push_back("j" + component->getNome());
                } else if ((element[3]) == "PULSE") {
                    TensaoPulso *component = new TensaoPulso(
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
                        tempo
                    );
                    componentes.push_back(component);
                    auxNodes.push_back("j" + component->getNome());
                } else {
                    throw invalid_argument("Tipo de Fonte desconhecida");
                }
            } else if (type == "I") {
                if ((element[3]) == "DC") {
                    CorrenteDC *component = new CorrenteDC(
                        element[0],
                        stoi(element[1]),
                        stoi(element[2]),
                        stod(element[4])
                    );
                    componentes.push_back(component);
                } else if ((element[3]) == "SIN") {
                    CorrenteSenoidal *component = new CorrenteSenoidal(
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
                    CorrentePulso *component = new CorrentePulso(
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
                        tempo
                    );
                    componentes.push_back(component);
                } else {
                    throw invalid_argument("Tipo de Fonte desconhecida");
                }
            } else if (type == ".") {
                setTempoFinal(stod(element[1]));
                setPasso(stod(element[2]));
                setMetodo(element[3]);
                setPassoPonto(stod(element[4]));
                //@todo melhorar a excecao
                if (! isTrapezio()) {
                    throw invalid_argument("So faz analise por trapezio, sry");
                }
            } else if (type == "*"){
                //comentario so ignorar
            }
        }
};

#endif