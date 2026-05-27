; ModuleID = '/home/matveevda/projects/mini_compiler/tests/showcase/nested_calls_and_scopes.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/showcase/nested_calls_and_scopes.mc"
target triple = "x86_64-pc-linux-gnu"

define internal i64 @clamp(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, ptr %x1, align 4
  %x.value = load i64, ptr %x1, align 4
  switch i64 %x.value, label %switch.default [
    i64 0, label %switch.case
    i64 1, label %switch.case2
  ]

switch.end:                                       ; preds = %if.end
  unreachable

switch.default:                                   ; preds = %entry
  %x.value3 = load i64, ptr %x1, align 4
  %cmptmp = icmp sgt i64 %x.value3, 5
  br i1 %cmptmp, label %if.then, label %if.else

switch.case:                                      ; preds = %entry
  ret i64 0

switch.case2:                                     ; preds = %entry
  ret i64 1

if.then:                                          ; preds = %switch.default
  ret i64 5

if.else:                                          ; preds = %switch.default
  %x.value4 = load i64, ptr %x1, align 4
  ret i64 %x.value4

if.end:                                           ; No predecessors!
  br label %switch.end
}

define internal i64 @mix(i64 %a, i64 %b) {
entry:
  %inner = alloca i64, align 8
  %result = alloca i64, align 8
  %b2 = alloca i64, align 8
  %a1 = alloca i64, align 8
  store i64 %a, ptr %a1, align 4
  store i64 %b, ptr %b2, align 4
  %a.value = load i64, ptr %a1, align 4
  store i64 %a.value, ptr %result, align 4
  %b.value = load i64, ptr %b2, align 4
  %addtmp = add i64 %b.value, 2
  store i64 %addtmp, ptr %inner, align 4
  %inner.value = load i64, ptr %inner, align 4
  %cmptmp = icmp sgt i64 %inner.value, 10
  br i1 %cmptmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %inner.value3 = load i64, ptr %inner, align 4
  %clamp.call = call i64 @clamp(i64 %inner.value3)
  ret i64 %clamp.call

if.else:                                          ; preds = %entry
  %result.value = load i64, ptr %result, align 4
  %inner.value4 = load i64, ptr %inner, align 4
  %addtmp5 = add i64 %result.value, %inner.value4
  store i64 %addtmp5, ptr %result, align 4
  br label %if.end

if.end:                                           ; preds = %if.else
  %result.value6 = load i64, ptr %result, align 4
  %clamp.call7 = call i64 @clamp(i64 %result.value6)
  ret i64 %clamp.call7
}

define i64 @compiled_fn(i64 %arg) {
entry:
  %right = alloca i64, align 8
  %left = alloca i64, align 8
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %mix.call = call i64 @mix(i64 %arg.value, i64 3)
  store i64 %mix.call, ptr %left, align 4
  %arg.value2 = load i64, ptr %arg1, align 4
  %divtmp = sdiv i64 %arg.value2, 2
  %mix.call3 = call i64 @mix(i64 2, i64 %divtmp)
  store i64 %mix.call3, ptr %right, align 4
  %left.value = load i64, ptr %left, align 4
  %eqtmp = icmp eq i64 %left.value, 5
  %right.value = load i64, ptr %right, align 4
  %eqtmp4 = icmp eq i64 %right.value, 5
  %andtmp = and i1 %eqtmp, %eqtmp4
  br i1 %andtmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %left.value5 = load i64, ptr %left, align 4
  %right.value6 = load i64, ptr %right, align 4
  %addtmp = add i64 %left.value5, %right.value6
  ret i64 %addtmp

if.else:                                          ; preds = %entry
  ret i64 0

if.end:                                           ; No predecessors!
  unreachable
}
