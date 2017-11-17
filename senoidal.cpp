#ifndef SENOIDAL
#define SENOIDAL

/**
 * Inclui:
 *  - sin
 */
#include <math.h>
/**
 * Modelo basico de componentes
 */
#include "fonteindependente.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Senoidal : public FonteIndependente
{
    public:
        /**
         * Construtor
         */
        Senoidal(string n, int a, int b,
            double a0, double a, double f,
            double delay, double damp, double p,
            double cic, double t) : FonteIndependente(n, a, b)
        {
            setNivelDC(a0);
            setAmplitude(a);
            setFrequencia(f);
            setAtraso(delay);
            setAmortecimento(damp);
            setFase(p);
            setCiclos(cic);
            setTempo(t);
        }

        /**
         * Define o nivel DC da fonte
         * @param a0 nivel DC
         */
        void setNivelDC(double a0)
        {
            nivelDC = a0;
        }

        /**
         * Define a amplitude da fonte
         * @param a amplitude
         */
        void setAmplitude(double a)
        {
            amplitude = a;
        }

        /**
         * Define a frenquencia de oscilacao
         * @param f frequencia
         */
        void setFrequencia(double f)
        {
            frequencia = f;
        }

        /**
         * Define o atraso na senoide
         * @param delay atraso
         */
        void setAtraso(double delay)
        {
            atraso = delay;
        }

        /**
         * Define o amortecimento da oscilacao
         * @param damp amortecimento
         */
        void setAmortecimento(double damp)
        {
            atraso = damp;
        }

        /**
         * Define a fase da senoide
         * @param p fase
         */
        void setFase(double p)
        {
            fase = p;
        }

        /**
         * Define o numero de ciclos da fonte
         * @param cic ciclos
         */
        void setCiclos(double cic)
        {
            ciclos = cic;
        }

        /**
         * Define o instante de tempo atual
         * @param t tempo
         */
        void setTempo(double t)
        {
            tempo = t;
        }

        /**
         * Define o valor da fonte
         */
        void setValor()
        {
            float amplitude;
            float senoide;

            amplitude = getAmplitude() * exp((-1 * getAmortecimento()) * (getTempo() - getAtraso()));
            senoide = sin(2 * M_PI * getFrequencia() * (getTempo() - getAtraso()) + ((M_PI/180) * getFase()))
            valor = getNivelDC() + (amplitude * senoide);
        }

        /**
         * Retorna o nivel DC
         */
        double getNivelDC()
        {
            return nivelDC;
        }

        /**
         * Retorna a amplitude
         */
        double getAmplitude()
        {
            return amplitude;
        }

        /**
         * Retorna a frequencia
         */
        double getFrequencia()
        {
            return frequencia;
        }

        /**
         * Retorna o atraso
         */
        double getAtraso()
        {
            return atraso;
        }

        /**
         * Retorna o amortecimento
         */
        double getAmortecimento()
        {
            return amortecimento;
        }

        /**
         * Retorna a fase
         */
        double getFase()
        {
            return fase;
        }

        /**
         * Retorna numero de ciclos
         */
        double getCiclos()
        {
            return ciclos;
        }

        /**
         * Retorna tempo atual
         */
        double getTempo()
        {
            return tempo;
        }

    private:
        /**
         * Nivel DC da senoide
         */
        double nivelDC;

        /**
         * Amplitude da onda
         */
        double amplitude;

        /**
         * Frequencia de oscilacao
         */
        double frequencia;

        /**
         * Atraso da senoide
         */
        double atraso;

        /**
         * Amortecimento da oscilacao
         */
        double amortecimento;

        /**
         * Fase da senoide
         */
        double fase;

        /**
         * Ciclos da fonte
         */
        double ciclos;

        /**
         * Tempo atual
         */
        double tempo;
};

#endif