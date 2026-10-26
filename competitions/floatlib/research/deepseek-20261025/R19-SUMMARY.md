# R19 DeepSeek 六小时总结（2026-10-26T19:47Z—2026-10-27T01:47Z）

分支 `huan/dhs-deepseek`；保留候选 B2 `622d8394`（未改动）。
所有计时均为 public-v2 嵌套入口（official `4b7e8384`、25 轮、500k pairs），每候选独立 full gate；
A/B 在同 run 内对 B2 anchor 归一，p05 用本地独立 bootstrap（2000、Random(90423)、25 抽中位数、linear p05）。

## 一、实验与结论

| # | 机制 | 候选/回执 | 关键数字 | 结论 |
|---|---|---|---|---|
| 1 | B2 分派放宽到 m≥2/m≥1/全部 | 40390827505 | bmm 1.152/1.186/1.181 | 负；保留 m≥4 |
| 2 | 逐行闭包改一阶循环（3 变体） | 40395050251；C 见 40394386767 | bmm 0.998/1.001/0.983 | 负；生成的 C 已无 alloc_closure |
| 3 | mul 去掉低尺度软件分支（常数 128→0） | 发现 40397668271；确认 40400995011 | EPYC whole 0.9691/mul 0.9228；Xeon whole 0.9940/mul 0.9854 | 确认失败，REJECTED |
| 3b | 同 seed CPU 对照 | 40410071271、40412279339 | seed 1826011 EPYC 0.9544；seed 1826012 EPYC 0.9784 vs Xeon 0.9940 | CPU 关联有 seed 对照；仍不达标 |
| 4 | convert→`Float32.ofBits`（add+mul） | 40405652739 | add 1.160、mul 1.135、whole 1.121 | 强负；表解码保留 |
| 5 | `NativeFinal.dot` 内联 | 40403277972 | bmm 0.9947 | 负 |
| 6 | `Packed10.finish` 内联 | 40408096257 | bmm 1.0008 | 负 |
| 7 | peer temporal-b2 复制复刻 | 40414394748（0.9991，噪声大）、40416378615（干净，bmm 0.9671） | 方向正、幅度随 seed 缩小；整包 <1% | 部分复现，形状依赖 |

## 二、mul th0：本轮最接近的发现

- EPYC 7763（seed 1826011）：whole 0.96905、mul 0.9228、p05 +0.0212（单组过 0.97）。
- EPYC 9V74（同 seed）：whole 0.9544、mul 0.8837、p05 +0.0450。
- Xeon 8573C（seed 1826012）：whole 0.9940、mul 0.9854、p05 −0.0204 → 确认失败。
- EPYC 9V74（同 seed 1826012）：whole 0.9784、mul 0.9400、p05 −0.0301 → 仍不达标。
- 机制：删掉 `if ex+ey<128 then LowScale.mul else nativeMul` 后，优化器 DCE 掉 `expField` 与整条软件路径；
  AMD 对 denormal 处理便宜，Intel 的 `mul:subnormal` 慢 23%。
- 判断：CPU 相关、整包收益 1.6—4.6% 且不稳定，**不采用、不组合**；若将来确认官方硬件为 EPYC，可重新评估。

## 三、可迁移教训

1. **C 证据必须先确认命中的是 selected body**：旧 `RowOutput_row` 的闭包不在 B2 实际调用链上；
   其后生成的 C（`rowLoop`/`emitLoop`）确实无 closure，但计时无收益 → 闭包不是 B2 瓶颈。
2. **Xeon 单 run 的未改动标量可漂 ±10%**（add 1.116、sum 0.95 同源）；1—2% 的结论必须多组。
3. **表解码 `R2W01b.convert` 已优于 `Float32.ofBits`**（add +16%、mul +13.5%）；
   bitcast 不是免费替代，与早期 R2 结论一致。
4. **CPU 型号影响 denormal 路径**：以后任何去掉软件 denormal 分支的候选，必须记录 runner CPU 并做同 seed 对照。
5. BMM 的 per-row/per-output 调用与闭包消除空间已很小；剩余大头上限在结构/索引与 mul（CPU 相关）。

## 四、回执与文件

- 原始 CI：`ci-runs/40390827505`、`40394386767`、`40395050251`、`40397668271`、`40400995011`、
  `40410071271`、`40412279339`、`40405652739`、`40403277972`、`40408096257`、`40414394748`、`40416378615`。
- 逐题记录：`R19-b2-relax-negative.md`、`R19-loop-negative.md`、`R19-mul-native.md`、
  `R19-conversion-inline-negatives.md`、`R19-peer-replication.md`。
- 构建脚本：`build-b2-relax.py`、`make-loopdc1.py`、`make-loopb2row.py`、`make-loopboth.py`、
  `build-mul-thresholds.py`、`make-bits-addmul.py`、`make-inline-dot.py`、`make-inline-finish.py`、
  `make-peercheck.py`、`compute-p05.py`、`show-public-classes.py`。

## 五、保留状态

- 保留候选不变：B2 `622d8394`（226829 B，3 组采用证据）。
- 本轮无新采用；无正式提交；无组合。
- th0 与其它负结果源码保留在分支，供以后有 CPU 证据时复查。

> 口径说明（2026-10-26T23:32Z 更正）：本文中若标注 raw 的 op 比值仅作诊断；采用口径为归一化 (sub/inc)_cand ÷ (sub/inc)_B2。归一化值见 R19-SUMMARY.md 的更正表与 messages/20261026T233200000Z-r19-normalized-correction.md。
