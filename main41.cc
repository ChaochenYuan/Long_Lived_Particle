// main41.cc is a part of the PYTHIA event generator.
// Copyright (C) 2021 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Authors: Mikhail Kirsanov <Mikhail.Kirsanov@cern.ch>.

// Keywords: basic usage; hepmc;

// This program illustrates how HepMC can be interfaced to Pythia8.
// It studies the charged multiplicity distribution at the LHC.
// HepMC events are output to the hepmcout41.dat file.

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"
using namespace Pythia8;
int main() {
  // Interface for conversion from Pythia8::Event to HepMC event.
  HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io("test.dat", std::ios::out);
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  pythia.readString("Random:setSeed=on");
  pythia.readString("Random:seed=111");
  pythia.readString("Beams:eCM = 14000.");
  pythia.readString("HiddenValley:ffbar2Zv = on");
  pythia.readString("HiddenValley:FSR = on");
  pythia.readString("HiddenValley:fragment = on");
  pythia.readString("HiddenValley:alphaOrder = 1");
  pythia.readString("HiddenValley:alphaFSR = 0.7");
  pythia.readString("HiddenValley:Ngauge = 3");
  pythia.readString("HiddenValley:Lambda=5");
  pythia.readString("HiddenValley:pTminFSR =5.5");
  pythia.readString("HiddenValley:nFlav = 1");
  pythia.readString("HiddenValley:probVector = 0");
  pythia.readString("4900023:m0 = 200");
  pythia.readString("4900023:onMode = off");
  pythia.readString("4900023:onIfAny = 4900101");
  pythia.readString("4900023:mWidth = 0.01");
  pythia.readString("4900101:m0 = 1");
  pythia.readString("4900111:m0 = 5");
  pythia.readString("4900113:m0 = 5");
  pythia.readString("4900111:tau0 = 1000");
  pythia.readString("4900111:oneChannel 1 1 0 13 -13");
  pythia.readString("PartonLevel:MPI = off");
  pythia.init();
  //int nAbort = pythia.mode("Main:timesAllowErrors");
  //Hist mult("charged multiplicity", 100, -0.5, 799.5);
  // Begin event loop. Generate event. Skip if error.
  //int iAbort = 0;
  for (int iEvent = 0; iEvent < 3000; ++iEvent) {
   cout<< iEvent;
   if (iEvent==1000){
    pythia.event.list();
   }
   if (iEvent==2985){
    pythia.event.list();
   }
    if (!pythia.next()) continue;
//{
     // if (++iAbort < nAbort) continue;
//			cout << " Event generation aborted prematurely, owing to error!\n";
//			break;
//    }
    // Find number of all final charged particles and fill histogram.
    // Construct new empty HepMC event and fill it.
    // Units will be as chosen for HepMC build; but can be changed
    // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    ToHepMC.fill_next_event( pythia, hepmcevt );
    // Write the HepMC event to file. Done with it.
    ascii_io << hepmcevt;
    delete hepmcevt;
    cout<<"done"<<" ";
  // End of event loop. Statistics. Histogram.
  }
  pythia.stat();
  // Done.
  return 0;
}
