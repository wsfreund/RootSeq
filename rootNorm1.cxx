#include"rootNorm1.h"

RootNorm1::RootNorm1(TChain *outsideReadingChain, TTree *outsidefillingTree) 
    : debugFile(NULL) {

    readingChain = outsideReadingChain;
    fillingTree = outsidefillingTree;

    ringer_rings_f  =   new std::vector<float>;
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
        debugFile = new ofstream("/tmp/ws-debug-norm1.txt", ios::out | ios::trunc);
        debugFile->precision(6);
        debugFile->setf(ios::boolalpha);
    }

//NeuralRinger Variables
    readingChain->SetBranchStatus("Ringer_Rings", 		true);
	readingChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
	readingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	readingChain->SetBranchStatus("Ringer_LVL2_Et",		true);
	readingChain->SetBranchStatus("Ringer_NClusters",	true);
//	readingChain->SetBranchStatus("Ringer_LVL1_Id",		true);
//	readingChain->SetBranchStatus("Ringer_Roi_Id",		true);

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
    readingChain->SetBranchAddress("Ringer_Rings",      &ringer_rings_f);
    readingChain->SetBranchAddress("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
    readingChain->SetBranchAddress("Ringer_LVL2_Phi",   &ringer_lvl2_phi);       
    readingChain->SetBranchAddress("Ringer_LVL2_Et",	&ringer_lvl2_et);
    readingChain->SetBranchAddress("Ringer_NClusters",	&ringer_nclusters);
//	readingChain->SetBranchAddress("Ringer_LVL1_Id",	&ringer_lvl1_id);
//	readingChain->SetBranchAddress("Ringer_Roi_Id",		&ringer_roi_id);

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
    fillingTree->Branch("Ringer_Rings",      &ringer_rings_f);
    fillingTree->Branch("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
    fillingTree->Branch("Ringer_LVL2_Phi",   &ringer_lvl2_phi);       
    fillingTree->Branch("Ringer_LVL2_Et",	 &ringer_lvl2_et);
//    fillingTree->Branch("Ringer_LVL1_Id",    &ringer_lvl1_id);
//    fillingTree->Branch("Ringer_Roi_Id",     &ringer_roi_id);
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


RootNorm1::CODE RootNorm1::normalise(){

    //Loop over all entries
	int entries	= static_cast<int>(readingChain->GetEntries());
    for(int entry = 0; entry < entries; ++entry){
        
        readingChain->GetEntry(entry);


        for(unsigned numEvent=0; numEvent < ringer_lvl2_eta->size(); ++numEvent){

            float norm1=0;
            for(unsigned numRing=numEvent*ringer_rings_f->size()/ringer_lvl2_eta->size(); numRing < ringer_rings_f->size()*(numEvent+1)/ringer_lvl2_eta->size(); ++numRing)
                norm1+=ringer_rings_f->at(numEvent);
            norm1=1/norm1;
            for(unsigned numRing=numEvent*ringer_rings_f->size()/ringer_lvl2_eta->size(); numRing < ringer_rings_f->size()*(numEvent+1)/ringer_lvl2_eta->size(); ++numRing)
                ringer_rings_f->at(numEvent)*=norm1;

        }//Close Events Loop

        fillingTree->Fill(); 

    }//Close Entry Loop



    return RootNorm1::OK;

}

RootNorm1::~RootNorm1(){

    if (DEBUG) {
        debugFile->close();
        delete debugFile;
    }

    delete ringer_rings_f;
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
