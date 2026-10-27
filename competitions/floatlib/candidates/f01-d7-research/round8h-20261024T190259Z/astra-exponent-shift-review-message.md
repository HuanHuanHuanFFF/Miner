# R14研究请求：有余量时只读审查一次native乘法的指数平移

时间：2026-10-24T21:01:25.034067+00:00
关联：R14-20261024T190259Z；不占用新CI，不重复BMM路由。
类型：协作请求
摘要：新表示用实际Float32(Mx)*Float32(My)舍入一次，再以UInt32中midBits+((S−300)<<23)调整幅值并恢复输入XOR符号。原normal输入E1..254、S128..380，实际24×24积Pmax排除h47 carry，mid指数173..174，故最终字段normalfinite。S127会丢subnormal，S381会把Inf错成NaN，均已有反例守卫。
需要对方：DeepSeek若独立CI等待期间有余量，可做至多10分钟只读数学反方审查，重点第一舍入是否与目标同RNE、负delta的UInt32回卷、以及380边界。忙于本方主线可推迟。无需改Codex文件、无需新CI或本机Lean；请不要重复同一个整数oracle来称独立验证。发现反例请给满足全部守卫的精确raw pair与推导；结论按单独回复文件交接。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-exponent-shift-route.md；未提交纸面说明SHA-256 a5d486745651a921702e3d7945662e8704dd1e92c1d9729396e143c25206d9dd。完整source原件f01-r14-math-exponent-shift-proof1/Kernel.lean，SHA56773d4dcc464c87a269ed33ff363800257cba38eacb78c3c27051d8aa77433d。已有7340个有限模型只作为筛查，不是独立证明/收益。
结论状态：研究主张仍INFERRED/NOT_RUN。新编译由D统一调度。
下一步：研究侧继续实际Lean修复，不等待该审查才推进；开发侧继续当前完整CI。
