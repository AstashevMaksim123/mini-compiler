	.text
	.file	"loop_switch_aggregation.mc"
	.p2align	4, 0x90                         # -- Begin function classify
	.type	classify,@function
classify:                               # @classify
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -8(%rsp)
	movq	-8(%rsp), %rax
	movq	%rax, -24(%rsp)                 # 8-byte Spill
	movabsq	$6148914691236517206, %rcx      # imm = 0x5555555555555556
	imulq	%rcx
	movq	-24(%rsp), %rax                 # 8-byte Reload
	movq	%rdx, %rcx
	shrq	$63, %rcx
	addq	%rcx, %rdx
	leaq	(%rdx,%rdx,2), %rcx
	subq	%rcx, %rax
	movq	%rax, -16(%rsp)                 # 8-byte Spill
	je	.LBB0_2
	jmp	.LBB0_4
.LBB0_4:                                # %entry
	movq	-16(%rsp), %rax                 # 8-byte Reload
	subq	$1, %rax
	je	.LBB0_3
	jmp	.LBB0_1
.LBB0_1:                                # %switch.default
	movl	$7, %eax
	retq
.LBB0_2:                                # %switch.case
	movl	$3, %eax
	retq
.LBB0_3:                                # %switch.case2
	movl	$5, %eax
	retq
.Lfunc_end0:
	.size	classify, .Lfunc_end0-classify
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
	movq	%rdi, (%rsp)
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
.LBB1_1:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	16(%rsp), %rax
	cmpq	(%rsp), %rax
	jge	.LBB1_4
# %bb.2:                                # %for.body
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	16(%rsp), %rdi
	callq	classify
	movq	%rax, 24(%rsp)
	movq	24(%rsp), %rax
	movq	%rax, 32(%rsp)
	cmpq	$0, 16(%rsp)
	setg	%al
	cmpq	$4, 16(%rsp)
	setl	%cl
	andb	%cl, %al
	testb	$1, %al
	jne	.LBB1_5
	jmp	.LBB1_6
.LBB1_3:                                # %for.step
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	16(%rsp), %rax
	addq	$1, %rax
	movq	%rax, 16(%rsp)
	jmp	.LBB1_1
.LBB1_4:                                # %for.end
	movq	8(%rsp), %rax
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB1_5:                                # %if.then
                                        #   in Loop: Header=BB1_1 Depth=1
	.cfi_def_cfa_offset 48
	movq	32(%rsp), %rax
	addq	16(%rsp), %rax
	movq	%rax, 32(%rsp)
	jmp	.LBB1_7
.LBB1_6:                                # %if.else
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	32(%rsp), %rax
	subq	$1, %rax
	movq	%rax, 32(%rsp)
.LBB1_7:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	8(%rsp), %rax
	addq	32(%rsp), %rax
	movq	%rax, 8(%rsp)
	cmpq	$40, 8(%rsp)
	jle	.LBB1_9
# %bb.8:                                # %if.then13
	jmp	.LBB1_4
.LBB1_9:                                # %if.else14
                                        #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_3
.Lfunc_end1:
	.size	compiled_fn, .Lfunc_end1-compiled_fn
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym classify
