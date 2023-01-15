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
FINAL_IMAGE=${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=app/flasher/flasher.c app/programmer/bus.c app/programmer/programmer.c app/app.c app/connect_state.c app/result.c app/app_data.c app/leds.c app/flasher.c logger/logger.c mcc_generated_files/usb/usb_device_generic.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/system.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/traps.c mcc_generated_files/clock.c mcc_generated_files/mcc.c mcc_generated_files/tmr2.c mcc_generated_files/tmr3.c mcc_generated_files/i2c1.c main.c delay.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/app/flasher/flasher.o ${OBJECTDIR}/app/programmer/bus.o ${OBJECTDIR}/app/programmer/programmer.o ${OBJECTDIR}/app/app.o ${OBJECTDIR}/app/connect_state.o ${OBJECTDIR}/app/result.o ${OBJECTDIR}/app/app_data.o ${OBJECTDIR}/app/leds.o ${OBJECTDIR}/app/flasher.o ${OBJECTDIR}/logger/logger.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/mcc_generated_files/i2c1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/delay.o
POSSIBLE_DEPFILES=${OBJECTDIR}/app/flasher/flasher.o.d ${OBJECTDIR}/app/programmer/bus.o.d ${OBJECTDIR}/app/programmer/programmer.o.d ${OBJECTDIR}/app/app.o.d ${OBJECTDIR}/app/connect_state.o.d ${OBJECTDIR}/app/result.o.d ${OBJECTDIR}/app/app_data.o.d ${OBJECTDIR}/app/leds.o.d ${OBJECTDIR}/app/flasher.o.d ${OBJECTDIR}/logger/logger.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d ${OBJECTDIR}/mcc_generated_files/system.o.d ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/traps.o.d ${OBJECTDIR}/mcc_generated_files/clock.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/delay.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/app/flasher/flasher.o ${OBJECTDIR}/app/programmer/bus.o ${OBJECTDIR}/app/programmer/programmer.o ${OBJECTDIR}/app/app.o ${OBJECTDIR}/app/connect_state.o ${OBJECTDIR}/app/result.o ${OBJECTDIR}/app/app_data.o ${OBJECTDIR}/app/leds.o ${OBJECTDIR}/app/flasher.o ${OBJECTDIR}/logger/logger.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o ${OBJECTDIR}/mcc_generated_files/system.o ${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/traps.o ${OBJECTDIR}/mcc_generated_files/clock.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/tmr2.o ${OBJECTDIR}/mcc_generated_files/tmr3.o ${OBJECTDIR}/mcc_generated_files/i2c1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/delay.o

# Source Files
SOURCEFILES=app/flasher/flasher.c app/programmer/bus.c app/programmer/programmer.c app/app.c app/connect_state.c app/result.c app/app_data.c app/leds.c app/flasher.c logger/logger.c mcc_generated_files/usb/usb_device_generic.c mcc_generated_files/usb/usb_descriptors.c mcc_generated_files/usb/usb_device.c mcc_generated_files/usb/usb_device_events.c mcc_generated_files/usb/usb_hal_16bit.c mcc_generated_files/system.c mcc_generated_files/pin_manager.c mcc_generated_files/interrupt_manager.c mcc_generated_files/traps.c mcc_generated_files/clock.c mcc_generated_files/mcc.c mcc_generated_files/tmr2.c mcc_generated_files/tmr3.c mcc_generated_files/i2c1.c main.c delay.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GB106
MP_LINKER_FILE_OPTION=,--script=p24FJ256GB106.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/app/flasher/flasher.o: app/flasher/flasher.c  .generated_files/flags/default/8177dfe0237a6f7480b80866072061b94232124c .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/flasher" 
	@${RM} ${OBJECTDIR}/app/flasher/flasher.o.d 
	@${RM} ${OBJECTDIR}/app/flasher/flasher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/flasher/flasher.c  -o ${OBJECTDIR}/app/flasher/flasher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/flasher/flasher.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/programmer/bus.o: app/programmer/bus.c  .generated_files/flags/default/cbd06e76142c5ec10b19cc5a68c00f9bc8b9df00 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/programmer" 
	@${RM} ${OBJECTDIR}/app/programmer/bus.o.d 
	@${RM} ${OBJECTDIR}/app/programmer/bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/programmer/bus.c  -o ${OBJECTDIR}/app/programmer/bus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/programmer/bus.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/programmer/programmer.o: app/programmer/programmer.c  .generated_files/flags/default/a85257700d1da681bdb811282a5bc9d903134444 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/programmer" 
	@${RM} ${OBJECTDIR}/app/programmer/programmer.o.d 
	@${RM} ${OBJECTDIR}/app/programmer/programmer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/programmer/programmer.c  -o ${OBJECTDIR}/app/programmer/programmer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/programmer/programmer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/app.o: app/app.c  .generated_files/flags/default/c3c4453867945c6e18405d4bba8ea251077914be .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/app.o.d 
	@${RM} ${OBJECTDIR}/app/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/app.c  -o ${OBJECTDIR}/app/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/connect_state.o: app/connect_state.c  .generated_files/flags/default/746a958e9d89d030781dedab7ab771819d4572be .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/connect_state.o.d 
	@${RM} ${OBJECTDIR}/app/connect_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/connect_state.c  -o ${OBJECTDIR}/app/connect_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/connect_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/result.o: app/result.c  .generated_files/flags/default/898345d7d8a8fe65f3f744d3a5b2867d5f374ec0 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/result.o.d 
	@${RM} ${OBJECTDIR}/app/result.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/result.c  -o ${OBJECTDIR}/app/result.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/result.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/app_data.o: app/app_data.c  .generated_files/flags/default/2453b9486f63d64fb0c806afb6829c79feed4c03 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/app_data.o.d 
	@${RM} ${OBJECTDIR}/app/app_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/app_data.c  -o ${OBJECTDIR}/app/app_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/app_data.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/leds.o: app/leds.c  .generated_files/flags/default/58cce1d30a58f7d501eb505fcf05a6a5fbdcf412 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/leds.o.d 
	@${RM} ${OBJECTDIR}/app/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/leds.c  -o ${OBJECTDIR}/app/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/leds.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/flasher.o: app/flasher.c  .generated_files/flags/default/d834166f02a9885611940f36c433d95154425e20 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/flasher.o.d 
	@${RM} ${OBJECTDIR}/app/flasher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/flasher.c  -o ${OBJECTDIR}/app/flasher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/flasher.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/logger/logger.o: logger/logger.c  .generated_files/flags/default/85f1a0198b9a32ee39b39008c9a2eee8af15cacf .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/logger" 
	@${RM} ${OBJECTDIR}/logger/logger.o.d 
	@${RM} ${OBJECTDIR}/logger/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  logger/logger.c  -o ${OBJECTDIR}/logger/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/logger/logger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o: mcc_generated_files/usb/usb_device_generic.c  .generated_files/flags/default/53069c15684f21809633320e3e36c1b015d5eff3 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_generic.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/2de05b0b89c4f4d9cee6820d22653766d1affe1a .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/ba0a44e4b94a9207caf3b76c18b1e5dc5f7a6f69 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/ad7804bd69620c0017572925a58a3263d0f4ea33 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/c575f868e28df79ed387049ca1a3a975682e89e7 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/c14fb7ed84422ed72380db0d726e479365b275ed .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/611ffb16917590a3d456cf5049b381852119f871 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/8f756e3ca2c1a44259725fd158627d5d0b3a4ed5 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/6b38519c037df4ef3cb7274d7fabe4375224daef .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/73645e3e33e8d1f508a6a0f10c949952bd616e77 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/5e6174a9e50f623f7be8a03094e7a1272ed3dbf2 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/44a10b12c0c75455adfb1635212a1adf57d3142a .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/189cbb2f0a9bbef4ee9c6f5a3ae41cabaac0fe9e .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c1.o: mcc_generated_files/i2c1.c  .generated_files/flags/default/39d028080d58198768daf1f48893f4922ebaa80a .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/d9d6452ab906d1b0bc7c7640d66072fa27d70a8c .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/delay.o: delay.c  .generated_files/flags/default/5c50f5f18d039b5f655861fd4dfb6cf54cd76970 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.o.d 
	@${RM} ${OBJECTDIR}/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  delay.c  -o ${OBJECTDIR}/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/app/flasher/flasher.o: app/flasher/flasher.c  .generated_files/flags/default/5d69f2822d5218af27dae3640023b9313b53959f .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/flasher" 
	@${RM} ${OBJECTDIR}/app/flasher/flasher.o.d 
	@${RM} ${OBJECTDIR}/app/flasher/flasher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/flasher/flasher.c  -o ${OBJECTDIR}/app/flasher/flasher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/flasher/flasher.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/programmer/bus.o: app/programmer/bus.c  .generated_files/flags/default/abfc9d4b418843f0c7ebc6141a5e7a44f63ed7a8 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/programmer" 
	@${RM} ${OBJECTDIR}/app/programmer/bus.o.d 
	@${RM} ${OBJECTDIR}/app/programmer/bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/programmer/bus.c  -o ${OBJECTDIR}/app/programmer/bus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/programmer/bus.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/programmer/programmer.o: app/programmer/programmer.c  .generated_files/flags/default/84f7b6467641f175a1d5d06f8a85755980e64100 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app/programmer" 
	@${RM} ${OBJECTDIR}/app/programmer/programmer.o.d 
	@${RM} ${OBJECTDIR}/app/programmer/programmer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/programmer/programmer.c  -o ${OBJECTDIR}/app/programmer/programmer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/programmer/programmer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/app.o: app/app.c  .generated_files/flags/default/1e20f3d5c058ecc770f97f863bccbf955daad66a .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/app.o.d 
	@${RM} ${OBJECTDIR}/app/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/app.c  -o ${OBJECTDIR}/app/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/app.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/connect_state.o: app/connect_state.c  .generated_files/flags/default/1fc242ce804616403f216118ce7a602a4a4ec09 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/connect_state.o.d 
	@${RM} ${OBJECTDIR}/app/connect_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/connect_state.c  -o ${OBJECTDIR}/app/connect_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/connect_state.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/result.o: app/result.c  .generated_files/flags/default/dce1b3b415a6254d2243df66451c5d5d4a7449ef .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/result.o.d 
	@${RM} ${OBJECTDIR}/app/result.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/result.c  -o ${OBJECTDIR}/app/result.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/result.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/app_data.o: app/app_data.c  .generated_files/flags/default/2da355a57e1e09880c75c8973e954f3d6f08931c .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/app_data.o.d 
	@${RM} ${OBJECTDIR}/app/app_data.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/app_data.c  -o ${OBJECTDIR}/app/app_data.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/app_data.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/leds.o: app/leds.c  .generated_files/flags/default/8c88f26b8552b1cb1d0365083d67e6fba83e6f14 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/leds.o.d 
	@${RM} ${OBJECTDIR}/app/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/leds.c  -o ${OBJECTDIR}/app/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/leds.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app/flasher.o: app/flasher.c  .generated_files/flags/default/6a487fe573c6493da4bb7d2a92d31181002abc31 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/app" 
	@${RM} ${OBJECTDIR}/app/flasher.o.d 
	@${RM} ${OBJECTDIR}/app/flasher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app/flasher.c  -o ${OBJECTDIR}/app/flasher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app/flasher.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/logger/logger.o: logger/logger.c  .generated_files/flags/default/fdf2744133cc8a714b80fb1d9a492b57afdf327d .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/logger" 
	@${RM} ${OBJECTDIR}/logger/logger.o.d 
	@${RM} ${OBJECTDIR}/logger/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  logger/logger.c  -o ${OBJECTDIR}/logger/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/logger/logger.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o: mcc_generated_files/usb/usb_device_generic.c  .generated_files/flags/default/9a215eed2dbd09967e591d3bcbcca5ec8cb00100 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_generic.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_generic.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o: mcc_generated_files/usb/usb_descriptors.c  .generated_files/flags/default/f87527ac4736089955cdbfc40336b27d83c535 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_descriptors.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_descriptors.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device.o: mcc_generated_files/usb/usb_device.c  .generated_files/flags/default/6d8462a091e3f1059fc6ba87f58dc9774e2b04ea .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o: mcc_generated_files/usb/usb_device_events.c  .generated_files/flags/default/dc71d855f6b50dd35c560fb0fe085ee0e2658001 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_device_events.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_device_events.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o: mcc_generated_files/usb/usb_hal_16bit.c  .generated_files/flags/default/65172113a3adcd704ac1d1d4b862a8c2b51326fa .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/usb" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/usb/usb_hal_16bit.c  -o ${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/usb/usb_hal_16bit.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system.o: mcc_generated_files/system.c  .generated_files/flags/default/fad4ce47b62080e7bf00729c272dd11695c0ae16 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system.c  -o ${OBJECTDIR}/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  .generated_files/flags/default/b3c636aa42ef183b65500a88f33f3fe5eecb258 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/7dbf374f78e5f73ec86722aeeb8d5abc1c788e75 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/traps.o: mcc_generated_files/traps.c  .generated_files/flags/default/2d7b1402baf1c9c9295738c06137fb71812b81d8 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/traps.c  -o ${OBJECTDIR}/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/clock.o: mcc_generated_files/clock.c  .generated_files/flags/default/5e02d5a02104245003ebd1e444881467635cf1a7 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/clock.c  -o ${OBJECTDIR}/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  .generated_files/flags/default/53ed71805b3b211c8d49d0f2df247d4adf486259 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/mcc.c  -o ${OBJECTDIR}/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr2.o: mcc_generated_files/tmr2.c  .generated_files/flags/default/53cd9582165bb96f8ed79248531bf1eb2d642de0 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/tmr3.o: mcc_generated_files/tmr3.c  .generated_files/flags/default/c3a4b94179b86fb114dbb1a514695ca1372cc822 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr3.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c1.o: mcc_generated_files/i2c1.c  .generated_files/flags/default/214c6d2f015660e08434016356418f6952b30448 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c1.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/7f2ddff91f740dd5c14cabd37142c5f737fff4b1 .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/delay.o: delay.c  .generated_files/flags/default/7637d428e4d43d65f6e43ebd2cd1539484aa3f0d .generated_files/flags/default/b3f7377e0834b0af39411d4b05ef64f524878e8b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.o.d 
	@${RM} ${OBJECTDIR}/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  delay.c  -o ${OBJECTDIR}/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/delay.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=10240,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/MainController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/MainController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=10240,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/MainController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
