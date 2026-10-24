# general Panel4 的局部尾行准备与证明接线

状态：**ASSET_READY / NEW_LEAN_NOT_RUN；PARK 本轮全m实际入口替换**。没有生成第二Kernel，也没有修改Astra主稿、旧9a/eb9或既有writer资产。这里只交可供后续statement验证的证明/实现资产；不能把它当成00:46前已能完成的整包。恢复实际入口投入至少还须927同对象机器码判别、下面tail最小statement、Panel4具体投影和新入口接线全部通过。主wide不等待此路线。

资产为 `review-output-panel4-tail.lean`，**9276 B，SHA256 1afa76878e5f09cd1e1f5d2ce20795aca9a2755a83d05b845fc059bfeda112f3**，12个声明。静态原版policy、namespace/唯一声明及运行定义无global map检查PASS；新Lean、内核、公理、checksum、实际入口、fullgate与性能均未验证。没有新的数值近似或浮点重排。

## 可以闭合的最小接口

每batch令 `first=4*(m/4)`、`rows=m-first=m%4≤3`、`rawBase=(b*m+first)*n`。prepare仅构造长度rows*n的Array Float32，q位置为原 `toFloat32(Araw.getD(rawBase+q) posZero)`。完整四行块继续使用每块一次的F4 panel；尾数组在本batch全部尾行/列组之前只准备一次，不重建全局nativeA。

三个基址必须保持区别：

| 用途 | 地址 |
|---|---|
| 尾部准备起点 | `(b*m+first)*n` |
| local tail numeric dot | `rTail*n` |
| 原raw A的finish/NaN replay | `(b*m+first+rTail)*n` |
| 原raw B的finish/NaN replay | `b*n*p+j` |

`prepare_read`对r:Fin rows、k:Fin n直接证明：

```lean
tailA.getD (r.val*n+k.val) zero32 =
  (Araw.map toFloat32).getD (rawBase+r.val*n+k.val) zero32
```

它来自Array.ofFn合法索引、Nat.succ_mul跨度界和既有Packed10.nativeA_getD。全局map是证明中的参照，不是prepare/group/row/tail运行函数的参数或数据准备。原raw读取越界时两边都精确用+0默认，因而没有隐藏raw数组范围前提。

`dot10_shift`对任意k和任意10个Float32累加器，按原k顺序归纳：只要实际读取的A值相等，localBase和rawBase两个Packed10.dot10完全相等。每步仍是原mul后add，不转换为实数或近似模型。`runDot_shift`先用既有runDot_eq，把机器与Nat两分支统一到这个定理；`runDot_prepared`用prepare_read关闭实际局部数组实例。它不要求人为假设局部/原始浮点读取相等。

尾组运行helper每g只调用一次 `Packed10Index.runDot n (rTail*n) tailA packedB[b][g]`，立即将有效lane连续emit；finish却使用原始raw A/B基址。`group_prefix`依次用runDot_prepared、point_row、packB_lane、finish_dot10_lane连接原RowStream.point；随后row_prefix复用列组foldl_inv，tail_prefix复用尾行foldl_inv。没有逐输出重算F10，也没有缓存整尾部的所有F10结果。

prepare/group/row/tail的可执行定义没有 `.map`。全域命题仍覆盖n=0、p=0、空tail、first≤m和任意Nat；m=0时没有Fin尾行，正性只从实际有效r/g得到。first=4*(m/4)自动满足first≤m。runDot_eq保留巨大Nat/不满足机器界时的原Nat回退。NaN/Inf/subnormal/±0由实际读取等价和原finish/dot桥继承；尤其不得把local r*n传给原字NaN回放。

## 完整Panel4还缺的接线

这份tail桥没有解决Panel4自身的四行循环投影。应新增F4的row选择与Panel4.wordLoop_row，使F40的projectRow等于原Packed10.dot10；可以在证明内用Array.ofFn投影出一条F4行，再接本dot10_shift。该行Array只能出现在证明，不应在运行中把F4重新拆成四个Float32数组。Panel4.packA_get可给出实际逐k字段，最后闭到当前Projects中的global-map参照；这个参照仍只是Prop。

具体buildTiles应在列组Vector.ofFn外let绑定Panel4.packA，内部对每g调用Panel4.runDot。新实际入口在原UnderflowZero最外守卫的miss内，至少证明n<USize.size再调用Panel4机器count；巨大n、空/短n及不满足形状的路径走原parent bmm。不能为省global map删掉巨大Nat回退。

generic writeBatch删除nativeA数据参数，将旧emitTail替换为本tail；output只let绑定原global packedB，buildTiles捕获原raw A而非A.map。保持Projects/emitRow/emitBlock的既有语义和连续结果Array。这样完整块转换4*n、尾部转换rows*n，总转换原字数仍是m*n；减少的是表示/生存范围，不是把ofBits工作移出计时。B fullpack、raw A/B、全部准备和析构仍在原调用内。

局部tail仍可能构造最多3*n个Float32对象，packA仍有每k四次转换、F4构造和回调；Panel4块的实际共享/释放、尾loop的machine guard成本均未知。若同时保留旧global nativeA map再加panel/tail，会重复准备，不满足本路线。

## 28b精确依赖替代与容量账本

本节只绑定 `f01-r11-wide4-inline-proof3/Kernel.lean`：253315 B，SHA28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b。所有删除都是未来新source中的条件计划，本次没有实施。逐声明边界取完整命令代码，保留相邻注释/许可与namespace对，不按别的版本行号套用。

| 未来动作 | 28b原代码B | 条件 |
|---|---:|---|
| 替换旧R11WideRows4机器家族 | 10105 | 新Panel4.wordLoop_row/run与所有caller已改完 |
| 删除R11WideLayout.nativeA_span | 570 | 没有旧global-A机器入口再引用 |
| 替换旧rowIndex/emitTail/emitTail_prefix | 2031 | 新局部tail及writeBatch已接线 |
| 重写writeBatch/writeBatch_prefix/output/output_prefix | 3848 | 这些不是无条件可删容量，必须放回新正文 |
| 重写R11WideActual.buildTiles及其projects/output/prefix | 1480 | 具体Panel4与新generic接口的完整实例 |

旧机器家族完整清单是 **R11WideRows4**下的wordLoop、baseAt、row_bound、wordLoop_row、lane_of_row_eq、joinRows、within、within_row、run、run_row。不得误删同名的**Packed10Index** loop/within/runDot或它们的证明，它们仍是尾部及父本fallback的真实依赖。

保留：F40、R11WideRows4.projectRow/lane40/lane40_eq；R11WideLayout的Tiles、groupFor/laneFor/columnFor、Projects及行投影提升、finish_lane_eq_point、emitRow/emitRow_prefix、emitBlock/emitBlock_prefix；原Packed10/Packed10Index/NativeFinal/NaN replay、global packB与全套fallback、Direct/fused/Underflow和四spec。保留所有来源/许可注释。**只需接新局部tail，不应再盲加整份13.6KB旧writer。**

Panel4探针中不含重复F40 header的Panel4 namespace正文为4676 B，SHAbdeb74007629566ed5949e387778d3b45ba6a58940e3aa770f5db02d7da0ec2b。按前三项旧段替换、加入这4676 B和本9276 B资产，纯容量算术为254561 B，余1439 B，**还没有**新增F4投影/具体wiring，而且旧flow尚未重写，不能当成可编译候选。

若将后两项旧flow正文也先列为待替换，临时容量账本为249233 B，余6767 B给**全部**新F4投影和放回的新flow/实例，不是额外净收益。28b原件还有1538 B不与注释重叠的普通空白行；未来删段可能与这部分重叠，不能把1538直接加两遍。实际新正文尚UNKNOWN，最终必须新候选重新核完整词元、notice、namespace、四spec、精确逆向及256000 B上限。

关键旧段精确范围示例（均半开字节，未来必须同时复核28b整源SHA）：wordLoop[216038,219198)，SHA7ccbcf384ded65e6ee806d539a54082a64ee490b989d0d473cd0a8a8f4ae8209；wordLoop_row[220553,222552)，SHAbfacc778d9695469ac17c493b3701beb3751b92c10f59ea07ef465eb6b9c1eed；within[224446,225589)，SHAe4400c9a24c85203c971aa3028d8c53e982f7331fc188c2fd8846e75f0ea0f77；within_row[225590,227403)，SHA002890dffb56296c7c3daceb0d8ec3dec9920d79c0c43131efd1ed801eeefdac。

## 冻结判断与边界

已有接口没有暴露数学上的阻断：局部读取桥、任意累加器的shift归纳、原字finish与尾前缀都有完整无占位草稿。未闭合的是**实际Lean接受**、新的F4循环投影/Projects实例、具体flow替换、源码裁剪依赖闭包及同场完整成本；还不能承诺在当前00:46源码目标前完成这整个新算法闭环。因此本轮实际generalPanel入口标 **PARK_PENDING_PROOF_CODEGEN_AND_CAPACITY**，保留资产，不生成第二Kernel，不阻塞主wide。

本地624个尾地址计划、3024个抽象地址读取检查通过，覆盖m%4所有尾数及空n；仅是索引诊断，不代替Lean或浮点执行。没有读取未来确认输入、派发CI或修改既有源。后续若Root重新选择此路线，应先最小statement验本asset与Panel4投影，再让实际新entry接受完整gate；unused probe的fullPASS不验收这一算法。
