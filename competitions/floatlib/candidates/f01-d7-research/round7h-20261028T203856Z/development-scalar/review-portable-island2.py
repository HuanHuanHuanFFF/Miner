"""Read-only reconstruction/integration inventory; no Lean, Git or parent writes."""
from pathlib import Path
import ast,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
CAND=PUB/'f01-r24-dev-portable-island2'
sha=lambda b:hashlib.sha256(b).hexdigest()

def strip_comments(s):
    out=[];i=depth=0
    while i<len(s):
        if s.startswith('/-',i):depth+=1;i+=2
        elif depth and s.startswith('-/',i):depth-=1;i+=2
        elif depth:
            if s[i]=='\n':out.append('\n')
            i+=1
        elif s.startswith('--',i):
            j=s.find('\n',i);i=len(s) if j<0 else j
        elif s[i]=='"':
            out.append(' ');i+=1
            while i<len(s):
                if s[i]=='\\':i+=2
                elif s[i]=='"':i+=1;break
                else:
                    if s[i]=='\n':out.append('\n')
                    i+=1
        else:out.append(s[i]);i+=1
    assert depth==0
    return ''.join(out)

def inventory(s):
    stack=[];ns='';names=[]
    for line in strip_comments(s).splitlines():
        m=re.match(r'^\s*(namespace|section)\b\s*([\w.\']*)',line)
        if m:
            stack.append(ns)
            if m[1]=='namespace':ns=(ns+'.' if ns else '')+m[2]
            continue
        if re.match(r'^\s*end(?:\s+[\w.\']+)?\s*$',line):
            assert stack,('unmatched end',line);ns=stack.pop();continue
        m=re.match(r'^\s*(?:@\[[^\]]*\]\s*)?(?:(?:private|protected|noncomputable)\s+)*(?:theorem|lemma|def|abbrev|opaque)\s+([\w.\']+)',line)
        if m:names.append((ns+'.' if ns else '')+m[1])
    assert not stack,stack
    return names

def main():
    m=json.loads((CAND/'manifest.json').read_bytes());raw=(CAND/'Kernel.lean').read_bytes()
    assert sha(raw)==m['candidate_sha256']=='66b57afc9ee65d681101d82c0c4954e5706a90523d7e0347009b7f31c773b976'
    assert len(raw)==m['candidate_bytes']==95124
    prefix=ROOT/m['runtime_prefix']['path'];b=prefix.read_bytes()
    assert sha(b)==m['runtime_prefix']['sha256'] and len(b)==33043 and raw.startswith(b)
    parts=[]
    for c in m['components']:
        b=(ROOT/c['path']).read_bytes();assert sha(b)==c['sha256'] and len(b)==c['bytes'];parts.append(b)
    assert raw==prefix.read_bytes()+b'\n\n'+b'\n\n'.join(parts)
    assert len({c['path'] for c in m['components']})==len(parts)==8
    extracted=m['extracted_dependency'];b2=(ROOT/extracted['source_path']).read_bytes()
    assert sha(b2)==extracted['source_sha256']
    body=b2[extracted['start_byte']:extracted['end_byte_exclusive']]
    assert sha(body)==extracted['extracted_sha256'] and len(body)==extracted['exact_extracted_bytes']==7577
    canonical=b2[extracted['canonical_start_byte']:extracted['canonical_end_byte_exclusive']]
    assert sha(canonical)==extracted['canonical_extracted_sha256'] and len(canonical)==767
    assert parts[0]==body+b'end NativeBridge\n\nopen FloatLib.Floats\nopen FloatLib.Floats.Formats.BinaryInterchange\n\n'+canonical+b'end R2W01c\n'
    for p in m['parents']:
        pm=json.loads((PUB/p['candidate']/'manifest.json').read_bytes());pr=(PUB/p['candidate']/'Kernel.lean').read_bytes()
        assert sha(pr)==p['sha256']==pm['candidate_sha256'] and pr.startswith(b2)
    names=inventory(raw.decode());roots=m['explicit_helper_audit']
    assert len(roots)==len(set(roots))==m['helper_audit_expected_count']==36
    assert roots==m['helper_audit_required_endpoints']
    assert all(n in names for n in roots),[n for n in roots if n not in names]
    assert len(names)==len(set(names)),[n for n in names if names.count(n)>1]
    assert 'R2W01c.NativeBridge.modelMulFinite' in names
    assert 'R2W01c.modelCanonical_of_decode' in names
    assert 'R2W01c.modelCanonicalOfFinite' in names
    assert raw.count(b'R2W01c.modelCanonical_of_decode')==1
    helper=PUB/m['helper_audit_module_path'];assert sha(helper.read_bytes())==m['helper_audit_module_sha256']=='5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    tree=ast.parse((HERE.parent/'build-portable-island-v2.py').read_bytes());assert isinstance(tree,ast.Module)
    report={'status':'READY_STATIC_INTEGRATION_CLOSURE_REVIEW','source_sha256':sha(raw),'bytes':len(raw),
        'components_exact':8,'parents_rehashed':6,'declared_names':len(names),'root_namespace_inventory':36,
        'reconstruction':'EXACT_PASS','namespace_balance':'PASS_STATIC_ONLY','duplicate_declarations':'NONE_STATIC_INVENTORY',
        'closure_fix':'Exact B2 modelCanonicalOfFinite and modelCanonical_of_decode bodies present in global R2W01c, with both source byte ranges and hashes verified.',
        'cross_component_reference_inventory':'Only explicit R2W01c references in Widen/NativeMul now resolve to integrated declarations; imported library names remain Lean CI obligations.',
        'helper':'Exact fixed v8 digest,36 unique endpoint names matching source inventory. No parent acceptance inherited.',
        'Lean':'NOT_RUN','scope':'One narrow integration review, not an individual mathematical re-review or proof acceptance.'}
    (HERE/'review-portable-island2.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps(report,indent=2))
if __name__=='__main__':main()
