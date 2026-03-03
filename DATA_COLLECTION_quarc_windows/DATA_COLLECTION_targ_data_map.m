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
    ;% Auto data (DATA_COLLECTION_P)
    ;%
      section.nData     = 34;
      section.data(34)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.KE_D1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.KE_D2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_P.Kt1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.Kt2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_P.L1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_P.L2
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.LIMIT_SWITCHES_ENABLE
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_P.R1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_P.R2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_P.a1_hat
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_P.a2_hat
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_P.b1_hat
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_P.b2_hat
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_P.b_hat
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_P.fc1_hat
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_P.fc2_hat
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_P.i_sat1
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_P.i_sat2
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_P.ke1
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_P.ke2
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% DATA_COLLECTION_P.ki1
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_P.ki_traj
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_P.kp1
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_P.kp2
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_P.v_eps_hat
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative3_ICPrevScale
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative_ICPrevScaled
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative_ICPrevScal_k
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative2_ICPrevScale
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 31;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative1_ICPrevScale
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 32;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative3_ICPrevSca_i
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative_ICPrevScal_l
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative2_ICPrevSca_n
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 35;
	
	  ;% DATA_COLLECTION_P.DiscreteDerivative1_ICPrevSca_c
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 36;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.HILWriteDigitalTimebase_clock
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.HILReadEncoder_channels
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.HILReadEncoder_channels_d
	  section.data(2).logicalSrcIdx = 36;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.HILReadAnalog_channels
	  section.data(3).logicalSrcIdx = 37;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_P.HILWriteAnalog_channels
	  section.data(4).logicalSrcIdx = 38;
	  section.data(4).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.HILReadEncoder_channels_g
	  section.data(5).logicalSrcIdx = 39;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_P.HILReadAnalog_channels_e
	  section.data(6).logicalSrcIdx = 40;
	  section.data(6).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_P.HILWriteAnalog_channels_h
	  section.data(7).logicalSrcIdx = 41;
	  section.data(7).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_P.HILWriteDigitalTimebase_channel
	  section.data(8).logicalSrcIdx = 42;
	  section.data(8).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_P.HILWriteDigital_channels
	  section.data(9).logicalSrcIdx = 43;
	  section.data(9).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_P.HILReadDigital_channels
	  section.data(10).logicalSrcIdx = 44;
	  section.data(10).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_P.HILReadDigital_channels_j
	  section.data(11).logicalSrcIdx = 45;
	  section.data(11).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_P.HILWriteDigitalTimebase_samples
	  section.data(12).logicalSrcIdx = 46;
	  section.data(12).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 48;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_P.StopwithMessage2_message_icon
	  section.data(3).logicalSrcIdx = 49;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.StopwithMessage3_message_icon
	  section.data(4).logicalSrcIdx = 50;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 43;
      section.data(43)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.TSamp_WtEt
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_p
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_P.UnitDelay_InitialCondition
	  section.data(3).logicalSrcIdx = 53;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.Gain_Gain
	  section.data(4).logicalSrcIdx = 54;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_gainval
	  section.data(5).logicalSrcIdx = 55;
	  section.data(5).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_IC
	  section.data(6).logicalSrcIdx = 56;
	  section.data(6).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_e
	  section.data(7).logicalSrcIdx = 57;
	  section.data(7).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_P.UnitDelay1_InitialCondition
	  section.data(8).logicalSrcIdx = 58;
	  section.data(8).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_P.Gain2_Gain
	  section.data(9).logicalSrcIdx = 59;
	  section.data(9).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_ei
	  section.data(10).logicalSrcIdx = 60;
	  section.data(10).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_gainva_p
	  section.data(11).logicalSrcIdx = 61;
	  section.data(11).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_IC_i
	  section.data(12).logicalSrcIdx = 62;
	  section.data(12).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_a
	  section.data(13).logicalSrcIdx = 63;
	  section.data(13).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_P.Gain2_Gain_c
	  section.data(14).logicalSrcIdx = 64;
	  section.data(14).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_h
	  section.data(15).logicalSrcIdx = 65;
	  section.data(15).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_l
	  section.data(16).logicalSrcIdx = 66;
	  section.data(16).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_g
	  section.data(17).logicalSrcIdx = 67;
	  section.data(17).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_gainva_k
	  section.data(18).logicalSrcIdx = 68;
	  section.data(18).dtTransOffset = 19;
	
	  ;% DATA_COLLECTION_P.DiscreteTimeIntegrator_IC_l
	  section.data(19).logicalSrcIdx = 69;
	  section.data(19).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_P.TSamp_WtEt_pz
	  section.data(20).logicalSrcIdx = 70;
	  section.data(20).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_P.Gain2_Gain_l
	  section.data(21).logicalSrcIdx = 71;
	  section.data(21).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_P.UnitDelay2_InitialCondition
	  section.data(22).logicalSrcIdx = 72;
	  section.data(22).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_P.PulseGenerator_Amp
	  section.data(23).logicalSrcIdx = 73;
	  section.data(23).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_P.PulseGenerator_Period
	  section.data(24).logicalSrcIdx = 74;
	  section.data(24).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_P.PulseGenerator_Duty
	  section.data(25).logicalSrcIdx = 75;
	  section.data(25).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_P.PulseGenerator_PhaseDelay
	  section.data(26).logicalSrcIdx = 76;
	  section.data(26).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_P.HILInitialize_OOTerminate
	  section.data(27).logicalSrcIdx = 77;
	  section.data(27).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_P.HILInitialize_OOExit
	  section.data(28).logicalSrcIdx = 78;
	  section.data(28).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_P.HILInitialize_OOStart
	  section.data(29).logicalSrcIdx = 79;
	  section.data(29).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_P.HILInitialize_OOEnter
	  section.data(30).logicalSrcIdx = 80;
	  section.data(30).dtTransOffset = 31;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOFinal
	  section.data(31).logicalSrcIdx = 81;
	  section.data(31).dtTransOffset = 32;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POFinal
	  section.data(32).logicalSrcIdx = 82;
	  section.data(32).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AIHigh
	  section.data(33).logicalSrcIdx = 83;
	  section.data(33).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AILow
	  section.data(34).logicalSrcIdx = 84;
	  section.data(34).dtTransOffset = 35;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOHigh
	  section.data(35).logicalSrcIdx = 85;
	  section.data(35).dtTransOffset = 36;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOLow
	  section.data(36).logicalSrcIdx = 86;
	  section.data(36).dtTransOffset = 37;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOInitial
	  section.data(37).logicalSrcIdx = 87;
	  section.data(37).dtTransOffset = 38;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOWatchdog
	  section.data(38).logicalSrcIdx = 88;
	  section.data(38).dtTransOffset = 39;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIFrequency
	  section.data(39).logicalSrcIdx = 89;
	  section.data(39).dtTransOffset = 40;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POFrequency
	  section.data(40).logicalSrcIdx = 90;
	  section.data(40).dtTransOffset = 41;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POInitial
	  section.data(41).logicalSrcIdx = 91;
	  section.data(41).dtTransOffset = 42;
	
	  ;% DATA_COLLECTION_P.EnableActiveLow_Value
	  section.data(42).logicalSrcIdx = 92;
	  section.data(42).dtTransOffset = 43;
	
	  ;% DATA_COLLECTION_P.MasterEnableActiveHigh_Value
	  section.data(43).logicalSrcIdx = 93;
	  section.data(43).dtTransOffset = 45;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 94;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.HILInitialize_CKModes
	  section.data(2).logicalSrcIdx = 95;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOWatchdog
	  section.data(3).logicalSrcIdx = 96;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIInitial
	  section.data(4).logicalSrcIdx = 97;
	  section.data(4).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POModes
	  section.data(5).logicalSrcIdx = 98;
	  section.data(5).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 99;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 100;
	  section.data(2).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DIChannels
	  section.data(3).logicalSrcIdx = 101;
	  section.data(3).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOChannels
	  section.data(4).logicalSrcIdx = 102;
	  section.data(4).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIChannels
	  section.data(5).logicalSrcIdx = 103;
	  section.data(5).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIQuadrature
	  section.data(6).logicalSrcIdx = 104;
	  section.data(6).dtTransOffset = 41;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 50;
      section.data(50)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.HILReadEncoder_Active
	  section.data(1).logicalSrcIdx = 105;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.HILReadEncoder_Active_a
	  section.data(2).logicalSrcIdx = 106;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_P.HILReadAnalog_Active
	  section.data(3).logicalSrcIdx = 107;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.HILWriteAnalog_Active
	  section.data(4).logicalSrcIdx = 108;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_P.HILReadEncoder_Active_j
	  section.data(5).logicalSrcIdx = 109;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_P.HILReadAnalog_Active_l
	  section.data(6).logicalSrcIdx = 110;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.HILWriteAnalog_Active_l
	  section.data(7).logicalSrcIdx = 111;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_P.HILInitialize_Active
	  section.data(8).logicalSrcIdx = 112;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOTerminate
	  section.data(9).logicalSrcIdx = 113;
	  section.data(9).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOExit
	  section.data(10).logicalSrcIdx = 114;
	  section.data(10).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOTerminate
	  section.data(11).logicalSrcIdx = 115;
	  section.data(11).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOExit
	  section.data(12).logicalSrcIdx = 116;
	  section.data(12).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POTerminate
	  section.data(13).logicalSrcIdx = 117;
	  section.data(13).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POExit
	  section.data(14).logicalSrcIdx = 118;
	  section.data(14).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_P.HILInitialize_CKPStart
	  section.data(15).logicalSrcIdx = 119;
	  section.data(15).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_P.HILInitialize_CKPEnter
	  section.data(16).logicalSrcIdx = 120;
	  section.data(16).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_P.HILInitialize_CKStart
	  section.data(17).logicalSrcIdx = 121;
	  section.data(17).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_P.HILInitialize_CKEnter
	  section.data(18).logicalSrcIdx = 122;
	  section.data(18).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AIPStart
	  section.data(19).logicalSrcIdx = 123;
	  section.data(19).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AIPEnter
	  section.data(20).logicalSrcIdx = 124;
	  section.data(20).dtTransOffset = 19;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOPStart
	  section.data(21).logicalSrcIdx = 125;
	  section.data(21).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOPEnter
	  section.data(22).logicalSrcIdx = 126;
	  section.data(22).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOStart
	  section.data(23).logicalSrcIdx = 127;
	  section.data(23).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOEnter
	  section.data(24).logicalSrcIdx = 128;
	  section.data(24).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_P.HILInitialize_AOReset
	  section.data(25).logicalSrcIdx = 129;
	  section.data(25).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOPStart
	  section.data(26).logicalSrcIdx = 130;
	  section.data(26).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOPEnter
	  section.data(27).logicalSrcIdx = 131;
	  section.data(27).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOStart
	  section.data(28).logicalSrcIdx = 132;
	  section.data(28).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOEnter
	  section.data(29).logicalSrcIdx = 133;
	  section.data(29).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOReset
	  section.data(30).logicalSrcIdx = 134;
	  section.data(30).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIPStart
	  section.data(31).logicalSrcIdx = 135;
	  section.data(31).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIPEnter
	  section.data(32).logicalSrcIdx = 136;
	  section.data(32).dtTransOffset = 31;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIStart
	  section.data(33).logicalSrcIdx = 137;
	  section.data(33).dtTransOffset = 32;
	
	  ;% DATA_COLLECTION_P.HILInitialize_EIEnter
	  section.data(34).logicalSrcIdx = 138;
	  section.data(34).dtTransOffset = 33;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POPStart
	  section.data(35).logicalSrcIdx = 139;
	  section.data(35).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POPEnter
	  section.data(36).logicalSrcIdx = 140;
	  section.data(36).dtTransOffset = 35;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POStart
	  section.data(37).logicalSrcIdx = 141;
	  section.data(37).dtTransOffset = 36;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POEnter
	  section.data(38).logicalSrcIdx = 142;
	  section.data(38).dtTransOffset = 37;
	
	  ;% DATA_COLLECTION_P.HILInitialize_POReset
	  section.data(39).logicalSrcIdx = 143;
	  section.data(39).dtTransOffset = 38;
	
	  ;% DATA_COLLECTION_P.HILInitialize_OOReset
	  section.data(40).logicalSrcIdx = 144;
	  section.data(40).dtTransOffset = 39;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOFinal
	  section.data(41).logicalSrcIdx = 145;
	  section.data(41).dtTransOffset = 40;
	
	  ;% DATA_COLLECTION_P.HILInitialize_DOInitial
	  section.data(42).logicalSrcIdx = 146;
	  section.data(42).dtTransOffset = 41;
	
	  ;% DATA_COLLECTION_P.HILWriteDigitalTimebase_Active
	  section.data(43).logicalSrcIdx = 147;
	  section.data(43).dtTransOffset = 42;
	
	  ;% DATA_COLLECTION_P.HILWriteDigital_Active
	  section.data(44).logicalSrcIdx = 148;
	  section.data(44).dtTransOffset = 43;
	
	  ;% DATA_COLLECTION_P.HILReadDigital_Active
	  section.data(45).logicalSrcIdx = 149;
	  section.data(45).dtTransOffset = 44;
	
	  ;% DATA_COLLECTION_P.HILReadDigital_Active_c
	  section.data(46).logicalSrcIdx = 150;
	  section.data(46).dtTransOffset = 45;
	
	  ;% DATA_COLLECTION_P.Constant_Value
	  section.data(47).logicalSrcIdx = 151;
	  section.data(47).dtTransOffset = 46;
	
	  ;% DATA_COLLECTION_P.Constant_Value_h
	  section.data(48).logicalSrcIdx = 152;
	  section.data(48).dtTransOffset = 47;
	
	  ;% DATA_COLLECTION_P.Constant_Value_m
	  section.data(49).logicalSrcIdx = 153;
	  section.data(49).dtTransOffset = 48;
	
	  ;% DATA_COLLECTION_P.Constant_Value_i
	  section.data(50).logicalSrcIdx = 154;
	  section.data(50).dtTransOffset = 49;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_P.ManualSwitch3_CurrentSetting
	  section.data(1).logicalSrcIdx = 155;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_P.ManualSwitch2_CurrentSetting
	  section.data(2).logicalSrcIdx = 156;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 157;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_P.ManualSwitch4_CurrentSetting
	  section.data(4).logicalSrcIdx = 158;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_P.ManualSwitch3_CurrentSetting_n
	  section.data(5).logicalSrcIdx = 159;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_P.ManualSwitch2_CurrentSetting_j
	  section.data(6).logicalSrcIdx = 160;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_P.ManualSwitch1_CurrentSetting_k
	  section.data(7).logicalSrcIdx = 161;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_P.ManualSwitch4_CurrentSetting_i
	  section.data(8).logicalSrcIdx = 162;
	  section.data(8).dtTransOffset = 7;
	
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
    ;% Auto data (DATA_COLLECTION_B)
    ;%
      section.nData     = 27;
      section.data(27)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_B.TSamp
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_B.TSamp_d
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_B.VectorConcatenate1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_B.Sum2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_B.TSamp_i
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_B.FromWorkspace3
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_B.FromWorkspace1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_B.Torquetocurrent
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_B.TSamp_f
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_B.Current
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_B.Sum1
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_B.TSamp_p
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_B.Saturation
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_B.VectorConcatenate
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_B.TSamp_g
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_B.TSamp_b
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_B.Torquetocurrent_k
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 24;
	
	  ;% DATA_COLLECTION_B.TSamp_j
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 25;
	
	  ;% DATA_COLLECTION_B.Current_b
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 26;
	
	  ;% DATA_COLLECTION_B.Sum1_d
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 27;
	
	  ;% DATA_COLLECTION_B.TSamp_bl
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 28;
	
	  ;% DATA_COLLECTION_B.Saturation_m
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 29;
	
	  ;% DATA_COLLECTION_B.VectorConcatenate_d
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_B.UnitDelay2
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 34;
	
	  ;% DATA_COLLECTION_B.HILReadDigital_o1
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 36;
	
	  ;% DATA_COLLECTION_B.HILReadDigital_o2
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 37;
	
	  ;% DATA_COLLECTION_B.HILReadDigital_o3
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 29;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 30;
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
    ;% Auto data (DATA_COLLECTION_DW)
    ;%
      section.nData     = 23;
      section.data(23)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.UD_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_g
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_DW.UnitDelay_DSTATE
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_e
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_DW.UnitDelay1_DSTATE
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_g1
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_p
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_j
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_h
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_i
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_er
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 15;
	
	  ;% DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_a
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_DW.UD_DSTATE_d
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_DW.UnitDelay2_DSTATE
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_DW.HILReadAnalog_Buffer
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_DW.HILReadAnalog_Buffer_n
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 21;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_AIMinimums
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_AIMaximums
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 30;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_AOMinimums
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 38;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_AOMaximums
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 46;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_AOVoltages
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 54;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_FilterFrequency
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 62;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILWriteDigitalTimebase_Task
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.HILReadEncoder_PWORK_g
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_DW.FromWorkspace3_PWORK.TimePtr
	  section.data(3).logicalSrcIdx = 27;
	  section.data(3).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_DW.FromWorkspace2_PWORK.TimePtr
	  section.data(4).logicalSrcIdx = 28;
	  section.data(4).dtTransOffset = 3;
	
	  ;% DATA_COLLECTION_DW.FromWorkspace1_PWORK.TimePtr
	  section.data(5).logicalSrcIdx = 29;
	  section.data(5).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_DW.HILReadAnalog_PWORK
	  section.data(6).logicalSrcIdx = 30;
	  section.data(6).dtTransOffset = 5;
	
	  ;% DATA_COLLECTION_DW.HILWriteAnalog_PWORK
	  section.data(7).logicalSrcIdx = 31;
	  section.data(7).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_DW.Ielbow_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 32;
	  section.data(8).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_DW.ToWorkspace_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 33;
	  section.data(9).dtTransOffset = 9;
	
	  ;% DATA_COLLECTION_DW.Velbow_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 34;
	  section.data(10).dtTransOffset = 10;
	
	  ;% DATA_COLLECTION_DW.HILReadEncoder_PWORK_k
	  section.data(11).logicalSrcIdx = 35;
	  section.data(11).dtTransOffset = 11;
	
	  ;% DATA_COLLECTION_DW.HILReadAnalog_PWORK_a
	  section.data(12).logicalSrcIdx = 36;
	  section.data(12).dtTransOffset = 12;
	
	  ;% DATA_COLLECTION_DW.HILWriteAnalog_PWORK_g
	  section.data(13).logicalSrcIdx = 37;
	  section.data(13).dtTransOffset = 13;
	
	  ;% DATA_COLLECTION_DW.Ishoulder1_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 38;
	  section.data(14).dtTransOffset = 14;
	
	  ;% DATA_COLLECTION_DW.ToWorkspace_PWORK_l.LoggedData
	  section.data(15).logicalSrcIdx = 39;
	  section.data(15).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_DW.Vshoulder_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 40;
	  section.data(16).dtTransOffset = 17;
	
	  ;% DATA_COLLECTION_DW.theta1_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 41;
	  section.data(17).dtTransOffset = 18;
	
	  ;% DATA_COLLECTION_DW.theta2_PWORK.LoggedData
	  section.data(18).logicalSrcIdx = 42;
	  section.data(18).dtTransOffset = 20;
	
	  ;% DATA_COLLECTION_DW.HILWriteDigital_PWORK
	  section.data(19).logicalSrcIdx = 43;
	  section.data(19).dtTransOffset = 22;
	
	  ;% DATA_COLLECTION_DW.HILReadDigital_PWORK
	  section.data(20).logicalSrcIdx = 44;
	  section.data(20).dtTransOffset = 23;
	
	  ;% DATA_COLLECTION_DW.HILReadDigital_PWORK_h
	  section.data(21).logicalSrcIdx = 45;
	  section.data(21).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILReadEncoder_Buffer
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.HILReadEncoder_Buffer_a
	  section.data(2).logicalSrcIdx = 47;
	  section.data(2).dtTransOffset = 2;
	
	  ;% DATA_COLLECTION_DW.HILReadEncoder_Buffer_d
	  section.data(3).logicalSrcIdx = 48;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_DW.clockTickCounter
	  section.data(4).logicalSrcIdx = 49;
	  section.data(4).dtTransOffset = 6;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_DOStates
	  section.data(5).logicalSrcIdx = 50;
	  section.data(5).dtTransOffset = 7;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_QuadratureModes
	  section.data(6).logicalSrcIdx = 51;
	  section.data(6).dtTransOffset = 16;
	
	  ;% DATA_COLLECTION_DW.HILInitialize_InitialEICounts
	  section.data(7).logicalSrcIdx = 52;
	  section.data(7).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.FromWorkspace3_IWORK.PrevIndex
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.FromWorkspace2_IWORK.PrevIndex
	  section.data(2).logicalSrcIdx = 54;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_DW.FromWorkspace1_IWORK.PrevIndex
	  section.data(3).logicalSrcIdx = 55;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.HILWriteDigitalTimebase_Started
	  section.data(2).logicalSrcIdx = 57;
	  section.data(2).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% DATA_COLLECTION_DW.HILWriteDigitalTimebase_Buffer
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
	  ;% DATA_COLLECTION_DW.HILWriteDigital_Buffer
	  section.data(2).logicalSrcIdx = 59;
	  section.data(2).dtTransOffset = 1;
	
	  ;% DATA_COLLECTION_DW.HILReadDigital_Buffer
	  section.data(3).logicalSrcIdx = 60;
	  section.data(3).dtTransOffset = 4;
	
	  ;% DATA_COLLECTION_DW.HILReadDigital_Buffer_g
	  section.data(4).logicalSrcIdx = 61;
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


  targMap.checksum0 = 3187002445;
  targMap.checksum1 = 388937937;
  targMap.checksum2 = 2328183639;
  targMap.checksum3 = 1541979293;

