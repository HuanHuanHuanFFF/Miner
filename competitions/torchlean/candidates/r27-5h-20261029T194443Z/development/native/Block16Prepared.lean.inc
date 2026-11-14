namespace R27Block16
@[specialize] def sum (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) : Nat -> ؾ -> ػ -> ػ
 | 0,_,a=>a
 | fuel+1,k,a=>if h:k<n then sum n f fuel (k+1) (a+f k h) else a
@[specialize] def groups (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ) : Nat -> ؾ -> ػ -> ػ -> ػ
 | 0,k,hi,lo=>QY6G n f B bw hi lo k
 | fuel+1,k,hi,lo=>
   let q:=sum n f 16 k 0
   groups n f B bw fuel (k+16) (QhiS hi lo q) (lo+q)
@[inline] def run (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ)
 (hi lo:ػ) (k:ؾ):ػ:=groups n f B bw (n.toNat/16) k hi lo
end R27Block16
