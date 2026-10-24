from pathlib import Path
import hashlib,importlib.util,json,subprocess,tempfile,unittest
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
REL='competitions/floatlib/candidates/f01-d7-research/round6h-20261024T051445Z/capture-mainfull.py'

class DispatcherTests(unittest.TestCase):
 def run_case(self,mode):
  sp=importlib.util.spec_from_file_location('capture_dispatch_under_test',HERE.parent/'capture-codegen.py')
  m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
  with tempfile.TemporaryDirectory(dir=ROOT/'.runtime/floatlib-r12-6h') as folder:
   repo=Path(folder);helper=repo/REL;helper.parent.mkdir(parents=True)
   body='from subprocess import CompletedProcess\ndef run_gate(argv,cwd,env,log_path,timeout,output,kernel):\n return CompletedProcess(argv,7), {"state":"CAPTURED","delegated":True}\n'
   if mode=='after_start_error':body='def run_gate(*args):\n raise RuntimeError("delegate already entered")\n'
   helper.write_text(body,encoding='utf-8',newline='\n')
   helper.with_name('scalar-capture-legacy-fd17.py').write_bytes((HERE/'scalar-capture-legacy-fd17.py').read_bytes())
   kernel=repo/'inputs/f01-current/Kernel.lean';kernel.parent.mkdir(parents=True);kernel.write_bytes(b'exact kernel\n')
   cfg={'round':'R12-20261024T051445Z','module':REL,'module_sha256':hashlib.sha256(helper.read_bytes()).hexdigest(),
        'legacy_sha256':'fd17f35a4ef1bc1b1df2afe5fcfe39691d88e7e605968acbe3c38df09df9078b','candidates':['f01-current']}
   if mode=='bad_hash':cfg['module_sha256']='0'*64
   plan={'candidates':[{'candidate':'f01-current','capture_codegen':True,'sha256':hashlib.sha256(kernel.read_bytes()).hexdigest()}]}
   if mode!='default':plan['r12_mainfull_capture']=cfg
   pp=repo/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json';pp.parent.mkdir(parents=True);pp.write_text(json.dumps(plan),encoding='utf-8')
   calls=[]
   def legacy(*args):calls.append(args);return subprocess.CompletedProcess(args[0],7),{'state':'CAPTURED','errors':[]}
   m._submission_run_gate=legacy
   argv=['unchanged','gate'];env={'GITHUB_WORKSPACE':str(repo),'UNCHANGED':'yes'}
   if mode=='after_start_error':
    with self.assertRaisesRegex(RuntimeError,'already entered'):m.run_gate(argv,repo,env,repo/'log',9,repo/'out',kernel)
    self.assertFalse(calls);return
   proc,record=m.run_gate(argv,repo,env,repo/'log',9,repo/'out',kernel)
   self.assertEqual(proc.returncode,7);self.assertEqual(proc.args,argv)
   self.assertEqual(env,{'GITHUB_WORKSPACE':str(repo),'UNCHANGED':'yes'})
   self.assertEqual(len(calls),0 if mode=='valid' else 1)
   self.assertEqual(record['state'],'UNKNOWN' if mode=='bad_hash' else 'CAPTURED')
 def test_valid_delegate(self):self.run_case('valid')
 def test_invalid_setup_runs_legacy_once(self):self.run_case('bad_hash')
 def test_default_behavior(self):self.run_case('default')
 def test_entered_delegate_is_never_retried(self):self.run_case('after_start_error')

if __name__=='__main__':unittest.main()
