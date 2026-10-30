# 已关闭的近榜粗ReLU证书投入
父在官方固定ExactSuite核实：ResNet四conv/最后linear、Mobile三conv+两dw/最后linear全部relu=false；true在后继独立bn（ResNet另addSaved）。R27粗整数ReLU证书需要relu=true，故对当前两近榜目标dot覆盖为0，停止直接移植和大证明。详父RELU-COVERAGE-DECISION.md；不约束本来relu=true的NMLP/Mixer/MLP接口。不要利用未来BN或生成器正scale省略conv值，全12独立义务不允许。A/B/C继续各自实际卷积表示/布局/共享读机制。
