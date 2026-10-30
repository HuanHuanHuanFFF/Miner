# 优先使用 v2：源36 smallK 分发差异

UTC17:29:12，冻结v1/6751ff4b完全未改；新增v2 **7b6e0cba /252828B**，recipe`build_gemm36_pairlinear_v2.py` SHA8a59c56f，依赖原recipe80c7bbdd。

源证据改变选择：Mixer token GEMM 的 k=T，typical8..16/boundary9..17；source36原Ya3M已覆盖全部正k。v1沿用donor27的k<20分发，虽保留精确原Ya3回退，却丢失了这些smallK上的prepared路径，不应称完整保留优化。v2只将此literal20→1，所有finite非空k进入YaVM/MD2双行；原证明仅用k>0，仍需精确新all12gate。无本次native反馈/选择输入用于修改。

Root若batch2尚未派发，请优先v2；若v1已启动则不取消，作为独立历史诊断收齐。全部gate/速度UNKNOWN，不改已冻结v1。README/HANDOFF的早期smallK保留指语义回退，现明确优化范围差异。READY已指v2，旧v1全元数据保留previous_candidate_v1。
