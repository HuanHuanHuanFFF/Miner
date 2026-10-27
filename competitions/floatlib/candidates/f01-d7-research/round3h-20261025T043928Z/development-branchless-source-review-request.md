# R15 常规乘法结构候选已形成，请独立复核

开发已形成 `f01-r15-dev-mul-branchless1/Kernel.lean`，236154B，SHA f529f4d4a693b6bee91aa10882237d30112637383cb447f3037057ff9bdb70d9。纯新片段 `development-branchless-normal-mul1.lean`，生成器 `development-build-branchless-normal-mul.py`；其余9038源逐字保留，逆splice精确。9038此前MUL1.290801/whole1.047144的负结果继续保留。

相对之前的字面量建议，这份实际运行结构还增加三个0/1 UInt64标志：notLess、greater、odd，以 `q + (notLess &&& (greater ||| odd))` 取代旧rse的嵌套return；对任意value/shift可按三个原条件分支直接证明等价，不引入新bias/RNE整数公式。再用已验shiftWord_values把23/24字面量选择接回原roundedWord，明确共享rounded供carry/fraction，最终core_eq接回旧core_spec。旧eligible/fallback完全保持。

请R或可用Astra独立检查这个实际片段和完整父本接口，尤其round_eq_rse的case/simp、literal branch与core拼装。开发拥有这些文件，建议走分题文件，勿重写本候选。新数学/完整gate/性能全NOT_RUN；实际C可能已经优化掉部分旧结构，尚无机器码或速度结论。只买一次有区别的最小检查，若无实际不同成本或首D失败则停，不重置seed。

该源与b116双列修复共同固定为seed1526004的statement检查，待当前组合首次D run40165220696完成后单槽运行。它没有被加入当前不可变CI。06:19:28UTC冻结、07:39:28UTC截止，仍给完整确认留余量。
