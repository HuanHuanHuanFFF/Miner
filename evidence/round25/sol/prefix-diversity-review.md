# Parent eight-byte prefix diversity: independent review

Status: **structural review and diagnostic proposal, no new candidate**.
The approved observer is
`scripts/research-round25-prefix-diversity-counts.py`; its local source
reversal/schema checks pass, but Rust execution has not yet run.

## The retention question

The actual parent is `r22-595-chain-halfhead`, Rust SHA-256
`57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275`.
`pc_f_link` stores the previous short-hash head in `prev[i%32768]`, then
sets that hash head to i. It does not inspect key bytes or compare eight
bytes. Thus repeated8 prefixes can occupy the only secondary opportunity,
but their frequency and opportunity cost on the **parent** trajectory
remain UNKNOWN until the new observer runs.

R2 bucket2 kept the nearest two positions of a short key in two SoA planes;
its subsequent two-runner means were +0.6127%/+0.1219% with identical
output. R13 pair64 kept the nearest two full U32 positions in one U64 cell
at the same capacity; its total time was +0.02751%. These tested access
layout, not a policy that deliberately retains distinct8 prefixes. They
do not rule out a semantic retention change, but do rule out assuming that
two tables or a shorter pointer dependency will be faster.

R24's capped8 LCP metadata preserved31.5M query answers, added10.1M prefix
constructions and was +3.282%/+2.133% slower. R25 wordtail preserved444
finite cases and28 public outputs, yet its main blocks were
+0.4954%/-0.05995% versus end4 and all current projections stayed zero.
Neither prefix-work removal nor representation changes are speed evidence.

## What dual8 E establishes, and what it does not

The actual dual8 observer `38127500920` reported4,130,586 hash8 operations,
including2,538,080 record updates. Accepted older long candidates were
105,759 in primary-length3–7 and7,240 in misses. The combined already-long
domains had224,440 queries and zero older hints or acceptances.

This zero has a structural explanation under the observed monotone,
same-position updates, full4-byte key, exact8-byte match and timestamps
that fit U32: a primary matching8 bytes has itself written the query's
long-hash slot. Subsequent writes to that slot cannot make it older than
the primary. Therefore `c8<c` fails. This is not a formal all-input lemma;
in particular, the stated timestamp and coherent-head assumptions matter.

The same explanation **does not make the parent's repeated8 predecessor
redundant**. The parent's older source can match farther beyond byte8.
If its only predecessor is always chosen to have a different8 prefix
from the main head, then on four-byte depth1 routes it cannot improve a
primary match of length>=8. That would delete the parent's entire
already-long secondary capability. Dual8's domain distribution cannot
bound this loss because its trajectory and retained sources are different.

## Two opposing finite byte examples

All three source prefixes below have the same initial4-byte key. These
are byte-comparison examples, not observed corpus cases or Rust runs.

- **Opportunity:** head and immediate predecessor are `ABCD1111...`;
  query is `ABCD2222QQ...`. Both nearest sources stop after4 bytes. An
  earlier `ABCD2222QQ...` source can be longer, so the duplicate consumes
  shallow search capacity without helping that query.
- **Loss:** head is `ABCDEFGHRR...`, predecessor is `ABCDEFGHQQ...`, and
  query is `ABCDEFGHQQ...`. The head stops after8 bytes while the same8
  predecessor extends beyond it. Replacing that predecessor by a
  different8 prefix such as `ABCDzzzz...` loses the actual longer match.

A distinct-prefix retention policy also is not equivalent to independently
indexing the current query's8 prefix. It retains only a small recent set
of classes under one short-hash slot; an interleaved third class can still
be absent. Hash-slot collisions must be distinguished from equality of
the actual first4 bytes.

## Minimum parent observation

The new observer keeps original parent f/g, recording and emitted tokens.
It hooks only actual `km=0xffffffff, dp=1` routes1/6. Other routes are
parsed and decoded normally but contribute zero targeted counters.

For every targeted matched query it records the main length domain,
live/invalid old predecessor, actual4/8-prefix relations, and whether the
original secondary wins. The long domain separately records all wins
whose old source has the same8 prefix and their local extra lengths.

Only for a short main match with a live same8 predecessor does it inspect
up to8 additional strict-decreasing, in-window old-chain links, stopping
at the first different8 prefix. It checks that candidate's complete
bounded byte match against the current query and records local gains over
both primary and the unchanged original choice. Hash collisions, invalid
endpoints and cap exhaustion stay separate. Exhausting8 links is UNKNOWN,
not proof that no different prefix exists.

Compilation/run caps are180s/240s. A fresh Linux runner must compare the
complete frozen and observer token arrays, independently decode all28
inputs, retain input/source/harness hashes, verify15,930,000 input bytes
and every counter identity before recording VERIFIED. Extra reads and
atomics are excluded from original algorithm operation counts; the
observer has no performance interpretation.

## Decision that this evidence can change

If short duplicate queries rarely expose a useful first distinct source,
stop this diversity route without another layout/tag/packed retry. If
already-long same8 parent wins are substantial, a global unique8
secondary is unacceptable even if short opportunities exist. If short
opportunities are useful and usually close in the old chain, the evidence
can support one separately specified way to access them while preserving
the original long-domain source; it does not choose that implementation
or prove its encoded quality/time tradeoff.

Avoiding hash8 multiplication is not free maintenance: a byte-aware link
policy would need old-source word loads and possibly a predecessor load
at each recorded position. The current observer resolves query relevance,
not insertion cost. Actual new Rust, original encoder, paired total time,
fresh proof and frozen independent confirmation remain separate gates.
