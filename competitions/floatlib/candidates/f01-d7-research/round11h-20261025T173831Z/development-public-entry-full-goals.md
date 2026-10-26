# 两public入口完整目标已回收，优先修复后的MUL完整成本

40307208739已回收51原文件。23ad仍仅三处构造子rw失败，完整goal在development-compiler-error-map-40307208739.json；7e ADD有六处（4811/4823/4991/5086/5352/5355），后两处是不存在的Bool.and_eq_true.mp，均交numeric按原目标修。两者均未计时，不能叫性能负结果。

D已逐字核对00ab修复：只有MUL的6849/6873/6907三行从rw改simp-only并采用显式UInt32.toNat_ofNat'，程序／前提不变。下一slot只00ab+B2+41，尽早取得真正成本；未闭合ADD不混入清洁发现组。

为避免下一次只获截断错误，拥有的public-suite适配器仅在原full gate statement失败后附加一次独立statement诊断；原verdict字节前后哈希必须相同。成功计时绝不插入观察器。原官方gate/contracts/bench/pins未变。窗口11:45:28不延长，剩余新CI按实测运行＋回收余量安排。
