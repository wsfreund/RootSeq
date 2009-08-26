#include"rootSeq.h"
#include<TChain.h>
#include<TTree.h>
#include<TFile.h>
#include<iostream>

int normalise(const char *inPut, const char *outPut){

	TFile 		*file;
	TChain		*readingChain;
	TTree		*normalizedData;

	normalizedData = new TTree("CollectionTree", "Tree with sequential normalized rings and T2CaloData for HypoCompTool");

	readingChain = new TChain("CollectionTree");
	readingChain->Add(inPut);
	readingChain->SetBranchStatus("*",	false);

	file        = new TFile(outPut,"recreate");

	RootSeq     myRootSeq(readingChain, normalizedData);

    myRootSeq.normalise();

    std::cout<<"Passou normalise()\n";


    normalizedData->GetCurrentFile()->Write();
    normalizedData->GetCurrentFile()->Close();

//    delete file;
    delete myRootSeq;
    delete readingChain;
    delete normalizedData;

    return 0;

}

