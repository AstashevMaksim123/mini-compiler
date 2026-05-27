	.text
	.file	"control_flow_showcase.mc"
	.p2align	4, 0x90                         # -- Begin function score
	.type	score,@function
score:                                  # @score
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	-8(%rsp), %rax
	movl	$2, %ecx
	cqto
	idivq	%rcx
	cmpq	$0, %rdx
	jne	.LBB0_2
# %bb.1:                                # %if.then
	movq	-8(%rsp), %rax
	addq	$1, %rax
	retq
.LBB0_2:                                # %if.else
	movq	-8(%rsp), %rax
	shlq	%rax
	retq
.Lfunc_end0:
	.size	score, .Lfunc_end0-score
	.cfi_endproc
                                        # -- End function
	.globl	compiled_fn                     # -- Begin function compiled_fn
	.p2align	4, 0x90
	.type	compiled_fn,@function
compiled_fn:                            # @compiled_fn
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
.LBB1_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	32(%rsp), %rax
	cmpq	16(%rsp), %rax
	jge	.LBB1_4
# %bb.2:                                # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	cmpq	$2, 32(%rsp)
	je	.LBB1_5
	jmp	.LBB1_6
.LBB1_3:                                # %for.step
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	32(%rsp), %rax
	addq	$1, %rax
	movq	%rax, 32(%rsp)
	jmp	.LBB1_1
.LBB1_4:                                # %for.end
	movq	24(%rsp), %rax
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB1_5:                                # %if.then
                                        #   in Loop: Header=BB1_1 Depth=1
	.cfi_def_cfa_offset 48
	jmp	.LBB1_3
.LBB1_6:                                # %if.else
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	addq	$0, %rax
	movq	%rax, 24(%rsp)
# %bb.7:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	32(%rsp), %rax
	movq	%rax, %rdx
	addq	$3, %rdx
	testq	%rax, %rax
	movq	%rax, %rcx
	cmovsq	%rdx, %rcx
	andq	$-4, %rcx
	subq	%rcx, %rax
	movq	%rax, 8(%rsp)                   # 8-byte Spill
	je	.LBB1_10
	jmp	.LBB1_16
.LBB1_16:                               # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	8(%rsp), %rax                   # 8-byte Reload
	subq	$1, %rax
	je	.LBB1_11
	jmp	.LBB1_17
.LBB1_17:                               # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	8(%rsp), %rax                   # 8-byte Reload
	subq	$2, %rax
	je	.LBB1_12
	jmp	.LBB1_9
.LBB1_8:                                # %switch.end
                                        #   in Loop: Header=BB1_1 Depth=1
	cmpq	$60, 24(%rsp)
	jg	.LBB1_13
	jmp	.LBB1_14
.LBB1_9:                                # %switch.default
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	addq	$30, %rax
	movq	%rax, 24(%rsp)
	jmp	.LBB1_8
.LBB1_10:                               # %switch.case
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	movq	%rax, (%rsp)                    # 8-byte Spill
	movq	32(%rsp), %rdi
	callq	score
	movq	%rax, %rcx
	movq	(%rsp), %rax                    # 8-byte Reload
	addq	%rcx, %rax
	movq	%rax, 24(%rsp)
	jmp	.LBB1_8
.LBB1_11:                               # %switch.case7
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	addq	$10, %rax
	movq	%rax, 24(%rsp)
	jmp	.LBB1_8
.LBB1_12:                               # %switch.case10
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	addq	$20, %rax
	movq	%rax, 24(%rsp)
	jmp	.LBB1_8
.LBB1_13:                               # %if.then17
	jmp	.LBB1_4
.LBB1_14:                               # %if.else18
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	24(%rsp), %rax
	addq	$1, %rax
	movq	%rax, 24(%rsp)
# %bb.15:                               # %if.end19
                                        #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_3
.Lfunc_end1:
	.size	compiled_fn, .Lfunc_end1-compiled_fn
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym score
