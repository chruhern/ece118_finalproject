#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o
POSSIBLE_DEPFILES=${OBJECTDIR}/HelloWorld.o.d ${OBJECTDIR}/_ext/1347132459/AD.o.d ${OBJECTDIR}/_ext/1347132459/BOARD.o.d ${OBJECTDIR}/_ext/1347132459/serial.o.d ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d ${OBJECTDIR}/_ext/1347132459/LED.o.d ${OBJECTDIR}/_ext/1347132459/pwm.o.d ${OBJECTDIR}/_ext/1347132459/timers.o.d ${OBJECTDIR}/TapeDetectorHarness.o.d ${OBJECTDIR}/TrackWireDetectorHarness.o.d ${OBJECTDIR}/BeaconDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o

# Source Files
SOURCEFILES=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\ECE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/692e9071788dacdd9126e3a57a739e013dbdaddf .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/54020f68b90b2221624bcc7d6310ec7e28ee756a .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/b2c12c414c40109e8898b4975b3bfacb8780001f .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/dcdfe14f943f191b0c9ca441f3e1068d232ea5ce .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/7f45d8f42adb7b40add30570bbd436aa4657a579 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/a44f65ee155c88bd2f817ccd9d6b1a0f322c6db0 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/fc6d92db9f2f8cf7ab31eb17f5053e657d53a6bf .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/d86fc9147f2c22e7cffffbb3e2b5d31b8fef1a47 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/a143877cb51c571462fef9fa73dd9a3494d27848 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/58d72fc061a6a81a08102a777d2a6462baea51d .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/a66d2d7b40ef4ea62eaf13f28424bb4a8d0adcae .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/240e186048dd2ececfda6a8d0315e295519577c9 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/57d537b7e2347613ac3a089245c324d71d019d43 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/d0ac7d2acd195557327976d38ebb4ec5ab69900a .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/74a2ae44916976ef572f052f62f852c5d6d2f484 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/6470556620f76d56c6786dd5ed7cd3d512145ce3 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/28789e3f8ef9631441d5e901478d026d8c27eecd .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/4c1f29a2562326a41ccfb7d110d35b14bee0bf85 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/28503e147062cac71550e821d3919a2387200798 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/77129921d14944d18e5dbcb52f2021260306469e .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/b41cebb09b799af7e279ecb2e8339792644bd15a .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/aae2c8901e4776ce37aff32f3a9840dde8682330 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/7a2dfc5763fe16450522841999f29f32e2bd205f .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/78e133255d83f0a08a20822195432417a410a550 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/aed1781c2ca2009a0758f5fcf51c84d6d8c00436 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/2bfda4a708d91b4343651e138430fa000ac4d917 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/b5e3091567a9323639323bd295ceed4fcceec42f .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/18cab8f27ed80fe4fd7683718a269c2916c4c354 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../ECE118/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../ECE118/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/ECE118_FinalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
