#include"rootSeq.h"
#include"rootNorm1.h"
#include<TChain.h>
#include<TTree.h>
#include<TFile.h>
#include<iostream>

int normalise(const char *inPut, const char *outPut, const char *normMethod = "sequential"){

    if (!strcmp(normMethod,"sequential")){
 
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

        normalizedData->Write();
    //    normalizedData->GetCurrentFile()->Write();
        file->Close();

        delete file;
        delete readingChain;
        delete normalizedData;

        return 0;

    } else if (!strcmp(normMethod,"norm1")){

	    TFile 		*file;
	    TChain		*readingChain;
	    TTree		*normalizedData;

	    normalizedData = new TTree("CollectionTree", "Tree with norm1 normalized rings and T2CaloData for HypoCompTool");

	    readingChain = new TChain("CollectionTree");
	    readingChain->Add(inPut);
	    readingChain->SetBranchStatus("*",	false);

	    file        = new TFile(outPut,"recreate");

	    RootNorm1    myRootNorm1(readingChain, normalizedData);

        myRootNorm1.normalise();

        normalizedData->Write();
    //    normalizedData->GetCurrentFile()->Write();
        file->Close();

        delete file;
        delete readingChain;
        delete normalizedData;

        return 0;

    }
    else return 1;

}

