##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pwdbsrv
ConfigurationName      :=Release
IntermediateDirectory  :=../bin/Release/$(ProjectName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/pwdbsrv"
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
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/pwdbsrv/pwdbsrv.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall --std=c++0x -m64 $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O2 -rdynamic
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../common $(IncludeSwitch)../proto $(IncludeSwitch)../pwcommon $(IncludeSwitch)../libcore/inc $(IncludeSwitch)../g3dlite/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)expat $(LibrarySwitch)zmq $(LibrarySwitch)ACE $(LibrarySwitch)tbb $(LibrarySwitch)core $(LibrarySwitch)log4cpp $(LibrarySwitch)pthread $(LibrarySwitch)mysqlclient $(LibrarySwitch)common $(LibrarySwitch)g3dlite 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../libcore/Release $(LibraryPathSwitch)../common/Release $(LibraryPathSwitch)../g3dlite/Release 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/pw_dbsrv_node$(ObjectSuffix) $(IntermediateDirectory)/pw_dbsrv_service$(ObjectSuffix) $(IntermediateDirectory)/pw_dbsrv_service_sql$(ObjectSuffix) $(IntermediateDirectory)/pw_dbsrv_table$(ObjectSuffix) $(IntermediateDirectory)/pw_dbsrv_service_loader$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(ObjectSuffix) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(ObjectSuffix) \
	$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(ObjectSuffix) 

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
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/main.cpp"

$(IntermediateDirectory)/pw_dbsrv_node$(ObjectSuffix): pw_dbsrv_node.cpp $(IntermediateDirectory)/pw_dbsrv_node$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_node.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_dbsrv_node$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_dbsrv_node$(DependSuffix): pw_dbsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_dbsrv_node$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_dbsrv_node$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_node.cpp"

$(IntermediateDirectory)/pw_dbsrv_node$(PreprocessSuffix): pw_dbsrv_node.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_dbsrv_node$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_node.cpp"

$(IntermediateDirectory)/pw_dbsrv_service$(ObjectSuffix): pw_dbsrv_service.cpp $(IntermediateDirectory)/pw_dbsrv_service$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_dbsrv_service$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_dbsrv_service$(DependSuffix): pw_dbsrv_service.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_dbsrv_service$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_dbsrv_service$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service.cpp"

$(IntermediateDirectory)/pw_dbsrv_service$(PreprocessSuffix): pw_dbsrv_service.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_dbsrv_service$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service.cpp"

$(IntermediateDirectory)/pw_dbsrv_service_sql$(ObjectSuffix): pw_dbsrv_service_sql.cpp $(IntermediateDirectory)/pw_dbsrv_service_sql$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_sql.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_dbsrv_service_sql$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_dbsrv_service_sql$(DependSuffix): pw_dbsrv_service_sql.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_dbsrv_service_sql$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_dbsrv_service_sql$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_sql.cpp"

$(IntermediateDirectory)/pw_dbsrv_service_sql$(PreprocessSuffix): pw_dbsrv_service_sql.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_dbsrv_service_sql$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_sql.cpp"

$(IntermediateDirectory)/pw_dbsrv_table$(ObjectSuffix): pw_dbsrv_table.cpp $(IntermediateDirectory)/pw_dbsrv_table$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_table.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_dbsrv_table$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_dbsrv_table$(DependSuffix): pw_dbsrv_table.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_dbsrv_table$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_dbsrv_table$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_table.cpp"

$(IntermediateDirectory)/pw_dbsrv_table$(PreprocessSuffix): pw_dbsrv_table.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_dbsrv_table$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_table.cpp"

$(IntermediateDirectory)/pw_dbsrv_service_loader$(ObjectSuffix): pw_dbsrv_service_loader.cpp $(IntermediateDirectory)/pw_dbsrv_service_loader$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_loader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_dbsrv_service_loader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_dbsrv_service_loader$(DependSuffix): pw_dbsrv_service_loader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_dbsrv_service_loader$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_dbsrv_service_loader$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_loader.cpp"

$(IntermediateDirectory)/pw_dbsrv_service_loader$(PreprocessSuffix): pw_dbsrv_service_loader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_dbsrv_service_loader$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/pw_dbsrv_service_loader.cpp"

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

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(ObjectSuffix): dist_impl/pw_rpcs_impl_simpldb.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldb.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(DependSuffix): dist_impl/pw_rpcs_impl_simpldb.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldb.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simpldb.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldb.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(ObjectSuffix): dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(DependSuffix): dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simplsqlexecutor.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(ObjectSuffix): dist_impl/pw_rpcs_impl_simpldbloader.cpp $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldbloader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(DependSuffix): dist_impl/pw_rpcs_impl_simpldbloader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(ObjectSuffix) -MF$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldbloader.cpp"

$(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(PreprocessSuffix): dist_impl/pw_rpcs_impl_simpldbloader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/pwdbsrv/dist_impl/pw_rpcs_impl_simpldbloader.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_node$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_node$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_node$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_sql$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_sql$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_sql$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_table$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_table$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_table$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_loader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_loader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_dbsrv_service_loader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_ngs_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pwcommon_pw_rpc_proxy$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldb$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simplsqlexecutor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dist_impl_pw_rpcs_impl_simpldbloader$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/pwdbsrv"


