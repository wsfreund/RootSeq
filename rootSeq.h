#ifndef ROOTSEQ

#include<TChain.h>
#include<vector>
#include<cmath>


#define ROOTSEQ

class RootSeq {

	enum CODE {ERROR=0, OK};

    static const unsigned  ringsDist[];
    static const float     stopEnergy = 100.;
    static const float     energyThreshold = 0.001;

	std::vector<float>	*ringer_rings;
	std::vector<float>	*ringer_lvl2_eta;
	std::vector<float>	*ringer_lvl2_phi;
	std::vector<float>	*ringer_lvl2_et;

	std::vector<float>	*t2ca_lvl2_eta;
	std::vector<float>	*t2ca_lvl2_phi;
	std::vector<float>	*t2ca_rcore;
	std::vector<float>	*t2ca_eratio;
	std::vector<float>	*t2ca_emes1;
	std::vector<float>	*t2ca_eme;
    std::vector<float>  *t2ca_ehades0;


    TChain  *fillingChain;
    TChain  *readingChain;

    unsigned    getLayerInit(unsigned numEvent, unsigned curLayer);
    float       max_abs(unsigned layerInit, unsigned curLayer);
    float       calcNorm0(unsigned layerInit, unsigned curLayer);
    void        fillNormValues(float norm[], unsigned layerInit, unsigned curLayer);
    void        applySequentialNorm(float norm[], unsigned layerInit, unsigned curLayer);



    public:

    RootSeq(TChain *outsideChain, TChain *outsideFillingChain);
    ~RootSeq();

    CODE normalise();

};


#endif
