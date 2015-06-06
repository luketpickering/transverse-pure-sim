#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TTree.h"

#include "CLITools.hxx"
#include "PureGenUtils.hxx"

#include "GiRooTracker.hxx"

namespace {

std::string InpFName;

int nuType;
int TargetA;
int TargetZ;
long MaxEntries;

int Verbosity = 0;

  int GiBUUToPDG(int GiBUUCode, double GiBUUCharge){
    //https://gibuu.hepforge.org/trac/wiki/ParticleIDs
    switch(GiBUUCode){
      case 1:{
        return (GiBUUCharge>0)?2212:2112;
      }
      case 101:{
        if(GiBUUCharge){ return(GiBUUCharge>0)?211:-211; }
        return 111;
      }
      case 901:{
        return (GiBUUCharge<0)?11:-11;
      }
      case 902:{
        return (GiBUUCharge<0)?13:-13;
      }
      case 911:{
        return 12;
      }
      case 912:{
        return 14;
      }
      case 999:{
        return 22;
      }
      default:{
        return 0;
      }
    }
  }

  int GiBUU2NeutReacCode(int GiBUUCode){
    //1=QE, 2-31=res ID, 32,33=1pi, 34=DIS, 35,36=2p2h, 37=2pi
    //From https://gibuu.hepforge.org/trac/wiki/LesHouches
    if(GiBUUCode==1) { return 1; } // QES

    //How best to translate this to a specific NEUT code.
    if(GiBUUCode >= 2 && GiBUUCode <= 31){ return 11; } //CCResonance
    if(GiBUUCode == 34){ return 26; } //DIS
    if((GiBUUCode == 35) || (GiBUUCode == 36)){ return 2; } // MEC/2p-2h
    if(GiBUUCode == 37){ return 21; } //CCCoh?
    if(Verbosity>=1){
      std::cout << "[WARN]: Missed a GiBUU reaction code: " << GiBUUCode
        << std::endl;
    }
    return 0;
  }
}

int GiBUUToStdHep(){
  std::ifstream ifs(InpFName);
  std::string line;
  long ctr = 0;

  TFile* outFile = new TFile("GiBUURooTracker.root","CREATE");
  if(!outFile->IsOpen()){
    std::cout << "Couldn't open output file." << std::endl;
    return 2;
  }

  TTree* rooTrackerTree = new TTree("giRooTracker","GiBUU StdHepVariables");
  GiRooTracker* outRooTracker = new GiRooTracker();
  outRooTracker->AddBranches(rooTrackerTree);

  int LastEvNum = 0;
  while(std::getline(ifs,line)){
    if(!ctr){ctr++;continue;} //skip the table header
    std::istringstream iss(line);

    int Run, EvNum, ID, History, Prodid;
    float Charge,PerWeight,Pos1,Pos2,Pos3,Mom0,Mom1,Mom2,Mom3,Enu;

    iss >> Run >> EvNum >> ID >> Charge >> PerWeight >> Pos1 >>
      Pos2 >> Pos3 >> Mom0 >> Mom1 >> Mom2 >> Mom3 >> History >> Prodid >> Enu;

    if(EvNum != LastEvNum){
      if(LastEvNum){
        rooTrackerTree->Fill();
        outRooTracker->Reset();
      }
      if(!(EvNum%1000)){ std::cout << "On Ev: " << EvNum << std::endl; }
      if(MaxEntries == EvNum){
        std::cout << "Finishing after " << EvNum << " entries." << std::endl;
        break;
      }
      outRooTracker->GiBUU2NeutCode = GiBUU2NeutReacCode(Prodid);
      outRooTracker->EvtNum = EvNum;

      //neutrino
      outRooTracker->StdHepPdg[0] = nuType;
      outRooTracker->StdHepStatus[0] = -1;
      outRooTracker->StdHepP4[0][GiRooTracker::kStdHepIdxPx] = 0;
      outRooTracker->StdHepP4[0][GiRooTracker::kStdHepIdxPy] = 0;
      outRooTracker->StdHepP4[0][GiRooTracker::kStdHepIdxPz] = Enu;
      outRooTracker->StdHepP4[0][GiRooTracker::kStdHepIdxE] = Enu;

      //target
      outRooTracker->StdHepPdg[1] = PGUtils::MakeNuclearPDG(TargetZ,TargetA);
      outRooTracker->StdHepStatus[1] = -1;
      outRooTracker->StdHepP4[1][GiRooTracker::kStdHepIdxPx] = 0;
      outRooTracker->StdHepP4[1][GiRooTracker::kStdHepIdxPy] = 0;
      outRooTracker->StdHepP4[1][GiRooTracker::kStdHepIdxPz] = 0;
      outRooTracker->StdHepP4[1][GiRooTracker::kStdHepIdxE] = TargetA;

      outRooTracker->StdHepN = 2;
      LastEvNum = EvNum;
    }

    outRooTracker->StdHepPdg[outRooTracker->StdHepN] = GiBUUToPDG(ID,Charge);
    outRooTracker->StdHepStatus[outRooTracker->StdHepN] = 1;
    outRooTracker->StdHepP4[outRooTracker->StdHepN]\
      [GiRooTracker::kStdHepIdxPx] = Mom1;
    outRooTracker->StdHepP4[outRooTracker->StdHepN]\
      [GiRooTracker::kStdHepIdxPy] = Mom2;
    outRooTracker->StdHepP4[outRooTracker->StdHepN]\
      [GiRooTracker::kStdHepIdxPz] = Mom3;
    outRooTracker->StdHepP4[outRooTracker->StdHepN]\
      [GiRooTracker::kStdHepIdxE] = Mom0;
    outRooTracker->StdHepN++;

    if(Verbosity>2){
      std::cout << "Line: " << line << std::endl;
      std::cout << "Copy: " << Run << " " <<  EvNum<< " " <<  ID << " "
        << Charge << " " << PerWeight << " " << Pos1 << " " <<
        Pos2 << " " << Pos3 << " " << Mom0 << " " << Mom1 << " " << Mom2
        << " " << Mom3 << " " <<  History << " " <<  Prodid << " " <<  Enu
        << std::endl;
    }
    ctr++;
  }
  rooTrackerTree->Fill();
  rooTrackerTree->Write();
  outFile->Write();
  outFile->Close();
  delete outRooTracker;
  ifs.close();
  return 0;
}

void SetOpts(){
  CLIArgs::OptSpec.emplace_back("-h","--help", false,
    [&] (std::string const &opt) -> bool {
      CLIArgs::SayRunLike();
      exit(0);
    });

  CLIArgs::OptSpec.emplace_back("-i", "--input-file", true,
    [&] (std::string const &opt) -> bool {
      std::cout << "\tReading GiBUU file : " << opt << std::endl;
      InpFName = opt;
      return true;
    }, true,[](){},"<File Name>");

  CLIArgs::OptSpec.emplace_back("-u", "--nu-pdg", true,
    [&] (std::string const &opt) -> bool {
      int vbhold;
      if(PGUtils::str2int(vbhold,opt.c_str()) == PGUtils::STRINT_SUCCESS){
        std::cout << "Nu PDG: " << vbhold << std::endl;
        nuType = vbhold;
        return true;
      }
      return false;
    }, true,[](){},"<Neutrino PDG identifier>");

  CLIArgs::OptSpec.emplace_back("-a", "--target-a", true,
    [&] (std::string const &opt) -> bool {
      int vbhold;
      if(PGUtils::str2int(vbhold,opt.c_str()) == PGUtils::STRINT_SUCCESS){
        std::cout << "Target A: " << vbhold << std::endl;
        TargetA = vbhold;
        return true;
      }
      return false;
    }, true,[](){},"<Target A>");

  CLIArgs::OptSpec.emplace_back("-z", "--target-z", true,
    [&] (std::string const &opt) -> bool {
      int vbhold;
      if(PGUtils::str2int(vbhold,opt.c_str()) == PGUtils::STRINT_SUCCESS){
        std::cout << "Target Z: " << vbhold << std::endl;
        TargetZ = vbhold;
        return true;
      }
      return false;
    }, true,[](){},"<Target Z>");

  CLIArgs::OptSpec.emplace_back("-v", "--verbosity", true,
    [&] (std::string const &opt) -> bool {
      int vbhold;
      if(PGUtils::str2int(vbhold,opt.c_str()) == PGUtils::STRINT_SUCCESS){
        std::cout << "Verbosity: " << vbhold << std::endl;
        Verbosity = vbhold;
        return true;
      }
      return false;
    }, false,
    [&](){Verbosity = 0;}, "<0-4>{default==0}");

  CLIArgs::OptSpec.emplace_back("-n", "--nevs", true,
    [&] (std::string const &opt) -> bool {
      int vbhold;
      if(PGUtils::str2int(vbhold,opt.c_str()) == PGUtils::STRINT_SUCCESS){
        std::cout << "Number of events: " << vbhold << std::endl;
        MaxEntries = vbhold;
        return true;
      }
      return false;
    }, false,
    [&](){MaxEntries = -1;}, "<Num Entries [<-1>: means all]> [default==-1]");
}

int main(int argc, char const *argv[]){

  SetOpts();
  CLIArgs::AddArguments(argc,argv);
  if(!CLIArgs::GetOpts()){
    CLIArgs::SayRunLike();
    return 1;
  }

  return GiBUUToStdHep();
}
