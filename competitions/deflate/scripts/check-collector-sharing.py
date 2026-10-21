"""Windows regression at the actual downloaded-directory promotion seam."""
from pathlib import Path
import importlib.util,os,threading,time,uuid

ROOT=Path(__file__).resolve().parents[1]

def main():
    assert os.name=='nt','This regression exercises Windows directory sharing semantics'
    loader=importlib.util.spec_from_file_location('receipt_collector',ROOT/'scripts/collect-round4.py');m=importlib.util.module_from_spec(loader);loader.loader.exec_module(m)
    folder=ROOT/'evidence/round13'/('.collector-regression-'+uuid.uuid4().hex);folder.mkdir()
    stage=folder/'stage';stage.mkdir();p=stage/'Funs.lean';raw=b'-- fixed sharing regression\n';p.write_bytes(raw);target=folder/'extraction'
    held=p.open('rb')
    try:
        try:stage.rename(target)
        except PermissionError as exc:assert exc.winerror in(5,32);print('RED_ORIGINAL_RENAME',exc.winerror)
        else:raise AssertionError('Open-file fixture did not reproduce directory promotion failure')
        release=threading.Thread(target=lambda:(time.sleep(.4),held.close()));release.start()
        m.rename_download(stage,target);release.join();assert not stage.exists()and(target/'Funs.lean').read_bytes()==raw
        print('GREEN_BOUNDED_RETRY_BYTES_PRESERVED')
        other=folder/'other';other.mkdir();(other/'receipt.json').write_bytes(b'{}')
        try:m.rename_download(other,target)
        except FileExistsError:pass
        else:raise AssertionError('Existing receipt was replaced')
        assert (target/'Funs.lean').read_bytes()==raw and (other/'receipt.json').read_bytes()==b'{}'
        print('GREEN_EXISTING_RECEIPT_NEVER_REPLACED')
    finally:
        held.close()
    # Only these known generated files/directories are removed, no recursive
    # traversal or computed-path deletion of any user files.
    assert folder.resolve().parent==(ROOT/'evidence/round13').resolve()
    (target/'Funs.lean').unlink();target.rmdir();(other/'receipt.json').unlink();other.rmdir();folder.rmdir()

if __name__=='__main__':main()
