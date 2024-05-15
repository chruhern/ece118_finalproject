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
SOURCEFILES_QUOTED_IF_SPACED=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c TemplateEventChecker.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/TemplateEventChecker.o
POSSIBLE_DEPFILES=${OBJECTDIR}/HelloWorld.o.d ${OBJECTDIR}/_ext/1347132459/AD.o.d ${OBJECTDIR}/_ext/1347132459/BOARD.o.d ${OBJECTDIR}/_ext/1347132459/serial.o.d ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d ${OBJECTDIR}/_ext/1347132459/LED.o.d ${OBJECTDIR}/_ext/1347132459/pwm.o.d ${OBJECTDIR}/_ext/1347132459/timers.o.d ${OBJECTDIR}/TapeDetectorHarness.o.d ${OBJECTDIR}/TrackWireDetectorHarness.o.d ${OBJECTDIR}/BeaconDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d ${OBJECTDIR}/TemplateEventChecker.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/HelloWorld.o ${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TapeDetectorHarness.o ${OBJECTDIR}/TrackWireDetectorHarness.o ${OBJECTDIR}/BeaconDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/TemplateEventChecker.o

# Source Files
SOURCEFILES=HelloWorld.c ../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/serial.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/pwm.c ../ECE118/src/timers.c TapeDetectorHarness.c TrackWireDetectorHarness.c BeaconDetectorHarness.c ../ECE118/DC_Motor_TestHarness.c ../ECE118/TapeChipDetectorHarness.c ../ECE118/SwitchTestHarness.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c TemplateEventChecker.c



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
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/119a300a5703167c9879bc2eaa05374cc548ea9a .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/6da3ca24eda5d92268c5862f0da50d6500db5ad6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/1ca15d3ccf8a261595ee85a5c6103bb6410c8b98 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/3bd87088e3c662f4479277664d3ce907c01df9a9 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/7018d74ffa04e1f163d6e617349858dfa7ab6e83 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/f44c623b8aa7af2662b7c3ce99f32002f82bc79c .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/7ee3397fa095370e037d540a90b381f29fbdbad8 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/72567b7bc9fb89f3e958d4aed7efdec68c95e396 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/860afa8bf03fde0ef041bda875266b0b1a889eaf .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/d511125ad585dad6e3c66ba2cfc4f1c58fd9d8a4 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/5a158bfdfb9d72c33e2966568af09c4f34173394 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/af86dc1805d0c0482660ad39190d261a969d8de2 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/532ebe85e07c2f22c99d7c1324e76d44dfbdbebc .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/48054aba11e24aa3e99b69fb60175635dd6d12de .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/d8ffe09dad56f58db1d1da7daf7e7d8b2814f122 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/a262de3de79e67452b072d65f37d0862b89c423c .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/75244a0e2034da6167d55899f7a477c68f7eed5 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/e60ad225dfbf3c9869c01d118f098f664b37e016 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/a78d0b520606f72384c730932e468e810e2c8fb2 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/8bd3bc0d2f43cd25585f8fa8af40adb10a63a436 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/fa7a7a4e4bd50dea530aeaea71bf4f393b61c809 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateEventChecker.o: TemplateEventChecker.c  .generated_files/flags/default/a370bd6497bf9340a837478e964401b35ebaa342 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateEventChecker.o.d" -o ${OBJECTDIR}/TemplateEventChecker.o TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/HelloWorld.o: HelloWorld.c  .generated_files/flags/default/1cd29ff055aa5c5f8b0d77db36b99792a93fd37a .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HelloWorld.o.d 
	@${RM} ${OBJECTDIR}/HelloWorld.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/HelloWorld.o.d" -o ${OBJECTDIR}/HelloWorld.o HelloWorld.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/907d380070ca7cca806767d56b7adbef824836fc .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/46ac86cb8f4a6caa8030301c0d08651d9eabad18 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/b113bf3206d11dcbed462bad77db20a82ff49baa .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/13cb76d7d82d287fecff8c1fd299d6abdfb925c6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/1cc25f293d4c5f4286ed9a47aeb4ec24067f9a5f .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/6f98aec7f046efdcae6f09c509eb28d8285265bd .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/df8c9766844ea728770687a659d33be397b7058f .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeDetectorHarness.o: TapeDetectorHarness.c  .generated_files/flags/default/4383ae4af2b56c8d3ebed461043a4a04331df913 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TapeDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeDetectorHarness.o.d" -o ${OBJECTDIR}/TapeDetectorHarness.o TapeDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TrackWireDetectorHarness.o: TrackWireDetectorHarness.c  .generated_files/flags/default/46050d387a9850b7804f3a2deda1721e0bee20e7 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/TrackWireDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TrackWireDetectorHarness.o.d" -o ${OBJECTDIR}/TrackWireDetectorHarness.o TrackWireDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BeaconDetectorHarness.o: BeaconDetectorHarness.c  .generated_files/flags/default/6289e97c8abfeda24014b9c52c6362ba852042d3 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/BeaconDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BeaconDetectorHarness.o.d" -o ${OBJECTDIR}/BeaconDetectorHarness.o BeaconDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o: ../ECE118/DC_Motor_TestHarness.c  .generated_files/flags/default/f4630afeb6f69680c69d92af31c78de9259c88b6 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/DC_Motor_TestHarness.o ../ECE118/DC_Motor_TestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o: ../ECE118/TapeChipDetectorHarness.c  .generated_files/flags/default/ab9d5f15b0c9fb37945f7fe0b87d3a388e0ec78d .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/TapeChipDetectorHarness.o ../ECE118/TapeChipDetectorHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o: ../ECE118/SwitchTestHarness.c  .generated_files/flags/default/f43bbca14cfac69b29fdb7a9da784134caaa7757 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/2123729024" 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d 
	@${RM} ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o.d" -o ${OBJECTDIR}/_ext/2123729024/SwitchTestHarness.o ../ECE118/SwitchTestHarness.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/859cce4d52f49a4c63d40daa480b918117cca54b .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/91d2274354fd9eaae0937419b1627ba9ef263015 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/72127625a82b876438f210632881102ecce949bc .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/f911d28f865093751ba26ecf4e4f3865e81af9b2 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/64bcacd5f4346d07ab412c406900aeee263eb453 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/865c867c0a8b6dcf28e8986cdcb95790ad0fd4c2 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/7706355d60b70e3aab85b9f18e175f42dd9f7f40 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateEventChecker.o: TemplateEventChecker.c  .generated_files/flags/default/7852021e0e8d04677a5581ddd8906d77ee394497 .generated_files/flags/default/a8d72842549110e9d8f1974f4230d40db2209aef
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"../ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateEventChecker.o.d" -o ${OBJECTDIR}/TemplateEventChecker.o TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
