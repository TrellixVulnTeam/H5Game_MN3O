##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pwdist
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/pwdist"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=cbh
Date                   :=2013年01月24日
CodeLitePath           :="/home/cbh/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)TBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/pwdist/pwdist.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := --std=c++0x $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../common $(IncludeSwitch)../proto $(IncludeSwitch)../libcore/inc $(IncludeSwitch)../g3dlite/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)expat $(LibrarySwitch)zmq $(LibrarySwitch)ACE $(LibrarySwitch)tbb $(LibrarySwitch)log4cpp $(LibrarySwitch)pthread $(LibrarySwitch)core $(LibrarySwitch)common $(LibrarySwitch)lua5.1 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../libcore/Release $(LibraryPathSwitch)../common/Release 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/main_test$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdist/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdist/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdist/main.cpp"

$(IntermediateDirectory)/main_test$(ObjectSuffix): main_test.cpp $(IntermediateDirectory)/main_test$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdist/main_test.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main_test$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main_test$(DependSuffix): main_test.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main_test$(ObjectSuffix) -MF$(IntermediateDirectory)/main_test$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdist/main_test.cpp"

$(IntermediateDirectory)/main_test$(PreprocessSuffix): main_test.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main_test$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdist/main_test.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main_test$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main_test$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main_test$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/pwdist"


