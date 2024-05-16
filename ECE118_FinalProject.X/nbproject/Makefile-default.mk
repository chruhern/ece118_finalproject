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
SOURCEFILES_QUOTED_IF_SPACED=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c TemplateEventChecker.c TemplateService.c ../ECE118/Robot.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/TemplateEventChecker.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/_ext/2123729024/Robot.o
POSSIBLE_DEPFILES=${OBJECTDIR}/HelloWorld.o.d ${OBJECTDIR}/_ext/1347132459/AD.o.d ${OBJECTDIR}/_ext/1347132459/BOARD.o.d ${OBJECTDIR}/_ext/1347132459/serial.o.d ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d ${OBJECTDIR}/_ext/1347132459/LED.o.d ${OBJECTDIR}/_ext/1347132459/pwm.o.d ${OBJECTDIR}/_ext/1347132459/timers.o.d ${OBJECTDIR}/TapeDetectorHarness.o.d ${OBJECTDIR}/TrackWireDetectorHarness.o.d ${OBJECTDIR}/BeaconDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d ${OBJECTDIR}/TemplateEventChecker.o.d ${OBJECTDIR}/TemplateService.o.d ${OBJECTDIR}/_ext/2123729024/Robot.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/TemplateEventChecker.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/_ext/2123729024/Robot.o

# Source Files
SOURCEFILES=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c TemplateEventChecker.c TemplateService.c ../ECE118/Robot.c



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

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MX320F128H
ProjectDir="C:\Users\derri\ECE118\ece118_finalproject\ECE118_FinalProject.X"
ProjectName=ECE118_FinalProject
ConfName=default
ImagePath="${DISTDIR}\ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
ImageName="ECE118_FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
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
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/dbf17ed571659fbc02bef5ab460d921dcfc97f18 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/a8b9588e5aec4d92ff65305469b5f410775c91b1 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/d7e269fdcd0aca9a21a362b9be20f7f15d43f765 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/1ce0dc8e8486958863ae3a12076f1f14092c95c6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/81cf35d9ffe541ec19c164a959a172d12368ded9 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/5eba83879f4d4ae287fcdbdd87744fb6a346bc11 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/f7beba27331ae26e982c386f1a9f80d860b390d4 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/ccae7bf4a65b2aef1fc65d397cf665df6c4a303b .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/267dd9eaf911b25c15fc4f940c128c583add49b2 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/7f70fe88077c3e6e528b4f217197b4fe49ca27cf .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/30133190fe088bd7b985ff6f4034a1f3a54e6ff6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/214d75f342a11331355ebafc3ab3a6c0c6871023 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/e1783cd1e3f93da67bb1423b572197562693c456 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/6954711505fa82b657a1518abc937ac03cf270d .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/da2216fe98b07878845c9ce76c643e42f1e62572 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/c57066d22faa7e60f1230905d48e1f0025ded75e .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/e250142da14b6cf27e080484f3e2906ee2720b21 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/d3ba979dc6de60b7b6e9395e1ee73592e3ba8ad8 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/c6982587154c69bbfea8f88e92344961ce265e8d .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/e04d1a488382dc44991dfb99ba1753ff6564982b .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/4a6958416be78a8964122f995dac4a9ed7b5ec9 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateEventChecker.o: TemplateEventChecker.c  .generated_files/flags/default/a76de277b81b591db09c7d11929046c314271a86 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateEventChecker.o.d" -o ${OBJECTDIR}/TemplateEventChecker.o TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/d26538eee369399f6c7f9fc0ced4183365cd0c2c .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/Robot.o: ../ECE118/Robot.c  .generated_files/flags/default/edcf0667a0d9395087d330ca0fa7175c909b1024 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/Robot.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/Robot.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/Robot.o.d" -o ${OBJECTDIR}/_ext/2123729024/Robot.o ../ECE118/Robot.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/87a1b3b24806377601743d296994d81fb786c0bf .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/23714fa7d7fc2b20812d82ea1f0102724d99606 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/f4795bb9093dda7cc73dcee521cefdcbd3adea38 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/8d68574a858787b79897aae9d749ed98e007e305 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/9a83d86ec0b23e785d1ce95037675def9e8ff2a7 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/747a7827ef503d6e4b4f261935aed2efccace186 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/ae12dce28fb1a9ca38b17e9a7ff2f7c5b1e18230 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/86155ae4ae267766e9c752e9c14deb1b286851f0 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/255a8cd77873431f04955c2b23f1a05ff9dccb60 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/ecf83980a8fe43bb36e99ba475a966f1638d8fe4 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/5889851321fd56863e5abceaaf0f0fecdad5568e .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/e7a3102ec8b0ffe8800c5703a5b8ded000259606 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/68036b5a6fdc1e4836bebc948d0a79b64a29e6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/fd3ab34c03077d5c588e47e3ec37e722679b9e4b .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/971fd99a8a756be0c85ab7880165d39c05a37afd .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/15249a3579c7178945d6f1b221d4539fdec68c6d .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/42cccf1e459be2eeec0fdae6aa8a0fc6243cf816 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/85082b849fdee14b791ed59d77baea3aa7a9ce75 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/5c0ed9fdbc01a38329556014d0661081dc09bd42 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/8a6d132e02bede6d45e2c7452f6c3ce3ce77f271 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/90c3b71e52eafed3495aa54ac8a3f819fe2f041 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateEventChecker.o: TemplateEventChecker.c  .generated_files/flags/default/173beb0a5c4f764aa3b98379b72815193b869031 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateEventChecker.o.d" -o ${OBJECTDIR}/TemplateEventChecker.o TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/43ed50353ea7b4ea6a4436fa59f4d653185c1e96 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/Robot.o: ../ECE118/Robot.c  .generated_files/flags/default/aec1a41f8e30923a0afd0916cc9eb45b7b60c4f3 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/Robot.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/Robot.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/Robot.o.d" -o ${OBJECTDIR}/_ext/2123729024/Robot.o ../ECE118/Robot.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python ..\ECE118\scripts\Enum_To_String.py]"
	@python ..\ECE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

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
