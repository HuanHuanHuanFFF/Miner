# R17 MUL 整数往返最小接口交接

**选择B：UInt64精确乘积→Float32→UInt64，继续最小编译／代码生成判别；速度UNKNOWN。** A的“两U32cast＋FPmul＋UInt64反向cast”原件保留，不并排开两条完整计时队列。B少一个前向转换，但整数乘法和UInt64转换串行；没有按原语数宣布更快。

- 当前数学片段 `Bridge-u64-integer-v3-lf.lean.inc`：**6664B /2261f1e317310bfb6505eb3ee333ad8b6b31f9ad13307f728719ecd3920fb906**。13个新声明包含实际U64前向模型、整数decode／truncate／无夹断、48bit乘积无回卷、舍入阈值和匹配shift的尾数恢复证明尝试。未编译，不称已闭合。
- 当前运行片段 `Runtime-u64-mul-integer-v3-lf.lean.inc`：**1098B /cd301ba43a18ba2b9db2a8b2f1109406d00242acdd543b26364d9925ffde6c67**。原normal与S128..380域；一次整数乘、一次前向和一次反向cast；R阈值取2^47；E=S−127+b、q=R>>(23+b)、fraction=q−2^23；失败调用原fallback。新准入片段无toBits/ofBits站点，回退保留原调用。旧v2仅CRLF不同，完整保留，newline-receipt.json核了文本相等。
- **最小反例与边界证据：** v3有限模型23192对／21982准入、888个46→47进位、384偶平局和384奇平局，0差异；两种形式同R。另65536指数对验证新guard与原域完全相同。外部5秒timeout，约0.24秒。u=0x20000001,v=0x207ffffe证明按未舍入N选b会错；必须按R。没有读取未来holdout。
- **实际接口：** 固定Lean293d5d0c的UInt64.toFloat32、Float32.toUInt64均为Model def且runtime static inline；无夹断引理和FloatLib0d918257 exact-value/toInt桥已核原文。old-c972-binding.json重新核了旧实际C与输入5份SHA：旧准入路径确有external toBits，标量ASM仍缺。c972 whole1.03055/MUL1.08190负结果不重置。
- **机会与下一判别：** 已完成B2样本MUL占整包37.38%–38.21%；10%整包需消掉26.17%–26.75%的全部MUL时间，准入子域真实时间UNKNOWN。先查实际unsigned64前后转换是否引入helper、2^63补偿、clamp和spill；表面少调用不是收益。可选Diagnostic-entry-v2.lean.inc给两输入诊断caller，不冒充正式MainFull入口。
- **剩余接线：** runtime高位Bool→shift、U64→U32无回卷、E/fraction/sign到旧model_mul_normal_fields以及公共mul_spec尚未连接。原固定文本检查通过；未建大包、未跑Lean/CI/Git。仅作容量算术：c972＋选中LF两片段＋诊断caller为255515B，余485B；完整公共证明须先替换／裁掉已无用途的旧toBits桥，不能继续盲目追加。integration-boundary.md列明依赖。

初判在18:19:46前落盘，当前提前交付最小接口，不填满19:08:31窗口。tokens/cache UNKNOWN；CI占用0；CI启动授权仍由根／D核对。所有文件在本子目录；完整身份与当前选择见stage-status.json。
