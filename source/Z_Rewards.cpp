#include "../headers/Z_Rewards.h"

double Exp_Sat_HypGeo_Score(NCluster *a, int obj, int domain,double w, RelationGraph *hin){

    IOSet *neighbors = hin->GetNeighbors(domain);
    double score = 0.0;
    for(int i=0; i < neighbors->Size(); i++){
        double B= a->GetSetById( neighbors->At(i))->Size() ;
        if(B > 0){
            Context *currContext = hin->GetContext(domain,neighbors->At(i));
            IOSet *tmp = Intersect(currContext->GetSet(domain,obj),a->GetSetById( neighbors->At(i) ));
            int n = a->GetSetById( neighbors->At(i) )->Size();
            int m = currContext->GetSet(domain,obj)->Size();
            int NN =currContext->GetNumSets(neighbors->At(i));
            double expected = Hypgeo_Mean(n,m,NN);
            double std = Hypgeo_Dev(n,m,NN);
            double ones = tmp->Size();
            double tfactor = 1.0;///pow(tired[domain][obj],1.5);
            double zscore = Z_Score(ones,expected,std);
            double z = tfactor*zscore-w;
            score += z;
            delete tmp;
        }
    }
    delete neighbors;
    return score;
}

double Exp_Sat_BetaBinomail_Score(NCluster *a, int obj, int domain,double w, RelationGraph *hin){

    IOSet *neighbors = hin->GetNeighbors(domain);
    double score = 0.0;
    for(int i=0; i < neighbors->Size(); i++){
        double B= a->GetSetById( neighbors->At(i))->Size() ;
        if(B > 0){
            Context *currContext = hin->GetContext(domain,neighbors->At(i));
            IOSet *tmp = Intersect(currContext->GetSet(domain,obj),a->GetSetById( neighbors->At(i) ));
            int n = a->GetSetById( neighbors->At(i) )->Size();
            int alpha = currContext->GetSet(domain,obj)->Size()+1;
            int beta =currContext->GetNumSets(neighbors->At(i))-(alpha-1)+1;
            double expected =  BetaBinomial_Mean(n, alpha,beta);
            double std = BetaBinomial_Dev(n, alpha,beta);
            double ones = tmp->Size();
            double tfactor = 1.0;//pow(tired[domain][obj],1.5);//1.0;//pow(tired[domain][obj],1.5);
            double zscore = Z_Score(ones,expected,std);
            double z = tfactor*zscore-w;
            score += z;
            delete tmp;
        }
    }
    delete neighbors;
    return score;
}
