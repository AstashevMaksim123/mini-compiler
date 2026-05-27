; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/assignment.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/assignment.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %x = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  store i64 %arg.value, ptr %x, align 4
  %x.value = load i64, ptr %x, align 4
  %addtmp = add i64 %x.value, 7
  store i64 %addtmp, ptr %x, align 4
  %x.value2 = load i64, ptr %x, align 4
  ret i64 %x.value2
}
