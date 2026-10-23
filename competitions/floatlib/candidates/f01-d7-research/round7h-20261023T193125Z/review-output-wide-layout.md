# wide4 实际输出与容量：给 Astra 的独立资产

状态：**DESIGN_WITH_TYPED_PROOF_DRAFT / NOT_RUN**。本输出设计项只写本报告和 `review-output-wide-layout.lean`；没有生成wide Kernel。后续另获Root授权落盘的无wide容量基座见文末。唯一probe仍是 `f01-r11-wide4-codegen-probe/Kernel.lean`，eb9e76393b13448bd031134035706d3b05ce08b018f7d81dd5614db0c9ac007f，241262 B，其实际入口完全没有调用wide4，不能从它推导新BMM性能。

## 建议的单一运行路径

外层形状条件为 `4 ≤ m ∧ 2 < p ∧ 4 < n`。机器循环再要求 `n < USize.size ∧ A.toArray.size < USize.size`；任一条件不满足就走原parent完整bmm。检查在新准备之前，避免miss还做一遍nativeA/packB。Astra可在该条件下给wordLoop构造四个跨度证明，无需另造40累加器Nat循环；这是明确的巨大Nat回退，不以机器字截断替代原Nat地址。

命中后，只做一次 `nativeA := A.toArray.map ...` 与 `packedB := Packed10.packB batch n p B`，二者覆盖原全batch并在调用内计费。按batch、完整四行块 `h : Fin (m/4)` 遍历，块首行 `first=4*h`。每个列组g恰好计算一次F40，输入四个A基址为 `(b*m+first+r)*n`，共用既有 `packedB[b][g] : Vector F10 n`。wordLoop保持40个scalar Float32累加参数与原mul后add顺序，初值全部+0。

当前块的终点结果保存为 `Vector F40 (Packed10.groups p)`，**先完成该向量，再写四行**。r=0..3外层、j=0..p-1内层，读取 `tiles[j/10]` 的column-major字段 `c(j%10)r`，以本行A基址与本列B基址调用原 `Packed10.finish`，依次push到同一最终Array。buildTiles在块内let绑定一次；不能把它换成每输出调用的F40计算函数。写完四行后，该临时结果向量不再进入下一块状态；实际引用计数和释放时机仍待真实caller C确认。

最后 `m-4*(m/4)=m%4` 行（0..3）通过现有 `RowStream.row`，继续用同一global nativeA/packedB、相同最终Array。只计算完整四行块，不计算跨到下一batch的虚拟行。最后列组继续用原F10零填充，只有j<p的lane会finish；无效lane即使因Inf×0得到NaN，也不得影响独立有效lane。每个有效输出仍用正确原始A/B字做NaN回放，±0/Inf/subnormal及payload语义交给原finish/dot桥。

## 可直接使用的 typed 接口

Lean资产当前13649 B，SHA256 **42a3547cd310297a2f79c636b8eb152547c8d4118f3bb66893b4762fd808bab1**，19个命名声明，全部未编译。它接在compact的RowStream和唯一probe之后，没有占位证明或新增全局前提。

`Projects`要求，对每g、r、l：

```lean
lane40 (tiles.get g) r l = Packed10.lane
  (Packed10Index.runDot n ((b.val*m+first+r.val)*n)
    globalNativeA ((globalPackedB.get b).get g)) l
```

这里global值在命题中展开成原map/packB，因此精确绑定原始A/B。若Astra先证明四个F10行投影，`Projects_of_row_projection`可直接把四份结果提升为上述40lane接口。Astra尚须提供：具体F40选择/行投影、wordLoop的四行投影、USize入口及buildTiles确实只运行一次的实现/连接；本资产没有把这些缺项伪装成已经成立。

后续完整草稿链为：`nativeA_span`给四条A跨度界；`finish_lane_eq_point`用runDot_eq、packB_lane与finish_dot10_lane连接实际结果和RowStream.point；`emitRow_prefix`复用emit_prefix；`emitBlock_prefix`用foldl_inv 4；`emitTail_prefix`复用原row_prefix；`writeBatch_prefix`用foldl_inv(m/4)再接尾部；`output_prefix`用外batch foldl_inv。最终Vector长度/参考等价可直接接现有 `prefix_vector_eq_ofFn` 和 `points_eq_reference`，再接原referenceBmm_spec。

输出、尾部和global准备已有实质typed草稿；未完成的数学主接口只剩Astra负责的Projects实例和入口机器界/wordLoop连接。这些都是**NOT_RUN**。通用资产中的lane40/buildTiles是函数参数，供证明复用；实际候选应使用具体命名实现或确认专化结果，不能假设源码写了Fin.foldl就消除了所有closure/callback。

O2剪枝会删除 `groups_pos_of_col` 与 `column_decomposition`。资产因此自带groupFor/laneFor/columnFor，未重新依赖O1–O5旧链；保留的依赖是Packed10.packB/packB_lane、finish/finish_dot10_lane、Packed10Index.runDot_eq、NativeFinal.dot以及RowStream真实Prefix/emit/row接口。

## 实际字节容量

probe相对a066的**完整后缀**为4120 B、SHA7f65025b4de83d3e2327b224adc6d59ab8054079379fc4560bb05b6c978bd859，包含probe标记与namespace；不误用另一个increment文件的hash。以下都只做内存拼接/唯一范围检查，没有写组合源。

| 起点和所需准备 | 加probe后B | 再加本13649 B资产 | 剩给Astra投影、机器wrapper和最终entry |
|---|---:|---:|---:|
| a066 + probe | 241262 | 不可直接计为可用组合：其RowStream只有旧core，缺Prefix/emit/row_prefix | 需先迁移typed基座 |
| 已验5b完整fused基座 + probe | 249961 | 263610 | 超7610 B |
| compact f2fa + probe | 240520 | 254169 | 1831 B |
| compact − S1–S5 − O1–O5 + probe | 232672 | 246321 | 9679 B |
| 上行再迁7317官方add回退 + probe | 217159 | 230808 | 25192 B |

不能把a066+probe+资产裸字节254911 B称作可用入口，因为它缺typed基座；表中5b是已经存在的完整基座迁移口径，不代表已经穷尽更小的辅助链。compact父本236400 B，SHAf2fa8d10872e1b341f2400db3ceb3c2a9e4f0f6e6d9cd9779469bc9286760553。按冻结headroom清单逐段hash和唯一范围实际删除S共5011 B、O共2837 B：内存结果228552 B、SHA29ce6cae4fb3b6fd517fee7ac7effcf853cda1b6410f66a8284c0deee402bbeb。再精确应用7317三步变换净减15513 B，内存结果213039 B、SHA700982043714854acb73632442b145ee718b218b6a27b27276348ef1565776cf。初稿测算时回退成本待919；随后Root通报isolated7317在919 fullPASS，呈现小幅混合成本变化，不作提速声明。删链、投影和入口的新组合仍需重新Lean/fullgate。

这些余量是精确容量，不是“最终必能装下”的保证。四行投影/机器wrapper实际新增字节尚UNKNOWN。优先评估S/O版本能否在9679 B内关闭；Root已基于919授权另建容量基座，但没有把回退认定为免费或最终采用。没有为了容量修改原许可或源码词元。

## R4 负例的准确对照

原R4 `7de60fa5`、`8c0c1954`已经有scalar累加参数、仅终点F8/F16构造，实际SIMD和B复用形成，热回边无call/FMA/rsp操作；完整调用却分别约慢9%/0.6%。因此不能把它们说成逐MAC boxed-vector失败，也不能宣称新40参数自动解决了旧负面。证据为原R4 checkpoint-03及checkpoint-04-final；后者SHA d1914ccb1eb3d8d0ae636ac012ed837ab57e2935cf9e5804fb9454d0739bede2。

可证伪差异在tile/output组织：旧R4先保存整个batch的嵌套结果Vector，再最终Vector.ofFn逐输出选择；这里仅保存当前四行块的F40组向量，按行连续push，缩短结果tile生存范围，并保持当前F10 B打包，不退回2×4更小B对象。新路径仍有全局nativeA的Float32对象、global F10 B对象、每组终点F40和每块tile引用数组。没有“整包零分配”或“已消除boxing”的声明；实际callback、RC、spill、终点构造和完整准备/释放成本都须检查真实入口C/汇编及原full gate。

本地仅验证来源hash/唯一裁剪、namespace库存、与原版policy兼容、无被删O链依赖，以及960个小形状/74520个抽象输出标签的遍历顺序和列号分解。它们不代替Lean、浮点执行或性能。未触碰任何f01-r11-*、冻结composer、既有候选、Git或CI；没有第二宽度Kernel。

## 后续另行授权的无wide容量基座

`f01-d11-bmm-combined-capacity/Kernel.lean`已按Root后续授权生成并冻结：239141 B，SHA **f8dca27517ed79927ab928af1b96ac25facffdff8b29efcbeccc48312fda9d03**，余16859 B。它保留Cross/Underflow/DirectContinuous/fused和6457分类，仅接7317官方add回退，没有wide。新wrapper SHA **d6b6c02602f784e55a0ab3144a8cd9f9277dae681f9274bf560dc14d94f2e1b1**，只调用并校验冻结6c2d构造器a13842131e051be7e84796a2fafe8978acb6c38f5aff1b84cb2d677f6f9476de的construct('classifier+fallback')；旧构造器/Kernel均未改动，也未裁剪空白。

其完整最外Underflow namespace在0655、6c2d、新基座均为同一1039 B，SHA **b135a8eef0606c7356dc12d5956115d3832aa5cddb5dc5e71e5030380c76062e**；静态回执含完整原文字节。**Wide必须插在bmmBeforeUnderflowZero中，或等价只替换最外零守卫的miss，不能让wide形状守卫先吞掉已证零矩阵路径。** exact-inverse.json的后三步恢复6c2d，origin-inverse.json全六步恢复0655；spec命题、notice及原policy重新检查PASS。该新基座的Lean/fullgate仍NOT_RUN，不继承919组件验收。

这个combined基座加现4120 B probe后只余12739 B，尚须装Astra具体投影和精简writer。不能把本13649 B通用资产全文盲复制进去：会先超910 B，且还未加投影。可按Root授权只裁普通空白、复用已有Prefix桥、精简不需要的通用层；最终容量与证明由Astra精确候选再验收。

## Root 最新容量决定：独立无Cross wide backbone

Root随后选择为真实wide主线单独保留underflow+direct+fused+classifier+official-fallback，暂不接Cross；旧f8dc保持冻结。唯一新 `f01-d11-bmm-wide-backbone/Kernel.lean` 已生成：**223584 B，SHA749bc933597ec15b200e8146899f7a055e25b4eef425e156bca337a13c38ca28，余32416 B**。新wrapper SHA **e24d4ea5d781d47452b893f7d172df0bd3fd91b5b14e064ff3466bb5ee0fb8c0**；只在内存调用冻结compose299a的underflow+direct，精确得到2fd068b1893ac6d24feb766ec86673dc025a056650f0cdc5bdaf6b64073ef605/239031 B，再应用6457/7317六段唯一补丁。

该base加当前4120 B probe后为227704 B；再完整加本13649 B通用资产为241353 B，**尚余14647 B**给Astra具体投影、USize wrapper和实际入口，未计任何假设的空白裁剪。最终实际新增与全gate仍待Astra候选，不将这个字节估算称为已完成wide。此决定只为容量和隔离机制，不声称移除Cross提速。

新base的六步逆变换恢复2fd，继续用冻结compose账本逆回compact f2fa；Cross声明0，除已选组合外只删40个TunedAdd声明。原四spec命题保持，add_spec仅回退证明替换，原其余公开spec正文不变。notice扫描没有减少原受保护注释；删除namespace后，保留的fastlog介绍与保留的FastMul来源段相邻，扫描器额外将该介绍归为保护段，这一分类新增已在回执显式记录，未改注释字节。

最外Underflow namespace仍是同一1039 B/b135a8ee…c76062e；**Wide仍只能接它的miss**。所有新Lean、内核、公理、checksum、完整gate和生成代码均NOT_RUN。旧compose、donor builder、f8dc、wide4 probe及其它原件未改，也没有Git/CI动作。
