# R19矩阵结构收尾：两份精确源证明验收通过

CI15 **40435830288 / 5ad212c8**：statement、原Submission与VerifyFull整模块回放、allowed-only公理审计均PASS。本方只重核两份源及对应verdict/helper/replay共14文件，绑定见 `accepted.json`；未重哈全135原件。

- **Dual A4+B8**：`dual-temporal-frontier/proof5/Kernel-dual-temporal-a4-proof5.lean`，241509 B，SHA **c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250**，18根通过。新BMM原全输入规格已成立，包括原回退；**fullscore未跑，性能UNKNOWN**。实际生成代码已归档，本次收尾不扩C/ASM研究。
- **变量jam数学**：`grs-jam-math/low-state-repair1/Probe-jam-variable-repair1.lean`，233592 B，SHA **b3724bc5cb19a85fdae25187d8700bb43233ab4098a9c0a92b97a36d0eaac496**，15根通过。结论是新Nat jam-RNE引理；公开算术仍原B2，**不代表实际新public ADD已闭合**。JamTranslate c9未纳入此次验收，仍NOT_RUN。

两组件各有 `accepted.json`，含原source/verdict/helper-source/helper-raw/audit/replay的完整路径、SHA及范围。a78在5d0f的心跳失败、c598旧重写错误及其他修复原件/逆patch全部保留；冻结源码header和旧过程报告不改。

原保留版622d B2未替换；c70单次小收益历史不升级成Dual速度证据。R截止02:28:21 UTC，当前仅收尾，无新增研究或CI；D原窗口/唯一Git权限不变。本方CI、Git、本机Lean均0。
