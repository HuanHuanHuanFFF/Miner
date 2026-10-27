# R14：MUL/组合是SIGTERM无诊断；补一个纯证明工程备选

时间：2026-10-25T01:55Z。已读40151550349的原始verdict/replay.log，不根据空reason猜数学错误。

- ADD2/f958的statement真实通过，full replay/axiom/performance尚未运行。
- MUL4/2c7194：`lake build VerifyFull exit=-15 in21.9s`；combined2/27cc：同命令exit=-15 in22.5s；full-build-output都是单个LF（SHA01ba4719...），没有Lean错误文本。不能写成“编译通过但缺结果”，也不能诊断成反例。
- 固定gate.run源码的TimeoutExpired返回124，killed()只识别SIGKILL(-9/137)，所以-15不被标exhausted且reason空。当前**终止原因UNKNOWN**；须看实际runner/资源事件，不能直接改原gate/cap、怪用户取消或声称OOM已证实。

如果确认需要降低大模数证明成本，可用新备选 `astra-biased-rne4-quotient.lean`，3808B，SHA **f30f16a715db5773356781f4f5544d5cbb5afcbf64fd28596a898d50b86661c7**。仅替换fd3的Nat证明：先对任意half>0用q/r恒等式、符号小系数证明通用quotient_bias，再实例化half=2^22/2^23，避免让omega直接发现整个大模数周期恒等式。nat_bias原陈述、biased运行体、word_bias剩余suffix逐字相同；**未编译、未证明资源改善，不把fd3记成数学错误**。不改已通过ADD的小位移证明。

`astra-biased-rne4-quotient.json`保存内存预览：精确2c源单片替换后255265B、SHA6791b890...；精确27cc单替换后254680B、SHA3c2d53de...，均未创建候选，没有独立CI/推送。是否采用请按你真实资源诊断决定，不扩展第三种运行表示或队列。截止/冻结时间不变。
