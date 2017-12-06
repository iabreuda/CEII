#ifndef PULSO
#define PULSO

/**
 * Inclui:
 *  - sin
 */
#include <math.h>
/**
 * Modelo basico de fontes independetes
 */
#include "fonteindependente.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Pulso : public FonteIndependente
{
    public:
        /**
         * Construtor
         */
        Pulso(string n, int a, int b,
            double a1, double a2, double delay,
            double tSub, double tDes, double tOn,
            double per, double cic, double t, double p) : FonteIndependente(n, a, b)
        {
            setAmp1(a1);
            setAmp2(a2);
            setAtraso(delay);
            setTempoSubida(tSub);
            setTempoDescida(tDes);
            setTempoLigada(tOn);
            setPeriodo(per);
            setCiclo(cic);
            setTempo(t);
            setPasso(p);
            setValor();
        }

        /**
         * Define o valor da amplitude 1
         * @param a1 amplitude 1
         */
        void setAmp1(double a1)
        {
            amp1 = a1;
        }

        /**
         * Define o valor da amplitude 2
         * @param a2 amplitude 2
         */
        void setAmp2(double a2)
        {
            amp2 = a2;
        }

        /**
         * Define o atraso onde a amplitude 1 ficara antes
         * de subir para a amlitude 2
         * @param delay atraso antes de iniciar a subida
         */
        void setAtraso(double delay)
        {
            atraso = delay;
        }

        /**
         * Define o Tempo ate sair da ampltude 1 para a amplitude 2
         * linear
         * @param tSub tempo de subida
         */
        void setTempoSubida(double tSub)
        {
            tSubida = tSub;
        }

        /**
         * Define o tempo para sair da amplitude 2 para a amplitude 1
         * @param tDes tempo de descida
         */
        void setTempoDescida(double tDes)
        {
            tDescida = tDes;
        }

        /**
         * Define o tempo de passo
         */
        void setPasso(double p)
        {
            passo = p;
        }

        /**
         * Define o tempo em que a fonte fica na amplitude 2
         * @param tOn tempo da fonte ligada
         */
        void setTempoLigada(double tOn)
        {
            tLigada = tOn;
        }

        /**
         * Define o tempo do periodo
         * @param per periodo de duracao de um ciclo
         */
        void setPeriodo(double per)
        {
            periodo = per;
        }

        /**
         * Define o numero de ciclos de execucao
         * @param cic numero de ciclos
         */
        void setCiclo(double cic)
        {
            ciclo = cic;
        }

        /**
         * Define o instante de tempo atual
         * @param t instante de tempo atual
         */
        void setTempo(double t)
        {
            tempo = t;
        }

        /**
         * Retorna a amplitude 1
         */
        double getAmp1()
        {
            return amp1;
        }

        /**
         * Retorna o passo
         */
        double getPasso()
        {
            return passo;
        }

        /**
         * Retorna a amplitude 2
         */
        double getAmp2()
        {
            return amp2;
        }

        /**
         * Retorna o tempo de duracao da amp 1
         */
        double getAtraso()
        {
            return atraso;
        }

        /**
         * Retorna o tempo ate da amp1 ate a amp2
         */
        double getTempoSubida()
        {
            return tSubida;
        }

        /**
         * Retorna o tempo ate da amp2 ate a amp1
         */
        double getTempoDescida()
        {
            return tDescida;
        }

        /**
         * Retorna o tempo de duracao da amp 2
         */
        double getTempoLigada()
        {
            return tLigada;
        }

        /**
         * Retorna o tempo de duracao do periodo
         */
        double getPeriodo()
        {
            return periodo;
        }

        /**
         * Retorna o numero de ciclos da fonte
         */
        double getCiclo()
        {
            return ciclo;
        }

        /**
         * Retorna o instante de tempo atual
         */
        double getTempo()
        {
            return tempo;
        }

        /**
         * Define o valor atual da fonte
         * no instante de tempo presente
         */
        void setValor()
        {
            /**
             * Modela casos em que o tempo de subida e descida
             * sao iguais a 0 para evitar problemas na plotagem
             * do grafico
             */
            if (getTempoSubida() == 0) {
                setTempoSubida(getPasso());
            }
            if (getTempoDescida() == 0) {
                setTempoDescida(getPasso());
            }

            /**
             * Regiao em que a fonte se encontra dentro do periodo
             */
            double iPeriod = fmod((getTempo() - getAtraso()), getPeriodo());

            if (getTempo() <= getAtraso()) {
                valor = getAmp1();
            }  else if (getTempo() > ((getPeriodo()* getCiclo()) + getAtraso())) {
                valor = getAmp1();
            } else if (iPeriod < getTempoSubida()) {
                double deltaAmp = getAmp2() - getAmp1();
                double dPdts = iPeriod / getTempoSubida();
                valor = ((deltaAmp * dPdts) + getAmp1());
            } else if (iPeriod >= getTempoSubida() && (iPeriod <= (getTempoSubida() + getTempoLigada()))) {
                valor = getAmp2();
            } else if ((iPeriod > (getTempoSubida() + getTempoLigada())) && (iPeriod < (getTempoDescida() + getTempoSubida() + getTempoLigada()))) {
                double deltaAmp = getAmp1() - getAmp2();
                double dPdts = ((iPeriod - getTempoSubida() - getTempoLigada()) / getTempoDescida());
                valor = (deltaAmp * dPdts) + getAmp2();
            } else {
                valor = getAmp1();
            }
        }

        /**
         * Pega o valor de tensao
         */
        double getValor()
        {
            return valor;
        }

    private:
        /**
         * Amplitude inicial
         */
        double amp1;

        /**
         * Amplitude apos o fim do atraso
         */
        double amp2;

        /**
         * Tempo em que o sinal ficara em
         * cada amplitude
         */
        double atraso;

        /**
         * tempo necessario para a fonte passar
         * linearmente da amp 1 para a amp 2
         * Sobe
         */
        double tSubida;

        /**
         * tempo necessario para a fonte passar
         * linearmente da amp 2 para a amp 1
         * Desce
         */
        double tDescida;

        /**
         * tempo em que a fonte fica na amplitude 2
         */
        double tLigada;

        /**
         * tempo para um ciclo
         */
        double periodo;

        /**
         * numero de vezes que o preiodo
         * ira se repetir
         */
        double ciclo;

        /**
         * Instante de tempo atual
         */
        double tempo;
        /**
         * Valor da tensao em um determinado
         * instante de tempo
         */
        double valor;
        /**
         * Passo da analise do trapezio
         */
        double passo;
};

#endif