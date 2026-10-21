# Extension90m 评分层独立复核（gate 状态另行判断）

- 官方快照：`29973`；捕获目录 `evidence/round26/extension90m/official-final`。
- 标准 run：11；原协议配对进程：132。
- 原始 JSONL 哈希：True；评分坐标/份额重算误差最大值：X `0`，Y `0` pp，份额 `4.44e-16` pp。
- 唯一 Rust 哈希数：6；同版本副本始终单列控制，不并入候选主版本样本。

| 机制 | Rust SHA-256 | 样本身份 | run角色 | 校准 | 视图数 | 零份额 | 中位份额 (%) | 正份额范围 (%) |
|---|---|---|---|---|---:|---:|---:|---:|
| C2 | `305f6089dc6f…` | candidate_main | discovery | primary | 1 | 0 | 0.714174 | 0.714174–0.714174 |
| C2 | `305f6089dc6f…` | candidate_main | discovery | shadow | 1 | 1 | 0.000000 | — |
| C2 | `305f6089dc6f…` | candidate_main | independent_confirmation | primary | 4 | 1 | 0.722806 | 0.665445–0.862346 |
| C2 | `305f6089dc6f…` | candidate_main | independent_confirmation | shadow | 4 | 1 | 0.626929 | 0.591307–0.973760 |
| C2 | `305f6089dc6f…` | same_binary_copy_control | discovery | primary | 2 | 2 | 0.000000 | — |
| C2 | `305f6089dc6f…` | same_binary_copy_control | discovery | shadow | 2 | 2 | 0.000000 | — |
| C2 | `305f6089dc6f…` | same_binary_copy_control | incidental_control_in_confirmation_batch | primary | 4 | 3 | 0.000000 | 0.979656–0.979656 |
| C2 | `305f6089dc6f…` | same_binary_copy_control | incidental_control_in_confirmation_batch | shadow | 4 | 3 | 0.000000 | 1.093280–1.093280 |
| C3 | `58324f244b6d…` | candidate_main | discovery | primary | 1 | 0 | 0.760308 | 0.760308–0.760308 |
| C3 | `58324f244b6d…` | candidate_main | discovery | shadow | 1 | 1 | 0.000000 | — |
| C3 | `58324f244b6d…` | candidate_main | independent_confirmation | primary | 4 | 2 | 0.293485 | 0.586970–0.723256 |
| C3 | `58324f244b6d…` | candidate_main | independent_confirmation | shadow | 4 | 1 | 0.649900 | 0.606877–0.782228 |
| C3 | `58324f244b6d…` | same_binary_copy_control | discovery | primary | 1 | 0 | 0.910306 | 0.910306–0.910306 |
| C3 | `58324f244b6d…` | same_binary_copy_control | discovery | shadow | 1 | 1 | 0.000000 | — |
| C3 | `58324f244b6d…` | same_binary_copy_control | incidental_control_in_confirmation_batch | primary | 4 | 2 | 0.411084 | 0.822167–1.177958 |
| C3 | `58324f244b6d…` | same_binary_copy_control | incidental_control_in_confirmation_batch | shadow | 4 | 2 | 0.615177 | 1.230353–1.295192 |
| D1 | `f6c7f97f9fb2…` | candidate_main | discovery | primary | 1 | 1 | 0.000000 | — |
| D1 | `f6c7f97f9fb2…` | candidate_main | discovery | shadow | 1 | 1 | 0.000000 | — |
| D1 | `f6c7f97f9fb2…` | same_binary_copy_control | discovery | primary | 2 | 2 | 0.000000 | — |
| D1 | `f6c7f97f9fb2…` | same_binary_copy_control | discovery | shadow | 2 | 2 | 0.000000 | — |
| D2 | `3f866acdc2f1…` | candidate_main | discovery | primary | 1 | 1 | 0.000000 | — |
| D2 | `3f866acdc2f1…` | candidate_main | discovery | shadow | 1 | 1 | 0.000000 | — |
| D2 | `3f866acdc2f1…` | same_binary_copy_control | discovery | primary | 1 | 1 | 0.000000 | — |
| D2 | `3f866acdc2f1…` | same_binary_copy_control | discovery | shadow | 1 | 1 | 0.000000 | — |
| E1 | `bc1b3fec788a…` | candidate_main | discovery | primary | 1 | 0 | 1.101498 | 1.101498–1.101498 |
| E1 | `bc1b3fec788a…` | candidate_main | discovery | shadow | 1 | 0 | 1.115200 | 1.115200–1.115200 |
| E1 | `bc1b3fec788a…` | candidate_main | independent_confirmation | primary | 4 | 3 | 0.000000 | 0.837346–0.837346 |
| E1 | `bc1b3fec788a…` | candidate_main | independent_confirmation | shadow | 4 | 2 | 0.343342 | 0.686684–1.402246 |
| E1 | `bc1b3fec788a…` | same_binary_copy_control | discovery | primary | 2 | 1 | 0.331071 | 0.662143–0.662143 |
| E1 | `bc1b3fec788a…` | same_binary_copy_control | discovery | shadow | 2 | 1 | 0.337422 | 0.674843–0.674843 |
| E1 | `bc1b3fec788a…` | same_binary_copy_control | incidental_control_in_confirmation_batch | primary | 4 | 1 | 0.741212 | 0.649796–1.111466 |
| E1 | `bc1b3fec788a…` | same_binary_copy_control | incidental_control_in_confirmation_batch | shadow | 4 | 1 | 0.739836 | 0.718842–1.196802 |
| E2 | `586dec576a20…` | candidate_main | discovery | primary | 1 | 0 | 0.738067 | 0.738067–0.738067 |
| E2 | `586dec576a20…` | candidate_main | discovery | shadow | 1 | 0 | 0.765269 | 0.765269–0.765269 |
| E2 | `586dec576a20…` | candidate_main | independent_confirmation | primary | 4 | 2 | 0.496953 | 0.993905–1.236124 |
| E2 | `586dec576a20…` | candidate_main | independent_confirmation | shadow | 4 | 3 | 0.000000 | 0.671875–0.671875 |
| E2 | `586dec576a20…` | same_binary_copy_control | discovery | primary | 1 | 1 | 0.000000 | — |
| E2 | `586dec576a20…` | same_binary_copy_control | discovery | shadow | 1 | 1 | 0.000000 | — |
| E2 | `586dec576a20…` | same_binary_copy_control | incidental_control_in_confirmation_batch | primary | 4 | 2 | 0.303436 | 0.606873–0.854600 |
| E2 | `586dec576a20…` | same_binary_copy_control | incidental_control_in_confirmation_batch | shadow | 4 | 4 | 0.000000 | — |

## 评分器来源字节核对

当前 close rules scorer `486f9b425ef6fc0bfae2fdc9eb2f342de9c40efcae3b41bf14ced18128b571dd`；`analyze-round26.py` 指向的 scorer `486f9b425ef6fc0bfae2fdc9eb2f342de9c40efcae3b41bf14ced18128b571dd`；字节一致：`True`。旧脚本未修改。

完整逐流程 X/Y、候选与同 binary copy 的投影坐标、raw receipt 哈希、官方 scorer replay 见同名机器 JSON。所有份额均为该官方快照下的几何单点投影；gate/proof 状态不由本评分审计推断。
