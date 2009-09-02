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
<<<<<<< HEAD:rootSeq.h
    static const float     stopEnergy = 100.;
    static const float     energyThreshold = 0.001;
    static const int       DEBUG = 1;
=======
    static const double     stopEnergy = 100.;
    static const double     energyThreshold = 0.001;
    static const int       DEBUG = 0;
>>>>>>> 0d3cf3a8e71ca422ddcab377f37df52c31dd6e85:rootSeq.h

	std::vector<double>	*ringer_rings;
	std::vector<double>	*ringer_lvl2_eta;
	std::vector<double>	*ringer_lvl2_phi;
	std::vector<double>	*ringer_lvl2_et;


	std::vector<double>	*t2ca_lvl2_eta;
	std::vector<double>	*t2ca_lvl2_phi;
	std::vector<double>	*t2ca_rcore;
	std::vector<double>	*t2ca_eratio;
	std::vector<double>	*t2ca_emes1;
	std::vector<double>	*t2ca_eme;
    std::vector<double>  *t2ca_ehades0;

	std::vector<double>	*t2cahade;

	UInt_t          	*ringer_nclusters;
    UInt_t          	*t2canclus;

    TTree   *fillingTree;
    TChain  *readingChain;

    ofstream *debugFile;

    unsigned    getLayerInit(const unsigned numEvent, const unsigned curLayer);
    double       max_abs(const unsigned layerInit, const unsigned curLayer);
    double       calcNorm0(const unsigned layerInit, const unsigned curLayer);
    void        fillNormValues(double norm[], const unsigned layerInit, const unsigned curLayer);
    void        applySequentialNorm(const double norm[], const unsigned layerInit, const unsigned curLayer);

    public:

    RootSeq(TChain *outsideReadingChain, TTree *outsidefillingTree);
    ~RootSeq();

    CODE normalise();

};


const unsigned  RootSeq::ringsDist[] = {8, 64, 8, 8, 4, 4, 4};


#endif
