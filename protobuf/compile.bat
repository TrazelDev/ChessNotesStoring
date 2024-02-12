C:\tools\protobuf-24.1\bin\protoc.exe -I=. --csharp_out=. msgFormat.proto
protoc --plugin=protoc-gen-ts_proto=".\\node_modules\\.bin\\protoc-gen-ts_proto.cmd" --ts_proto_out=. ./msgFormat.proto
pause