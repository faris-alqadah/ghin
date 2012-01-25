#include "../headers/random_sample.h"




vector<long double> * NClusterRandomSample::GetFreqWeights(Context *c, int s, int t){
    vector<long double> *weights = new vector<long double>(c->GetNumSets(t));
    long double sum = 0;
    for (int i=0; i < c->GetNumSets(t); i++){
        long double pwr=(long double)c->GetSet(t,i)->Size();///10.0;
       // cout<<"\nweights i "<<i<<" as "<<c->GetSet(t,i)->Size();
        (*weights)[i] = pow(2,pwr); // weigh by size of power set
        sum += (*weights)[i];
    }
    for(int i=0; i < weights->size(); i++) (*weights)[i] /= sum;
    return weights;
}

vector<long double> * NClusterRandomSample::GetFreqWeightsStar(RelationGraph *g, int s){
    IOSet *sObjs = g->GetLabels(s);
    vector<long double> *weights = new vector<long double>(sObjs->Size());
    vector<Context*> *ctxs = g->GetContexts(s);
    long double sum=0.0;
    for(int i=0; i < sObjs->Size(); i++){
        long double avgTlength=0;
        for(int j=0; j < ctxs->size(); j++){
            pair<int,int> dIds = (*ctxs)[j]->GetDomainIds();
			int t= dIds.first == s ? dIds.second: dIds.first;
			long double currTLength = (*ctxs)[j]->GetSet(s,i)->Size();
			if (currTLength == 0){
				avgTlength = 0;
				break;
			}else{
				avgTlength += avgTlength;
			}
        }
		avgTlength /= (long double) ctxs->size();
		(*weights)[i] = pow(2,avgTlength);
                sum += (*weights)[i];
		
    }
    delete sObjs;
    for(int i=0; i < weights->size(); i++) (*weights)[i] /= sum;
    return weights;
}

vector<long double> * NClusterRandomSample::GetFreqWeightsStar(RelationGraph *g, int s, NCluster *subSets){
    IOSet *sObjs = g->GetLabels(s);
    vector<long double> *weights = new vector<long double>(sObjs->Size());
    fill(weights->begin(),weights->end(),0.0);
    IOSet *tmp = sObjs;
    sObjs = Intersect(sObjs,subSets->GetSetById(s));
    delete tmp;
    vector<Context*> *ctxs = g->GetContexts(s);
    long double sum=0.0;
    for(int i=0; i < sObjs->Size(); i++){
        long double avgTlength=0;
        for(int j=0; j < ctxs->size(); j++){
            pair<int,int> dIds = (*ctxs)[j]->GetDomainIds();
			int t= dIds.first == s ? dIds.second: dIds.first;
                        IOSet *tt =  Intersect( (*ctxs)[j]->GetSet(s,sObjs->At(i)),subSets->GetSetById(t));

			long double currTLength = tt->Size();
                        //cout<<"\ncurr length "<<currTLength;
			if (currTLength == 0){
				avgTlength = 0;
				break;
			}else{
				avgTlength += currTLength;
			}
                        delete tt;
        }
       // cout<<"\navgT "<<avgTlength;
                avgTlength /= (long double) ctxs->size();
                if(avgTlength == 0)
                    (*weights)[sObjs->At(i)] = (long double)0.0;
                else
                    (*weights)[sObjs->At(i)] = (long double)pow(2.0,avgTlength);
               // cout<<"\nadding weight "<<(*weights)[sObjs->At(i)]<<" at loc: "<<sObjs->At(i);
                sum += (*weights)[sObjs->At(i)];

    }

    delete sObjs;
    if (sum == 0){
      // DstryVector(weights);
        return NULL;
    }
    for(int i=0; i < weights->size(); i++){
       
        (*weights)[i] /= sum;
         //cout<<"\nweights ("<<i<<"): "<<(*weights)[i];
    }
    return weights;
}
vector<long double> * NClusterRandomSample::GetAreaWeights(Context *c, int s, int t){
    vector< long double> *weights = new vector<long double>(c->GetNumSets(t));
    long double sum=0;
    for (int i=0; i < c->GetNumSets(t); i++){
        double pwr=(long double)c->GetSet(t,i)->Size();///10.0;
        (*weights)[i] = pwr*pow(2,pwr-1); // weigh by size of power set
        sum += (*weights)[i];
    }
    for(int i=0; i < weights->size(); i++) (*weights)[i] /= sum;

    return weights;
}

IOSet* NClusterRandomSample::SubspaceFreq(Context *c, int s,int t, vector<long double> &weights){
    //randomly draw object from t
    cout<<"\nweights size: "<<weights.size();
    int randT;
    do{
        randT =  WeightedUniformDraw(weights);
    }while(c->GetSet(t,randT)->Size() == 0);
   cout<<"\ntransaction selected: "<<randT;
   cout<<"\ntransact had weight "<<weights[randT];
    //uniformly select from power set of psi^t(randT)
    cout<<"\t size: "<<c->GetSet(t,randT)->Size();
    cout.flush();
    IOSet *ret = UniformSubsetDraw(c->GetSet(t,randT));
    ret->SetId(s);
    return ret;

}
IOSet* NClusterRandomSample::SubspaceArea(Context *c, int s, int t, vector<long double> &weights){
    int randT =  WeightedUniformDraw(weights);
    //cout<<"\ntransaction selected: "<<randT;
    //uniformly select from power set of psi^t(randT)
    IOSet *ret =  BinomialSubsetDraw(c->GetSet(t,randT));
    ret->SetId(s);
    return ret;
}



NCluster* NClusterRandomSample::SubspaceStarShapedFreqSample(RelationGraph *g, int s, NCluster *sample, IOSet *completedDomains ){
    vector<Context*> *ctxs = g->GetContexts(s);
    //assign weights to s-objects based on average frequence in all domains
    vector<long double> *sWeights = GetFreqWeightsStar(g,s, sample);
    if (sWeights == NULL)
        return NULL;
    //draw an object in s ~ sWeights
    int randS;
   // cout<<"\nsWeights size: "<<sWeights->size();
    randS = WeightedUniformDraw(*sWeights);
  //  cout<<"\nrandomly drew "<<randS<<" as S object...with weight: "<<(*sWeights)[randS]<<"\nGetting primes...\n";
   // cout.flush();
    //now do primes
    NCluster *ret = new NCluster;
    IOSet *ss = new IOSet;
        for(int i=0; i < ctxs->size(); i++){
            Context *currContext = (*ctxs)[i];
              pair<int,int> ctxIds = currContext->GetDomainIds();
              int t = ctxIds.first == s ? ctxIds.second : ctxIds.first;
              if(!completedDomains->Contains(t)) { //only perform operation in context not already sampled
               //   cout<<"\nprimeing and intersectiong in context "<<t<<"_"<<s;
                  IOSet *currT = currContext->GetSet(s,randS);
                //  cout<<"\nbefore intersect: "; currT->Output();
                  currT = Intersect(currT,sample->GetSetById(t));
         
                  //cout<<endl; cout<<"\nafter the intersectt...the curr T: ";currT->Output();
                  IOSet *tt= UniformSubsetDraw(currT);
                  tt->SetId(t);
                  ret->AddSet(tt);
                  //now prime into s and take intersection
                  IOSet *sPrime = Prime(ret,g,t,s,1);
                  if(sPrime == NULL){
                      delete ret;
                      delete ss;
                      delete currT;
                      delete sWeights;
                      return NULL;
                  }
                  IOSet *tmp = sPrime;
                  //intersect to get subset
                 // cout<<"\nsprime: "; sPrime->Output();
                 // cout.flush();
                  sPrime = Intersect(sPrime,sample->GetSetById(s));
                   delete tmp;
                  //now intersection with other s Sets
                   if(ss->Size() > 0){
                       tmp =ss;
                       ss=Intersect(ss,sPrime);
                       delete tmp;
                   }else{
                       ss->DeepCopy(sPrime);
                   }
                   delete sPrime;
                   delete currT;
              }
         }
    ss->SetId(s);
    ret->AddSet(ss);
    delete sWeights;
    return ret;
    }


NCluster * NClusterRandomSample::SubspaceFreqNetwork(RelationGraph *g, int s,NCluster *subspace){
    //first step is to generate n-cluster in initial star shaped hin
    //as defined by s
    IOSet *completedDomains = new IOSet; // keep tracking of the domains that have already been completed
    //construct the sample subspace
    NCluster *sampleSubspace = new NCluster(*subspace);
     NCluster *init1 = SubspaceStarShapedFreqSample(g,s,sampleSubspace,completedDomains);
   //  cout<<"\ngot init1...\n";
     if (init1 == NULL){
         delete completedDomains;
         delete sampleSubspace;
         return NULL;
     }
     NCluster *ret = new NCluster;
     AdjustSampleSubspace(sampleSubspace,init1,ret,completedDomains);
     delete init1;
     //cout<<"\nsample subspace: \n";
     //sampleSubspace->Output();
    //do a BFS using SubspaceStarShapedFreqSample
    //insert all neighboring articulation nodes of s
    IOSet *artDomains = g->GetArtDomains();
    queue<int> q;
//     cout<<"\nthe init1\n"; init->Output();
//    cout.flush();
    IOSet *sNeighbors = g->GetNeighbors(s);
    for(int i=0; i < sNeighbors->Size(); i++){
        if(artDomains->Contains(sNeighbors->At(i)))
            q.push(sNeighbors->At(i));
    }
  // cout<<"\nq size: "<<q.size();
    delete sNeighbors;
    while (!q.empty()){
        int s1 = q.front();
        q.pop();
        NCluster *init1 = SubspaceStarShapedFreqSample(g,s1,sampleSubspace,completedDomains);
        if(init1 == NULL){
           // cout<<"\ninit 1 was null (q)";
            delete ret;
            delete completedDomains;
            delete sampleSubspace;
            return NULL;
        }
     //   cout<<"\ngot init1: \n"; init1->Output();
        AdjustSampleSubspace(sampleSubspace,init1,ret,completedDomains);
        delete init1;
        sNeighbors = g->GetNeighbors(s1);
        for(int i=0; i < sNeighbors->Size(); i++){
            int id = sNeighbors->At(i);
            if(artDomains->Contains(sNeighbors->At(i)) && !completedDomains->Contains(sNeighbors->At(i)))
                q.push(sNeighbors->At(i));
        }
        delete sNeighbors;
    }
    delete completedDomains;
    delete sampleSubspace;
    return ret;
}

void NClusterRandomSample::AdjustSampleSubspace(NCluster *sampleSubspace, NCluster *sample, NCluster *ret, IOSet *completedDomains){
    for(int i=0; i < sample->GetN(); i++){
        int currId = sample->GetSet(i)->Id();
        IOSet *tt = new IOSet(sample->GetSetById(currId));
        ret->AddSet(tt);
        completedDomains->Add(currId);
        IOSet *currSample =sampleSubspace->GetSetById(currId);
        currSample->DeepCopy(sample->GetSetById(currId));
    }
}
