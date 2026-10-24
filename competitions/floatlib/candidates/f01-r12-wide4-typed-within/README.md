# R12：由已证条件直接进入四行循环

基于完整E5，而非削掉Cross后比较。generic output增加`nativeA.size = A.toArray.size`这一Prop参数，真实A.map构造时给出证明；外层原shape/machine guard给出n正性、n界和raw A大小界。具体buildTiles用已接受nativeA_span建立最后一行跨度，直接调用within，块base及packedB[b]在g循环外计算。这里新增的是实际接线，不是又一份未调用的数学探针。

所有原始注释/作者/许可/来源和运行义务保持顺序与原字节；最外Underflow入口1039 B为b135a8ee。Cross、DirectContinuous、Underflow与既有MAC顺序/within/原字NaN回放、尾行、巨大Nat miss保持原样。仅在全部producer/proof caller改完后删R11WideRows4的joinRows/run/run_row；Packed10Index的同名路径保留。原官方bmm_spec仍对全部Nat维度及原输入成立，内部core的额外前提由原guard命中提供。

build.py默认只读重构；--write只允许不存在的新Kernel。manifest与exact-inverse.json绑定完整E5父本及所有变化，可逐字逆恢复。初始静态PASS，Lean/full/性能均NOT_RUN。不修改R11冻结源、helper、根状态或正式提交。

Root先做短statement，再按原full比较新稿/E5/6c2d/41。真实C应证伪：每g不再调用run或重复三个界检查；base与batch B选择在g外；只有一次全局A/B准备，块缓存仍只算一次，没有新增每输出Float32回调装箱。within内部仍含机器基址转换，是否被后端继续移动只按实际C/asm报告。整次成本包含全部准备、输出、尾部与析构，不预言收益。
