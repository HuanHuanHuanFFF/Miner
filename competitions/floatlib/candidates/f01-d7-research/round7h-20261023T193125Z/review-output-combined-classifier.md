# 0655 组合的终点分类迁移

**READY_FOR_STATEMENT**。唯一落盘源 `f01-d11-bmm-combined-classifier/Kernel.lean`：SHA256 `6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d`，254654 B，余1346 B。父本严格为0655 `0655b26612f7359c100b2c7e091e3d2f4c53fcde5e8286d25f3c41cbdc75f06e`，254588 B。

独立build.py先用6457与7317各自的精确三段逆变换账本从a066重建donor并逐字节核对，再把6457的相同三段迁入0655：NativeFinal.dot和Packed10.finish改用已有self-BEq守卫，dot_eq通过nonNaN_eq_true_iff转换前提。没有修改公开add/mul/sum/bmm及四份spec的类型或证明正文，没有改Cross→DirectContinuous/fused分派、underflow最外层、packing、原字NaN回放或许可段。新完整逆变换恢复0655全部字节。没有接官方add回退。

6457的917/run40034884263原statement回执已读，summary SHA5353b65fe9e8acb1c216aa59b1aa618603e273e03bb52495774351a749e02661，精确6457 statement_pass=true；这不验收6c2d。新组合的Lean语句、leanchecker、axiom审核、checksum、fullgate、生成代码均**NOT_RUN**，性能UNKNOWN_NOT_ADDITIVE。

可选`classifier+fallback`只做dry run：预计239141 B，余16859 B，SHA256 `f8dca27517ed79927ab928af1b96ac25facffdff8b29efcbeccc48312fda9d03`。它在6c2d之后改官方add回退/证明并删精确TunedAdd块，四份spec的命题保持，add_spec证明仅改变回退分支。完整六步逆变换同样恢复0655；许可、声明删除库存和原policy检查PASS。完整账本存于review-output-combined-classifier-fallback-dryrun.json，**没有写第二份Kernel**，CLI明确拒绝该recipe的--write，等待919真实结果与Root决定。

默认执行为dry run；`--write`仅允许首次生成本目录classifier，拒绝覆盖；`--verify`重建并核对冻结源。已核唯一范围/hash、donor精确复现、两种recipe完整逆向、namespace/export库存、四spec、原policy、许可和资源选项。覆盖写入与fallback写入拒绝测试均PASS，现有文件hash不变。未调用或改写冻结compose299a、0655/918文件、Git或CI。后续由Root先statement再原完整gate。
