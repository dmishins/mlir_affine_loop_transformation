; ModuleID = 'LLVMDialectModule'
source_filename = "LLVMDialectModule"
target triple = "x86_64-unknown-linux-gnu"

@str0 = internal constant [7 x i8] c"hi %u\0A\00"
@array = private global [10 x i32] undef

declare ptr @malloc(i64)

declare void @free(ptr)

declare i32 @printf(ptr, ...)

define i32 @main() !dbg !3 {
  br label %1, !dbg !7

1:                                                ; preds = %4, %0
  %2 = phi i64 [ %7, %4 ], [ 0, %0 ]
  %3 = icmp slt i64 %2, 10, !dbg !9
  br i1 %3, label %4, label %8, !dbg !10

4:                                                ; preds = %1
  %5 = trunc i64 %2 to i32, !dbg !11
  %6 = getelementptr i32, ptr @array, i64 %2, !dbg !12
  store i32 %5, ptr %6, align 4, !dbg !13
  %7 = add i64 %2, 1, !dbg !14
  br label %1, !dbg !15

8:                                                ; preds = %1
  br label %9, !dbg !16

9:                                                ; preds = %12, %8
  %10 = phi i64 [ %16, %12 ], [ 0, %8 ]
  %11 = icmp slt i64 %10, 10, !dbg !17
  br i1 %11, label %12, label %17, !dbg !18

12:                                               ; preds = %9
  %13 = getelementptr i32, ptr @array, i64 %10, !dbg !19
  %14 = load i32, ptr %13, align 4, !dbg !20
  %15 = call i32 (ptr, ...) @printf(ptr @str0, i32 %14), !dbg !21
  %16 = add i64 %10, 2, !dbg !22
  br label %9, !dbg !23

17:                                               ; preds = %9
  ret i32 0, !dbg !24
}

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "mlir", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug)
!1 = !DIFile(filename: "LLVMDialectModule", directory: "/")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = distinct !DISubprogram(name: "main", linkageName: "main", scope: null, file: !4, line: 8, type: !5, scopeLine: 8, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !6)
!4 = !DIFile(filename: "<stdin>", directory: "/home/dmishins/583/test2/Polygeist/build")
!5 = !DISubroutineType(types: !6)
!6 = !{}
!7 = !DILocation(line: 16, column: 5, scope: !8)
!8 = !DILexicalBlockFile(scope: !3, file: !4, discriminator: 0)
!9 = !DILocation(line: 18, column: 10, scope: !8)
!10 = !DILocation(line: 19, column: 5, scope: !8)
!11 = !DILocation(line: 21, column: 10, scope: !8)
!12 = !DILocation(line: 22, column: 11, scope: !8)
!13 = !DILocation(line: 23, column: 5, scope: !8)
!14 = !DILocation(line: 24, column: 11, scope: !8)
!15 = !DILocation(line: 25, column: 5, scope: !8)
!16 = !DILocation(line: 29, column: 5, scope: !8)
!17 = !DILocation(line: 31, column: 11, scope: !8)
!18 = !DILocation(line: 32, column: 5, scope: !8)
!19 = !DILocation(line: 34, column: 11, scope: !8)
!20 = !DILocation(line: 35, column: 11, scope: !8)
!21 = !DILocation(line: 36, column: 11, scope: !8)
!22 = !DILocation(line: 37, column: 11, scope: !8)
!23 = !DILocation(line: 38, column: 5, scope: !8)
!24 = !DILocation(line: 40, column: 5, scope: !8)
