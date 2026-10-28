# R22 A：broad-word 最小数学准备

本小步 **23:30:40—23:45:40 UTC**，共同截止 **03:12:47 UTC** 不变；A实际首工具21:17:47。D唯一Git/CI，C拥有冻结5655/0274运行体与模型，本方未改。

- [MinimalRounding.lean.inc](MinimalRounding.lean.inc)：**24efa3a7 / 2956 B / 3根 / NOT_RUN**。固定Nat bias3、UInt32 n<2^28的bias无wrap及RSE接线、d>=25的Nat远距舍入吸收。没有Model.add/publicADD完整声明、候选或CI。
- [接口映射](INTERFACE-MAP.md)：b372已验jam及偶阈值helper直接复用；未定位SameSignGRS/T0已验精确根。旧private quotient只有014acd完整typecheck；旧公开bias限t23/24与UInt64，不能继承为新k3/UInt32。
- [manifest/有限反例](manifest.json)：4608固定bias输入、120 far边界均零差异；bias2/4变异被抓，d24 tie与域外32bit回卷反例保留。**第二carry必须保留**：T=2^27−4、e127由加法pack得0x40000000，错误OR-mask得0x3f800000；e254对应Inf。不是Float32/Lean全证明。

下一步由完整成本决定，当前停在三个小稿与映射；guard、jam/normalized范围、signed normal Model.add和公共运输仍缺。旧UInt64/带cast GRS负结果与当时UNKNOWN不改。先前Pair8/77a资产仍冻结在[原目录](../streaming-public/HANDOFF.md)。
