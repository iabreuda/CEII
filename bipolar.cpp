#ifndef BIPOLAR
#define BIPOLAR
/**
 * Modelo basico de componentes
 */
#include "components4t.cpp"
 /**
  * Modelo basico do diodo
  */
#include "diodo.cpp"
 /**
  * Modelo basico de fonte de corrente dc
  */
#include "correntedc.cpp"
 /**
  * Modelo basico de fonte contralada corrente tensao
  */
#include "correntetensao.cpp"

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
            setLinearidade(false);
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
            double tensaoRamoVEB = resultado[getNoC()] - resultado[getNoB()]; // Tensao VEB
            double tensaoRamoVCB = resultado[getNoA()] - resultado[getNoB()]; // Tensao VCB
            /**
             * Descarta o no Zero uma vez que ele e linearmente dependente
             */
            if (getNoA() == 0) {
                tensaoRamoVBC = resultado[getNoB()]; // Tensao VBC
                tensaoRamoVCB = -1*resultado[getNoB()]; // Tensao VCB
            }
            if (getNoB() == 0) {
                tensaoRamoVBE = -1*resultado[getNoC()]; // Tensao VBE
                tensaoRamoVBC = -1*resultado[getNoA()]; // Tensao VBC
                tensaoRamoVEB = resultado[getNoC()]; // Tensao VEB
                tensaoRamoVCB = resultado[getNoA()]; // Tensao VCB
            }
            if (getNoC() == 0) {
                tensaoRamoVBE = resultado[getNoB()]; // Tensao VBE
                tensaoRamoVEB = -1*resultado[getNoB()]; // Tensao VEB
            }

            if (getTipo() == "NPN") {
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
                 * estampa os diodos
                 */
                diodoBaseEmissor->estampar(condutancia, correntes, nodes, resultado);
                diodoBaseColetor->estampar(condutancia, correntes, nodes, resultado);
                /**
                 * Parametros do diodo
                 */
                double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVBC);
                double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVBC);
                double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVBE);
                double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVBE);
                /**
                 * Initializa as fontes de corrente
                 */
                CorrenteDC *correnteAlfaIe = new CorrenteDC(
                    "aie", getNoA(), getNoB(), getAlfa()*correnteEmissor
                );
                CorrenteDC *correnteAlfaRIc = new CorrenteDC(
                    "aie", getNoC(), getNoB(), getAlfaR()*correnteColetor
                );
                /**
                 * Estampa fontes de corrente
                 */
                correnteAlfaIe->estampar(condutancia, correntes, nodes, resultado);
                correnteAlfaRIc->estampar(condutancia, correntes, nodes, resultado);
                /**
                 * Initializa as fontes de corrente controladas
                 */
                CorrenteTensao *correnteAlfaGeVbe = new CorrenteTensao(
                    "aie", getNoA(), getNoB(), getNoB(), getNoC(), getAlfa()*(1/resistenciaEmissor)
                );
                CorrenteTensao *correnteAlfaRGcVbc = new CorrenteTensao(
                    "aie", getNoC(), getNoB(), getNoB(), getNoA(), getAlfaR()*(1/resistenciaColetor)
                );
                /**
                 * Estampa fontes de corrente controladas
                 */
                correnteAlfaGeVbe->estampar(condutancia, correntes, nodes, resultado);
                correnteAlfaRGcVbc->estampar(condutancia, correntes, nodes, resultado);
            } else if (getTipo() == "PNP") {
                /**
                 * Initializa os diodos para modelagem Ebers-moll
                 */
                Diodo *diodoBaseEmissor = new Diodo(
                    "dbe", getNoC(), getNoB(), getIsBaseEmissor(), getNVtBaseEmissor()
                );
                Diodo *diodoBaseColetor = new Diodo(
                    "dbc", getNoA(), getNoB(), getIsBaseColetor(), getNVtBaseColetor()
                );
                /**
                 * estampa os diodos
                 */
                diodoBaseEmissor->estampar(condutancia, correntes, nodes, resultado);
                diodoBaseColetor->estampar(condutancia, correntes, nodes, resultado);
                /**
                 * Parametros do diodo
                 */
                double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVCB);
                double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVCB);
                double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVEB);
                double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVEB);
                /**
                 * Initializa as fontes de corrente
                 */
                CorrenteDC *correnteAlfaIe = new CorrenteDC(
                    "aie", getNoB(), getNoA(), getAlfa()*correnteEmissor
                );
                CorrenteDC *correnteAlfaRIc = new CorrenteDC(
                    "aie", getNoB(), getNoC(), getAlfaR()*correnteColetor
                );
                /**
                 * Estampa fontes de corrente
                 */
                correnteAlfaIe->estampar(condutancia, correntes, nodes, resultado);
                correnteAlfaRIc->estampar(condutancia, correntes, nodes, resultado);
                /**
                 * Initializa as fontes de corrente controladas
                 */
                CorrenteTensao *correnteAlfaGeVbe = new CorrenteTensao(
                    "aie", getNoB(), getNoA(), getNoB(), getNoC(), getAlfa()*(1/resistenciaEmissor)
                );
                CorrenteTensao *correnteAlfaRGcVbc = new CorrenteTensao(
                    "aie", getNoB(), getNoC(), getNoB(), getNoA(), getAlfaR()*(1/resistenciaColetor)
                );
                /**
                 * Estampa fontes de corrente controladas
                 */
                correnteAlfaGeVbe->estampar(condutancia, correntes, nodes, resultado);
                correnteAlfaRGcVbc->estampar(condutancia, correntes, nodes, resultado);
            } else {
                throw invalid_argument("Tipo de transistor desconhecido");
            }
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
            double tensaoRamoVEB = resultado[getNoC()] - resultado[getNoB()]; // Tensao VEB
            double tensaoRamoVCB = resultado[getNoA()] - resultado[getNoB()]; // Tensao VCB
            /**
             * Descarta o no Zero uma vez que ele e linearmente dependente
             */
            if (getNoA() == 0) {
                tensaoRamoVBC = resultado[getNoB()]; // Tensao VBC
                tensaoRamoVCB = -1*resultado[getNoB()]; // Tensao VCB
            }
            if (getNoB() == 0) {
                tensaoRamoVBE = -1*resultado[getNoC()]; // Tensao VBE
                tensaoRamoVBC = -1*resultado[getNoA()]; // Tensao VBC
                tensaoRamoVEB = resultado[getNoC()]; // Tensao VEB
                tensaoRamoVCB = resultado[getNoA()]; // Tensao VCB
            }
            if (getNoC() == 0) {
                tensaoRamoVBE = resultado[getNoB()]; // Tensao VBE
                tensaoRamoVEB = -1*resultado[getNoB()]; // Tensao VEB
            }

            if (getTipo() == "NPN") {
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
                 * desestampa os diodos
                 */
                diodoBaseEmissor->desestampar(condutancia, correntes, resultado);
                diodoBaseColetor->desestampar(condutancia, correntes, resultado);
                /**
                 * Parametros do diodo
                 */
                double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVBC);
                double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVBC);
                double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVBE);
                double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVBE);
                /**
                 * Initializa as fontes de corrente
                 */
                CorrenteDC *correnteAlfaIe = new CorrenteDC(
                    "aie", getNoA(), getNoB(), getAlfa()*correnteEmissor
                );
                CorrenteDC *correnteAlfaRIc = new CorrenteDC(
                    "aie", getNoC(), getNoB(), getAlfaR()*correnteColetor
                );
                /**
                 * desestampa fontes de corrente
                 */
                correnteAlfaIe->desestampar(condutancia, correntes, resultado);
                correnteAlfaRIc->desestampar(condutancia, correntes, resultado);
                /**
                 * Initializa as fontes de corrente controladas
                 */
                CorrenteTensao *correnteAlfaGeVbe = new CorrenteTensao(
                    "aie", getNoA(), getNoB(), getNoB(), getNoC(), getAlfa()*(1/resistenciaEmissor)
                );
                CorrenteTensao *correnteAlfaRGcVbc = new CorrenteTensao(
                    "aie", getNoC(), getNoB(), getNoB(), getNoA(), getAlfaR()*(1/resistenciaColetor)
                );
                /**
                 * desestampa fontes de corrente controladas
                 */
                correnteAlfaGeVbe->desestampar(condutancia, correntes, resultado);
                correnteAlfaRGcVbc->desestampar(condutancia, correntes, resultado);
            } else if (getTipo() == "PNP") {
                /**
                 * Initializa os diodos para modelagem Ebers-moll
                 */
                Diodo *diodoBaseEmissor = new Diodo(
                    "dbe", getNoC(), getNoB(), getIsBaseEmissor(), getNVtBaseEmissor()
                );
                Diodo *diodoBaseColetor = new Diodo(
                    "dbc", getNoA(), getNoB(), getIsBaseColetor(), getNVtBaseColetor()
                );
                /**
                 * desestampa os diodos
                 */
                diodoBaseEmissor->desestampar(condutancia, correntes, resultado);
                diodoBaseColetor->desestampar(condutancia, correntes, resultado);
                /**
                 * Parametros do diodo
                 */
                double correnteColetor = diodoBaseColetor->getCorrente(tensaoRamoVCB);
                double resistenciaColetor = diodoBaseColetor->getResistencia(tensaoRamoVCB);
                double correnteEmissor = diodoBaseEmissor->getCorrente(tensaoRamoVEB);
                double resistenciaEmissor = diodoBaseEmissor->getResistencia(tensaoRamoVEB);
                /**
                 * Initializa as fontes de corrente
                 */
                CorrenteDC *correnteAlfaIe = new CorrenteDC(
                    "aie", getNoB(), getNoA(), getAlfa()*correnteEmissor
                );
                CorrenteDC *correnteAlfaRIc = new CorrenteDC(
                    "aie", getNoB(), getNoC(), getAlfaR()*correnteColetor
                );
                /**
                 * desestampa fontes de corrente
                 */
                correnteAlfaIe->desestampar(condutancia, correntes, resultado);
                correnteAlfaRIc->desestampar(condutancia, correntes, resultado);
                /**
                 * Initializa as fontes de corrente controladas
                 */
                CorrenteTensao *correnteAlfaGeVbe = new CorrenteTensao(
                    "aie", getNoB(), getNoA(), getNoB(), getNoC(), getAlfa()*(1/resistenciaEmissor)
                );
                CorrenteTensao *correnteAlfaRGcVbc = new CorrenteTensao(
                    "aie", getNoB(), getNoC(), getNoB(), getNoA(), getAlfaR()*(1/resistenciaColetor)
                );
                /**
                 * desestampa fontes de corrente
                 */
                correnteAlfaGeVbe->desestampar(condutancia, correntes, resultado);
                correnteAlfaRGcVbc->desestampar(condutancia, correntes, resultado);
            } else {
                throw invalid_argument("Tipo de transistor desconhecido");
            }
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