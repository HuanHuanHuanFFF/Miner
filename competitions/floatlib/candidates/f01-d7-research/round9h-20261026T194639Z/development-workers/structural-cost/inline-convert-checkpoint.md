# R19 inline-convert检查点

本阶段UTC20:54:30接手，15分钟检查点上限21:09:30，30分钟上限21:24:30。只写本目录新文件，无Git/CI/编译/候选或manifest修改；未读取在途40398675395及后续D/A/B材料。

**决定：继续精确B2草稿，已有旧负结果不能判作这份B2/USize机制已失败。** `audit_inline_convert_history.py`核40164630534的58原件和40165220696的46原件，约5.16MB，逐项hash/大小一致。f65e4aa5在R15冻结清单为`COMPONENT_PROTOTYPE_NOT_SELECTED_STANDALONE`，只改旧R14ThinBCache的一条Nat/getD、单累加器、Array Float32 B读取路线，旧源没有R15PackedB2。

旧组合cb7f1099完整25轮gate正确，首D对DF whole0.980419638、BMM0.856268405、p05=-0.004020053，门槛失败保留；它还改了短n准入和scalar MUL cutoff84，因此不隔离转换成本。原C41493–41622确实将旧B1 A转换内联：合格分支用table+uint32→Float32+mul，ofBits只在拒绝分支；未发现同精确B2/双累加器/USize完整负测证据。详细边界见`inline-convert-history.json`。

**完整草稿已生成：** `Kernel-index-inline-convert.draft.lean`，SHA`f84ea2dbffbf0406f453bbc20b4335288ba5d77bb787ae33db203665016ac384`，234290B。父源精确9f7/234277B；仅两处替换：Indexed.wordLoop的A读取后用根`R2W01b.convert`，wordLoop_eq原simp列表加入根`R2W01c.convert_eq`。`inline-convert-exact-delta.json`及diff保存old/new原文，逆替换逐字节恢复9f7。packB、shape/global guard、finish、旧loop及全部其他字节不变，无A.map。

转换既有接纳域为幅值0或`0x0c000000 ≤ magnitude < 0x7f800000`，涵盖±0和E24..254；域外保留原ofBits。固定Lean头部确认uint32→Float32是内联C cast，ofBits为导出函数。当前9f7保存C的root converter用已存在共享scaleTable全局指针，合格分支没有per-step once。它们只支持可行性；**新source的Lean/replay/axioms/MainFull C/ASM/性能全部NOT_RUN，call和spill是否删除UNKNOWN。**

下一产物：精确两处更改的静态复核、证明义务及选中MainFull C/ASM验收条件；尤其要求从public bmm实际快速caller确认合格路径call-free，并逐路径检查spill，不能用root leaf C或旧B1成功代替。tokens/cache UNKNOWN，CI占用0。
