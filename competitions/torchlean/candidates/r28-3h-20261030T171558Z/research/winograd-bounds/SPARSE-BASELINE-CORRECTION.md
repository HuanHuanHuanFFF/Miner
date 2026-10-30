# 修正父最初的稀疏成本基线

父research/requests/1746把“50%零权重时36项可降18项”的假设带到了原source11。这是错误的成本归因：A重新追踪实际`cdQ→Yt3w→Yt3g/Yt3f`，原11特殊3×3没有weight-support过滤。直接代码对四个空间输出仍执行36个scalar产品（72个split-word产品）；新空间变换是16个scalar产品（32个split-word产品），准备/逆变换等成本另算。

18只适用于理想或已经过滤零权重的直接实现，例如别的强source53分支，不能当原11的实际基线。变换填密的文献事实仍成立，却不能因此断定原11 sparse情形“只有18对16的空间”。A原始纠正与具体源计数在`resnet-mechanism/SPATIAL-SPARSE-COST-SCOPE.md`。父接受这一纠正，保留当时原请求及修正链，不改写旧有限回执。

因此父1818最小空间runtime提案中的“weights全部非零”只是一项过度保守的接线建议，并非数学必须或由原成本证据推出。可在实际原narrow guard内支持含零权重；全零weight行须在producer/偏置尺度和signedzero桥中明确覆盖，或精确回原路径。不要更改已冻结zero/support源，也不据此声称native更快。若未来比较的是新zero/packed或现任私有实现，则应使用它们各自真实成本，不沿用原11操作数。
