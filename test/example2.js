const randomx = require('node-gyp-build')(__dirname + '/..')
let crypto = require('crypto');

	//mine        mining mode: 2080 MiB
	//verify      verification mode: 256 MiB
	//jit         JIT compiled mode (default: interpreter)
	//secure      W^X policy for JIT pages (default: off)
	//largePages  use large pages (default: small pages)
	//softAes     use software AES (default: hardware AES)
	//ssse3       use optimized Argon2 for SSSE3 CPUs
	//avx2        use optimized Argon2 for AVX2 CPUs
	
function difficulty(h){
	let count = 0;
	let i = 0;
	let bit = 0;
	do {
		bit = ((h[i/8|0]) & (1 << (7 - (i%8)))) >> (7 - (i%8));
		count += !(bit);
		i++;
	} while (!bit);
	return count;
}

let key = new Uint8Array(Buffer.from("0410591dc8b3bba89f949212982f05deeb4a1947e939c62679dfc7610c62"))

let vm;
console.log("Starting RandomX virtual machine...");
try{
	vm = randomx.RandomxVM(key.buffer, ["jit", "ssse3"]);
}
catch(e){
	console.log(e);
	return 0;
}
let hash;
let total = 0;
let target = 5;

console.log("Start hashing...");
for(let i = 0; i < 100; i++){
	let block = {
		"foo" : (crypto.randomBytes(32)).toString('hex'),
		"bar" : (crypto.randomBytes(32)).toString('hex'),
		"nonce" : 0
	}
	do {
		let str = ['foo','bar','nonce'].map(v => block[v].toString()).join("");
		let blob = crypto.createHmac('sha256', '').update(str).digest()
		hash = randomx.hash(vm, blob.buffer);
		block.nonce++;
	}
	while(!(difficulty(Buffer.from(hash, "hex")) >= target))
	console.log("Hash: " + new Uint8Array(hash) + " Nonce: " + (block.nonce - 1));
	total += (block.nonce - 1)
}
console.log("Average nonce: " + (total / 100))
