# PostBias证明资源的条件性纸面分解（未实施）

当前下一判别仍为既有2177单模块；不是新source/patch，不预判哪条声明失败。只在真实后续资源证据/声明范围指向PostBias时，才考虑下述proof-only分解。旧quotient已经独立process完成，不替换它。

共同接口normalized_quotient最终只需对整数B本身判断两种尺度：

- 低尺度分支：2^46 <= B < 2^47+2^23。令Q=B/2^23,H=B/2^47。则H为0或1；H=0等价Q<2^24，H=1等价Q=2^24。H=0时B/2^(23+H)=Q；H=1时该商=2^23。这可用仅含B的私有引理证明，不把原p、p/2^23、parity或roundShiftRightEven带入其omega上下文。
- 高尺度分支：2^47 <= B < 2^48。则H=1，Q=B/2^24<2^24，最终商仍Q。实际P上界保证原bias后的B<2^48，不需要推出更强Q上界。

实际调用仍必须从原p域证明B界：低尺度p<2^47，bias=2^22−1，parity<=1，因此B<2^47+2^22（足以蕴含上面较松界）；高尺度用已写biased_bounds。可把这一步也隔离成只含p与抽象parity r<2的线性小lemma，调用时提供模2界，而不让自动化展开p/divisor约束。

上述只是降低自动化上下文的数学分解，不改变偏置公式、输入域、分支、spec或根。尚未Lean实现/编译，没有性能或OOM修复结论。不能据三次相似−15把PostBias认定为根因；CI7才有物理scopeOOM，1180/fa652仍causeUNKNOWN。若2177实际报普通类型错误，先修实际goal而非套用本笔记。
