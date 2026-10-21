# Release-code discriminator for linkearly

Use the actual paired benchmark release library, not an independent rebuilt harness. The existing round4 cpu_diagnostics captures its SHA256, source digest, nm output and objdump text. The main thread selects record-nonempty and linkearly explicitly for this evidence. No binary needs to be downloaded to Windows.

1. Bind each artifact to its exact candidate Rust, same pinned toolchain/runner and library SHA. Check whether objdump text is truncated. Missing target-body coverage means UNKNOWN rather than identical code.
2. Locate candidate::parse::d_plan or the symbol containing its inlined D loop from nm, rather than relying on the older walk-outline symbol addresses. Source d_walk is inline(always); it need not have a standalone symbol.
3. Identify both D chain-walk loops by the same distance/window/nice/candidate guards. A predecessor read is a DWORD load indexed by the current chain position masked to0x7fff and based at prev4/prev7. Distinguish it from table stores and other cost/ring reads. Follow address-register definitions to establish its role.
4. Identify the current probe's input QWORD load and any ensuing common-prefix comparison loop. Compare CONTROL-FLOW/value-dependency order, not absolute addresses or the textual order of cold blocks. The intended evidence is that the existing next-link load now dominates the byte-probe entry, where previously it was reached after the probe-result merge, allowing its latency to begin earlier.
5. Check whether the read simply moved into a stack spill/reload sequence, whether it was duplicated on paths, and whether added register pressure changed loop size. Report those separately from the scheduling hypothesis.

The .so digest changing only proves that some compiled bytes differ. Register renaming, symbol relocation, jump-displacement changes or function alignment do not establish an earlier load. If normalized CFG and role-specific memory-operation order match, classify the intended CPU mechanism as NOT_OBSERVED; any timing difference remains unattributed layout/noise evidence. If the baseline already loads the predecessor before probing, this source reorder buys no newly established overlap.

Historical R7 walk-outline disassembly has an input-word read at0x1f670 and predecessor read at0x1f8e1 after candidate/length processing. It is only a late-load example in another compilation shape, not current inlined D evidence. Its exact file hash is recorded in manifest.json.

Native444 token/decode equivalence and identical public compressed output must hold before using timing as a same-output comparison. Fresh extraction and the small moved-modulo/index proof binding still require the original obligation, allowed axioms and public round trip for full-gate acceptance. Only materially positive paired total compression justifies later combination or confirmation; do not sweep instruction-order micro-variants.
