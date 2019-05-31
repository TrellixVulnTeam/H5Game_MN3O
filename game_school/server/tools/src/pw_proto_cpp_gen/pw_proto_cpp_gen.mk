##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pw_proto_cpp_gen
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen"
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
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/pw_proto_cpp_gen.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             :=  $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../../shared/pwmsg $(IncludeSwitch)../common 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)protobuf $(LibrarySwitch)uuid 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/common_tokenizer$(ObjectSuffix) $(IntermediateDirectory)/gen_defs$(ObjectSuffix) $(IntermediateDirectory)/gen_hpps$(ObjectSuffix) $(IntermediateDirectory)/gen_cpps$(ObjectSuffix) $(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) $(IntermediateDirectory)/gen_lua$(ObjectSuffix) 

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
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/main.cpp"

$(IntermediateDirectory)/common_tokenizer$(ObjectSuffix): ../common/tokenizer.cpp $(IntermediateDirectory)/common_tokenizer$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/common_tokenizer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_tokenizer$(DependSuffix): ../common/tokenizer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/common_tokenizer$(ObjectSuffix) -MF$(IntermediateDirectory)/common_tokenizer$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp"

$(IntermediateDirectory)/common_tokenizer$(PreprocessSuffix): ../common/tokenizer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_tokenizer$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp"

$(IntermediateDirectory)/gen_defs$(ObjectSuffix): gen_defs.cpp $(IntermediateDirectory)/gen_defs$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_defs.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gen_defs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gen_defs$(DependSuffix): gen_defs.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gen_defs$(ObjectSuffix) -MF$(IntermediateDirectory)/gen_defs$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_defs.cpp"

$(IntermediateDirectory)/gen_defs$(PreprocessSuffix): gen_defs.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gen_defs$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_defs.cpp"

$(IntermediateDirectory)/gen_hpps$(ObjectSuffix): gen_hpps.cpp $(IntermediateDirectory)/gen_hpps$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_hpps.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gen_hpps$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gen_hpps$(DependSuffix): gen_hpps.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gen_hpps$(ObjectSuffix) -MF$(IntermediateDirectory)/gen_hpps$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_hpps.cpp"

$(IntermediateDirectory)/gen_hpps$(PreprocessSuffix): gen_hpps.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gen_hpps$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_hpps.cpp"

$(IntermediateDirectory)/gen_cpps$(ObjectSuffix): gen_cpps.cpp $(IntermediateDirectory)/gen_cpps$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_cpps.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gen_cpps$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gen_cpps$(DependSuffix): gen_cpps.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gen_cpps$(ObjectSuffix) -MF$(IntermediateDirectory)/gen_cpps$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_cpps.cpp"

$(IntermediateDirectory)/gen_cpps$(PreprocessSuffix): gen_cpps.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gen_cpps$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_cpps.cpp"

$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix): ../../shared/pwmsg/options.pb.cc $(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix): ../../shared/pwmsg/options.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) -MF$(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix) -MM "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc"

$(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix): ../../shared/pwmsg/options.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix) "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc"

$(IntermediateDirectory)/gen_lua$(ObjectSuffix): gen_lua.cpp $(IntermediateDirectory)/gen_lua$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_lua.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/gen_lua$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gen_lua$(DependSuffix): gen_lua.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gen_lua$(ObjectSuffix) -MF$(IntermediateDirectory)/gen_lua$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_lua.cpp"

$(IntermediateDirectory)/gen_lua$(PreprocessSuffix): gen_lua.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gen_lua$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pw_proto_cpp_gen/gen_lua.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/common_tokenizer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/common_tokenizer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/common_tokenizer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gen_defs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gen_defs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gen_defs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gen_hpps$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gen_hpps$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gen_hpps$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gen_cpps$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gen_cpps$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gen_cpps$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gen_lua$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gen_lua$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gen_lua$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/pw_proto_cpp_gen"


