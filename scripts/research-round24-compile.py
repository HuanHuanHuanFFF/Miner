"""Build the original benchmark shim unchanged and retain only text evidence."""
from pathlib import Path
import hashlib,json,os,shutil,subprocess
from round4 import ROOT,validate
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);names=spec['r24_compile_identity'];assert len(names)==3 and len(set(names))==3
    by={e['name']:e for e in spec['entries']};assert by[names[0]]['hashes']==by[names[1]]['hashes']
    upstream=Path(os.environ['DEFLATE_ROOT']);template=upstream/'validator/measure/candidate';toolchain=upstream/'validator/rust-toolchain.toml'
    root=Path(os.environ['RUNNER_TEMP'])/'r24-compile';root.mkdir();out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r24-compile';out.mkdir(parents=True)
    result={'status':'STARTED_COMPILER_DIAGNOSTIC','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'template_hashes':{f:sha(template/f)for f in ['Cargo.toml','lib.rs']},'toolchain_sha256':sha(toolchain),'build_command':['cargo','build','--release','--offline','-q'],'entries':{},'scope':'Originalbenchmark crate files and flags, compiled on runner without timing. This is code-identity evidence, not the original sandbox performance protocol or fullgate. No binaries are retained as artifacts.'}
    for n in names:
        e=by[n];p=root/n;(p/'src').mkdir(parents=True);shutil.copyfile(template/'Cargo.toml',p/'Cargo.toml');shutil.copyfile(template/'lib.rs',p/'src/lib.rs');shutil.copyfile(toolchain,p/'rust-toolchain.toml');shutil.copyfile(ROOT/e['path']/'parse.rs',p/'src/parse.rs');assert sha(p/'src/parse.rs')==e['hashes']['parse.rs']
        env=dict(os.environ);assert not env.get('RUSTFLAGS') and not env.get('CARGO_ENCODED_RUSTFLAGS')
        c=subprocess.run(result['build_command'],cwd=p,env=env,capture_output=True,text=True,timeout=300);(out/(n+'.build.log')).write_text(c.stdout+c.stderr);assert c.returncode==0
        lib=p/'target/release/libcandidate.so';assert lib.is_file();item={'source_files':e['hashes'],'library_sha256':sha(lib),'library_bytes':lib.stat().st_size,'sections':{}}
        for section in ['.text','.rodata']:
            target=p/(section[1:]+'.bin');copy=p/(section[1:]+'-copy.so');cp=subprocess.run(['objcopy','--dump-section',section+'='+str(target),str(lib),str(copy)],capture_output=True,text=True,timeout=30);assert cp.returncode==0 and target.is_file();item['sections'][section]={'sha256':sha(target),'bytes':target.stat().st_size}
        result['entries'][n]=item
    a,b,c=[result['entries'][n]for n in names]
    result.update(status='VERIFIED_ORIGINAL_TEMPLATE_COMPILER_COMPARISON',same_source_library_equal=a['library_sha256']==b['library_sha256'],same_source_sections_equal=a['sections']==b['sections'],candidate_library_equal=a['library_sha256']==c['library_sha256'],candidate_sections_equal=a['sections']==c['sections'])
    assert result['same_source_sections_equal'];(out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({k:result[k]for k in ['status','same_source_library_equal','same_source_sections_equal','candidate_library_equal','candidate_sections_equal']}))
    subprocess.run(['git','diff','--exit-code'],cwd=upstream,check=True)
if __name__=='__main__':main()
