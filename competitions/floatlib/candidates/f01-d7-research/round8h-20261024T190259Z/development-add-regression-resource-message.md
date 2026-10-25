# R14：ADD全正确但性能回退，继续固定MUL路线
时间：2026-10-25T02:11:36.967443+00:00
关联：020414冻结；run40152158687/40153361143
类型：CI结果 / 路线选择
ADD2=f958在source bea、seed1425016完整gate/25轮全通过，46原件全收。相对同场DF whole1.18927645091，add1.56212815662，BMM.89204956589，p05-.2280894；停放新ADD public arm，不开A/B，不换输入重挑D。组合整体变化不能归因于单独一项，add本项明确慢；proof/model对齐与UInt字段证明确实已被完整gate使用。
已启动受控statement5018：run40153361143/source37b5/标准公共runner，oldBias最小73f4、newBias最小30c5、M5 6791、combined3 3c2d。状态刚开始queued，按原cap完成，不借槽。先最小化复现再读控制，不先认定OOM或数学失败。
冻结后源码选择：不再把慢ADD arm带入性能候选。另有f01-r14-dev-mul-cache-proof4=0ab970e382f0e29cca4ac5d54cf40bd8424180872b77b90754ee512ab51240ab，236678B，**只是既有冻结前d2b8/234967B的proof-only修复**：BIAS2→quotient4（运行suffix相同）、core_model2单声明、薄B冗余dsimp；其余字节完整相同，没有改运行定义/阈值/布局。仍是原DF add/SUM＋integer MUL＋thin/p8，runtime早已存在；它不是新的机制，也不重置ADD或thin/6990的失败D。若本批MUL编译通过，后续full先比较M5与这个既有组合，不再测带慢ADD的allword3性能。
需要研究R：等待本批最小对照真实输出，继续固定MUL的证明/终止定位；原始Graph审阅与数学片段保留。
需要自由侧：当前无新源交付，冻结后仅交接思路/核对既有结果，不启动新机制。
证据：development-add2-first-d-decision.json、result1425016原件、development-mul-cache-existing-runtime-proof4.json，当前root还未将新增decision/proof4推送，下一结果批次一起提交。
下一：5018全收→按实际编译结果做固定乘法路线完整D；窗口03:02:59Z，已启验收/必要证据做完。
