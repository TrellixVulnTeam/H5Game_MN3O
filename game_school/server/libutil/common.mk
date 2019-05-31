##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=common
ConfigurationName      :=Release
IntermediateDirectory  :=../bin/Release/$(ProjectName)
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/cbh/workspace/pwngs/server"
ProjectPath            := "/home/cbh/workspace/pwngs/server/common"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=cbh
Date                   :=2013年01月25日
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
OutputFile             :=./Release/lib$(ProjectName).a
Preprocessors          :=$(PreprocessorSwitch)TBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/cbh/workspace/pwngs/server/common/common.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall --std=c++0x $(Preprocessors)
C_CmpOptions           :=  $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../libcore/inc 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/pw_backtrace$(ObjectSuffix) $(IntermediateDirectory)/pw_command$(ObjectSuffix) $(IntermediateDirectory)/pw_runnable$(ObjectSuffix) $(IntermediateDirectory)/pw_tick_timer$(ObjectSuffix) $(IntermediateDirectory)/pw_logger$(ObjectSuffix) $(IntermediateDirectory)/pw_memhook$(ObjectSuffix) $(IntermediateDirectory)/pw_csv$(ObjectSuffix) $(IntermediateDirectory)/pw_time$(ObjectSuffix) $(IntermediateDirectory)/pw_xml$(ObjectSuffix) $(IntermediateDirectory)/tokenizer$(ObjectSuffix) \
	$(IntermediateDirectory)/pw_circle_buffer$(ObjectSuffix) $(IntermediateDirectory)/pw_error_handler$(ObjectSuffix) $(IntermediateDirectory)/pw_byte_order$(ObjectSuffix) $(IntermediateDirectory)/pw_utils$(ObjectSuffix) $(IntermediateDirectory)/pw_stack_walker_win32$(ObjectSuffix) $(IntermediateDirectory)/pw_random$(ObjectSuffix) $(IntermediateDirectory)/pw_iconv$(ObjectSuffix) $(IntermediateDirectory)/mongoose$(ObjectSuffix) $(IntermediateDirectory)/sqlite3$(ObjectSuffix) $(IntermediateDirectory)/pw_lua$(ObjectSuffix) \
	$(IntermediateDirectory)/pw_luaseri$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@$(MakeDirCommand) "/home/cbh/workspace/pwngs/server/.build-release"
	@echo rebuilt > "/home/cbh/workspace/pwngs/server/.build-release/common"

../bin/Release/$(ProjectName):
	@test -d ../bin/Release/$(ProjectName) || $(MakeDirCommand) ../bin/Release/$(ProjectName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/pw_backtrace$(ObjectSuffix): pw_backtrace.cpp $(IntermediateDirectory)/pw_backtrace$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_backtrace.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_backtrace$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_backtrace$(DependSuffix): pw_backtrace.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_backtrace$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_backtrace$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_backtrace.cpp"

$(IntermediateDirectory)/pw_backtrace$(PreprocessSuffix): pw_backtrace.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_backtrace$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_backtrace.cpp"

$(IntermediateDirectory)/pw_command$(ObjectSuffix): pw_command.cpp $(IntermediateDirectory)/pw_command$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_command.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_command$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_command$(DependSuffix): pw_command.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_command$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_command$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_command.cpp"

$(IntermediateDirectory)/pw_command$(PreprocessSuffix): pw_command.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_command$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_command.cpp"

$(IntermediateDirectory)/pw_runnable$(ObjectSuffix): pw_runnable.cpp $(IntermediateDirectory)/pw_runnable$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_runnable.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_runnable$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_runnable$(DependSuffix): pw_runnable.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_runnable$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_runnable$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_runnable.cpp"

$(IntermediateDirectory)/pw_runnable$(PreprocessSuffix): pw_runnable.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_runnable$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_runnable.cpp"

$(IntermediateDirectory)/pw_tick_timer$(ObjectSuffix): pw_tick_timer.cpp $(IntermediateDirectory)/pw_tick_timer$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_tick_timer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_tick_timer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_tick_timer$(DependSuffix): pw_tick_timer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_tick_timer$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_tick_timer$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_tick_timer.cpp"

$(IntermediateDirectory)/pw_tick_timer$(PreprocessSuffix): pw_tick_timer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_tick_timer$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_tick_timer.cpp"

$(IntermediateDirectory)/pw_logger$(ObjectSuffix): pw_logger.cpp $(IntermediateDirectory)/pw_logger$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_logger.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_logger$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_logger$(DependSuffix): pw_logger.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_logger$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_logger$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_logger.cpp"

$(IntermediateDirectory)/pw_logger$(PreprocessSuffix): pw_logger.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_logger$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_logger.cpp"

$(IntermediateDirectory)/pw_memhook$(ObjectSuffix): pw_memhook.cpp $(IntermediateDirectory)/pw_memhook$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_memhook.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_memhook$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_memhook$(DependSuffix): pw_memhook.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_memhook$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_memhook$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_memhook.cpp"

$(IntermediateDirectory)/pw_memhook$(PreprocessSuffix): pw_memhook.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_memhook$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_memhook.cpp"

$(IntermediateDirectory)/pw_csv$(ObjectSuffix): pw_csv.cpp $(IntermediateDirectory)/pw_csv$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_csv.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_csv$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_csv$(DependSuffix): pw_csv.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_csv$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_csv$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_csv.cpp"

$(IntermediateDirectory)/pw_csv$(PreprocessSuffix): pw_csv.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_csv$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_csv.cpp"

$(IntermediateDirectory)/pw_time$(ObjectSuffix): pw_time.cpp $(IntermediateDirectory)/pw_time$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_time.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_time$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_time$(DependSuffix): pw_time.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_time$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_time$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_time.cpp"

$(IntermediateDirectory)/pw_time$(PreprocessSuffix): pw_time.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_time$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_time.cpp"

$(IntermediateDirectory)/pw_xml$(ObjectSuffix): pw_xml.cpp $(IntermediateDirectory)/pw_xml$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_xml.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_xml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_xml$(DependSuffix): pw_xml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_xml$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_xml$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_xml.cpp"

$(IntermediateDirectory)/pw_xml$(PreprocessSuffix): pw_xml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_xml$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_xml.cpp"

$(IntermediateDirectory)/tokenizer$(ObjectSuffix): tokenizer.cpp $(IntermediateDirectory)/tokenizer$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tokenizer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tokenizer$(DependSuffix): tokenizer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tokenizer$(ObjectSuffix) -MF$(IntermediateDirectory)/tokenizer$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp"

$(IntermediateDirectory)/tokenizer$(PreprocessSuffix): tokenizer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tokenizer$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/tokenizer.cpp"

$(IntermediateDirectory)/pw_circle_buffer$(ObjectSuffix): pw_circle_buffer.cpp $(IntermediateDirectory)/pw_circle_buffer$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_circle_buffer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_circle_buffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_circle_buffer$(DependSuffix): pw_circle_buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_circle_buffer$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_circle_buffer$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_circle_buffer.cpp"

$(IntermediateDirectory)/pw_circle_buffer$(PreprocessSuffix): pw_circle_buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_circle_buffer$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_circle_buffer.cpp"

$(IntermediateDirectory)/pw_error_handler$(ObjectSuffix): pw_error_handler.cpp $(IntermediateDirectory)/pw_error_handler$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_error_handler.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_error_handler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_error_handler$(DependSuffix): pw_error_handler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_error_handler$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_error_handler$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_error_handler.cpp"

$(IntermediateDirectory)/pw_error_handler$(PreprocessSuffix): pw_error_handler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_error_handler$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_error_handler.cpp"

$(IntermediateDirectory)/pw_byte_order$(ObjectSuffix): pw_byte_order.cpp $(IntermediateDirectory)/pw_byte_order$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_byte_order.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_byte_order$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_byte_order$(DependSuffix): pw_byte_order.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_byte_order$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_byte_order$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_byte_order.cpp"

$(IntermediateDirectory)/pw_byte_order$(PreprocessSuffix): pw_byte_order.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_byte_order$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_byte_order.cpp"

$(IntermediateDirectory)/pw_utils$(ObjectSuffix): pw_utils.cpp $(IntermediateDirectory)/pw_utils$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_utils.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_utils$(DependSuffix): pw_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_utils$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_utils.cpp"

$(IntermediateDirectory)/pw_utils$(PreprocessSuffix): pw_utils.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_utils$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_utils.cpp"

$(IntermediateDirectory)/pw_stack_walker_win32$(ObjectSuffix): pw_stack_walker_win32.cpp $(IntermediateDirectory)/pw_stack_walker_win32$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_stack_walker_win32.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_stack_walker_win32$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_stack_walker_win32$(DependSuffix): pw_stack_walker_win32.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_stack_walker_win32$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_stack_walker_win32$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_stack_walker_win32.cpp"

$(IntermediateDirectory)/pw_stack_walker_win32$(PreprocessSuffix): pw_stack_walker_win32.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_stack_walker_win32$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_stack_walker_win32.cpp"

$(IntermediateDirectory)/pw_random$(ObjectSuffix): pw_random.cpp $(IntermediateDirectory)/pw_random$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_random.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_random$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_random$(DependSuffix): pw_random.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_random$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_random$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_random.cpp"

$(IntermediateDirectory)/pw_random$(PreprocessSuffix): pw_random.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_random$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_random.cpp"

$(IntermediateDirectory)/pw_iconv$(ObjectSuffix): pw_iconv.cpp $(IntermediateDirectory)/pw_iconv$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_iconv.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_iconv$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_iconv$(DependSuffix): pw_iconv.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_iconv$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_iconv$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_iconv.cpp"

$(IntermediateDirectory)/pw_iconv$(PreprocessSuffix): pw_iconv.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_iconv$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_iconv.cpp"

$(IntermediateDirectory)/mongoose$(ObjectSuffix): mongoose.c $(IntermediateDirectory)/mongoose$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/mongoose.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mongoose$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mongoose$(DependSuffix): mongoose.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mongoose$(ObjectSuffix) -MF$(IntermediateDirectory)/mongoose$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/mongoose.c"

$(IntermediateDirectory)/mongoose$(PreprocessSuffix): mongoose.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mongoose$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/mongoose.c"

$(IntermediateDirectory)/sqlite3$(ObjectSuffix): sqlite3.c $(IntermediateDirectory)/sqlite3$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/sqlite3.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sqlite3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sqlite3$(DependSuffix): sqlite3.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sqlite3$(ObjectSuffix) -MF$(IntermediateDirectory)/sqlite3$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/sqlite3.c"

$(IntermediateDirectory)/sqlite3$(PreprocessSuffix): sqlite3.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sqlite3$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/sqlite3.c"

$(IntermediateDirectory)/pw_lua$(ObjectSuffix): pw_lua.cpp $(IntermediateDirectory)/pw_lua$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_lua.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_lua$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_lua$(DependSuffix): pw_lua.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_lua$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_lua$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_lua.cpp"

$(IntermediateDirectory)/pw_lua$(PreprocessSuffix): pw_lua.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_lua$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_lua.cpp"

$(IntermediateDirectory)/pw_luaseri$(ObjectSuffix): pw_luaseri.cpp $(IntermediateDirectory)/pw_luaseri$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/cbh/workspace/pwngs/server/common/pw_luaseri.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pw_luaseri$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pw_luaseri$(DependSuffix): pw_luaseri.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pw_luaseri$(ObjectSuffix) -MF$(IntermediateDirectory)/pw_luaseri$(DependSuffix) -MM "/home/cbh/workspace/pwngs/server/common/pw_luaseri.cpp"

$(IntermediateDirectory)/pw_luaseri$(PreprocessSuffix): pw_luaseri.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pw_luaseri$(PreprocessSuffix) "/home/cbh/workspace/pwngs/server/common/pw_luaseri.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/pw_backtrace$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_backtrace$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_backtrace$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_command$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_command$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_command$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_runnable$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_runnable$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_runnable$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_tick_timer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_tick_timer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_tick_timer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_logger$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_logger$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_logger$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_memhook$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_memhook$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_memhook$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_csv$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_csv$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_csv$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_time$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_time$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_time$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_xml$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_xml$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_xml$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tokenizer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tokenizer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tokenizer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_circle_buffer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_circle_buffer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_circle_buffer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_error_handler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_error_handler$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_error_handler$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_byte_order$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_byte_order$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_byte_order$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_stack_walker_win32$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_stack_walker_win32$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_stack_walker_win32$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_random$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_random$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_random$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_iconv$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_iconv$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_iconv$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mongoose$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mongoose$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mongoose$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_lua$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_lua$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_lua$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pw_luaseri$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pw_luaseri$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pw_luaseri$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/cbh/workspace/pwngs/server/.build-release/common"


