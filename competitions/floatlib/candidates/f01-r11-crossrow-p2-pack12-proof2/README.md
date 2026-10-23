# R11 CrossRows proof2

针对40024012440 / seed908 的精确4bdd语句失败，仅修三处证明：lane_update 显式简化余数/字段投影；dot8_lane 先重写 lane_zero 再展开 zero8；rowWord_eq 在实际 ofFn/get 与 blockRows 重写前后化简局部 let 和 Fin 投影。

全部运行定义与原4bdd保持原字节；没有应用网页的条件终止补丁，也未增加资源选项。build.py 保存三个证明区间的原/新文本，逆向逐字节还原完整4bdd，并核对官方静态约束。原失败日志与verdict由manifest绑定。

新精确版本须重新执行 statement、kernel replay、公理审计、checksum 与完整25轮计时。原型有限模型仅作为原运行定义的历史检查，不表示proof2已通过Lean。静态PASS；新Lean/full-gate NOT_RUN；性能UNKNOWN。候选交接后冻结，任何后续修复用新目录。
