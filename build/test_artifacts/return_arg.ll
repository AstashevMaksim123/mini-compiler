; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/return_arg.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/return_arg.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  ret i64 %arg.value
}
