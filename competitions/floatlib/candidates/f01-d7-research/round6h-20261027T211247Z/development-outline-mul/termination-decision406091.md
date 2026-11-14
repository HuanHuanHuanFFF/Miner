# 88cdf的SIGTERM：等两块原样资源探针，不盲改整包

`review_termination406091.py` 重核61原件并复放确切症状：failure-only实际VerifyFull exit=-15／28.7s，保存的build-output只有一字节换行、无Lean报错；原gate约30.7s、exhausted=false。原INFO log没记第一遍的具体子进程code，父会话另报告-15，二者区分保存。不是一次已经定位到typed goal的数学失败。

原gate BUILD_TIMEOUT=1800、entry默认600；本次字节绑定的原adapter实际设置entry900，另有4GiB／swap0／Tasks256。timeout路径是124＋SIGKILL，exhausted只识别timeout／SIGKILL／disk／SIGXFSZ，**不识别SIGTERM**，所以exhausted=false不能排除子进程OOM后scope的stop。observer capture记录timed_out=false、0 statement events／0 snapshot attempts、gate exit1、errors空；failure-only不带observer仍同症状，observer不是必要条件。旧2177已有物理4GiB OOM，只约束那个精确旧源／运行，不能回填这次88cdf的未测memory因果。

新full源无bv_decide/native_decide。已核原样NatPostClosure cbdb2/4877B与NoWrapOnly8d49/1821B身份，两者逻辑独立，root在相同原4GiB g.own/read下分别观测，不因第一块失败跳过另一块，除非base失败／预算不足。这里不重复监控实现，也不改proof或造第3整包。

| 结果 | 最快下一步 |
|---|---|
| NatPost PASS，NoWrap OOM/终止 | 保留Nat商数证明；只替换biased_sum_nat内1338B无回卷块，先同一单根模块验证。 |
| NatPost OOM，NoWrap PASS | 保留word no-wrap；旧quotient-only已有完成记录，不重写它。先把NatPost去掉normalized_quotient后的原样前缀单独判别，再只处理PostBias闭包。 |
| 两者PASS | 小公共块可分别完成，整包／2177仍未闭合；查其余word/shape声明或单模块累积context，不能把分模块成功加成整包成功。 |
| 两者OOM/终止 | 保存两个独立症状，不能锁成单一数学cause；看scope／ancestor事件与base空import控制后分别缩小。 |
| 终止且scope无OOM、远低于4GiB | 查scope结果／父进程生存／Tasks事件／信号来源；不先修改数学或提高资源。 |

## 若NoWrap块失败：精确的低求解成本替代

原定理的域和等式不变。令pn=p.toNat，bn=bias.toNat，rn=parity.toNat；证明中应先得到 **pn<=281474943156225，bn<=8388607，rn<=1**，再显式组合：

`pn + bn <= 281474951544832 < 18446744073709551616`

`pn + bn + rn <= 281474951544833 < 18446744073709551616`。

用Nat.add_le_add、Nat.le_trans／lt_of_le_of_lt及闭合Nat常数比较产生两个小界，**作为具名引理参数**传给Nat.mod_eq_of_lt，再rw UInt64.toNat_add；不要让omega在带UInt64 shift／and／模／pow和整个局部context时重新发现这些界。parity界可直接由hparity及Nat.mod_lt／Nat.le_of_lt_succ获得；hone可由hb.1与固定常数传递获得，ht64可对ht两字面值分别闭合。这样可以消掉该块的五处omega，保留原shift-toNat／and-to-mod两个库接口与原假设；未运行，不能先称修复。

若该替代仍失败且telemetry指向同一块，下一最小探针是**原样两个闭合UInt64 half常数／bounds**，区分rcases+decide的word归约与Nat no-wrap推导。若它们有问题，改用UInt64.toNat_shiftLeft的投影式与纯Nat常量归约，避免闭合word表达式的整体decide；具体API必须据固定源／真实goal确认，不凭猜测修改。

## 若NatPost失败

优先隔离normalized_quotient，避免重做已完成的quotient_bias。以B=biased p，将hp两支分别切成B<2^47和B>=2^47。小分支有B<2^47+2^23；大分支有2^47<=B<2^48。显式用Nat.div_eq_of_lt／div_eq_of_lt_le给出B/2^47、B/2^23和B/2^24的必要值／界，再处理q=2^24的carry分支，避免在同时含多个变量shift／pow／division的omega context中搜整条结论。只替换实际失败段，不重命名或改runtime，不把纸面等式当Lean成功。
