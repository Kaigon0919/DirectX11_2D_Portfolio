#pragma once


#define SAFE_RELEASE(P) if(nullptr != P) { P->Release(); P = nullptr; }