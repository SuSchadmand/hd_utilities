// $Id$
//
//    File: FCALbadchannels.hh
// Created: Wed Sep 11 13:39:58 EDT 2019
// Creator: cakondi (on Linux ifarm1802 3.10.0-327.el7.x86_64 x86_64)
//

#ifndef _FCALbadchannels_
#define _FCALbadchannels_

#include <JANA/JEventProcessor.h>
#include <TRACKING/DTrackFitter.h>
#include <TRACKING/DReferenceTrajectory.h>
using namespace jana;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <TRIGGER/DL1Trigger.h>

#include "TApplication.h"
#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include "TProfile.h"
#include "TCanvas.h"
#include <TH3.h>


class FCALbadchannels:public jana::JEventProcessor{
public:
  FCALbadchannels();
  ~FCALbadchannels();
  const char* className(void){return "FCALbadchannels";}
  
private:
  jerror_t init(void);						///< Called once at program start.
  jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);	///< Called everytime a new run number is detected.
  jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
  jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
  jerror_t fini(void);						///< Called after last event of last event source has been processed.
  
  
  
  
  
  ////// trigger bit section  variables
  
  static const Int_t max_bit  =  32;
  Int_t trig_bit[max_bit];
  Int_t trig_bit_fp[max_bit];
  
  Int_t trigbit;
  Int_t trigfpbit;
  
  static const Int_t  kBlocksWidth = 59 ;
  static const Int_t  kBlocksHeight = 59 ;
  static const Int_t  max_blocks  =  kBlocksWidth*kBlocksHeight;  /// 59 x59 = # blocks width x # blocks height
  static const Int_t  nranges  =  5;
  
  TH1F *htrigfp;
  TH1F *hrawtrigbit;

  TH1F *hAllInte;
  TH1F *hTotalInte;
  TH1F *hTotalInteCut;
  TH1F *hRanges;

  TH1F *hhitcnter;
  TH2F *hTotalInteHits;
  TH2F *hhitt;
  
  TH1F *hNhits;
  TH2F *hRowColOcc;
  TH1F *hEff;
  TH2F *hRowColEff;

  TH1F *hEffReg_[nranges];
  TH2F *hRowColReg_[nranges];

  TH1F *hRangesE;
  TH1F *hTotalInteE;
  TH1F *hHitTime2121;
  TH1F *hTotalInteE_Cut;
  TH1F *hHitTimeRange0_[max_blocks];
  TH1F *hHitTimeRange1_[max_blocks];
  TH1F *hHitTimeRange2_[max_blocks];
  TH1F *hHitTimeRange3_[max_blocks];
  TH1F *hHitTimeRange4_[max_blocks];
  
};

#endif // _FCALbadchannels_

