##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pwconnsrv
ConfigurationName      :=Release
IntermediateDirectory  :=../bin/Release/$(ProjectName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/pwconnsrv"
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
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/pwconnsrv/pwconnsrv.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall --std=c++0x $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2 -rdynamic
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../common $(IncludeSwitch)../proto $(IncludeSwitch)../pwcommon $(IncludeSwitch)../libcore/inc $(IncludeSwitch)../g3dlite/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)expat $(LibrarySwitch)zmq $(LibrarySwitch)ACE $(LibrarySwitch)tbb $(LibrarySwitch)core $(LibrarySwitch)log4cpp $(LibrarySwitch)pthread $(LibrarySwitch)common $(LibrarySwitch)g3dlite 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../libcore/Release $(LibraryPathSwitch)../common/Release $(LibraryPathSwitch)../g3dlite/Release 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/pw_connsrv_listener$(ObjectSuffix) $(IntermediateDirectory)/pw_connsrv_connection$(ObjectSuffix) $(IntermediateDirectory)/pw_connsrv_node$(ObjectSuffix) $(IntermediateDirectory)/pw_connsrv_service_port$(ObjectSuffix) $(IntermediateDirectory)/pw_epoll_reactor$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(ObjectSuffix) \
	

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
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/main.cpp"

$(IntermediateDirectory)/pw_connsrv_listener$(ObjectSuffix): pw_connsrv_listener.cpp $(IntermediateDirectory)/pw_connsrv_listener$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_listener.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_connsrv_listener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_connsrv_listener$(DependSuffix): pw_connsrv_listener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_connsrv_listener$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_connsrv_listener$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_listener.cpp"

$(IntermediateDirectory)/pw_connsrv_listener$(PreprocessSuffix): pw_connsrv_listener.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_connsrv_listener$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_listener.cpp"

$(IntermediateDirectory)/pw_connsrv_connection$(ObjectSuffix): pw_connsrv_connection.cpp $(IntermediateDirectory)/pw_connsrv_connection$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_connection.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_connsrv_connection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_connsrv_connection$(DependSuffix): pw_connsrv_connection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_connsrv_connection$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_connsrv_connection$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_connection.cpp"

$(IntermediateDirectory)/pw_connsrv_connection$(PreprocessSuffix): pw_connsrv_connection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_connsrv_connection$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_connection.cpp"

$(IntermediateDirectory)/pw_connsrv_node$(ObjectSuffix): pw_connsrv_node.cpp $(IntermediateDirectory)/pw_connsrv_node$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_node.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_connsrv_node$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_connsrv_node$(DependSuffix): pw_connsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_connsrv_node$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_connsrv_node$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_node.cpp"

$(IntermediateDirectory)/pw_connsrv_node$(PreprocessSuffix): pw_connsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_connsrv_node$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_node.cpp"

$(IntermediateDirectory)/pw_connsrv_service_port$(ObjectSuffix): pw_connsrv_service_port.cpp $(IntermediateDirectory)/pw_connsrv_service_port$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_service_port.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_connsrv_service_port$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_connsrv_service_port$(DependSuffix): pw_connsrv_service_port.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_connsrv_service_port$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_connsrv_service_port$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_service_port.cpp"

$(IntermediateDirectory)/pw_connsrv_service_port$(PreprocessSuffix): pw_connsrv_service_port.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_connsrv_service_port$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_connsrv_service_port.cpp"

$(IntermediateDirectory)/pw_epoll_reactor$(ObjectSuffix): pw_epoll_reactor.cpp $(IntermediateDirectory)/pw_epoll_reactor$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_epoll_reactor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_epoll_reactor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_epoll_reactor$(DependSuffix): pw_epoll_reactor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_epoll_reactor$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_epoll_reactor$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_epoll_reactor.cpp"

$(IntermediateDirectory)/pw_epoll_reactor$(PreprocessSuffix): pw_epoll_reactor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_epoll_reactor$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/pw_epoll_reactor.cpp"

$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix): ../pwcommon/pw_ngs_utils.cpp $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix): ../pwcommon/pw_ngs_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix): ../pwcommon/pw_ngs_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwcommon/pw_ngs_utils.cpp"

$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix): ../pwcommon/pw_rpc_proxy.cpp $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix): ../pwcommon/pw_rpc_proxy.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) -MF$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp"

$(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix): ../pwcommon/pw_rpc_proxy.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwcommon/pw_rpc_proxy.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(ObjectSuffix): dist_impl/pw_rpcs_impl_connection.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_connection.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(DependSuffix): dist_impl/pw_rpcs_impl_connection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_connection.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(PreprocessSuffix): dist_impl/pw_rpcs_impl_connection.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_connection.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(ObjectSuffix): dist_impl/pw_rpcs_impl_simplsend.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_simplsend.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(DependSuffix): dist_impl/pw_rpcs_impl_simplsend.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_simplsend.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simplsend.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwconnsrv/dist_impl/pw_rpcs_impl_simplsend.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_listener$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_listener$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_listener$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_connection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_connection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_connection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_node$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_node$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_node$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_service_port$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_service_port$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_connsrv_service_port$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_epoll_reactor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_epoll_reactor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_epoll_reactor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_connection$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsend$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/pwconnsrv"


