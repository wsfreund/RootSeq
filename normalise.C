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

    std::cout<<readingChain<<endl;

	RootSeq myRootSeq(readingChain, normalizedData);

	int entries	= static_cast<int>(readingChain->GetEntries());
    //Loop over all entries
    for(int entry = 0; entry < entries; ++entry){
        std::cout<<"Debug2\n";
        std::cout<<readingChain<<std::endl;
        readingChain->GetEntry(entry);
        std::cout<<"Debug3\n";
        myRootSeq.normalise();
    }

    normalizedData->Write();
    file->Close();

    delete file;
    delete readingChain;
    delete normalizedData;

    return 0;

}

