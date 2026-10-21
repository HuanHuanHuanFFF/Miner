# Actual linkearly release-code result

Both saved objdump streams are globally truncated at2M characters, but their complete d_plan bodies and the following symbol headers occur before that boundary. Parent d_plan is16664 bytes and linkearly is16693 bytes. Source/library/text digests and exact coverage offsets are in codegen-result.json.

| D chain | Parent next-link load | Linkearly next-link load | Linkearly first word comparison | Later next-pointer use |
|---|---|---|---|---|
| H4 | 0x21147, after probe-result merge | 0x20f00 | 0x20f08 | 0x21230, cmp r10,r13 |
| H7 | 0x215cc, after probe-result merge | 0x21334 | 0x2133c | 0x21652, cmp rdx,r10 |

The index masking and array base offsets establish load roles: prev4 is indexed via0x7fff at stack offset0x69c58; prev7 at0xc9c58. Their results are retained across probe work and used in the later next<c decision. Control paths now reach these predecessor loads before first-word equality and extension branches; this is a real ordering change, not only renamed registers or relocated addresses.

The initial input QWORD loads still come first at0x20ef0/0x21320. Static instruction ordering does not establish actual CPU overlap or cache latency. Candidate also keeps updated best length in[rsp+8] where parent uses rcx, with candidate store/guard-read pairs0x21226/0x20ebc and0x21648/0x212ec. That is an observed extra stack-storage pattern; whether register pressure offsets the hoist is an inference without hardware counters.

Native444 token/decode cases and public bytes agree. Paired total time versus record is +0.110205% / +0.381368%, mean +0.245787%, with identical size. Stop this exact version without full gate or ordering variants. A slight two-block time increase does not establish a statistically reliable slowdown or identify its single cause, but it supplies no speed gain worth further budget here.
