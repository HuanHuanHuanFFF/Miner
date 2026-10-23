未发现确定静态错误。精确候选a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78，237142B；父41bce485…235169B。本人未编写此候选/builder。本审查不运行Lean、builder、Git、CI、网络或读取842/843，只新增本MD/JSON。

独立diff为四行旧bmm/spec标识符改名（各+16B）和追加1909B新块；逆变换恢复完整41，净增1973B，距上限18858B。原NativeFinal.dotLoop/dot、全部scalar/sum/packed/NaN replay均原字节。旧bmm改名bmmBeforeDirectRows，定义体与spec证明只改对应名字；新bmm:6381仅n≤4且p>2走DirectRows，其余调用原41。最终bmm及spec各唯一，没有新增运行时浮点guard。

行序等式是具体的，不依赖直觉：固定Vector.getElem_flatMap:2050–2056把第q项定位到外层xs[q/p]、内层[q%p]；ofFn身份向量给r=q/p。新(b,i,j)=((q/p)/m,(q/p)%m,q%p)。原bmmDecodeC在m*p非零、p非零时为(q/(m*p),(q%(m*p))/p,(q%(m*p))%p)。

- Nat.div_div_eq_div_mul q p m及mul_comm p m将batch商归一为q/(m*p)。
- Nat.mod_mul_left_div_self q p m将原行号(q%(m*p))/p归一为(q/p)%m。
- Nat.mod_mul_left_mod q m p将原列号归一为q%p。

因此baseA=(b*m+i)*n、baseB=b*n*p+j和A/B.toArray参数逐项相同，调用完全原NativeFinal.dot。三个固定原件引理均为全Nat签名，不缺额外m>0参数。core_eq:6356–6374先由有效q<hbatch*m*p推出hmp/hp，供原bmmDecodeC条件消去；getElem_flatMap/ofFn再暴露上述式子。空输出没有有效q，证明是空域情况，不是全局假定非空。父RowStream.core_eq已有相同hmp/hp构造和同一Nat simp列表，新增Nat b/i反而少了Fin包装。最后bmm_spec真分支经core_eq和DirectSmall.core_eq_reference接referenceBmm_spec，假分支用原改名spec；没有新浮点等价义务或递归termination义务。

边界保持：batch=0或m=0时外层身份Vector为空，行回调不会执行，m的除模不发生；p=0/1/2不走新入口。n=0、p>2虽进入新行布局，但同原dot0从+0返回、不读空A/B。巨大维度仍是Nat，没有新USize截断或机器字溢出假设；实际资源是否能分配不是本次语义结论。另作119个手选小形状地址对应见证，只核整数布局，不是Lean或浮点测试。

新增命名空间闭合，所有被引用定义都已在前面声明；未见具体可预见坏名字、类型或Nat前提缺口。实际simp是否结束于目标仍须精确源statement确认，不能报Lean通过。原4b7静态policy检查PASS，唯一import仍ContractTensor，无新options/attributes，许可保留。builder只读，parentSHA和禁止覆盖已有Kernel断言、写前容量检查均存在。

性能UNKNOWN。每行Vector、身份row Vector以及底层Array.flatMap合并成本都在完整入口内，省逐输出除模不等于净收益；LLVM是否真正共享行基址、额外分配/复制及新outerguard成本仍需C和完整计时。首先确认core_eq与最终spec，再同41完整对照并保留慢/失败样本，遵守本轮三组冻结门槛。交付前Kernel再核仍同一a06608…；没有修改候选、状态或其他文件。
