namespace R27Block16
@[inline] def sum (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (k:ؾ):ػ:=
 let a0:=if h:k<n then f k h else 0
 let k1:=k+1
 let a1:=if h:k1<n then f k1 h else 0
 let k2:=k+2
 let a2:=if h:k2<n then f k2 h else 0
 let k3:=k+3
 let a3:=if h:k3<n then f k3 h else 0
 let k4:=k+4
 let a4:=if h:k4<n then f k4 h else 0
 let k5:=k+5
 let a5:=if h:k5<n then f k5 h else 0
 let k6:=k+6
 let a6:=if h:k6<n then f k6 h else 0
 let k7:=k+7
 let a7:=if h:k7<n then f k7 h else 0
 let k8:=k+8
 let a8:=if h:k8<n then f k8 h else 0
 let k9:=k+9
 let a9:=if h:k9<n then f k9 h else 0
 let k10:=k+10
 let a10:=if h:k10<n then f k10 h else 0
 let k11:=k+11
 let a11:=if h:k11<n then f k11 h else 0
 let k12:=k+12
 let a12:=if h:k12<n then f k12 h else 0
 let k13:=k+13
 let a13:=if h:k13<n then f k13 h else 0
 let k14:=k+14
 let a14:=if h:k14<n then f k14 h else 0
 let k15:=k+15
 let a15:=if h:k15<n then f k15 h else 0
 a0+a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12+a13+a14+a15
@[specialize] def groups (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ) : Nat -> ؾ -> ػ -> ػ -> ػ
 | 0,k,hi,lo=>QY6G n f B bw hi lo k
 | fuel+1,k,hi,lo=>
   let q:=sum n f k
   groups n f B bw fuel (k+16) (QhiS hi lo q) (lo+q)
@[inline] def run (n:ؾ) (f:(k:ؾ) -> k<n -> ػ) (B:ػ) (bw:ؼ)
 (hi lo:ػ) (k:ؾ):ػ:=groups n f B bw (n.toNat/16) k hi lo
end R27Block16
