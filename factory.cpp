#ifndef FACTORY
#define FACTORY

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


/* Necessario para nao precisar escrever std:: */
using namespace std;

class Factory
{
    public:
        /**
         * Construtor
         */
        Factory(vector<vector<string> > listOfElements)
        {
            setup(listOfElements);
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

        bool isTrapezio()
        {
            return getMetodo() == "TRAP";
        }

    private:
        double tempoFinal;
        double passo;
        double passoPonto;
        string metodo;

        vector<Components*> componentes;
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
        }

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
                componentes.push_back(component);
            } else if (type == "L") {
                Indutor *component = new Indutor(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stod(element[3])
                );
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
            } else if (type == "O") {
                AmpOp *component = new AmpOp(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stoi(element[4])
                );
                componentes.push_back(component);
            } else if (type == "N") {
                ResistorNLinear *component = new ResistorNLinear(
                    element[0],
                    stoi(element[1]),
                    stoi(element[2]),
                    stoi(element[3]),
                    stod(element[4]),
                    stod(element[5]),
                    stod(element[6]),
                    stod(element[7]),
                    stod(element[8]),
                    stod(element[9]),
                    stod(element[10]),
                    stod(element[11])
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