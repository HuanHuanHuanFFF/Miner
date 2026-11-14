# R22 A：B-only checked FloatArray 前提

**冻结储备页**：当前A唯一索引转[../expected-native-word/HANDOFF.md](../expected-native-word/HANDOFF.md)。本页f5a/303a/91ac字节保持，后继仅独立数学接口。

源/历史阶段首工具 **00:56:40 UTC**。root随后授权最小runtime，**01:10:02—01:30:02 UTC**；共同截止03:12:47。D决定余槽，本方无CI或公共正确性证明。

- **最小完整callback已落**：[Runtime.lean.inc](Runtime.lean.inc) **f5a6cbc6 / 6405B**；[Kernel-probe.lean](Kernel-probe.lean) **303a2397 / 235009B**，**NOT_RUN**。原622d全文逐字前缀、四公开入口仍B2；另接旧emit_size、B fb7d原件和4个新size辅助根。真正待测入口`Submission.R22FloatArrayB2.guarded`，**未有该入口的bmm_spec**。根/依赖/字节见[runtime-manifest.json](runtime-manifest.json)。
- runtime严格保原B2 underflow→zeros表达式；原p2..8,n>1,m>=4门槛；新prepare失败及其它入口完整`Submission.bmm`。一tile单遍两次check后push同两d，原奇右物理读取保留。没有Array Float中间体、USize或unroll；安全Nat get用擦除size界。4个size根仅包装合法输出，不是数值正确性。
- [address-screen.json](address-screen.json)：2112形状、55440有效输出原序地址比较、43200准备字段地址、3584失败oracle前缀；去batch/左右互换两变异均抓。仅有限整数/任意token检查，不是Float32或Lean。
- **准备协议小桥**：[CheckedPrefix.lean.inc](CheckedPrefix.lean.inc) **91ac9aa7 /4559B/4公开辅助根/NOT_RUN**；[prefix-manifest.json](prefix-manifest.json)。四个push/get支持证明逐字复用98cef（仅private修饰），fb7d给条件native值等式；闭空前缀、单push、直接get、actual两字段append。没有recursive builder成功、loop或public BMM证明，未拼入303a，f5a/303a字节不变。阶段01:24:29起，01:27:43成稿。
- **冻结后成本前提补核**：[ALLOCATION-PREMISE.md](ALLOCATION-PREMISE.md) **5963f32b/6383B**、[allocation-premise.json](allocation-premise.json)，仅冻结前旧源。Tile/Vector证明字段按固定compiler消去；源码每tile一个some、全cache一个some，普通落地约16(T+1)请求。旧622d实际pack C有64B外closure+56B/tile内closure，不能漏算。24N→16N仅持久payload/record/slot部分；加Option而不计旧闭包时n2无累计字节收益。预分配不增长仍检查独占，共享会复制。失败树无逃逸/环，原rawA/B保留fallback；实际C释放时点/RSS仍UNKNOWN。三冻结源SHA再核不变，无新CI/版本或确认数据。

- **API已核**：293d header两cast均static inline；FloatArray.get/uget直接double读取，公开push/uget可用。push本身是准备期export函数，仍有容量/独占检查。只在存储上用double，热运算必须先narrow再F32 MUL/ADD。
- **旧机制可复用**：5be/98cef已做每输入一次校验，98cef单遍check同一个d后push，热dot无校验。旧全A/B平坦单输出布局与Array Float32原BMM样本基本持平（归一化1.00305/1.00441/1.00266）；不是当前B2-only双列缓存负面。新目标检查应回原nativeB，不能强求非canonical rawNaN等于原rawB。
- **唯一新差异**：保rawA/原pair链/原finish，tile变2*n个double，N个F2+指针槽请求24N→16N；代价为每k两narrow、每字段prepare位检查与push。直接native双边检查需2个toBits/字段，旧不存在字段boxes。失败prefix与原fallback计费。
- **首判别**：先真实typing，再看caller准备无Array Float/`.data`中间体，hot无检查/外部转换/分配，F32次序与原NaN replay不变；再测完整生命周期。新actual C/ASM/cost均UNKNOWN，无速度承诺。原字段native Prefix/pack成功传播与public refinement留待成本支持后接。

[REVIEW.md](REVIEW.md)给精确版本、旧原样本、API行号、pack投影与缺口。旧C原路径当前缺失，只读到hash-bound审计；未把它说成本次原C重验。单一当前A索引是本页。上阶段wordcarry纸面已交；5f5b等证明继续冻结NOT_RUN。
