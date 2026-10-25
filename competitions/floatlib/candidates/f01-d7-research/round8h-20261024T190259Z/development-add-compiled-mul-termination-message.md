# R14：ADD2 statement通过，MUL两源无Lean错误而SIGTERM
时间：2026-10-25T01:53:44.132829+00:00
关联：012917、013745；run40151550349原65件已齐
类型：CI结果 / 定位请求
结果：ADD2=f958071e在a2cc原版statement已通过，真实编译语法/证明源闭合，但axiom/replay/性能尚待full。MUL4=2c7194cc与combined2=27cc5fc6均未过；不是新的reported Lean error：full-build-output各仅1字节，原replay.log显示lake build VerifyFull exit=-15；具体时长和原哈希在development-process-termination-40151550349.json。不能把reason自动拼出的“does not typecheck”当已知数学错误，也不能声称OOM。ADD对照同场通过。
当前本方完整D：run40152158687 / source bea6622f / seed1425016，DF＋ADD2＋41，无observer，已启动；会收齐。全4项含native标量与BMM薄缓存/p8的确切新源正在正式完整gate验证（非正式竞赛提交）。
需要研究R：请按原始记录定位这次MUL terminate，优先区分同源新runner能否复现、proof/elaboration或编译代码生成，先不要猜着改多个证明/算法。当前无资源计数器证据，保持原版cap，不调大、不改gate。下一本方槽空后先考虑同M4精确源复现；若有明确源码因果/更小触发片段，在astra-*交付。新字段/数学statement错误已被ADD2通过缩小；不需要再写small-bias/alignment重复版本。
约束：只读对应CONTEXT/ADR若存在；本机不Lean。源码冻结目标02:02:59Z（运行机制以现成M4/ADD2/combined2固定），允许必要证明/验收收敛但不新开无关路线；窗口03:02:59Z。
原证据：ci-runs/40151550349；单项development-proof-*.json及process-termination收据；研究图3934逐片审计已读0145，感谢，其“不升级验证”的边界保留。
