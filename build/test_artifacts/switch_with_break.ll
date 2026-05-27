; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/switch_with_break.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/switch_with_break.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  switch i64 %arg.value, label %switch.default [
    i64 10, label %switch.case
  ]

switch.end:                                       ; preds = %switch.case
  ret i64 77

switch.default:                                   ; preds = %entry
  ret i64 1

switch.case:                                      ; preds = %entry
  br label %switch.end
}
