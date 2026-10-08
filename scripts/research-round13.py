"""Runner-only R13 native decode of actual candidate Rust."""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from round4 import ROOT,validate

def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
    spec=validate(os.environ['ROUND4_SPEC']);out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts';out.mkdir(exist_ok=True)
    if any(e.get('native_decode_reference')for e in spec['entries']):
        # Reuse the repository's own audited finite harness. Add explicit
        # 128/192/256KiB wrap cases; no private uploaded corpus is needed.
        path=ROOT/'scripts/research-round12-decode.py'
        loader=importlib.util.spec_from_file_location('r13_repo_decode',path);module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module)
        old=module.harness
        def expanded(s):
            text,pairs=old(s)
            needle='65537,98305,131073]'
            assert text.count(needle)==1
            return text.replace(needle,'65537,98305,131073,131071,131072,196607,196608,196609,262145]',1),pairs
        module.harness=expanded
        # The added six lengths × eight modes × two seeds produce96 cases.
        source=path.read_text().replace("int(count)==444", "int(count)==540")
        source=source.replace('444 finite reference/candidate', '540 finite reference/candidate')
        namespace=dict(module.__dict__);namespace['harness']=expanded;namespace['__name__']='r13_extended_decode'
        # Define main against the copied repository logic while preserving the
        # expanded harness binding; no uploaded package code is executed remotely.
        main_source=source[source.index('def main():'):source.index("if __name__")]
        exec(main_source,namespace);namespace['main']()
        print('R13_NATIVE_DECODE expected540 finite cases; not original gate')
    if spec.get('pc_prune_counts'):
        loader=importlib.util.spec_from_file_location('r13_pc_counts',ROOT/'scripts/research-round13-counts.py')
        module=importlib.util.module_from_spec(loader);loader.loader.exec_module(module);module.main()

if __name__=='__main__':main()
