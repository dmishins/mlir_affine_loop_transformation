; ModuleID = 'LLVMDialectModule'
source_filename = "LLVMDialectModule"
target triple = "x86_64-unknown-linux-gnu"

@str0 = internal constant [8 x i8] c"%u  %u\0A\00"

declare ptr @malloc(i64)

declare void @free(ptr)

declare i32 @printf(ptr, ...)

define i32 @main() !dbg !3 {
  br label %1, !dbg !7

1:                                                ; preds = %5, %0
  %2 = phi i64 [ %9, %5 ], [ 0, %0 ]
  %3 = phi i32 [ %7, %5 ], [ 0, %0 ]
  %4 = icmp slt i64 %2, 10, !dbg !9
  br i1 %4, label %5, label %10, !dbg !10

5:                                                ; preds = %1
  %6 = trunc i64 %2 to i32, !dbg !11
  %7 = add i32 %3, %6, !dbg !12
  %8 = call i32 (ptr, ...) @printf(ptr @str0, i32 %6, i32 %7), !dbg !13
  %9 = add i64 %2, 1, !dbg !14
  br label %1, !dbg !15

10:                                               ; preds = %1
  ret i32 %3, !dbg !16
}

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "mlir", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "LLVMDialectModule", directory: "/")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: null, file: !4, line: 4, type: !5, scopeLine: 4, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !6)
!4 = !DIFile(filename: "<stdin>", directory: "/home/dmishins/583/test2/Polygeist/build")
!5 = !DISubroutineType(types: !6)
!6 = !{}
!7 = !DILocation(line: 11, column: 5, scope: !8)
!8 = !DILexicalBlockFile(scope: !3, file: !4, discriminator: 0)
!9 = !DILocation(line: 13, column: 10, scope: !8)
!10 = !DILocation(line: 14, column: 5, scope: !8)
!11 = !DILocation(line: 16, column: 10, scope: !8)
!12 = !DILocation(line: 17, column: 11, scope: !8)
!13 = !DILocation(line: 18, column: 11, scope: !8)
!14 = !DILocation(line: 19, column: 11, scope: !8)
!15 = !DILocation(line: 20, column: 5, scope: !8)
!16 = !DILocation(line: 22, column: 5, scope: !8)
