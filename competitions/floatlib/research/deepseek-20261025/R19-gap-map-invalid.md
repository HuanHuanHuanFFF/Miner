# R19 分析：跨 suite 逐类 gap 映射不可用（2026-10-26T23:57Z）

## 做法

用冠军 #323 的私有 suite 逐类 `submission_ns/incumbent_ns` 除以 B2 在 public-v2 的逐类比值，
假设两 suite 的参照“同族”，估 `champ/B2 ≈ r_champ/r_b2`，再乘 B2 类耗时排序。

## 结果：假设明显不成立

- 得到 sum 类 est 8.9—110×、bmm 7—20×，与团队按组均值的估计（sum 1.17、bmm 3.00）差一个量级。
- 根因：public-v2 的 incumbent 是慢速参考（B2 的 sum 比值 0.06—0.11、bmm 0.05—0.14），
  私有 suite 的 incumbent 是优化参考（冠军比值 0.56—1.01）；两参照不同族，逐类比值不可跨 suite 相除。
- 只有 mul 的 est（1.39—1.73）与组均值 1.16 同量级，属巧合可用；其余不可用。

## 结论

- **不要**用跨 suite 逐类比值做目标排序；只能用同 suite 的相对变化或组均值粗估。
- 本文件保留为方法负结果，gap-map.py 仅作诊断脚本，不进入任何采用/排序。
- 下一轮若要精确定位，需要同一 suite 上的逐类对照，或官方私有 suite 的原始数据（UNKNOWN）。
