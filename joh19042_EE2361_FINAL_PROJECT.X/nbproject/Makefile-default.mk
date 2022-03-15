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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=joh19042_rotationsLib_v001.c lixx5451_FinalProject_mainMin.c lixx5451_button.c lixx5451_i2cLCD.c karam003_conversion_v001.c joh19042_PIDlib_v001.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/joh19042_rotationsLib_v001.o ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o ${OBJECTDIR}/lixx5451_button.o ${OBJECTDIR}/lixx5451_i2cLCD.o ${OBJECTDIR}/karam003_conversion_v001.o ${OBJECTDIR}/joh19042_PIDlib_v001.o
POSSIBLE_DEPFILES=${OBJECTDIR}/joh19042_rotationsLib_v001.o.d ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o.d ${OBJECTDIR}/lixx5451_button.o.d ${OBJECTDIR}/lixx5451_i2cLCD.o.d ${OBJECTDIR}/karam003_conversion_v001.o.d ${OBJECTDIR}/joh19042_PIDlib_v001.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/joh19042_rotationsLib_v001.o ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o ${OBJECTDIR}/lixx5451_button.o ${OBJECTDIR}/lixx5451_i2cLCD.o ${OBJECTDIR}/karam003_conversion_v001.o ${OBJECTDIR}/joh19042_PIDlib_v001.o

# Source Files
SOURCEFILES=joh19042_rotationsLib_v001.c lixx5451_FinalProject_mainMin.c lixx5451_button.c lixx5451_i2cLCD.c karam003_conversion_v001.c joh19042_PIDlib_v001.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/joh19042_rotationsLib_v001.o: joh19042_rotationsLib_v001.c  .generated_files/9a930a5d3509a731ba241f9179c9119cf78dddc2.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/joh19042_rotationsLib_v001.o.d 
	@${RM} ${OBJECTDIR}/joh19042_rotationsLib_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  joh19042_rotationsLib_v001.c  -o ${OBJECTDIR}/joh19042_rotationsLib_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/joh19042_rotationsLib_v001.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_FinalProject_mainMin.o: lixx5451_FinalProject_mainMin.c  .generated_files/b2536c49483c1c4cf3d566ae04a36efdb301c0b3.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_FinalProject_mainMin.c  -o ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_FinalProject_mainMin.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_button.o: lixx5451_button.c  .generated_files/9d2bec232f997298ae227ffcdd7578f7aa432859.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_button.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_button.c  -o ${OBJECTDIR}/lixx5451_button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_button.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_i2cLCD.o: lixx5451_i2cLCD.c  .generated_files/977b0a075eda9be9cf094b4a26e3f792df88672d.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_i2cLCD.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_i2cLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_i2cLCD.c  -o ${OBJECTDIR}/lixx5451_i2cLCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_i2cLCD.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/karam003_conversion_v001.o: karam003_conversion_v001.c  .generated_files/a088019a9009f717f54d1566cb39cc075e11de93.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/karam003_conversion_v001.o.d 
	@${RM} ${OBJECTDIR}/karam003_conversion_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  karam003_conversion_v001.c  -o ${OBJECTDIR}/karam003_conversion_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/karam003_conversion_v001.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/joh19042_PIDlib_v001.o: joh19042_PIDlib_v001.c  .generated_files/c4aaf8b3cc0530e18467033880fb6c507973e607.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/joh19042_PIDlib_v001.o.d 
	@${RM} ${OBJECTDIR}/joh19042_PIDlib_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  joh19042_PIDlib_v001.c  -o ${OBJECTDIR}/joh19042_PIDlib_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/joh19042_PIDlib_v001.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/joh19042_rotationsLib_v001.o: joh19042_rotationsLib_v001.c  .generated_files/92ec1423e6f9b6e12367171d5ff8c9b69ffc6a7a.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/joh19042_rotationsLib_v001.o.d 
	@${RM} ${OBJECTDIR}/joh19042_rotationsLib_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  joh19042_rotationsLib_v001.c  -o ${OBJECTDIR}/joh19042_rotationsLib_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/joh19042_rotationsLib_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_FinalProject_mainMin.o: lixx5451_FinalProject_mainMin.c  .generated_files/586fcab4d36fb4e6022609d27cc6f3866c741fea.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_FinalProject_mainMin.c  -o ${OBJECTDIR}/lixx5451_FinalProject_mainMin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_FinalProject_mainMin.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_button.o: lixx5451_button.c  .generated_files/91cb82a6ad474a027895513618adb6cda957deca.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_button.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_button.c  -o ${OBJECTDIR}/lixx5451_button.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_button.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lixx5451_i2cLCD.o: lixx5451_i2cLCD.c  .generated_files/13a7967720d502f74e0b9c1c3f3615887a195d2e.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lixx5451_i2cLCD.o.d 
	@${RM} ${OBJECTDIR}/lixx5451_i2cLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lixx5451_i2cLCD.c  -o ${OBJECTDIR}/lixx5451_i2cLCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lixx5451_i2cLCD.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/karam003_conversion_v001.o: karam003_conversion_v001.c  .generated_files/90ecd338f997abe457df813086e370b961c04361.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/karam003_conversion_v001.o.d 
	@${RM} ${OBJECTDIR}/karam003_conversion_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  karam003_conversion_v001.c  -o ${OBJECTDIR}/karam003_conversion_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/karam003_conversion_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/joh19042_PIDlib_v001.o: joh19042_PIDlib_v001.c  .generated_files/2c14b72305c47dbbe24ca02913c6ce1481f19805.flag .generated_files/647cdef09a74fadadc5113b1ead3e23ada6a50f5.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/joh19042_PIDlib_v001.o.d 
	@${RM} ${OBJECTDIR}/joh19042_PIDlib_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  joh19042_PIDlib_v001.c  -o ${OBJECTDIR}/joh19042_PIDlib_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/joh19042_PIDlib_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/joh19042_EE2361_FINAL_PROJECT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
