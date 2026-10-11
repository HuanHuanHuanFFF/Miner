// Read-only chain evidence. Never opens wallet files or signs transactions.
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
const [dependencyRoot, inputPath, destination, endpoint='wss://archive.chain.opentensor.ai:443'] = process.argv.slice(2);
if (!destination) throw Error('Usage: node read-dashboard-costs.mjs dependency-root inputs destination');
fs.mkdirSync(destination, {recursive:true});
const {ApiPromise, WsProvider} = await import(pathToFileURL(path.join(dependencyRoot,'@polkadot/api/index.js')));
const provider=new WsProvider(endpoint);
let api;
const timer=setTimeout(()=>{provider.disconnect().catch(()=>{});process.exit(2);},110000);
try {
 api=await ApiPromise.create({provider,noInitWarn:true});
 const finalized=await api.rpc.chain.getFinalizedHead();const header=await api.rpc.chain.getHeader(finalized);const at=await api.at(finalized);
 const sn=at.query.subtensorModule;
 const names=Object.keys(sn).filter(x=>/alphaIn|tao|alphaOut|blockAtRegistration|price/i.test(x));
 const pools={};for(const key of names.filter(x=>/^(subnet)?(alphaIn|taoIn|alphaOut|tao)$/i.test(x))) pools[key]=(await sn[key](66)).toString();
 const inputs=inputPath==='--price-only'?{registrations:[],failed_registrations:[],missing_registration_hotkeys:{}}:JSON.parse(fs.readFileSync(inputPath));const output={checked_at_utc:new Date().toISOString(),endpoint,finalized_block:header.number.toNumber(),finalized_hash:finalized.toHex(),pool_storage_names:names,pools,registrations:[],failed_registrations:inputs.failed_registrations,missing_registration_hotkeys:inputs.missing_registration_hotkeys};
 fs.writeFileSync(path.join(destination,'chain-read.json'),JSON.stringify(output,null,2)+'\n');
 for(const hint of inputs.registration_hints||[]){
  const proofHash=await api.rpc.chain.getBlockHash(hint.proof_block);const proof=await api.at(proofHash);
  const height=(await proof.query.subtensorModule.blockAtRegistration(66,hint.uid)).toNumber();const hash=await api.rpc.chain.getBlockHash(height);const block=await api.rpc.chain.getBlock(hash);
  const matches=block.block.extrinsics.map((tx,index)=>({tx,index})).filter(({tx})=>tx.method.section==='subtensorModule'&&/register/i.test(tx.method.method)&&tx.method.args.some(arg=>arg.toString()===hint.hotkey));
  if(matches.length!==1)throw Error('Registration history must identify exactly one transaction');const {tx,index}=matches[0];
  inputs.registrations.push({submission_ids:hint.submission_ids,hotkey:hint.hotkey,block:height,block_hash:hash.toHex(),tx_hash:tx.hash.toHex(),extrinsic_index:index});
 }
 for(const r of inputs.registrations){
  const hash=await api.rpc.chain.getBlockHash(r.block);if(hash.toHex()!==r.block_hash)throw Error('Block hash mismatch');
  const past=await api.at(hash);const events=await past.query.system.events();const block=await api.rpc.chain.getBlock(hash);const tx=block.block.extrinsics[r.extrinsic_index];if(tx.hash.toHex()!==r.tx_hash)throw Error('Tx mismatch');
  const ev=events.filter(e=>e.phase.isApplyExtrinsic&&e.phase.asApplyExtrinsic.toNumber()===r.extrinsic_index).map(e=>({section:e.event.section,method:e.event.method,data:e.event.data.toJSON(),fields:e.event.meta.fields.map(f=>f.name.toString())}));
  let burnBefore=null;try{const key=sn.burn.key(66);const raw=await api.rpc.state.getStorage(key,block.block.header.parentHash);if(raw.isSome)burnBefore=api.registry.createType('u64',raw.unwrap()).toString();}catch{}
  output.registrations.push({...r,call:tx.method.toHuman(),burn_before_block_rao:burnBefore,events:ev});
  fs.writeFileSync(path.join(destination,'chain-read.json'),JSON.stringify(output,null,2)+'\n');
 }
 if(sn.blockAtRegistration){for(const [sid,hotkey]of Object.entries(inputs.missing_registration_hotkeys)){const uid=await sn.uids(66,hotkey);output.missing_registration_hotkeys[sid]={hotkey,uid:uid.isSome?uid.unwrap().toNumber():null};if(uid.isSome)output.missing_registration_hotkeys[sid].block=(await sn.blockAtRegistration(66,uid.unwrap())).toString();}}
 fs.writeFileSync(path.join(destination,'chain-read.json'),JSON.stringify(output,null,2)+'\n');
 console.log(JSON.stringify({finalized_block:output.finalized_block,pools,registration_count:output.registrations.length,missing:output.missing_registration_hotkeys}));
} catch(error) {fs.writeFileSync(path.join(destination,'failure.json'),JSON.stringify({checked_at_utc:new Date().toISOString(),endpoint,error:String(error)},null,2)+'\n');throw error;
} finally {clearTimeout(timer);if(api)await api.disconnect();else await provider.disconnect();}
