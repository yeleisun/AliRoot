/* $Id: AliTriggerAnalysis.h 35782 2009-10-22 11:54:31Z jgrosseo $ */

#ifndef ALITRIGGERANALYSIS_H
#define ALITRIGGERANALYSIS_H

#include <TObject.h>

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

//-------------------------------------------------------------------------
//                      Implementation of   Class AliTriggerAnalysis
//   This class provides function to check if events have been triggered based on the data in the ESD
//   The trigger bits, trigger class inputs and only the data (offline trigger) can be used
//   Origin: Jan Fiete Grosse-Oetringhaus, CERN
//-------------------------------------------------------------------------

class AliVEvent;
class AliESDEvent;
class AliESDtrackCuts;
class TH1F;
class TH2F;
class TCollection;
class TMap;

class AliTriggerAnalysis : public TObject{
public:
  enum Trigger { kAcceptAll = 1, kMB1 = 2, kMB2, kMB3, kSPDGFO, kSPDGFOBits, kV0A, kV0C, kV0OR, kV0AND, 
    kV0ABG, kV0CBG, kZDC, kZDCA, kZDCC, kZNA, kZNC, kZNABG, kZNCBG, kFMDA, kFMDC, kFPANY, kNSD1, kMB1Prime, 
    kSPDGFOL0, kSPDGFOL1, kZDCTDCA, kZDCTDCC, kZDCTime, kCTPV0A, kCTPV0C, kTPCLaserWarmUp, kSPDClsVsTrkBG,
    kCentral,kSemiCentral, kT0, kT0BG, kT0Pileup, kEMCAL, kTPCHVdip,
    kTRDHCO, kTRDHJT, kTRDHSE, kTRDHQU, kTRDHEE,
    kEmcalL0,kEmcalL1GammaHigh, kEmcalL1GammaLow, kEmcalL1JetHigh, kEmcalL1JetLow,
    kIncompleteEvent,
    kStartOfFlags = 0x0100, kOfflineFlag = 0x8000, kOneParticle = 0x10000, kOneTrack = 0x20000}; // MB1, MB2, MB3 definition from ALICE-INT-2005-025
  enum AliceSide { kASide = 1, kCSide, kCentralBarrel };
  enum V0Decision { kV0Invalid = -1, kV0Empty = 0, kV0BB, kV0BG, kV0Fake };
  enum T0Decision { kT0Invalid = -1, kT0Empty = 0, kT0BB, kT0DecBG, kT0DecPileup };
  static const char* GetTriggerName(Trigger trigger);

  AliTriggerAnalysis();
  virtual ~AliTriggerAnalysis();
  void EnableHistograms(Bool_t isLowFlux = kFALSE);
  void SetAnalyzeMC(Bool_t flag = kTRUE) { fMC = flag; }
  
  Bool_t IsTriggerFired(const AliESDEvent* aEsd, Trigger trigger);
  Int_t EvaluateTrigger(const AliESDEvent* aEsd, Trigger trigger);
  Bool_t IsTriggerBitFired(const AliESDEvent* aEsd, Trigger trigger) const; // obsolete
  Bool_t IsTriggerBitFired(const AliESDEvent* aEsd, ULong64_t tclass) const;
  Bool_t IsOfflineTriggerFired(const AliESDEvent* aEsd, Trigger trigger);
  
  // some "raw" trigger functions
  V0Decision V0Trigger(const AliESDEvent* aEsd, AliceSide side, Bool_t online, Bool_t fillHists = kFALSE);
  T0Decision T0Trigger(const AliESDEvent* aEsd, Bool_t online, Bool_t fillHists = kFALSE);
  Bool_t SPDGFOTrigger(const AliESDEvent* aEsd, Int_t origin) { return SPDFiredChips(aEsd, origin) >= fSPDGFOThreshold; }
  Bool_t ZDCTrigger   (const AliESDEvent* aEsd, AliceSide side) const;
  Bool_t ZDCTDCTrigger(const AliESDEvent* aEsd, AliceSide side, Bool_t useZN=kTRUE, Bool_t useZP=kFALSE, Bool_t fillHists=kFALSE) const;
  Bool_t ZDCTimeTrigger(const AliESDEvent *aEsd, Bool_t fillHists=kFALSE) const;
  Bool_t ZDCTimeBGTrigger(const AliESDEvent *aEsd, AliceSide side) const;
  Bool_t FMDTrigger(const AliESDEvent* aEsd, AliceSide side);
  Bool_t TRDTrigger(const AliESDEvent* esd, Trigger trigger);
  Bool_t EMCALCellsTrigger(const AliESDEvent *aEsd);
  Bool_t EMCALTrigger(const AliVEvent* event, Trigger trigger);

  Int_t SSDClusters(const AliVEvent* event);
  Int_t SPDFiredChips(const AliESDEvent* aEsd, Int_t origin, Bool_t fillHists = kFALSE, Int_t layer = 0);
  Bool_t IsSPDClusterVsTrackletBG(const AliVEvent* event, Bool_t fillHists = kFALSE);
  Bool_t IsLaserWarmUpTPCEvent(const AliESDEvent* esd);
  Bool_t IsHVdipTPCEvent(const AliESDEvent* esd);
  Bool_t IsIncompleteEvent(const AliESDEvent* esd);
  
  void FillHistograms(const AliESDEvent* aEsd);
  void FillTriggerClasses(const AliESDEvent* aEsd);
  
  void SetSPDGFOThreshhold(Int_t t) { fSPDGFOThreshold = t; }
  void SetSPDGFOEfficiency(TH1F* hist) { fSPDGFOEfficiency = hist; }
  void SetSPDClustersVsTrackletsParameters(Float_t a, Float_t b) { fASPDCvsTCut = a; fBSPDCvsTCut =b;}
  void SetV0TimeOffset(Float_t offset) { fV0TimeOffset = offset; }
  void SetV0AdcThr(Float_t thr) { fV0AdcThr = thr; }
  void SetV0HwPars(Float_t thr, Float_t winLow, Float_t winHigh) { fV0HwAdcThr = thr; fV0HwWinLow = winLow; fV0HwWinHigh = winHigh; }
  void SetFMDThreshold(Float_t low, Float_t hit) { fFMDLowCut = low; fFMDHitCut = hit; }
  void SetDoFMD(Bool_t flag = kTRUE) {fDoFMD = flag;}
  void SetZDCCutParams(Float_t refSum, Float_t refDelta, Float_t sigmaSum, Float_t sigmaDelta) { fZDCCutRefSum = refSum; fZDCCutRefDelta = refDelta; fZDCCutSigmaSum = sigmaSum; fZDCCutSigmaDelta = sigmaDelta; }
  void SetCorrZDCCutParams(Float_t refSum, Float_t refDelta, Float_t sigmaSum, Float_t sigmaDelta) { fZDCCutRefSumCorr = refSum; fZDCCutRefDeltaCorr = refDelta; fZDCCutSigmaSumCorr = sigmaSum; fZDCCutSigmaDeltaCorr = sigmaDelta; }
  void SetZNCorrCutParams(Float_t znaTimeCorrMin, Float_t znaTimeCorrMax, Float_t zncTimeCorrMin, Float_t zncTimeCorrMax)
  { fZDCCutZNATimeCorrMin = znaTimeCorrMin; fZDCCutZNATimeCorrMax = znaTimeCorrMax; 
  fZDCCutZNCTimeCorrMin = zncTimeCorrMin; fZDCCutZNCTimeCorrMax = zncTimeCorrMax; }
  
  void SetTRDTriggerParameters(Float_t ptHSE, UChar_t pidHSE, Float_t ptHQU, UChar_t pidHQU, Float_t ptHEE, UChar_t pidHEE, UChar_t minSectorHEE, UChar_t maxSectorHEE, Float_t ptHJT, UChar_t nHJT) {
    fTRDptHSE = ptHSE; fTRDpidHSE = pidHSE;
    fTRDptHQU = ptHQU; fTRDpidHQU = pidHQU;
    fTRDptHEE = ptHEE; fTRDpidHEE = pidHEE;
    fTRDminSectorHEE = minSectorHEE; fTRDmaxSectorHEE = maxSectorHEE;
    fTRDptHJT = ptHJT; fTRDnHJT = nHJT;
  }
  
  Int_t GetSPDGFOThreshhold() const { return fSPDGFOThreshold; }
  Float_t GetV0TimeOffset() const { return fV0TimeOffset; }
  Float_t GetV0AdcThr()     const { return fV0AdcThr; }
  Float_t GetFMDLowThreshold() const { return fFMDLowCut; }
  Float_t GetFMDHitThreshold() const { return fFMDHitCut; }
  TMap * GetTriggerClasses() const { return fTriggerClasses;}
  
  
  virtual Long64_t Merge(TCollection* list);
  void SaveHistograms() const;
  
  void PrintTriggerClasses() const;
  void SetESDTrackCuts(AliESDtrackCuts* cuts) { fEsdTrackCuts = cuts;}
  AliESDtrackCuts* GetESDTrackCuts() const  {return fEsdTrackCuts;}
  
  void SetTPCOnly(Bool_t bTPCOnly) {fTPCOnly = bTPCOnly;}
  Bool_t GetTPCOnly() const {return fTPCOnly;}
  
protected:
  Float_t V0CorrectLeadingTime(Int_t i, Float_t time, Float_t adc, Int_t runNumber) const;
  Float_t V0LeadingTimeWeight(Float_t adc) const;
  Int_t FMDHitCombinations(const AliESDEvent* aEsd, AliceSide side, Bool_t fillHists = kFALSE);
  
  Int_t fSPDGFOThreshold;         // number of chips to accept a SPD GF0 trigger
  TH1F* fSPDGFOEfficiency;         // SPD FASTOR efficiency - is applied in SPDFiredChips. Histogram contains efficiency as function of chip number (bin 1..400: first layer; 401..1200: second layer)
  
  Float_t fV0TimeOffset;          // time offset applied to the times read from the V0 (in ns)
  Float_t fV0AdcThr;              // thresholds applied on V0 ADC data
  Float_t fV0HwAdcThr;            // online V0 trigger - thresholds applied on ADC data 
  Float_t fV0HwWinLow;            // online V0 trigger - lower edge of time window
  Float_t fV0HwWinHigh;           // online V0 trigger - upper edge of time window
  
  Float_t fZDCCutRefSum;          // ZDC time cut configuration
  Float_t fZDCCutRefDelta;        // ZDC time cut configuration
  Float_t fZDCCutSigmaSum;        // ZDC time cut configuration
  Float_t fZDCCutSigmaDelta;      // ZDC time cut configuration
  
  Float_t fZDCCutRefSumCorr;      // Corrected ZDC time cut configuration
  Float_t fZDCCutRefDeltaCorr;    // Corrected ZDC time cut configuration
  Float_t fZDCCutSigmaSumCorr;    // Corrected ZDC time cut configuration
  Float_t fZDCCutSigmaDeltaCorr;  // Corrected ZDC time cut configuration
  
  Float_t fZDCCutZNATimeCorrMin;  // Corrected ZNA time cut configuration
  Float_t fZDCCutZNATimeCorrMax;  // Corrected ZNA time cut configuration
  Float_t fZDCCutZNCTimeCorrMin;  // Corrected ZNA time cut configuration
  Float_t fZDCCutZNCTimeCorrMax;  // Corrected ZNA time cut configuration
  
  Float_t fASPDCvsTCut; // constant for the linear cut in SPD clusters vs tracklets
  Float_t fBSPDCvsTCut; // slope for the linear cut in SPD  clusters vs tracklets
  
  // Variables for the TRD triggers
  Float_t fTRDptHSE;            // pt threshold for HSE trigger
  UChar_t fTRDpidHSE;           // PID threshold for HSE trigger
  Float_t fTRDptHQU;            // pt threshold for HQU trigger
  UChar_t fTRDpidHQU;           // PID threshold for HQU trigger
  Float_t fTRDptHEE;            // pt threshold for HEE trigger
  UChar_t fTRDpidHEE;           // PID threshold for HEE trigger
  UChar_t fTRDminSectorHEE;     // min sector for HEE trigger
  UChar_t fTRDmaxSectorHEE;     // max sector for HEE trigger
  Float_t fTRDptHJT;            // pt threshold for HJT trigger
  UChar_t fTRDnHJT;             // no of track threshold for HJT trigger
  
  Bool_t  fDoFMD;               // If false, skips the FMD (physics selection runs much faster)
  Float_t fFMDLowCut;           // 
  Float_t fFMDHitCut;           // 
  
  TH2F* fHistBitsSPD;        // offline trigger bits (calculated from clusters) vs hardware trigger bits
  TH1F* fHistFiredBitsSPD;   // fired hardware bits
  TH2F* fHistSPDClsVsTrk;    // histogram of clusters vs tracklet BG cut
  TH1F* fHistV0A;            // histograms that histogram the criterion the cut is applied on: bb triggers
  TH1F* fHistV0C;            // histograms that histogram the criterion the cut is applied on: bb triggers
  TH1F* fHistZDC;            //histograms that histogram the criterion the cut is applied on: fired bits (6 bins)
  TH1F* fHistTDCZDC;         // histograms that histogram the criterion the cut is applied on: TDC bits (32 bins)
  TH2F* fHistTimeZDC;        // histograms that histogram the criterion the cut is applied on: ZDC TDC timing
  TH2F* fHistTimeCorrZDC;    // histograms that histogram the criterion the cut is applied on: ZDC Corrected TDC timing
  TH1F* fHistFMDA;           // histograms that histogram the criterion the cut is applied on: number of hit combination above threshold
  TH1F* fHistFMDC;           // histograms that histogram the criterion the cut is applied on: number of hit combination above threshold
  TH1F* fHistFMDSingle;      // histograms that histogram the criterion the cut is applied on: single mult value (more than one entry per event)
  TH1F* fHistFMDSum;         // histograms that histogram the criterion the cut is applied on: summed mult value (more than one entry per event)
  TH1F* fHistT0;             // histograms that histogram the criterion the cut is applied on: bb triggers
  TMap* fTriggerClasses;    // counts the active trigger classes (uses the full string)
  
  Bool_t fMC;              // flag if MC is analyzed
  AliESDtrackCuts* fEsdTrackCuts;  //Track Cuts to select ESD tracks
  
  Bool_t fTPCOnly;         // flag to set whether TPC only tracks have to be used for the offline trigger 
  
  ClassDef(AliTriggerAnalysis, 23)
  
private:
  AliTriggerAnalysis(const AliTriggerAnalysis&);
  AliTriggerAnalysis& operator=(const AliTriggerAnalysis&);
};

#endif