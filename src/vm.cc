#include "vm.h"

NrandomxVM::NrandomxVM(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NrandomxVM>(info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	randomx_vm *myMachine = info[0].As<Napi::External<randomx_vm>>().Data();
	this->vm = myMachine;
};

Napi::FunctionReference NrandomxVM::constructor;

void NrandomxVM::Init(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);

	Napi::Function func = DefineClass(env, "NrandomxVM", {});
	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();
	exports.Set("NrandomxVM", func);
}

Napi::Object NrandomxVM::NewInstance(Napi::Value arg) {
	Napi::Object obj = constructor.New({ arg });
	return obj;
}

void NrandomxVM::Finalize(Napi::Env env) {
	//experimantial may need to release dataset also ??
	std::cout << "node-randomx: Attempting to release VM" << std::endl;
	randomx_destroy_vm(this->vm);
	std::cout << "node-randomx: randomx_destroy_vm ran" << std::endl;
}

NrandomxVM::~NrandomxVM() {
	std::cout << "node-randomx: D'tor attempting to release VM" << std::endl;
	randomx_destroy_vm(this->vm);
	std::cout << "node-randomx: D'tor randomx_destroy_vm ran" << std::endl;
}