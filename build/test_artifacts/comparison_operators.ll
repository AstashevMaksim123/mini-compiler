; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/comparison_operators.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/comparison_operators.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %cmptmp = icmp sge i64 %arg.value, 10
  %arg.value2 = load i64, ptr %arg1, align 4
  %cmptmp3 = icmp sgt i64 %arg.value2, 9
  %andtmp = and i1 %cmptmp, %cmptmp3
  %arg.value4 = load i64, ptr %arg1, align 4
  %cmptmp5 = icmp sle i64 %arg.value4, 10
  %andtmp6 = and i1 %andtmp, %cmptmp5
  %arg.value7 = load i64, ptr %arg1, align 4
  %cmptmp8 = icmp slt i64 %arg.value7, 11
  %andtmp9 = and i1 %andtmp6, %cmptmp8
  %arg.value10 = load i64, ptr %arg1, align 4
  %netmp = icmp ne i64 %arg.value10, 0
  %andtmp11 = and i1 %andtmp9, %netmp
  %arg.value12 = load i64, ptr %arg1, align 4
  %eqtmp = icmp eq i64 %arg.value12, 10
  %andtmp13 = and i1 %andtmp11, %eqtmp
  br i1 %andtmp13, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  ret i64 1

if.else:                                          ; preds = %entry
  ret i64 0

if.end:                                           ; No predecessors!
  unreachable
}
