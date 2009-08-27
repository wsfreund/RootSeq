#ifndef ROOTSEQ

#include<TChain.h>
#include<TTree.h>
#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>
#include<iomanip>


#define ROOTSEQ


class RootSeq {

	enum CODE {ERROR=0, OK};

    static const unsigned  ringsDist[];
    static const float     stopEnergy = 100.;
    static const float     energyThreshold = 0.001;
    static const int       DEBUG = 0;

	std::vector<float>	*ringer_rings;
	std::vector<float>	*ringer_lvl2_eta;
	std::vector<float>	*ringer_lvl2_phi;
	std::vector<float>	*ringer_lvl2_et;
	std::vector<float>	*ringer_nclusters;

	std::vector<float>	*t2ca_lvl2_eta;
	std::vector<float>	*t2ca_lvl2_phi;
	std::vector<float>	*t2ca_rcore;
	std::vector<float>	*t2ca_eratio;
	std::vector<float>	*t2ca_emes1;
	std::vector<float>	*t2ca_eme;
    std::vector<float>  *t2ca_ehades0;
	std::vector<float>	*t2canclus;
	std::vector<float>	*t2cahade;

    TTree   *fillingTree;
    TChain  *readingChain;

    ofstream *debugFile;

    unsigned    getLayerInit(const unsigned numEvent, const unsigned curLayer);
    float       max_abs(const unsigned layerInit, const unsigned curLayer);
    float       calcNorm0(const unsigned layerInit, const unsigned curLayer);
    void        fillNormValues(float norm[], const unsigned layerInit, const unsigned curLayer);
    void        applySequentialNorm(const float norm[], const unsigned layerInit, const unsigned curLayer);

    public:

    RootSeq(TChain *outsideReadingChain, TTree *outsidefillingTree);
    ~RootSeq();

    CODE normalise();

};


const unsigned  RootSeq::ringsDist[] = {8, 64, 8, 8, 4, 4, 4};


#endif
