# R15 公开起点与真实运行入口审查

2026-10-25 04:53:28Z 接受；05:02:38Z 已取得下列实物结论。本分工的有界调查完成，整轮冲冠目标未完成。当前没有值得因本报告单独占用完整 CI 的新候选。仅写本目录；没有 Git/index/branch/push/CI、Lean、本机重编译、子 agent、消息、正式提交或资金操作。

**本次实质变化**是刷新原作者当前固定源码，并在精确 df5c 原生成 C 中核对真实 callee；不是把旧 M16、R9、R14 解释换名再试。性能保持 NOT_RUN；机器码和动态成本未由静态源码推断。

## 已核查的来源

| 来源 | 本次实际取得 | 决定 |
|---|---|---|
| 官方内核仓库 | main 仍为 `4b7e83841cc0c32c6529f533923c73d33b5ecf97`；21 个公开 branch；full incumbent 33043 B，SHA `5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868`，与本地旧参考逐字节相同 | Conjectures.io / MIT，属于旧参考，没有取得冠军代码 |
| 当前公开 validator | main 仍为 `38533e8620a9da0cd66568d79b82e0041eef55e0`；实际 floatlib.py 只注册 metadata、health、leaderboard、champions、detail、report GET | 当前源码没有 FloatLib source handler。R11 的4次源404不重放为今天的404；当前冠军代码、作者、许可证、其他地点可得性仍 UNKNOWN |
| 固定 Lean | v4.34.0 tag 直接指向 `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`；实际 lean.h / object.cpp / LICENSE 已取回 | Apache-2.0；文件头作者 Leonardo de Moura，版权 Microsoft Corporation。运行时语义与旧报告一致 |
| 固定 FloatLib | 官方 manifest 固定 `0d91825727839f597fd06b22fdd038ea21480f0c`；实际 Mul dispatch、Narrow mul 和 native Representation 源码 | FloatLib Team / MIT；已有 checked word 后端，无新直接 native 桥 |
| 原作者最新 FloatLib | main `51e6940eaa4014691be91f663a49ca7239ca0c07`，包版本2.0.0，Lean4.35.0 | 新版 Narrow `mulFiniteWord?` 与旧 `mulFiniteImpl?` 运行体规范化名字后完全相同；ModelBridge 是 word/dyadic/model 证明。所查文件没有 native Float→Float32 RNE 桥；不升级依赖 |

原文、来源 URL、UTF-8长度、SHA-256、Git blob身份及许可在 [source-index.json](source-index.json)、[current-floatlib-comparison.json](current-floatlib-comparison.json)。GitHub connector不暴露HTTP status，记录为 NOT_EXPOSED，没有捏造200。错误的 src/runtime/float.cpp 查询404保留在 [source-fetch-failure.json](source-fetch-failure.json)，随后通过实际目录定位 object.cpp。搜索引擎的两次GitHub限定检索无结果，只是弱检索证据，不是全网不存在证明。

## 精确 df5c 的实际 C

审查输入确为 248144 B 的 `df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172`。R13 run40092014611留存的未插桩 Submission.c 为1430091 B，SHA `31e1409237ccf2e66b3b107a1ff8b3a257c9faa4e2786749c624b6aac03ccbc2`。独立逐字节核对了该run保存的输入；未把外层8eb carrier的汇编冒充DF。

| 函数 | 原C行 | 实际接口及边界 |
|---|---:|---|
| R2W01b.convert | 12570–12621 | `float(uint32_t)`；table fast path、of_bits fallback；本体无lean_apply、显式lean_alloc |
| Submission.add | 21261–21595 | `uint32_t(uint32_t,uint32_t)`；两个converter已展开；正常结果一次add、self-beq、to_bits；原字NaN选择及AddBackend cold回退仍在 |
| Submission.nativeMul | 21609–21936 | 同样unboxed接口；普通路径两次数值转换、两次table load及缩放mul、一次结果mul、self-beq及to_bits |
| Submission.mul | 21950–23623 | 同样unboxed接口；指数和选择LowScale；nativeMul已展开；本体无lean_apply、显式lean_alloc |

[code-excerpts](code-excerpts)保留四个精确函数，静态站点计数由 [audit-sources.py](audit-sources.py)产生。计数不等于动态次数；依赖callee内部可能分配，冷分支也未动态计时；未证明同一计时MainFull的最终机器码。独立的 `___boxed` 适配器确实存在，但存在不是被选中调用的证据。现有add/mul已是inline，继续加inline不会提供新机制。

固定运行时的具体约束：

- lean.h:3253–3257中of_bits/to_bits只有外部声明，add/mul是static inline C算术；beq在3260也是inline。
- object.cpp:1987–1993中的of_bits是bit_cast后NaN规范化；2000–2004的to_bits遇NaN返回0x7fc00000。不能当作任意raw payload往返，也不能称为未知重型软件解码。
- tableIndex为u>>>23，范围0–511。lean.h:2092的UInt32→Nat经1496的小整数分支；335的box是tagged值；1011的fget_borrowed直接取指针；675的lean_dec对scalar不递减引用。这里没有“每次索引必分配一个Nat”的证据。表中已有Float32对象被unbox，不能写成每次查表都新建浮点盒。
- 最终to_bits是否尾调用、跨调用spill、Clang是否消掉具体边界，须看精确选中计时二进制。现有本体足以反驳“仅凭函数名存在就要修装箱/动态调用”的投入依据。

上述不少事实R14已经记录，本报告是当前源码与另一份精确DF证据的复核，不作为新发明或新增性能成果。

## 可复用的证明接口与最小证伪

DF的低成本合法decoder替换接口已有：
```lean
R2W01c.convert_eq (u : UInt32) :
  R2W01b.convert u = Float32.ofBits u
```
新decoder若有全输入同型等式，可依现有 `Submission.add_spec` (3118)、`nativeMul_spec` (3139)的两个rewrite接入，保留result nonNaN guard、原字cold路径；之后由 `mul_spec` (3159)连接LowScale。不能省NaN payload、Inf、±0、subnormal，也不能用native roundtrip替代任意raw roundtrip。sum/bmm继续保持原顺序和初始+0。

这只是已存在的集成接口：没有不同实现成本，不能因为证明容易就重新运行同一decoder。M16完整PASS但BMM约慢0.6%；R9直接decoder完整PASS但BMM慢17.3%、whole慢4.0%；R13一次性prep转换whole1.003435/BMM1.005952；R14纯整数ADD慢56.2%、MUL慢29.1%均保持负结果。

当前取舍：

1. **公开冠军包：PARK。** 有具体新公开作者仓库/commit或官方source路由才重开；榜单刷新不替代源码。
2. **USize表索引、泛化inline、去boxed包装：不建候选。** 首个证伪已发现小整数/borrowed读取及直接scalar入口；没有动态瓶颈证据。
3. **最新FloatLib窄乘法回移：不建候选。** 被检查的运行体无实质差异，且主分支工具链已4.35；新增ModelBridge不关闭native narrowing。
4. **真正新decoder/表示：仅在有不同实际成本机制时重开。** 首个有效检查应先绑定精确Kernel与其statement/MainFull生成C、实际所选caller/ELF，查减少了什么；随后完整原gate与25轮D，whole<=.97/p05>0后冻结并作两次独立确认。没有新caller差异就不把同路线换seed当新候选。

本报告未取得更快完整包，也未证明这些优化方向永远无效。它排除的是本次核查范围内把相同公开源码、已内联入口、小整数索引或旧decoder负结果重新包装成低成本机会。

