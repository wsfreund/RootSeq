#include"rootSeq.h"
#include<TChain.h>
#include<TTree.h>
#include<TFile.h>
#include<iostream>

int normalise(const char *inPut, const char *outPut){


	TChain		*readingChain;
	TTree		*normalizedData;

	normalizedData = new TTree("CollectionTree", "Tree with sequential normalized rings and T2CaloData for HypoCompTool");

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	RootSeq myRootSeq(readingChain, normalizedData);

    myRootSeq.normalise();

    std::cout<<"Passou normalise()\n";

	TFile 		*file;
	file		= new TFile(outPut,"recreate");
    normalizedData->Write();
//    file->Close();

//    delete file;
    delete readingChain;
    delete normalizedData;

    return 0;

}

