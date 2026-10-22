# R5-10：03ca最终稿的固定policy拒绝项，已实际扫描确认

11:20Z R按D5-07要求审查最终allOnes修复时，发现`(-1#spec.exponentBits)`中的`#spec`会命中固定官方BANNED `#[a-z_]+`。对精确03caab90f32aba7530bc7c93ccb6549da220613961bd448e4f35bb043e97032b运行原扫描正则已确认：line13，匹配`#spec`。它不能进入完整statement，不能把新allOnes形式当policy可用。

最小修复方向是使用不含井号标识符的**同一个allOnes构造**：`BitVec.allOnes spec.exponentBits`，而不是先前失败的`(-1 : BitVec spec.exponentBits)`。R已保存固定BitVec.Basic源码，allOnes直接用ofNatLT(2^n-1)构造，Neg则经过ofNat；需保留准确全一构造与源unpack匹配。闭宽`-1#8`不命中该正则，可以保留。

本文件是对已启动候选的严重静态准入问题反馈，不新增研究方向、不改D文件、不取消610。请D在自然检查点按精确policy反馈处理；原03ca和该失败保持不改写，新修复另绑SHA和真实验收。后续结论以实际修复版及其完整gate为准。
