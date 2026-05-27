; ModuleID = '/home/matveevda/projects/mini_compiler/tests/positive/if_false_branch.mc'
source_filename = "/home/matveevda/projects/mini_compiler/tests/positive/if_false_branch.mc"
target triple = "x86_64-pc-linux-gnu"

define i64 @compiled_fn(i64 %arg) {
entry:
  %arg1 = alloca i64, align 8
  store i64 %arg, ptr %arg1, align 4
  %arg.value = load i64, ptr %arg1, align 4
  %cmptmp = icmp slt i64 %arg.value, 5
  br i1 %cmptmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  ret i64 1

if.else:                                          ; preds = %entry
  ret i64 2

if.end:                                           ; No predecessors!
  unreachable
}
