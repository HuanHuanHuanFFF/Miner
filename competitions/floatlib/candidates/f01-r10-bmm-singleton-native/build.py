"""Port the one-term dot mechanism onto exact41; default is read-only verification."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, ast, hashlib, importlib.util, json, re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
CS = HERE.parent
ROUND = CS / 'f01-d7-research/round2h-20261023T170031Z'
PINS = {
    'f01-r8-combined-result-guard': '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
    'f01-d7-singleton-native-normalize': '47d429fe3a351a5e002f98c1f4cb95dfdc04368c268275508be758d176f3a347',
    'f01-d7-direct-nonfinite': '97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26',
}

def sha(b): return hashlib.sha256(b).hexdigest()

def fixed(name):
    b = (CS/name/'Kernel.lean').read_bytes(); assert sha(b) == PINS[name], name
    assert b'\r' not in b
    return b.decode('utf-8')

def rename_dispatcher(source):
    a = source.rindex('\ndef bmm (batch m n p : Nat)')
    z = source.index('\nend Submission', a)
    block = source[a:z]
    assert block.count('theorem bmm_spec') == 1
    renamed = re.sub(r'\bbmm_spec\b', 'bmmBeforeSingleton_spec', block)
    renamed = re.sub(r'\bbmm\b', 'bmmBeforeSingleton', renamed)
    assert renamed.count('bmmBeforeSingleton') == 4
    assert renamed.replace('bmmBeforeSingleton_spec','bmm_spec').replace('bmmBeforeSingleton','bmm') == block
    return source[:a]+renamed+source[z:], {'start': a, 'end': z, 'old': block, 'new': renamed}

def classifier_port(seed):
    changes=[]; s=seed
    for name, following, body in [
        ('model_toModel_isNaN','theorem toFloat32_isNaN',
         '  exact Submission.R7W05.model_toModel_isNaN x\n\n'),
        ('toFloat32_isNaN','theorem native_pack_unpack',
         '  exact Submission.R7W05.toFloat32_isNaN x\n\n'),
    ]:
        start=s.index('theorem '+name)
        a=s.index(':= by\n',start)+len(':= by\n');z=s.index(following,a)
        old=s[a:z];changes.append({'theorem':name,'old_body':old,'new_body':body,'old_body_sha256':sha(old.encode()),'new_body_sha256':sha(body.encode())})
        s=s[:a]+body+s[z:]
    for change in reversed(changes):
        assert s.count(change['new_body']) == 1
    return s, changes

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--write',action='store_true');args=ap.parse_args()
    parent=fixed('f01-r8-combined-result-guard');donor=fixed('f01-d7-singleton-native-normalize');base97=fixed('f01-d7-direct-nonfinite')
    seed_path=CS/'f01-d7-research/seed-normalize-block.lean';seed=seed_path.read_bytes().decode()
    native_path=CS/'f01-d7-research/singleton-native-product-block.lean';native=native_path.read_bytes().decode()
    assert sha(seed.encode())=='c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26'
    assert sha(native.encode())=='acbdd0a61024056d4764abb7ce3fed5c217639de7f4b44691e7c6195c73e3442'
    assert donor.count(seed)==1 and donor.count(native)==1
    donor_start=donor.index(seed);addition=donor[donor_start:]
    renamed97,_=rename_dispatcher(base97)
    assert renamed97+'\n\n'+addition==donor, 'Exact47d parent construction differs'
    assert 'namespace D7SeedNormalize' not in parent and 'namespace D7SingletonNative' not in parent and 'def singletonCore ' not in parent
    adapted_seed, proof_changes=classifier_port(seed)
    adapted=addition.replace(seed,adapted_seed,1)
    restored=adapted
    for c in reversed(proof_changes):restored=restored.replace(c['new_body'],c['old_body'],1)
    assert restored==addition
    renamed, rename=rename_dispatcher(parent)
    result=renamed+'\n\n'+adapted;data=result.encode();assert len(data)<=256000
    assert result[:len(renamed)]==renamed and result[len(renamed)+2:]==adapted
    inverse=result[:len(renamed)];inverse=inverse[:rename['start']]+rename['old']+inverse[rename['start']+len(rename['new']):]
    assert inverse==parent
    # All new runtime declarations are exact47d bytes; only two classifier proof bodies differ.
    assert adapted.count(native)==1
    runtime_normalizer=seed[seed.index('@[inline] def normalizeProductSeedRaw'):seed.index('\ntheorem normalizeProductSeedRaw_raw')]
    assert adapted.count(runtime_normalizer)==1
    core=addition[addition.index('def singletonCore '):addition.index('\ntheorem singletonCore_eq_reference')]
    assert adapted.count(core)==1
    sp=parent[parent.index('namespace R7SinglePassSum\n'):]
    assert result.count(sp)==1
    inv_spec=importlib.util.spec_from_file_location('r8_static_inventory',CS/'f01-r8-combined-result-guard/build.py')
    inv=importlib.util.module_from_spec(inv_spec);inv_spec.loader.exec_module(inv)
    decl=inv.declarations(result)
    names=['Submission.'+n for n in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']]
    assert all(len(decl.get(n,[]))==1 for n in names)
    assert all(len(v)==1 for k,v in decl.items() if k.startswith(('D7SeedNormalize.','D7SingletonNative.','Submission.singletonCore')))
    gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree=ast.parse(gate.read_text())
    def value(n):return next(x.value for x in tree.body if isinstance(x,ast.Assign) and any(isinstance(t,ast.Name) and t.id==n for t in x.targets))
    assert not re.compile(ast.literal_eval(value('BANNED').args[0])).search(result)
    assert [ln for ln in result.splitlines() if re.search(r'\bimport\b',ln)]==['import ContractTensor']
    env={'re':re,'OPTIONS':ast.literal_eval(value('OPTIONS'))};fn=next(x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name=='options')
    exec(compile(ast.Module(body=[fn],type_ignores=[]),str(gate),'exec'),env);assert env['options'](result) is None
    attrs=ast.literal_eval(value('ATTRIBUTES'))
    for group in re.findall(r'@\[([^\]]*)\]',result):
        for attr in group.split(','):assert attr.split()[-1] in attrs
    now=datetime.now(timezone.utc).isoformat()
    manifest={'candidate':HERE.name,'candidate_file':'Kernel.lean','candidate_sha256':sha(data),'candidate_bytes':len(data),'created_at_utc':now,
              'parent':'f01-r8-combined-result-guard','parent_sha256':PINS['f01-r8-combined-result-guard'],
              'mechanism_source':'f01-d7-singleton-native-normalize','mechanism_source_sha256':PINS['f01-d7-singleton-native-normalize'],
              'mechanism':'Onlyn=1: nativeproduct once; nonNaN product directly wrapped, NaN usesexactoriginalrawSubmission.mul; normalize onlyrawnegativezero topositivezero. This removesgeneralNat dotloop andinitialnative+0 add. Alln!=1 call exact41 dispatcher.',
              'proof_port':'Exact old47d runtime andsingleton proof retained. Onlytwo duplicate seedclassifier proofbodies delegate toalreadyaccepted41 R7W05 lemmas; old47d itself remainsunvalidated.',
              'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_FULL_COMPOSITION','full_gate':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED',
              'preservation':'All41 bytes preserved except exact reversible finalbmm/spec renaming. Originalscalar,sum,R7SinglePassSum,replay,packed/direct code andlicences unchanged. Newproof/runtime append only.',
              'build_script_sha256':sha(Path(__file__).read_bytes())}
    prior=json.loads((ROUND/'astra-bmm.json').read_text())
    report={**prior,'state':'CANDIDATE_BUILT_STATIC_ONLY_PENDING_FINAL_REVIEW','built_at_utc':now,'candidate':manifest,
            'donor_exact_reconstruction':{'old97f_plus_exactaddition_recovers47d':True,'donor_addition_bytes':len(addition.encode()),'donor_addition_sha256':sha(addition.encode())},
            'classifier_proof_changes':proof_changes,'adapted_addition_sha256':sha(adapted.encode()),'adapted_addition_bytes':len(adapted.encode()),
            'dispatcher_rename':rename,'inverse_parent_sha256':sha(inverse.encode()),'singlepass_tail_sha256':sha(sp.encode()),'singlepass_tail_byte_preserved':True,
            'runtime_identity':{'normalizer_sha256':sha(runtime_normalizer.encode()),'native_helper_sha256':sha(native.encode()),'singleton_core_sha256':sha(core.encode()),'all_three_exact47d':True},
            'static_policy':'PASS_IMPORT_SIZE_BANNED_OPTIONS_ATTRIBUTES','namespace_balance':True,'four_exports_specs':{n:decl[n] for n in names},
            'size_margin':256000-len(data),'remaining':['Exact candidateLean/axiom/kernel replayNOT_RUN','Completechecksums/25pairedrounds inallthreeDgroupsNOT_RUN','C/assembly/wholegainUNKNOWN'],
            'next_test':'D originalfullgate onexact candidate+41, allobserversoff, sourcefreeze beforeunused846/extra groups. No componentgain addition.'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data);(HERE/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        (ROUND/'astra-bmm.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes()==data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256']==sha(data)
    print(json.dumps({'sha256':sha(data),'bytes':len(data),'margin':256000-len(data),'donor_reproduced':True,'runtime_donor_unchanged':True,'exact_Lean':'NOT_RUN'}))

if __name__=='__main__':main()
