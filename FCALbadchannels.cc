// $Id$
//
//    File: FCALbadchannels.cc
// Created: Wed Sep 11 13:39:58 EDT 2019
// Creator: cakondi (on Linux ifarm1802 3.10.0-327.el7.x86_64 x86_64)
//
#include <iostream>
#include <iomanip>
#include <map>
#include "FCALbadchannels.hh"
using namespace jana;
#include <JANA/JEvent.h>
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
//// DFCAL Hit factory.cc included the following header files
#include <HDGEOMETRY/DGeometry.h>
#include "FCAL/DFCALDigiHit.h"
#include "FCAL/DFCALGeometry.h"
#include "FCAL/DFCALHit_factory.h"
#include "DAQ/Df250PulseIntegral.h"
#include "DAQ/Df250PulsePedestal.h"
#include "DAQ/Df250Config.h"
#include "TTAB/DTTabUtilities.h"
#include <FCAL/DFCALHit.h>
#include <TRIGGER/DL1Trigger.h>
#include <DAQ/DL1Info.h>
#include "DVector2.h"
#include "units.h"
#include <DVector3.h>
#include "FCAL/DFCALCluster.h"
#include "FCAL/DFCALCluster_factory.h"
#include "HDGEOMETRY/DGeometry.h"
#include <FCAL/DFCALShower.h>
#include <FCAL/DFCALHit.h>
#include <PID/DEventRFBunch.h>
#include "TApplication.h"
#include "TH3.h"






// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
extern "C"{
void InitPlugin(JApplication *app){
  InitJANAPlugin(app);
  app->AddProcessor(new FCALbadchannels());
}
} // "C"


//------------------
// FCALbadchannels (Constructor)
//------------------
FCALbadchannels::FCALbadchannels()
{
  
}

//------------------
// ~FCALbadchannels (Destructor)
//------------------
FCALbadchannels::~FCALbadchannels()
{
  
}

//------------------
// init
//------------------
jerror_t FCALbadchannels::init(void)
{
  char hname[100];
  const int max_blocks  =  2800, max_rows = 59 , max_cols = 59;
  static const int  nranges  =  5;

  htrigfp     = new TH1F("htrigfp", "", 32,0,31);
  hrawtrigbit = new TH1F("hrawtrigbit", "", 32,0,31);
  
  hAllInte  = new TH1F("hAllInte", "", 2000,0,200000);
  
  hTotalInte  = new TH1F("hTotalInte", "", 20000,0.,200000000.);
  hTotalInteCut  = new TH1F("hTotalInteCut", "", 20000,0.,200000000.);
  hRanges     = new TH1F("hRanges", "", 20000,0.,200000000.);

  hhitcnter      = new TH1F("hhitcnter", "", 11,0,10);
  hTotalInteHits = new TH2F("hTotalInteHits", "",20000,0.,200000000., 11,0,10);
  
  hNhits = new TH1F("hNhits", "", max_blocks,-0.5,max_blocks-0.5);
  hEff   = new TH1F("hEff",   "", max_blocks,-0.5,max_blocks-0.5);
  
  hRowColOcc = new TH2F("hRowColOcc", "", max_cols,-0.5,max_cols-0.5, max_rows,-0.5,max_rows-0.5);
  hRowColEff = new TH2F("hRowColEff", "", max_cols,-0.5,max_cols-0.5, max_rows,-0.5,max_rows-0.5);

  for(int ira=0; ira<nranges; ira++){
	sprintf(hname,"hEffReg_%d", ira);    hEffReg_[ira]    = new TH1F(hname,"",max_blocks,-0.5,max_blocks-0.5);
	sprintf(hname,"hRowColReg_%d", ira); hRowColReg_[ira] = new TH2F(hname,"",max_cols,-0.5,max_cols-0.5, max_rows,-0.5,max_rows-0.5);
  }
 
  //-----------------
  //--- for LED time:
  //
  hTotalInteE = new TH1F("hTotalInteE", "", 2000,0.,20000.);
  hHitTime2121= new TH1F("hHitTime2121","",211,-10.5,200.5);
  hTotalInteE_Cut = new TH1F("hTotalInteE_Cut", "", 2000,0.,20000.);
  hRangesE       = new TH1F("hRangesE", "", 2000,0.,20000.);
  for(Int_t ibl = 0; ibl < max_blocks; ibl++) {
	sprintf(hname,"hHitTimeRange0_%d",ibl);
	hHitTimeRange0_[ibl]= new TH1F(hname,"",211,-10.5,200.5);
	sprintf(hname,"hHitTimeRange1_%d",ibl);
	hHitTimeRange1_[ibl]= new TH1F(hname,"",211,-10.5,200.5);
	sprintf(hname,"hHitTimeRange2_%d",ibl);
	hHitTimeRange2_[ibl]= new TH1F(hname,"",211,-10.5,200.5);
	sprintf(hname,"hHitTimeRange3_%d",ibl);
	hHitTimeRange3_[ibl]= new TH1F(hname,"",211,-10.5,200.5);
	sprintf(hname,"hHitTimeRange4_%d",ibl);
	hHitTimeRange4_[ibl]= new TH1F(hname,"",211,-10.5,200.5);
  }

  
  return NOERROR;
}

//------------------
// brun
//------------------
jerror_t FCALbadchannels::brun(JEventLoop *eventLoop, int32_t runnumber)
{
  // This is called whenever the run number changes
  return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t FCALbadchannels::evnt(JEventLoop *loop, uint64_t eventnumber)
{
  ///// extract the FCAL Geometry information DFCALHits_factory.cc
  
  vector<const DFCALGeometry*> fcalGeomVect;
  loop->Get( fcalGeomVect );
  if (fcalGeomVect.size() < 1)
	return OBJECT_NOT_AVAILABLE;
  const DFCALGeometry& fcalGeom = *(fcalGeomVect[0]);
  
  
  ///////////////Trigger and Front Panel Trigger /////////////////////////
  
  vector<const DL1Trigger *> l1trig;
  loop->Get(l1trig);
  
  japp->RootFillLock(this);
  
  int rawtrignumber,trigfpnumber;
  if( l1trig.size() > 0) {
	for(unsigned int trigcounter = 0; trigcounter < 32; trigcounter++){
	  trig_bit[trigcounter+1] = (l1trig[0]->trig_mask & (1 << trigcounter)) ? 1 : 0;
	  if (trig_bit[trigcounter+1] == 1) {
		trigbit=trigcounter+1;
		rawtrignumber=trigbit;
		//hrawtrigbit->Fill(trigbit);
	  }
	}
	hrawtrigbit->Fill(trigbit);

	for(unsigned int  trigfpcounter = 0; trigfpcounter < 32; trigfpcounter++){
	  trig_bit_fp[trigfpcounter+1] = (l1trig[0]->fp_trig_mask & (1 << trigfpcounter)) ? 1 : 0;
	  if (trig_bit_fp[trigfpcounter+1] == 1) {
		trigfpbit=trigfpcounter+1;
		trigfpnumber=trigfpbit;
		//htrigfp->Fill(trigfpbit);
	  }
	}
	htrigfp->Fill(trigfpbit);
  }
  
  //-----------------
  if(trigfpnumber!=3) return  NOERROR;   // trigfpnumber!=3 for FCAL FP trigger
  // if(rawtrignumber!=1) return  NOERROR; // trignumber!=1 for rawdata // trignumber !4 for PS

  vector<const DFCALDigiHit*> digihits;
  loop->Get(digihits);
    
  Double_t  RegLo[5] = { 5e+6, 10e+6, 15e+6, 28e+6, 33e+6};
  // Double_t  RegHi[5] = {10e+6, 15e+6, 20e+6, 33e+6, 38e+6};
  Double_t  RegHi[5] = {10e+6, 15e+6, 20e+6, 33e+6, 45e+6};// RunPeriod-2019-11 -- not great

  for(int ira=0; ira<nranges; ira++){
	hRanges->Fill(RegLo[ira]);
	hRanges->Fill(RegHi[ira]);
  }
  
  float TotalInte=0;
  int Row[max_blocks], Column[max_blocks];
  int hitcnter[max_blocks];
  for(int ibl=0; ibl<max_blocks; ibl++){
	hitcnter[ibl] = 0;
  }
  
  for(unsigned int i=0; i < digihits.size(); i++) {
  const DFCALDigiHit *digihit = digihits[i];
	if (digihit->pulse_time == 0 || digihit->pedestal == 0 || digihit->pulse_peak == 0) continue;
	int  ibl = fcalGeom.channel(digihit->row,digihit->column);
	Row[ibl] = digihit->row;
	Column[ibl] = digihit->column;
	hitcnter[ibl]++;

	hNhits->Fill(ibl);
	hRowColOcc->Fill(Column[ibl],Row[ibl]);
		
	double inte = (digihit->pulse_integral) -(((double)digihit->pedestal/digihit->nsamples_pedestal)*digihit->nsamples_integral);

	hAllInte->Fill(inte);

	TotalInte += inte;
  }
  hTotalInte->Fill(TotalInte);

  if (TotalInte > RegLo[0] && TotalInte <= RegHi[4]){
	hTotalInteCut->Fill(TotalInte);

	for(int ibl=0; ibl<max_blocks; ibl++){
	  if (hitcnter[ibl] > 0) {
		
		hEff->Fill(ibl);
		hRowColEff->Fill(Column[ibl],Row[ibl]);
		
		for(int ira=0; ira<nranges; ira++){
		  if (TotalInte > RegLo[ira] && TotalInte <= RegHi[ira]){
			hEffReg_[ira]->Fill(ibl);
			hRowColReg_[ira]->Fill(Column[ibl],Row[ibl]);
		  }
		}
		
		int yval;
		if (hitcnter[ibl] <= 10) yval = hitcnter[ibl];
		if (hitcnter[ibl] >  10) yval = 10;
		hhitcnter->Fill(yval);
		hTotalInteHits->Fill(TotalInte, yval);
				
	  } // hitcnter
	} // ibl
  } // TotalInte threshold

  
  //-----------------
  //--- for LED time:
  //
  vector<const DFCALHit *>  fcalhits;
  loop->Get(fcalhits);

  // RunPeriod-2019-11
  Double_t  RegLoE[5] = {2000, 3200, 4700, 6500, 8000};
  Double_t  RegHiE[5] = {3200, 4700, 6500, 8000, 10000};
  
  for(int ira=0; ira<nranges; ira++){
	hRangesE->Fill(RegLoE[ira]);
	hRangesE->Fill(RegHiE[ira]);
  }

  float TotalInteE=0;
  for (unsigned int i = 0; i < fcalhits.size(); i++){
  const DFCALHit *fcalhit = fcalhits[i];
	int  ibl = fcalGeom.channel(fcalhit->row, fcalhit->column);
	if(trigfpnumber==3){
	  TotalInteE += fcalhit->E;
	  if (ibl == 2121) hHitTime2121->Fill(fcalhit->t);
	}
  }
  
  hTotalInteE->Fill(TotalInteE);
  for(int ira=0; ira<nranges; ira++){
	if (TotalInteE > RegLoE[ira] && TotalInteE <= RegHiE[ira]){
	  hTotalInteE_Cut->Fill(TotalInteE);
	  for (unsigned int i = 0; i < fcalhits.size(); i++){
		const DFCALHit *fcalhit = fcalhits[i];
		int  ibl = fcalGeom.channel(fcalhit->row, fcalhit->column);
		if (ira == 0) hHitTimeRange0_[ibl]->Fill(fcalhit->t);
		if (ira == 1) hHitTimeRange1_[ibl]->Fill(fcalhit->t);
		if (ira == 2) hHitTimeRange2_[ibl]->Fill(fcalhit->t);
		if (ira == 3) hHitTimeRange3_[ibl]->Fill(fcalhit->t);
		if (ira == 4) hHitTimeRange4_[ibl]->Fill(fcalhit->t);
	  }
	}
  }


  
  japp->RootFillUnLock(this);
  
  return NOERROR;
}

//------------------
// erun
//------------------
jerror_t FCALbadchannels::erun(void)
{
  // This is called whenever the run number changes, before it is
  // changed to give you a chance to clean up before processing
  // events from the next run number.
  return NOERROR;
}

//------------------
// fini
//------------------
jerror_t FCALbadchannels::fini(void)
{
  // Called before program exit after event processing is finished.
  return NOERROR;
}

