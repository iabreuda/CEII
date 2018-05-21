#ifndef BIPOLAR
#define BIPOLAR
/**
 * Modelo basico de componentes
 */
#include "components4t.cpp"
 /**
  * Modelo basico do diogo
  */
#include "diodo.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Bipolar : public Components4t
{
    public:
        /**
         * Construtor
         */
        Bipolar(string n, int a, int b, int c, int d,
            string t, double alfa, double alfar,
            double isbe, double nvtbe , double isbc,
            double nvtbc) : Components4t(n, a, b, c, d)
        {
            setTipo(t);
            setAlfa(alfa);
            setAlfaR(alfar);
            setISBE(isbe);
            setISBC(isbc);
            setNVtBE(nvtbe);
            setNVtBC(nvtbc);
        }

        /**
         * Define o tipo do transistor bipolar
         * @param t valor da corrente
         */
        void setTipo(string t)
        {
            tipo = t;
        }

        /**
         * Define o parametro alfa do transistor bipolar
         * @param a parametro alfa
         */
        void setAlfa(double a)
        {
            alfa = a;
        }

        /**
         * Define o parametro alfaR do transistor bipolar
         * @param ar parametro alfaR
         */
        void setAlfaR(double ar)
        {
            alfaR = ar;
        }

        /**
         * Define a corrente reversa base-emissor
         * do transistor bipolar
         * @param isbe corrente reversa base-emissor
         */
        void setISBE(double isbe)
        {
            isBaseEmissor = isbe;
        }

        /**
         * Define a corrente reversa base-coletor
         * do transistor bipolar
         * @param isbc corrente reversa base-coletor
         */
        void setISBC(double isbc)
        {
            isBaseColetor = isbc;
        }

        /**
         * Define o nvt base-emissor do transistor bipolar
         * @param nvtbe variacao de temperatura base-emissor
         */
        void setNVtBE(double nvtbe)
        {
            nvtBaseEmissor = nvtbe;
        }

        /**
         * Define o nvt base-coletor do transistor bipolar
         * @param nvtbc variacao de temperatura base-coletor
         */
        void setNVtBC(double nvtbc)
        {
            nvtBaseColetor = nvtbc;
        }

        /**
         * Retorna o tipo do bipolar
         */
        string getTipo()
        {
            return tipo;
        }

        /**
         * Retorna o alfa do bipolar
         */
        double getAlfa()
        {
            return alfa;
        }

        /**
         * Retorna o alfaR do bipolar
         */
        double getAlfaR()
        {
            return alfaR;
        }

        /**
         * Retorna o is base-emissor do bipolar
         */
        double getIsBaseEmissor()
        {
            return isBaseEmissor;
        }

        /**
         * Retorna o is base-coletor do bipolar
         */
        double getIsBaseColetor()
        {
            return isBaseColetor;
        }

        /**
         * Retorna o vt base-emissor do bipolar
         */
        double getNVtBaseEmissor()
        {
            return nvtBaseEmissor;
        }

        /**
         * Retorna o vt base-coletor do bipolar
         */
        double getNVtBaseColetor()
        {
            return nvtBaseColetor;
        }

        /**
         * Estampa da matriz nodal modificada para um bipolar
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
            /**
             * Pega a tensao no ramo no instante de tempo anterior
             */
            double tensaoRamoVBE = resultado[getNoB()] - resultado[getNoC()]; // Tensao VBE
            double tensaoRamoVBC = resultado[getNoB()] - resultado[getNoA()]; // Tensao VBC
            /**
             * Descarta o no Zero uma vez que ele e linearmente dependente
             */
            if (getNoA() == 0) {
                tensaoRamoVBC = resultado[getNoB()]; // Tensao VBC
            }
            if (getNoB() == 0) {
                tensaoRamoVBE = -1*resultado[getNoC()]; // Tensao VBE
                tensaoRamoVBC = -1*resultado[getNoA()]; // Tensao VBC
            }
            if (getNoC() == 0) {
                tensaoRamoVBE = 1*resultado[getNoB()]; // Tensao VBE
            }
            /**
             * Initializa os diodos para modelagem Ebers-moll
             */
            Diodo *diodoBaseEmissor = new Diodo(
                "dbe", getNoB(), getNoC(), getIsBaseEmissor(), getNVtBaseEmissor()
            );
            Diodo *diodoBaseColetor = new Diodo(
                "dbc", getNoB(), getNoA(), getIsBaseColetor(), getNVtBaseColetor()
            );
            /**
             * Parametros do diodo
             */
            double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVBC);
            double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVBC);
            double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVBE);
            double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVBE);
            /**
             * Estampa do Bipolar
             */
            condutancia[getNoA()][getNoA()] += 1/resistenciaColetor;
            condutancia[getNoA()][getNoB()] += -1/resistenciaColetor;
            condutancia[getNoB()][getNoA()] += -1/resistenciaColetor;
            condutancia[getNoB()][getNoB()] += (1/resistenciaColetor + 1/resistenciaEmissor);
            condutancia[getNoB()][getNoC()] += -1/resistenciaEmissor;
            condutancia[getNoC()][getNoB()] += -1/resistenciaEmissor;;
            condutancia[getNoC()][getNoC()] += 1/resistenciaEmissor;;

            correntes[getNoA()] += (correnteColetor - (getAlfa()*correnteEmissor) - (getAlfa()*(1/resistenciaEmissor)*tensaoRamoVBE));
            correntes[getNoB()] += ((getAlfa()*correnteEmissor) + (getAlfaR()*correnteColetor) + (getAlfa()*(1/resistenciaEmissor)*tensaoRamoVBE)
                + (getAlfaR()*(1/resistenciaColetor)*tensaoRamoVBC) - correnteEmissor - correnteColetor);
            correntes[getNoC()] += (correnteEmissor - (getAlfaR()*correnteColetor) - (getAlfaR()*(1/resistenciaColetor)*tensaoRamoVBC));
        }

        /**
         * Desestampa da matriz nodal modificada para um bipolar
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void desestampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<double> resultado)
        {
            /**
             * Pega a tensao no ramo no instante de tempo anterior
             */
            double tensaoRamoVBE = resultado[getNoB()] - resultado[getNoC()]; // Tensao VBE
            double tensaoRamoVBC = resultado[getNoB()] - resultado[getNoA()]; // Tensao VBC
            /**
             * Descarta o no Zero uma vez que ele e linearmente dependente
             */
            if (getNoA() == 0) {
                tensaoRamoVBC = resultado[getNoB()]; // Tensao VBC
            }
            if (getNoB() == 0) {
                tensaoRamoVBE = -1*resultado[getNoC()]; // Tensao VBE
                tensaoRamoVBC = -1*resultado[getNoA()]; // Tensao VBC
            }
            if (getNoC() == 0) {
                tensaoRamoVBE = 1*resultado[getNoB()]; // Tensao VBE
            }
            /**
             * Initializa os diodos para modelagem Ebers-moll
             */
            Diodo *diodoBaseEmissor = new Diodo(
                "dbe", getNoB(), getNoC(), getIsBaseEmissor(), getNVtBaseEmissor()
            );
            Diodo *diodoBaseColetor = new Diodo(
                "dbc", getNoB(), getNoA(), getIsBaseColetor(), getNVtBaseColetor()
            );
            /**
             * Parametros do diodo
             */
            double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVBC);
            double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVBC);
            double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVBE);
            double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVBE);
            /**
             * Estampa do Bipolar
             */
            condutancia[getNoA()][getNoA()] += -1/resistenciaColetor;
            condutancia[getNoA()][getNoB()] += 1/resistenciaColetor;
            condutancia[getNoB()][getNoA()] += 1/resistenciaColetor;
            condutancia[getNoB()][getNoB()] += -1*(1/resistenciaColetor + 1/resistenciaEmissor);
            condutancia[getNoB()][getNoC()] += 1/resistenciaEmissor;
            condutancia[getNoC()][getNoB()] += 1/resistenciaEmissor;;
            condutancia[getNoC()][getNoC()] += -1/resistenciaEmissor;;

            correntes[getNoA()] += -1*(correnteColetor - (getAlfa()*correnteEmissor) - (getAlfa()*(1/resistenciaEmissor)*tensaoRamoVBE));
            correntes[getNoB()] += -1*((getAlfa()*correnteEmissor) + (getAlfaR()*correnteColetor) + (getAlfa()*(1/resistenciaEmissor)*tensaoRamoVBE)
                + (getAlfaR()*(1/resistenciaColetor)*tensaoRamoVBC) - correnteEmissor - correnteColetor);
            correntes[getNoC()] += -1*(correnteEmissor - (getAlfaR()*correnteColetor) - (getAlfaR()*(1/resistenciaColetor)*tensaoRamoVBC));
        }

    private:
        /**
         * Tipo do Bipolar
         */
        string tipo;
        /**
         * Parametro alfa
         */
        double alfa;
        /**
         * Parametro alfaR
         */
        double alfaR;
        /**
         * Corrente reversa base-emissor
         */
        double isBaseEmissor;
        /**
         * Corrente reversa base-coletor
         */
        double isBaseColetor;
        /**
         * vt de variacao de temperatura base-emissor
         */
        double nvtBaseEmissor;
        /**
         * vt de variacao de temperatura base-coletor
         */
        double nvtBaseColetor;
};

#endif