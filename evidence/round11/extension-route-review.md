# R11 延长窗口：独立质量路线评审

范围：只读方法文档、R8／R9／R10失败证据和冻结 pipeline／官方 encoder／旧 H16 源码；仅写本文件。未写候选、未运行原生 Rust／Lean、未启动 CI、未提交或访问 withheld 源码。延长后的截止时间为 2026-10-08 15:14:07；本评审不扩大后续执行授权。

**建议保留一个有明确差异、可快速证伪的方向：把 D 后向的每块 Huffman 码长模型与官方 package-merge 对齐。先读取实际直方图差分；若没有有效符号码长差异，就直接否决，不为零机会移植证明。** 这不是已经有效的优化。现有证据不足以承诺它补足固定时间下约0.008275 pp的条件大小缺口。

## 先排除不值得在本窗口重复的方向

| 旧路线 | 已有证据 | 对本次选择的限制 |
|---|---|---|
| R8 已保留候选的距离成本重选 | 约598.9万长度段只有0.615%可换较便宜距离；full/top/suffix 公共均多10字节 | 不再对已有距离后缀加缓存或扫选择规则 |
| R9 整份 q9 候选缓存 | 有新增长度，但构建自身约为整个旧 parser 的3.608倍 | 不移植全位置 finder，也不把新匹配数量当压缩收益 |
| R10 greedy／lazy／cost seed | 搜索流保持，统计规划仍损失大小；加 pass 更慢 | 不换另一长度种子、不加规划遍数 |
| R10 压链、压记录、RMQ；R11 groups | 内存／逻辑读写减少没有稳定总轴收益；groups均值又有块间变号和 incumbent 分母移动 | 不由缓存大小或指令数推断速度，更不能当私有集保证 |
| R10 endprobe 与更早 overlay | E-2只省319字节／0.0017765 pp；更早普通节点会丢原 gap 边，补 owner 后仍涉及动态 push 边 | 不能只把查询位置往前移；完整 overlay 改图和证明超出本轮低成本优先级 |

固定 pipeline 大小时仍需约5%速度，远高于已经得到的可靠新增信号；固定时间下的条件大小缺口更小。因此优先寻找能改变 token 选择的模型错误，而不是继续 CPU 小改。

## 来源中存在的具体差异

冻结父 `candidates/r10-finder-pipeline-proof/parse.rs`：

- `d_tally`（约1910行）按第一遍 plan 的16384-token块收集真实 `lf/df`，每块 EOB 为1。
- `d_push_table`（约1857行）对 literal/length 与 distance 分别调用 `d_huff`，随后通过原 `d_sym_costs`、原 `ck` 构建一次后向 DP 的价格。
- `d_huff`（1716行）先做普通 Huffman 树，把深度截到1..15，再依频率排序顺序延长稀有码，直到 Kraft 和可用。它并非官方的最优限长分配算法。
- 官方未改 `sources/conjectures-optimisation-deflate/validator/measure/src/deflate.rs:90` 使用15位 package-merge，按 `(frequency,symbol)` 稳定排序，并在同重量时先取 leaf。最终 encoder 还会做动态头和 fixed/stored 选择；仅对齐码长并不等于优化了完整编码成本。

因此，一份最小候选可以只替换 `d_push_table` 使用的码长生成器，保留原 `d_parse` 搜索／第一遍 plan、rs、块起点、passes=1、cost kind、backward 图和 checked emit。这会改变现有后向选择的价格，不需增加查找、候选流、二次 parse 或新节点。

它不重复 R7 `huff8k`：后者在原 **前向 DP** 把熵价格切成普通 Huffman，并改变 rebuild 间隔；本项不触碰该前向阶段。它也不重复 R5 exact-cost selection：R5 用完整成本比较已有 parse 结果，随后因边界漂移／收益不足停止；它没有把精确 package-merge 码长送进本 D 的一次后向 DP。R8则只在给定旧价格下换距离，未修订价格生成。

## 可以复用的实现与证明，不需要照搬官方动态包列表

`candidates/r5-h16-small-proofopt` 的已验收包为 Rust `d9826bc92ba02f49cb6e552ed172a4fb82dc10fa8fb51aacf73e7947ed38a94d`、Lean `d55744de52bb0469768f0bbfd73ffecbabf9899b63e0167469fd7bb79c6293c7`，其 VERIFICATION 绑定 run37584216832。该历史完整 gate 不自动覆盖新组合。

本次只读调用闭包核对：从 `h_pkg_merge_pm` 出发共 **23个函数、7061 UTF-8字节**，与 R5 exact-cost候选中对应函数逐字相同。固定数组包括288个排序项、288个leaf weight、1152个双缓冲weight、9216字节flags和288个计数。该表示没有官方 `Vec<Pkg{syms:Vec<_>}>` 的逐包分配；包括 radix／insertion稳定排序、leaf-before-package tie、逐层 flags 和逆向计数。

原 H16 Lean 已有这些函数及循环的总性证明，例如 `h_sort_live`、`h_pm_levels`、`h_count_back`、`h_pkg_merge_pm` 在约4615–4746行。D 的 `d_huff_spec` 与 `d_push_table_spec` 本来只承诺规划函数总性；最终义务仍由 unchanged checked emitter 负责。最低迁移是所需 H helper/证明依赖子集、一个 fixed-array 转换 wrapper，以及 `d_push_table_spec` 两处调用绑定。无需证明 package-merge 最优性才能关闭原 LZ77 obligation，但“确与官方码长一致”须另有实际差分检查，不能拿 totality 替代。

移植成本为中等：需保留 #361 与所借 H16／#402 来源归属，处理 slice/array mutable-back 接口、排序和层数循环的实际提取签名。父 Lean 约407KB，不能粗暴拼入整个 H16 证明；只取必要闭包并检查524288字节上限。精确新 Rust／Lean 必须重新提取并过原 obligation、公理白名单和公共 roundtrip。旧 helper gate 只降低迁移不确定性，不是新 pair 接受证书。

## 已做的低成本否证与尚缺的关键数据

本次执行了两个**只读 Python 源模型**比较：D普通树＋修补模型与 R5 flags/backtracking package-merge模型。长度2..7、每项频数1..4的 **21,840** 个小分布，码长向量全部相同。另用固定种子111211，对30和286符号各100个零／稀疏／偏斜频数组合进行比较；200例中25例码长向量不同，24例加权位成本不同。随机频数来自 `[0,0,1,1,2,3,8,20,100,500,1000]`，总和未限制为一个真实 encoder 块，因此不是公共直方图收益或可行总输入的证明。没有执行相应 Rust，也没有保存新候选。

这个结果削弱了“只换 tie 就能普遍改进”的假设：小分布看不到差异，机会可能集中在过长树及修补区。不能由存在25个模型差异推断当前130个公共 D 块也不同。

已有 R11 observer 的实际130次公共 d_load epoch中，最大literal价格分布为 `{144:1,160:1,176:2,192:3,195:1,208:6,224:11,232:1,240:104}`。其中240经常也可能是“未出现符号=最长码+1，再截15”的价格，而非真实活跃符号发生了15位限长修补；CSV还可能是混合成本。故该统计**不能证明**有104个值得修正的限长表，也不能代替真实频数／码长对照。

真正缺的是 `d_push_table` 上游每个实际 `lf/df` 的旧／新码长差分：活跃符号、unseen价格、是否原始深度超15、weighted bits、变化块及文件分布。只读插桩还须保持 frozen token／decode相同，并让任何新增计算不进入性能计时。

## 最小实验与窗口控制

优先只有一份候选，配合一个观察诊断；不做码长上限、cost-kind、passes或阈值扫参。

1. **首次机会检查。** 在 baseline 的真实 `d_push_table` 处，对130个公共块及已有固定生成输入的实际频数比较原 `d_huff`、固定数组 PM、临时官方参考 package-merge。记录逐符号码长和 weighted bits；公共完整 parser保持原样，诊断只读。若可与下一批编译／计时准备同时完成，避免为一个计数单独耗尽 runner setup。
2. **唯一原型。** 仅把上述两处 D 码长调用换成 PM wrapper。保留 max-length／unseen返回约定和原 cost kind；零／单符号行为明确对齐。同步 native decode、实际提取、与 pipeline 的公共 paired总压缩时间及真实大小。token允许改变，不宣称大小单调。
3. **确认／gate。** 只有实测新两轴在当前完整快照下形成足够条件余量，才迁移剩余证明并独立复测。若首轮不足，直接关闭；不因完整PM理论最优就加第二pass。官方树对固定histogram最优，并不表示由旧plan构造的新价格一定改善最终plan、块边界和动态头。

如首次差分说明只有少数实际发生过长树的块受影响，最多可在**独立证据支持后**比较一份“保留原法，只有原树需限长时调用PM”的成本对照；不得未经证明／差分验证就假定该 shortcut 与完整 PM 同码长。这是可选第二变体，不是本次已经推荐执行的扫参。若实际表完全相同，则0份候选，停止本方向。

在约75分钟内得到首次公共测量的条件是：复用上述已有Rust闭包和现有原生／paired runner，不写全新 encoder，不做全输入额外扫描，不先展开整份 Lean。预计实现与本地源码审计可在15分钟级完成；实际 setup／提取／测量墙钟由 runner 决定，不能保证75分钟内完整 gate。主线程应先保留独立复测／最终归档时间；若PM引入的依赖迁移压缩了这部分时间，宁可仅交差分结论而不称可提交。

**停止条件明确：** 活跃符号码长和 unseen 价格无差异；差异只影响未被选择的路径且公共大小不降；总时间代价使新点仍被支配；任何native decode／官方提取失败且剩余时间不支持修复与确认。固定输入、模型较小表、同族校准都不提供私有保证；本文件没有产生正式成绩、admission或支付结论。

备选的“同长度但向后延伸更远的额外候选”虽然也未被R8覆盖，但会撞到 rs 的递增长度／d_top owner／动态push处理，需要额外格式或回推路径；R10 overlay反例已经说明简单追加不保留原图。相较有23函数可复用的PM表模型，该路线在剩余窗口内证明与图语义成本更高，本次不建议实现。

## 后续授权的最小实际诊断已准备，未执行

主线程随后单独授权了 `scripts/research-round11-huffman.py`，尚未授权／生成新候选。脚本 SHA `fe56d4de0e977c58a668efb73317b3c0573ef0d01cf0b52dfbd3ae4a16dc326b`。它只需临时 GitHub Linux runner 的固定 Rust nightly 和公共语料，不要求安装 Lean。入口为 `--corpus <28文件目录> --output "$RUNNER_TEMP/round4-receipts/huffman-diagnostics"`；也支持 `--official-source`、`--corpus-manifest`、`--toolchain`。官方文件优先取 `DEFLATE_ROOT/validator/measure/src/deflate.rs`，默认输入 SHA 基准为 probe-a 的 pipeline 原始 JSONL，逐文件名、bytes、SHA 必须完全相同，不能仅用总字节和文件数代替。

观察副本只将 `d_push_table` 的两次调用套记录 wrapper，并在原 `d_huff` 截深度前读取实际深度。wrapper 仍返回原码长和原最大值；诊断输出不会进入候选规划。exact PM 直接抽取临时 runner 原官方函数到独立 std-only 模块，附只读 wrapper；原官方文件不变。报告保存官方整源和函数 SHA、冻结／观察 Rust SHA、harness SHA、run_id/git_sha、每输入 SHA，以及每张真实 lf/df、旧／PM码长、原最大深度、活跃符号差异、weighted bits、纯unseen差异。冻结／观察各跑28公共输入，要求 tokens逐字相同并独立decode。

本地仅通过 Python self-check、精确注入反转与语法检查。预期观察源 SHA `b351aa491447a157ebde3c9dc44c6b6e9a58d6793267dba3508fb70f56d031e3`；本地官方整源 SHA `4d0e99c02586925420eed57470866d808917ddd2adaa00703f630520869fbc7a`、抽取 PM 函数 SHA `974664691910f142a5e69d0526da7ab69591296213a424f380338a7daa31991a`。编译180秒、运行300秒上限，编译／运行失败与超时保留日志和失败状态；**native compile/run均UNKNOWN，尚无真实频表差分结论**。
