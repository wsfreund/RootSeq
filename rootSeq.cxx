#include"rootSeq.h"

RootSeq::RootSeq(TChain *outsideReadingChain, TTree *outsidefillingTree) 
    : debugFile(NULL) {

    readingChain = outsideReadingChain;
    fillingTree = outsidefillingTree;

	ringer_rings	=	new std::vector<float>;
	ringer_lvl2_eta	=	new std::vector<float>;
	ringer_lvl2_phi	=	new std::vector<float>;
	ringer_lvl2_et  =	new std::vector<float>;



	t2ca_lvl2_eta	=	new std::vector<float>;
	t2ca_lvl2_phi   =	new std::vector<float>;
	t2ca_rcore		=	new std::vector<float>;
    t2ca_eratio		=	new std::vector<float>;
    t2ca_emes1		=	new std::vector<float>;
    t2ca_eme		=	new std::vector<float>;
    t2ca_ehades0	=	new std::vector<float>;
    t2cahade        =   new std::vector<float>;



    if (DEBUG)  {
        debugFile = new ofstream("/tmp/ws-debug.txt", ios::out | ios::trunc);
        debugFile->precision(6);
        debugFile->setf(ios::boolalpha);
    }

//NeuralRinger Variables
    readingChain->SetBranchStatus("Ringer_Rings", 		true);
	readingChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
	readingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	readingChain->SetBranchStatus("Ringer_LVL2_Et",		true);
	readingChain->SetBranchStatus("Ringer_NClusters",	true);

//T2Calo Variables
	readingChain->SetBranchStatus("T2CaEta", 		true);
	readingChain->SetBranchStatus("T2CaPhi",		true);
	readingChain->SetBranchStatus("T2CaRcore", 	    true);
	readingChain->SetBranchStatus("T2CaEratio",	    true);
	readingChain->SetBranchStatus("T2CaEmES1", 	    true);
	readingChain->SetBranchStatus("T2CaEmE", 		true);
	readingChain->SetBranchStatus("T2CaHadES0", 	true);
	readingChain->SetBranchStatus("T2CaNclus",   	true);
	readingChain->SetBranchStatus("T2CaHadE",   	true);



//NeuralRinger Variables
    readingChain->SetBranchAddress("Ringer_Rings",      &ringer_rings);
    readingChain->SetBranchAddress("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
    readingChain->SetBranchAddress("Ringer_LVL2_Phi",   &ringer_lvl2_phi);       
    readingChain->SetBranchAddress("Ringer_LVL2_Et",	&ringer_lvl2_et);
    readingChain->SetBranchAddress("Ringer_NClusters",	&ringer_nclusters);

//T2Calo Variables
	readingChain->SetBranchAddress("T2CaEta", 		&t2ca_lvl2_eta);
	readingChain->SetBranchAddress("T2CaPhi",		&t2ca_lvl2_phi);
	readingChain->SetBranchAddress("T2CaRcore", 	&t2ca_rcore);
	readingChain->SetBranchAddress("T2CaEratio",	&t2ca_eratio);
	readingChain->SetBranchAddress("T2CaEmES1", 	&t2ca_emes1);
	readingChain->SetBranchAddress("T2CaEmE", 		&t2ca_eme);
	readingChain->SetBranchAddress("T2CaHadES0", 	&t2ca_ehades0);
	readingChain->SetBranchAddress("T2CaNclus", 	&t2canclus);
	readingChain->SetBranchAddress("T2CaHadE", 	    &t2cahade);

//NeuralRinger
    fillingTree->Branch("Ringer_Rings",      &ringer_rings);
    fillingTree->Branch("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
    fillingTree->Branch("Ringer_LVL2_Phi",   &ringer_lvl2_phi);       
    fillingTree->Branch("Ringer_LVL2_Et",	 &ringer_lvl2_et);
    fillingTree->Branch("Ringer_NClusters",	 &ringer_nclusters, "ringer_nclusters/i");

//T2Calo
	fillingTree->Branch("T2CaEta", 		&t2ca_lvl2_eta);
	fillingTree->Branch("T2CaPhi",		&t2ca_lvl2_phi);
	fillingTree->Branch("T2CaRcore", 	&t2ca_rcore);
	fillingTree->Branch("T2CaEratio",	&t2ca_eratio);
	fillingTree->Branch("T2CaEmES1", 	&t2ca_emes1);
	fillingTree->Branch("T2CaEmE", 		&t2ca_eme);
	fillingTree->Branch("T2CaHadES0", 	&t2ca_ehades0);
	fillingTree->Branch("T2CaNclus", 	&t2canclus, "t2canclus/i");
	fillingTree->Branch("T2CaHadE", 	&t2cahade);

}

inline unsigned RootSeq::getLayerInit(const unsigned numEvent, const unsigned curLayer){
    unsigned layerInitialRing=0;

    for(unsigned i = 0; i < curLayer; ++i) layerInitialRing += ringsDist[i];
    return numEvent*100+layerInitialRing;

}

inline float RootSeq::calcNorm0(const unsigned layerInit, const unsigned curLayer){

    float vNorm = 0.;
    if (DEBUG) *debugFile<<"Calculating Norm0, Current Energy rings for this Layer:\n";
    for(unsigned curLyrRing=0; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
        if (DEBUG) *debugFile<<setw(12)<<internal<<ringer_rings->at(layerInit+curLyrRing)<<"    ";
        if (DEBUG && ((curLyrRing+1)%8)==0 && (curLyrRing!=ringsDist[curLayer]-1)) *debugFile<<std::endl;
        vNorm+=fabs(ringer_rings->at(layerInit+curLyrRing));
    }
    if (DEBUG) *debugFile<<"\n Its Total Energy is : "<<vNorm<<std::endl;
    return vNorm;

}


inline float RootSeq::max_abs(const unsigned layerInit, const unsigned curLayer){

    float maxValue = 0.;
    for(unsigned curLyrRing=0; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
        float curRingAbs = fabs(ringer_rings->at(layerInit+curLyrRing));
        if (maxValue<curRingAbs) 
            maxValue=curRingAbs;
    }
    return maxValue;

}

inline void RootSeq::fillNormValues(float norm[], const unsigned layerInit, const unsigned curLayer){

    if (DEBUG) *debugFile<<"--------------------------------------------"<<std::endl;
    if (DEBUG) *debugFile<<"Inside FillNormValues.\n";
    if (norm[0]<stopEnergy){

        float layerMax = max_abs(layerInit, curLayer);

        if (norm[0]<layerMax){
            if (DEBUG) *debugFile<<"Norm[0] = "<<norm[0]<<" < "<<" stopEnergy = "<<stopEnergy<<" : MaxValue for this Layer "<<layerMax<<" and now will be the norm[0]value"<<std::endl;
            norm[0]=layerMax;
        }
        else 
            if (DEBUG) *debugFile<<"Norm[0] = "<< norm[0] << " < " <<" stopEnergy = "<<stopEnergy<<" MaxValue for this Layer "<<layerMax<<" that is lesser than norm[0]"<<std::endl;
        
        if (DEBUG) *debugFile<<"Applying energyThreshold test\n";

        if (norm[0]<energyThreshold) {
            if (DEBUG) *debugFile<<"norm[0] < energyThreshold("<<energyThreshold<<") and now norm[0] = energyThreshold\n";
            norm[0]=energyThreshold;
        }
        else 
            if (DEBUG) *debugFile<<"norm[0] > energyThreshold("<<energyThreshold<<") and is still the same\n";

        //Setting all layer rings normalized by norm0:
        for(unsigned curLyrRing=1; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
            norm[curLyrRing]=norm[0];
            if (DEBUG) *debugFile<<"Norm["<<curLyrRing<<"] = "<<norm[curLyrRing]<<std::endl;
        }
    }else{
        if (DEBUG) *debugFile<<"Norm[0] = "<<norm[0]<<" > "<<" stopEnergy = "<<stopEnergy<<std::endl;
        bool fixed = false;
        for(unsigned curLyrRing=1; curLyrRing<ringsDist[curLayer]; ++curLyrRing){
            if (!(norm[ curLyrRing - 1] - fabs(ringer_rings->at(layerInit + curLyrRing-1))<stopEnergy) && !fixed){
                norm[curLyrRing] = norm[ curLyrRing - 1] - fabs(ringer_rings->at(layerInit + curLyrRing-1));
                if (DEBUG) *debugFile<<"Fixed = "<<fixed<<" and ("<<setw(12)<<(norm[ curLyrRing - 1] - fabs(ringer_rings->at(layerInit + curLyrRing-1)))<<" < "<<stopEnergy<<") = "<<!(norm[ curLyrRing - 1] - fabs(ringer_rings->at(layerInit + curLyrRing-1))<stopEnergy)<<" norm["<<setw(2)<<setfill('0')<<curLyrRing<<"] = "<<setw(12)<<setfill(' ')<<internal<<norm[curLyrRing - 1]<<" - "<<setw(12)<<fabs(ringer_rings->at(layerInit + curLyrRing-1))<<" = "<<norm[curLyrRing]<<std::endl;
            }
            else {
                norm[curLyrRing] = norm[ 0 ];
                if (DEBUG) *debugFile<<"Fixed = "<<fixed<<" and ("<<norm[curLyrRing-1]<<" < "<<stopEnergy<<") = "<<(norm[curLyrRing-1]<stopEnergy)<<" norm["<<setw(2)<<setfill('0')<<curLyrRing<<setfill(' ')<<"] = "<<norm[curLyrRing]<<std::endl;
                fixed = true;
            }
        }

    }
    if (DEBUG) *debugFile<<"Finished fillNormValues\n";
    if (DEBUG) *debugFile<<"--------------------------------------------"<<std::endl;
}

inline void RootSeq::applySequentialNorm(const float norm[], const unsigned layerInit, const unsigned curLayer){

    if (DEBUG) *debugFile<<"--------------------------------------------"<<std::endl;
    if (DEBUG) *debugFile<<"Inside Sequential Norm\n";
    for(unsigned curLyrRing=0; curLyrRing<ringsDist[curLayer]; ++curLyrRing){

        
        if (norm[curLyrRing]!=energyThreshold){
            if (DEBUG) *debugFile << "Ring number "<<setw(2)<<curLyrRing+layerInit+1<< " new value = (old value)" <<setw(12)<<internal<< ringer_rings->at(layerInit + curLyrRing) << " / (norm[" <<setw(2)<<setfill('0')<< curLyrRing << setfill(' ')<< "]) "<<setw(12) <<norm[curLyrRing];
            ringer_rings->at(layerInit + curLyrRing)/=norm[curLyrRing];
            if (DEBUG) *debugFile<<" = (new value) "<<ringer_rings->at(layerInit + curLyrRing)<<std::endl;
        }
        else if (DEBUG) *debugFile << "Ring number "<<setw(2)<<curLyrRing+layerInit+1<< " new value = (old value)" <<setw(12)<<internal<< ringer_rings->at(layerInit + curLyrRing)<<"(norm=energyThreshold)"<<std::endl;


    }
    if (DEBUG) *debugFile<<"--------------------------------------------"<<std::endl;

}


RootSeq::CODE RootSeq::normalise(){

    if (DEBUG) *debugFile<<"||||||| Debug init |||||||\n";
    //Total rings size
    unsigned totalRings = 0;
    for(unsigned i =0; i<sizeof(ringsDist)/sizeof(unsigned); ++i) totalRings+=ringsDist[i];
    if (DEBUG) *debugFile<<"Total rings for each ROI is "<<totalRings<<std::endl;
	int entries	= static_cast<int>(readingChain->GetEntries());

    //Loop over all entries
    for(int entry = 0; entry < entries; ++entry){
        if (DEBUG) *debugFile<<"-----------"<<std::endl;
        if (DEBUG) *debugFile<<"Initializing Entry Number "<< entry+1<<std::endl;
        readingChain->GetEntry(entry);

        if (DEBUG) *debugFile<<"Ringer_rings values are : "<<std::endl;

        if (DEBUG) for(unsigned f=0; (DEBUG && f<ringer_rings->size() ); ++f)
            *debugFile<<f<<" "<<ringer_rings->at(f)<<std::endl;

        //Case ringerRings have multiple ROIs will loop on this for:
        for(unsigned numEvent=0; numEvent < (ringer_rings->size()/totalRings); ++numEvent){
            //Looping over all Layers
            if (DEBUG) *debugFile<<"----------------------"<<std::endl;
            if (DEBUG) *debugFile<<"Initializing Event Number "<< numEvent+1<<std::endl;
            for(unsigned curLayer=0;  curLayer<sizeof(ringsDist)/sizeof(unsigned); ++curLayer){
                if (DEBUG) *debugFile<<"---------------------------------"<<std::endl;
                if (DEBUG) *debugFile<<"Initializing LAYER Number "<<curLayer+1<<std::endl;

                float norm[ringsDist[curLayer]];//norm have the same size of its layer

                unsigned layerInitialRing = getLayerInit(numEvent, curLayer);

                if (DEBUG) *debugFile<<"Entry Number "<<entry+1<<" from "<<entries<<" : numEvent "<<numEvent+1<<" : from "<<(ringer_rings->size()/totalRings)<<" events : Layer number "<<curLayer+1<<" from "<<sizeof(ringsDist)/sizeof(unsigned)<<" layers : It's size is "<<ringsDist[curLayer]<<" : and it begins on Ring "<<layerInitialRing+1<<std::endl;

                // Calculate initial norm value
                norm[0] = calcNorm0(layerInitialRing, curLayer);
                //fillingNormValues
                fillNormValues(norm, layerInitialRing, curLayer);
                //ApplySequential Norm
                applySequentialNorm(norm, layerInitialRing, curLayer);

                if (DEBUG) *debugFile<<"Ended LAYER Number "<<curLayer+1<<std::endl;
                if (DEBUG) *debugFile<<"---------------------------------"<<std::endl;
            }//Close Layer loop
            if (DEBUG) *debugFile<<"Ended Event Number "<< numEvent+1<<std::endl;
            if (DEBUG) *debugFile<<"----------------------"<<std::endl;
        }//Close Events Loop

        if (DEBUG) *debugFile<<"Ended Entry Number "<< entry+1<<std::endl;
        if (DEBUG) *debugFile<<"-----------"<<std::endl;
        if (DEBUG) *debugFile<<"Filling Tree with ringer_rings values of : "<<std::endl;

        if (DEBUG) for(unsigned f=0; (DEBUG && f<ringer_rings->size() ); ++f)
            *debugFile<<f<<" "<<ringer_rings->at(f)<<std::endl;

        fillingTree->Fill();
    }//Close Entry Loop

    return RootSeq::OK;

}

RootSeq::~RootSeq(){

    if (DEBUG) {
        debugFile->close();
        delete debugFile;
    }

	delete ringer_rings;
	delete ringer_lvl2_eta;	
	delete ringer_lvl2_phi;	
	delete ringer_lvl2_et;  

	delete t2ca_lvl2_eta;	
	delete t2ca_lvl2_phi;   
	delete t2ca_rcore;		
    delete t2ca_eratio;		
    delete t2ca_emes1;		
    delete t2ca_eme;		
    delete t2ca_ehades0;
    delete t2cahade;
	
}
