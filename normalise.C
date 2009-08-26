#include"rootSeq.h"
#include<TChain.h>
#include<TFile.h>
#include<iostream>

int normalise(const char *inPut, const char *outPut){

	TFile 		*file;
	TChain		*readingChain;
	TChain		*normalizedData;

	file		= new TFile(outPut,"recreate");

	normalizedData = new TChain("CollectionTree", "Tree with sequential normalized rings and T2CaloData for HypoCompTool");

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData);

    myRootSeq.normalise();

    std::cout<<"Passou normalise()\n";

    normalizedData->Write();
//    file->Close();

//    delete file;
    delete readingChain;
    delete normalizedData;

    return 0;

}

