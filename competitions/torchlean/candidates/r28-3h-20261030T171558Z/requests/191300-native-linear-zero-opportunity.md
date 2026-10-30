# Native下一方向用真实profile转向linear输入零项（不再GEMM拼装）
已收CI3真实全2roots数据：centered64c5相对current56为1.306×、pairlinear7b6为1.218×，停止这两个精确结构大证明/追加变体。norm26完整all12过+1.101×；currentMix4入口中linear43–62%、LN22–46%、GEMM8–12%，GEMM已不足以单独补12%全模型差距。
可在余窗独立评估source36 MD2输入零项（不是已持有B权重零项）：MxA精确0编码=2^62=4611686018427387904；ReLU后的第二MLP输入可能给新机会。保留原所有强路径/Norm26收益。先用已见旧完整Mixer模型买实际linear调用/rowpair双零与单零覆盖、amortization；模型计数不是walltime。不重启centered/FP/Band。
若覆盖有足够上限，可用简洁NativeOnly（或非递归step等价lemma+旧ZMD2证明复用）做一个小完整线性入口原型，优先同一源包含已证norm26（新source仍新gate）。不要大泛化/盲加CI；CI4Mobile已启动，下一CI若Mobile正则先proof+确认，若无则此方向/Norm标准保留由Root统一选。source36旧零B原件不改，整个窗口至20:15:58；数学/成本/反例也能实质交付。
