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
    ;% Auto data (TRACKING_CONTROL_RasconIET_P)
    ;%
      section.nData     = 30;
      section.data(30)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.KE_D1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.KE_D2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Kt1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Kt2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_P.L1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.L2
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.LIMIT_SWITCHES_ENABLE
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_P.R1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_P.R2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_P.a1_hat
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_P.a2_hat
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_P.b1_hat
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_P.b2_hat
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_P.b_hat
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_P.dt
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_P.i_sat1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_P.i_sat2
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ke1
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ke2
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ki1
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_P.kp1
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_P.kp2
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative3_ICPrevScale
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative_ICPrevScaled
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative2_ICPrevScale
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative1_ICPrevScale
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative3_ICPrevSca_k
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative_ICPrevScal_n
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative2_ICPrevSca_b
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteDerivative1_ICPrevSca_n
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigitalTimebase_clock
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_channels
	  section.data(1).logicalSrcIdx = 31;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_channels_n
	  section.data(2).logicalSrcIdx = 32;
	  section.data(2).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadAnalog_channels
	  section.data(3).logicalSrcIdx = 33;
	  section.data(3).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteAnalog_channels
	  section.data(4).logicalSrcIdx = 34;
	  section.data(4).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_channels_l
	  section.data(5).logicalSrcIdx = 35;
	  section.data(5).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadAnalog_channels_b
	  section.data(6).logicalSrcIdx = 36;
	  section.data(6).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteAnalog_channels_a
	  section.data(7).logicalSrcIdx = 37;
	  section.data(7).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigitalTimebase_channel
	  section.data(8).logicalSrcIdx = 38;
	  section.data(8).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigital_channels
	  section.data(9).logicalSrcIdx = 39;
	  section.data(9).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadDigital_channels
	  section.data(10).logicalSrcIdx = 40;
	  section.data(10).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadDigital_channels_p
	  section.data(11).logicalSrcIdx = 41;
	  section.data(11).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigitalTimebase_samples
	  section.data(12).logicalSrcIdx = 42;
	  section.data(12).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 44;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_P.StopwithMessage2_message_icon
	  section.data(3).logicalSrcIdx = 45;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.StopwithMessage3_message_icon
	  section.data(4).logicalSrcIdx = 46;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 43;
      section.data(43)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay2_InitialCondition
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay3_InitialCondition
	  section.data(2).logicalSrcIdx = 48;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay1_InitialCondition
	  section.data(3).logicalSrcIdx = 49;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay_InitialCondition
	  section.data(4).logicalSrcIdx = 50;
	  section.data(4).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant10_Value
	  section.data(5).logicalSrcIdx = 51;
	  section.data(5).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant11_Value
	  section.data(6).logicalSrcIdx = 52;
	  section.data(6).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay4_InitialCondition
	  section.data(7).logicalSrcIdx = 53;
	  section.data(7).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_P.UnitDelay5_InitialCondition
	  section.data(8).logicalSrcIdx = 54;
	  section.data(8).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt
	  section.data(9).logicalSrcIdx = 55;
	  section.data(9).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_p
	  section.data(10).logicalSrcIdx = 56;
	  section.data(10).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_i
	  section.data(11).logicalSrcIdx = 57;
	  section.data(11).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteTimeIntegrator_gainval
	  section.data(12).logicalSrcIdx = 58;
	  section.data(12).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteTimeIntegrator_IC
	  section.data(13).logicalSrcIdx = 59;
	  section.data(13).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_o
	  section.data(14).logicalSrcIdx = 60;
	  section.data(14).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Gain2_Gain
	  section.data(15).logicalSrcIdx = 61;
	  section.data(15).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_d
	  section.data(16).logicalSrcIdx = 62;
	  section.data(16).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_m
	  section.data(17).logicalSrcIdx = 63;
	  section.data(17).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_c
	  section.data(18).logicalSrcIdx = 64;
	  section.data(18).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteTimeIntegrator_gainva_p
	  section.data(19).logicalSrcIdx = 65;
	  section.data(19).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_P.DiscreteTimeIntegrator_IC_m
	  section.data(20).logicalSrcIdx = 66;
	  section.data(20).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_P.TSamp_WtEt_f
	  section.data(21).logicalSrcIdx = 67;
	  section.data(21).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Gain2_Gain_p
	  section.data(22).logicalSrcIdx = 68;
	  section.data(22).dtTransOffset = 21;
	
	  ;% TRACKING_CONTROL_RasconIET_P.PulseGenerator_Amp
	  section.data(23).logicalSrcIdx = 69;
	  section.data(23).dtTransOffset = 22;
	
	  ;% TRACKING_CONTROL_RasconIET_P.PulseGenerator_Period
	  section.data(24).logicalSrcIdx = 70;
	  section.data(24).dtTransOffset = 23;
	
	  ;% TRACKING_CONTROL_RasconIET_P.PulseGenerator_Duty
	  section.data(25).logicalSrcIdx = 71;
	  section.data(25).dtTransOffset = 24;
	
	  ;% TRACKING_CONTROL_RasconIET_P.PulseGenerator_PhaseDelay
	  section.data(26).logicalSrcIdx = 72;
	  section.data(26).dtTransOffset = 25;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_OOTerminate
	  section.data(27).logicalSrcIdx = 73;
	  section.data(27).dtTransOffset = 26;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_OOExit
	  section.data(28).logicalSrcIdx = 74;
	  section.data(28).dtTransOffset = 27;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_OOStart
	  section.data(29).logicalSrcIdx = 75;
	  section.data(29).dtTransOffset = 28;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_OOEnter
	  section.data(30).logicalSrcIdx = 76;
	  section.data(30).dtTransOffset = 29;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOFinal
	  section.data(31).logicalSrcIdx = 77;
	  section.data(31).dtTransOffset = 30;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POFinal
	  section.data(32).logicalSrcIdx = 78;
	  section.data(32).dtTransOffset = 31;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AIHigh
	  section.data(33).logicalSrcIdx = 79;
	  section.data(33).dtTransOffset = 32;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AILow
	  section.data(34).logicalSrcIdx = 80;
	  section.data(34).dtTransOffset = 33;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOHigh
	  section.data(35).logicalSrcIdx = 81;
	  section.data(35).dtTransOffset = 34;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOLow
	  section.data(36).logicalSrcIdx = 82;
	  section.data(36).dtTransOffset = 35;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOInitial
	  section.data(37).logicalSrcIdx = 83;
	  section.data(37).dtTransOffset = 36;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOWatchdog
	  section.data(38).logicalSrcIdx = 84;
	  section.data(38).dtTransOffset = 37;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIFrequency
	  section.data(39).logicalSrcIdx = 85;
	  section.data(39).dtTransOffset = 38;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POFrequency
	  section.data(40).logicalSrcIdx = 86;
	  section.data(40).dtTransOffset = 39;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POInitial
	  section.data(41).logicalSrcIdx = 87;
	  section.data(41).dtTransOffset = 40;
	
	  ;% TRACKING_CONTROL_RasconIET_P.EnableActiveLow_Value
	  section.data(42).logicalSrcIdx = 88;
	  section.data(42).dtTransOffset = 41;
	
	  ;% TRACKING_CONTROL_RasconIET_P.MasterEnableActiveHigh_Value
	  section.data(43).logicalSrcIdx = 89;
	  section.data(43).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 90;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKModes
	  section.data(2).logicalSrcIdx = 91;
	  section.data(2).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOWatchdog
	  section.data(3).logicalSrcIdx = 92;
	  section.data(3).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIInitial
	  section.data(4).logicalSrcIdx = 93;
	  section.data(4).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POModes
	  section.data(5).logicalSrcIdx = 94;
	  section.data(5).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 95;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 96;
	  section.data(2).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DIChannels
	  section.data(3).logicalSrcIdx = 97;
	  section.data(3).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOChannels
	  section.data(4).logicalSrcIdx = 98;
	  section.data(4).dtTransOffset = 24;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIChannels
	  section.data(5).logicalSrcIdx = 99;
	  section.data(5).dtTransOffset = 33;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIQuadrature
	  section.data(6).logicalSrcIdx = 100;
	  section.data(6).dtTransOffset = 41;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 50;
      section.data(50)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_Active
	  section.data(1).logicalSrcIdx = 101;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_Active_l
	  section.data(2).logicalSrcIdx = 102;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadAnalog_Active
	  section.data(3).logicalSrcIdx = 103;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteAnalog_Active
	  section.data(4).logicalSrcIdx = 104;
	  section.data(4).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadEncoder_Active_d
	  section.data(5).logicalSrcIdx = 105;
	  section.data(5).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadAnalog_Active_n
	  section.data(6).logicalSrcIdx = 106;
	  section.data(6).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteAnalog_Active_e
	  section.data(7).logicalSrcIdx = 107;
	  section.data(7).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_Active
	  section.data(8).logicalSrcIdx = 108;
	  section.data(8).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOTerminate
	  section.data(9).logicalSrcIdx = 109;
	  section.data(9).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOExit
	  section.data(10).logicalSrcIdx = 110;
	  section.data(10).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOTerminate
	  section.data(11).logicalSrcIdx = 111;
	  section.data(11).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOExit
	  section.data(12).logicalSrcIdx = 112;
	  section.data(12).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POTerminate
	  section.data(13).logicalSrcIdx = 113;
	  section.data(13).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POExit
	  section.data(14).logicalSrcIdx = 114;
	  section.data(14).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKPStart
	  section.data(15).logicalSrcIdx = 115;
	  section.data(15).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKPEnter
	  section.data(16).logicalSrcIdx = 116;
	  section.data(16).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKStart
	  section.data(17).logicalSrcIdx = 117;
	  section.data(17).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_CKEnter
	  section.data(18).logicalSrcIdx = 118;
	  section.data(18).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AIPStart
	  section.data(19).logicalSrcIdx = 119;
	  section.data(19).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AIPEnter
	  section.data(20).logicalSrcIdx = 120;
	  section.data(20).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOPStart
	  section.data(21).logicalSrcIdx = 121;
	  section.data(21).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOPEnter
	  section.data(22).logicalSrcIdx = 122;
	  section.data(22).dtTransOffset = 21;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOStart
	  section.data(23).logicalSrcIdx = 123;
	  section.data(23).dtTransOffset = 22;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOEnter
	  section.data(24).logicalSrcIdx = 124;
	  section.data(24).dtTransOffset = 23;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_AOReset
	  section.data(25).logicalSrcIdx = 125;
	  section.data(25).dtTransOffset = 24;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOPStart
	  section.data(26).logicalSrcIdx = 126;
	  section.data(26).dtTransOffset = 25;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOPEnter
	  section.data(27).logicalSrcIdx = 127;
	  section.data(27).dtTransOffset = 26;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOStart
	  section.data(28).logicalSrcIdx = 128;
	  section.data(28).dtTransOffset = 27;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOEnter
	  section.data(29).logicalSrcIdx = 129;
	  section.data(29).dtTransOffset = 28;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOReset
	  section.data(30).logicalSrcIdx = 130;
	  section.data(30).dtTransOffset = 29;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIPStart
	  section.data(31).logicalSrcIdx = 131;
	  section.data(31).dtTransOffset = 30;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIPEnter
	  section.data(32).logicalSrcIdx = 132;
	  section.data(32).dtTransOffset = 31;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIStart
	  section.data(33).logicalSrcIdx = 133;
	  section.data(33).dtTransOffset = 32;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_EIEnter
	  section.data(34).logicalSrcIdx = 134;
	  section.data(34).dtTransOffset = 33;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POPStart
	  section.data(35).logicalSrcIdx = 135;
	  section.data(35).dtTransOffset = 34;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POPEnter
	  section.data(36).logicalSrcIdx = 136;
	  section.data(36).dtTransOffset = 35;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POStart
	  section.data(37).logicalSrcIdx = 137;
	  section.data(37).dtTransOffset = 36;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POEnter
	  section.data(38).logicalSrcIdx = 138;
	  section.data(38).dtTransOffset = 37;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_POReset
	  section.data(39).logicalSrcIdx = 139;
	  section.data(39).dtTransOffset = 38;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_OOReset
	  section.data(40).logicalSrcIdx = 140;
	  section.data(40).dtTransOffset = 39;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOFinal
	  section.data(41).logicalSrcIdx = 141;
	  section.data(41).dtTransOffset = 40;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILInitialize_DOInitial
	  section.data(42).logicalSrcIdx = 142;
	  section.data(42).dtTransOffset = 41;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigitalTimebase_Active
	  section.data(43).logicalSrcIdx = 143;
	  section.data(43).dtTransOffset = 42;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILWriteDigital_Active
	  section.data(44).logicalSrcIdx = 144;
	  section.data(44).dtTransOffset = 43;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadDigital_Active
	  section.data(45).logicalSrcIdx = 145;
	  section.data(45).dtTransOffset = 44;
	
	  ;% TRACKING_CONTROL_RasconIET_P.HILReadDigital_Active_e
	  section.data(46).logicalSrcIdx = 146;
	  section.data(46).dtTransOffset = 45;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant_Value
	  section.data(47).logicalSrcIdx = 147;
	  section.data(47).dtTransOffset = 46;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant_Value_o
	  section.data(48).logicalSrcIdx = 148;
	  section.data(48).dtTransOffset = 47;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant_Value_f
	  section.data(49).logicalSrcIdx = 149;
	  section.data(49).dtTransOffset = 48;
	
	  ;% TRACKING_CONTROL_RasconIET_P.Constant_Value_d
	  section.data(50).logicalSrcIdx = 150;
	  section.data(50).dtTransOffset = 49;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch3_CurrentSetting
	  section.data(1).logicalSrcIdx = 151;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch2_CurrentSetting
	  section.data(2).logicalSrcIdx = 152;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 153;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch4_CurrentSetting
	  section.data(4).logicalSrcIdx = 154;
	  section.data(4).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch3_CurrentSetting_g
	  section.data(5).logicalSrcIdx = 155;
	  section.data(5).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch2_CurrentSetting_o
	  section.data(6).logicalSrcIdx = 156;
	  section.data(6).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch1_CurrentSetting_i
	  section.data(7).logicalSrcIdx = 157;
	  section.data(7).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_P.ManualSwitch4_CurrentSetting_l
	  section.data(8).logicalSrcIdx = 158;
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
    ;% Auto data (TRACKING_CONTROL_RasconIET_B)
    ;%
      section.nData     = 30;
      section.data(30)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_B.UnaryMinus
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_B.UnitDelay2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_B.UnaryMinus1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_B.UnitDelay3
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_B.FromWorkspace4
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_B.VectorConcatenate
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Sum3
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Sum
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_g
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Torquetocurrent
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_k
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Current
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Sum1
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_e
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Saturation
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 21;
	
	  ;% TRACKING_CONTROL_RasconIET_B.VectorConcatenate_j
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 22;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_gy
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 26;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_d
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 27;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Torquetocurrent_d
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 28;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_dk
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 29;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Current_c
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 30;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Sum1_l
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 31;
	
	  ;% TRACKING_CONTROL_RasconIET_B.TSamp_i
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 32;
	
	  ;% TRACKING_CONTROL_RasconIET_B.Saturation_h
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 33;
	
	  ;% TRACKING_CONTROL_RasconIET_B.VectorConcatenate_g
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 34;
	
	  ;% TRACKING_CONTROL_RasconIET_B.HILReadDigital_o1
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
	  ;% TRACKING_CONTROL_RasconIET_B.HILReadDigital_o2
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% TRACKING_CONTROL_RasconIET_B.HILReadDigital_o3
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 40;
	
	  ;% TRACKING_CONTROL_RasconIET_B.z3_out
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 41;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 30;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 31;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 32;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 33;
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
    ;% Auto data (TRACKING_CONTROL_RasconIET_DW)
    ;%
      section.nData     = 24;
      section.data(24)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay2_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay3_DSTATE
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay1_DSTATE
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay_DSTATE
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay4_DSTATE
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UnitDelay5_DSTATE
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_e
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_i
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_f
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_a
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_p
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_az
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.DiscreteTimeIntegrator_DSTATE_m
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.UD_DSTATE_i4
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadAnalog_Buffer
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadAnalog_Buffer_g
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_AIMinimums
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_AIMaximums
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 28;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_AOMinimums
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 36;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_AOMaximums
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 44;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_AOVoltages
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 52;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_FilterFrequency
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 60;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteDigitalTimebase_Task
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 25;
      section.data(25)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 26;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Scope_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 27;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Scope1_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 28;
	  section.data(3).dtTransOffset = 3;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace4_PWORK.TimePtr
	  section.data(4).logicalSrcIdx = 29;
	  section.data(4).dtTransOffset = 5;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace1_PWORK.TimePtr
	  section.data(5).logicalSrcIdx = 30;
	  section.data(5).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace2_PWORK.TimePtr
	  section.data(6).logicalSrcIdx = 31;
	  section.data(6).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.ToWorkspace_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 32;
	  section.data(7).dtTransOffset = 8;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.ToWorkspace1_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 33;
	  section.data(8).dtTransOffset = 9;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.ToWorkspace2_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 34;
	  section.data(9).dtTransOffset = 10;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_PWORK_j
	  section.data(10).logicalSrcIdx = 35;
	  section.data(10).dtTransOffset = 11;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace3_PWORK.TimePtr
	  section.data(11).logicalSrcIdx = 36;
	  section.data(11).dtTransOffset = 12;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadAnalog_PWORK
	  section.data(12).logicalSrcIdx = 37;
	  section.data(12).dtTransOffset = 13;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteAnalog_PWORK
	  section.data(13).logicalSrcIdx = 38;
	  section.data(13).dtTransOffset = 14;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Ielbow_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 39;
	  section.data(14).dtTransOffset = 15;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.ToWorkspace_PWORK_l.LoggedData
	  section.data(15).logicalSrcIdx = 40;
	  section.data(15).dtTransOffset = 17;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Velbow_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 41;
	  section.data(16).dtTransOffset = 18;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_PWORK_i
	  section.data(17).logicalSrcIdx = 42;
	  section.data(17).dtTransOffset = 19;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadAnalog_PWORK_e
	  section.data(18).logicalSrcIdx = 43;
	  section.data(18).dtTransOffset = 20;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteAnalog_PWORK_a
	  section.data(19).logicalSrcIdx = 44;
	  section.data(19).dtTransOffset = 21;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Ishoulder1_PWORK.LoggedData
	  section.data(20).logicalSrcIdx = 45;
	  section.data(20).dtTransOffset = 22;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.ToWorkspace_PWORK_k.LoggedData
	  section.data(21).logicalSrcIdx = 46;
	  section.data(21).dtTransOffset = 24;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.Vshoulder_PWORK.LoggedData
	  section.data(22).logicalSrcIdx = 47;
	  section.data(22).dtTransOffset = 25;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteDigital_PWORK
	  section.data(23).logicalSrcIdx = 48;
	  section.data(23).dtTransOffset = 26;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadDigital_PWORK
	  section.data(24).logicalSrcIdx = 49;
	  section.data(24).dtTransOffset = 27;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadDigital_PWORK_l
	  section.data(25).logicalSrcIdx = 50;
	  section.data(25).dtTransOffset = 28;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_Buffer
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_Buffer_l
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_Buffer_c
	  section.data(3).logicalSrcIdx = 53;
	  section.data(3).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.clockTickCounter
	  section.data(4).logicalSrcIdx = 54;
	  section.data(4).dtTransOffset = 6;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_DOStates
	  section.data(5).logicalSrcIdx = 55;
	  section.data(5).dtTransOffset = 7;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_QuadratureModes
	  section.data(6).logicalSrcIdx = 56;
	  section.data(6).dtTransOffset = 16;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_InitialEICounts
	  section.data(7).logicalSrcIdx = 57;
	  section.data(7).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace4_IWORK.PrevIndex
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace1_IWORK.PrevIndex
	  section.data(2).logicalSrcIdx = 59;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace2_IWORK.PrevIndex
	  section.data(3).logicalSrcIdx = 60;
	  section.data(3).dtTransOffset = 2;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.FromWorkspace3_IWORK.PrevIndex
	  section.data(4).logicalSrcIdx = 61;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 62;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteDigitalTimebase_Started
	  section.data(2).logicalSrcIdx = 63;
	  section.data(2).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteDigitalTimebase_Buffer
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILWriteDigital_Buffer
	  section.data(2).logicalSrcIdx = 65;
	  section.data(2).dtTransOffset = 1;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadDigital_Buffer
	  section.data(3).logicalSrcIdx = 66;
	  section.data(3).dtTransOffset = 4;
	
	  ;% TRACKING_CONTROL_RasconIET_DW.HILReadDigital_Buffer_a
	  section.data(4).logicalSrcIdx = 67;
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


  targMap.checksum0 = 1054174084;
  targMap.checksum1 = 223224040;
  targMap.checksum2 = 480339065;
  targMap.checksum3 = 2294769690;

