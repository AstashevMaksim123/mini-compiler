; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/switch_middle_case.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/switch_middle_case.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %x = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  store i64 1, ptr %x, align 4
  %x.value = load i64, ptr %x, align 4
  switch i64 %x.value, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case2
  ]

switch.end:                                       ; No predecessors!
  unreachable

switch.default:                                   ; preds = %entry
  %arg.value = load i64, ptr %arg1, align 4
  ret i64 %arg.value

switch.case:                                      ; preds = %entry
  ret i64 100

switch.case2:                                     ; preds = %entry
  ret i64 101
}
