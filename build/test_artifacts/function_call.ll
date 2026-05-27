; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/function_call.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/function_call.mc"
target triple = "x86_64-pc-linux-gnu"

define internal i64 @helper(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, ptr %x1, align 4
  %x.value = load i64, ptr %x1, align 4
  %multmp = mul i64 %x.value, 2
  ret i64 %multmp
}

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %helper.call = call i64 @helper(i64 %arg.value)
  %addtmp = add i64 %helper.call, 1
  ret i64 %addtmp
}
