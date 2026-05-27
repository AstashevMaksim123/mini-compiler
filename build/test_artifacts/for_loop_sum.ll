; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/for_loop_sum.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/for_loop_sum.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
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
  %sum.value = load i64, ptr %sum, align 4
  %i.value2 = load i64, ptr %i, align 4
  %addtmp = add i64 %sum.value, %i.value2
  store i64 %addtmp, ptr %sum, align 4
  br label %for.step

for.step:                                         ; preds = %for.body
  %i.value3 = load i64, ptr %i, align 4
  %addtmp4 = add i64 %i.value3, 1
  store i64 %addtmp4, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %sum.value5 = load i64, ptr %sum, align 4
  ret i64 %sum.value5
}
