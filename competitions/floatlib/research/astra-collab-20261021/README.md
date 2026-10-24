# FloatLib R：2026-10-21 协作研究

研究当前状态与待处理交接的唯一入口：[research-status.json](research-status.json)。总体开发、Git和CI状态由D维护：[development-status.json](../../coordination/development-status.json)。

[本轮收尾快照](closing-report.md)区分已收回完整结果与仍在运行的最终确认批次。

[后续网页6 Pro研究与文件交接](web-6pro-handoff.md)：用户新增的方法约定，下载原件保存在 `E:\Download` 下并随交接交给开发D。

共同窗口2026-10-21 10:32:09—11:32:09 UTC，11:15前转入冻结与确认。R只写本目录及f01-r1-*，不派CI、不提交／推送、不操作资金或正式参赛。准备与等待均计时。

## 直接采用入口

- [冻结源码复核](closing-source-review.md)：最终三个精确版本的guard、顺序、舍入边界；[回执审计](window-audit.json)分开完整gate与编译诊断。
- [R-07](checkpoint-07.md)：乘法最后的命名空间适配、native加法首个完整验收；D已冻结其等价修补。
- [R-06](checkpoint-06.md)：native乘法桥接修复、native sum累加器包；源码及SHA都在交接内。
- [R-05](checkpoint-05.md)：直接循环完整gate回执与归因修正；native位往返证明草稿。
- [R-03](checkpoint-03.md)：公开Lean4.34/FloatLib native加法逻辑模型路线及首包。
- [R-02](checkpoint-02.md)：零回退频率与反例；[模型结果](fallback-probe-result.json)、[其他反例](counterexamples.json)。
- [R-01](checkpoint-01.md)：最初循环与计时边界判别，后续以R-05收紧其适用范围。
- [R-04](checkpoint-04.md)：native乘法初稿与原生累加状态设计；初稿实际失败，修复见R-06。

## 来源与复现

sources/保存官方及上游源码，source/native-source/mul-source/newer-mul-source的responses和receipts绑定URL、版本、解码UTF-8字节及SHA。原始runner回执保留在D的ci-runs目录，研究审计只链接并重新核对，不改原件。

本地轻量脚本：fallback-probe.py重放有限路径频率；counterexample-probe.py复现反例；audit-direct-loop.py核对精确完整gate与父／子C；build-*.py仅生成研究包。所有Lean草稿必须以D实际完整gate为准，存在文件或模型通过不等于Lean验收。

## 公开代码归属

FloatLib代码与移植引理归FloatLib Team，MIT许可：[许可全文](sources/FloatLib-LICENSE.txt)，源文件头保留作者。R-06移植的三个引理来自较新公开commit `1f5771b3e36a98f17fcac2c6d76aaa024b36aa37`，只放入候选自身命名空间；官方pinned依赖保持原样。后续发布含这些引理的单文件包时，保留Copyright (c) 2026 FloatLib与MIT许可通知。

Lean标准库源码按各原文件头的Apache-2.0归属保留，作为原语与语义调查材料；未把其已有实现或定理冒称本次原创。
