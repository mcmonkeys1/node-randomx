#pragma once

#include <napi.h>
#include "../binaries/randomx.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

class NrandomxVM : public Napi::ObjectWrap<NrandomxVM> {
public:
	static void Init(Napi::Env env, Napi::Object exports);
	static Napi::Object NewInstance(Napi::Value arg);
	NrandomxVM(const Napi::CallbackInfo& info);
	randomx_vm *vm;
	randomx_cache *cache;
	~NrandomxVM();
private:
	static Napi::FunctionReference constructor;
	Napi::Value GetValue(const Napi::CallbackInfo& info);
};