"""Independent read-only assembly/pruning/root/runtime and review1 delta audit."""
from pathlib import Path
import ast,datetime,difflib,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
D=HERE.parent.parent.parent/'astra-workers/exact-arithmetic/bias-frontier'
H=lambda b:hashlib.sha256(b).hexdigest()
spec=importlib.util.spec_from_file_location('lex',ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py')
lex=importlib.util.module_from_spec(spec);spec.loader.exec_module(lex)

def decls(s):
    c=lex.lex(s)[0];bounds=[m.start() for m in lex.CMD.finditer(c)]+[len(c)]
    return [(m['kind'],m['name'],c[m.start():next(i for i in bounds if i>m.start())].strip()) for m in lex.DECL.finditer(c)]

def names(s):
    c=lex.lex(s)[0];scope=[];out={}
    for line in c.splitlines():
        m=re.match(r'namespace\s+(\S+)',line)
        if m:scope.append(('ns',m[1]));continue
        if re.match(r'section\b',line):scope.append(('section',''));continue
        if re.match(r'end\b',line):
            assert scope,line
            scope.pop();continue
        m=lex.DECL.match(line)
        if m:
            n='.'.join([x for kind,x in scope if kind=='ns']+[m['name']])
            assert n not in out,n
            out[n]=m['kind']
    assert not scope,scope
    return out

def binding(p,expected=None):
    b=p.read_bytes();h=H(b)
    if expected:assert h==expected,(p,h)
    return {'path':str(p.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def main():
    basepath=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
    bindings=[binding(basepath,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')]
    base=basepath.read_text();v1p=D/'Kernel-direct-bias-public-v1.lean';rawp=D/'Kernel-direct-bias-public-unpruned.lean';mathp=D/'MathOutlet-interface-v1.lean'
    bindings += [binding(v1p,'79e8f72155bb60ab042d48f687668021a6821a77bdf0449c85d6b55fac1df591'),binding(rawp),binding(mathp,'fae38339c987417e987bf3b320fc5cd7f9a05f725e5380de8364268f6fa19889')]
    v1=v1p.read_text();whole=rawp.read_text();math=mathp.read_text();m=json.loads((D/'public-v1-manifest.json').read_text())
    parts=[]
    for row in m['parts']:
        bindings.append(binding(D/row['path'],row['sha256']));parts.append((D/row['path']).read_text())
    builder=ast.parse((D/'build_full_public.py').read_text())
    wrapper=next(ast.literal_eval(n.value) for n in builder.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='wrapper' for t in n.targets))
    assert '\n\n'.join([base]+parts).replace('Submission','R19BiasBase')+wrapper==whole
    assert 'import Submission\n\n'+'\n\n'.join(parts)==math
    # Reconstruct each original removed theorem slice from the original source.
    replay=whole;removed=[]
    for row in m['removed_B2_ordinary_theorem_leaves']:
        n=row['name'];match=re.search(r'^theorem '+re.escape(n)+r'\b',replay,re.M);assert match
        e=re.search(r'^((?:@\[[^\n]*\]\s*)?(?:theorem|def|end|namespace|abbrev|instance|structure)\b|/[-*])',replay[match.end():],re.M);assert e
        end=match.end()+e.start();piece=replay[match.start():end]
        assert len(piece.encode())==row['bytes']
        assert len(re.findall(r'(?<![A-Za-z0-9_\x27?])'+re.escape(n)+r'(?![A-Za-z0-9_\x27?])',replay))==1
        assert match.start()<replay.index('namespace BranchlessRNESeed')
        removed.append({**row,'sha256':H(piece.encode())})
        replay=replay[:match.start()]+replay[end:]
    assert replay==v1 and sum(x['bytes'] for x in removed)==4814 and len(removed)==9
    assert ''.join(difflib.unified_diff(whole.splitlines(True),v1.splitlines(True),fromfile='unpruned',tofile='public-v1'))==(D/'public-source-budget.patch').read_text()
    nonproof=lambda s:[x for x in decls(s) if x[0] not in ('theorem','lemma')]
    assert nonproof(whole)==nonproof(v1)
    bnon=nonproof(base);basepart=v1[:v1.index('namespace BranchlessRNESeed')].replace('R19BiasBase','Submission')
    assert nonproof(basepart)==bnon
    runtime=(D/'Runtime-direct-bias.lean.inc').read_text()
    assert v1.count(runtime.replace('Submission','R19BiasBase'))==1
    assert math.count(runtime)==1
    known=names(v1);knownmath={**names(base),**names(math)}
    roots={}
    for fn,universe in [('HelperAudit-public-direct-bias.lean.inc',known),('HelperAudit-math-outlet.lean.inc',knownmath)]:
        rs=re.findall(r'^#print axioms (\S+)$',(D/fn).read_text(),re.M)
        assert len(rs)==len(set(rs))==48 and all(n in universe for n in rs)
        assert all(universe[n]=='theorem' for n in rs)
        roots[fn]=rs
        bindings.append(binding(D/fn))
    newtheorems=[n for n,k in names('\n\n'.join(parts)).items() if k=='theorem' and not n.endswith('.quotient_bias')]
    assert len(newtheorems)==44
    assert set(roots['HelperAudit-public-direct-bias.lean.inc'])==set(['Submission.'+op+'_spec' for op in ('add','mul','sum','bmm')]+[n.replace('Submission','R19BiasBase') for n in newtheorems])
    assert 'R14ExponentShift' not in '\n\n'.join(parts)
    required=['normal_guard','sum_guard','product_bounds','finiteScale_sum','normalCore_eq_roundP','normalCore_eq_core','guardedMul_spec']
    assert all('R19BiasBase.R19DirectBias.'+n in known for n in required)
    review=D/'public-proof-review1';rpub=review/v1p.name;rmath=review/mathp.name
    bindings += [binding(rpub,'fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5'),binding(rmath,'2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266')]
    prep=ast.parse((D/'prepare_public_review1.py').read_text());strings={}
    for n in prep.body:
        if isinstance(n,ast.Assign) and len(n.targets)==1 and isinstance(n.targets[0],ast.Name) and n.targets[0].id in ('old','new'):strings[n.targets[0].id]=ast.literal_eval(n.value)
    old,new=strings['old'],strings['new'];assert len(new.encode())-len(old.encode())==42
    for before,p in [(v1,rpub),(math,rmath)]:
        after=p.read_text();assert before.count(old)==1 and before.replace(old,new)==after and after.replace(new,old)==before
        assert nonproof(before)==nonproof(after)
    for fn in roots:assert (D/fn).read_bytes()==(review/fn).read_bytes()
    result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'STATIC_REVIEW_ONLY_NOT_RUN_HOLD_PREFIX_RESULTS','bindings':bindings,
      'assembly_exact':True,'MathOutlet_exact':True,'pruning_exact':True,'patch_exact':True,'removed':removed,
      'nonproof_declaration_counts':{'B2_original':len(bnon),'unpruned_complete':len(nonproof(whole)),'pruned_complete':len(nonproof(v1))},
      'B2_nonproof_bodies_identical_after_namespace_inverse':True,'entire_nonproof_pruning_identical':True,
      'runtime_full_fragment_identical_except_namespace':True,'roots':roots,'new_named_theorems':44,'old_public_specs':4,
      'runtime_roots_transitively_covered':'normalCore_eq_roundP and guardedMul_spec mention frozen runtime; no need to reinterpret48 as48newtheorems or require duplicate3definition roots',
      'R14_dependency_pit_locally_closed_in_source':required,'actual_public_namespace':'R19BiasBase, NOT prior illustrative R19Base',
      'namespace_claim':'32-root prior table is superseded for this exact full source; MathOutlet leaves four public specs on importedB2, publicKernel installs newMULwrapper',
      'review1':{'delta_bytes':42,'only_theorem':'R19BiasBase.R19BiasShape.exponentWord_nat','inverse_exact':True,'nonproof_identical':True,'roots_identical':True,
        'public_bytes':rpub.stat().st_size,'remaining_bytes':256000-rpub.stat().st_size,'math_bytes':rmath.stat().st_size,
        'status':'Preventive source-level rw-target refinement; not a reproduced Lean failure or accepted fix'},
      'validation':'No Lean statement/kernel/axiom/fullgate/performance validation performed. Source census does not establish elaboration.'}
    (HERE/'public79e8-and-review1-audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'counts':result['nonproof_declaration_counts'],'roots':48,'remaining':result['review1']['remaining_bytes'],'audit_sha':H((HERE/'public79e8-and-review1-audit.json').read_bytes())}))

if __name__=='__main__':main()
