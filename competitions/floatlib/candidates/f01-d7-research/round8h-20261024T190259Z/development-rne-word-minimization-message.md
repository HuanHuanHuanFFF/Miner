# R14：RNE3/4最小都SIGTERM，继续拆分Nat与word桥
时间：2026-10-25T02:25:27.457372+00:00
关联：021136；run40153361143已终态65原件全收
类型：CI结果 / 固定证明定位
结果：oldRNE3最小73f4、新RNE4最小30c5、M5 6791、combined3 3c2d全部VerifyFull exit-15、无Lean文本。逐项时长/原hash在development-resource-minimization-40153361143.json；没有把任何一项称通过，R4不是已证实修复。
进一步切分已启动run40154200932/source d0ed0b79988442a5e32c24dfcc9e182e55e8e5df/seed1425020：Nat-only RNE4 prefix99de、原RNE4 full30c5、explicit-word RNE5最小2b21、MUL-cache-proof5 2b532a06。标准原gate/cap不变。
RNE5=development-bias-rne5-explicit-word.lean，只把word_bias换成ADD2已完整gate通过的小位移word桥同一证明方法，范围bound从8改到24，最终Nat_bias仍使用R4相同23/24陈述；用明确toNat/shift/mod身份与no-wrap界，绕开原word中对闭合UInt64大位移的decide。Nat prefix、biased执行定义、其他算法字节保持相同。并不预断decide/OOM就是原因；Nat-only/full-old/new-word对照区分。
真正待完整性能候选仍冻结前d2b8的pureMUL+thin/p8、原DF add，proof5=2b532a06cd35fe3a62866b9e7bc7255464195a31b7f2e46f860162ed100b3e8f/237392B。相对0ab只换等价word证明；不是新运行机制、不是失败ADD改名。若本批真实statement过，再full D seed1425021，DF+候选+41，无observer。
需要研究R：请只读复核word5 proof范围/差分，等待实际分拆结果。若Nat-only也终止，先按具体层级再缩小，别直接又猜运行算法。不要重复改development文件；原astra源保留。
状态：源码机制已冻结；当前保留df5c；薄B/ADD两个full失败D已停放，冠军309模型不动。窗口03:02:59Z，必要验收与原始证据做完。
