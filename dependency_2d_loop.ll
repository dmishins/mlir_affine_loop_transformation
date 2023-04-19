; ModuleID = 'LLVMDialectModule'
source_filename = "LLVMDialectModule"
target triple = "x86_64-unknown-linux-gnu"

@str0 = internal constant [4 x i8] c"%u\0A\00"
@array = private global [10000 x [1000 x i32]] undef

declare ptr @malloc(i64)

declare void @free(ptr)

declare i32 @printf(ptr, ...)

define i32 @main() !dbg !3 {
  br label %1, !dbg !7

1:                                                ; preds = %4, %0
  %2 = phi i64 [ %9, %4 ], [ 0, %0 ]
  %3 = icmp slt i64 %2, 10000, !dbg !9
  br i1 %3, label %4, label %10, !dbg !10

4:                                                ; preds = %1
  %5 = trunc i64 %2 to i32, !dbg !11
  %6 = mul i64 %2, 1000, !dbg !12
  %7 = add i64 %6, 0, !dbg !13
  %8 = getelementptr i32, ptr @array, i64 %7, !dbg !14
  store i32 %5, ptr %8, align 4, !dbg !15
  %9 = add i64 %2, 1, !dbg !16
  br label %1, !dbg !17

10:                                               ; preds = %1
  br label %11, !dbg !18

11:                                               ; preds = %29, %10
  %12 = phi i64 [ %30, %29 ], [ 1, %10 ]
  %13 = icmp slt i64 %12, 1000, !dbg !19
  br i1 %13, label %14, label %31, !dbg !20

14:                                               ; preds = %11
  br label %15, !dbg !21

15:                                               ; preds = %18, %14
  %16 = phi i64 [ %28, %18 ], [ 0, %14 ]
  %17 = icmp slt i64 %16, 10000, !dbg !22
  br i1 %17, label %18, label %29, !dbg !23

18:                                               ; preds = %15
  %19 = add i64 %12, -1, !dbg !24
  %20 = mul i64 %16, 1000, !dbg !25
  %21 = add i64 %20, %19, !dbg !26
  %22 = getelementptr i32, ptr @array, i64 %21, !dbg !27
  %23 = load i32, ptr %22, align 4, !dbg !28
  %24 = add i32 %23, 1, !dbg !29
  %25 = mul i64 %16, 1000, !dbg !30
  %26 = add i64 %25, %12, !dbg !31
  %27 = getelementptr i32, ptr @array, i64 %26, !dbg !32
  store i32 %24, ptr %27, align 4, !dbg !33
  %28 = add i64 %16, 1, !dbg !34
  br label %15, !dbg !35

29:                                               ; preds = %15
  %30 = add i64 %12, 1, !dbg !36
  br label %11, !dbg !37

31:                                               ; preds = %11
  %32 = load i32, ptr getelementptr (i32, ptr @array, i64 5999), align 4, !dbg !38
  %33 = call i32 (ptr, ...) @printf(ptr @str0, i32 %32), !dbg !39
  ret i32 0, !dbg !40
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
!7 = !DILocation(line: 21, column: 5, scope: !8)
!8 = !DILexicalBlockFile(scope: !3, file: !4, discriminator: 0)
!9 = !DILocation(line: 23, column: 11, scope: !8)
!10 = !DILocation(line: 24, column: 5, scope: !8)
!11 = !DILocation(line: 26, column: 11, scope: !8)
!12 = !DILocation(line: 27, column: 11, scope: !8)
!13 = !DILocation(line: 28, column: 11, scope: !8)
!14 = !DILocation(line: 29, column: 11, scope: !8)
!15 = !DILocation(line: 30, column: 5, scope: !8)
!16 = !DILocation(line: 31, column: 11, scope: !8)
!17 = !DILocation(line: 32, column: 5, scope: !8)
!18 = !DILocation(line: 34, column: 5, scope: !8)
!19 = !DILocation(line: 36, column: 11, scope: !8)
!20 = !DILocation(line: 37, column: 5, scope: !8)
!21 = !DILocation(line: 39, column: 5, scope: !8)
!22 = !DILocation(line: 41, column: 11, scope: !8)
!23 = !DILocation(line: 42, column: 5, scope: !8)
!24 = !DILocation(line: 44, column: 11, scope: !8)
!25 = !DILocation(line: 45, column: 11, scope: !8)
!26 = !DILocation(line: 46, column: 11, scope: !8)
!27 = !DILocation(line: 47, column: 11, scope: !8)
!28 = !DILocation(line: 48, column: 11, scope: !8)
!29 = !DILocation(line: 49, column: 11, scope: !8)
!30 = !DILocation(line: 50, column: 11, scope: !8)
!31 = !DILocation(line: 51, column: 11, scope: !8)
!32 = !DILocation(line: 52, column: 11, scope: !8)
!33 = !DILocation(line: 53, column: 5, scope: !8)
!34 = !DILocation(line: 54, column: 11, scope: !8)
!35 = !DILocation(line: 55, column: 5, scope: !8)
!36 = !DILocation(line: 57, column: 11, scope: !8)
!37 = !DILocation(line: 58, column: 5, scope: !8)
!38 = !DILocation(line: 65, column: 11, scope: !8)
!39 = !DILocation(line: 66, column: 11, scope: !8)
!40 = !DILocation(line: 67, column: 5, scope: !8)
