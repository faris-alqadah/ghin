#include "../headers/Count_Rewards.h"

double Simple_Weighted_Score(NCluster *a, int obj, int domain, double w, RelationGraph *hin){

    IOSet *neighbors = hin->GetNeighbors(domain);
    double score = 0.0;
    for(int i=0; i < neighbors->Size(); i++){
        double B= a->GetSetById( neighbors->At(i))->Size() ;
        if(B > 0){
            Context *currContext = hin->GetContext(domain,neighbors->At(i));
            IOSet *tmp = Intersect(currContext->GetSet(domain,obj),a->GetSetById( neighbors->At(i) ));
            IOSet *tmp1 = Difference(a->GetSetById( neighbors->At(i) ),currContext->GetSet(domain,obj));
            double zeros =  tmp1->Size();
            double ones = tmp->Size();
            score += (ones - w*zeros) / B;
            delete tmp;
            delete tmp1;
        }
    }
    delete neighbors;
    return score;
}
