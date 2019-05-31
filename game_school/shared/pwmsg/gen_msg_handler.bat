"./ProbuffAssembly.exe" ./proto/01000_01009_login.proto
"./ProbuffAssembly.exe" ./proto

"../../server/bin/protoc.exe" --cpp_out=./ ./pwngs/protocol/accsrv/accsrv.proto
copy .\pwngs\protocol\accsrv\accsrv.pb.h ..\..\server\pwaccsrv\msg\accsrv.pb.h /y
copy .\pwngs\protocol\accsrv\accsrv.pb.cc ..\..\server\pwaccsrv\msg\accsrv.pb.cc /y

copy .\proto\00000_00000_def.proto .\pwngs\protocol\worldsrv\00000_00000_def.proto /y


"../../server/bin/protoc.exe" --cpp_out=./ ./pwngs/protocol/worldsrv/00000_00000_def.proto
"../../server/bin/protoc.exe" --cpp_out=../../server/pwworldsrv/msg ./process_proto/01000_01009_login.proto

copy .\pwngs\protocol\worldsrv\00000_00000_def.pb.h ..\..\server\pwworldsrv\msg\process_proto\00000_00000_def.pb.h /y
copy .\pwngs\protocol\worldsrv\00000_00000_def.pb.cc ..\..\server\pwworldsrv\msg\process_proto\00000_00000_def.pb.cc /y
copy .\pwngs\options.pb.h .\options.pb.h /y
copy .\pwngs\options.pb.cc .\options.pb.cc /y

"../../server/bin/pw_proto_cpp_gen.exe" ./accsrv.proto ../../server/pwaccsrv/msg pwaccsrv
"../../server/bin/pw_proto_cpp_gen.exe" ./worldsrv.proto  ../../server/pwworldsrv/msg pwworldsrv ../../server/pwworldsrv/msg/process_proto

svn add ../../server/pwworldsrv/msg/*.cpp --force

pause

