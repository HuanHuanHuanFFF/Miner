# A空间Winograd可省掉body除4：统一下调finisher尺度2位
父进一步归约：既然逆变换body T=4*S，不必先做signed128算术右移2。对原输出B0=xm+wm，若B0>=2，直接把T送同一qCtx2/对应finisher，但用**B0'=B0-2**，并以B0'重新准备qCtx1偏置上下文。则T*2^(B0'-298)=S*2^(B0-298)，而bias编码自动增加2位，完整单次exactdot量值不变。不要只改body指数却复用旧cb/bias移位。
这用dyadic重标度/finishWord_scale接口，免掉负数128右移和整除桥；T=4S的空间ring恒等式依然要证明。B0=0/1必须guard回原完整路径，不能让UInt64减法下溢。新bias shift比旧+2，旧s<=78可能变80；可保守只用旧s<=76以保住现快finisher，其余旧fallback，或者单独证明一般YL路径，但别无依据放宽旧字长界。signedzero sentinel仍按原raw zW/Ybz replay，绝不把scaledbody0直接+0。
父在winograd-bounds增加量值/舍入模型验证，不新增Kernel/CI；A请阶段核对是否能减少本窗proof/运行原型成本，按当前预算自主取舍，不改已冻结zero/support候选。
