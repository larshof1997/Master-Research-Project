  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 9;
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
    ;% Auto data (torque_control_P)
    ;%
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% torque_control_P.KE_D1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.KE_D2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_P.Kt1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_P.L1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_P.L2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_P.LIMIT_SWITCHES_ENABLE
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_P.R1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_P.R2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% torque_control_P.ke1
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% torque_control_P.ke2
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% torque_control_P.DiscreteDerivative1_ICPrevScale
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% torque_control_P.DiscreteDerivative_ICPrevScaled
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% torque_control_P.DiscreteDerivative3_ICPrevScale
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% torque_control_P.DiscreteDerivative2_ICPrevScale
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% torque_control_P.HILWriteDigitalTimebase_clock
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% torque_control_P.HILReadEncoder_channels
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.HILReadAnalog_channels
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 2;
	
	  ;% torque_control_P.HILWriteAnalog_channels
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 3;
	
	  ;% torque_control_P.HILWriteDigitalTimebase_channel
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 4;
	
	  ;% torque_control_P.HILWriteDigital_channels
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 5;
	
	  ;% torque_control_P.HILReadDigital_channels
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 8;
	
	  ;% torque_control_P.HILWriteDigitalTimebase_samples
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% torque_control_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 22;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 23;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_P.StopwithMessage2_message_icon
	  section.data(3).logicalSrcIdx = 24;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_P.StopwithMessage3_message_icon
	  section.data(4).logicalSrcIdx = 25;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 37;
      section.data(37)  = dumData; %prealloc
      
	  ;% torque_control_P.TSamp_WtEt
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.TSamp_WtEt_e
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_P.tau_ref_Value
	  section.data(3).logicalSrcIdx = 28;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_P.SineWave_Amp
	  section.data(4).logicalSrcIdx = 29;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_P.SineWave_Bias
	  section.data(5).logicalSrcIdx = 30;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_P.SineWave_Freq
	  section.data(6).logicalSrcIdx = 31;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_P.SineWave_Phase
	  section.data(7).logicalSrcIdx = 32;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_P.TSamp_WtEt_o
	  section.data(8).logicalSrcIdx = 33;
	  section.data(8).dtTransOffset = 7;
	
	  ;% torque_control_P.Gain_Gain
	  section.data(9).logicalSrcIdx = 34;
	  section.data(9).dtTransOffset = 8;
	
	  ;% torque_control_P.DiscreteTimeIntegrator_gainval
	  section.data(10).logicalSrcIdx = 35;
	  section.data(10).dtTransOffset = 9;
	
	  ;% torque_control_P.DiscreteTimeIntegrator_IC
	  section.data(11).logicalSrcIdx = 36;
	  section.data(11).dtTransOffset = 10;
	
	  ;% torque_control_P.Gain1_Gain
	  section.data(12).logicalSrcIdx = 37;
	  section.data(12).dtTransOffset = 11;
	
	  ;% torque_control_P.TSamp_WtEt_o3
	  section.data(13).logicalSrcIdx = 38;
	  section.data(13).dtTransOffset = 12;
	
	  ;% torque_control_P.Gain2_Gain
	  section.data(14).logicalSrcIdx = 39;
	  section.data(14).dtTransOffset = 13;
	
	  ;% torque_control_P.Im_r1Saturation_UpperSat
	  section.data(15).logicalSrcIdx = 40;
	  section.data(15).dtTransOffset = 14;
	
	  ;% torque_control_P.Im_r1Saturation_LowerSat
	  section.data(16).logicalSrcIdx = 41;
	  section.data(16).dtTransOffset = 15;
	
	  ;% torque_control_P.PulseGenerator_Amp
	  section.data(17).logicalSrcIdx = 42;
	  section.data(17).dtTransOffset = 16;
	
	  ;% torque_control_P.PulseGenerator_Period
	  section.data(18).logicalSrcIdx = 43;
	  section.data(18).dtTransOffset = 17;
	
	  ;% torque_control_P.PulseGenerator_Duty
	  section.data(19).logicalSrcIdx = 44;
	  section.data(19).dtTransOffset = 18;
	
	  ;% torque_control_P.PulseGenerator_PhaseDelay
	  section.data(20).logicalSrcIdx = 45;
	  section.data(20).dtTransOffset = 19;
	
	  ;% torque_control_P.HILInitialize_OOTerminate
	  section.data(21).logicalSrcIdx = 46;
	  section.data(21).dtTransOffset = 20;
	
	  ;% torque_control_P.HILInitialize_OOExit
	  section.data(22).logicalSrcIdx = 47;
	  section.data(22).dtTransOffset = 21;
	
	  ;% torque_control_P.HILInitialize_OOStart
	  section.data(23).logicalSrcIdx = 48;
	  section.data(23).dtTransOffset = 22;
	
	  ;% torque_control_P.HILInitialize_OOEnter
	  section.data(24).logicalSrcIdx = 49;
	  section.data(24).dtTransOffset = 23;
	
	  ;% torque_control_P.HILInitialize_AOFinal
	  section.data(25).logicalSrcIdx = 50;
	  section.data(25).dtTransOffset = 24;
	
	  ;% torque_control_P.HILInitialize_POFinal
	  section.data(26).logicalSrcIdx = 51;
	  section.data(26).dtTransOffset = 25;
	
	  ;% torque_control_P.HILInitialize_AIHigh
	  section.data(27).logicalSrcIdx = 52;
	  section.data(27).dtTransOffset = 26;
	
	  ;% torque_control_P.HILInitialize_AILow
	  section.data(28).logicalSrcIdx = 53;
	  section.data(28).dtTransOffset = 27;
	
	  ;% torque_control_P.HILInitialize_AOHigh
	  section.data(29).logicalSrcIdx = 54;
	  section.data(29).dtTransOffset = 28;
	
	  ;% torque_control_P.HILInitialize_AOLow
	  section.data(30).logicalSrcIdx = 55;
	  section.data(30).dtTransOffset = 29;
	
	  ;% torque_control_P.HILInitialize_AOInitial
	  section.data(31).logicalSrcIdx = 56;
	  section.data(31).dtTransOffset = 30;
	
	  ;% torque_control_P.HILInitialize_AOWatchdog
	  section.data(32).logicalSrcIdx = 57;
	  section.data(32).dtTransOffset = 31;
	
	  ;% torque_control_P.HILInitialize_EIFrequency
	  section.data(33).logicalSrcIdx = 58;
	  section.data(33).dtTransOffset = 32;
	
	  ;% torque_control_P.HILInitialize_POFrequency
	  section.data(34).logicalSrcIdx = 59;
	  section.data(34).dtTransOffset = 33;
	
	  ;% torque_control_P.HILInitialize_POInitial
	  section.data(35).logicalSrcIdx = 60;
	  section.data(35).dtTransOffset = 34;
	
	  ;% torque_control_P.EnableActiveLow_Value
	  section.data(36).logicalSrcIdx = 61;
	  section.data(36).dtTransOffset = 35;
	
	  ;% torque_control_P.MasterEnableActiveHigh_Value
	  section.data(37).logicalSrcIdx = 62;
	  section.data(37).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% torque_control_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.HILInitialize_CKModes
	  section.data(2).logicalSrcIdx = 64;
	  section.data(2).dtTransOffset = 2;
	
	  ;% torque_control_P.HILInitialize_DOWatchdog
	  section.data(3).logicalSrcIdx = 65;
	  section.data(3).dtTransOffset = 4;
	
	  ;% torque_control_P.HILInitialize_EIInitial
	  section.data(4).logicalSrcIdx = 66;
	  section.data(4).dtTransOffset = 5;
	
	  ;% torque_control_P.HILInitialize_POModes
	  section.data(5).logicalSrcIdx = 67;
	  section.data(5).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% torque_control_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 68;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 69;
	  section.data(2).dtTransOffset = 8;
	
	  ;% torque_control_P.HILInitialize_DIChannels
	  section.data(3).logicalSrcIdx = 70;
	  section.data(3).dtTransOffset = 16;
	
	  ;% torque_control_P.HILInitialize_DOChannels
	  section.data(4).logicalSrcIdx = 71;
	  section.data(4).dtTransOffset = 24;
	
	  ;% torque_control_P.HILInitialize_EIChannels
	  section.data(5).logicalSrcIdx = 72;
	  section.data(5).dtTransOffset = 33;
	
	  ;% torque_control_P.HILInitialize_EIQuadrature
	  section.data(6).logicalSrcIdx = 73;
	  section.data(6).dtTransOffset = 41;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 45;
      section.data(45)  = dumData; %prealloc
      
	  ;% torque_control_P.HILReadEncoder_Active
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.HILReadAnalog_Active
	  section.data(2).logicalSrcIdx = 75;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_P.HILWriteAnalog_Active
	  section.data(3).logicalSrcIdx = 76;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_P.HILInitialize_Active
	  section.data(4).logicalSrcIdx = 77;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_P.HILInitialize_AOTerminate
	  section.data(5).logicalSrcIdx = 78;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_P.HILInitialize_AOExit
	  section.data(6).logicalSrcIdx = 79;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_P.HILInitialize_DOTerminate
	  section.data(7).logicalSrcIdx = 80;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_P.HILInitialize_DOExit
	  section.data(8).logicalSrcIdx = 81;
	  section.data(8).dtTransOffset = 7;
	
	  ;% torque_control_P.HILInitialize_POTerminate
	  section.data(9).logicalSrcIdx = 82;
	  section.data(9).dtTransOffset = 8;
	
	  ;% torque_control_P.HILInitialize_POExit
	  section.data(10).logicalSrcIdx = 83;
	  section.data(10).dtTransOffset = 9;
	
	  ;% torque_control_P.HILInitialize_CKPStart
	  section.data(11).logicalSrcIdx = 84;
	  section.data(11).dtTransOffset = 10;
	
	  ;% torque_control_P.HILInitialize_CKPEnter
	  section.data(12).logicalSrcIdx = 85;
	  section.data(12).dtTransOffset = 11;
	
	  ;% torque_control_P.HILInitialize_CKStart
	  section.data(13).logicalSrcIdx = 86;
	  section.data(13).dtTransOffset = 12;
	
	  ;% torque_control_P.HILInitialize_CKEnter
	  section.data(14).logicalSrcIdx = 87;
	  section.data(14).dtTransOffset = 13;
	
	  ;% torque_control_P.HILInitialize_AIPStart
	  section.data(15).logicalSrcIdx = 88;
	  section.data(15).dtTransOffset = 14;
	
	  ;% torque_control_P.HILInitialize_AIPEnter
	  section.data(16).logicalSrcIdx = 89;
	  section.data(16).dtTransOffset = 15;
	
	  ;% torque_control_P.HILInitialize_AOPStart
	  section.data(17).logicalSrcIdx = 90;
	  section.data(17).dtTransOffset = 16;
	
	  ;% torque_control_P.HILInitialize_AOPEnter
	  section.data(18).logicalSrcIdx = 91;
	  section.data(18).dtTransOffset = 17;
	
	  ;% torque_control_P.HILInitialize_AOStart
	  section.data(19).logicalSrcIdx = 92;
	  section.data(19).dtTransOffset = 18;
	
	  ;% torque_control_P.HILInitialize_AOEnter
	  section.data(20).logicalSrcIdx = 93;
	  section.data(20).dtTransOffset = 19;
	
	  ;% torque_control_P.HILInitialize_AOReset
	  section.data(21).logicalSrcIdx = 94;
	  section.data(21).dtTransOffset = 20;
	
	  ;% torque_control_P.HILInitialize_DOPStart
	  section.data(22).logicalSrcIdx = 95;
	  section.data(22).dtTransOffset = 21;
	
	  ;% torque_control_P.HILInitialize_DOPEnter
	  section.data(23).logicalSrcIdx = 96;
	  section.data(23).dtTransOffset = 22;
	
	  ;% torque_control_P.HILInitialize_DOStart
	  section.data(24).logicalSrcIdx = 97;
	  section.data(24).dtTransOffset = 23;
	
	  ;% torque_control_P.HILInitialize_DOEnter
	  section.data(25).logicalSrcIdx = 98;
	  section.data(25).dtTransOffset = 24;
	
	  ;% torque_control_P.HILInitialize_DOReset
	  section.data(26).logicalSrcIdx = 99;
	  section.data(26).dtTransOffset = 25;
	
	  ;% torque_control_P.HILInitialize_EIPStart
	  section.data(27).logicalSrcIdx = 100;
	  section.data(27).dtTransOffset = 26;
	
	  ;% torque_control_P.HILInitialize_EIPEnter
	  section.data(28).logicalSrcIdx = 101;
	  section.data(28).dtTransOffset = 27;
	
	  ;% torque_control_P.HILInitialize_EIStart
	  section.data(29).logicalSrcIdx = 102;
	  section.data(29).dtTransOffset = 28;
	
	  ;% torque_control_P.HILInitialize_EIEnter
	  section.data(30).logicalSrcIdx = 103;
	  section.data(30).dtTransOffset = 29;
	
	  ;% torque_control_P.HILInitialize_POPStart
	  section.data(31).logicalSrcIdx = 104;
	  section.data(31).dtTransOffset = 30;
	
	  ;% torque_control_P.HILInitialize_POPEnter
	  section.data(32).logicalSrcIdx = 105;
	  section.data(32).dtTransOffset = 31;
	
	  ;% torque_control_P.HILInitialize_POStart
	  section.data(33).logicalSrcIdx = 106;
	  section.data(33).dtTransOffset = 32;
	
	  ;% torque_control_P.HILInitialize_POEnter
	  section.data(34).logicalSrcIdx = 107;
	  section.data(34).dtTransOffset = 33;
	
	  ;% torque_control_P.HILInitialize_POReset
	  section.data(35).logicalSrcIdx = 108;
	  section.data(35).dtTransOffset = 34;
	
	  ;% torque_control_P.HILInitialize_OOReset
	  section.data(36).logicalSrcIdx = 109;
	  section.data(36).dtTransOffset = 35;
	
	  ;% torque_control_P.HILInitialize_DOFinal
	  section.data(37).logicalSrcIdx = 110;
	  section.data(37).dtTransOffset = 36;
	
	  ;% torque_control_P.HILInitialize_DOInitial
	  section.data(38).logicalSrcIdx = 111;
	  section.data(38).dtTransOffset = 37;
	
	  ;% torque_control_P.HILWriteDigitalTimebase_Active
	  section.data(39).logicalSrcIdx = 112;
	  section.data(39).dtTransOffset = 38;
	
	  ;% torque_control_P.HILWriteDigital_Active
	  section.data(40).logicalSrcIdx = 113;
	  section.data(40).dtTransOffset = 39;
	
	  ;% torque_control_P.HILReadDigital_Active
	  section.data(41).logicalSrcIdx = 114;
	  section.data(41).dtTransOffset = 40;
	
	  ;% torque_control_P.Constant_Value
	  section.data(42).logicalSrcIdx = 115;
	  section.data(42).dtTransOffset = 41;
	
	  ;% torque_control_P.Constant_Value_k
	  section.data(43).logicalSrcIdx = 116;
	  section.data(43).dtTransOffset = 42;
	
	  ;% torque_control_P.Constant_Value_m
	  section.data(44).logicalSrcIdx = 117;
	  section.data(44).dtTransOffset = 43;
	
	  ;% torque_control_P.Constant_Value_me
	  section.data(45).logicalSrcIdx = 118;
	  section.data(45).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% torque_control_P.ManualSwitch3_CurrentSetting
	  section.data(1).logicalSrcIdx = 119;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_P.ManualSwitch2_CurrentSetting
	  section.data(2).logicalSrcIdx = 120;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 121;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(9) = section;
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
    nTotSects     = 2;
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
    ;% Auto data (torque_control_B)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% torque_control_B.TSamp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_B.TSamp_l
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_B.ManualSwitch3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_B.Torquetocurrent
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_B.TSamp_lo
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_B.ManualSwitch1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_B.Current
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_B.Sum1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% torque_control_B.Gain1
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% torque_control_B.TSamp_n
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% torque_control_B.Gain2
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% torque_control_B.Im_r1Saturation
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% torque_control_B.VectorConcatenate
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% torque_control_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
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
    nTotSects     = 7;
    sectIdxOffset = 2;
    
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
    ;% Auto data (torque_control_DW)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% torque_control_DW.UD_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_DW.UD_DSTATE_f
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_DW.UD_DSTATE_a
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_DW.UD_DSTATE_m
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_DW.HILReadAnalog_Buffer
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_DW.HILInitialize_AIMinimums
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_DW.HILInitialize_AIMaximums
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 14;
	
	  ;% torque_control_DW.HILInitialize_AOMinimums
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 22;
	
	  ;% torque_control_DW.HILInitialize_AOMaximums
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 30;
	
	  ;% torque_control_DW.HILInitialize_AOVoltages
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 38;
	
	  ;% torque_control_DW.HILInitialize_FilterFrequency
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 46;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILWriteDigitalTimebase_Task
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_DW.HILReadAnalog_PWORK
	  section.data(2).logicalSrcIdx = 15;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_DW.HILWriteAnalog_PWORK
	  section.data(3).logicalSrcIdx = 16;
	  section.data(3).dtTransOffset = 2;
	
	  ;% torque_control_DW.ToWorkspace_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 17;
	  section.data(4).dtTransOffset = 3;
	
	  ;% torque_control_DW.Voltage_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 18;
	  section.data(5).dtTransOffset = 4;
	
	  ;% torque_control_DW.current_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 19;
	  section.data(6).dtTransOffset = 5;
	
	  ;% torque_control_DW.currenterror_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 20;
	  section.data(7).dtTransOffset = 6;
	
	  ;% torque_control_DW.omega_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 21;
	  section.data(8).dtTransOffset = 7;
	
	  ;% torque_control_DW.refcurrent_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 22;
	  section.data(9).dtTransOffset = 8;
	
	  ;% torque_control_DW.HILWriteDigital_PWORK
	  section.data(10).logicalSrcIdx = 23;
	  section.data(10).dtTransOffset = 9;
	
	  ;% torque_control_DW.HILReadDigital_PWORK
	  section.data(11).logicalSrcIdx = 24;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILReadEncoder_Buffer
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_DW.clockTickCounter
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 2;
	
	  ;% torque_control_DW.HILInitialize_DOStates
	  section.data(3).logicalSrcIdx = 27;
	  section.data(3).dtTransOffset = 3;
	
	  ;% torque_control_DW.HILInitialize_QuadratureModes
	  section.data(4).logicalSrcIdx = 28;
	  section.data(4).dtTransOffset = 12;
	
	  ;% torque_control_DW.HILInitialize_InitialEICounts
	  section.data(5).logicalSrcIdx = 29;
	  section.data(5).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_DW.HILWriteDigitalTimebase_Started
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% torque_control_DW.HILWriteDigitalTimebase_Buffer
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% torque_control_DW.HILWriteDigital_Buffer
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 1;
	
	  ;% torque_control_DW.HILReadDigital_Buffer
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
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


  targMap.checksum0 = 2611712601;
  targMap.checksum1 = 842854290;
  targMap.checksum2 = 972620699;
  targMap.checksum3 = 1590904538;

