/*
 ==============================================================================
 
 This file is part of the iPlug 2 library. Copyright (C) the iPlug 2 developers. 
 
 See LICENSE.txt for  more info.
 
 ==============================================================================
*/

#ifndef CUSTOM_BUSTYPE_FUNC
static uint64_t GetAPIBusTypeForChannelIOConfig(int configIdx, ERoute dir, int busIdx, IOConfig* pConfig, WDL_TypedBuf<uint64_t>* APIBusTypes = nullptr)
{
  assert(pConfig != nullptr);
  assert(busIdx >= 0 && busIdx < pConfig->NBuses(dir));

  int numChans = pConfig->GetBusInfo(dir, busIdx)->mNChans;

  switch (numChans)
  {
    case 0: APIBusTypes->Add(kAudioChannelLayoutTag_UseChannelDescriptions | 0);
      return kAudioChannelLayoutTag_UseChannelDescriptions | 0;
    case 1:
      APIBusTypes->Add(kAudioChannelLayoutTag_Mono);
      break;
    case 2:
//      APIBusTypes->Add(kAudioChannelLayoutTag_Binaural);
      APIBusTypes->Add(kAudioChannelLayoutTag_Stereo);
      break;
    case 3:
      APIBusTypes->Add(kAudioChannelLayoutTag_ITU_3_0 | 3);
      break;
    case 4:
      // by default support any 4 channel layout
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_4);
      APIBusTypes->Add(kAudioChannelLayoutTag_Ambisonic_B_Format);
      APIBusTypes->Add(kAudioChannelLayoutTag_HOA_ACN_SN3D | 4);
      break;
    case 5:
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_5_0);
      break;
    case 6:
      // by default support any 6 channel layout
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_5_1);
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_6_0);
      break;
    case 7:
      // by default support any 7 channel layout
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_6_1);
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_7_0);
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_7_1_Front);
      break;
    case 8:
      // by default support any 8 channel layout
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_7_1);
      APIBusTypes->Add(kAudioChannelLayoutTag_AudioUnit_7_1_Front);
      break;
    case 9:
    case 16: // 2nd and 3rd order ambisonics
      APIBusTypes->Add(kAudioChannelLayoutTag_HOA_ACN_SN3D | numChans);
      break;
    default:
      APIBusTypes->Add(kAudioChannelLayoutTag_DiscreteInOrder | numChans);
      break;
  }
  return true;
}
#else
extern uint64_t GetAPIBusTypeForChannelIOConfig(int configIdx, ERoutingDir dir, int busIdx, IOConfig* pConfig, WDL_TypedBuf<uint64_t>* APIBusTypes = nullptr);
#endif //CUSTOM_BUSTYPE_FUNC