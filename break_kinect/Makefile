# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined, otherwise the make command will not work
ifndef OF_ROOT
    OF_ROOT= #$(realpath ../..)
endif

# call the project makefile, otherwise the make command will not work
include $(OF_ROOT)/
#/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk is the default location of the openframeworks makefile, 
#if you followed the default install procedure it should be there 
