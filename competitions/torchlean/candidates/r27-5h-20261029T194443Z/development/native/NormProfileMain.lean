import ExactSuite
import Submission

/- Owned layer-cost discriminator. This file is never a submitted Kernel.
   It keeps every raw timing; hash and output lifetime are inside the interval,
   matching the existing developer profile boundary. These layer timings cannot
   replace the original whole-model scorer or prove a champion improvement. -/
open ExactRuntime ExactSuite

def r27LayerLabel : Layer → String
  | .linear rows input output _ _ _ => s!"linear:{rows}:{input}:{output}"
  | .rmsnorm rows width _ _ => s!"rmsnorm:{rows}:{width}"
  | .layernorm rows width _ _ _ => s!"layernorm:{rows}:{width}"
  | _ => "other"

def main (args : List String) : IO UInt32 := do
  let seedNat := ((args.getD 0 "27102901").toNat?).getD 27102901
  let seed := seedNat.toUInt32
  let repetitions := min 31 (max 1 (((args.getD 1 "7").toNat?).getD 7))
  IO.println "R27_PROFILE\tseed\tprofile\tkind\tbatch\tlayer\tlabel\trepetition\twarmup\tns\tchecksum"
  for profile in ["typical", "scale", "boundary"] do
    for kind in ["normal", "wide", "sparse"] do
      for batch in [1, 8] do
        let cell : Cell := ⟨"nmlp", batch, kind⟩
        let prepared := prepareProfile cell seed profile
        if prepared.samples != 1 then
          throw (IO.userError "Unexpected nmlp samples; refuse a partial profile")
        let mut state : Array Word × Array Word := (prepared.input, #[])
        let mut index := 0
        for layer in prepared.layers do
          let input := state
          for repetition in [0:repetitions + 1] do
            let start ← IO.monoNanosNow
            let checksum ← IO.lazyPure fun _ =>
              hashArr (layer.apply Submission.kernels (touch repetition input.1, input.2)).1
            let finish ← IO.monoNanosNow
            IO.println s!"R27_PROFILE\t{seedNat}\t{profile}\t{kind}\t{batch}\t{index}\t{r27LayerLabel layer}\t{repetition}\t{repetition == 0}\t{finish-start}\t{checksum}"
          state := layer.apply Submission.kernels state
          index := index + 1
  return 0
