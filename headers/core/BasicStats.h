/*!
 Author: Faris Alqadah
 Basic stat functions

 */


#ifndef BASICSTATS_H
#define	BASICSTATS_H

#include "NCluster.h"
#include "NRCluster.h"



/*!
 Computes the mean of a hypergeometrically distributed random varaiable
    \param n see wiki entry of hypergeomtric distribution
    \param m see wiki entry of hypergeomtric distribution
    \param NN corresponds to N in wiki entry of hypergeomtric distribution
 */
double Hypgeo_Mean(int n, int m, int NN);

/*!
 Computes the standard devation of a hypergeometrically distributed random varaiable
    \param n see wiki entry of hypergeomtric distribution
    \param m see wiki entry of hypergeomtric distribution
    \param NN corresponds to N in wiki entry of hypergeomtric distribution
 */
double Hypgeo_Dev(int n, int m, int NN);


/*!
 Computes the mean of a beta-binomial distributed random varaiable
    \param n see wiki entry of beta-binomial distribution
    \param alpha see wiki entry of beta-binomial distribution
    \param beta see wiki entry of beta-binomial distribution
 */
double BetaBinomial_Mean(int n, int alpha, int beta);

/*!
 Computes the standard devation of a beta-binomial distributed random varaiable
    \param n see wiki entry of beta-binomial distribution
    \param alpha see wiki entry of beta-binomial distribution
    \param beta see wiki entry of beta-binomial distribution
 */
double BetaBinomial_Dev(int n, int alpha, int beta);



/*!
 Computes a z-score
    \param x the value compute z-score for
    \param mean the mean of the sample
    \parm std the standard deviation of the sample
 */
double Z_Score(double x, double mean, double std);


#endif	/* BASICSTATS_H */

