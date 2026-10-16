(function(root){
'use strict';
const day = d => /^\d{4}-\d{2}-\d{2}$/.test(d) && !Number.isNaN(Date.parse(d)) && new Date(d).toISOString().slice(0,10)===d;
function validate(r,rows=[]){
 if(!r || !day(r.date) || !['Öğle','Akşam'].includes(r.meal) || !['plate','surplus','prep'].includes(r.type) || !['demo','sensor'].includes(r.source)) throw Error('Tarih, öğün, tür veya kaynak geçersiz.');
 for(const k of ['weight','people','produced','planned']) if(!Number.isFinite(r[k]) || r[k]<=0 || r[k]>1e7) throw Error('Ağırlık, kişi, üretim ve plan pozitif ve sonlu olmalı.');
 if(!Number.isInteger(r.people)||!Number.isInteger(r.planned)) throw Error('Kişi sayıları tam sayı olmalı.');
 const same=rows.filter(x=>x.date===r.date&&x.meal===r.meal&&x.source===r.source);
 if(same.some(x=>x.people!==r.people||x.produced!==r.produced||x.planned!==r.planned)) throw Error('Aynı servis için kişi, üretim ve plan bilgileri önceki kayıtla aynı olmalı.');
 if(same.reduce((n,x)=>n+x.weight,0)+r.weight>r.produced*1000) throw Error('Servis toplam atığı üretim ağırlığını aşamaz.');
 return r;
}
function metrics(rows){
 const services=new Map(); for(const r of rows) services.set(r.date+'|'+r.meal,r);
 const sum=k=>[...services.values()].reduce((s,r)=>s+r[k],0);
 const weight=rows.reduce((s,r)=>s+r.weight,0),people=sum('people'),produced=sum('produced'),planned=sum('planned');
 return {weight,people,produced,planned,gpp:people?weight/people:null,surplus:produced?rows.filter(r=>r.type==='surplus').reduce((s,r)=>s+r.weight,0)/(produced*1000)*100:null,delta:planned?Math.abs(planned-people)/planned*100:null};
}
function trend(rows,end){if(!day(end))return []; return Array.from({length:7},(_,i)=>{const d=new Date(end+'T12:00:00Z');d.setUTCDate(d.getUTCDate()-6+i);const date=d.toISOString().slice(0,10);return {date,value:metrics(rows.filter(r=>r.date===date)).gpp};});}
function effect(base,post){if(!Number.isFinite(base)||base<=0||!Number.isFinite(post)||post<0)throw Error('Baseline pozitif, son değer sıfır veya pozitif olmalı.');return (base-post)/base*100;}
function sensor(d){return d && typeof d.device_uid==='string' && d.device_uid.length>0 && d.device_uid.length<=100 && typeof d.calibration_version==='string' && d.calibration_version.length>0 && d.calibration_version.length<=100 && typeof d.stable==='boolean' && Number.isFinite(d.weight_g) && d.weight_g>=0 && d.weight_g<=1e7;}
const api={day,validate,metrics,trend,effect,sensor};if(typeof module!=='undefined')module.exports=api;else root.FC=api;
})(globalThis);
