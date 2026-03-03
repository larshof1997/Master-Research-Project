  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 11;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_open_loop_P)
    ;%
      section.nData     = 23;
      section.data(23)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.A1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.A2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_P.B1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 32;
	
	  ;% q_2dsfl_open_loop_P.B2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 36;
	
	  ;% q_2dsfl_open_loop_P.C1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 40;
	
	  ;% q_2dsfl_open_loop_P.C2
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 56;
	
	  ;% q_2dsfl_open_loop_P.DTH1_LIM_ENABLE
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 72;
	
	  ;% q_2dsfl_open_loop_P.DTH2_LIM_ENABLE
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 73;
	
	  ;% q_2dsfl_open_loop_P.DTH2_MAX
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 74;
	
	  ;% q_2dsfl_open_loop_P.DTH2_MIN
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 75;
	
	  ;% q_2dsfl_open_loop_P.K1_defl_b
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 76;
	
	  ;% q_2dsfl_open_loop_P.K1_strain_b
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 77;
	
	  ;% q_2dsfl_open_loop_P.K2_defl_b
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 78;
	
	  ;% q_2dsfl_open_loop_P.K2_strain_b
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 79;
	
	  ;% q_2dsfl_open_loop_P.KE_D1
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 80;
	
	  ;% q_2dsfl_open_loop_P.KE_D2
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 81;
	
	  ;% q_2dsfl_open_loop_P.LIMIT_SWITCHES_ENABLE
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 82;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_end_time
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 83;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_end_time_n
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 84;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_start_time
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 85;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_start_time_k
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 86;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_switch_id
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 87;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_switch_id_c
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 88;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.HILReadEncoderTimebase_clock
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.HILReadEncoderTimebase_channels
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.HILReadAnalog_channels
	  section.data(2).logicalSrcIdx = 25;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.HILWriteAnalog_channels
	  section.data(3).logicalSrcIdx = 26;
	  section.data(3).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.HILReadEncoder_channels
	  section.data(4).logicalSrcIdx = 27;
	  section.data(4).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.HILReadAnalog_channels_g
	  section.data(5).logicalSrcIdx = 28;
	  section.data(5).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.HILWriteAnalog_channels_j
	  section.data(6).logicalSrcIdx = 29;
	  section.data(6).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_P.HILWriteDigital_channels
	  section.data(7).logicalSrcIdx = 30;
	  section.data(7).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.HILReadDigital_channels
	  section.data(8).logicalSrcIdx = 31;
	  section.data(8).dtTransOffset = 11;
	
	  ;% q_2dsfl_open_loop_P.HILReadDigital_channels_p
	  section.data(9).logicalSrcIdx = 32;
	  section.data(9).dtTransOffset = 14;
	
	  ;% q_2dsfl_open_loop_P.HILReadEncoderTimebase_samples_
	  section.data(10).logicalSrcIdx = 33;
	  section.data(10).dtTransOffset = 18;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 35;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage_message_icon_a
	  section.data(3).logicalSrcIdx = 36;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage1_message_icon_p
	  section.data(4).logicalSrcIdx = 37;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage_message_icon_k
	  section.data(5).logicalSrcIdx = 38;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage1_message_icon_m
	  section.data(6).logicalSrcIdx = 39;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage2_message_icon
	  section.data(7).logicalSrcIdx = 40;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_P.StopwithMessage3_message_icon
	  section.data(8).logicalSrcIdx = 41;
	  section.data(8).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 65;
      section.data(65)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.AmplitudeA_Gain
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.Im_r1_Gain
	  section.data(2).logicalSrcIdx = 43;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.AmplitudeA_Gain_j
	  section.data(3).logicalSrcIdx = 44;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.Im_r2_Gain
	  section.data(4).logicalSrcIdx = 45;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_OOTerminate
	  section.data(5).logicalSrcIdx = 46;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_OOExit
	  section.data(6).logicalSrcIdx = 47;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_OOStart
	  section.data(7).logicalSrcIdx = 48;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_OOEnter
	  section.data(8).logicalSrcIdx = 49;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOFinal
	  section.data(9).logicalSrcIdx = 50;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POFinal
	  section.data(10).logicalSrcIdx = 51;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AIHigh
	  section.data(11).logicalSrcIdx = 52;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AILow
	  section.data(12).logicalSrcIdx = 53;
	  section.data(12).dtTransOffset = 11;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOHigh
	  section.data(13).logicalSrcIdx = 54;
	  section.data(13).dtTransOffset = 12;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOLow
	  section.data(14).logicalSrcIdx = 55;
	  section.data(14).dtTransOffset = 13;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOInitial
	  section.data(15).logicalSrcIdx = 56;
	  section.data(15).dtTransOffset = 14;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOWatchdog
	  section.data(16).logicalSrcIdx = 57;
	  section.data(16).dtTransOffset = 15;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIFrequency
	  section.data(17).logicalSrcIdx = 58;
	  section.data(17).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POFrequency
	  section.data(18).logicalSrcIdx = 59;
	  section.data(18).dtTransOffset = 17;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POInitial
	  section.data(19).logicalSrcIdx = 60;
	  section.data(19).dtTransOffset = 18;
	
	  ;% q_2dsfl_open_loop_P.ustStage2DOFSFJRobotStateSpaceM
	  section.data(20).logicalSrcIdx = 61;
	  section.data(20).dtTransOffset = 19;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain
	  section.data(21).logicalSrcIdx = 62;
	  section.data(21).dtTransOffset = 20;
	
	  ;% q_2dsfl_open_loop_P.Filter3_A
	  section.data(22).logicalSrcIdx = 63;
	  section.data(22).dtTransOffset = 21;
	
	  ;% q_2dsfl_open_loop_P.Filter3_C
	  section.data(23).logicalSrcIdx = 64;
	  section.data(23).dtTransOffset = 23;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain_m
	  section.data(24).logicalSrcIdx = 65;
	  section.data(24).dtTransOffset = 25;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter1_A
	  section.data(25).logicalSrcIdx = 66;
	  section.data(25).dtTransOffset = 26;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter1_C
	  section.data(26).logicalSrcIdx = 67;
	  section.data(26).dtTransOffset = 28;
	
	  ;% q_2dsfl_open_loop_P.SignalGenerator_Amplitude
	  section.data(27).logicalSrcIdx = 68;
	  section.data(27).dtTransOffset = 30;
	
	  ;% q_2dsfl_open_loop_P.SignalGenerator_Frequency
	  section.data(28).logicalSrcIdx = 69;
	  section.data(28).dtTransOffset = 31;
	
	  ;% q_2dsfl_open_loop_P.Step_Time
	  section.data(29).logicalSrcIdx = 70;
	  section.data(29).dtTransOffset = 32;
	
	  ;% q_2dsfl_open_loop_P.Step_Y0
	  section.data(30).logicalSrcIdx = 71;
	  section.data(30).dtTransOffset = 33;
	
	  ;% q_2dsfl_open_loop_P.Step_YFinal
	  section.data(31).logicalSrcIdx = 72;
	  section.data(31).dtTransOffset = 34;
	
	  ;% q_2dsfl_open_loop_P.Step1_Time
	  section.data(32).logicalSrcIdx = 73;
	  section.data(32).dtTransOffset = 35;
	
	  ;% q_2dsfl_open_loop_P.Step1_Y0
	  section.data(33).logicalSrcIdx = 74;
	  section.data(33).dtTransOffset = 36;
	
	  ;% q_2dsfl_open_loop_P.Step1_YFinal
	  section.data(34).logicalSrcIdx = 75;
	  section.data(34).dtTransOffset = 37;
	
	  ;% q_2dsfl_open_loop_P.Im_r1Saturation_UpperSat
	  section.data(35).logicalSrcIdx = 76;
	  section.data(35).dtTransOffset = 38;
	
	  ;% q_2dsfl_open_loop_P.Im_r1Saturation_LowerSat
	  section.data(36).logicalSrcIdx = 77;
	  section.data(36).dtTransOffset = 39;
	
	  ;% q_2dsfl_open_loop_P.VoltstoAmps_Gain
	  section.data(37).logicalSrcIdx = 78;
	  section.data(37).dtTransOffset = 40;
	
	  ;% q_2dsfl_open_loop_P.AmpstoVolts_Gain
	  section.data(38).logicalSrcIdx = 79;
	  section.data(38).dtTransOffset = 41;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain_n
	  section.data(39).logicalSrcIdx = 80;
	  section.data(39).dtTransOffset = 42;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter2_A
	  section.data(40).logicalSrcIdx = 81;
	  section.data(40).dtTransOffset = 43;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter2_C
	  section.data(41).logicalSrcIdx = 82;
	  section.data(41).dtTransOffset = 45;
	
	  ;% q_2dsfl_open_loop_P.undStage2DOFSFJRobotStateSpaceM
	  section.data(42).logicalSrcIdx = 83;
	  section.data(42).dtTransOffset = 47;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain_m4
	  section.data(43).logicalSrcIdx = 84;
	  section.data(43).dtTransOffset = 48;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter3_A
	  section.data(44).logicalSrcIdx = 85;
	  section.data(44).dtTransOffset = 49;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter3_C
	  section.data(45).logicalSrcIdx = 86;
	  section.data(45).dtTransOffset = 51;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain_g
	  section.data(46).logicalSrcIdx = 87;
	  section.data(46).dtTransOffset = 53;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter1_A_l
	  section.data(47).logicalSrcIdx = 88;
	  section.data(47).dtTransOffset = 54;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter1_C_o
	  section.data(48).logicalSrcIdx = 89;
	  section.data(48).dtTransOffset = 56;
	
	  ;% q_2dsfl_open_loop_P.SignalGenerator1_Amplitude
	  section.data(49).logicalSrcIdx = 90;
	  section.data(49).dtTransOffset = 58;
	
	  ;% q_2dsfl_open_loop_P.SignalGenerator1_Frequency
	  section.data(50).logicalSrcIdx = 91;
	  section.data(50).dtTransOffset = 59;
	
	  ;% q_2dsfl_open_loop_P.Step_Time_f
	  section.data(51).logicalSrcIdx = 92;
	  section.data(51).dtTransOffset = 60;
	
	  ;% q_2dsfl_open_loop_P.Step_Y0_m
	  section.data(52).logicalSrcIdx = 93;
	  section.data(52).dtTransOffset = 61;
	
	  ;% q_2dsfl_open_loop_P.Step_YFinal_n
	  section.data(53).logicalSrcIdx = 94;
	  section.data(53).dtTransOffset = 62;
	
	  ;% q_2dsfl_open_loop_P.Step1_Time_h
	  section.data(54).logicalSrcIdx = 95;
	  section.data(54).dtTransOffset = 63;
	
	  ;% q_2dsfl_open_loop_P.Step1_Y0_g
	  section.data(55).logicalSrcIdx = 96;
	  section.data(55).dtTransOffset = 64;
	
	  ;% q_2dsfl_open_loop_P.Step1_YFinal_e
	  section.data(56).logicalSrcIdx = 97;
	  section.data(56).dtTransOffset = 65;
	
	  ;% q_2dsfl_open_loop_P.Im_r2Saturation_UpperSat
	  section.data(57).logicalSrcIdx = 98;
	  section.data(57).dtTransOffset = 66;
	
	  ;% q_2dsfl_open_loop_P.Im_r2Saturation_LowerSat
	  section.data(58).logicalSrcIdx = 99;
	  section.data(58).dtTransOffset = 67;
	
	  ;% q_2dsfl_open_loop_P.VoltstoAmps_Gain_g
	  section.data(59).logicalSrcIdx = 100;
	  section.data(59).dtTransOffset = 68;
	
	  ;% q_2dsfl_open_loop_P.AmpstoVolts_Gain_e
	  section.data(60).logicalSrcIdx = 101;
	  section.data(60).dtTransOffset = 69;
	
	  ;% q_2dsfl_open_loop_P.Gain_Gain_n5
	  section.data(61).logicalSrcIdx = 102;
	  section.data(61).dtTransOffset = 70;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter2_A_g
	  section.data(62).logicalSrcIdx = 103;
	  section.data(62).dtTransOffset = 71;
	
	  ;% q_2dsfl_open_loop_P.DerivativeFilter2_C_f
	  section.data(63).logicalSrcIdx = 104;
	  section.data(63).dtTransOffset = 73;
	
	  ;% q_2dsfl_open_loop_P.EnableActiveLow_Value
	  section.data(64).logicalSrcIdx = 105;
	  section.data(64).dtTransOffset = 75;
	
	  ;% q_2dsfl_open_loop_P.MasterEnableActiveHigh_Value
	  section.data(65).logicalSrcIdx = 106;
	  section.data(65).dtTransOffset = 77;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 107;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKModes
	  section.data(2).logicalSrcIdx = 108;
	  section.data(2).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOWatchdog
	  section.data(3).logicalSrcIdx = 109;
	  section.data(3).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIInitial
	  section.data(4).logicalSrcIdx = 110;
	  section.data(4).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POModes
	  section.data(5).logicalSrcIdx = 111;
	  section.data(5).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 112;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 113;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DIChannels
	  section.data(3).logicalSrcIdx = 114;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOChannels
	  section.data(4).logicalSrcIdx = 115;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIChannels
	  section.data(5).logicalSrcIdx = 116;
	  section.data(5).dtTransOffset = 32;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIQuadrature
	  section.data(6).logicalSrcIdx = 117;
	  section.data(6).dtTransOffset = 40;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.Constant_Value
	  section.data(1).logicalSrcIdx = 118;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_k
	  section.data(2).logicalSrcIdx = 119;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_p
	  section.data(3).logicalSrcIdx = 120;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_o
	  section.data(4).logicalSrcIdx = 121;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_Active
	  section.data(5).logicalSrcIdx = 122;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOTerminate
	  section.data(6).logicalSrcIdx = 123;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOExit
	  section.data(7).logicalSrcIdx = 124;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOTerminate
	  section.data(8).logicalSrcIdx = 125;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOExit
	  section.data(9).logicalSrcIdx = 126;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POTerminate
	  section.data(10).logicalSrcIdx = 127;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POExit
	  section.data(11).logicalSrcIdx = 128;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKPStart
	  section.data(12).logicalSrcIdx = 129;
	  section.data(12).dtTransOffset = 11;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKPEnter
	  section.data(13).logicalSrcIdx = 130;
	  section.data(13).dtTransOffset = 12;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKStart
	  section.data(14).logicalSrcIdx = 131;
	  section.data(14).dtTransOffset = 13;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_CKEnter
	  section.data(15).logicalSrcIdx = 132;
	  section.data(15).dtTransOffset = 14;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AIPStart
	  section.data(16).logicalSrcIdx = 133;
	  section.data(16).dtTransOffset = 15;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AIPEnter
	  section.data(17).logicalSrcIdx = 134;
	  section.data(17).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOPStart
	  section.data(18).logicalSrcIdx = 135;
	  section.data(18).dtTransOffset = 17;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOPEnter
	  section.data(19).logicalSrcIdx = 136;
	  section.data(19).dtTransOffset = 18;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOStart
	  section.data(20).logicalSrcIdx = 137;
	  section.data(20).dtTransOffset = 19;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOEnter
	  section.data(21).logicalSrcIdx = 138;
	  section.data(21).dtTransOffset = 20;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_AOReset
	  section.data(22).logicalSrcIdx = 139;
	  section.data(22).dtTransOffset = 21;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOPStart
	  section.data(23).logicalSrcIdx = 140;
	  section.data(23).dtTransOffset = 22;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOPEnter
	  section.data(24).logicalSrcIdx = 141;
	  section.data(24).dtTransOffset = 23;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOStart
	  section.data(25).logicalSrcIdx = 142;
	  section.data(25).dtTransOffset = 24;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOEnter
	  section.data(26).logicalSrcIdx = 143;
	  section.data(26).dtTransOffset = 25;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOReset
	  section.data(27).logicalSrcIdx = 144;
	  section.data(27).dtTransOffset = 26;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIPStart
	  section.data(28).logicalSrcIdx = 145;
	  section.data(28).dtTransOffset = 27;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIPEnter
	  section.data(29).logicalSrcIdx = 146;
	  section.data(29).dtTransOffset = 28;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIStart
	  section.data(30).logicalSrcIdx = 147;
	  section.data(30).dtTransOffset = 29;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_EIEnter
	  section.data(31).logicalSrcIdx = 148;
	  section.data(31).dtTransOffset = 30;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POPStart
	  section.data(32).logicalSrcIdx = 149;
	  section.data(32).dtTransOffset = 31;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POPEnter
	  section.data(33).logicalSrcIdx = 150;
	  section.data(33).dtTransOffset = 32;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POStart
	  section.data(34).logicalSrcIdx = 151;
	  section.data(34).dtTransOffset = 33;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POEnter
	  section.data(35).logicalSrcIdx = 152;
	  section.data(35).dtTransOffset = 34;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_POReset
	  section.data(36).logicalSrcIdx = 153;
	  section.data(36).dtTransOffset = 35;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_OOReset
	  section.data(37).logicalSrcIdx = 154;
	  section.data(37).dtTransOffset = 36;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOFinal
	  section.data(38).logicalSrcIdx = 155;
	  section.data(38).dtTransOffset = 37;
	
	  ;% q_2dsfl_open_loop_P.HILInitialize_DOInitial
	  section.data(39).logicalSrcIdx = 156;
	  section.data(39).dtTransOffset = 38;
	
	  ;% q_2dsfl_open_loop_P.HILReadEncoderTimebase_Active
	  section.data(40).logicalSrcIdx = 157;
	  section.data(40).dtTransOffset = 39;
	
	  ;% q_2dsfl_open_loop_P.HILReadAnalog_Active
	  section.data(41).logicalSrcIdx = 158;
	  section.data(41).dtTransOffset = 40;
	
	  ;% q_2dsfl_open_loop_P.HILWriteAnalog_Active
	  section.data(42).logicalSrcIdx = 159;
	  section.data(42).dtTransOffset = 41;
	
	  ;% q_2dsfl_open_loop_P.HILReadEncoder_Active
	  section.data(43).logicalSrcIdx = 160;
	  section.data(43).dtTransOffset = 42;
	
	  ;% q_2dsfl_open_loop_P.HILReadAnalog_Active_p
	  section.data(44).logicalSrcIdx = 161;
	  section.data(44).dtTransOffset = 43;
	
	  ;% q_2dsfl_open_loop_P.HILWriteAnalog_Active_a
	  section.data(45).logicalSrcIdx = 162;
	  section.data(45).dtTransOffset = 44;
	
	  ;% q_2dsfl_open_loop_P.HILWriteDigital_Active
	  section.data(46).logicalSrcIdx = 163;
	  section.data(46).dtTransOffset = 45;
	
	  ;% q_2dsfl_open_loop_P.HILReadDigital_Active
	  section.data(47).logicalSrcIdx = 164;
	  section.data(47).dtTransOffset = 46;
	
	  ;% q_2dsfl_open_loop_P.HILReadDigital_Active_h
	  section.data(48).logicalSrcIdx = 165;
	  section.data(48).dtTransOffset = 47;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_h
	  section.data(49).logicalSrcIdx = 166;
	  section.data(49).dtTransOffset = 48;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_i
	  section.data(50).logicalSrcIdx = 167;
	  section.data(50).dtTransOffset = 49;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_e
	  section.data(51).logicalSrcIdx = 168;
	  section.data(51).dtTransOffset = 50;
	
	  ;% q_2dsfl_open_loop_P.Constant_Value_d
	  section.data(52).logicalSrcIdx = 169;
	  section.data(52).dtTransOffset = 51;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.ManualSwitch1_CurrentSetting
	  section.data(1).logicalSrcIdx = 170;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.ManualSwitch_CurrentSetting
	  section.data(2).logicalSrcIdx = 171;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(9) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.unity_Value
	  section.data(1).logicalSrcIdx = 172;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.UnitDelay_InitialCondition
	  section.data(2).logicalSrcIdx = 173;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Sumk1n1xk_InitialCondition
	  section.data(3).logicalSrcIdx = 174;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.zero_Y0
	  section.data(4).logicalSrcIdx = 175;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Constant_Value
	  section.data(5).logicalSrcIdx = 176;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Vbiased_Y0
	  section.data(6).logicalSrcIdx = 177;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Vunbiased_Y0
	  section.data(7).logicalSrcIdx = 178;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Stepstart_time_Y0
	  section.data(8).logicalSrcIdx = 179;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Stepstart_time_YFinal
	  section.data(9).logicalSrcIdx = 180;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Stepend_time_Y0
	  section.data(10).logicalSrcIdx = 181;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval_e.Stepend_time_YFinal
	  section.data(11).logicalSrcIdx = 182;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(10) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_P.BiasRemoval.unity_Value
	  section.data(1).logicalSrcIdx = 183;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.UnitDelay_InitialCondition
	  section.data(2).logicalSrcIdx = 184;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Sumk1n1xk_InitialCondition
	  section.data(3).logicalSrcIdx = 185;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.zero_Y0
	  section.data(4).logicalSrcIdx = 186;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Constant_Value
	  section.data(5).logicalSrcIdx = 187;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Vbiased_Y0
	  section.data(6).logicalSrcIdx = 188;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Vunbiased_Y0
	  section.data(7).logicalSrcIdx = 189;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Stepstart_time_Y0
	  section.data(8).logicalSrcIdx = 190;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Stepstart_time_YFinal
	  section.data(9).logicalSrcIdx = 191;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Stepend_time_Y0
	  section.data(10).logicalSrcIdx = 192;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_P.BiasRemoval.Stepend_time_YFinal
	  section.data(11).logicalSrcIdx = 193;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(11) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_open_loop_B)
    ;%
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_B.Motor1EncoderCalib
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_B.Gain
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_B.Gain_a
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_B.positiveCCW
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_B.VoltstoBaseStrain
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_B.Im_r1Saturation
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_B.VoltstoAmps
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_B.AmpstoVolts
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_B.StraintoDeflection
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 10;
	
	  ;% q_2dsfl_open_loop_B.Motor2EncoderCalib
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 11;
	
	  ;% q_2dsfl_open_loop_B.Gain_p
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 12;
	
	  ;% q_2dsfl_open_loop_B.Gain_m
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 14;
	
	  ;% q_2dsfl_open_loop_B.positiveCCW_l
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_B.VoltstoStrain
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 17;
	
	  ;% q_2dsfl_open_loop_B.Im_r2Saturation
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 18;
	
	  ;% q_2dsfl_open_loop_B.VoltstoAmps_h
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 19;
	
	  ;% q_2dsfl_open_loop_B.AmpstoVolts_d
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 20;
	
	  ;% q_2dsfl_open_loop_B.StraintoDeflection_g
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 21;
	
	  ;% q_2dsfl_open_loop_B.HILReadDigital_o1
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 22;
	
	  ;% q_2dsfl_open_loop_B.HILReadDigital_o2
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 23;
	
	  ;% q_2dsfl_open_loop_B.HILReadDigital_o3
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_B.CheckMaximumAllowedPosition
	  section.data(5).logicalSrcIdx = 25;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_B.Compare
	  section.data(6).logicalSrcIdx = 26;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_B.CheckMinimumAllowedPosition
	  section.data(7).logicalSrcIdx = 27;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_B.Compare_p
	  section.data(8).logicalSrcIdx = 28;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_B.CheckMaximumAllowedPosition_a
	  section.data(9).logicalSrcIdx = 29;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_B.Compare_l
	  section.data(10).logicalSrcIdx = 30;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_B.CheckMinimumAllowedPosition_d
	  section.data(11).logicalSrcIdx = 31;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_open_loop_B.Compare_b
	  section.data(12).logicalSrcIdx = 32;
	  section.data(12).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.Switch
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.VVavg
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.Vin
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.Constant
	  section.data(4).logicalSrcIdx = 36;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.Count
	  section.data(5).logicalSrcIdx = 37;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.Sum
	  section.data(6).logicalSrcIdx = 38;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval_e.div
	  section.data(7).logicalSrcIdx = 39;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_B.BiasRemoval.Switch
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.VVavg
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.Vin
	  section.data(3).logicalSrcIdx = 43;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.Constant
	  section.data(4).logicalSrcIdx = 44;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.Count
	  section.data(5).logicalSrcIdx = 45;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.Sum
	  section.data(6).logicalSrcIdx = 46;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_B.BiasRemoval.div
	  section.data(7).logicalSrcIdx = 47;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 15;
    sectIdxOffset = 4;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_open_loop_DW)
    ;%
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% q_2dsfl_open_loop_DW.HILReadAnalog_Buffer
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 50;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 18;
      section.data(18)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.theta11deg_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.theta12deg_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_DW.HILReadAnalog_PWORK
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_DW.BaseStrainmmmm_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_DW.CurrentResponse1A_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_open_loop_DW.HILWriteAnalog_PWORK
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_open_loop_DW.StrainGauge0V_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 16;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_open_loop_DW.HILReadEncoder_PWORK
	  section.data(8).logicalSrcIdx = 17;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_open_loop_DW.theta21deg_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 18;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_DW.theta22deg_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 19;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_open_loop_DW.HILReadAnalog_PWORK_k
	  section.data(11).logicalSrcIdx = 20;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_open_loop_DW.BaseStrainmmmm_PWORK_b.LoggedData
	  section.data(12).logicalSrcIdx = 21;
	  section.data(12).dtTransOffset = 11;
	
	  ;% q_2dsfl_open_loop_DW.CurrentResponse2A_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 22;
	  section.data(13).dtTransOffset = 12;
	
	  ;% q_2dsfl_open_loop_DW.HILWriteAnalog_PWORK_b
	  section.data(14).logicalSrcIdx = 23;
	  section.data(14).dtTransOffset = 13;
	
	  ;% q_2dsfl_open_loop_DW.StrainGauge1V_PWORK.LoggedData
	  section.data(15).logicalSrcIdx = 24;
	  section.data(15).dtTransOffset = 14;
	
	  ;% q_2dsfl_open_loop_DW.HILWriteDigital_PWORK
	  section.data(16).logicalSrcIdx = 25;
	  section.data(16).dtTransOffset = 15;
	
	  ;% q_2dsfl_open_loop_DW.HILReadDigital_PWORK
	  section.data(17).logicalSrcIdx = 26;
	  section.data(17).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_DW.HILReadDigital_PWORK_o
	  section.data(18).logicalSrcIdx = 27;
	  section.data(18).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILInitialize_DOStates
	  section.data(1).logicalSrcIdx = 28;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 29;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_2dsfl_open_loop_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 30;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Buffer
	  section.data(4).logicalSrcIdx = 31;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_2dsfl_open_loop_DW.HILReadEncoder_Buffer
	  section.data(5).logicalSrcIdx = 32;
	  section.data(5).dtTransOffset = 25;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC_b
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.HILWriteDigital_Buffer
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.HILReadDigital_Buffer
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_DW.HILReadDigital_Buffer_c
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.PositionWatchdog_MODE
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.PositionWatchdog_MODE_k
	  section.data(2).logicalSrcIdx = 40;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.UnitDelay_DSTATE
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.Sumk1n1xk_DSTATE
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCase_ActiveSubsystem
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem2_Subs
	  section.data(2).logicalSrcIdx = 44;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem1_Subs
	  section.data(3).logicalSrcIdx = 45;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem_Subsy
	  section.data(4).logicalSrcIdx = 46;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.EnabledMovingAverage_SubsysRanB
	  section.data(5).logicalSrcIdx = 47;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval_e.EnabledMovingAverage_MODE
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.UnitDelay_DSTATE
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.Sumk1n1xk_DSTATE
	  section.data(2).logicalSrcIdx = 50;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.SwitchCase_ActiveSubsystem
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs
	  section.data(3).logicalSrcIdx = 53;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy
	  section.data(4).logicalSrcIdx = 54;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB
	  section.data(5).logicalSrcIdx = 55;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_open_loop_DW.BiasRemoval.EnabledMovingAverage_MODE
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 601783685;
  targMap.checksum1 = 3843670298;
  targMap.checksum2 = 3954036039;
  targMap.checksum3 = 3719966662;

