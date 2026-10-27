# 914实际CrossRows代码核查

对象：5c5e7071927400ecd75d02d69b0ce62236a50a615912d99e7f8470a9ccf19c6b，252699B。原完整gate通过，verdict SHA 4fbb680b74a401dff45bd3cdfc7eb320209dca9a4d71a4519c7d0189f22a9566。详细逐函数C、从bmm出发的静态调用/函数指针路径、20份选定汇编及哈希见astra-cross-codegen-914.json；可用astra-cross-codegen-audit.py重新只读核查。

捕获为原完整gate同进程的statement阶段对象，不是另行重编的微基准。C SHA e2f48c0ff8285e3d56ccea18bec0282630dbe7e5afe037fcfd001ba026869ee6；对象608256B、SHA 3d3053e0ac15570973ea4c788541af0e98135fa52fb0ffc49e9c0843b5ec9ab2。compiled-Submission.lean与冻结源逐字节相同；捕获在首次观察到score前完成。trace确认Lean4.34/293d、x86_64、O3、ffp-contract=off，无march=native。原对象已按捕获器政策删除，原C/trace/选定汇编仍完整；20-symbol预算使assembly状态为PARTIAL，不宣称全部调用端都有asm。观测开销仍可能存在，性能属于发现组。

## 1. 真正执行的内核已获得SIMD

实际bmm→core→words的ofFn闭包→blockRows→blockAt→dot8→wordLoop___redArg路径在C中闭合。不是只看未调用的natLoop/update：这两个证明用数据函数在该入口静态图中不可达。

wordLoop___redArg的216B汇编把8个标量累加器组织为两组4-lane寄存器。0x28–0x92的有效迭代区域没有call或rsp/rbp栈读写；主循环0x50–0x91每次处理两个k，4条mulps+4条addps，保持每条输出链的k顺序，未使用FMA或水平归约。C使用lean_array_uget_borrowed读取P12，没有逐步记录引用计数或逐MAC构造。

退出后0x93起才把两个XMM向量暂存32B栈，调用heartbeat与mi_malloc_small，构造一个40B含头F8对象，再写回向量。不能把退出分配前的spill误报为热循环spill。

## 2. 打包共享真实成立，但准备成本仍在

实际packShared回调有6次of_bits：4个A、2个B。两个B结果分别写入4个字段；general回调有12次of_bits。两者均执行lean_alloc_ctor(0,0,48)，即一个56B含头P12对象，绝不是12个Float32盒子。

每组仍通过通用Array.ofFn闭包创建n个P12记录并形成Array；dot8执行wordLoop后释放该Array。共享B只省转换，没有省掉8个B字段的存储。准备回调仍有总定义读取、Nat索引/边界分支和原始字解包；不能由热循环已优化推出全调用准备免费。这里是已冻结short A的实际动机，7cad的最终C/成本须等916。

## 3. 输出装箱假设正式PARK

本次实际finish8（C43732起）八次直接调用返回uint32_t的Packed10.finish，不调用它的___boxed入口，也没有逐结果Binary32堆构造。汇编进一步内联了这些调用：全非NaN路径每组8次foreign isnan和8次to_bits；源码调用数与控制流闭合。汇编有12个isnan静态调用点，是大Nat地址/冷分支复制，不能把12当每组动态次数。

F8→W8也已有复用：finish8先读8个float字段，检查输入对象exclusive；exclusive时直接覆写同一32B scalar payload为8个UInt32，只有reuse失败才另分配40B。wordLoop新建F8，dot8直接返回，blockAt直接交给finish8且不增加该F8引用；因此当前可见主路径具备单所有者复用条件。保守结论是不能把F8和W8按每组必然两次堆分配计费。

终结阶段确有float值跨foreign分类/序列化调用的栈保存，但不在wordLoop热循环内。仅改成word返回类型不会消掉这些成本。Root/Sol迁移现有self-BEq可针对isnan调用；R自己的等价guard补丁继续PARK，不重复候选。

## 4. 输出控制留下明确结构机会

实际core仍构造全部W8结果数组，再用通用Array.ofFn闭包逐输出读取。rowWord借用W8对象，返回uint32_t；最终___boxed回调仅做64位UInt32 immediate tag，不能算浮点/结果堆盒子。闭包适配中的引用计数及通用回调仍可见，未捕获导入的Array.ofFn实现汇编，不能给它编造周期成本。

关键实证：core___redArg___lam__0仍捕获运行期p。其普通小Nat分支对q/p和q%p执行两次硬件div；即使实际入口只有p=2，也没有在这个回调中常量化。rowWord再做r>>2与r%4。blockRows的C另有四个r_i/m操作，但该函数asm未入本次20-symbol预算，不把C操作数当实际除法指令数。

后续可判别方向是固定p2输出reader（让回调体本身使用字面量2，单纯把2传给通用core未必穿透闭包），或与已有连续输出证明结合后逐组发出8个字，去掉W8全量中间数组/逐输出除模。两者都要实际新C与完整计时；此报告不生成新Kernel，也不把这些控制操作已存在当作它们占主要耗时的测量。

## 5. 当前发现组覆盖与边界

已执行914的六个p2计分案例为[batch,m,n,p]：
- dense:2 [182,161,3,2]
- ml:4 [58,66,23,2]
- subnormal:0 [4901,3,6,2]
- subnormal:1 [9803,3,3,2]
- subnormal:2 [334,1,264,2]
- subnormal:3 [119,2,369,2]

该组没有p2且n1/n2，不能用于声称short A收益。尾组仍计算全部四行、完成全部8个结果，再只输出合法行；全矩阵最多3个多算行。上述大输出案例的尾部占比很小，长n的小行数案例需按完整成本保留。虚拟尾地址仍是Nat/total getD；之前32/64位超USize反例继续限制未来机器地址转换。

完整发现比较（各自原参照归一化）：vs a066 whole0.9775279143、BMM0.9177310746，whole收益p05约+.00967；vs41 whole0.9586347301、BMM0.8555585758。不是独立留出、正式冠军比较或阶段耗时分解。约2.25%整包增量不自动满足更强采纳门槛，组件收益不能相加。

结论：保留四行SIMD结构；先收齐short A、self分类及连续输出真实成本。热点内再扩宽不由本次结果支持。F40四行×10列的下一步应先做单一unused CODEGEN_ONLY机器循环探针，判别寄存器和spill，再投入输出接线；与本报告的完整5c5e验收分开。
