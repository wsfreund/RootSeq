#ifndef ROOTNORM1

#include<TChain.h>
#include<TTree.h>
#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>
#include<iomanip>
#include <algorithm>


#define ROOTNORM1


class RootNorm1 {

	enum CODE {ERROR=0, OK};

    static const int       DEBUG = 0;

//	std::vector<double>	*ringer_rings;
	std::vector<float>	*ringer_rings_f;
	std::vector<float>	*ringer_lvl2_eta;
	std::vector<float>	*ringer_lvl2_phi;
	std::vector<float>	*ringer_lvl2_et;
//    std::vector<float>  *ringer_lvl1_id;
//    std::vector<float>  *ringer_roi_id;


	std::vector<float>	*t2ca_lvl2_eta;
	std::vector<float>	*t2ca_lvl2_phi;
	std::vector<float>	*t2ca_rcore;
	std::vector<float>	*t2ca_eratio;
	std::vector<float>	*t2ca_emes1;
	std::vector<float>	*t2ca_eme;
    std::vector<float>  *t2ca_ehades0;

	std::vector<float>	*t2cahade;

	UInt_t          	*ringer_nclusters;
    UInt_t          	*t2canclus;

    TTree   *fillingTree;
    TChain  *readingChain;

    ofstream *debugFile;

    public:

    RootNorm1(TChain *outsideReadingChain, TTree *outsidefillingTree);
    ~RootNorm1();

    CODE normalise();

};

#endif
