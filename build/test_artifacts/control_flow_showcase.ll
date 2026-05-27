; ModuleID = '/home/matveevda/projects/mini_compiler/tests/showcase/control_flow_showcase.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/showcase/control_flow_showcase.mc"
target triple = "x86_64-pc-linux-gnu"

define internal i64 @score(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, ptr %x1, align 4
  %x.value = load i64, ptr %x1, align 4
  %modtmp = srem i64 %x.value, 2
  %eqtmp = icmp eq i64 %modtmp, 0
  br i1 %eqtmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x.value2 = load i64, ptr %x1, align 4
  %addtmp = add i64 %x.value2, 1
  ret i64 %addtmp

if.else:                                          ; preds = %entry
  %x.value3 = load i64, ptr %x1, align 4
  %multmp = mul i64 %x.value3, 2
  ret i64 %multmp

if.end:                                           ; No predecessors!
  unreachable
}

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
  %arg.value = load i64, ptr %arg1, align 4
  %cmptmp = icmp slt i64 %i.value, %arg.value
  br i1 %cmptmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %i.value2 = load i64, ptr %i, align 4
  %eqtmp = icmp eq i64 %i.value2, 2
  br i1 %eqtmp, label %if.then, label %if.else

for.step:                                         ; preds = %if.end19, %if.then
  %i.value22 = load i64, ptr %i, align 4
  %addtmp23 = add i64 %i.value22, 1
  store i64 %addtmp23, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %if.then17, %for.cond
  %total.value24 = load i64, ptr %total, align 4
  ret i64 %total.value24

if.then:                                          ; preds = %for.body
  br label %for.step

if.else:                                          ; preds = %for.body
  %total.value = load i64, ptr %total, align 4
  %addtmp = add i64 %total.value, 0
  store i64 %addtmp, ptr %total, align 4
  br label %if.end

if.end:                                           ; preds = %if.else
  %i.value3 = load i64, ptr %i, align 4
  %modtmp = srem i64 %i.value3, 4
  switch i64 %modtmp, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case7
    i64 2, label %switch.case10
  ]

switch.end:                                       ; preds = %switch.default, %switch.case10, %switch.case7, %switch.case
  %total.value15 = load i64, ptr %total, align 4
  %cmptmp16 = icmp sgt i64 %total.value15, 60
  br i1 %cmptmp16, label %if.then17, label %if.else18

switch.default:                                   ; preds = %if.end
  %total.value13 = load i64, ptr %total, align 4
  %addtmp14 = add i64 %total.value13, 30
  store i64 %addtmp14, ptr %total, align 4
  br label %switch.end

switch.case:                                      ; preds = %if.end
  %total.value4 = load i64, ptr %total, align 4
  %i.value5 = load i64, ptr %i, align 4
  %score.call = call i64 @score(i64 %i.value5)
  %addtmp6 = add i64 %total.value4, %score.call
  store i64 %addtmp6, ptr %total, align 4
  br label %switch.end

switch.case7:                                     ; preds = %if.end
  %total.value8 = load i64, ptr %total, align 4
  %addtmp9 = add i64 %total.value8, 10
  store i64 %addtmp9, ptr %total, align 4
  br label %switch.end

switch.case10:                                    ; preds = %if.end
  %total.value11 = load i64, ptr %total, align 4
  %addtmp12 = add i64 %total.value11, 20
  store i64 %addtmp12, ptr %total, align 4
  br label %switch.end

if.then17:                                        ; preds = %switch.end
  br label %for.end

if.else18:                                        ; preds = %switch.end
  %total.value20 = load i64, ptr %total, align 4
  %addtmp21 = add i64 %total.value20, 1
  store i64 %addtmp21, ptr %total, align 4
  br label %if.end19

if.end19:                                         ; preds = %if.else18
  br label %for.step
}
