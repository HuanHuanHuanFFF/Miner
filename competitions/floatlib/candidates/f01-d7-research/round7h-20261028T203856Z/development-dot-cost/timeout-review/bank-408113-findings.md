# R24 dot-bank run 40811305126 review

**Diagnostic complete:** all 116 artifact files and sizes verified (11,570,406 bytes; artifact 12871125203).

- The workflow receipt concluded `success`; this is still an exploratory measurement and does not advance official submission or admission status.

- Frozen source: bank2 Kernel `b2855ceccccde7f8416a6210a635a3785107b010a12d009f29292607c9c580e8` equals bank1 Kernel exactly. All six captured C/ASM artifacts also match bank1 byte-for-byte and match both runs’ original artifact receipts.
- Full run: 16/16 processes exit 0; all 16 raw logs and row JSONs re-parsed. Preserved 144 raw ns values (3 per case), across the 3 cases/run. Parser recomputed the stored paired result exactly.
- Native verify log: 6 cases, 464 words, 3 backends, 18 sum checks all pass. Main checks each exact/eager/lazy output word before logging sums; finite verification is not an all-input proof.
- Eager/exact own-control ratios: 0.272269, 0.289203, 0.274803, 0.286351 (range 0.272269–0.289203).
- Lazy/exact own-control ratios: 0.375556, 0.368271, 0.371850, 0.365720 (range 0.365720–0.375556).
- Flags, own barrier delta, three typed array-bank callers, output observer/release audit, manifest component/source identity, and originals_unchanged all pass.
- The measured call includes row-cache preparation and full output allocation/observation/drop. This is a single exploratory runner, not independent confirmation, champion comparison, official score, adoption, or success probability; runtime correctness remains UNPROVED.
