#pragma once
/*
#include "ATLT/src/types/basic/ALString.cpp"
#include "ATLT/src/types/basic/ALBytesIOBuffer.cpp"
//#include "src/ExitGuard.cpp"
#include "ATLT/src/types/adv/ALHashmap.cpp"
#include "ATLT/src/types/basic/ALList.cpp"
#include "ATLT/src/types/basic/filesys/ALFile.cpp"
#include "ATLT/src/types/core/Error.cpp"
*/
#include "ATLT/ALString.h"
#include "ATLT/ALBytesIOBuffer.h"
#include "ATLT/ALHashmap.h"
#include "ATLT/ALList.h"
#include "ATLT/ALFile.h"
//#include "ATLT/Error.h"
#include "ATLT/Helper.h"
#include "ATLT/BasicExceptionStack.h"
#include "ATLT/BasicException.h"
//namespace ATLT {
//	void Exit(ALError& err) {
//		ALExitGuardian(err);
//	}
//	static inline void ALExitGuardian(ALError& err);
//}
//static inline uint32_t ALExitGuardian(ALError& err) {return err.getID();}