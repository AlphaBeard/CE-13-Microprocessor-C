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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=include/Ascii.c include/BOARD.c include/CircularBuffer.c include/FieldOled.c include/Lab09_main.c include/Oled.c include/OledDriver.c include/Uart1.c include/Message.c include/Field.c include/Negotiation.c include/Agent.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/include/Ascii.o ${OBJECTDIR}/include/BOARD.o ${OBJECTDIR}/include/CircularBuffer.o ${OBJECTDIR}/include/FieldOled.o ${OBJECTDIR}/include/Lab09_main.o ${OBJECTDIR}/include/Oled.o ${OBJECTDIR}/include/OledDriver.o ${OBJECTDIR}/include/Uart1.o ${OBJECTDIR}/include/Message.o ${OBJECTDIR}/include/Field.o ${OBJECTDIR}/include/Negotiation.o ${OBJECTDIR}/include/Agent.o
POSSIBLE_DEPFILES=${OBJECTDIR}/include/Ascii.o.d ${OBJECTDIR}/include/BOARD.o.d ${OBJECTDIR}/include/CircularBuffer.o.d ${OBJECTDIR}/include/FieldOled.o.d ${OBJECTDIR}/include/Lab09_main.o.d ${OBJECTDIR}/include/Oled.o.d ${OBJECTDIR}/include/OledDriver.o.d ${OBJECTDIR}/include/Uart1.o.d ${OBJECTDIR}/include/Message.o.d ${OBJECTDIR}/include/Field.o.d ${OBJECTDIR}/include/Negotiation.o.d ${OBJECTDIR}/include/Agent.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/include/Ascii.o ${OBJECTDIR}/include/BOARD.o ${OBJECTDIR}/include/CircularBuffer.o ${OBJECTDIR}/include/FieldOled.o ${OBJECTDIR}/include/Lab09_main.o ${OBJECTDIR}/include/Oled.o ${OBJECTDIR}/include/OledDriver.o ${OBJECTDIR}/include/Uart1.o ${OBJECTDIR}/include/Message.o ${OBJECTDIR}/include/Field.o ${OBJECTDIR}/include/Negotiation.o ${OBJECTDIR}/include/Agent.o

# Source Files
SOURCEFILES=include/Ascii.c include/BOARD.c include/CircularBuffer.c include/FieldOled.c include/Lab09_main.c include/Oled.c include/OledDriver.c include/Uart1.c include/Message.c include/Field.c include/Negotiation.c include/Agent.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/include/Ascii.o: include/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Ascii.o.d 
	@${RM} ${OBJECTDIR}/include/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Ascii.o.d" -o ${OBJECTDIR}/include/Ascii.o include/Ascii.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/BOARD.o: include/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/BOARD.o.d 
	@${RM} ${OBJECTDIR}/include/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/include/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/BOARD.o.d" -o ${OBJECTDIR}/include/BOARD.o include/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/CircularBuffer.o: include/CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/CircularBuffer.o.d 
	@${RM} ${OBJECTDIR}/include/CircularBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/include/CircularBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/CircularBuffer.o.d" -o ${OBJECTDIR}/include/CircularBuffer.o include/CircularBuffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/FieldOled.o: include/FieldOled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/FieldOled.o.d 
	@${RM} ${OBJECTDIR}/include/FieldOled.o 
	@${FIXDEPS} "${OBJECTDIR}/include/FieldOled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/FieldOled.o.d" -o ${OBJECTDIR}/include/FieldOled.o include/FieldOled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Lab09_main.o: include/Lab09_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Lab09_main.o.d 
	@${RM} ${OBJECTDIR}/include/Lab09_main.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Lab09_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Lab09_main.o.d" -o ${OBJECTDIR}/include/Lab09_main.o include/Lab09_main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Oled.o: include/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Oled.o.d 
	@${RM} ${OBJECTDIR}/include/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Oled.o.d" -o ${OBJECTDIR}/include/Oled.o include/Oled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/OledDriver.o: include/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/include/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/include/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/OledDriver.o.d" -o ${OBJECTDIR}/include/OledDriver.o include/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Uart1.o: include/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Uart1.o.d 
	@${RM} ${OBJECTDIR}/include/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Uart1.o.d" -o ${OBJECTDIR}/include/Uart1.o include/Uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Message.o: include/Message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Message.o.d 
	@${RM} ${OBJECTDIR}/include/Message.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Message.o.d" -o ${OBJECTDIR}/include/Message.o include/Message.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Field.o: include/Field.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Field.o.d 
	@${RM} ${OBJECTDIR}/include/Field.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Field.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Field.o.d" -o ${OBJECTDIR}/include/Field.o include/Field.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Negotiation.o: include/Negotiation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Negotiation.o.d 
	@${RM} ${OBJECTDIR}/include/Negotiation.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Negotiation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Negotiation.o.d" -o ${OBJECTDIR}/include/Negotiation.o include/Negotiation.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Agent.o: include/Agent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Agent.o.d 
	@${RM} ${OBJECTDIR}/include/Agent.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Agent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Agent.o.d" -o ${OBJECTDIR}/include/Agent.o include/Agent.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/include/Ascii.o: include/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Ascii.o.d 
	@${RM} ${OBJECTDIR}/include/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Ascii.o.d" -o ${OBJECTDIR}/include/Ascii.o include/Ascii.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/BOARD.o: include/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/BOARD.o.d 
	@${RM} ${OBJECTDIR}/include/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/include/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/BOARD.o.d" -o ${OBJECTDIR}/include/BOARD.o include/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/CircularBuffer.o: include/CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/CircularBuffer.o.d 
	@${RM} ${OBJECTDIR}/include/CircularBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/include/CircularBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/CircularBuffer.o.d" -o ${OBJECTDIR}/include/CircularBuffer.o include/CircularBuffer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/FieldOled.o: include/FieldOled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/FieldOled.o.d 
	@${RM} ${OBJECTDIR}/include/FieldOled.o 
	@${FIXDEPS} "${OBJECTDIR}/include/FieldOled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/FieldOled.o.d" -o ${OBJECTDIR}/include/FieldOled.o include/FieldOled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Lab09_main.o: include/Lab09_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Lab09_main.o.d 
	@${RM} ${OBJECTDIR}/include/Lab09_main.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Lab09_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Lab09_main.o.d" -o ${OBJECTDIR}/include/Lab09_main.o include/Lab09_main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Oled.o: include/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Oled.o.d 
	@${RM} ${OBJECTDIR}/include/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Oled.o.d" -o ${OBJECTDIR}/include/Oled.o include/Oled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/OledDriver.o: include/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/include/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/include/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/OledDriver.o.d" -o ${OBJECTDIR}/include/OledDriver.o include/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Uart1.o: include/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Uart1.o.d 
	@${RM} ${OBJECTDIR}/include/Uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Uart1.o.d" -o ${OBJECTDIR}/include/Uart1.o include/Uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Message.o: include/Message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Message.o.d 
	@${RM} ${OBJECTDIR}/include/Message.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Message.o.d" -o ${OBJECTDIR}/include/Message.o include/Message.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Field.o: include/Field.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Field.o.d 
	@${RM} ${OBJECTDIR}/include/Field.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Field.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Field.o.d" -o ${OBJECTDIR}/include/Field.o include/Field.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Negotiation.o: include/Negotiation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Negotiation.o.d 
	@${RM} ${OBJECTDIR}/include/Negotiation.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Negotiation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Negotiation.o.d" -o ${OBJECTDIR}/include/Negotiation.o include/Negotiation.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/Agent.o: include/Agent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/Agent.o.d 
	@${RM} ${OBJECTDIR}/include/Agent.o 
	@${FIXDEPS} "${OBJECTDIR}/include/Agent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/include/Agent.o.d" -o ${OBJECTDIR}/include/Agent.o include/Agent.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  include/Lab9SupportLib.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    include\Lab9SupportLib.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  include/Lab9SupportLib.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    include\Lab9SupportLib.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab9.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
