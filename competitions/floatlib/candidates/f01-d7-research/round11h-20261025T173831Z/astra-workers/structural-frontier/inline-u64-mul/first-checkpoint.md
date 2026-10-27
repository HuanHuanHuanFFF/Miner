# 18:20 前接口判别

**CONTINUE 最小数值桥；尚不建议仅据模型直接排完整计时。** 固定 Float32→UInt64 是有模型定义的数值转换；UInt64.ofNatClamp 的真实无夹断引理已从固定源码核到。指数公式E=exu+exv−127+[R>=2^47]正确，原 normal 与S128..380域保持。

有限检查23192对、21982准入对，0差异：888个46→47进位、384偶平局、384奇平局；R覆盖2^46至281474943156224，E覆盖1至254。外部5秒timeout，实际约0.22秒。原v1没有命中平局，其脚本/回执保留；v2增加定向平局。均为整数/宿主模型，不是Lean、实际机器码或性能。

明确反例：u=0x20000001,v=0x207ffffe，N=2^47−2而R=2^47。按R判b得到0x01000000；误按N判b得到0x00800000。不能忽略舍入进位。

新机制实际减少的是c972准入路径里的非尾部external toBits边界。仍付2个前向cast、1MUL、1UInt64反向cast、0/2^64夹断比较、阈值/移位、guard和fallback；unsigned64可能另有2^63转换补偿，是否消除spill与净收益UNKNOWN。c972完整负成绩保持。

证据：first-discriminator.md、sources.json、numeric-model-v2.json。下一步是在c972已验数学接口之上写独立UInt64 decode→truncate→no-clamp桥和小运行片段，先不造大包。全部写入仍限本子目录，无CI/Git/本机Lean/未来holdout读取。
