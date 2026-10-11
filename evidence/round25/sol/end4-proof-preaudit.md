# End-4 proof pre-audit

**Source inspection only; extraction and Lean compile NOT RUN by this agent.**

Parent expanded the delegated edit range to
`candidates/r25-astra-end4-proof1` and `scripts/build-round25-end4-proof.py`.
The original `r25-astra-end4` pair remains frozen and is owned by Astra.

The end-4 source has Rust SHA-256
`03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6` and
inherited Lean SHA-256
`4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`.
Its only source delta inserts this guarded code between the original
record-head loop and original tail recording:

```rust
if end >= 4 && ins <= end - 4 && end - 4 < lim {
    let j = end - 4;
    let a = pc_slot_of_m::<H>(s, j, km);
    pc_f_link::<H>(head, prev, a, j);
}
```

The intended migration remains confined to `PC.f_record3_spec`, provided
fresh extraction confirms the loop/caller interfaces remain unchanged.
Its existing premises are:

```text
HeadBound head B
end < B + 1
lim + 8 = s.length
ins0 <= lim + 1
0 < H
```

`slot_of_m_spec` needs only `j+4 <= Usize.max` and `0<H`, then returns a
slot below `H`. In the new branch, `j=end-4<lim`; therefore `j+4` is bounded
by `lim+8=s.length<=Usize.max`. `f_link_spec` needs the valid slot and
`j<B+1`, supplied by `j<end<B+1`; it preserves `HeadBound` after the
additional insertion. Its predecessor array contents have no invariant
in this interface, since later matching validates real bytes and window.

The head/tail loop specifications and measures do not need a stronger
monotone-history property for safety. Native insertion-order evidence
under `astra/` concerns compression behavior, not this `HeadBound` proof.
Changing chain history is intentional and is not an equality obligation.

The inherited `step*` and conditional splitting may already prove the
extra direct calls. Do not claim that without a real compile. Before
writing a proof candidate, compare emitted `pc_f_record3`, both recording
loops and affected caller signatures; bind the exact emitted Funs hash.
If binder order is unchanged, try the smallest local theorem change or
unchanged theorem first, preserving the final obligation and axiom policy.
Any failed compilation remains explicit, and a passing full gate applies
only to the exact final Rust/Lean pair.
