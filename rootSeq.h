#ifndef ROOTSEQ

#include<TChain.h>
#include<TTree.h>
#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>
#include<iomanip>
#include <algorithm>


#define ROOTSEQ


class RootSeq {

	enum CODE {ERROR=0, OK};

    static const unsigned  ringsDist[];
    static const double    stopEnergy = 100.;
    static const double    energyThreshold = 0.001;
    static const           DEBUG = 0;

	std::vector<double>	*ringer_rings;
	std::vector<float>	*ringer_rings_f;
	std::vector<float>	*ringer_lvl2_eta;
	std::vector<float>	*ringer_lvl2_phi;
	std::vector<float>	*ringer_lvl2_et;
    std::vector<float>  *ringer_lvl1_id;
    std::vector<float>  *ringer_roi_id;


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

    unsigned    getLayerInit(const unsigned numEvent, const unsigned curLayer);
    double      max(const unsigned layerInit, const unsigned curLayer);
    double      min(const unsigned layerInit, const unsigned curLayer);
    double      calcNorm0(const unsigned layerInit, const unsigned curLayer);
    void        fillNormValues(double norm[], const unsigned layerInit, const unsigned curLayer);
    void        applySequentialNorm(const double norm[], const unsigned layerInit, const unsigned curLayer);

    public:

    RootSeq(TChain *outsideReadingChain, TTree *outsidefillingTree);
    ~RootSeq();

    CODE normalise();

};


const unsigned  RootSeq::ringsDist[] = {8, 64, 8, 8, 4, 4, 4};


#endif
