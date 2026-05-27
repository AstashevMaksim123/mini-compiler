; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/boolean_logic.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/boolean_logic.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %cmptmp = icmp sgt i64 %arg.value, 0
  %arg.value2 = load i64, ptr %arg1, align 4
  %eqtmp = icmp eq i64 %arg.value2, 5
  %nottmp = xor i1 %eqtmp, true
  %andtmp = and i1 %cmptmp, %nottmp
  br i1 %andtmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  ret i64 1

if.else:                                          ; preds = %entry
  ret i64 0

if.end:                                           ; No predecessors!
  unreachable
}
