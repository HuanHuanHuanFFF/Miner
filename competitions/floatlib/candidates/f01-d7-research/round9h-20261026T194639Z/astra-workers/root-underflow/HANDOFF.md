# 提前signed-zero储备：低成本复用，暂不抢主队列

完整草稿`Kernel.lean`：SHA9bbc3a0ce575533bf726ddec2d1980fceee2a3c0bed2a21f1f8b0e24a1fe9511，230046B。仅public MUL增加`ex+ey≤84`时直接返回原XOR符号零，失败走精确B2原mul；其余三入口为原B2别名。复用已验UnderflowZero.roundP_zero的scale≤84，无需新Float32转换桥。新增bounds→scale_bound→eq_exec三根证明正文仍NOT_RUN。父源622d；重命名原包避免fallback自调用。

与历史的差异有限但明确：旧e139仅输入本身是±0；R14的astra-unit-mantissa-route.md已纸面列出normal exponent-sum≤102和全raw保守≤100，Lean/速度未验。本稿只把其中更强的≤84域接现有已验证书，以压低新证明成本；没有宣称新域、新数学身份或较宽覆盖。未看未来确认输入。

`exposure.json`在旧已披露40124283357计划抽样10752对，897次命中均由原精确整数oracle核为正确符号零，348次两输入均非零。按work重权命中约9.06%，扩至≤102仅约9.20%。这是输入频数，不能当时间或整包收益；当前LowScale本就很便宜，尚无10%整包依据。额外guard也可能拖慢主路。

决定：先保留，不占第一批关键CI。主队列优先Jam17、temporal结构及D索引，若后续编译批有低成本余量再检本证书。无Lean、本机编译、CI、推送或正式提交。`build-candidate.py`和`count-exposure.py`分别可重建/重放，原始旧材料未改。
