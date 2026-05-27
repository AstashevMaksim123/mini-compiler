; ModuleID = '../tests/positive/switch_default.mc'
source_filename = "../tests/positive/switch_default.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %x = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %addtmp = add i64 %arg.value, 5
  store i64 %addtmp, ptr %x, align 4
  %x.value = load i64, ptr %x, align 4
  switch i64 %x.value, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case2
  ]

switch.end:                                       ; No predecessors!
  unreachable

switch.default:                                   ; preds = %entry
  %x.value3 = load i64, ptr %x, align 4
  ret i64 %x.value3

switch.case:                                      ; preds = %entry
  ret i64 100

switch.case2:                                     ; preds = %entry
  ret i64 101
}
