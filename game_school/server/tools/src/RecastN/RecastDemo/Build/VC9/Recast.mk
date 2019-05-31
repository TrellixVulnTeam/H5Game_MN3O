##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Recast
ConfigurationName      :=Debug
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/projects/test/Recast/RecastDemo/Build/VC9"
ProjectPath            := "/home/cbh/projects/test/Recast/RecastDemo/Build/VC9"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=cbh
Date                   :=2011年08月18日
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
OutputFile             :=
Preprocessors          :=$(PreprocessorSwitch)WIN32 $(PreprocessorSwitch)_DEBUG $(PreprocessorSwitch)_WINDOWS $(PreprocessorSwitch)_CRT_SECURE_NO_WARNINGS 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cbh/projects/test/Recast/RecastDemo/Build/VC9/Recast.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../Contrib/fastlz $(IncludeSwitch)../../Contrib/SDL/include $(IncludeSwitch)../../Include $(IncludeSwitch)../../../DetourCrowd/Include $(IncludeSwitch)../../../Detour/Include $(IncludeSwitch)../../../DebugUtils/Include $(IncludeSwitch)../../../Recast/Include $(IncludeSwitch)../../Contrib $(IncludeSwitch)../../../DetourTileCache/Include 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)opengl32.lib $(LibrarySwitch)glu32.lib $(LibrarySwitch)sdlmain.lib $(LibrarySwitch)sdl.lib 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../Contrib/SDL/lib 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/Source_Recast$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastAlloc$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastArea$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastContour$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastFilter$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastLayers$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastMesh$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastMeshDetail$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastRasterization$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastRegion$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_DetourAlloc$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourCommon$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourNavMesh$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourNavMeshQuery$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourNode$(ObjectSuffix) $(IntermediateDirectory)/Source_ChunkyTriMesh$(ObjectSuffix) $(IntermediateDirectory)/Source_ConvexVolumeTool$(ObjectSuffix) $(IntermediateDirectory)/Source_CrowdTool$(ObjectSuffix) $(IntermediateDirectory)/Source_Filelist$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_imgui$(ObjectSuffix) $(IntermediateDirectory)/Source_imguiRenderGL$(ObjectSuffix) $(IntermediateDirectory)/Source_InputGeom$(ObjectSuffix) $(IntermediateDirectory)/Source_main$(ObjectSuffix) $(IntermediateDirectory)/Source_MeshLoaderObj$(ObjectSuffix) $(IntermediateDirectory)/Source_NavMeshTesterTool$(ObjectSuffix) $(IntermediateDirectory)/Source_OffMeshConnectionTool$(ObjectSuffix) $(IntermediateDirectory)/Source_PerfTimer$(ObjectSuffix) $(IntermediateDirectory)/Source_Sample$(ObjectSuffix) $(IntermediateDirectory)/Source_Sample_Debug$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_Sample_SoloMesh$(ObjectSuffix) $(IntermediateDirectory)/Source_Sample_TempObstacles$(ObjectSuffix) $(IntermediateDirectory)/Source_Sample_TileMesh$(ObjectSuffix) $(IntermediateDirectory)/Source_SampleInterfaces$(ObjectSuffix) $(IntermediateDirectory)/Source_SlideShow$(ObjectSuffix) $(IntermediateDirectory)/Source_TestCase$(ObjectSuffix) $(IntermediateDirectory)/Source_ValueHistory$(ObjectSuffix) $(IntermediateDirectory)/Source_DebugDraw$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourDebugDraw$(ObjectSuffix) $(IntermediateDirectory)/Source_RecastDebugDraw$(ObjectSuffix) \
	$(IntermediateDirectory)/Source_RecastDump$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourCrowd$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourLocalBoundary$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourPathCorridor$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourPathQueue$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourProximityGrid$(ObjectSuffix) $(IntermediateDirectory)/fastlz_fastlz$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourTileCache$(ObjectSuffix) $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(ObjectSuffix) \
	

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Source_Recast$(ObjectSuffix): ../../../Recast/Source/Recast.cpp $(IntermediateDirectory)/Source_Recast$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/Recast.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Recast$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Recast$(DependSuffix): ../../../Recast/Source/Recast.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Recast$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Recast$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/Recast.cpp"

$(IntermediateDirectory)/Source_Recast$(PreprocessSuffix): ../../../Recast/Source/Recast.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Recast$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/Recast.cpp"

$(IntermediateDirectory)/Source_RecastAlloc$(ObjectSuffix): ../../../Recast/Source/RecastAlloc.cpp $(IntermediateDirectory)/Source_RecastAlloc$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastAlloc.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastAlloc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastAlloc$(DependSuffix): ../../../Recast/Source/RecastAlloc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastAlloc$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastAlloc$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastAlloc.cpp"

$(IntermediateDirectory)/Source_RecastAlloc$(PreprocessSuffix): ../../../Recast/Source/RecastAlloc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastAlloc$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastAlloc.cpp"

$(IntermediateDirectory)/Source_RecastArea$(ObjectSuffix): ../../../Recast/Source/RecastArea.cpp $(IntermediateDirectory)/Source_RecastArea$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastArea.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastArea$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastArea$(DependSuffix): ../../../Recast/Source/RecastArea.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastArea$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastArea$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastArea.cpp"

$(IntermediateDirectory)/Source_RecastArea$(PreprocessSuffix): ../../../Recast/Source/RecastArea.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastArea$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastArea.cpp"

$(IntermediateDirectory)/Source_RecastContour$(ObjectSuffix): ../../../Recast/Source/RecastContour.cpp $(IntermediateDirectory)/Source_RecastContour$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastContour.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastContour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastContour$(DependSuffix): ../../../Recast/Source/RecastContour.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastContour$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastContour$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastContour.cpp"

$(IntermediateDirectory)/Source_RecastContour$(PreprocessSuffix): ../../../Recast/Source/RecastContour.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastContour$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastContour.cpp"

$(IntermediateDirectory)/Source_RecastFilter$(ObjectSuffix): ../../../Recast/Source/RecastFilter.cpp $(IntermediateDirectory)/Source_RecastFilter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastFilter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastFilter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastFilter$(DependSuffix): ../../../Recast/Source/RecastFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastFilter$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastFilter$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastFilter.cpp"

$(IntermediateDirectory)/Source_RecastFilter$(PreprocessSuffix): ../../../Recast/Source/RecastFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastFilter$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastFilter.cpp"

$(IntermediateDirectory)/Source_RecastLayers$(ObjectSuffix): ../../../Recast/Source/RecastLayers.cpp $(IntermediateDirectory)/Source_RecastLayers$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastLayers.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastLayers$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastLayers$(DependSuffix): ../../../Recast/Source/RecastLayers.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastLayers$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastLayers$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastLayers.cpp"

$(IntermediateDirectory)/Source_RecastLayers$(PreprocessSuffix): ../../../Recast/Source/RecastLayers.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastLayers$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastLayers.cpp"

$(IntermediateDirectory)/Source_RecastMesh$(ObjectSuffix): ../../../Recast/Source/RecastMesh.cpp $(IntermediateDirectory)/Source_RecastMesh$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastMesh.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastMesh$(DependSuffix): ../../../Recast/Source/RecastMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastMesh$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastMesh.cpp"

$(IntermediateDirectory)/Source_RecastMesh$(PreprocessSuffix): ../../../Recast/Source/RecastMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastMesh$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastMesh.cpp"

$(IntermediateDirectory)/Source_RecastMeshDetail$(ObjectSuffix): ../../../Recast/Source/RecastMeshDetail.cpp $(IntermediateDirectory)/Source_RecastMeshDetail$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastMeshDetail.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastMeshDetail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastMeshDetail$(DependSuffix): ../../../Recast/Source/RecastMeshDetail.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastMeshDetail$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastMeshDetail$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastMeshDetail.cpp"

$(IntermediateDirectory)/Source_RecastMeshDetail$(PreprocessSuffix): ../../../Recast/Source/RecastMeshDetail.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastMeshDetail$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastMeshDetail.cpp"

$(IntermediateDirectory)/Source_RecastRasterization$(ObjectSuffix): ../../../Recast/Source/RecastRasterization.cpp $(IntermediateDirectory)/Source_RecastRasterization$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastRasterization.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastRasterization$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastRasterization$(DependSuffix): ../../../Recast/Source/RecastRasterization.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastRasterization$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastRasterization$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastRasterization.cpp"

$(IntermediateDirectory)/Source_RecastRasterization$(PreprocessSuffix): ../../../Recast/Source/RecastRasterization.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastRasterization$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastRasterization.cpp"

$(IntermediateDirectory)/Source_RecastRegion$(ObjectSuffix): ../../../Recast/Source/RecastRegion.cpp $(IntermediateDirectory)/Source_RecastRegion$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Recast/Source/RecastRegion.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastRegion$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastRegion$(DependSuffix): ../../../Recast/Source/RecastRegion.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastRegion$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastRegion$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Recast/Source/RecastRegion.cpp"

$(IntermediateDirectory)/Source_RecastRegion$(PreprocessSuffix): ../../../Recast/Source/RecastRegion.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastRegion$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Recast/Source/RecastRegion.cpp"

$(IntermediateDirectory)/Source_DetourAlloc$(ObjectSuffix): ../../../Detour/Source/DetourAlloc.cpp $(IntermediateDirectory)/Source_DetourAlloc$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourAlloc.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourAlloc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourAlloc$(DependSuffix): ../../../Detour/Source/DetourAlloc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourAlloc$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourAlloc$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourAlloc.cpp"

$(IntermediateDirectory)/Source_DetourAlloc$(PreprocessSuffix): ../../../Detour/Source/DetourAlloc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourAlloc$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourAlloc.cpp"

$(IntermediateDirectory)/Source_DetourCommon$(ObjectSuffix): ../../../Detour/Source/DetourCommon.cpp $(IntermediateDirectory)/Source_DetourCommon$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourCommon.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourCommon$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourCommon$(DependSuffix): ../../../Detour/Source/DetourCommon.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourCommon$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourCommon$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourCommon.cpp"

$(IntermediateDirectory)/Source_DetourCommon$(PreprocessSuffix): ../../../Detour/Source/DetourCommon.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourCommon$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourCommon.cpp"

$(IntermediateDirectory)/Source_DetourNavMesh$(ObjectSuffix): ../../../Detour/Source/DetourNavMesh.cpp $(IntermediateDirectory)/Source_DetourNavMesh$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMesh.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourNavMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourNavMesh$(DependSuffix): ../../../Detour/Source/DetourNavMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourNavMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourNavMesh$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMesh.cpp"

$(IntermediateDirectory)/Source_DetourNavMesh$(PreprocessSuffix): ../../../Detour/Source/DetourNavMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourNavMesh$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMesh.cpp"

$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(ObjectSuffix): ../../../Detour/Source/DetourNavMeshBuilder.cpp $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshBuilder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(DependSuffix): ../../../Detour/Source/DetourNavMeshBuilder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshBuilder.cpp"

$(IntermediateDirectory)/Source_DetourNavMeshBuilder$(PreprocessSuffix): ../../../Detour/Source/DetourNavMeshBuilder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshBuilder.cpp"

$(IntermediateDirectory)/Source_DetourNavMeshQuery$(ObjectSuffix): ../../../Detour/Source/DetourNavMeshQuery.cpp $(IntermediateDirectory)/Source_DetourNavMeshQuery$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshQuery.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourNavMeshQuery$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourNavMeshQuery$(DependSuffix): ../../../Detour/Source/DetourNavMeshQuery.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourNavMeshQuery$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourNavMeshQuery$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshQuery.cpp"

$(IntermediateDirectory)/Source_DetourNavMeshQuery$(PreprocessSuffix): ../../../Detour/Source/DetourNavMeshQuery.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourNavMeshQuery$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourNavMeshQuery.cpp"

$(IntermediateDirectory)/Source_DetourNode$(ObjectSuffix): ../../../Detour/Source/DetourNode.cpp $(IntermediateDirectory)/Source_DetourNode$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/Detour/Source/DetourNode.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourNode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourNode$(DependSuffix): ../../../Detour/Source/DetourNode.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourNode$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourNode$(DependSuffix) -MM "/home/cbh/projects/test/Recast/Detour/Source/DetourNode.cpp"

$(IntermediateDirectory)/Source_DetourNode$(PreprocessSuffix): ../../../Detour/Source/DetourNode.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourNode$(PreprocessSuffix) "/home/cbh/projects/test/Recast/Detour/Source/DetourNode.cpp"

$(IntermediateDirectory)/Source_ChunkyTriMesh$(ObjectSuffix): ../../Source/ChunkyTriMesh.cpp $(IntermediateDirectory)/Source_ChunkyTriMesh$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/ChunkyTriMesh.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_ChunkyTriMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ChunkyTriMesh$(DependSuffix): ../../Source/ChunkyTriMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ChunkyTriMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ChunkyTriMesh$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/ChunkyTriMesh.cpp"

$(IntermediateDirectory)/Source_ChunkyTriMesh$(PreprocessSuffix): ../../Source/ChunkyTriMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ChunkyTriMesh$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/ChunkyTriMesh.cpp"

$(IntermediateDirectory)/Source_ConvexVolumeTool$(ObjectSuffix): ../../Source/ConvexVolumeTool.cpp $(IntermediateDirectory)/Source_ConvexVolumeTool$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/ConvexVolumeTool.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_ConvexVolumeTool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ConvexVolumeTool$(DependSuffix): ../../Source/ConvexVolumeTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ConvexVolumeTool$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ConvexVolumeTool$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/ConvexVolumeTool.cpp"

$(IntermediateDirectory)/Source_ConvexVolumeTool$(PreprocessSuffix): ../../Source/ConvexVolumeTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ConvexVolumeTool$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/ConvexVolumeTool.cpp"

$(IntermediateDirectory)/Source_CrowdTool$(ObjectSuffix): ../../Source/CrowdTool.cpp $(IntermediateDirectory)/Source_CrowdTool$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/CrowdTool.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_CrowdTool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_CrowdTool$(DependSuffix): ../../Source/CrowdTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_CrowdTool$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_CrowdTool$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/CrowdTool.cpp"

$(IntermediateDirectory)/Source_CrowdTool$(PreprocessSuffix): ../../Source/CrowdTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_CrowdTool$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/CrowdTool.cpp"

$(IntermediateDirectory)/Source_Filelist$(ObjectSuffix): ../../Source/Filelist.cpp $(IntermediateDirectory)/Source_Filelist$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Filelist.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Filelist$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Filelist$(DependSuffix): ../../Source/Filelist.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Filelist$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Filelist$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Filelist.cpp"

$(IntermediateDirectory)/Source_Filelist$(PreprocessSuffix): ../../Source/Filelist.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Filelist$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Filelist.cpp"

$(IntermediateDirectory)/Source_imgui$(ObjectSuffix): ../../Source/imgui.cpp $(IntermediateDirectory)/Source_imgui$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/imgui.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_imgui$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_imgui$(DependSuffix): ../../Source/imgui.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_imgui$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_imgui$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/imgui.cpp"

$(IntermediateDirectory)/Source_imgui$(PreprocessSuffix): ../../Source/imgui.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_imgui$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/imgui.cpp"

$(IntermediateDirectory)/Source_imguiRenderGL$(ObjectSuffix): ../../Source/imguiRenderGL.cpp $(IntermediateDirectory)/Source_imguiRenderGL$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/imguiRenderGL.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_imguiRenderGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_imguiRenderGL$(DependSuffix): ../../Source/imguiRenderGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_imguiRenderGL$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_imguiRenderGL$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/imguiRenderGL.cpp"

$(IntermediateDirectory)/Source_imguiRenderGL$(PreprocessSuffix): ../../Source/imguiRenderGL.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_imguiRenderGL$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/imguiRenderGL.cpp"

$(IntermediateDirectory)/Source_InputGeom$(ObjectSuffix): ../../Source/InputGeom.cpp $(IntermediateDirectory)/Source_InputGeom$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/InputGeom.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_InputGeom$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_InputGeom$(DependSuffix): ../../Source/InputGeom.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_InputGeom$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_InputGeom$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/InputGeom.cpp"

$(IntermediateDirectory)/Source_InputGeom$(PreprocessSuffix): ../../Source/InputGeom.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_InputGeom$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/InputGeom.cpp"

$(IntermediateDirectory)/Source_main$(ObjectSuffix): ../../Source/main.cpp $(IntermediateDirectory)/Source_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_main$(DependSuffix): ../../Source/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_main$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_main$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/main.cpp"

$(IntermediateDirectory)/Source_main$(PreprocessSuffix): ../../Source/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_main$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/main.cpp"

$(IntermediateDirectory)/Source_MeshLoaderObj$(ObjectSuffix): ../../Source/MeshLoaderObj.cpp $(IntermediateDirectory)/Source_MeshLoaderObj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/MeshLoaderObj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_MeshLoaderObj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_MeshLoaderObj$(DependSuffix): ../../Source/MeshLoaderObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_MeshLoaderObj$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_MeshLoaderObj$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/MeshLoaderObj.cpp"

$(IntermediateDirectory)/Source_MeshLoaderObj$(PreprocessSuffix): ../../Source/MeshLoaderObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_MeshLoaderObj$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/MeshLoaderObj.cpp"

$(IntermediateDirectory)/Source_NavMeshTesterTool$(ObjectSuffix): ../../Source/NavMeshTesterTool.cpp $(IntermediateDirectory)/Source_NavMeshTesterTool$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/NavMeshTesterTool.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_NavMeshTesterTool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_NavMeshTesterTool$(DependSuffix): ../../Source/NavMeshTesterTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_NavMeshTesterTool$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_NavMeshTesterTool$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/NavMeshTesterTool.cpp"

$(IntermediateDirectory)/Source_NavMeshTesterTool$(PreprocessSuffix): ../../Source/NavMeshTesterTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_NavMeshTesterTool$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/NavMeshTesterTool.cpp"

$(IntermediateDirectory)/Source_OffMeshConnectionTool$(ObjectSuffix): ../../Source/OffMeshConnectionTool.cpp $(IntermediateDirectory)/Source_OffMeshConnectionTool$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/OffMeshConnectionTool.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_OffMeshConnectionTool$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_OffMeshConnectionTool$(DependSuffix): ../../Source/OffMeshConnectionTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_OffMeshConnectionTool$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_OffMeshConnectionTool$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/OffMeshConnectionTool.cpp"

$(IntermediateDirectory)/Source_OffMeshConnectionTool$(PreprocessSuffix): ../../Source/OffMeshConnectionTool.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_OffMeshConnectionTool$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/OffMeshConnectionTool.cpp"

$(IntermediateDirectory)/Source_PerfTimer$(ObjectSuffix): ../../Source/PerfTimer.cpp $(IntermediateDirectory)/Source_PerfTimer$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/PerfTimer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_PerfTimer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_PerfTimer$(DependSuffix): ../../Source/PerfTimer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_PerfTimer$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_PerfTimer$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/PerfTimer.cpp"

$(IntermediateDirectory)/Source_PerfTimer$(PreprocessSuffix): ../../Source/PerfTimer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_PerfTimer$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/PerfTimer.cpp"

$(IntermediateDirectory)/Source_Sample$(ObjectSuffix): ../../Source/Sample.cpp $(IntermediateDirectory)/Source_Sample$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sample$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sample$(DependSuffix): ../../Source/Sample.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sample$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sample$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample.cpp"

$(IntermediateDirectory)/Source_Sample$(PreprocessSuffix): ../../Source/Sample.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sample$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample.cpp"

$(IntermediateDirectory)/Source_Sample_Debug$(ObjectSuffix): ../../Source/Sample_Debug.cpp $(IntermediateDirectory)/Source_Sample_Debug$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_Debug.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sample_Debug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sample_Debug$(DependSuffix): ../../Source/Sample_Debug.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sample_Debug$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sample_Debug$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_Debug.cpp"

$(IntermediateDirectory)/Source_Sample_Debug$(PreprocessSuffix): ../../Source/Sample_Debug.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sample_Debug$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_Debug.cpp"

$(IntermediateDirectory)/Source_Sample_SoloMesh$(ObjectSuffix): ../../Source/Sample_SoloMesh.cpp $(IntermediateDirectory)/Source_Sample_SoloMesh$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_SoloMesh.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sample_SoloMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sample_SoloMesh$(DependSuffix): ../../Source/Sample_SoloMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sample_SoloMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sample_SoloMesh$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_SoloMesh.cpp"

$(IntermediateDirectory)/Source_Sample_SoloMesh$(PreprocessSuffix): ../../Source/Sample_SoloMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sample_SoloMesh$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_SoloMesh.cpp"

$(IntermediateDirectory)/Source_Sample_TempObstacles$(ObjectSuffix): ../../Source/Sample_TempObstacles.cpp $(IntermediateDirectory)/Source_Sample_TempObstacles$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TempObstacles.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sample_TempObstacles$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sample_TempObstacles$(DependSuffix): ../../Source/Sample_TempObstacles.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sample_TempObstacles$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sample_TempObstacles$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TempObstacles.cpp"

$(IntermediateDirectory)/Source_Sample_TempObstacles$(PreprocessSuffix): ../../Source/Sample_TempObstacles.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sample_TempObstacles$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TempObstacles.cpp"

$(IntermediateDirectory)/Source_Sample_TileMesh$(ObjectSuffix): ../../Source/Sample_TileMesh.cpp $(IntermediateDirectory)/Source_Sample_TileMesh$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TileMesh.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_Sample_TileMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_Sample_TileMesh$(DependSuffix): ../../Source/Sample_TileMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_Sample_TileMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_Sample_TileMesh$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TileMesh.cpp"

$(IntermediateDirectory)/Source_Sample_TileMesh$(PreprocessSuffix): ../../Source/Sample_TileMesh.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_Sample_TileMesh$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/Sample_TileMesh.cpp"

$(IntermediateDirectory)/Source_SampleInterfaces$(ObjectSuffix): ../../Source/SampleInterfaces.cpp $(IntermediateDirectory)/Source_SampleInterfaces$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/SampleInterfaces.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_SampleInterfaces$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_SampleInterfaces$(DependSuffix): ../../Source/SampleInterfaces.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_SampleInterfaces$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_SampleInterfaces$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/SampleInterfaces.cpp"

$(IntermediateDirectory)/Source_SampleInterfaces$(PreprocessSuffix): ../../Source/SampleInterfaces.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_SampleInterfaces$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/SampleInterfaces.cpp"

$(IntermediateDirectory)/Source_SlideShow$(ObjectSuffix): ../../Source/SlideShow.cpp $(IntermediateDirectory)/Source_SlideShow$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/SlideShow.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_SlideShow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_SlideShow$(DependSuffix): ../../Source/SlideShow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_SlideShow$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_SlideShow$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/SlideShow.cpp"

$(IntermediateDirectory)/Source_SlideShow$(PreprocessSuffix): ../../Source/SlideShow.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_SlideShow$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/SlideShow.cpp"

$(IntermediateDirectory)/Source_TestCase$(ObjectSuffix): ../../Source/TestCase.cpp $(IntermediateDirectory)/Source_TestCase$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/TestCase.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_TestCase$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_TestCase$(DependSuffix): ../../Source/TestCase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_TestCase$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_TestCase$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/TestCase.cpp"

$(IntermediateDirectory)/Source_TestCase$(PreprocessSuffix): ../../Source/TestCase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_TestCase$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/TestCase.cpp"

$(IntermediateDirectory)/Source_ValueHistory$(ObjectSuffix): ../../Source/ValueHistory.cpp $(IntermediateDirectory)/Source_ValueHistory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Source/ValueHistory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_ValueHistory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_ValueHistory$(DependSuffix): ../../Source/ValueHistory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_ValueHistory$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_ValueHistory$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Source/ValueHistory.cpp"

$(IntermediateDirectory)/Source_ValueHistory$(PreprocessSuffix): ../../Source/ValueHistory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_ValueHistory$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Source/ValueHistory.cpp"

$(IntermediateDirectory)/Source_DebugDraw$(ObjectSuffix): ../../../DebugUtils/Source/DebugDraw.cpp $(IntermediateDirectory)/Source_DebugDraw$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DebugUtils/Source/DebugDraw.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DebugDraw$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DebugDraw$(DependSuffix): ../../../DebugUtils/Source/DebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DebugDraw$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DebugDraw$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DebugUtils/Source/DebugDraw.cpp"

$(IntermediateDirectory)/Source_DebugDraw$(PreprocessSuffix): ../../../DebugUtils/Source/DebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DebugDraw$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DebugUtils/Source/DebugDraw.cpp"

$(IntermediateDirectory)/Source_DetourDebugDraw$(ObjectSuffix): ../../../DebugUtils/Source/DetourDebugDraw.cpp $(IntermediateDirectory)/Source_DetourDebugDraw$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DebugUtils/Source/DetourDebugDraw.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourDebugDraw$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourDebugDraw$(DependSuffix): ../../../DebugUtils/Source/DetourDebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourDebugDraw$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourDebugDraw$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DebugUtils/Source/DetourDebugDraw.cpp"

$(IntermediateDirectory)/Source_DetourDebugDraw$(PreprocessSuffix): ../../../DebugUtils/Source/DetourDebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourDebugDraw$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DebugUtils/Source/DetourDebugDraw.cpp"

$(IntermediateDirectory)/Source_RecastDebugDraw$(ObjectSuffix): ../../../DebugUtils/Source/RecastDebugDraw.cpp $(IntermediateDirectory)/Source_RecastDebugDraw$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDebugDraw.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastDebugDraw$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastDebugDraw$(DependSuffix): ../../../DebugUtils/Source/RecastDebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastDebugDraw$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastDebugDraw$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDebugDraw.cpp"

$(IntermediateDirectory)/Source_RecastDebugDraw$(PreprocessSuffix): ../../../DebugUtils/Source/RecastDebugDraw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastDebugDraw$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDebugDraw.cpp"

$(IntermediateDirectory)/Source_RecastDump$(ObjectSuffix): ../../../DebugUtils/Source/RecastDump.cpp $(IntermediateDirectory)/Source_RecastDump$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDump.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_RecastDump$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_RecastDump$(DependSuffix): ../../../DebugUtils/Source/RecastDump.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_RecastDump$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_RecastDump$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDump.cpp"

$(IntermediateDirectory)/Source_RecastDump$(PreprocessSuffix): ../../../DebugUtils/Source/RecastDump.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_RecastDump$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DebugUtils/Source/RecastDump.cpp"

$(IntermediateDirectory)/Source_DetourCrowd$(ObjectSuffix): ../../../DetourCrowd/Source/DetourCrowd.cpp $(IntermediateDirectory)/Source_DetourCrowd$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourCrowd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourCrowd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourCrowd$(DependSuffix): ../../../DetourCrowd/Source/DetourCrowd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourCrowd$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourCrowd$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourCrowd.cpp"

$(IntermediateDirectory)/Source_DetourCrowd$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourCrowd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourCrowd$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourCrowd.cpp"

$(IntermediateDirectory)/Source_DetourLocalBoundary$(ObjectSuffix): ../../../DetourCrowd/Source/DetourLocalBoundary.cpp $(IntermediateDirectory)/Source_DetourLocalBoundary$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourLocalBoundary.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourLocalBoundary$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourLocalBoundary$(DependSuffix): ../../../DetourCrowd/Source/DetourLocalBoundary.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourLocalBoundary$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourLocalBoundary$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourLocalBoundary.cpp"

$(IntermediateDirectory)/Source_DetourLocalBoundary$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourLocalBoundary.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourLocalBoundary$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourLocalBoundary.cpp"

$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(ObjectSuffix): ../../../DetourCrowd/Source/DetourObstacleAvoidance.cpp $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourObstacleAvoidance.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(DependSuffix): ../../../DetourCrowd/Source/DetourObstacleAvoidance.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourObstacleAvoidance.cpp"

$(IntermediateDirectory)/Source_DetourObstacleAvoidance$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourObstacleAvoidance.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourObstacleAvoidance.cpp"

$(IntermediateDirectory)/Source_DetourPathCorridor$(ObjectSuffix): ../../../DetourCrowd/Source/DetourPathCorridor.cpp $(IntermediateDirectory)/Source_DetourPathCorridor$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathCorridor.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourPathCorridor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourPathCorridor$(DependSuffix): ../../../DetourCrowd/Source/DetourPathCorridor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourPathCorridor$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourPathCorridor$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathCorridor.cpp"

$(IntermediateDirectory)/Source_DetourPathCorridor$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourPathCorridor.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourPathCorridor$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathCorridor.cpp"

$(IntermediateDirectory)/Source_DetourPathQueue$(ObjectSuffix): ../../../DetourCrowd/Source/DetourPathQueue.cpp $(IntermediateDirectory)/Source_DetourPathQueue$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathQueue.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourPathQueue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourPathQueue$(DependSuffix): ../../../DetourCrowd/Source/DetourPathQueue.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourPathQueue$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourPathQueue$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathQueue.cpp"

$(IntermediateDirectory)/Source_DetourPathQueue$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourPathQueue.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourPathQueue$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourPathQueue.cpp"

$(IntermediateDirectory)/Source_DetourProximityGrid$(ObjectSuffix): ../../../DetourCrowd/Source/DetourProximityGrid.cpp $(IntermediateDirectory)/Source_DetourProximityGrid$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourProximityGrid.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourProximityGrid$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourProximityGrid$(DependSuffix): ../../../DetourCrowd/Source/DetourProximityGrid.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourProximityGrid$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourProximityGrid$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourProximityGrid.cpp"

$(IntermediateDirectory)/Source_DetourProximityGrid$(PreprocessSuffix): ../../../DetourCrowd/Source/DetourProximityGrid.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourProximityGrid$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourCrowd/Source/DetourProximityGrid.cpp"

$(IntermediateDirectory)/fastlz_fastlz$(ObjectSuffix): ../../Contrib/fastlz/fastlz.c $(IntermediateDirectory)/fastlz_fastlz$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/RecastDemo/Contrib/fastlz/fastlz.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/fastlz_fastlz$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fastlz_fastlz$(DependSuffix): ../../Contrib/fastlz/fastlz.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fastlz_fastlz$(ObjectSuffix) -MF$(IntermediateDirectory)/fastlz_fastlz$(DependSuffix) -MM "/home/cbh/projects/test/Recast/RecastDemo/Contrib/fastlz/fastlz.c"

$(IntermediateDirectory)/fastlz_fastlz$(PreprocessSuffix): ../../Contrib/fastlz/fastlz.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fastlz_fastlz$(PreprocessSuffix) "/home/cbh/projects/test/Recast/RecastDemo/Contrib/fastlz/fastlz.c"

$(IntermediateDirectory)/Source_DetourTileCache$(ObjectSuffix): ../../../DetourTileCache/Source/DetourTileCache.cpp $(IntermediateDirectory)/Source_DetourTileCache$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCache.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourTileCache$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourTileCache$(DependSuffix): ../../../DetourTileCache/Source/DetourTileCache.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourTileCache$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourTileCache$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCache.cpp"

$(IntermediateDirectory)/Source_DetourTileCache$(PreprocessSuffix): ../../../DetourTileCache/Source/DetourTileCache.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourTileCache$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCache.cpp"

$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(ObjectSuffix): ../../../DetourTileCache/Source/DetourTileCacheBuilder.cpp $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCacheBuilder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(DependSuffix): ../../../DetourTileCache/Source/DetourTileCacheBuilder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(ObjectSuffix) -MF$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(DependSuffix) -MM "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCacheBuilder.cpp"

$(IntermediateDirectory)/Source_DetourTileCacheBuilder$(PreprocessSuffix): ../../../DetourTileCache/Source/DetourTileCacheBuilder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(PreprocessSuffix) "/home/cbh/projects/test/Recast/DetourTileCache/Source/DetourTileCacheBuilder.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Source_Recast$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Recast$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Recast$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastAlloc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastAlloc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastAlloc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastArea$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastArea$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastArea$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastContour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastContour$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastContour$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastFilter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastFilter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastFilter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastLayers$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastLayers$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastLayers$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMeshDetail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMeshDetail$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastMeshDetail$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRasterization$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRasterization$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRasterization$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRegion$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRegion$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastRegion$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourAlloc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourAlloc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourAlloc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCommon$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCommon$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCommon$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshBuilder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshQuery$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshQuery$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNavMeshQuery$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourNode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_ChunkyTriMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_ChunkyTriMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_ChunkyTriMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_ConvexVolumeTool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_ConvexVolumeTool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_ConvexVolumeTool$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_CrowdTool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_CrowdTool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_CrowdTool$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Filelist$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Filelist$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Filelist$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_imgui$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_imgui$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_imgui$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_imguiRenderGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_imguiRenderGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_imguiRenderGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_InputGeom$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_InputGeom$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_InputGeom$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_MeshLoaderObj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_MeshLoaderObj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_MeshLoaderObj$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_NavMeshTesterTool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_NavMeshTesterTool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_NavMeshTesterTool$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_OffMeshConnectionTool$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_OffMeshConnectionTool$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_OffMeshConnectionTool$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_PerfTimer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_PerfTimer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_PerfTimer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_Debug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_Debug$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_Debug$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_SoloMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_SoloMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_SoloMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TempObstacles$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TempObstacles$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TempObstacles$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TileMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TileMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_Sample_TileMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_SampleInterfaces$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_SampleInterfaces$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_SampleInterfaces$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_SlideShow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_SlideShow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_SlideShow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_TestCase$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_TestCase$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_TestCase$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_ValueHistory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_ValueHistory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_ValueHistory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DebugDraw$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DebugDraw$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DebugDraw$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourDebugDraw$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourDebugDraw$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourDebugDraw$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDebugDraw$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDebugDraw$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDebugDraw$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDump$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDump$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_RecastDump$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCrowd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCrowd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourCrowd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourLocalBoundary$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourLocalBoundary$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourLocalBoundary$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourObstacleAvoidance$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathCorridor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathCorridor$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathCorridor$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathQueue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathQueue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourPathQueue$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourProximityGrid$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourProximityGrid$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourProximityGrid$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/fastlz_fastlz$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/fastlz_fastlz$(DependSuffix)
	$(RM) $(IntermediateDirectory)/fastlz_fastlz$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCache$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCache$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCache$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Source_DetourTileCacheBuilder$(PreprocessSuffix)
	$(RM) $(OutputFile)


