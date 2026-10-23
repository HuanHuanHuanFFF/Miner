41的BMM仍有值得定位的完整路径成本，但当前证据支持先区分direct与packed/replay，不能直接重开更大微块。精确Kernel SHA41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7，235169B。821/822原完整gate各25轮通过；本次将两批各43份artifact原文件重新核SHA/字节，input、seed和原verdict均匹配。没有新候选、Git、CI或agent。

计分成本按原完整gate各cell的submission_ns×精确work重建，包含实际入口的制备/运算/输出/回退；不是整次runner walltime。单位ms为计分ns之和的换算，不是某个单一case调用时间。

| BMM cell | 821成本ms | 占整包% | 822成本ms | 占整包% |
| --- | ---: | ---: | ---: | ---: |
| bmm:dense | 16.139 | 8.722 | 1.888 | 1.481 |
| bmm:ml | 6.496 | 3.511 | 5.835 | 4.576 |
| bmm:sparse | 8.053 | 4.352 | 6.899 | 5.411 |
| bmm:specials | 17.222 | 9.308 | 6.003 | 4.708 |
| bmm:subnormal | 5.823 | 3.147 | 13.521 | 10.604 |
| bmm:extremes | 1.985 | 1.073 | 1.020 | 0.800 |

BMM合计分别55.718ms/30.113%与35.166ms/27.579%，相对各自shipped reference的BMM ratio约0.15979/0.16457。若其余运算不变，要取得整包3%降耗，BMM本身需约9.96%/10.88%下降；这是机械门槛，不是可实现收益。各cell参考成本、spread和BMM内份额保存在JSON。两个seed的shape/data与runner不同，不能合并原始ns，也不能把混合cell耗时分配给一个路由。

真实路线是Kernel:6099的n≤4或p≤2走DirectSmall:6071，按q解码地址并调用NativeFinal.dot:5201/Nat dotLoop:5156；非NaN导入native结果，NaN走raw replayEarly:5095及quiet-stop replayLoop。其余正维度走RowStream:6003：nativeA map＋packB，按行生成Packed10Index USize十累加器tile，再RowOutput.row:5910/finish:5451。空输出或n=0保留referenceBmm。825实际C确认direct每k仍有Nat推进/地址操作（dotLoop:37928–38002，Nat add:37993）；packed loop:38779–38862已是size_t参数。两者常规native内循环均不逐MAC调用scalar guard。41没有候选4792的canonical整dot扫描/共享缓存，不把旧scanner读数当成现有扫描成本。

能改变方向的最小证据：

- 优先量清direct路径。821有5个long-thin p≤2案例/536724 work，822有6个/542429；两轮各有2个n=1案例，输出数184440和352867。后者在822恰落在两个subnormal case：形状2941×10×1×6和2291×11×1×7。当前n=1仍经过通用Nat dot框架，原47d native-singleton有静态材料但本证据没有完整计时；旧4ba是证明失败，不是性能负面。第一判别是当前41按case、route及阶段的有控制诊断；若direct成本足够，USize索引或native n1特化是不同于旧packed微块的上下文。必须保留巨大Nat fallback、地址边界、+0 seed对-0的规则和rawNaN payload。
- 在改Packed10前分清普通prep/output与NaN replay。821最重为specials/dense，822为subnormal；这不证明某阶段占主导。41对同批a84的BMM归一化0.905491/0.852078是真实整包组件反馈，但不能据此分配phase成本。若replay重，暂不扩tile；若prep重，检查窄组制备是否可省；只有native loop重才继续机器码驱动的tile改变。

公开留存历史源码与真实负面已经核对：R3 packed8 USize同批旧三类算术均值1.187918，相比Nat版1.323695约为0.8974，原verdict SHA已重读；它说明去Nat机制曾在真实上下文有效，但当前packed已继承，新增机会是仍Nat的direct。R4 2×4与2×8均完整通过，BMM却约慢9%/0.6%；真实SIMD/B复用已形成且无热spill，不能再把“形成SIMD”当收益证据。旧套件是固定大矩阵，不能把负面泛化为新variable-shape direct p1/p2优化必失败。

R5 matrix numeric decoder完整gate负面重新按原verdict核为1.022965，即约慢2.30%；只覆盖旧固定50×100×50、batch2的normal输入，无E1..23。这阻止盲目整体替换decoder，并不单凭机制名称否定新输入上下文；本轮不重开scalar939。R5 row-output/row-stream已有实际优势，现已在41继承，不能再计一次。lazy-finish约0.996232无明确采用优势，而当前rowstream已外提大部分行地址，残余更需profile。独立eager/lazy共享摘要及Float32存储历史仍缺当前普通路径完整成本，保持PARK。

关键缺口是当前41按case/route拆分的prep/native/finish/replay时长。821/822只有cell；825只有C与选定对象汇编；807是旧8eb重编译，R5的13调用混timed/raw，R6曾zero FL_CALL，均不能继承为当前阶段份额。新诊断必须绑定41/精确计划，分开checksum、timed与raw并记录每case instrumentation overhead；n1尤其容易被观察开销淹没，函数提取也不能只接受lean_object*而漏uint32_t/float。不得把诊断对象当原fullgate计时对象。

现冠军285对应的“3.05×”实际是candidate/champion BMM耗时跨runner投影中位数3.0474768：假设硬件比例1，并把private suite分组均值映射到public工作量，shape/value分布不同。它不是本轮实验收益、直接同suite冠军测量、置信区间或官方准入；也不是本轮必须追回的已测3.05倍差距。引用2026-10-23 12:39:03快照，不声称本次刷新了官方状态。新R9路线收益UNKNOWN。
