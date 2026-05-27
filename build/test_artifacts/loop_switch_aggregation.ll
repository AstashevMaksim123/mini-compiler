; ModuleID = '/home/matveevda/projects/mini_compiler/tests/showcase/loop_switch_aggregation.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/showcase/loop_switch_aggregation.mc"
target triple = "x86_64-pc-linux-gnu"

define internal i64 @classify(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, ptr %x1, align 4
  %x.value = load i64, ptr %x1, align 4
  %modtmp = srem i64 %x.value, 3
  switch i64 %modtmp, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case2
  ]

switch.end:                                       ; No predecessors!
  unreachable

switch.default:                                   ; preds = %entry
  ret i64 7

switch.case:                                      ; preds = %entry
  ret i64 3

switch.case2:                                     ; preds = %entry
  ret i64 5
}

define i64 @compiled_fn(i64 %arg) {
entry:
  %local = alloca i64, align 8
  %value = alloca i64, align 8
  %i = alloca i64, align 8
  %sum = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  store i64 0, ptr %sum, align 4
  store i64 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.step, %entry
  %i.value = load i64, ptr %i, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %cmptmp = icmp slt i64 %i.value, %arg.value
  br i1 %cmptmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %i.value2 = load i64, ptr %i, align 4
  %classify.call = call i64 @classify(i64 %i.value2)
  store i64 %classify.call, ptr %value, align 4
  %value.value = load i64, ptr %value, align 4
  store i64 %value.value, ptr %local, align 4
  %i.value3 = load i64, ptr %i, align 4
  %cmptmp4 = icmp sgt i64 %i.value3, 0
  %i.value5 = load i64, ptr %i, align 4
  %cmptmp6 = icmp slt i64 %i.value5, 4
  %andtmp = and i1 %cmptmp4, %cmptmp6
  br i1 %andtmp, label %if.then, label %if.else

for.step:                                         ; preds = %if.end15, %if.else14
  %i.value16 = load i64, ptr %i, align 4
  %addtmp17 = add i64 %i.value16, 1
  store i64 %addtmp17, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %if.then13, %for.cond
  %sum.value18 = load i64, ptr %sum, align 4
  ret i64 %sum.value18

if.then:                                          ; preds = %for.body
  %local.value = load i64, ptr %local, align 4
  %i.value7 = load i64, ptr %i, align 4
  %addtmp = add i64 %local.value, %i.value7
  store i64 %addtmp, ptr %local, align 4
  br label %if.end

if.else:                                          ; preds = %for.body
  %local.value8 = load i64, ptr %local, align 4
  %subtmp = sub i64 %local.value8, 1
  store i64 %subtmp, ptr %local, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %sum.value = load i64, ptr %sum, align 4
  %local.value9 = load i64, ptr %local, align 4
  %addtmp10 = add i64 %sum.value, %local.value9
  store i64 %addtmp10, ptr %sum, align 4
  %sum.value11 = load i64, ptr %sum, align 4
  %cmptmp12 = icmp sgt i64 %sum.value11, 40
  br i1 %cmptmp12, label %if.then13, label %if.else14

if.then13:                                        ; preds = %if.end
  br label %for.end

if.else14:                                        ; preds = %if.end
  br label %for.step

if.end15:                                         ; No predecessors!
  br label %for.step
}
