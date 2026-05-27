; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/nested_blocks.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/nested_blocks.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %y = alloca i64, align 8
  %x2 = alloca i64, align 8
  %x = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  store i64 %arg.value, ptr %x, align 4
  store i64 3, ptr %x2, align 4
  %x.value = load i64, ptr %x2, align 4
  %addtmp = add i64 %x.value, 4
  store i64 %addtmp, ptr %y, align 4
  %y.value = load i64, ptr %y, align 4
  %eqtmp = icmp eq i64 %y.value, 7
  br i1 %eqtmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x.value3 = load i64, ptr %x2, align 4
  %y.value4 = load i64, ptr %y, align 4
  %addtmp5 = add i64 %x.value3, %y.value4
  ret i64 %addtmp5

if.else:                                          ; preds = %entry
  ret i64 0

if.end:                                           ; No predecessors!
  unreachable
}
