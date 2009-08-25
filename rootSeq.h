#include<TChain.h>
#include<cmath>

#ifndef ROOTSEQ
#define ROOTSEQ

class RootSeq {

	enum CODE {ERROR=0, OK};

    const unsigned  ringsDist[];
    const float     stopEnergy;
    const float     energyThreshold;

	vector<float>	*ringer_rings;
	vector<float>	*ringer_lvl2_eta;
	vector<float>	*ringer_lvl2_phi;
	vector<float>	*ringer_lvl2_et;

	vector<float>	*t2ca_lvl2_eta;
	vector<float>	*t2ca_lvl2_phi;
	vector<float>	*t2ca_rcore;
	vector<float>	*t2ca_eratio;
	vector<float>	*t2ca_emes1;
	vector<float>	*t2ca_eme;
    vector<float>   *t2ca_ehades0;


    TChain  *fillingChain;
    TChain  *readingChain;

    unsigned    getLayerInit(unsigned numEvent, unsigned layerNumber);
    float       max_abs(unsigned layerInit);
    float       calcNorm0(unsigned layerInit);
    void        fillNormValues(float norm[], layerInit);
    void        applySequentialNorm(float norm[], layerInit);

    public:

    RootSeq(TChain *outsideChain, TChain *outsideFillingChain, unsigned usrRingsDist[], float usrStopEnergy, float usrEnergyThreshold);

    CODE normalise();

};
