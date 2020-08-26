#include "vm.h"

bool getFlag(std::string str, std::vector<std::string> v){
	return std::find(v.begin(), v.end(), str) != v.end();
}

Napi::Object CreateVM(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
		if (info.Length() != 2) {
			throw Napi::Error::New(env, "C++ error. Expected exactly two arguments");
		}
		if(!info[0].IsArrayBuffer()){
			throw Napi::Error::New(env, "C++ error. Expected a UInt8Array");
		}
   	Napi::ArrayBuffer arrBuf = info[0].As<Napi::ArrayBuffer>();
   	Napi::Array arrFlags = info[1].As<Napi::Array>();

	const std::uint8_t* key = reinterpret_cast<std::uint8_t*>(arrBuf.Data());
	const int keySize = arrBuf.ByteLength() / sizeof(std::uint8_t);

	std::vector<std::string> nflags(arrFlags.Length());
	for(int i  = 0; i < arrFlags.Length(); i++){
		Napi::Value val = arrFlags[i];
		nflags.push_back(val.ToString());
	}

	randomx_flags flags = randomx_get_flags();

	bool mining = getFlag("mine", nflags);
	if (getFlag("auto", nflags)) {
		flags = randomx_get_flags();
	}
	else {
		//flags = RANDOMX_FLAG_DEFAULT;
		if (getFlag("ssse3", nflags)) {
			flags |= RANDOMX_FLAG_ARGON2_SSSE3;
		}
		if (getFlag("avx2", nflags)) {
			flags |= RANDOMX_FLAG_ARGON2_AVX2;
		}
		if (!getFlag("softAes", nflags)) {
			flags |= RANDOMX_FLAG_HARD_AES;
		}
		if (getFlag("jit", nflags)) {
			flags |= RANDOMX_FLAG_JIT;
		}
	}
	if (getFlag("largepages", nflags)) {
		flags |= RANDOMX_FLAG_LARGE_PAGES;
	}
	if (mining) {
		flags |= RANDOMX_FLAG_FULL_MEM;
	}

	randomx_cache *myCache = randomx_alloc_cache(flags);
	if (myCache == nullptr) {
		throw Napi::Error::New(env, "C++ error: randomx_alloc_cache() error");
	}

	randomx_init_cache(myCache, key, keySize);
	randomx_dataset* dataset = nullptr;
	if(mining){
		dataset = randomx_alloc_dataset(flags);
		if (dataset == nullptr) {
			throw Napi::Error::New(env, "C++ error: randomx_alloc_dataset() error");
		}
		uint32_t datasetItemCount = randomx_dataset_item_count();
		randomx_init_dataset(dataset, myCache, 0, datasetItemCount);
		randomx_release_cache(myCache);
		myCache = nullptr;
	}
	
	randomx_vm *myMachine = randomx_create_vm(flags, myCache, dataset);
	if (myMachine == nullptr) {
		throw Napi::Error::New(env, "C++ error: randomx_create_vm() error");
	}
    
    Napi::Object obj = NrandomxVM::NewInstance(Napi::External<randomx_vm>::New(info.Env(), myMachine));
	return obj;
}

Napi::String CalcHash(const Napi::CallbackInfo& info) {
   	char hash[RANDOMX_HASH_SIZE];
	NrandomxVM* nvm = Napi::ObjectWrap<NrandomxVM>::Unwrap(info[0].As<Napi::Object>());
   	Napi::String a = info[1].As<Napi::String>();
	std::string input(a.Utf8Value());

	uint32_t isize = input.size() + 1;
	const char* myInput = input.c_str();
	randomx_calculate_hash(nvm->vm, myInput, isize, hash);

	//randomx_dataset* dataset;
	//randomx_get_dataset_memory(dataset);

	//randomx_destroy_vm(nvm->vm);
	//randomx_release_dataset(dataset);

	std::stringstream ss;
	for (int i = 0; i < RANDOMX_HASH_SIZE; ++i)
	    ss << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)hash[i]);

	return Napi::String::New(info.Env(), ss.str());
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	NrandomxVM::Init(env, exports);
	exports.Set(Napi::String::New(env, "RandomxVM"),
	  Napi::Function::New(env, CreateVM));
	exports.Set(Napi::String::New(env, "hash"),
	  Napi::Function::New(env, CalcHash));
	return exports;
}

NODE_API_MODULE(addon, InitAll)