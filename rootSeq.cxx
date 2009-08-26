#include"rootSeq.h"

RootSeq::RootSeq(TChain *outsideReadingChain, TTree *outsidefillingTree){

    readingChain = outsideReadingChain;
    fillingTree = outsidefillingTree;

//NeuralRinger Variables
    readingChain->SetBranchStatus("Ringer_Rings", 		true);
//	readingChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
//	readingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
//	readingChain->SetBranchStatus("Ringer_LVL2_Et",		true);

//T2Calo Variables
//	readingChain->SetBranchStatus("T2CaEta", 		true);
//	readingChain->SetBranchStatus("T2CaPhi",		true);
//	readingChain->SetBranchStatus("T2CaRcore", 	    true);
//	readingChain->SetBranchStatus("T2CaEratio",	    true);
//	readingChain->SetBranchStatus("T2CaEmES1", 	    true);
//	readingChain->SetBranchStatus("T2CaEmE", 		true);
//	readingChain->SetBranchStatus("T2CaHadES0", 	true);

//NeuralRinger Variables
    readingChain->SetBranchAddress("Ringer_Rings",      &ringer_rings);
//    readingChain->SetBranchAddress("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
//    readingChain->SetBranchAddress("Ringer_LVL2_Phi",   &ringer_lvl2_phi);       
//   readingChain->SetBranchAddress("Ringer_LVL2_Et",	&ringer_lvl2_et);

//T2Calo Variables
//	readingChain->SetBranchAddress("T2CaEta", 		&t2ca_lvl2_eta);
//	readingChain->SetBranchAddress("T2CaPhi",		&t2ca_lvl2_phi);
//	readingChain->SetBranchAddress("T2CaRcore", 	&t2ca_rcore);
//	readingChain->SetBranchAddress("T2CaEratio",	&t2ca_eratio);
//	readingChain->SetBranchAddress("T2CaEmES1", 	&t2ca_emes1);
//	readingChain->SetBranchAddress("T2CaEmE", 		&t2ca_eme);
//	readingChain->SetBranchAddress("T2CaHadES0", 	&t2ca_ehades0);

//NeuralRinger
    fillingTree->Branch("Ringer_Rings",      &ringer_rings);
//    fillingTree->Branch("Ringer_LVL2_Eta",   &ringer_lvl2_eta2);       
//    fillingTree->Branch("Ringer_LVL2_Phi",   &ringer_lvl2_phi2);       
//   fillingTree->Branch("Ringer_LVL2_Et",	 &ringer_lvl2_et2);

//T2Calo
//	fillingTree->Branch("T2CaEta", 		&t2ca_lvl2_eta2);
//	fillingTree->Branch("T2CaPhi",		&t2ca_lvl2_phi2);
//	fillingTree->Branch("T2CaRcore", 	&t2ca_rcore2);
//	fillingTree->Branch("T2CaEratio",	&t2ca_eratio2);
//	fillingTree->Branch("T2CaEmES1", 	&t2ca_emes12);
//	fillingTree->Branch("T2CaEmE", 		&t2ca_eme2);
//	fillingTree->Branch("T2CaHadES0", 	&t2ca_ehades02);

}

void RootSeq::copyVectors(){

    ringer_rings2->insert(ringer_rings2->begin(), ringer_rings->begin(), ringer_rings->end());

}

void RootSeq::clearVectors(){

    ringer_rings2->clear();

}

inline unsigned RootSeq::getLayerInit(const unsigned numEvent, const unsigned curLayer){
    unsigned layerInitialRing=0;

    for(unsigned i = 0; i < curLayer; ++i) layerInitialRing += ringsDist[i];
    return numEvent*100+layerInitialRing;

}

inline float RootSeq::calcNorm0(const unsigned layerInit, const unsigned curLayer){

    float vNorm = 0.;

    for(unsigned curLyrRing=0; curLyrRing<ringsDist[curLayer]; ++curLyrRing)
        vNorm+=std::fabs(ringer_rings->at(layerInit+curLyrRing));
    return vNorm;

}


inline float RootSeq::max_abs(const unsigned layerInit, const unsigned curLayer){

    float maxValue = 0.;
    for(unsigned curLyrRing=0; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
        float curRingAbs = std::fabs(ringer_rings->at(layerInit+curLyrRing));
        if (maxValue<curRingAbs) 
            maxValue=curRingAbs;
    }
    return maxValue;

}

inline void RootSeq::fillNormValues(float norm[], const unsigned layerInit, const unsigned curLayer){

    if (norm[0]<stopEnergy){

        float layerMax = max_abs(layerInit, curLayer);
        if (norm[0]<layerMax) norm[0]=layerMax;
        
        if (norm[0]<energyThreshold) norm[0]=energyThreshold;

        //Setting all layer rings normalized by norm0:
        for(unsigned curLyrRing=1; curLyrRing<ringsDist[curLayer]; ++curLyrRing) norm[curLyrRing]=norm[0];

    }else{
        bool fixed = false;
        for(unsigned curLyrRing=1; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
            if (!(norm[curLyrRing-1]<stopEnergy) || !fixed)
                norm[curLyrRing] = norm[layerInit + curLyrRing - 1] - std::fabs(ringer_rings->at(layerInit + curLyrRing-1));
            else {
                norm[curLyrRing] = norm[layerInit + curLyrRing - 1];
                fixed = true;
            }
        }

    }

}

inline void RootSeq::applySequentialNorm(const float norm[], const unsigned layerInit, const unsigned curLayer){

    for(unsigned curLyrRing=1; curLyrRing<ringsDist[curLayer]; ++curLyrRing) 
        ringer_rings->at(layerInit + curLyrRing)/=norm[curLyrRing];

}


RootSeq::CODE RootSeq::normalise(){

    //Total rings size
    std::cout<<"Debug\n";
    unsigned totalRings = 0;
    for(unsigned i =0; i<sizeof(ringsDist)/sizeof(unsigned); ++i) totalRings+=ringsDist[i];

    std::cout<<"Debug1\n";
	int entries	= static_cast<int>(readingChain->GetEntries());

    //Loop over all entries
    for(int entry = 0; entry < entries; ++entry){
        std::cout<<"Debug2\n";
        readingChain->GetEntry(entry);
        std::cout<<"Debug3\n";

        //Case ringerRings have multiple ROIs will loop on this for:
        for(unsigned numEvent=0; numEvent < (ringer_rings->size()/totalRings); ++numEvent){
            std::cout<<"Debug4\n";
            //Looping over all Layers
            for(unsigned curLayer=0;  curLayer<sizeof(ringsDist)/sizeof(unsigned); ++curLayer){
                std::cout<<"Debug5\n";
                float norm[ringsDist[curLayer]];//norm have the same size of its layer

                unsigned layerInitialRing = getLayerInit(numEvent, curLayer);

                // Calculate initial norm value
                norm[0] = calcNorm0(layerInitialRing, curLayer);
                std::cout<<"Debug6\n";
                //fillingNormValues
                fillNormValues(norm, layerInitialRing, curLayer);
                std::cout<<"Debug7\n";
                //ApplySequential Norm
                applySequentialNorm(norm, layerInitialRing, curLayer);

            }//Close Layer loop

        }//Close Events Loop

    }//Close Entry Loop

    return RootSeq::OK;

}

