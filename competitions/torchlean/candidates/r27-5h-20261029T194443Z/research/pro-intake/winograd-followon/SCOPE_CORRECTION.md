# 600e实际候选：范围更正记录

本页与修订后的README／实验规格覆盖上一包及上一答中对最终候选的外推。数学推导、反例、原有限模型结果保留，不重做研究。

## 已纠正的四项归属

1. **已接线。** “所给Runtime未接线”仅描述此前孤立 `WinogradRuntime.lean.inc`。实际 `600eaaa1…／71667B nativefinish-v2` 由两份builder完成 `totalWords→finishWords` 调用；不能称最终候选缺此修复，不能记作本包新增效果。
2. **已有整入口回退。** v2在所有输入cache无效时，于W扫描／准备前返回retained整入口，保留原融合路径。尚存风险限定为仍进入逐输出分支时的scalar miss，尤其mixed-validity；不能把all-input-invalid与任意E=0混同。
3. **实际是NMLP/source12。** 冻结请求是 `normalized_mlp`、batch8全部三个linear（含输出宽10），batch1与norm不变，对照为source12内部控制。早期Mixer两个channel-linear建议不再描述600e；public23成本分析仍是独立对照，不是source12同机证据。
4. **71667B不是public23直拼预算。** 冻结请求与父控重构给出600e为71667B，低于256000B。此前public23本体252639B加片段的字节算术不能作为600e的预算障碍；未来完整证明后的正式条目仍未由本包验证。

## 证据层级

| 事实 | 本次证据 |
|---|---|
| 两份builder及冻结请求未损坏 | 三个内嵌区块SHA256均与附件声明匹配 |
| native finish接线及v2继承 | 静态检查builder文本／Python AST：首builder替换旧调用，v2基于该父产物加整入口回退 |
| 完整600e哈希、71667B、旧调用0／新调用1 | 父控逐字节重构报告及冻结请求；**本环境没有独立重构整候选** |
| 上轮Python finite模型 | 原脚本、Lean代数桥及verification.json保留；本次未重跑或扩增检查数 |
| 编译／完整性能／wide-gap Int helper | 本环境没有执行或验证：**NOT_COMPILED／UNKNOWN／UNKNOWN** |

实际候选完整SHA256：

```
600eaaa1af9c7f7b2da1436f4d55d15a51b6879642d2ece0c5fa261e13f10e8d
```

“旧接受调用为0”不表示宽gap没有Int终端。原helper的宽gap路径仍未验证，不能因接线确认、有限word模型或builder名称而升级结论。

## 包内片段的状态

本包 `crossSigned63`、`finishZeroBodyOr`、ReLU exact-zero出口及代数桥继续作为本轮已有的独立研究片段，均未编译、未合入600e、未扩展冻结队列。`make_probe_delta.py` 已标注 **LEGACY FRAGMENT ONLY / NOT A 600e FIX**；其中历史组装接线不再计入原创优化效果。

补充builders与原始冻结请求全文不装入zip；仅保存本说明及MANIFEST中的来源哈希、范围和核查记录。本次未读取其他候选的在途确认数据，未新增子代理、CI、工具链安装或实验窗口。
