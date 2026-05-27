; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/nested_switch_inside_for.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/nested_switch_inside_for.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %i = alloca i64, align 8
  %total = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  store i64 0, ptr %total, align 4
  store i64 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.step, %entry
  %i.value = load i64, ptr %i, align 4
  %cmptmp = icmp slt i64 %i.value, 5
  br i1 %cmptmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %i.value2 = load i64, ptr %i, align 4
  %modtmp = srem i64 %i.value2, 3
  switch i64 %modtmp, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case3
  ]

for.step:                                         ; preds = %switch.end
  %i.value8 = load i64, ptr %i, align 4
  %addtmp9 = add i64 %i.value8, 1
  store i64 %addtmp9, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %total.value10 = load i64, ptr %total, align 4
  ret i64 %total.value10

switch.end:                                       ; preds = %switch.default, %switch.case3, %switch.case
  br label %for.step

switch.default:                                   ; preds = %for.body
  %total.value6 = load i64, ptr %total, align 4
  %addtmp7 = add i64 %total.value6, 100
  store i64 %addtmp7, ptr %total, align 4
  br label %switch.end

switch.case:                                      ; preds = %for.body
  %total.value = load i64, ptr %total, align 4
  %addtmp = add i64 %total.value, 10
  store i64 %addtmp, ptr %total, align 4
  br label %switch.end

switch.case3:                                     ; preds = %for.body
  %total.value4 = load i64, ptr %total, align 4
  %addtmp5 = add i64 %total.value4, 1
  store i64 %addtmp5, ptr %total, align 4
  br label %switch.end
}
