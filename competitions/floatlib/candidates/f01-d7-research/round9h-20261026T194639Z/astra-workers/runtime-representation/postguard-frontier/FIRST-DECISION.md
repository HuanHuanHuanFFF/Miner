# 后置检查首决定（21:11 UTC）

**21:27 UTC新证据更新：暂缓aeaae的CI排队，以下21:11判断保留为历史时点。** 根的`astra-peer-discovery-40397668271.json`已核49份peer原件及源码差分：th0 `14a6ae2f9afd31cd584b5087fe24e001663d16222856515c9a4c4e10c1322ea5`仅把B2主MUL阈值128改为0；同批4份原完整gate/25轮通过，发现D whole/B2=0.9690534785132748、p05=0.02115601166435621。**仅发现组，未读取A/B、未采用；当前保留版仍B2/622d。** 性能原因仍UNKNOWN，阈值改动既删除分派，也把原LowScale输入送入native，不能把观察收益全归因于几条exsum指令。

该更便宜竞争实现已覆盖本稿声称的exsum前门消除机会。后续首次真实成本判断必须同时保留**B2、th0、冻结aeaae**对照；不能只比B2，更不能把th0的3.09%发现收益归给fused domain。需确认的是相对th0尚余的decoder资格判断和post-result检查节省，是否抵消joint guard、域外回退及布局成本。aeaae域外仍走原B2 LowScale分派，不能假定它继承th0全域路由或与th0收益相加。先复用新回执/必要代码生成做差分，证据不足就继续暂缓；不自动派CI、不改源、不添组合或范围变体。aeaae源码哈希已重新核对不变，compiled/codegen/fullgate/timing仍NOT_RUN。

**ADD停；保留一次MUL-only限定重访，先代码生成判别。** 本阶段20:56:36开始，21:16:36前交第一决定；主窗04:46:39不变。仅写本目录，无Git/CI/本机Lean/嵌套。

旧路线已核：R6 bdbc完整fastOK融合、8a0e normal区间、e46 upper外提；R7 60f scalar仍是finite input guard，后续改result self-BEq。R11 e279联合OR前门完整D919为whole1.008306、ADD1.051906、MUL1.011388（对41）；R12 42c cold结果复用未达标，R16高位ADD完整正确却whole1.29455/ADD1.87392。旧负面及UNKNOWN保持，不把旧input guard当新发现。

**新条件有实际C依据：** R11 selected MainFull MUL父路是两次ofBits；B2已变为两次带guard的numeric decoder。故复用旧E64..191联合guard在B2命中臂可绕过exsum/LowScale判断、两decoder资格判断与result self-BEq，保留同一套cast/table/3次MUL/toBits。输出toBits本身的NaN规范化仍在；域外多付一次joint guard后走精确B2。ADD没有这个新条件，保持原body。

最小完整源 `Kernel-postguard-mul-only.lean`：230900B，SHA256 `aeaae0d9b9d8557f2acc868c6dfbf5bb4779b0560e6e55ceb01461fc22742377`。13显式root，逆splice恢复622d，复用已读的finite native bridge/roundtrip与旧guard证明；**新Lean/C/gate/timing均NOT_RUN**。仅此一份，无区间/seed网格。

冻结模型ADD36.56%/MUL38.72%不是新测量；MUL-only整包10%需MUL降25.82%，目前未证明。旧R15输入模型ML/paired共4096/4096命中、dense1459/1536；sparse/subnormal/extremes大量miss仍付前门，频数不作耗时。真实selected MainFull需核净删除工作与miss成本，代码未变优则停，再好才考虑完整D及原D+A+B。

证据：`frontier-evidence.json`绑定历史源/原verdict/两份实际MainFull和暴露模型；`candidate-manifest.json`、`HelperAudit-postguard.lean.inc`；详细边界在`analysis.md`。不自动追加CI。
