#include "MSG.h"

std::pair<void*, size_t> MSG::serialize()
{
	return I_Serializable::serialize();
}
