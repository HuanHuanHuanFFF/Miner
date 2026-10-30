import ExactSuite
import Submission

/- Diagnostic only: old public seed42. Compile against unchanged public11.
   No official benchmark/contract/candidate mutation; no timing claim.
   It binds the Python convolution census to actual base outputs and guards. -/
open ExactRuntime

def main : IO Unit := do
  let profiles := ["legacy"]
  for profile in profiles do
    for kind in ["normal", "wide", "sparse"] do
      for batch in [1,4] do
        let c : ExactSuite.Cell := ⟨"cnn",batch,kind⟩
        let p := ExactSuite.prepareProfile c 42 profile
        for sample in [:p.samples] do
          let raw := p.input.extract (sample*p.size) ((sample+1)*p.size)
          for layer in [0,3,5,9] do
            match p.layers[layer]? with
            | some (.conv s relu w b) =>
              let inp := runModel Submission.kernels (p.layers.take layer) 1 p.size raw
              let k := s.cin*s.kh*s.kw
              let C := s.cout
              let bp := Submission.Yc inp inp.size 0
              let BW := Array.ofFn (n:=C) (fun o => Submission.Yc w k o.val)
              let xm := Submission.Ybh bp BW b
              let numerical := (Array.range C).all (fun o => Submission.Ybg BW[o]! b[o]! bp k xm)
              let structural := decide (s.kh≤s.h+2*s.pad ∧ s.kw≤s.w+2*s.pad ∧
                0<(s.h+2*s.pad)*(s.w+2*s.pad) ∧ k<256 ∧ C*k≤w.size ∧
                s.cin*((s.h+2*s.pad)*(s.w+2*s.pad))+(s.h+2*s.pad)*(s.w+2*s.pad)+
                  inp.size+w.size+C*(s.ho*s.wo)+s.ho*s.wo+s.stride≤4294967295)
              let specialized := s.kh==3 && s.kw==3 && decide (9≤k)
              let mut zero := 0
              for y in [:s.ho] do
                for x in [:s.wo] do
                  for t in [:k] do
                    if windowAt s inp y x t &&& 0x7fffffff == 0 then zero := zero+1
              let out := Submission.Ybp s relu inp w b
              IO.println s!"R28CENSUS|{profile}|{kind}|{batch}|{sample}|{layer}|{s.cin}|{s.cout}|{s.h}|{s.w}|{structural && numerical && specialized}|{zero}|{s.ho*s.wo*k}|{ExactSuite.hashArr inp}|{ExactSuite.hashArr out}"
            | _ => throw (IO.userError s!"Expected convolution at {layer}")
