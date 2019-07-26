// $Id$
//
//    File: DEventProcessor_photon_gun_hists.cc
// Created: Thu Aug 23 11:25:21 EDT 2018
// Creator: jzarling (on Linux stanley.physics.indiana.edu 2.6.32-696.18.7.el6.x86_64 x86_64)
//

#include "DEventProcessor_photon_gun_hists.h"

// Routine used to create our DEventProcessor

extern "C"
{
	void InitPlugin(JApplication *locApplication)
	{
		InitJANAPlugin(locApplication);
		locApplication->AddProcessor(new DEventProcessor_photon_gun_hists()); //register this plugin
		// locApplication->AddFactoryGenerator(new DFactoryGenerator_photon_gun_hists()); //register the factory generator
	}
} // "C"

//------------------
// init
//------------------
jerror_t DEventProcessor_photon_gun_hists::init(void)
{
	// This is called once at program startup.

	DELTAPHI_CUTPARM = 3.35; //Degrees
	DELTATHETA_CUTPARM = 0.35; //Degrees
	EMIN_CUTPARM = -1.; //GeV
	EMAX_CUTPARM = 1000; //GeV
	THETAMIN_CUTPARM = 0; //Degrees
	THETAMAX_CUTPARM = 1000; //Degrees
	
	if(gPARMS) {
	  gPARMS->SetDefaultParameter("PHOTONHISTS:DELTAPHI_CUTPARM",   DELTAPHI_CUTPARM);
	  gPARMS->SetDefaultParameter("PHOTONHISTS:DELTATHETA_CUTPARM", DELTATHETA_CUTPARM);
	  gPARMS->SetDefaultParameter("PHOTONHISTS:EMIN_CUTPARM",   EMIN_CUTPARM);
	  gPARMS->SetDefaultParameter("PHOTONHISTS:EMAX_CUTPARM", EMAX_CUTPARM);
	  gPARMS->SetDefaultParameter("PHOTONHISTS:THETAMIN_CUTPARM",   THETAMIN_CUTPARM);
	  gPARMS->SetDefaultParameter("PHOTONHISTS:THETAMAX_CUTPARM", THETAMAX_CUTPARM);
	}
	
	// Create directory
	TDirectory *dir = (TDirectory*)gROOT->FindObject("photon_gun_hists");
	if(!dir) dir = new TDirectoryFile("photon_gun_hists","photon_gun_hists");
	dir->cd();
	
	
 	//Initialize histograms here
	// h_thrownE_all_dist = new TH1F("h_thrownE_dist","Thrown Photon Energy Distribution",1000,0,10.);
	// h_thrownE_foundshow_dist = new TH1F("h_thrownE_foundshow_dist","Thrown Photon Energy, FCAL Shower Found",1000,0,10.);
	// h_reconE_dist = new TH1F("h_reconE_dist","Thrown Photon Energy Distribution",1000,0,10.);
	
	h_foundE_all_dist = new TH1F("h_foundE_all_dist","Found Photon Energy Distribution",1000,0,10.);
	h_foundE_DeltaPhiCuts_dist = new TH1F("h_foundE_DeltaPhiCuts_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_NeutralShower_DeltaPhiCuts_dist = new TH1F("h_foundE_NeutralShower_DeltaPhiCuts_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_NeutralShowerPreselect_DeltaPhiCuts_dist = new TH1F("h_foundE_NeutralShowerPreselect_DeltaPhiCuts_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_NeutralShowerHypothesis_DeltaPhiCuts_dist = new TH1F("h_foundE_NeutralShowerHypothesis_DeltaPhiCuts_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_NeutralParticle_DeltaPhiCuts_dist = new TH1F("h_foundE_NeutralParticle_DeltaPhiCuts_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_highestE_dist = new TH1F("h_foundE_highestE_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_primary_dist = new TH1F("h_foundE_primary_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_nonprimary_dist = new TH1F("h_foundE_nonprimary_dist","Found Photon Energy Distribution",1000,0,10.);
	
	// h_foundE_1orless_all_dist = new TH1F("h_foundE_1orless_all_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE__1orlessprimary_dist = new TH1F("h_foundE__1orlessprimary_dist","Found Photon Energy Distribution",1000,0,10.);
	// h_foundE_1orless_nonprimary_dist = new TH1F("h_foundE_1orless_nonprimary_dist","Found Photon Energy Distribution",1000,0,10.);
	
	h_PhotonInteractionZ = new TH1F("h_PhotonInteractionZ","Photon Interaction Z Position",10000,40,900.);
	h_PhotonInteractionMech = new TH1F("h_PhotonInteractionMech","Photon Interaction mech",201,0,20.);
	h2_PhotonInteractionMechvsInteractionZ = new TH2F("h2_PhotonInteractionMechvsInteractionZ","Photon Interaction mech vs Interaction Z",1000,40,900.,201,0,20.);
	h_PhotonInteractionCase = new TH1F("h_PhotonInteractionCase","",1000,0,5.);
	
	h_NFCALShowers = new TH1F("h_NFCALShowers","Number of Showers In Event (all cases)",1000,0,15.);
	// h_NNeutralShowers = new TH1F("h_NNeutralShowers","Number of Neutral Showers In Event (all cases)",1000,0,15.);
	// h_NNeutralShowersPreselect = new TH1F("h_NNeutralShowersPreselect","Number of Neutral Showers In Event (all cases)",1000,0,15.);
	// h_NFCALShowers_nonprimary = new TH1F("h_NFCALShowers_nonprimary","Number of Showers In Event (all cases)",1000,0,15.);
	// h_NFCALShowers_primary = new TH1F("h_NFCALShowers_primary","Number of Showers In Event (all cases)",1000,0,15.);
	
	h_ThrownPhotonE = new TH1F("h_ThrownPhotonE","Thrown Photon Energy",1000,0,10.);
	h_thrownTheta = new TH1F("h_thrownTheta","Thrown Photon #theta",10000,0,180.);
	
	h2_DeltaThetaDeltaPhi_all = new TH2F("h2_DeltaThetaDeltaPhi_all","#Delta #phi thrown and shower vs. #Delta #theta thrown and shower",1000,-90.,90,1000,-180.,180.);
	h_DeltaPhi_all = new TH1F("h_DeltaPhi_all","#Delta #phi thrown and shower",10000,-180.,180.);
	h_DeltaTheta_all = new TH1F("h_DeltaTheta_all","#Delta #theta thrown and shower",10000,-90.,90);
	
	//Histograms separated by where primary photon interacts. No consideration to secondaries here.
	//Barrel region: includes target, SC, CDC, FDC
	//AND upstream until arriving at TOF, hopefully name isn't too misleading
	h_foundE_BarrelRegionInteract_dist = new TH1F("h_foundE_BarrelRegionInteract_dist","Found Photon Energy Distribution, Interacts In Barrel Region",1000,0,10.);
	h_foundE_BarrelRegionInteract_DeltaPhiCuts_dist = new TH1F("h_foundE_BarrelRegionInteract_DeltaPhiCuts_dist","Found Photon Energy Distribution, Interacts In Barrel Region",1000,0,10.);
	//TOF region: includes TOF and FCAL darkroom material, hopefully name isn't too misleading
	h_foundE_TOFRegionInteract_dist = new TH1F("h_foundE_TOFRegionInteract_dist","Found Photon Energy Distribution, Interacts In TOF Region",1000,0,10.);
	h_foundE_TOFRegionInteract_DeltaPhiCuts_dist = new TH1F("h_foundE_TOFRegionInteract_DeltaPhiCuts_dist","Found Photon Energy Distribution, Interacts In TOF Region",1000,0,10.);
	//FCAL region: only FCAL material proper and a little behind
	h_foundE_FCALRegionInteract_dist = new TH1F("h_foundE_FCALRegionInteract_dist","Found Photon Energy Distribution, Interacts In FCAL Region",1000,0,10.);
	h_foundE_FCALRegionInteract_DeltaPhiCuts_dist = new TH1F("h_foundE_FCALRegionInteract_DeltaPhiCuts_dist","Found Photon Energy Distribution, Interacts In FCAL Region",1000,0,10.);
	
	//For all non-primary truth showers, plot opening angle between thrown photon and each shower 
	// h_nonprimary_FCALTruthShower_opangle = new TH1F("h_nonprimary_FCALTruthShower_opangle","Thrown Photon Opening Angle to Truth Shower",10000,0,180.);
	// h_nonprimary_TOFconv_FCALTruthShower_opangle = new TH1F("h_nonprimary_TOFconv_FCALTruthShower_opangle","Thrown Photon Opening Angle to Truth Shower",10000,0,180.);
	// h_nonprimary_notTOFconv_FCALTruthShower_opangle = new TH1F("h_nonprimary_notTOFconv_FCALTruthShower_opangle","Thrown Photon Opening Angle to Truth Shower",10000,0,180.);
	
	// h_thrownE_pairprod = new TH1F("h_thrownE_pairprod","Thrown Photon Energy Distribution",1000,0,10.);
 
	h_NFCALShowers->GetXaxis()->SetTitle("Number of FCAL Showers Reconstructed");
	h_foundE_all_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_DeltaPhiCuts_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_PhotonInteractionZ->GetXaxis()->SetTitle("Primary Photon Interaction Z (cm)");
	h_PhotonInteractionMech->GetXaxis()->SetTitle("Reaction Mechanism");
	h2_PhotonInteractionMechvsInteractionZ->GetXaxis()->SetTitle("Primary Photon Interaction Z (cm)");
	h2_PhotonInteractionMechvsInteractionZ->GetYaxis()->SetTitle("Reaction Mechanism");
	h_ThrownPhotonE->GetXaxis()->SetTitle("Thrown Photon Energy (GeV)");
	h_thrownTheta->GetXaxis()->SetTitle("Thrown Photon #theta (degrees)");
	h_DeltaPhi_all->GetXaxis()->SetTitle("#Delta#phi, thrown vs. reconstructed #gamma (degrees)");
	h_DeltaTheta_all->GetXaxis()->SetTitle("#Delta#theta, thrown vs. reconstructed #gamma (degrees)");
	h2_DeltaThetaDeltaPhi_all->GetXaxis()->SetTitle("#Delta#theta, thrown vs. reconstructed #gamma (degrees)");
	h2_DeltaThetaDeltaPhi_all->GetYaxis()->SetTitle("#Delta#phi, thrown vs. reconstructed #gamma (degrees)");
	h_foundE_BarrelRegionInteract_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_BarrelRegionInteract_DeltaPhiCuts_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_TOFRegionInteract_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_TOFRegionInteract_DeltaPhiCuts_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_FCALRegionInteract_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_foundE_FCALRegionInteract_DeltaPhiCuts_dist->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
	h_PhotonInteractionCase->GetXaxis()->SetTitle("0=primary photon interacts in barrel region, 1=TOF region, 2=FCAL region");
 
 
	/*
	//OPTIONAL: Create an EventStore skim.  
	string locSkimFileName = "photon_gun_hists.idxa";
	dEventStoreSkimStream.open(locSkimFileName.c_str());
	dEventStoreSkimStream << "IDXA" << endl;
	*/

	//CREATE TTREE, TFILE
	// photon_gun_tree_fname = "photon_gun_trees.root";
	// gPARMS->SetDefaultParameter("photon_gun_tree_fname",photon_gun_tree_fname);
	// dTreeInterface = DTreeInterface::Create_DTreeInterface("photon_gun", photon_gun_tree_fname);
	
	//TTREE BRANCHES
	// DTreeBranchRegister locBranchRegister;
	
	// locBranchRegister.Register_Single<Float_t>("thrown_X"); //Propogated to edge of FCAL
	// locBranchRegister.Register_Single<Float_t>("thrown_Y"); //Propogated to edge of FCAL
	// locBranchRegister.Register_Single<Float_t>("thrown_Z"); //Propogated to edge of FCAL
	// locBranchRegister.Register_Single<Float_t>("thrown_E"); //Propogated to edge of FCAL
	// locBranchRegister.Register_Single<Int_t>("Num_MCThrown");
	
	// locBranchRegister.Register_Single<Int_t>("InitPhotonShowersFCAL");
	// locBranchRegister.Register_Single<Int_t>("NonPrimaryFCALTruthFlag");
	// locBranchRegister.Register_Single<Int_t>("PhotonConvertsInTOF");
	// locBranchRegister.Register_Single<Int_t>("NFCALShowers");
	// locBranchRegister.Register_Single<Int_t>("NFCALTruthShowers");
	// locBranchRegister.Register_Single<Int_t>("NBCALShowers");
	// locBranchRegister.Register_Single<Int_t>("NBCALTruthShowers");
	// locBranchRegister.Register_Single<Int_t>("NTrackCandidates");
	
	// locBranchRegister.Register_Single<Float_t>("TruthShowers_Esum");
	// locBranchRegister.Register_Single<Float_t>("TruthShowers_nearby_Esum");
	
	// locBranchRegister.Register_Single<Float_t>("Ediff_recon_thr");
	// locBranchRegister.Register_Single<Float_t>("Ediff_truthshow_thr");
	// locBranchRegister.Register_Single<Float_t>("Ediff_neartruthshow_thr");
	
	// string locArraySizeString  =  "NumMaxShowers";
	// locBranchRegister.Register_Single<UInt_t>(locArraySizeString);
	// locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_X","NumMaxShowers",5);
	// locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_Y","NumMaxShowers",5);
	// locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_Z","NumMaxShowers",5);
	// locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_E","NumMaxShowers",5);
	// locBranchRegister.Register_FundamentalArray<Int_t>("IsFCAL","NumMaxShowers",5);
	
	
	
	
	//REGISTER BRANCHES
	// dTreeInterface->Create_Branches(locBranchRegister);
	
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t DEventProcessor_photon_gun_hists::brun(jana::JEventLoop* locEventLoop, int32_t locRunNumber)
{
	// This is called whenever the run number changes

	GX_Geom = NULL;
	DApplication *dapp = dynamic_cast< DApplication* >( locEventLoop->GetJApplication() );
	if( dapp ) GX_Geom = dapp->GetDGeometry( locRunNumber );	
	GX_Geom->GetFCALZ( fcalFrontFaceZ );

	verbosity_counter = 0;
	DMCTrajectoryPoint_checker = 0;
	
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t DEventProcessor_photon_gun_hists::evnt(jana::JEventLoop* locEventLoop, uint64_t locEventNumber)
{
	
	//Retrieve MCThrown stuff
	vector<const DMCThrown*> locMCThrowns;
	locEventLoop->Get(locMCThrowns);


	//Check MCThrown info. Must not be empty, first entry must be a photon
	if(locMCThrowns.size()==0) {
		cout << "ERROR! Thrown MC info empty! Skipping event..." << endl;
		return NOERROR;
	}
	// if(locMCThrowns.size()>=2) {
		// cout << "Warning! Found more than just one photon in MCThrown info. Topology is wrong or pair production occurred" << endl;
		// cout << "Number found: " << locMCThrowns.size() << endl;
		// return NOERROR;
	// }	
	if(locMCThrowns.size()==1&&locMCThrowns[0]->PID()!=Gamma) {
		cout << "Error: Correct number of MCThrown objects, but wrong PID" << endl;
		return NOERROR;
	}	
	if(locMCThrowns[0]->PID()!=Gamma) {
		cout << "Error: MCThrown object is not photon PID" << endl;
		return NOERROR;
	}	
	
	const DMCThrown* locThrownPhoton = locMCThrowns[0];
	
	if(locMCThrowns.size()>=2) {
		if(verbosity_counter<=2) cout << "Warning: multiple final state photons found in list of thrown products. Hists only use first photon in MCThrown list!! " << endl;
		

		for(int loc_i=0; loc_i<locMCThrowns.size(); ++loc_i) {
			verbosity_counter++;
			if(locMCThrowns[loc_i]->PID()==Gamma) {
				locThrownPhoton = locMCThrowns[loc_i];
				break;
				}
		}
	}
	
	auto locThrownPhotonP4 = locThrownPhoton->lorentzMomentum();
	
	//Cuts on sample, before entering any hists
	if(locThrownPhotonP4.E() < EMIN_CUTPARM || locThrownPhotonP4.E() > EMAX_CUTPARM) return NOERROR;
	if(locThrownPhotonP4.Theta()*180/3.14159 < THETAMIN_CUTPARM || locThrownPhotonP4.Theta()*180/3.14159 > THETAMAX_CUTPARM) return NOERROR;
	
	
	
	//Retrieve DMCTrajectoryPoint stuff
	vector<const DMCTrajectoryPoint*> locDMCTrajectoryPoints;
	locEventLoop->Get(locDMCTrajectoryPoints);
	bool valid_DMCTrajectoryInfo = false;
	
	// cout << "Size of trajectory points: " << locDMCTrajectoryPoints.size() << endl;
	if(locDMCTrajectoryPoints.size() == 0) {
		DMCTrajectoryPoint_checker++;
		if(DMCTrajectoryPoint_checker <=15) cout << "Warning: DMCTrajectoryPoint data is empty. Histograms that rely on this information will be empty. Check that your control.in file used for generation has flag TRAJECTORIES set to 1 or more" <<endl;
	}
	
	//If DMCThrown.size() is not 1, then I don't know what indexing should be.
	if(locDMCTrajectoryPoints.size() >= 1 && locMCThrowns.size() == 1) valid_DMCTrajectoryInfo = true;
	
	if(valid_DMCTrajectoryInfo) {
		// cout << "z position of photon birth (from generator) " << locDMCTrajectoryPoints[0]->z << endl;
		// cout << "z position of photon death (determined by geant) " << locDMCTrajectoryPoints[1]->z << endl;
		japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		double locPrimaryZ = locDMCTrajectoryPoints[1]->z;
		if(40.<locPrimaryZ&&locPrimaryZ<605.4) h_PhotonInteractionCase->Fill(0.);
		if(605.4<locPrimaryZ&&locPrimaryZ<624.7) h_PhotonInteractionCase->Fill(1.);
		if(624.7<locPrimaryZ&&locPrimaryZ<690.) h_PhotonInteractionCase->Fill(2.);
		h_PhotonInteractionZ->Fill(locPrimaryZ);
		h_PhotonInteractionMech->Fill(locDMCTrajectoryPoints[1]->mech);
		h2_PhotonInteractionMechvsInteractionZ->Fill(locPrimaryZ,locDMCTrajectoryPoints[1]->mech);
		japp->RootUnLock(); //RELEASE ROOT LOCK!!	
	}
	
	
	
	//Retrieve FCAL/BCAL showers
	// vector<const DFCALTruthShower*> DFCALTruthShowers;
	// locEventLoop->Get(DFCALTruthShowers);
	// vector<const DBCALTruthShower*> DBCALTruthShowers;
	// locEventLoop->Get(DBCALTruthShowers);
	vector<const DFCALShower*> DFCALShowers;
	locEventLoop->Get(DFCALShowers);
	vector<const DBCALShower*> DBCALShowers;
	locEventLoop->Get(DBCALShowers);
	// vector<const DTOFHitMC*> DTOFHitMCs;
	// locEventLoop->Get(DTOFHitMCs);
	// vector<const DTrackCandidate*> DTrackCandidates;
	// locEventLoop->Get(DTrackCandidates);
	// vector<const DNeutralParticleHypothesis*> DNeutralParticleHypotheses;
	// locEventLoop->Get(DNeutralParticleHypotheses);
	// vector<const DNeutralShower*> locNeutralShowers;
	// locEventLoop->Get(locNeutralShowers);
	// vector<const DNeutralParticle*> DNeutralParticles;
	// locEventLoop->Get(DNeutralParticles);
	// vector<const DPhoton*> DPhotons;
	// locEventLoop->Get(DPhotons);
	// vector<const DNeutralShower*> locNeutralShowersPreselect;
	// locEventLoop->Get(locNeutralShowersPreselect,"PreSelect");
	
	// if(DFCALShowers.size() + DBCALShowers.size() > 5) {
		// cout << "Warning: more than five total reconstructed showers in event, which is max array size. Skipping event..." << endl;
		// return NOERROR;
	// }
	
	//Flags
	// bool InitPhotonShowersFCAL = false;
	// bool PhotonConvertsInTOF = false;
	// bool NonPrimaryFCALTruthFlag = false;
	// if(DFCALShowers.size()==1 && DFCALTruthShowers.size() == 1) if(DFCALTruthShowers[0]->primary()) InitPhotonShowersFCAL = true;
	// if(DTOFHitMCs.size()>=1 && DFCALTruthShowers.size() >=1) if(!DFCALTruthShowers[0]->primary()) PhotonConvertsInTOF = true;
	//Non-primary: more than one truth shower or the one truth shower is flagged not-primary
	// if(DFCALTruthShowers.size()>=2) NonPrimaryFCALTruthFlag = true;
	// if(DFCALTruthShowers.size()==1) if(DFCALTruthShowers[0]->primary()!=1) NonPrimaryFCALTruthFlag = true;
	
	DVector3 ThrownPhotonAtFCAL;
	if(locMCThrowns.size()>=1) {
		ThrownPhotonAtFCAL = PropogateThrownNeutralToFCAL(locMCThrowns[0]->position(),locMCThrowns[0]->momentum());
		h_ThrownPhotonE->Fill(locThrownPhotonP4.E());
		h_thrownTheta->Fill( (locThrownPhotonP4.Theta())*180/3.1415) ;
	}
	else {
		cout << "Error, no stuff found, skipping... " << endl;
		return NOERROR;
	}
	
	//Loop over truth showers
	// double TruthShowers_Esum;
	// for(int loc_i=0; loc_i<DFCALTruthShowers.size(); ++loc_i) {
		
	// }

	
	// for(int loc_i=0; loc_i<locNeutralShowers.size(); ++loc_i) {
		// japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		// bool passes_shower_req = false;
		// if( fabs((locNeutralShowers[loc_i]->dSpacetimeVertex.Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) < DELTAPHI_CUTPARM && fabs( (locNeutralShowers[loc_i]->dSpacetimeVertex.Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415)< DELTATHETA_CUTPARM ) passes_shower_req = true;
		// if(passes_shower_req) h_foundE_NeutralShower_DeltaPhiCuts_dist->Fill(locNeutralShowers[loc_i]->dEnergy );
		// japp->RootUnLock(); //RELEASE ROOT LOCK!!
	// }
	
	// for(int loc_i=0; loc_i<locNeutralShowersPreselect.size(); ++loc_i) {
		// japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		// bool passes_shower_req = false;
		// if( fabs((locNeutralShowersPreselect[loc_i]->dSpacetimeVertex.Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) < DELTAPHI_CUTPARM && fabs( (locNeutralShowersPreselect[loc_i]->dSpacetimeVertex.Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415)< DELTATHETA_CUTPARM ) passes_shower_req = true;
		// if(passes_shower_req) h_foundE_NeutralShowerPreselect_DeltaPhiCuts_dist->Fill(locNeutralShowersPreselect[loc_i]->dEnergy );
		// japp->RootUnLock(); //RELEASE ROOT LOCK!!
	// }
	
	// for(int loc_i=0; loc_i<DNeutralParticleHypotheses.size(); ++loc_i) {
		// japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		// const DNeutralShower* locCurrShower = DNeutralParticleHypotheses[loc_i]->Get_NeutralShower();
		// bool passes_shower_req = false;
		// if( fabs((locCurrShower->dSpacetimeVertex.Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) < DELTAPHI_CUTPARM && fabs( (locCurrShower->dSpacetimeVertex.Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415)< DELTATHETA_CUTPARM ) passes_shower_req = true;
		// if(passes_shower_req) h_foundE_NeutralShowerHypothesis_DeltaPhiCuts_dist->Fill(locCurrShower->dEnergy );
		// japp->RootUnLock(); //RELEASE ROOT LOCK!!
	// }
	// for(int loc_i=0; loc_i<DNeutralParticles.size(); ++loc_i) {
		// japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		// const DNeutralShower* locCurrShower = DNeutralParticles[loc_i]->dNeutralShower;
		// bool passes_shower_req = false;
		// if( fabs((locCurrShower->dSpacetimeVertex.Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) < DELTAPHI_CUTPARM && fabs( (locCurrShower->dSpacetimeVertex.Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415)< DELTATHETA_CUTPARM ) passes_shower_req = true;
		// if(passes_shower_req) h_foundE_NeutralParticle_DeltaPhiCuts_dist->Fill(locCurrShower->dEnergy );
		// japp->RootUnLock(); //RELEASE ROOT LOCK!!
	// }



	
	Double_t max_E = 0.;
	for(int loc_i=0; loc_i<DFCALShowers.size(); ++loc_i) {
		if(DFCALShowers[loc_i]->getEnergy() > max_E) max_E = DFCALShowers[loc_i]->getEnergy();
		bool passes_shower_req = false;
		// +/- 3.35 degree default cut in phi: about 5 sigma cut (with 1.2 GeV test photon at 6 degrees, sigma = 0.67 degrees)
		// +/- 0.35 degree default cut in theta: about 5 sigma cut (with 1.2 GeV test photon at 6 degrees, sigma = 0.0682 degrees)
		if( fabs((DFCALShowers[loc_i]->getPosition().Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) < DELTAPHI_CUTPARM && fabs( (DFCALShowers[loc_i]->getPosition().Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415)< DELTATHETA_CUTPARM ) passes_shower_req = true;
		japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
		h_foundE_all_dist->Fill(DFCALShowers[loc_i]->getEnergy()) ;
		if(passes_shower_req) h_foundE_DeltaPhiCuts_dist->Fill(DFCALShowers[loc_i]->getEnergy());
		h_DeltaPhi_all->Fill( (DFCALShowers[loc_i]->getPosition().Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) ;
		h_DeltaTheta_all->Fill( (DFCALShowers[loc_i]->getPosition().Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415) ;
		h2_DeltaThetaDeltaPhi_all->Fill( (DFCALShowers[loc_i]->getPosition().Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415, (DFCALShowers[loc_i]->getPosition().Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415) ;
		
		if(valid_DMCTrajectoryInfo) {
			double locPrimaryZ = locDMCTrajectoryPoints[1]->z;
			if(40.<locPrimaryZ&&locPrimaryZ<605.4) h_foundE_BarrelRegionInteract_dist->Fill(DFCALShowers[loc_i]->getEnergy());
			if(605.4<locPrimaryZ&&locPrimaryZ<624.7) h_foundE_TOFRegionInteract_dist->Fill(DFCALShowers[loc_i]->getEnergy());
			if(624.7<locPrimaryZ&&locPrimaryZ<690.) h_foundE_FCALRegionInteract_dist->Fill(DFCALShowers[loc_i]->getEnergy());
		
			if(passes_shower_req)
				if(40.<locPrimaryZ&&locPrimaryZ<605.4) h_foundE_BarrelRegionInteract_DeltaPhiCuts_dist->Fill(DFCALShowers[loc_i]->getEnergy());
				if(605.4<locPrimaryZ&&locPrimaryZ<624.7) h_foundE_TOFRegionInteract_DeltaPhiCuts_dist->Fill(DFCALShowers[loc_i]->getEnergy());
				if(624.7<locPrimaryZ&&locPrimaryZ<690.) h_foundE_FCALRegionInteract_DeltaPhiCuts_dist->Fill(DFCALShowers[loc_i]->getEnergy());
			}
		japp->RootUnLock(); //RELEASE ROOT LOCK!!
		// if(DFCALTruthShowers.size()==1) cout << "Thrown x: " << ThrownPhotonAtFCAL.X() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Thrown y: " << ThrownPhotonAtFCAL.Y() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Thrown z: " << ThrownPhotonAtFCAL.Z() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Thrown phi: " << ThrownPhotonAtFCAL.Phi() *180/3.1415 << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Found x: " << DFCALShowers[loc_i]->getPosition().X() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Found y: " << DFCALShowers[loc_i]->getPosition().Y() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Found z: " << DFCALShowers[loc_i]->getPosition().Z() << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Found phi: " << DFCALShowers[loc_i]->getPosition().Phi() *180/3.1415 << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Delta phi: " << (DFCALShowers[loc_i]->getPosition().Phi()-ThrownPhotonAtFCAL.Phi())*180/3.1415 << endl << endl;
		// if(DFCALTruthShowers.size()==1) cout << "Delta theta: " << (DFCALShowers[loc_i]->getPosition().Theta()-ThrownPhotonAtFCAL.Theta())*180/3.1415 << endl << endl;
	}
	japp->RootWriteLock(); //ACQUIRE ROOT LOCK!!
	// h_foundE_highestE_dist->Fill(max_E);
	// if(InitPhotonShowersFCAL) h_foundE_primary_dist->Fill(max_E);
	// if(NonPrimaryFCALTruthFlag) h_foundE_nonprimary_dist->Fill(max_E);
	
	// if(DFCALShowers.size()<=1) h_foundE_1orless_all_dist->Fill(max_E);
	// if(DFCALShowers.size()<=1) if(InitPhotonShowersFCAL) h_foundE__1orlessprimary_dist->Fill(max_E);
	// if(DFCALShowers.size()<=1) if(NonPrimaryFCALTruthFlag) h_foundE_1orless_nonprimary_dist->Fill(max_E);
	h_NFCALShowers->Fill(DFCALShowers.size());
	// h_NNeutralShowers->Fill(locNeutralShowers.size());
	// h_NNeutralShowersPreselect->Fill(locNeutralShowersPreselect.size());
	// if(InitPhotonShowersFCAL) h_NFCALShowers_nonprimary->Fill(DFCALShowers.size());
	// if(NonPrimaryFCALTruthFlag) h_NFCALShowers_primary->Fill(DFCALShowers.size());
	japp->RootUnLock(); //RELEASE ROOT LOCK!!
	
	
/* 	dTreeFillData.Fill_Single<Float_t>("thrown_X",ThrownPhotonAtFCAL.X() ); //Propogated to edge of FCAL
	dTreeFillData.Fill_Single<Float_t>("thrown_Y",ThrownPhotonAtFCAL.X() ); //Propogated to edge of FCAL
	dTreeFillData.Fill_Single<Float_t>("thrown_Z",ThrownPhotonAtFCAL.X() ); //Propogated to edge of FCAL
	dTreeFillData.Fill_Single<Float_t>("thrown_E",locThrownPhotonP4.E() ); //Propogated to edge of FCAL
	dTreeFillData.Fill_Single<Int_t>("Num_MCThrown",locMCThrowns.size());
	
	dTreeFillData.Fill_Single<Int_t>("InitPhotonShowersFCAL",InitPhotonShowersFCAL);
	dTreeFillData.Fill_Single<Int_t>("NonPrimaryFCALTruthFlag",NonPrimaryFCALTruthFlag);
	dTreeFillData.Fill_Single<Int_t>("PhotonConvertsInTOF",PhotonConvertsInTOF);
	dTreeFillData.Fill_Single<Int_t>("NFCALShowers",DFCALShowers.size());
	dTreeFillData.Fill_Single<Int_t>("NFCALTruthShowers",DFCALTruthShowers.size());
	dTreeFillData.Fill_Single<Int_t>("NBCALShowers",DBCALShowers.size());
	dTreeFillData.Fill_Single<Int_t>("NBCALTruthShowers",DFCALTruthShowers.size());
	dTreeFillData.Fill_Single<Int_t>("NTrackCandidates",DTrackCandidates.size());
	
	dTreeFillData.Fill_Single<Float_t>("TruthShowers_Esum");
	dTreeFillData.Fill_Single<Float_t>("TruthShowers_nearby_Esum");
	
	dTreeFillData.Fill_Single<Float_t>("Ediff_recon_thr");
	dTreeFillData.Fill_Single<Float_t>("Ediff_truthshow_thr");
	dTreeFillData.Fill_Single<Float_t>("Ediff_neartruthshow_thr");
	
	string locArraySizeString  =  "NumMaxShowers";
	dTreeFillData.Fill_Single<UInt_t>(locArraySizeString);
	locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_X","NumMaxShowers",5);
	locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_Y","NumMaxShowers",5);
	locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_Z","NumMaxShowers",5);
	locBranchRegister.Register_FundamentalArray<Double_t>("RECON_Shower_E","NumMaxShowers",5);
	locBranchRegister.Register_FundamentalArray<Int_t>("IsFCAL","NumMaxShowers",5);
	
	dTreeFillData.Fill_Single<Float_t>("thrownE",locThrownPhotonP4.E());
	
	//FILL TTREE
	dTreeInterface->Fill(dTreeFillData);
 */	

 
	
 
	return NOERROR;
}

int DEventProcessor_photon_gun_hists::Get_FileNumber(JEventLoop* locEventLoop) const
{
	//Assume that the file name is in the format: *_X.ext, where:
		//X is the file number (a string of numbers of any length)
		//ext is the file extension (probably .evio or .hddm)

	//get the event source
	JEventSource* locEventSource = locEventLoop->GetJEvent().GetJEventSource();
	if(locEventSource == NULL)
		return -1;

	//get the source file name (strip the path)
	string locSourceFileName = locEventSource->GetSourceName();

	//find the last "_" & "." indices
	size_t locUnderscoreIndex = locSourceFileName.rfind("_");
	size_t locDotIndex = locSourceFileName.rfind(".");
	if((locUnderscoreIndex == string::npos) || (locDotIndex == string::npos))
		return -1;

	size_t locNumberLength = locDotIndex - locUnderscoreIndex - 1;
	string locFileNumberString = locSourceFileName.substr(locUnderscoreIndex + 1, locNumberLength);

	int locFileNumber = -1;
	istringstream locFileNumberStream(locFileNumberString);
	locFileNumberStream >> locFileNumber;

	return locFileNumber;
}

//------------------
// erun
//------------------
jerror_t DEventProcessor_photon_gun_hists::erun(void)
{
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t DEventProcessor_photon_gun_hists::fini(void)
{
	// Called before program exit after event processing is finished.
	if(dEventStoreSkimStream.is_open())
		dEventStoreSkimStream.close();
	
	// delete dTreeInterface; //saves trees to file, closes file
	
	return NOERROR;
}

//Convert thrown photon coordinates at primary vertex in target to coordinates at FCAL face 
DVector3 DEventProcessor_photon_gun_hists::PropogateThrownNeutralToFCAL(const DVector3 x4_init, const DVector3 p4_init) {
	
	//tan(theta1) = delta X / delta Z = Px / Pz
	//tan(theta1) = delta X / delta Z = Py / Pz
	
	double DeltaZ = fcalFrontFaceZ - x4_init.Z();
	
	double x_pos_AtFCAL = x4_init.X() + DeltaZ*(p4_init.Px()/p4_init.Pz());
	double y_pos_AtFCAL = x4_init.Y() + DeltaZ*(p4_init.Py()/p4_init.Pz());
	
	return DVector3(x_pos_AtFCAL,y_pos_AtFCAL,fcalFrontFaceZ);
}
