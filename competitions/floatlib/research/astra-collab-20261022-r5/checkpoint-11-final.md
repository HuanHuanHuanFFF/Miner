# R5研究最终交接

本轮共同窗口10:05:04—11:35:04 UTC（北京18:05:04—19:35:04）。R研究输入已冻结，三份原始候选、网页原件与已有验证结果已回收。D继续实际组合的选择、冻结后独立确认、Git与所有已启动CI的自然回收。本文件不表示共同任务提前结束，也不表示冲冠已达成。

## 三份精确候选均首次完整gate通过

| 候选 | SHA-256 | 实际完整验收 | 同批BMM发现结果 |
|---|---|---|---|
| f01-r5-row-output，136333 bytes | 97cbe074760474c7b04f549a508614c0ba3317ce192e1d9439632b930d77644d | 604 / 39763228504 | 新/父本归一化0.877162，约少12.3% |
| f01-r5-row-stream，138804 bytes | b5ae8d9b9c8c294ceaa6ee36893c95424bfa3bfc455dc7db7de5c736b154ff17 | 605 / 39763957746 | 新/父本归一化0.847728，约少15.2% |
| f01-r5-lazy-finish，136097 bytes | c127423da4562a2e34029c9c2e7df542db7a0664a9c6070b089527f05f28f136 | 606 / 39765604967 | 新/父本0.996232，未见明确采用优势 |

每份均有自己的全输入四义务、Submission/VerifyFull重放、三允许公理及12类25轮完整结果。父本统一ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630。R不修改这些冻结源码和manifest，当前状态与精确证据在research-status.json及三个*-first-result.json。

数学/实现成果：对任意tiles证明按行构造/flatten与原flat-q输出完全相等；单层stream再以商余数恒等式连接平坦行号，逐行计算并消费tile。零维和巨大Nat仍在最终规格内。点积原k顺序、逐次mul再add、非finite原raw输入回退未变。第三稿的条件分支外提全部定义相等，但性能不足采用；保留这一真实负面结果。

实际C确认了机制：逐输出回调从5mul/2add/3div/3mod/3数组get减至0mul/1add/1div/1mod/1get，行地址和高层get移至外层；stream只保留逐行tile及一次append，仍有复制与RC。lazy确把4mul/2add移入非finite分支，却没有明显完整调用优势，不能再凭减少调用数预测收益。

## 组合选择仍须整包确认

608同机AMD EPYC7763对照中，stream-pack（8eb63a2f，已在607/608完整PASS）BMM相对ba93为0.770708，rows-pack为0.803176；stream的BMM约比rows少4.0%。但本批整包新/旧分别1.020132和0.990347，矩阵优势没有直接转成一致的整包优势。

原始逐类/轮次、参考漂移、CPU和哈希在combined-same-batch-608.json；不要直接排序不同CPU的604/605百分比，也不要把若干部件收益相加。未改标量源码不意味着计时必然不变，当前差异原因UNKNOWN。最终采用和冠军目标必须依实际整包及新runner确认，R未声称正式准入或冠军已达成。

## 网页6 Pro：两路实际并行，全部原件已交D

R在网页执行期间独立完成三稿，两路均自然完成并下载至E:/Download。累计12份ZIP、12份Markdown全部重读SHA/CRC通过，清单为download-index-final.json；本轮各包清单也单独核验。

- W01 ZIP SHA24fbddcf7558d955eaf43991bfce22cfebf7b8c70530946f4d36d5e218a21904；19项清单通过。独立两层行序证明与首稿同机制，保留通用引理、16个回退见证，未重复消耗CI。其自身脚本仍NOT_RUN。
- W02 ZIP SHA4ed3278ca5c155411cf959930bbd1aea8f71480b8cfdb06aa7432721cfb0700b；16项清单通过。全域finiteBits/toBits桥原c09与首修c3均实际statement失败，未通过公理或完整验收。原件、失败与具体剩余目标在checkpoint-08/09和web-proof-and-profile-final.json。

W02仍有最后需D处理的准入问题：D合并版03ca虽统一了allOnes表示，但line13的`#spec`已由原官方正则实际检出，会被policy拒绝。checkpoint-10-policy-alert.md给出精确证据及直接使用BitVec.allOnes的最小修复方向。R没有改D文件、取消610或将未验修复写成通过。后续必须绑定新SHA和实际gate；同时核对真正可达finish，避免只修改未调用的helper。

## 阶段诊断的解释边界

601/603/605构建或回收失败，607是零工作量，原件全部保留。609的非零计数有效，但13次调用混合3个计时类各1次checksum+3次计时，以及1次不计分raw。约1秒output累计含raw软件回退，不能拿它说正式计分的output占99%。固定BenchBmm源码与调用计数已核对，正式计时域的阶段占比仍UNKNOWN。详见checkpoint-09。

## 承接事项

D已逐字节接收三份R候选和W02源码，并独立拥有组合脚本、CI、提交与看板。接下来由D收齐608/610及已启动后续确认，依据实际整包选择；优先处理checkpoint-10的精确policy问题。R没有未下载网页job，没有本地重型工具链或后台实验。

本地根/赛道自检通过（只覆盖路径、语法、manifest与配置，不能替代Lean）；候选和交接哈希另已核验。全部预算包含协调、等待与回收。共同目标未达成，已启动作业须自然完成并保留失败和慢样本。
