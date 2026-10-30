"""Own mapIdx experiment on hash-pinned retired public ResNet champion11.
No official tool/contract change; all new-source obligations require original gate.
"""
import hashlib
PIN='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
def transform(raw,submission,variant):
 assert submission==11 and hashlib.sha256(raw).hexdigest()==PIN
 assert variant=='mapidx-add-v2'
 s=raw.decode('utf-8')
 old='def Ybf (relu:Bool) (a b:Array Word):Array Word :=\n Ybd a.size λ i=>act relu (YaX a[i]! b[i]!)'
 new='def Ybf (relu:Bool) (a b:Array Word):Array Word :=\n a.mapIdx (λ i w=>act relu (YaX w b[i]!))'
 assert s.count(old)==1;s=s.replace(old,new)
 oldp='lemma ZdC:Ybf=addReluSpec:=by funext relu a b;simp only[Ybf,ZdA,addReluSpec,ZcQ];congr 1;funext i;rw[getElem!_pos a i؞ i.isLt];rfl'
 newp='lemma ZdC:Ybf=addReluSpec:=by\n funext relu a b\n rw [Ybf,Array.mapIdx_eq_mapFinIdx,Array.mapFinIdx_eq_ofFn]\n simp only [addReluSpec,ZcQ]\n congr 1\n funext i\n rw [getElem!_pos a i.val i.isLt]'
 assert s.count(oldp)==1;s=s.replace(oldp,newp)
 out=s.encode('utf-8');assert len(out)<=256000;return out
