##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pwaccsrv
ConfigurationName      :=Release
IntermediateDirectory  :=../bin/Release/$(ProjectName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/pwaccsrv"
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
OutputFile             :=../bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)TBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/pwaccsrv/pwaccsrv.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall --std=c++0x $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2 -rdynamic
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../common $(IncludeSwitch)../proto $(IncludeSwitch)../../shared/pwmsg $(IncludeSwitch)./msg $(IncludeSwitch)../mysql $(IncludeSwitch)../pwconnsrv $(IncludeSwitch)../pwcommon $(IncludeSwitch)../libcore/inc $(IncludeSwitch)../g3dlite/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)expat $(LibrarySwitch)zmq $(LibrarySwitch)ACE $(LibrarySwitch)tbb $(LibrarySwitch)core $(LibrarySwitch)log4cpp $(LibrarySwitch)pthread $(LibrarySwitch)protobuf $(LibrarySwitch)mysqlclient $(LibrarySwitch)common $(LibrarySwitch)g3dlite 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../libcore/Release $(LibraryPathSwitch)../common/Release $(LibraryPathSwitch)../g3dlite/Release 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/pw_accsrv_node$(ObjectSuffix) $(IntermediateDirectory)/pw_accsrv_service_port$(ObjectSuffix) $(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) $(IntermediateDirectory)/msg_accsrv.pb$(ObjectSuffix) $(IntermediateDirectory)/msg_msg.handler$(ObjectSuffix) $(IntermediateDirectory)/msg_msg.handler.CSLogin$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) \
	$(IntermediateDirectory)/pw_service_wallow$(ObjectSuffix) $(IntermediateDirectory)/pw_wallow_object$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(ObjectSuffix) 

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
	@test -d ../bin/Release/$(ProjectName) || $(MakeDirCommand) ../bin/Release/$(ProjectName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/main.cpp"

$(IntermediateDirectory)/pw_accsrv_node$(ObjectSuffix): pw_accsrv_node.cpp $(IntermediateDirectory)/pw_accsrv_node$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_node.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_accsrv_node$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_accsrv_node$(DependSuffix): pw_accsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_accsrv_node$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_accsrv_node$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_node.cpp"

$(IntermediateDirectory)/pw_accsrv_node$(PreprocessSuffix): pw_accsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_accsrv_node$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_node.cpp"

$(IntermediateDirectory)/pw_accsrv_service_port$(ObjectSuffix): pw_accsrv_service_port.cpp $(IntermediateDirectory)/pw_accsrv_service_port$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_service_port.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_accsrv_service_port$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_accsrv_service_port$(DependSuffix): pw_accsrv_service_port.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_accsrv_service_port$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_accsrv_service_port$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_service_port.cpp"

$(IntermediateDirectory)/pw_accsrv_service_port$(PreprocessSuffix): pw_accsrv_service_port.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_accsrv_service_port$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_accsrv_service_port.cpp"

$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix): ../../shared/pwmsg/options.pb.cc $(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix): ../../shared/pwmsg/options.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix) -MF$(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix) -MM "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc"

$(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix): ../../shared/pwmsg/options.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix) "/home/cbh/workspace/pwngs/shared/pwmsg/options.pb.cc"

$(IntermediateDirectory)/msg_accsrv.pb$(ObjectSuffix): msg/accsrv.pb.cc $(IntermediateDirectory)/msg_accsrv.pb$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/accsrv.pb.cc" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/msg_accsrv.pb$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/msg_accsrv.pb$(DependSuffix): msg/accsrv.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/msg_accsrv.pb$(ObjectSuffix) -MF$(IntermediateDirectory)/msg_accsrv.pb$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/accsrv.pb.cc"

$(IntermediateDirectory)/msg_accsrv.pb$(PreprocessSuffix): msg/accsrv.pb.cc
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/msg_accsrv.pb$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/accsrv.pb.cc"

$(IntermediateDirectory)/msg_msg.handler$(ObjectSuffix): msg/msg.handler.cpp $(IntermediateDirectory)/msg_msg.handler$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/msg_msg.handler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/msg_msg.handler$(DependSuffix): msg/msg.handler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/msg_msg.handler$(ObjectSuffix) -MF$(IntermediateDirectory)/msg_msg.handler$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.cpp"

$(IntermediateDirectory)/msg_msg.handler$(PreprocessSuffix): msg/msg.handler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/msg_msg.handler$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.cpp"

$(IntermediateDirectory)/msg_msg.handler.CSLogin$(ObjectSuffix): msg/msg.handler.CSLogin.cpp $(IntermediateDirectory)/msg_msg.handler.CSLogin$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.CSLogin.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/msg_msg.handler.CSLogin$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/msg_msg.handler.CSLogin$(DependSuffix): msg/msg.handler.CSLogin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/msg_msg.handler.CSLogin$(ObjectSuffix) -MF$(IntermediateDirectory)/msg_msg.handler.CSLogin$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.CSLogin.cpp"

$(IntermediateDirectory)/msg_msg.handler.CSLogin$(PreprocessSuffix): msg/msg.handler.CSLogin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/msg_msg.handler.CSLogin$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/msg/msg.handler.CSLogin.cpp"

$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix): ../pwcommon/pw_ngs_utils.cpp $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix): ../pwcommon/pw_ngs_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix): ../pwcommon/pw_ngs_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(ObjectSuffix): ../pwcommon/pw_connsrv_utils.cpp $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwcommon/pw_connsrv_utils.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(DependSuffix): ../pwcommon/pw_connsrv_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwcommon/pw_connsrv_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(PreprocessSuffix): ../pwcommon/pw_connsrv_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwcommon/pw_connsrv_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix): ../pwcommon/pw_rpc_proxy.cpp $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix): ../pwcommon/pw_rpc_proxy.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) -MF$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp"

$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix): ../pwcommon/pw_rpc_proxy.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp"

$(IntermediateDirectory)/pw_service_wallow$(ObjectSuffix): pw_service_wallow.cpp $(IntermediateDirectory)/pw_service_wallow$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_service_wallow.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_service_wallow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_service_wallow$(DependSuffix): pw_service_wallow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_service_wallow$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_service_wallow$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_service_wallow.cpp"

$(IntermediateDirectory)/pw_service_wallow$(PreprocessSuffix): pw_service_wallow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_service_wallow$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_service_wallow.cpp"

$(IntermediateDirectory)/pw_wallow_object$(ObjectSuffix): pw_wallow_object.cpp $(IntermediateDirectory)/pw_wallow_object$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_wallow_object.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_wallow_object$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_wallow_object$(DependSuffix): pw_wallow_object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_wallow_object$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_wallow_object$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_wallow_object.cpp"

$(IntermediateDirectory)/pw_wallow_object$(PreprocessSuffix): pw_wallow_object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_wallow_object$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/pw_wallow_object.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(ObjectSuffix): dist_impl/pw_rpcs_impl_simplacc.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplacc.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(DependSuffix): dist_impl/pw_rpcs_impl_simplacc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplacc.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simplacc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplacc.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(ObjectSuffix): dist_impl/pw_rpcs_impl_simplwallow.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplwallow.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(DependSuffix): dist_impl/pw_rpcs_impl_simplwallow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplwallow.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simplwallow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwaccsrv/dist_impl/pw_rpcs_impl_simplwallow.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_node$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_node$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_node$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_service_port$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_service_port$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_accsrv_service_port$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwmsg_options.pb$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/msg_accsrv.pb$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/msg_accsrv.pb$(DependSuffix)
	$(RM) $(IntermediateDirectory)/msg_accsrv.pb$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler$(DependSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler.CSLogin$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler.CSLogin$(DependSuffix)
	$(RM) $(IntermediateDirectory)/msg_msg.handler.CSLogin$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_connsrv_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_service_wallow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_service_wallow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_service_wallow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_wallow_object$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_wallow_object$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_wallow_object$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplacc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplwallow$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/pwaccsrv"


