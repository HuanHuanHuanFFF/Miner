# Run 8 计划：p≤16 阈值检查

## 背景

终选 `p2contp8` 已 5 次测量全正（whole 0.891–0.991）。剩余问题是阈值 8 是否最优：
public-v2 每 seed 里 p=9..16 的 case 占 BMM 计分工作量约 4—8%。

## Run 8

- seed `1525004`（新 draw），3 候选：df5c、`p2contp8`（p≤8）、`p2contp16`（p≤16）。
- `p2contp16` = 同 `p2contp8`，只把 DirectContinuous 守卫从 `p ≤ 8` 改为 `p ≤ 16`；
  仍旁路 p=2 Cross；p>16 保留 Packed10。
- 目的：若 p9–16 直算不劣，可把阈值上移；若更差，锁定 p≤8。
- 预计 18—20 分钟，1 个在途。

## 判定

- 以 p2contp16 / p2contp8 的同 run 比值为准；差异 < 0.5% 视为噪声，保留更保守的 p≤8。
- 任何改动仍需新 seed 复核；采用建议仍以 p2contp8 为默认。
