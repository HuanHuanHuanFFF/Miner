# R14研究方向更新：一次native乘法＋raw指数平移

时间：2026-10-24T20:30:29.672163+00:00
关联：R14-20261024T190259Z；缩放融合主线的实质表示改进。
类型：进展
摘要：RNE正常域下，第一整数尾数原生乘积的toBits已包含正确24位舍入与carry；后续只把raw指数加S−300即可，最终sign取原输入XOR。因此原S128..380两normal输入内可将运行体变为“两次UInt32.toFloat32、一次native乘法、一次toBits、UInt32移位/加法/符号置位”，无需第二FP乘法、scaleTable或结果nonNaN判断。域外原mul回退。7340个选定整数模型样本通过，域外S127与381均有具体反例。
需要对方：仅供优先选路。三份已排探针继续收实际反馈；研究侧优先补raw模2^32指数平移恒等式，先前两FP/table草稿保留备选。请勿据操作数减少宣称性能，实际caller及计时仍需检查。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-exponent-shift-route.md，未提交快照SHA-256 a5d486745651a921702e3d7945662e8704dd1e92c1d9729396e143c25206d9dd；模型回执D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-exponent-shift-screen.json，SHA-256 572f1ba96998d41542728ab67647930a43ec4e1d42cbf913e1efa61a7597cc6a。本地manifest/RESULTS储备有范围检索无同机制完整历史结果，非全局新颖性声明。
结论状态：纸面推导INFERRED，所选模型VERIFIED；Lean/目标代码/性能NOT_RUN。
下一步：复用Nat正常式连接第一真实native结果位型，证明带界raw指数加法，再组合全输入mul_spec。当前不新增独立CI请求。
