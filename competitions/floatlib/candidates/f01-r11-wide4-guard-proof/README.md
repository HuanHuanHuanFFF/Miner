# 未接入口的边界证明探针

原28b819的253315 B全部作为原字节前缀，后接已有astra-wide-guard-proof.lean的2085 B；合计255400 B，余600 B。只新增R11WideGuardBridge命名空间的四个定理，没有新增运行定义，没有改变四入口、四spec、dispatcher、资源选项或原作者/许可说明。

四个定理分别给出完整四行块的实际A跨度、任意等尺寸nativeA的跨度、由raw尺寸界推出native尺寸界，以及真实A.map/packB下直接within的Projects实例。它们为下一轮消除每列组run重复边界检查提供接口；当前候选仍调用原run，不能把证明探针当作检查已经移除或算法已经提速。

build.py默认只读重构并验证，exact-inverse.json说明删除精确2085 B后逐字恢复28b819。初始静态PASS；新Lean/kernel/axioms/full全部NOT_RUN。只安排短statement验证，真实报错最多两次新目录的proof-only修复。e5b279与最终6c2d及全部cohort文件保持不变。
