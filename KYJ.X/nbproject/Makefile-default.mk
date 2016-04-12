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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=SRC/LCD_LIXIAN.c SRC/delay.c SRC/main.c SRC/EEPROM.c SRC/KYJDEF.c SRC/adc.c SRC/key.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/SRC/LCD_LIXIAN.p1 ${OBJECTDIR}/SRC/delay.p1 ${OBJECTDIR}/SRC/main.p1 ${OBJECTDIR}/SRC/EEPROM.p1 ${OBJECTDIR}/SRC/KYJDEF.p1 ${OBJECTDIR}/SRC/adc.p1 ${OBJECTDIR}/SRC/key.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d ${OBJECTDIR}/SRC/delay.p1.d ${OBJECTDIR}/SRC/main.p1.d ${OBJECTDIR}/SRC/EEPROM.p1.d ${OBJECTDIR}/SRC/KYJDEF.p1.d ${OBJECTDIR}/SRC/adc.p1.d ${OBJECTDIR}/SRC/key.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/SRC/LCD_LIXIAN.p1 ${OBJECTDIR}/SRC/delay.p1 ${OBJECTDIR}/SRC/main.p1 ${OBJECTDIR}/SRC/EEPROM.p1 ${OBJECTDIR}/SRC/KYJDEF.p1 ${OBJECTDIR}/SRC/adc.p1 ${OBJECTDIR}/SRC/key.p1

# Source Files
SOURCEFILES=SRC/LCD_LIXIAN.c SRC/delay.c SRC/main.c SRC/EEPROM.c SRC/KYJDEF.c SRC/adc.c SRC/key.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K20
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/SRC/LCD_LIXIAN.p1: SRC/LCD_LIXIAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d 
	@${RM} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/LCD_LIXIAN.p1  SRC/LCD_LIXIAN.c 
	@-${MV} ${OBJECTDIR}/SRC/LCD_LIXIAN.d ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/delay.p1: SRC/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/delay.p1.d 
	@${RM} ${OBJECTDIR}/SRC/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/delay.p1  SRC/delay.c 
	@-${MV} ${OBJECTDIR}/SRC/delay.d ${OBJECTDIR}/SRC/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/main.p1: SRC/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/main.p1.d 
	@${RM} ${OBJECTDIR}/SRC/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/main.p1  SRC/main.c 
	@-${MV} ${OBJECTDIR}/SRC/main.d ${OBJECTDIR}/SRC/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/EEPROM.p1: SRC/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/SRC/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/EEPROM.p1  SRC/EEPROM.c 
	@-${MV} ${OBJECTDIR}/SRC/EEPROM.d ${OBJECTDIR}/SRC/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/KYJDEF.p1: SRC/KYJDEF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/KYJDEF.p1.d 
	@${RM} ${OBJECTDIR}/SRC/KYJDEF.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/KYJDEF.p1  SRC/KYJDEF.c 
	@-${MV} ${OBJECTDIR}/SRC/KYJDEF.d ${OBJECTDIR}/SRC/KYJDEF.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/KYJDEF.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/adc.p1: SRC/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/adc.p1.d 
	@${RM} ${OBJECTDIR}/SRC/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/adc.p1  SRC/adc.c 
	@-${MV} ${OBJECTDIR}/SRC/adc.d ${OBJECTDIR}/SRC/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/key.p1: SRC/key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/key.p1.d 
	@${RM} ${OBJECTDIR}/SRC/key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/key.p1  SRC/key.c 
	@-${MV} ${OBJECTDIR}/SRC/key.d ${OBJECTDIR}/SRC/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/SRC/LCD_LIXIAN.p1: SRC/LCD_LIXIAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d 
	@${RM} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/LCD_LIXIAN.p1  SRC/LCD_LIXIAN.c 
	@-${MV} ${OBJECTDIR}/SRC/LCD_LIXIAN.d ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/LCD_LIXIAN.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/delay.p1: SRC/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/delay.p1.d 
	@${RM} ${OBJECTDIR}/SRC/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/delay.p1  SRC/delay.c 
	@-${MV} ${OBJECTDIR}/SRC/delay.d ${OBJECTDIR}/SRC/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/main.p1: SRC/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/main.p1.d 
	@${RM} ${OBJECTDIR}/SRC/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/main.p1  SRC/main.c 
	@-${MV} ${OBJECTDIR}/SRC/main.d ${OBJECTDIR}/SRC/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/EEPROM.p1: SRC/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/SRC/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/EEPROM.p1  SRC/EEPROM.c 
	@-${MV} ${OBJECTDIR}/SRC/EEPROM.d ${OBJECTDIR}/SRC/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/KYJDEF.p1: SRC/KYJDEF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/KYJDEF.p1.d 
	@${RM} ${OBJECTDIR}/SRC/KYJDEF.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/KYJDEF.p1  SRC/KYJDEF.c 
	@-${MV} ${OBJECTDIR}/SRC/KYJDEF.d ${OBJECTDIR}/SRC/KYJDEF.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/KYJDEF.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/adc.p1: SRC/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/adc.p1.d 
	@${RM} ${OBJECTDIR}/SRC/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/adc.p1  SRC/adc.c 
	@-${MV} ${OBJECTDIR}/SRC/adc.d ${OBJECTDIR}/SRC/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SRC/key.p1: SRC/key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SRC" 
	@${RM} ${OBJECTDIR}/SRC/key.p1.d 
	@${RM} ${OBJECTDIR}/SRC/key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SRC/key.p1  SRC/key.c 
	@-${MV} ${OBJECTDIR}/SRC/key.d ${OBJECTDIR}/SRC/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SRC/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     --rom=default,-fd30-ffff --ram=default,-ef4-eff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -N31 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,-config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/KYJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
