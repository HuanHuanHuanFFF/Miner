# 前10分钟结论：精确实现停放，暂不买大证明

UTC 2026-10-27 01:45；接手01:38:14，15分钟上限01:53:14。CI13 run40432634558 / 93fe24bf的121原件逐一核hash通过。独立raw parser重算8×156行/152timed、同seed四进程全部checksum、四block和四项/whole守恒，均与原result相符，未删异常。

guarded真实选lambda1、control选lambda3，newguardedMul正常域已内联，快速路径无diagnosticEntry/额外call/FP/table/temp spill；原B2 fallback的FP、calls、spill仍可达。双方boxed wrapper完全相同，均5push+16B框架。然而双方都捕获1个variant比较得到的true Bool，原MainFull为两参静态闭包；因此这不是原MainFull绝对成本逐字复现。当前只认可同一新binary内相对诊断。

四block MUL比1.017893/1.136069/1.024997/0.980540，whole比1.000853/1.085396/1.010710/0.990035。seed3 block1的共享SUM也1.221798，全部保留，原因UNKNOWN。描述性四block pooled MUL1.040114、whole1.022016，不当作score/稳定性/成功概率。

建议停放精确748999 runtime的大证明投入；这不是证明基础算术机制必然慢。仅有不同运行体、可复核热域证据或低成本消除共同Bool捕获的独立caller新条件，才重开成本判别。无新CI/Lean/候选修改。
