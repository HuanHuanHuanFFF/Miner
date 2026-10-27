# 4e36：仅修真实emit_size错误；同一完整两行运行体

UTC11:11:39冻结。`Kernel.lean` **237212B/4e36c931825b4c152933208987f066c95a5a0aada79cdea67202a045a7953ba4**。原v1/5bbf保留，19根审计文本仍 **e23696a1d248072f60bfa737892ccc3035aaa27407771bab2408c46f66a2091a**。

- 亲读CI40492989029/a9a4053f完整输出，唯一源码error L6777:2：emit_size里apply foldl_inv留下Array/size metavars，未与RowStream.emit目标统一；原log SHA7c0fc2948865d878ee8ecd5d3d0e717501e7af757bee575672de2f1046ed5762。无整模块/19根通过或C声称。
- 唯一+121B证明修改：显式unfold RowStream.emit，再exact foldl_inv，β、acc/j类型、初始out全部给定。149个非证明声明一致，正逆patch可逐字恢复5bbf；算法、mapIdx、guard、finish、输出顺序均不变。
- manifest已按D schema绑定：helper_audit_source_sha256是本Kernel4e36；helper_audit_text_file_sha256是e236文本；explicit_helper_audit为19根list，工具固定development-helper-audit-v8.py/5b58eece…。原文本intake/policy/options PASS，**新Lean/重放/公理/C/性能NOT_RUN**。
- 完整caller为streamedPair/controlPair及streamedRows/controlRows，初始化、每k整列map、两遍原finish/raw replay、state析构和输出均在内。actual C需按上级C-ACCEPTANCE.md查真实链；CtorReuse/closure0/noCOW都未证实。
- D已承接候选等待单槽；本方不派CI、不抢原public fullD。共同截止11:35:38，冻结后后继研究完全隔离，不改此源。
