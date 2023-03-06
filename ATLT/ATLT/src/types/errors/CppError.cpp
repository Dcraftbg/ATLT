#include "../core/Error.cpp"
class ALCppError : public ALError {
private:
	uint32_t ID = 0;
public:
	ALCppError(uint32_t id) {
		this->ID = id;
	}
	uint32_t getID() {
		return ID;
	}
	ALError::Type getType() {
		return CPPERROR;
	}
	ALString toStr() {
		return strerror(ID);
	}
};