# 来源、作者与许可证

`originals/`内文件按原交付字节保存；网页报告、补丁及项目研究结论保留其原始署名和语境。本目录的整理不改变第三方源码归属，不将网页判断标作项目已验收结论。

W03含38份固定版本公共源码：Lean 25份、FloatLib 4份、LLVM/Clang 9份。具体文件、原URL、版本和哈希沿用包内的 `agent-runtime/primary/manifest.json`、`primary-floatlib/sources.json` 及 `agent-clang/sources*.json`；其中早期下载失败记录原样保留，实际副本的成功来源由后续清单记录。

| 来源 | 固定版本 | 补齐的许可证 |
|---|---|---|
| Lean 4及文件头所列作者 | `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` | [Apache 2.0](third-party-licenses/Lean4-LICENSE)，从[原仓库固定版本](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/LICENSE)取得 |
| FloatLib Team及文件头所列作者 | `0d91825727839f597fd06b22fdd038ea21480f0c` | [MIT](third-party-licenses/FloatLib-LICENSE)，从[原仓库固定版本](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/LICENSE)取得 |
| LLVM Project及文件头所列作者 | `llvmorg-22.1.4` | [Apache 2.0 with LLVM Exceptions及原文附带条款](third-party-licenses/LLVM-LICENSE.TXT)，从[原仓库固定标签](https://github.com/llvm/llvm-project/blob/llvmorg-22.1.4/LICENSE.TXT)取得 |

这些许可证是本次整理时补齐的伴随文件，没有插入或改写97份原件。来源见[许可证读取记录](third-party-licenses/sources.json)，解码后的字节已对照GitHub返回的Git blob SHA-1；SHA-256和大小另由本目录manifest固定。读取记录未保存逐次请求时间，不能把归档时间当作原网页下载时间。
