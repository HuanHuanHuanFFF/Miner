# 单一 preferred 空间成本源：ce1a8c2b / 255987B

响应父1854/1911，已先恢复真实Lean参数空白，再做唯一守卫修订：允许单项零权重，只拒绝BW.min=511的整行全零。19:16只读检查现有plan未发现8e5/f59/5a43/spatial11冻结条目；所有旧文件仍原样保留，不同版本不要并排队。

`build_spatial_mixed_zero.py` 的variant为 **spatial11-mixed-native**。源SHA `ce1a8c2b1eda3a9282e8c5ea21a70b18aebd04e65926690d282641e60b72e99c`；recipe/dependency完整哈希在 spatial-mixed-native-receipt.json。需要同目录 parser-repair与compact、以及所列history内的原owned generator。入口 **Submission.rV**，候选只importContractExact，**declares_correct=false/full_gate=false**，没有新Submission.correct。

相对5a43只删除逐项weights.all非零扫描，并在既有每输出guard增加`(BW[o]! >>>16) !=511`。原有限/narrow/size、cin≤8、偶数3×3、B0−2偏置上下文及shift≤76条件均保留；全零行和其它失败域走原完整Ybp。变换/word累计/cache/CHW/零符号回放没有改变，旧11全部runtime/proof仍保留。

新域通过同一既有Python表达式/字模型检查，并补真实mixed-zero局部−0与全零行/Inf拒绝例，见 spatial-mixed-model-receipt.json。这是同一证据家族，**不算第二次独立验证，也不是Lean/native**。源code主要成本风险仍是每coordinate循环、Nat getElem!和partial数组；实际速度未知。剩余13B，完整proof恢复字节未知。

D独占是否CI和排期；若没有成本预算，完整模型源码、证明接口、反例与模型留作后续，不为此另开独立CI或挤占达标源确认。
