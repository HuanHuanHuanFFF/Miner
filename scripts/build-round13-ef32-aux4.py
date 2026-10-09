"""Complement the useful three-byte fallback with a fourth-byte candidate key."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514';NAME='r13-514-ef32-aux4'

HELPER='''/// R13 fourth-byte candidate key; original three-byte matcher remains the fallback.
#[inline(always)]
pub fn r13_ef32_hash4(input: &[u8], p: usize) -> usize {
    let w=(input[p] as u32)|((input[p+1] as u32)<<8)|((input[p+2] as u32)<<16)|((input[p+3] as u32)<<24);
    (w.wrapping_mul(0x9E37_79B1)>>17) as usize
}
#[inline(always)]
pub fn r13_ef32_pick(input: &[u8], c: usize, c4: usize, p: usize) -> (usize, usize) {
    let l=ef32_probe(input,c,p);
    let l4=ef32_probe(input,c4,p);
    if l4>l { (l4,c4) } else { (l,c) }
}

'''

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('pub fn ef32_run(');b=original.index('// ─────────────── ETINY:',a);old=original[a:b];body=old
    edits=[('        let mut head = [0u32; 16384];','        let mut head = [0u32; 16384];\n        let mut head4 = [0u32;32768];',1),
        ('            let l = ef32_probe(input, c, p);','''            let h4 = r13_ef32_hash4(input,p);
            let c4 = head4[h4] as usize;
            head4[h4] = p as u32;
            let selected = r13_ef32_pick(input,c,c4,p);
            let l = selected.0;
            let c = selected.1;''',1)]
    for x,y,n in edits:assert body.count(x)==n;body=body.replace(x,y,1)
    restored=body
    for x,y,n in reversed(edits):assert restored.count(y)==n;restored=restored.replace(y,x,1)
    assert restored==old
    rust=original[:a]+body+original[b:];marker='/// EF32: f32 weights:';assert rust.count(marker)==1;rust=rust.replace(marker,HELPER+marker,1)
    assert rust.replace(HELPER,'',1).replace(body,old,1).encode()==raw['parse.rs']
    files={'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']};assert all(len(b)<=524288 for b in files.values())
    manifest={'candidate':NAME,'parent':'public514','comparison_baseline':'public514','formal_anchor_id':'514','native_relation':'decode_only','hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Keep original3-byte head and useful short matches; one additional32768-head four-byte key, choose only strictly longer byte-validated match and prefer original on ties. Same element alignment, skip, insertion and token format.',
        'evidence_basis':'Untimed original-position replay found12711 longer auxiliary matches,18740 added covered bytes,332 length>=7; wider3-byte keys found0. Captured-token prices showed original3-byte matches worth retaining.',
        'difference_from_previous':'Changes candidate information, not hash partition width or minimum length. Preserves short fallback; older generic D-family key5 supplement was costly and does not certify this narrower EF32 engine.',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'head_bytes_before':65536,'head_bytes_after':196608,'source_reversal':'Removing two new helpers and reversing two isolated EF32 run edits restores exact parent bytes. No routes/other engines changed.',
        'proof_status':'PARENT_PROOF_UNADAPTED_FOR_ADDITIONAL_HEAD_AND_PICK_HELPER; actual extraction and new frozen proof variant required',
        'semantic_status':'Token/search positions may change. Every selected candidate goes through original ef32_probe byte/window validation. Longer matches do not imply smaller final encoded output.',
        'performance_status':'UNKNOWN; opportunity coverage is not compressed-byte saving or timing gain','formal_submission_sent':False,
        'stop_condition':'Any decode/panic error stops. No worthwhile actual two-axis gain closes this fixed source; confirmation/gate still mandatory for promotion.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,b in files.items():(p/f).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
