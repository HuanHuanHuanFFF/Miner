# 后续冷miss：先保留接口，不抢当前公共证明队列

旧R14 `astra-math-route-notes-20261025.md` 已给出normal乘法S<=102必signed zero、S>=382必signed Inf；103／381不在域内。R19 `astra-workers/root-underflow/` 又有9bbc3a0c／230046B全raw保守S<=84提前零草稿及三根接口，仍NOT_RUN，只复用既有UnderflowZero.scale<=84证书。它们不是新数学或新覆盖，不把旧输入频数当时间收益；旧e139输入本身为零的已验范围也不扩大。

现在唯一新条件是406073精确outlined caller已真删热frame，同时保证miss的case测得12–16%损失。按当前已见1/3四块，若仅把这些case恢复到控制成本，能回收约0.35–0.58% whole；即把这些**整个pass**变成零时间，宽松上界也只有约3.25–4.18% whole，且包含不能消掉的循环／boxed／checksum成本。精确ns和边界在next-cold-miss-budget.json。这个上界只覆盖可由case参数保证all-miss的3–4项，不限制mixed constructor cases或隐藏套件。

因此当前优先88cdf公共source的原验证与完整D，不因miss损失自动开新网格或新大证明。若后续有低边际成本slot，最小不同实验可以在**noinline冷层**复用S<=84证书直接signed zero，其他仍尾跳原B2；不把额外guard塞到已冻结正常热臂。需先证明真实Main接受路径仍原45条且新冷层不继承B2 frame，再同binary保留outlined对照、全部guard miss与完整Suite成本。若需要携带已算出的sum进入三参数冷helper，须单独审ABI／寄存器成本；它与captured Bool无关，不能仅看arity数拒绝普通未捕获函数。

当前没有构造该后继候选、没有新CI、没有声称额外收益或完成全域证明。重访条件是当前公共验证不被拖延、真实冷函数能比旧LowScale减少可测工作，并且新Math／source-cap成本相对收益合理。R14/R19原未验状态和历史负结果保留。
