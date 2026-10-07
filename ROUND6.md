# ROUND6 — H16-small 核心与CPU优化

本轮按用户要求优先优化H16-small，基线为已通过公共完整gate的r5-h16-small-proofopt。仓库即时核对仍为私有，沿用用户已授权的标准GitHub Actions；不进行正式竞赛提交或钱包操作。

## 首轮候选与入口

- cpu-screen：环形最小值更新链inline、缓存查询重放inline；只改变指定函数属性，Lean正文保持原样，但新配对仍需完整gate。
- core-screen：复用真实比较得到的H3前缀；跳过不可观察的备用t5表构建。两份证明明确NOT_ADAPTED，先提取/有限等价/公共性能。
- 原版h16-base与同字节h16-shadow都在每批中；同时保留probe3、public432、fast3/#453、public299四个校准控制。
- 每批两个公共计时块，均为28文件、每文件11次测量和一次预热，配对官方incumbent并检查determinism/round trip。另做444输入token/decode等价检查，以及H16基线下同进程顺逆序诊断。后者单独标为辅助证据。
- 保存已有编译.so的size/nm/objdump文本用于分析调用与布局，不修改计时器/编码器/官方参数，不保存工具链或二进制。

首轮参考榜单25924保存于evidence/round6/frontier-start。公共改进、完整Lean gate、正式admission和奖励分别记录。保持压缩输出并稳定提速是首选；没有收益/输出回退/成本超过收益的候选停止，不做盲目预算扫参。

## 执行

分支codex/deflate-round6，工作流deflate-round6.yml仅明确手动批次执行；push只登记工作流且跳过实验，避免重复旧H16 gate。官方source/pins/corpus/toolchain与900秒证明限时保持不变。

收集：python scripts/collect-round4.py pull RUN_ID PHASE --round 6 --batch BATCH。首轮不执行新候选完整gate；有实测收益再做独立复测及证明验证。已有基线与全部失败证据保留。

## 首轮已测结论

cpu-screen37594267200和core-screen37594271466均已完成。四份候选各444个有限输入对照零差异，公共28文件两块的token/输出也与h16-base一致；本轮未为这四份执行新完整Lean gate。

| 候选 | 两块配对总时间变化 | 同进程正序 / 逆序 | 决定 |
| --- | ---: | ---: | --- |
| rm-inline | -0.278% | -0.010% / +0.086% | 停止：26个候选函数机器码与原版相同 |
| replay-inline | -0.328% | -0.008% / +0.031% | 停止：同上，微小差异不能认作优化 |
| h3prefix | +1.194% | +1.266% / +1.273% | 停止：输出相同但计时回退 |
| lazy-t5 | +0.502% | +0.232% / +0.373% | 停止：输出相同但计时回退 |

26个完整候选函数共88199字节的机器指令均落在保存区间且相同；完整nm文本也相同。保存的整个.so汇编有截断，不能据此宣称整个库字节完全相同；原版与shadow完整库SHA相同，两个属性版本库SHA不同的具体原因仍未建立。

唯一追加方向copyfast来自机器码证据：一处完整plan复制仍逐u32检查src/dst。新候选只改变h_copy32，合法区间一次检查后普通索引连续复制，非法区间保留原wrapping/get/set循环字节；证明NOT_ADAPTED。已启动37598783885，提取通过，性能及新完整gate仍待验证。详情见cpu-notes、copy-proof-plan及各原始回执。
