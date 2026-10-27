# R7 检查点29：D直接布局+单遍sum组合的只读接口核对

2026-10-23 02:36 UTC。按D协调请求只读核对3d9与97f共同父本0e8的接口，没有写D目录或新R候选。

`direct-singlepass-interface-audit.json`确认：0e8末尾BMM段在3d9中逐字节原样存在且唯一；97f的替换段与DirectSmall后缀无sum/sum_spec依赖，命名空间均自带显式open。NativeFinal.dot/dot_eq、add_eq/mul_eq、index_address和referenceBmm接口均沿用共同父本。原3d9完整追加sum块逐字节保持，最终导出sum仍指R7SinglePassSum.run；导出bmm只有一个。

以内存中精确替换该BMM段计算，预期232363bytes/SHA256 `cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc`，实际D新`f01-d7-direct-singlepass/Kernel.lean`恰好逐字节相等。逆替换恢复精确3d9。**没有识别到源码接口冲突，仅静态/身份核对；新Lean/fullgate/C/性能仍NOT_RUN。** 此组合与“353d旧decode hook被3d9绕过”的问题不同，不把后者误套到DirectSmall。

R7原7份ready源码无变化。D拥有cc06及其后续验证；R在02:45按计划记录本角色源码冻结并更新原包索引，04:22:17结束窗口。0新运行CI，公开push仍待原授权问题回复。
