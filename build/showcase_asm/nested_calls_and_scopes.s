	.text
	.file	"nested_calls_and_scopes.mc"
	.p2align	4, 0x90                         # -- Begin function clamp
	.type	clamp,@function
clamp:                                  # @clamp
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	-8(%rsp), %rax
	movq	%rax, -16(%rsp)                 # 8-byte Spill
	testq	%rax, %rax
	je	.LBB0_2
	jmp	.LBB0_6
.LBB0_6:                                # %entry
	movq	-16(%rsp), %rax                 # 8-byte Reload
	subq	$1, %rax
	je	.LBB0_3
	jmp	.LBB0_1
.LBB0_1:                                # %switch.default
	cmpq	$5, -8(%rsp)
	jg	.LBB0_4
	jmp	.LBB0_5
.LBB0_2:                                # %switch.case
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	retq
.LBB0_3:                                # %switch.case2
	movl	$1, %eax
	retq
.LBB0_4:                                # %if.then
	movl	$5, %eax
	retq
.LBB0_5:                                # %if.else
	movq	-8(%rsp), %rax
	retq
.Lfunc_end0:
	.size	clamp, .Lfunc_end0-clamp
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function mix
	.type	mix,@function
mix:                                    # @mix
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 8(%rsp)
	movq	%rsi, 16(%rsp)
	movq	8(%rsp), %rax
	movq	%rax, 24(%rsp)
	movq	16(%rsp), %rax
	addq	$2, %rax
	movq	%rax, 32(%rsp)
	cmpq	$10, 32(%rsp)
	jle	.LBB1_2
# %bb.1:                                # %if.then
	movq	32(%rsp), %rdi
	callq	clamp
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB1_2:                                # %if.else
	.cfi_def_cfa_offset 48
	movq	24(%rsp), %rax
	addq	32(%rsp), %rax
	movq	%rax, 24(%rsp)
# %bb.3:                                # %if.end
	movq	24(%rsp), %rdi
	callq	clamp
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	mix, .Lfunc_end1-mix
	.cfi_endproc
                                        # -- End function
	.globl	compiled_fn                     # -- Begin function compiled_fn
	.p2align	4, 0x90
	.type	compiled_fn,@function
compiled_fn:                            # @compiled_fn
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, (%rsp)
	movq	(%rsp), %rdi
	movl	$3, %esi
	callq	mix
	movq	%rax, 8(%rsp)
	movq	(%rsp), %rax
	movl	$2, %ecx
	cqto
	idivq	%rcx
	movq	%rax, %rsi
	movl	$2, %edi
	callq	mix
	movq	%rax, 16(%rsp)
	cmpq	$5, 8(%rsp)
	sete	%al
	cmpq	$5, 16(%rsp)
	sete	%cl
	andb	%cl, %al
	testb	$1, %al
	jne	.LBB2_1
	jmp	.LBB2_2
.LBB2_1:                                # %if.then
	movq	8(%rsp), %rax
	addq	16(%rsp), %rax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB2_2:                                # %if.else
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	compiled_fn, .Lfunc_end2-compiled_fn
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym clamp
	.addrsig_sym mix
