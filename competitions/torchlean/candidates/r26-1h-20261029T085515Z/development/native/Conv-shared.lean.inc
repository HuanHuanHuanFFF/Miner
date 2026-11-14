/- Identical ContractExact window getters and term order; only reuse prepared
   input windows across filters, and prepared filters across output positions. -/
namespace Submission.R26SharedConv
open ExactRuntime
open R26WordFallback

@[noinline] def conv2d (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let hw := s.ho * s.wo
  if s.cout * hw == 0 then #[]
  else
    let k := s.cin * s.kh * s.kw
    let windows := Array.ofFn (n := hw) fun p =>
      prepare (Array.ofFn (n := k + 1) fun t =>
        if t.val < k then windowAt s inp (p.val / s.wo) (p.val % s.wo) t.val
        else oneW)
    let filters := Array.ofFn (n := s.cout) fun o =>
      prepare (Array.ofFn (n := k + 1) fun t =>
        if t.val < k then wts[o.val * k + t.val]! else b[o.val]!)
    Array.ofFn (n := s.cout * hw) fun q =>
      act relu (dotPrepared windows[q.val % hw]! filters[q.val / hw]!)

@[noinline] def depthwise (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let hw := s.ho * s.wo
  if s.cin * hw == 0 then #[]
  else
    let k := s.kh * s.kw
    let filters := Array.ofFn (n := s.cin) fun c =>
      prepare (Array.ofFn (n := k + 1) fun t =>
        if t.val < k then wts[c.val * k + t.val]! else b[c.val]!)
    Array.ofFn (n := s.cin * hw) fun q =>
      let c := q.val / hw
      let y := q.val / s.wo % s.ho
      let x := q.val % s.wo
      let window := prepare (Array.ofFn (n := k + 1) fun t =>
        if t.val < k then windowAt s inp y x (c * k + t.val) else oneW)
      act relu (dotPrepared window filters[c]!)

end Submission.R26SharedConv
