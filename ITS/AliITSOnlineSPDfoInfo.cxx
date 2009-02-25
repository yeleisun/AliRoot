/**************************************************************************
 * Copyright(c) 2008-2010, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

////////////////////////////////////////////////////////////////
// Author: A. Mastroserio                                     // 
// This class is used within the detector algorithm framework //
// to collect information on how the scan was arranged.       //
////////////////////////////////////////////////////////////////

#include "AliITSOnlineSPDfoInfo.h"

ClassImp(AliITSOnlineSPDfoInfo)
  
//_____________________________________________________________________
AliITSOnlineSPDfoInfo::AliITSOnlineSPDfoInfo(): 
 fRunNumber(0), fRouter(999), fNumTriggers(0),
 fDBversion(0), fNumDACindex(0), fDACindex(0)
{}
//_____________________________________________________________________
AliITSOnlineSPDfoInfo::~AliITSOnlineSPDfoInfo() 
{}
//_____________________________________________________________________
void AliITSOnlineSPDfoInfo::ClearThis() {
  // reset all values for this object
  fRunNumber=0;
  fRouter=999;
  fNumTriggers=0;
  fDBversion=0;
  fNumDACindex=0;
  fDACindex.Reset();
}
//_____________________________________________________________________
void AliITSOnlineSPDfoInfo::AddDACindex(Short_t index) {
  // add a new DAC index, allocate space for TArrayS
  fNumDACindex++;
  fDACindex.Set(fNumDACindex);
  fDACindex.AddAt(index, fNumDACindex-1);
}
//_____________________________________________________________________
Short_t AliITSOnlineSPDfoInfo::GetDACindex(UShort_t id) const {
  // returns the DAC index at position id of TArrayS
  if (id>=fNumDACindex) return -1;
  else                  return fDACindex.At(id);
}
