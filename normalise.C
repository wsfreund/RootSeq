#include"rootSeq.h"
#include<TChain.h>
#include<TFile.h>

int normalise(const char *inPut, const char *outPut){

	TFile 		*file;
	TChain		*readingChain;
	TChain		*normalizedData;

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData);

    myRootSeq.normalise();

    normalizedData->Write();
    file->Close();

    delete file;
    delete redingChain;
    delete normalizedData;

}

int normalise(const char *inPut, const char *outPut, unsigned usrRingsDist[]){

	TFile 		*file;
	TChain		*readingChain;
	TChain		*normalizedData;

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData, usrRingsDist);

    myRootSeq.normalise();

    normalizedData->Write();
    file->Close();

    delete file;
    delete redingChain;
    delete normalizedData;

}

int normalise(const char *inPut, const char *outPut, unsigned usrRingsDist[], float usrStopEnergy){

	TFile 		*file;
	TChain		*readingChain;
	TChain		*normalizedData;

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData, usrRingsDist, usrStopEnergy);

    myRootSeq.normalise();

    normalizedData->Write();
    file->Close();

    delete file;
    delete redingChain;
    delete normalizedData;

}

int normalise(const char *inPut, const char *outPut, unsigned usrRingsDist[], float usrStopEnergy, float usrEnergyThreshold){

	TFile 		*file;
	TChain		*readingChain;
	TChain		*normalizedData;

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData, usrRingsDist, usrStopEnergy, usrEnergyThreshold);

    myRootSeq.normalise();

    normalizedData->Write();
    file->Close();

    delete file;
    delete redingChain;
    delete normalizedData;

}
