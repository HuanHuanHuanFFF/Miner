from pathlib import Path
from datetime import datetime,timezone
import base64,hashlib,json,zipfile,io
H=Path(__file__).resolve().parent;E=Path('E:/Download');mp=E/'R7-W11-base64-chunks-manifest.json';mb=mp.read_bytes()
assert hashlib.sha256(mb).hexdigest()=='490ae61804f552ec9093f8d6fb4041eac6a94135e96513e0b7ae066989e5199e'
m=json.loads(mb);assert m['chunk_count']==15 and len(m['chunks'])==15;assert m['original_bytes']==8798280
out=bytearray();rows=[]
for i,c in enumerate(m['chunks'],1):
 assert c['order']==i and c['raw_offset_start']==len(out)
 p=(E/c['filename']).resolve();assert p.is_relative_to(E.resolve()) and p.parent==E.resolve()
 b=p.read_bytes();assert len(b)==c['text_bytes'] and hashlib.sha256(b).hexdigest()==c['text_sha256']
 raw=base64.b64decode(b,validate=True);assert len(raw)==c['raw_bytes'] and hashlib.sha256(raw).hexdigest()==c['raw_sha256']
 assert c['raw_offset_end_exclusive']==len(out)+len(raw);out.extend(raw);rows.append({'filename':c['filename'],'encoded_sha256':c['text_sha256'],'decoded_sha256':c['raw_sha256'],'decoded_bytes':len(raw)})
assert len(out)==8798280 and hashlib.sha256(out).hexdigest()==m['original_sha256']=='18cec34b9ac33146e9144fb7dd7e31d49891b5355a0c7bc7501204464eb7b7f7'
with zipfile.ZipFile(io.BytesIO(out)) as z:
 entries=z.infolist();inventory={'members':len(entries),'uncompressed_bytes':sum(x.file_size for x in entries),'largest':sorted([{'file':x.filename,'bytes':x.file_size} for x in entries],key=lambda x:x['bytes'],reverse=True)[:8]}
 assert len(entries)<1000 and inventory['uncompressed_bytes']<150000000
 assert z.testzip() is None
 binaries=[]
 for x in entries:
  p=Path(x.filename);assert not p.is_absolute() and '..' not in p.parts and not x.is_dir()
  assert ((x.external_attr>>16)&0o170000)!=0o120000
  data=z.read(x)
  if data.startswith(b'\x7fELF') or p.suffix in ['.o','.so','.olean','.dll','.exe']:binaries.append(x.filename)
 assert not binaries
dest=H/'web/R7-W11/recovered-original.zip';dest.parent.mkdir(parents=True,exist_ok=True)
if dest.exists():assert dest.read_bytes()==out
else:dest.write_bytes(out)
(dest.parent/'recovery-manifest-original.json').write_bytes(mb)
receipt={'recovered_at_utc':datetime.now(timezone.utc).isoformat(),'original_zip_sha256':hashlib.sha256(out).hexdigest(),'original_zip_bytes':len(out),'recovery_manifest_sha256':hashlib.sha256(mb).hexdigest(),'parts_verified':rows,'zip_crc':'PASS','binary_members':binaries,'inventory':inventory,'workspace_archive':str(dest),'scope':'StrictBase64 decode of inboundoriginalbytes; originaltotalSHA/CRC checked. No downloaded script/object/toolchain executed. Eoriginalcopy/extraction pending separately.'}
(dest.parent/'reconstruction-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
print(json.dumps({k:v for k,v in receipt.items() if k!='parts_verified'},indent=2))
