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
    ;% Auto data (DATA_COLLECTION_1DOF_P)
    ;%
      section.nData     = 22;
      section.data(22)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.KE_D1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.KE_D2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_P.Kt1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.L1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_1DOF_P.L2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_P.LIMIT_SWITCHES_ENABLE
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_P.R1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_P.R2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_P.a1_hat
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_P.a2_hat
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_1DOF_P.b1_hat
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_P.b_hat
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_1DOF_P.i_sat1
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_1DOF_P.ke1
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_P.ke2
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_1DOF_P.ki1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_1DOF_P.ki_traj
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteDerivative3_ICPrevScale
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteDerivative_ICPrevScaled
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteDerivative_ICPrevScal_n
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteDerivative2_ICPrevScale
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteDerivative1_ICPrevScale
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigitalTimebase_clock
	  section.data(1).logicalSrcIdx = 22;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.HILReadEncoder_channels
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadEncoder_channels_i
	  section.data(2).logicalSrcIdx = 24;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadAnalog_channels
	  section.data(3).logicalSrcIdx = 25;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteAnalog_channels
	  section.data(4).logicalSrcIdx = 26;
	  section.data(4).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigitalTimebase_channel
	  section.data(5).logicalSrcIdx = 27;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigital_channels
	  section.data(6).logicalSrcIdx = 28;
	  section.data(6).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadDigital_channels
	  section.data(7).logicalSrcIdx = 29;
	  section.data(7).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadDigital_channels_p
	  section.data(8).logicalSrcIdx = 30;
	  section.data(8).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigitalTimebase_samples
	  section.data(9).logicalSrcIdx = 31;
	  section.data(9).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_P.StopwithMessage2_message_icon
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.StopwithMessage3_message_icon
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 34;
      section.data(34)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.TSamp_WtEt
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.TSamp_WtEt_j
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_P.Gain_Gain
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteTimeIntegrator_gainval
	  section.data(4).logicalSrcIdx = 39;
	  section.data(4).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteTimeIntegrator_IC
	  section.data(5).logicalSrcIdx = 40;
	  section.data(5).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_P.TSamp_WtEt_b
	  section.data(6).logicalSrcIdx = 41;
	  section.data(6).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_P.Gain2_Gain
	  section.data(7).logicalSrcIdx = 42;
	  section.data(7).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_P.TSamp_WtEt_h
	  section.data(8).logicalSrcIdx = 43;
	  section.data(8).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_1DOF_P.Gain_Gain_l
	  section.data(9).logicalSrcIdx = 44;
	  section.data(9).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteTimeIntegrator_gainva_m
	  section.data(10).logicalSrcIdx = 45;
	  section.data(10).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_1DOF_P.DiscreteTimeIntegrator_IC_l
	  section.data(11).logicalSrcIdx = 46;
	  section.data(11).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_1DOF_P.TSamp_WtEt_n
	  section.data(12).logicalSrcIdx = 47;
	  section.data(12).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_P.Gain2_Gain_f
	  section.data(13).logicalSrcIdx = 48;
	  section.data(13).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_1DOF_P.PulseGenerator_Amp
	  section.data(14).logicalSrcIdx = 49;
	  section.data(14).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_1DOF_P.PulseGenerator_Period
	  section.data(15).logicalSrcIdx = 50;
	  section.data(15).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_P.PulseGenerator_Duty
	  section.data(16).logicalSrcIdx = 51;
	  section.data(16).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_1DOF_P.PulseGenerator_PhaseDelay
	  section.data(17).logicalSrcIdx = 52;
	  section.data(17).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_OOTerminate
	  section.data(18).logicalSrcIdx = 53;
	  section.data(18).dtTransOffset = 19;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_OOExit
	  section.data(19).logicalSrcIdx = 54;
	  section.data(19).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_OOStart
	  section.data(20).logicalSrcIdx = 55;
	  section.data(20).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_OOEnter
	  section.data(21).logicalSrcIdx = 56;
	  section.data(21).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOFinal
	  section.data(22).logicalSrcIdx = 57;
	  section.data(22).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POFinal
	  section.data(23).logicalSrcIdx = 58;
	  section.data(23).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AIHigh
	  section.data(24).logicalSrcIdx = 59;
	  section.data(24).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AILow
	  section.data(25).logicalSrcIdx = 60;
	  section.data(25).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOHigh
	  section.data(26).logicalSrcIdx = 61;
	  section.data(26).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOLow
	  section.data(27).logicalSrcIdx = 62;
	  section.data(27).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOInitial
	  section.data(28).logicalSrcIdx = 63;
	  section.data(28).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOWatchdog
	  section.data(29).logicalSrcIdx = 64;
	  section.data(29).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIFrequency
	  section.data(30).logicalSrcIdx = 65;
	  section.data(30).dtTransOffset = 31;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POFrequency
	  section.data(31).logicalSrcIdx = 66;
	  section.data(31).dtTransOffset = 32;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POInitial
	  section.data(32).logicalSrcIdx = 67;
	  section.data(32).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_1DOF_P.EnableActiveLow_Value
	  section.data(33).logicalSrcIdx = 68;
	  section.data(33).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_1DOF_P.MasterEnableActiveHigh_Value
	  section.data(34).logicalSrcIdx = 69;
	  section.data(34).dtTransOffset = 36;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKModes
	  section.data(2).logicalSrcIdx = 71;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOWatchdog
	  section.data(3).logicalSrcIdx = 72;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIInitial
	  section.data(4).logicalSrcIdx = 73;
	  section.data(4).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POModes
	  section.data(5).logicalSrcIdx = 74;
	  section.data(5).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 76;
	  section.data(2).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DIChannels
	  section.data(3).logicalSrcIdx = 77;
	  section.data(3).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOChannels
	  section.data(4).logicalSrcIdx = 78;
	  section.data(4).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIChannels
	  section.data(5).logicalSrcIdx = 79;
	  section.data(5).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIQuadrature
	  section.data(6).logicalSrcIdx = 80;
	  section.data(6).dtTransOffset = 41;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 47;
      section.data(47)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.HILReadEncoder_Active
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadEncoder_Active_g
	  section.data(2).logicalSrcIdx = 82;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadAnalog_Active
	  section.data(3).logicalSrcIdx = 83;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteAnalog_Active
	  section.data(4).logicalSrcIdx = 84;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_Active
	  section.data(5).logicalSrcIdx = 85;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOTerminate
	  section.data(6).logicalSrcIdx = 86;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOExit
	  section.data(7).logicalSrcIdx = 87;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOTerminate
	  section.data(8).logicalSrcIdx = 88;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOExit
	  section.data(9).logicalSrcIdx = 89;
	  section.data(9).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POTerminate
	  section.data(10).logicalSrcIdx = 90;
	  section.data(10).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POExit
	  section.data(11).logicalSrcIdx = 91;
	  section.data(11).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKPStart
	  section.data(12).logicalSrcIdx = 92;
	  section.data(12).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKPEnter
	  section.data(13).logicalSrcIdx = 93;
	  section.data(13).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKStart
	  section.data(14).logicalSrcIdx = 94;
	  section.data(14).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_CKEnter
	  section.data(15).logicalSrcIdx = 95;
	  section.data(15).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AIPStart
	  section.data(16).logicalSrcIdx = 96;
	  section.data(16).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AIPEnter
	  section.data(17).logicalSrcIdx = 97;
	  section.data(17).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOPStart
	  section.data(18).logicalSrcIdx = 98;
	  section.data(18).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOPEnter
	  section.data(19).logicalSrcIdx = 99;
	  section.data(19).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOStart
	  section.data(20).logicalSrcIdx = 100;
	  section.data(20).dtTransOffset = 19;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOEnter
	  section.data(21).logicalSrcIdx = 101;
	  section.data(21).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_AOReset
	  section.data(22).logicalSrcIdx = 102;
	  section.data(22).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOPStart
	  section.data(23).logicalSrcIdx = 103;
	  section.data(23).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOPEnter
	  section.data(24).logicalSrcIdx = 104;
	  section.data(24).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOStart
	  section.data(25).logicalSrcIdx = 105;
	  section.data(25).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOEnter
	  section.data(26).logicalSrcIdx = 106;
	  section.data(26).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOReset
	  section.data(27).logicalSrcIdx = 107;
	  section.data(27).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIPStart
	  section.data(28).logicalSrcIdx = 108;
	  section.data(28).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIPEnter
	  section.data(29).logicalSrcIdx = 109;
	  section.data(29).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIStart
	  section.data(30).logicalSrcIdx = 110;
	  section.data(30).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_EIEnter
	  section.data(31).logicalSrcIdx = 111;
	  section.data(31).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POPStart
	  section.data(32).logicalSrcIdx = 112;
	  section.data(32).dtTransOffset = 31;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POPEnter
	  section.data(33).logicalSrcIdx = 113;
	  section.data(33).dtTransOffset = 32;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POStart
	  section.data(34).logicalSrcIdx = 114;
	  section.data(34).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POEnter
	  section.data(35).logicalSrcIdx = 115;
	  section.data(35).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_POReset
	  section.data(36).logicalSrcIdx = 116;
	  section.data(36).dtTransOffset = 35;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_OOReset
	  section.data(37).logicalSrcIdx = 117;
	  section.data(37).dtTransOffset = 36;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOFinal
	  section.data(38).logicalSrcIdx = 118;
	  section.data(38).dtTransOffset = 37;
	
	  ;% DATA_COLLECTION_1DOF_P.HILInitialize_DOInitial
	  section.data(39).logicalSrcIdx = 119;
	  section.data(39).dtTransOffset = 38;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigitalTimebase_Active
	  section.data(40).logicalSrcIdx = 120;
	  section.data(40).dtTransOffset = 39;
	
	  ;% DATA_COLLECTION_1DOF_P.HILWriteDigital_Active
	  section.data(41).logicalSrcIdx = 121;
	  section.data(41).dtTransOffset = 40;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadDigital_Active
	  section.data(42).logicalSrcIdx = 122;
	  section.data(42).dtTransOffset = 41;
	
	  ;% DATA_COLLECTION_1DOF_P.HILReadDigital_Active_h
	  section.data(43).logicalSrcIdx = 123;
	  section.data(43).dtTransOffset = 42;
	
	  ;% DATA_COLLECTION_1DOF_P.Constant_Value
	  section.data(44).logicalSrcIdx = 124;
	  section.data(44).dtTransOffset = 43;
	
	  ;% DATA_COLLECTION_1DOF_P.Constant_Value_i
	  section.data(45).logicalSrcIdx = 125;
	  section.data(45).dtTransOffset = 44;
	
	  ;% DATA_COLLECTION_1DOF_P.Constant_Value_e
	  section.data(46).logicalSrcIdx = 126;
	  section.data(46).dtTransOffset = 45;
	
	  ;% DATA_COLLECTION_1DOF_P.Constant_Value_d
	  section.data(47).logicalSrcIdx = 127;
	  section.data(47).dtTransOffset = 46;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_P.ManualSwitch3_CurrentSetting
	  section.data(1).logicalSrcIdx = 128;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_P.ManualSwitch2_CurrentSetting
	  section.data(2).logicalSrcIdx = 129;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 130;
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
    ;% Auto data (DATA_COLLECTION_1DOF_B)
    ;%
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_B.TSamp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_B.TSamp_o
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_B.VectorConcatenate1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_B.FromWorkspace3
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_B.Sum2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_B.TSamp_n
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_B.Torquetocurrent
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_B.TSamp_c
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_1DOF_B.Current
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_1DOF_B.Sum1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_B.TSamp_a
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_1DOF_B.Saturation
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_1DOF_B.VectorConcatenate
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_B.HILReadDigital_o1
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_1DOF_B.HILReadDigital_o2
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_1DOF_B.HILReadDigital_o3
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 22;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 19;
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
    nTotSects     = 8;
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
    ;% Auto data (DATA_COLLECTION_1DOF_DW)
    ;%
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.UD_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.UD_DSTATE_p
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_DW.UD_DSTATE_d
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_DW.UD_DSTATE_e
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_DW.DiscreteTimeIntegrator_DSTATE_a
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_DW.UD_DSTATE_m
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadAnalog_Buffer
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_AIMinimums
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_AIMaximums
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_AOMinimums
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_AOMaximums
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_AOVoltages
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 42;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_FilterFrequency
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 50;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteDigitalTimebase_Task
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadEncoder_PWORK_h
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace3_PWORK.TimePtr
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace2_PWORK.TimePtr
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace1_PWORK.TimePtr
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadAnalog_PWORK
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteAnalog_PWORK
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_1DOF_DW.Irefshoulder2_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_1DOF_DW.Ishoulder1_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_1DOF_DW.ToWorkspace_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_1DOF_DW.Vshoulder_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_1DOF_DW.theta1_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_1DOF_DW.theta2_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteDigital_PWORK
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadDigital_PWORK
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadDigital_PWORK_o
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILReadEncoder_Buffer
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadEncoder_Buffer_a
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_1DOF_DW.clockTickCounter
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_DOStates
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_QuadratureModes
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_InitialEICounts
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 22;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace3_IWORK.PrevIndex
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace2_IWORK.PrevIndex
	  section.data(2).logicalSrcIdx = 39;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_DW.FromWorkspace1_IWORK.PrevIndex
	  section.data(3).logicalSrcIdx = 40;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteDigitalTimebase_Started
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteDigitalTimebase_Buffer
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILWriteDigital_Buffer
	  section.data(2).logicalSrcIdx = 44;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadDigital_Buffer
	  section.data(3).logicalSrcIdx = 45;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_1DOF_DW.HILReadDigital_Buffer_c
	  section.data(4).logicalSrcIdx = 46;
	  section.data(4).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
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


  targMap.checksum0 = 3151836095;
  targMap.checksum1 = 576390926;
  targMap.checksum2 = 3453296544;
  targMap.checksum3 = 2426334978;

