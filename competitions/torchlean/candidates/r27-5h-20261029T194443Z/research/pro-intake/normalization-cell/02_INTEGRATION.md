# 接线与验收边界

`R28NativeCell.lean` 是独立研究草稿，不是可直接提交的Kernel；`R28CellLemmas.lean` 是未编译证明脚本。两者均只 import ContractExact，未新增axiom/unsafe/extern实现。

## 局部成本试验的唯一接入位置

保持MYbc的外层stable/legacy条件、Y8f、st/aux、YT循环与旧Ya7G全部存在。在原每元素lambda内已有 `s=st[r]!`、`u=aux[r]!`、`nU` 和原word索引时，新插入部分的形状是：

```lean
let candidate := R28NativeCell.attempt nU u.2.2 (!u.1) u.2.1
  s.2.2 x[r*n+j]! g[j]! b[j]!
if candidate == 0 then
  Ya7G n x[r*n+j]! g[j]! b[j]! s.1 s.2.1 s.2.2
    (fun _ => rowMean n x r) nU u.2.2 u.1 u.2.1
else candidate
```

这是本轮新增的接线建议，没有改动现有文件。若将独立源内联到单文件，保留原唯一import，去掉新增文件重复的import行；namespace保持R28NativeCell。实际`correct`不会自动闭合，不能拿成本版本当正式提交。

**符号陷阱：原u.1表示 `!(S1<0)`；新attempt的Ssign表示 `S1<0`，必须传 `!u.1`。** 新旧函数的两个参数不能同极性照抄。

nU沿用旧 `if n<4096 then n.toUInt64 else 0`；Sabs沿用旧60位guard和sentinel；b0来自同一行st。不要给n或Sabs直接做无guard截断。dw必须是同一Y8f输出，而不是native sqrt结果。w/g/b必须与旧Ya7G索引一致。

## 新runtime的关键证明义务

1. `mul64x24`：在b<2^24下精确积等于high·2^64+low。
2. `fits`：包括s=0,64,128边界；`shift`执行前无丢位，内部没有移位64的错误路径。
3. 两项各<2^127保证同号和<2^128；异号先比较再借位相减。
4. zero-aware c的完整含bias恒等式；把C、S、dw连接回Y8f的语义桥。
5. `certify=true` 对任意raw32 proposal推出正确word，涵盖minnormal/binade/maxfinite边界；strict midpoint miss不改变fallback语义。
6. 成功word→MYa7相等；失败仍走旧Ya7G；原MYbc全输入正确性重新闭合。

不能通过把这些义务当作额外axiom、未验证native cast假设或未证明输入域假设来接上correct。

## 成本与大小

全attempt仍有1次native double除法。计时必须包含3个U64→Float转换、2次FP乘法、1次FP加法、Float32 cast、所有guard和miss后旧路。Wide与Bool×Wide的分配/消除未知。

现阶段文件不是压缩生产版；public23只余3,361B，直接附加超限。将来若用MYa7承担fallback并替换Ya7G/Ya7Ge，需要同时重测miss代价及最终完整文件字节数。不能在未知冠军43上假设仍有相同的可消除成本。
