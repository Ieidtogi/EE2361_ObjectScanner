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
FINAL_IMAGE=${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Button.c Main.c oled_lib.c color_sensor_lib.c ASMLib.s CirBuf.c I2CLib.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Button.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/oled_lib.o ${OBJECTDIR}/color_sensor_lib.o ${OBJECTDIR}/ASMLib.o ${OBJECTDIR}/CirBuf.o ${OBJECTDIR}/I2CLib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Button.o.d ${OBJECTDIR}/Main.o.d ${OBJECTDIR}/oled_lib.o.d ${OBJECTDIR}/color_sensor_lib.o.d ${OBJECTDIR}/ASMLib.o.d ${OBJECTDIR}/CirBuf.o.d ${OBJECTDIR}/I2CLib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Button.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/oled_lib.o ${OBJECTDIR}/color_sensor_lib.o ${OBJECTDIR}/ASMLib.o ${OBJECTDIR}/CirBuf.o ${OBJECTDIR}/I2CLib.o

# Source Files
SOURCEFILES=Button.c Main.c oled_lib.c color_sensor_lib.c ASMLib.s CirBuf.c I2CLib.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Button.o: Button.c  .generated_files/flags/default/6bc03374dee0b2360ac93c0b63716a954830ce2b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Button.o.d 
	@${RM} ${OBJECTDIR}/Button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Button.c  -o ${OBJECTDIR}/Button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Button.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Main.o: Main.c  .generated_files/flags/default/6681a5f32a6a2cbc963e4e59832abdb86dc8752c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oled_lib.o: oled_lib.c  .generated_files/flags/default/d674de744d62b1cb842da7129c09b5c6204d090c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oled_lib.o.d 
	@${RM} ${OBJECTDIR}/oled_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oled_lib.c  -o ${OBJECTDIR}/oled_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oled_lib.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/color_sensor_lib.o: color_sensor_lib.c  .generated_files/flags/default/ac4474e60b5333dfd6136769a17daa2f6d993581 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/color_sensor_lib.o.d 
	@${RM} ${OBJECTDIR}/color_sensor_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  color_sensor_lib.c  -o ${OBJECTDIR}/color_sensor_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/color_sensor_lib.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/CirBuf.o: CirBuf.c  .generated_files/flags/default/10dff6d3330cf0c3fa4bda2fff809f7d530d4a79 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CirBuf.o.d 
	@${RM} ${OBJECTDIR}/CirBuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CirBuf.c  -o ${OBJECTDIR}/CirBuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/CirBuf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2CLib.o: I2CLib.c  .generated_files/flags/default/6cfc719246b390cfdb422429b1d6a1fa364b1255 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2CLib.o.d 
	@${RM} ${OBJECTDIR}/I2CLib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CLib.c  -o ${OBJECTDIR}/I2CLib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2CLib.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/Button.o: Button.c  .generated_files/flags/default/572640a8ca4241fde97e47b7b059e532b305d6b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Button.o.d 
	@${RM} ${OBJECTDIR}/Button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Button.c  -o ${OBJECTDIR}/Button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Button.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Main.o: Main.c  .generated_files/flags/default/d03d686ec01a693b06bd7d92ea9abcdba507d7df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Main.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oled_lib.o: oled_lib.c  .generated_files/flags/default/f6af941436f817e0c94105cfc9094eaa451413b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oled_lib.o.d 
	@${RM} ${OBJECTDIR}/oled_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oled_lib.c  -o ${OBJECTDIR}/oled_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oled_lib.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/color_sensor_lib.o: color_sensor_lib.c  .generated_files/flags/default/89ca855b5ca62ec7c55c97a5980beca771efabff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/color_sensor_lib.o.d 
	@${RM} ${OBJECTDIR}/color_sensor_lib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  color_sensor_lib.c  -o ${OBJECTDIR}/color_sensor_lib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/color_sensor_lib.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/CirBuf.o: CirBuf.c  .generated_files/flags/default/4b0f308bcbaecf91c0f69fa5e317c8fdbc8037b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CirBuf.o.d 
	@${RM} ${OBJECTDIR}/CirBuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CirBuf.c  -o ${OBJECTDIR}/CirBuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/CirBuf.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2CLib.o: I2CLib.c  .generated_files/flags/default/2ab0b37663770cc64521620f496040eb84b87cd5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2CLib.o.d 
	@${RM} ${OBJECTDIR}/I2CLib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2CLib.c  -o ${OBJECTDIR}/I2CLib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2CLib.o.d"        -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ASMLib.o: ASMLib.s  .generated_files/flags/default/ab0e7640c09287f9074998505c9b4a14300628e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ASMLib.o.d 
	@${RM} ${OBJECTDIR}/ASMLib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ASMLib.s  -o ${OBJECTDIR}/ASMLib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/ASMLib.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/ASMLib.o: ASMLib.s  .generated_files/flags/default/fe1683bb047153c0cb4995893eed0f4fb779806e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ASMLib.o.d 
	@${RM} ${OBJECTDIR}/ASMLib.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ASMLib.s  -o ${OBJECTDIR}/ASMLib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/ASMLib.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/ObjectScanner.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a    -mdfp="${DFP_DIR}/xc16" 
	
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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
