# Packed D record header review

Scope: source-only audit of the proposed `r10-record-packed`, against verified
`r10-record-nonempty` Rust
`7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`.
The reviewer implemented no Rust candidate and dispatched no CI. Finite format
model results are in `packed-record-review.json`.

**Verdict:** no source-level obstruction found. This is a representation change
that can preserve the entire logical node stream, unlike adding an overlay node.
Runtime equality and performance still require the requested tests and fresh gate.

## Conditions that make the encoding lossless

For every parse with the original usize `input.len() < 2^27`, use one header:
`((i as u32) << 5) | cnt`. The actual record loop considers at most 16 candidate
slots, so `cnt <= 16`; five low bits suffice. Valid parser positions satisfy
`i < input.len()`, hence fit the remaining 27 bits. Values 0..2^27-1 are
representable, although the chosen strict input-size guard leaves additional
position margin. The highest representable position with count16 encodes as
`0xfffffff0`, without overflowing the u32 field.

All nodes of one parse must use the same mode, selected from the **usize input
length**, not a truncated u32 length or each node's position. For `n >= 2^27`,
write and read the original `[i as u32, cnt]` format. This preserves the parent's
large-input behavior, including its existing absolute-position truncation beyond
4 GiB. At n=2^27 the fallback is intentional and conservative.

The node-zero rule remains essential. A stream containing only the required
empty first node changes from `[0,0]` to `[0]`. A packed loop must test
`e >= header_words`, with header_words=1, and process that node. Retaining the
old `e>=2` test skips it and loses the prefix-sweep mechanism.

## Reader arithmetic and concrete failure cases

For h=header_words in {1,2}, under the loop condition e>=h:

1. Compute e2=e-h; read the final word at e-1.
2. Packed mode extracts k=word&31 and p=word>>5. Wide mode retains the original
   k=last word and p=word at e-2.
3. Reject k>e2 or p>=hi before calculating a=e2-k or p+1.
4. Candidate payload is rs[a..e2]. If k>0, its top is at e2-1; otherwise top=0.
5. After processing the same logical node, set hi=p and e=a.

Every successful iteration decreases e because h>=1, even when k=0. The old
p<hi check still proves p+1 safe and bounds positional output accesses. The
candidate loop spans exactly k words in either representation. Using a total
top helper with `e2.wrapping_sub(1)` keeps its standalone contract simple;
well-formed active calls already imply e2>=1 whenever k>0.

Minimal representation failures:

- Masking with 15 instead of 31 turns count16 into zero.
- Packed `[0,3,97]` represents empty node0 followed by one length3/distance1
  candidate at p=3. At e=3, old `e-3` reads the first header0; correct e2-1 reads
  candidate3. This demonstrates why top must use the payload endpoint.
- Packing position2^27 wraps its position field to zero; the length-mode guard
  and actual-position bound are therefore required for losslessness.
- If mode selection casts n to u32 first, n=2^32+16 incorrectly enters packed
  mode. Selecting from the original usize avoids that bug.

Malformed packed headers can encode counts17..31 although the writer never does.
They need not be trusted: k>e2 and p>=hi rejection plus get0 and existing candidate
validation preserve safe progress. In particular, do not subtract the payload
count before checking it. Truncated headers, out-of-order positions, oversized
counts and arbitrary payload words remain totality obligations, not assumptions
about valid LZ77 data. No new unchecked indexing is needed.

## Capacity, platform and selection semantics

`d_push32` guards against usize::MAX entries, not 2^31 entries. In the packed
input range, the original stream has at most 18*n words (16 candidates plus two
headers per position), at most 2415919086 for n=2^27-1. That is below the 32-bit
usize maximum4294967295; the packed bound17*n is 2281701359. Thus this source
guard cannot create a different small-input stopping point just because one
format saves a word. This does not promise that such extreme allocations fit
physical memory or a 32-bit process; it addresses the source-level guard only.

The candidate payloads, logical p/k sequence and processing order remain the
same. If decoding is correct, d_gap, d_cand, their future prices and their dynamic
best-end pushes receive the same arguments. This is why same-token equivalence
is a reasonable target here: the transformation does not add/remove a logical
node or alter the DP edge-selection inputs. It still needs actual finite and
public tests; the review is not a universal Rust equivalence proof.

The n/2+64 Vec reservation should remain unchanged for this controlled test.
Fewer used words do not always reduce allocated capacity; they may instead avoid
a growth step, or may leave the same reserved allocation in place.

## Minimum proof delta

- The writer proof needs its new mode branch, fixed shift5, OR, and one/two
  existing safe push calls. Proving the full lossless encoding is useful for
  semantic review, but the official untrusted-planner obligation primarily
  requires totality and existing output validation.
- The outer d_dp loop gets a frozen h (or packed Boolean), with a proof that
  h is 1 or2. It does not need another evolving loop-state field.
- Replace the old subtraction/metadata-reading prefix with the guarded decoder.
  Existing payload, gap, candidate, block and output lemmas can remain.
- The parent helper `d2_dp_meas` explicitly assumes `i+2=e`. Generalize its
  decrease fact to `i+h=e` and `1<=h`; do not silently reuse the old two-word
  statement. Make the scalar decrease proposition explicit to avoid tuple
  projection simplification problems seen in the earlier seed proof.
- Update the top helper/call to the candidate endpoint e2. Its totality lemma
  can retain the same broad result specification.

Fresh extraction is needed before fixing generated argument/tuple order. Neither
the copied parent proof nor this format model establishes original-obligation,
axiom-whitelist, round-trip or runtime acceptance for the new candidate.

## Realistic gain and first falsifiers

For N retained nodes and C candidate words, exact storage decreases from
4*(C+2N) to 4*(C+N): **4N bytes saved**. With one candidate per nonempty node,
the stream saving approaches one third; with two it is one quarter; at sixteen
it is about5.56%. The isolated zero node saves one half. These are stream-size
ratios, not measured corpus ratios or total-time improvements.

Forward recording removes one store/push/capacity check per retained node;
backward decoding removes a metadata load but adds mask/shift and mode handling.
Reduced cache pressure and avoided Vec growth are plausible benefits. Candidate
search, cost fitting, DP arithmetic and the public encoder remain; those costs
bound the effect on total compression time. The prior empty-node result does
not establish the gain from this different metadata change.

The local model checked 24 valid record roundtrips, 6 large-input fallback cases,
16 field-boundary combinations and 3444 malformed streams. It preserves logical
records, verifies exact one-word-per-node saving, and checks strict reverse
cursor progress. It is a Python representation model only.

First reject any header/payload mismatch or failure to preserve node0. Then run
444 whole-parser token/decode cases, public byte identity and paired total time
against record (with scalar as the established control). A smaller stream with
unchanged or worse total time is a negative result; it is not a reason to add
unmeasured CPU combinations or alter the format threshold.
