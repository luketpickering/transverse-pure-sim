#include "PureGenUtils.hxx"

#include "GiRooTracker.hxx"

GiRooTracker::GiRooTracker(){
  GiStdHepNPmaxstr = PGUtils::int2str(kGiStdHepNPmax);
  StdHepPdg = new Int_t[kGiStdHepNPmax];
  StdHepStatus = new Int_t[kGiStdHepNPmax];
  Reset();
}
void GiRooTracker::Reset(){
  GiBUU2NeutCode = 0;
  EvtNum = 0;
  StdHepN = 0;

  PGUtils::ClearPointer(StdHepPdg,kGiStdHepNPmax);
  PGUtils::ClearPointer(StdHepStatus,kGiStdHepNPmax);
  PGUtils::ClearArray2D(StdHepP4);
}

void GiRooTracker::AddBranches(TTree* &tree){
  tree->Branch("GiBUU2NeutCode", &GiBUU2NeutCode, "GiBUU2NeutCode/I");

  tree->Branch("EvtNum", &EvtNum,"EvtNum/I");

  tree->Branch("StdHepN", &StdHepN,"StdHepN/I");

  tree->Branch("StdHepPdg", StdHepPdg,"StdHepPdg[StdHepN]/I");

  tree->Branch("StdHepStatus", StdHepStatus,"StdHepStatus[StdHepN]/I");

  tree->Branch("StdHepP4", StdHepP4,
    ("StdHepP4["+GiStdHepNPmaxstr+"][4]/D").c_str());
}
